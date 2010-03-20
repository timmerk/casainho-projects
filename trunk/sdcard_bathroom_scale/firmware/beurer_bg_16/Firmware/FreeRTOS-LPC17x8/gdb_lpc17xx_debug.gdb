#
# MicropendousX LPC17xx Development Board
#
# http://www.MicropendousX.org
#
# Connect to a debugger controlling a LPC17xx IC
#
# Start your OpenOCD gdb server before running
# this script with:  gdb -x gdb_lpc17xx_debug.gdb
#
# Note the 'monitor' command just passes its
# arguments to OpenOCD
#
# This file is released under the MIT License
#

# Connect to OpenOCD gdb server
target remote localhost:3333

# reset and halt the LPC17xx IC with OpenOCD commands
monitor reset
monitor halt

# load the firmware onto the device
load FreeRTOS_USB_Eth_Main.elf

# load the firmware's symbol table into gdb
file FreeRTOS_USB_Eth_Main.elf

# set a breakpoint on the first function in main()
br prvSetupHardware

# after the target starts and breakpoints, resume
monitor poll
echo -----------------------------------------------\n
monitor resume
monitor sleep 200
echo -----------------------------------------------\n
monitor poll
echo -----------------------------------------------\n

# now print the current value of a global variable
print dev_175x
