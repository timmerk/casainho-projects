#!/usr/bin/python
# encoding: utf-8
"""
RepStrap Extruder Communication Test

DESCRIPTION

This script can check the serial port configuration and conduct a basic verification of the firmware communication functionality

Please read the README.html usage.
"""

__author__ = "Saw Wong (sam@hellosam.net)"
__date__ = "2009/11/12"
__license__ = "GPL 3.0"

## Configuration Start ##
# You should change the following variable to reflect your Serial Port setup
COMM_PORT = "/dev/ttyACM0"
COMM_BAUDRATE = 38400
## Configuration End ##

import sys
from RepRapSerialComm import *

def sendPacket(p, CallBack):
    RetryCounter = 0
    sendFlag = True
    
    comm = RepRapSerialComm(port = COMM_PORT, baudrate = COMM_BAUDRATE)
    comm.reset()

    while RetryCounter < 10:
        # Send the Packet to slave.
        if sendFlag:
            comm.send(p)
            sendFlag = False

        # Read answer from slave.
        SlaveAnswer_Packet = comm.readback()
        if SlaveAnswer_Packet != None:
            if not(SlaveAnswer_Packet.rc != SimplePacket.RC_OK) and not(SlaveAnswer_Packet.get_8(0) != 1) and not(SlaveAnswer_Packet.id_received != SlaveAnswer_Packet.id()):
                # Execute the call back if there was no CRC mismatch on slave...
                (CallBack)(SlaveAnswer_Packet)
                return True

            if SlaveAnswer_Packet.rc != SimplePacket.RC_OK:
                print >> sys.stderr, datetime.now()
                print >> sys.stderr, "Slave -> Master communication error: RC: %d" %(SlaveAnswer_Packet.rc)
                print >> sys.stderr, " "

            if SlaveAnswer_Packet.get_8(0) != 1:
                print >> sys.stderr, datetime.now()
                print >> sys.stderr, "Master -> Slave communication error: response_code: %d" %(SlaveAnswer_Packet.get_8(0))
                print >> sys.stderr, " "

            if SlaveAnswer_Packet.id_received != SlaveAnswer_Packet.id():
                print >> sys.stderr, datetime.now()
                print >> sys.stderr, "Packet id error. id = %d; id_received = %d" % (SlaveAnswer_Packet.id(), SlaveAnswer_Packet.id_received)
                print >> sys.stderr, " "

            sendFlag = True
            RetryCounter += 1

    # There was to much errors...
    # Shut down system
    comm.reset()
    return None

def main(argv=None):
    comm = RepRapSerialComm(port = COMM_PORT, baudrate = COMM_BAUDRATE)

    print "Sleeping for 1 second for the serial port and firmware to settle..."
    time.sleep(1)

    print "Flushing communicaton channel..."
    comm.reset()
        
    print "Querying for Heater 1 temperature (Command 91)..."
    p = SimplePacket()
    p.add_8(0)
    p.add_8(91)
    sendPacket(p, print_temperature)
    
def print_temperature(SlaveAnswer_Packet):
    print "Reading back the response..."        
    print "Readback result code (1 for success, anything else - failure): " + str(SlaveAnswer_Packet.rc)
    if SlaveAnswer_Packet.rc == SimplePacket.RC_OK:
        print "The current temperature is: " + str(SlaveAnswer_Packet.get_16(1))

if __name__ == "__main__":
    main()
    
