CC      = arm-elf-gcc
LD      = arm-elf-ld -v
AR      = arm-elf-ar
AS      = arm-elf-as
CP      = arm-elf-objcopy
OD		= arm-elf-objdump

CFLAGS = -Wall -Wcast-align -Wcast-qual -Wimplicit
CFLAGS += -Wpointer-arith -Wswitch
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
CFLAGS  += -mcpu=arm7tdmi -I./ -c -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o
LDFLAGS  = -Map main.map -T linker_script-flash_memory.cmd
CPFLAGS = -O binary
ODFLAGS	= -x --syms


clean:
	-rm crt.lst crt.o main.o main.out main.map main.dmp main.bin \
	system.o timers.o lcd.o adc.o buttons.o isrsupport.o

all: main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp

main.out: crt.o main.o system.o timers.o lcd.o adc.o buttons.o isrsupport.o \
	linker_script-flash_memory.cmd 
	@ echo "..linking"
	$(LD) $(LDFLAGS) -o main.out crt.o main.o system.o timers.o lcd.o adc.o buttons.o \
	isrsupport.o libgcc.a libc.a libnewlib-lpc.a

crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s > crt.lst

main.o: main.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) main.c
	
system.o: system.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) system.c
	
timers.o: timers.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) timers.c
	
lcd.o: lcd.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) lcd.c
	
adc.o: adc.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) adc.c
	
buttons.o: buttons.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) buttons.c
	
isrsupport.o: isrsupport.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) isrsupport.c
										