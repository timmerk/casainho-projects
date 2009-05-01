NAME   = pedal_power_meter

CC      = arm-elf-gcc
LD      = arm-elf-ld -v
AR      = arm-elf-ar
AS      = arm-elf-as
CP      = arm-elf-objcopy
OD		= arm-elf-objdump

CFLAGS  = -I./ -c -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o
LFLAGS  =  -Map main.map -T linker_script-flash_memory.cmd
CPFLAGS = -O binary
ODFLAGS	= -x --syms

clean:
	-rm crt.lst main.lst crt.o main.o main.out main.hex main.map main.dmp main.bin

all: main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp

main.out: crt.o main.o  linker_script-flash_memory.cmd 
	@ echo "..linking"
	$(LD) $(LFLAGS) -o main.out  crt.o main.o

crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s > crt.lst

main.o: main.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) main.c
	
system.o: system.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) system.c	