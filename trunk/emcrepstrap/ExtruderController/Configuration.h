/****************************************************************************************
 * Here's where you define the overall electronics setup for your machine.
 ****************************************************************************************/

#define TEMPERATURE_SAMPLES 5
#define SERIAL_SPEED 38400

//the address for commands to listen to
#define RS485_ADDRESS 0 /* Keep this here even if we do not use RS485... */
#define PACKET_TIMEOUT 100

#define RX_ENABLE_PIN 4
#define TX_ENABLE_PIN 16

#define DEBUG_PIN 13

