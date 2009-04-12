NAME   = pedal_power_meter

# variables 
CC      = arm-elf-gcc
LD      = arm-elf-ld
AR      = arm-elf-ar
AS      = arm-elf-as
CP      = arm-elf-objcopy
OD		= arm-elf-objdump

CFLAGS  = -I./ -c -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o

# Uncomment one of each lines to build the code for running on flash or ram memory.
//LFLAGS  =  -Map main.map -T linker_script_ram.lds
LFLAGS  =  -Map main.map -T linker_script_flash.lds

CPFLAGS = --output-target=binary
ODFLAGS	= -x --syms

OBJECTS = crt.o main.o timer.o isrsupport.o lowlevelinit.o lcd.o adc.o


# make target called by Eclipse (Project -> Clean ...)
clean:
	-rm $(OBJECTS) crt.lst main.out main.bin main.map main.dmp

         
#make target called by Eclipse  (Project -> Build Project)
all:  main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp

main.out: $(OBJECTS)
	@ echo "..linking"
	$(LD) $(LFLAGS) -o main.out $(OBJECTS) libc.a libm.a libgcc.a

crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s > crt.lst

main.o: main.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) main.c
	
lowlevelinit.o: lowlevelinit.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) lowlevelinit.c
		
timer.o: timer.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) timer.c
	
isrsupport.o: isrsupport.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) isrsupport.c

lcd.o: lcd.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) lcd.c	

adc.o: adc.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) adc.c
