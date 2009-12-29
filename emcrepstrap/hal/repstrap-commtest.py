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

def sendPacket(self, p, CallBack):
    RetryCounter = 0

    while RetryCounter < 10:
        # Send the Packet to slave.
        self.comm.send(p)
        
        # Read answer from slave.
        SlaveAnswer = self.comm.readback()
        if SlaveAnswer != None:
            if SlaveAnswer.rc != SimplePacket.RC_OK:
                # There was a CRC mismatch on slave and we send again the command, since
                # slave do not execute the command if found a CRC mismatch.
                RetryCounter = RetryCounter  + 1
                print >> sys.stderr, "CRC mismatch on slave"

            else:
                # Execute the call back if there was no CRC mismatch on slave...
                (CallBack)(p)
                return True

    # There was to much CRC errors and/or timeouts...
    # Shut down system
    self.comm.reset()
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
    comm.send(p)
    
    print "Reading back the response..."
    p = comm.readback()
    while p == None:
        p = comm.readback()
        
    print "Readback result code (1 for success, anything else - failure): " + str(p.rc)
    if p.rc == SimplePacket.RC_OK: print "The current temperature is: " + str(p.get_16(1))
    print str(p.get_8(0))
    print str(p.get_8(1))
    print str(p.get_8(2))
    print str(p.get_8(3))


if __name__ == "__main__":
    main()
    
