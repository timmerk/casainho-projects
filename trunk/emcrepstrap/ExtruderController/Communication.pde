#include "SimplePacket.h"

SimplePacket masterPacket(rs485_tx);

// These are our query commands from the host
#define SLAVE_CMD_STATUS                80
/*  6 Byte.
 *  These bits will be pre-polled and cached by the controller, and return immediated on request
 *  For E-Stop trigger, E-Stop will be automatically flagged by microcontroller when those sistuation occurs
 *  Primary component bits are on LSB. (So 2nd byte Bit 0 represent the status of the primaary heater)
 *
 *  1st Byte: General
 *     Bit 0: E-Stop triggered (Clear when read)
 *     Bit 1: Machine online
 *  2nd Byte: Thermistor disconnected [E-Stop trigger]
 *  3rd Byte: Heater response [E-Stop trigger]
 *  4th Byte: Motor jammed [E-Stop trigger]
 *  5th Byte: No plastic
 *  6th Byte: Heater on
 */
#define SLAVE_CMD_TURN_ON               81
#define SLAVE_CMD_TURN_OFF              82

#define SLAVE_CMD_GET_HEATER1_PVSV      91
#define SLAVE_CMD_SET_HEATER1_SV        92

#define SLAVE_CMD_GET_MOTOR1_PVSV       95
#define SLAVE_CMD_SET_MOTOR1_SPEED      97

unsigned long packet_timeout = 0;
char packet_timeout_enabled = 0;

// Packet handling
void process_packets()
{
    if (packet_timeout_enabled != 0 && (signed long) (millis() - packet_timeout) >= 0)
    {
        // Sliently dropping timeout packet
        packet_timeout_enabled = 0;
        masterPacket.init();
        digitalWrite(DEBUG_PIN, LOW);
    }

    //do we have any data to process?
    if (Serial.available() > 0)
    {
        do
        {
            // grab a byte and process it.
            unsigned char d = Serial.read();
            masterPacket.process_byte(d);
        } while (!masterPacket.isFinished() && Serial.available() > 0);

        if (!masterPacket.isFinished() && masterPacket.getState() != PS_START)
        {
            digitalWrite(DEBUG_PIN, HIGH); /* Turns on debug LED while receiving data from serial (from a packet) */
            packet_timeout_enabled = 1;
            packet_timeout = millis() + PACKET_TIMEOUT;
        } else
        {
            digitalWrite(DEBUG_PIN, LOW);
        }
    }

    //do we have a finished packet?
    if (masterPacket.isFinished())
    {
        packet_timeout_enabled = 0;

        //only process packets intended for us.
        if (masterPacket.get_8(0) == RS485_ADDRESS)
        {
            last_packet = millis();

            if (masterPacket.getResponseCode() == RC_OK)
            {
                // take some action, if CRC is correct
                handle_query();

                /* Echo the packet id for verification -- packet id is the
                 * last byte received and sent on payload. */
                masterPacket.add_8(masterPacket.get_8(masterPacket.getLength()));
            }

            // send reply over RS485
            // This includes masterPacket.init();
            masterPacket.sendReply();

            return;
        }
    }
}

void handle_query()
{
    switch (masterPacket.get_8(1))
    {
        case SLAVE_CMD_STATUS:
            for (unsigned char i = 0; i < 6; i++)
            {
                masterPacket.add_8(status[i]);
            }
            break;

        case SLAVE_CMD_TURN_ON:
            turnOn();
            break;

        case SLAVE_CMD_TURN_OFF:
            turnOff();
            break;

        case SLAVE_CMD_GET_HEATER1_PVSV:
            masterPacket.add_16(heater1.getPV());
            masterPacket.add_16(heater1.getSV());
            break;

        case SLAVE_CMD_SET_HEATER1_SV:
            heater1.setSV(masterPacket.get_16(2));
            break;

        case SLAVE_CMD_GET_MOTOR1_PVSV:
            masterPacket.add_16(motor1.getPV());
            masterPacket.add_16(motor1.getSV());
            break;

        case SLAVE_CMD_SET_MOTOR1_SPEED:
            {
                int value = masterPacket.get_16(2);
                if (value >= -16383 && value < 16383)
                {
                    motor1.setSpeed(value);
                } else
                {
                    masterPacket.unsupported();
                }
            }
            break;

        default:
            masterPacket.unsupported();
            break;
    }
}

void rs485_tx(byte b)
{
    Serial.print(b, BYTE);
}

