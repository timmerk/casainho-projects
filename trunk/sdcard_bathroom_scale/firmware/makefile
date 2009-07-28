CC      = arm-elf-gcc
LD      = arm-elf-ld -v
AR      = arm-elf-ar
AS      = arm-elf-as
CP      = arm-elf-objcopy
OD		= arm-elf-objdump
SIZE		= arm-elf-size

THUMB    =
THUMB_IW =

CFLAGS = -Wall -Wcast-align -Wcast-qual -Wimplicit
CFLAGS += -Wpointer-arith -Wswitch
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused 
CFLAGS  += -mcpu=arm7tdmi $(THUMB_IW) -I./ -c -fno-common -g
O0 = -O0
OS = -Os
AFLAGS  = -ahls -mapcs-32 -g -o crt.o
LDFLAGS  = -Map main.map -T linker_script-flash_memory.cmd
CPFLAGS = -O binary
ODFLAGS	= -x --syms


clean:
	-rm crt.lst crt.o main.o main.out main.map main.dmp main.bin \
	system.o timers.o lcd.o isrsupport.o ios.o spi.o fatfs/mmc.o ff.o err.o rtc.o

all: main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp
	$(SIZE) main.out

main.out: crt.o main.o system.o timers.o lcd.o isrsupport.o ios.o spi.o ff.o \
	fatfs/mmc.o err.o rtc.o linker_script-flash_memory.cmd
	@ echo "..linking"
	$(LD) $(LDFLAGS) -o main.out crt.o main.o system.o timers.o lcd.o ios.o spi.o \
	fatfs/mmc.o ff.o err.o isrsupport.o rtc.o libgcc.a

crt.o: crt.s
	$(AS) $(AFLAGS) crt.s > crt.lst

main.o: main.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) main.c
	
system.o: system.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) system.c
	
timers.o: timers.c
	$(CC) $(CFLAGS) timers.c
	
lcd.o: lcd.c
	$(CC) $(THUMB) $(CFLAGS) lcd.c
	
isrsupport.o: isrsupport.c
	$(CC) $(CFLAGS) $(OS) isrsupport.c

ios.o: ios.c
	$(CC) $(THUMB) $(CFLAGS) ios.c
	
spi.o: spi.c
	$(CC) $(THUMB) $(CFLAGS) spi.c
	
fatfs/mmc: fatfs/mmc.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) fatfs/mmc.c
	
ff.o: fatfs/ff.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) fatfs/ff.c

err.o: err.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) err.c
	
rtc.o: rtc.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) rtc.c	
