CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AS = arm-none-eabi-as
CP = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar -r

CFLAGS = -Wall -Wcast-align -Wcast-qual -Wimplicit
CFLAGS += -Wpointer-arith -Wswitch
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused 
CFLAGS  += -mcpu=cortex-m3 -mthumb -mapcs-frame -I./ -c -fno-common -g
CFLAGS += -fmessage-length=0
CFLAGS += -fno-builtin
CFLAGS += -ffunction-sections
CFLAGS += -Wextra
CFLAGS += -D__thumb2__=1 
CFLAGS += -msoft-float 
CFLAGS += -mno-sched-prolog 
CFLAGS += -fno-hosted
CFLAGS += -mtune=cortex-m3
CFLAGS += -march=armv7-m
CFLAGS += -mfix-cortex-m3-ldrd

O0 = -O0
OS = -Os

AFLAGS  = -mcpu=cortex-m3 -mthumb -mapcs-frame -mthumb-interwork -g -o startup_LPC17xx.o

#LDFLAGS = --gc-sections
#LDFLAGS += -static
#LDFLAGS += -Wl,--start-group 
#LDFLAGS += -lc -lg -lstdc++ -lsupc++ 
#LDFLAGS += -lgcc -lm
#LDFLAGS += -Wl,--end-group 
LDFLAGS  = -T LPC17xx.ld

CPFLAGS = -O binary
ODFLAGS	= -x --syms


clean:
	-rm startup_LPC17xx.lst startup_LPC17xx.o main.o main.out main.map main.dmp main.bin \
	system_LPC17xx.o

all: main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp
	$(SIZE) main.out

main.out: startup_LPC17xx.o main.o system_LPC17xx.o LPC17xx.ld
	@ echo "..linking"
	$(LD) $(LDFLAGS) -o main.out startup_LPC17xx.o main.o system_LPC17xx.o

startup_LPC17xx.o: startup_LPC17xx.s
	$(AS) $(AFLAGS) startup_LPC17xx.s > startup_LPC17xx.lst

system_LPC17xx.o: system_LPC17xx.c
	$(CC) $(CFLAGS) $(OS) system_LPC17xx.c

main.o: main.c
	$(CC) $(CFLAGS) main.c
	
lcd.o: lcd.c
	$(CC) $(THUMB) $(CFLAGS) lcd.c
	
lcd_input.o: lcd_input.c
	$(CC) $(THUMB) $(CFLAGS) $(O0) lcd_input.c
	
spi.o: spi.c
	$(CC) $(THUMB) $(CFLAGS) spi.c
	
fatfs/mmc.o: fatfs/mmc.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) fatfs/mmc.c
	
fatfs/ff.o: fatfs/ff.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) fatfs/ff.c

err.o: err.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) err.c
	
rtc.o: rtc.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) rtc.c	

adc.o: adc.c
	$(CC) $(THUMB) $(CFLAGS) $(OS) adc.c