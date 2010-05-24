# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# WinAVR Makefile Template written by Eric B. Weddington, J�rg Wunsch, et al.
#  >> Modified for use with the LUFA project. <<
#
# Released to the Public Domain
#
# Altered for ARM Cortex-M3 by Opendous Inc. - 2010-01-05
#
# Additional material for this makefile was written by:
# Peter Fleury
# Tim Henigan
# Colin O'Flynn
# Reiner Patommel
# Markus Pfaff
# Sander Pool
# Frederik Rouleau
# Carlos Lamas
# Dean Camera
# Opendous Inc.
# Denver Gingerich
#
#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make program = Download the hex file to the device
#                Please customize the settings below first!
#
# make doxygen = Generate DoxyGen documentation for the project (must have
#                DoxyGen installed)
#
# make debug = Start debugging
#              Please customize the settings below first!
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# CPU architecture
CPU = cortex-m3

# Instruction Set to use (also known as CPU Mode)
CPU_MODE = mthumb

# Additional CPU flags
#CPU_FLAGS = -mapcs-frame -mthumb-interwork
CPU_FLAGS = -mapcs-frame
CPU_FLAGS_ASM = -mthumb-interwork

# Linker Script for the current MCU
LINKER_SCRIPT = LPC17xx.ld


# Target board (see library "Board Types" documentation, USER or blank for projects not requiring
# LUFA board drivers). If USER is selected, put custom board drivers in a directory called 
# "Board" inside the application directory.
BOARD  = USER


# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the 
#     processor frequency in Hz. You can then use this symbol in your source code to 
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_CLOCK below, as it is sourced by
#     F_CLOCK after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU = 12000000


# Input clock frequency.
#     This will define a symbol, F_CLOCK, in all source code files equal to the 
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections for high speed
#     clock generation for the USB and other subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock (via the CPU clock
#     adjust registers or the clock division fuses), this will be equal to F_CPU.
F_CLOCK = $(F_CPU)


# Output format. (can be srec, ihex, binary)
FORMAT = ihex


# Output Directory
OUTDIR = .


# Target file name (without extension).
TARGET = main


# Path to the LUFA library
LIBS_PATH = ../../libs
LUFA_PATH = $(LIBS_PATH)/LUFA
LPCUSB_PATH = $(LIBS_PATH)/LPCUSB
CMSIS_CORE_PATH = $(LIBS_PATH)/CMSIS/CM3/CoreSupport
CMSIS_DEVICE_PATH = $(LIBS_PATH)/CMSIS/CM3/DeviceSupport/NXP/LPC17xx
INCLUDE_PATH = $(LIBS_PATH)/CMSIS/CM3/INC/NXP/LPC17xx
WEBSERVER_PATH = ./
FREERTOS_PATH = ./FreeRTOS
FREERTOS_DEMO_DIR = ./CommonDemoTasks
FREERTOS_SOURCE_DIR = $(FREERTOS_PATH)/Source
FREERTOS_PORT_DIR = $(FREERTOS_PATH)/portable/GCC/ARM_CM3


# compile-time options - LUFA related
COMPILE_OPTS  = -D USB_DEVICE_ONLY
COMPILE_OPTS += -D FIXED_CONTROL_ENDPOINT_SIZE=8
COMPILE_OPTS += -D FIXED_NUM_CONFIGURATIONS=1
COMPILE_OPTS += -D USE_FLASH_DESCRIPTORS
COMPILE_OPTS += -D USE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"
# compile-time options - non LUFA related
COMPILE_OPTS += -D DEBUG
COMPILE_OPTS += -D PACK_STRUCT_END=__attribute\(\(packed\)\)
COMPILE_OPTS += -D ALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\)
# Microcontroller Model - the specific part number
COMPILE_OPTS += -D _LPC1758_
# Defines related to AVR to ARM conversion
COMPILE_OPTS += -D USB_SERIES_7_AVR=1


# List C source files here. (C dependencies are automatically generated.)
SRC = $(TARGET).c \
	  system_LPC17xx.c \


#	  Descriptors.c \
#	  Lib/RingBuff.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/DevChapter9.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/Endpoint.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/LowLevel.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/Events.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/USBInterrupt.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/USBTask.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/ConfigDescriptor.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/Class/Device/CDC.c \
#	  $(LUFA_PATH)/LUFA/Drivers/USB/Class/Host/CDC.c \


# List C++ source files here. (C dependencies are automatically generated.)
CPPSRC = 


# List Assembler source files here.
#     Make them always end in a capital .S.  Files ending in a lowercase .s
#     will not be considered source files but generated files (assembler
#     output from the compiler), and will be deleted upon "make clean"!
#     Even though the DOS/Win* filesystem matches both .s and .S the same,
#     it will preserve the spelling of the filenames, and gcc itself does
#     care about how the name is spelled on its command-line.
ASRC = 
ASRC += startup_LPC17xx.S
#ASRC += $(CMSIS_DEVICE_PATH)/startup/gcc/startup_LPC17xx.S


# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = .


# Optimization level, can be [0, 1, 2, 3, s]. 
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See libc FAQ.)
OPT = 0


# Debugging format.
#DEBUG = dwarf-2
DEBUG = 3


# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRAINCDIRS = $(LUFA_PATH)/ $(CMSIS_CORE_PATH)/ $(CMSIS_DEVICE_PATH)/ $(INCLUDE_PATH)/
EXTRAINCDIRS += $(FREERTOS_PATH)/include $(LPCUSB_PATH)/ ./webserver
EXTRAINCDIRS += $(FREERTOS_DEMO_DIR)/include $(FREERTOS_PORT_DIR)/


# Compiler flag to set the C Standard level.
#     c89   = "ANSI" C
#     gnu89 = c89 plus GCC extensions
#     c99   = ISO C99 standard (not yet fully implemented)
#     gnu99 = c99 plus GCC extensions
CSTANDARD = -std=gnu99


# Place -D or -U options here for C sources
CDEFS  = -DF_CPU=$(F_CPU)UL -DF_CLOCK=$(F_CLOCK)UL -DBOARD=BOARD_$(BOARD) $(COMPILE_OPTS)


# Place -D or -U options here for ASM sources
ADEFS = 


# Place -D or -U options here for C++ sources
CPPDEFS = -DF_CPU=$(F_CPU)UL
#CPPDEFS += -D__STDC_LIMIT_MACROS
#CPPDEFS += -D__STDC_CONSTANT_MACROS



#---------------- Compiler Options C ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -alhms...: create assembler listing
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS)
CFLAGS += -O$(OPT)
CFLAGS += -Wall
CFLAGS += -Wno-unused
CFLAGS += -Wno-comments
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
#CFLAGS += -Wundef
#CFLAGS += -funsigned-char
#CFLAGS += -funsigned-bitfields
#CFLAGS += -fno-inline-small-functions
#CFLAGS += -fpack-struct
#CFLAGS += -fshort-enums
#CFLAGS += -Wstrict-prototypes
#CFLAGS += -fno-unit-at-a-time
#CFLAGS += -Wunreachable-code
#CFLAGS += -Wsign-compare
CFLAGS += -Wa,-alhms=$(<:%.c=$(OBJDIR)/%.lst)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS += $(CSTANDARD)


#---------------- Compiler Options C++ ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -alhms...: create assembler listing
CPPFLAGS = -g$(DEBUG)
CPPFLAGS += $(CPPDEFS)
CPPFLAGS += -O$(OPT)
#CPPFLAGS += -funsigned-char
#CPPFLAGS += -funsigned-bitfields
#CPPFLAGS += -fpack-struct
#CPPFLAGS += -fshort-enums
#CPPFLAGS += -fno-exceptions
CPPFLAGS += -Wall
#CFLAGS += -Wundef
#CPPFLAGS += -mshort-calls
#CPPFLAGS += -fno-unit-at-a-time
#CPPFLAGS += -Wstrict-prototypes
#CPPFLAGS += -Wunreachable-code
#CPPFLAGS += -Wsign-compare
CPPFLAGS += -Wa,-alhms=$(<:%.cpp=$(OBJDIR)/%.lst)
CPPFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
#CPPFLAGS += $(CSTANDARD)


#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -alhms:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see libnew docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex 
#       dump that will be displayed for a given single line of source input.
ASFLAGS = -g$(DEBUG) $(ADEFS) -I. -I$(INCLUDE_PATH)/ -alhms=$(<:%.S=$(OBJDIR)/%.lst)


#---------------- Library Options ----------------
# Minimalistic printf version
PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt

# If this is left blank, then it will use the Standard printf version.
PRINTF_LIB = 
#PRINTF_LIB = $(PRINTF_LIB_MIN)
#PRINTF_LIB = $(PRINTF_LIB_FLOAT)


# Minimalistic scanf version
SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
SCANF_LIB_FLOAT = -Wl,-u,vfscanf -lscanf_flt

# If this is left blank, then it will use the Standard scanf version.
SCANF_LIB = 
#SCANF_LIB = $(SCANF_LIB_MIN)
#SCANF_LIB = $(SCANF_LIB_FLOAT)


MATH_LIB = -lm


# List any extra directories to look for libraries here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRALIBDIRS = 



#---------------- External Memory Options ----------------

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =



#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(TARGET).map
#LDFLAGS += -Wl,--relax 
LDFLAGS += --gc-sections
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(patsubst %,-L%,$(EXTRALIBDIRS))
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB)
LDFLAGS += -static
LDFLAGS += -Wl,--start-group 
#LDFLAGS += -L$(THUMB2GNULIB) -L$(THUMB2GNULIB2)
LDFLAGS += -lc -lg -lstdc++ -lsupc++ 
LDFLAGS += -lgcc -lm 
LDFLAGS += -Wl,--end-group 
#LDFLAGS += $(MATH_LIB)
#LDFLAGS += -T linker_script.x



#---------------- Programming Options ----------------

# ---------------------------------------------------------------------------
# Options for OpenOCD flash-programming
# Released to the Public Domain by Martin Thomas, Kaiserslautern, Germany 
# <eversmith(at)heizung-thomas(dot)de>
#
# Please read the OpenOCD user manual!
#
OOCD_LOADFILE=$(TARGET).hex
# if OpenOCD is in the $PATH just set OPENOCDEXE=openocd
OOCD_EXE=openocd
# interface and board/target settings (using the OOCD target-library here)
OOCD_CL=-f OpenOCD.cfg
# debug level
#OOCD_CL=-d3
OOCD_CL+=-d0
# initialize
OOCD_CL+=-c init
# show the targets
OOCD_CL+=-c targets
# increase JTAG frequency a little bit - can be disabled for tests
#OOCD_CL+= -c "jtag_khz 150"
# reset the target
OOCD_CL+=-c reset
# halt the target for loading
OOCD_CL+=-c halt
# sleep a bit to make sure halt occurs
OOCD_CL+=-c "sleep 200"
# wait for halt to finish
OOCD_CL+=-c wait_halt
# get info on flash
OOCD_CL+=-c "flash probe 0"
# get info on flash bank 0
OOCD_CL+=-c "flash info 0"
# flash-write and -verify
OOCD_CL+=-c "flash write_image erase unlock $(OOCD_LOADFILE)" -c "verify_image $(OOCD_LOADFILE)"
# sleep a bit to make sure everything completes
OOCD_CL+=-c "sleep 200"
# reset target
OOCD_CL+=-c "reset run"
# terminate OOCD after programming
OOCD_CL+=-c shutdown







# Programming hardware: alf avr910 avrisp bascom bsd 
# dt006 pavr picoweb pony-stk200 sp12 stk200 stk500
#
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE_PROGRAMMER = jtagmkII

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = usb

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep


# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude> 
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_FLAGS = -p $(CPU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)



#---------------- Debugging Options ----------------

# For simulavr only - target MCU frequency.
DEBUG_MFREQ = $(F_CPU)

# Set the DEBUG_UI to either gdb or insight.
# DEBUG_UI = gdb
DEBUG_UI = insight

# Set the debugging back-end to either avarice, simulavr.
DEBUG_BACKEND = avarice
#DEBUG_BACKEND = simulavr

# GDB Init Filename.
GDBINIT_FILE = __avr_gdbinit

# When using avarice settings for the JTAG
JTAG_DEV = /dev/com1

# Debugging port used to communicate between GDB / avarice / simulavr.
DEBUG_PORT = 4242

# Debugging host used to communicate between GDB / avarice / simulavr, normally
#     just set to localhost unless doing some sort of crazy debugging when 
#     avarice is running on a different computer.
DEBUG_HOST = localhost



#============================================================================


# Define programs and commands.
SHELL = sh
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc -T
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
READELF  = arm-none-eabi-readelf
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar -r
NM = arm-none-eabi-nm
REMOVE = rm -f
REMOVEDIR = rm -rf
COPY = cp
WINSHELL = cmd

# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before: 
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to COFF:
MSG_EXTENDED_COFF = Converting to Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling C:
MSG_COMPILING_CPP = Compiling C++:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:




# Define all object files.
OBJ = $(SRC:%.c=$(OBJDIR)/%.o) $(CPPSRC:%.cpp=$(OBJDIR)/%.o) $(ASRC:%.S=$(OBJDIR)/%.o) 

# Define all listing files.
LST = $(SRC:%.c=$(OBJDIR)/%.lst) $(CPPSRC:%.cpp=$(OBJDIR)/%.lst) $(ASRC:%.S=$(OBJDIR)/%.lst) 


# Compiler flags to generate dependency files.
#GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d
#GENDEPFLAGS = -MD $(OBJDIR)/$(@F).d
GENDEPFLAGS = -MMD -MP -MD


# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mcpu=$(CPU) -$(CPU_MODE) $(CPU_FLAGS) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_CPPFLAGS = -mcpu=$(CPU) -$(CPU_MODE) $(CPU_FLAGS) -I. -x c++ $(CPPFLAGS) $(GENDEPFLAGS)
#ALL_ASFLAGS = -mcpu=$(CPU) -$(CPU_MODE) $(CPU_FLAGS) -I. -x assembler-with-cpp $(ASFLAGS)
ALL_ASFLAGS = -mcpu=$(CPU) -$(CPU_MODE) $(CPU_FLAGS_ASM) $(ASFLAGS)
# only difference between Linker flags and CFLAGS is CPU_FLAGS_ASM as -mapcs-frame is not needed
ALL_CFLAGS_LINKER = -mcpu=$(CPU) -$(CPU_MODE) $(CPU_FLAGS_ASM)




# Default target.
#all: begin gccversion sizebefore build showliboptions showtarget sizeafter end
all: begin gccversion sizebefore build showtarget sizeafter end

# Change the build target to build a HEX file or a library.
build: elf hex bin srec lss sym
#build: lib


elf: $(TARGET).elf
hex: $(TARGET).hex
bin: $(TARGET).bin
srec: $(TARGET).srec
eep: $(TARGET).eep
lss: $(TARGET).lss
sym: $(TARGET).sym
LIBNAME=lib$(TARGET).a
lib: $(LIBNAME)



# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

end:
	@echo $(MSG_END)
	@echo


# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) $(MCU_FLAG) $(FORMAT_FLAG) $(TARGET).elf
MCU_FLAG = $(shell $(SIZE) --help | grep -- --mcu > /dev/null && echo --mcu=$(CPU) )
FORMAT_FLAG = $(shell $(SIZE) --help | grep -- --format=.*avr > /dev/null && echo --format=avr )

sizebefore:
	@if test -f $(TARGET).elf; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); \
	2>/dev/null; echo; fi

sizeafter:
	@if test -f $(TARGET).elf; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); \
	2>/dev/null; echo; fi

$(LUFA_PATH)/LUFA/LUFA_Events.lst:
	@make -C $(LUFA_PATH)/LUFA/LUFA_Events.lst

checkinvalidevents: $(LUFA_PATH)/LUFA/LUFA_Events.lst
	@echo
	@echo Checking for invalid events...
	@$(shell) avr-nm $(OBJ) | sed -n -e 's/^.*EVENT_/EVENT_/p' | \
	                 grep -F -v --file=$(LUFA_PATH)/LUFA/LUFA_Events.lst > InvalidEvents.tmp || true
	@sed -n -e 's/^/  WARNING - INVALID EVENT NAME: /p' InvalidEvents.tmp
	@if test -s InvalidEvents.tmp; then exit 1; fi

showliboptions:
	@echo
	@echo ---- Compile Time Library Options ----
	@for i in $(LUFA_OPTS:-D%=%); do \
		echo $$i; \
	done
	@echo --------------------------------------

showtarget:
	@echo
	@echo --------- Target Information ---------
	@echo ARM Model: $(CPU)
	@echo Board:     $(BOARD)
	@echo Clock:     $(F_CPU)Hz CPU, $(F_CLOCK)Hz Master
	@echo --------------------------------------
	

# Display compiler version information.
gccversion : 
	@$(CC) --version


# Program the device.  
#program: $(TARGET).hex $(TARGET).eep
#	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

program:
	$(OOCD_EXE) $(OOCD_CL)



# Generate avr-gdb config/init file which does the following:
#     define the reset signal, load the target file, connect to target, and set 
#     a breakpoint at main().
gdb-config: 
	@$(REMOVE) $(GDBINIT_FILE)
	@echo define reset >> $(GDBINIT_FILE)
	@echo SIGNAL SIGHUP >> $(GDBINIT_FILE)
	@echo end >> $(GDBINIT_FILE)
	@echo file $(TARGET).elf >> $(GDBINIT_FILE)
	@echo target remote $(DEBUG_HOST):$(DEBUG_PORT)  >> $(GDBINIT_FILE)
ifeq ($(DEBUG_BACKEND),simulavr)
	@echo load  >> $(GDBINIT_FILE)
endif
	@echo break main >> $(GDBINIT_FILE)

debug: $(TARGET).elf
	arm-none-eabi-gdb.exe -x gdb_lpc17xx_debug.gdb



# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT = $(OBJCOPY) --debugging
COFFCONVERT += --change-section-address .data-0x800000
COFFCONVERT += --change-section-address .bss-0x800000
COFFCONVERT += --change-section-address .noinit-0x800000
COFFCONVERT += --change-section-address .eeprom-0x810000



coff: $(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof


extcoff: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) $< $@

%.bin: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O binary $< $(TARGET).bin

%.srec: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O srec $< $(TARGET).srec

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -z -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@



# Create library from object files.
.SECONDARY : $(TARGET).a
.PRECIOUS : $(OBJ)
%.a: $(OBJ)
	@echo
	@echo $(MSG_CREATING_LIBRARY) $@
	$(AR) $@ $(OBJ)


# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(LD) $(LINKER_SCRIPT) $(ALL_CFLAGS_LINKER) $(LDFLAGS) -o $@ $^


# Compile: create object files from C source files.
$(OBJDIR)/%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 


# Compile: create object files from C++ source files.
$(OBJDIR)/%.o : %.cpp
	@echo
	@echo $(MSG_COMPILING_CPP) $<
	$(CC) -c $(ALL_CPPFLAGS) $< -o $@ 


# Compile: create assembler files from C source files.
%.s : %.c
	$(AS) -S $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C++ source files.
%.s : %.cpp
	$(CC) -S $(ALL_CPPFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
$(OBJDIR)/%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(AS) $< $(ALL_ASFLAGS) --MD $(OBJDIR)/$(@F).d -o $@


# Create preprocessed source for use in sending a bug report.
%.i : %.c
	$(CC) -E -mmcu=$(CPU) -I. $(CFLAGS) $< -o $@ 
	

# Target: clean project.
clean: begin clean_list clean_binary end

clean_binary:
	$(REMOVE) $(TARGET).hex
	
clean_list:
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET)eep.hex
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.o)
	$(REMOVE) $(SRC:%.c=$(OBJDIR)/%.lst)
	$(REMOVE) $(ASRC:%.S=$(OBJDIR)/%.lst)
	$(REMOVE) $(ASRC:%.S=$(OBJDIR)/%.o)
	$(REMOVE) $(ASRC:%.S=$(OBJDIR)/%.o.d)
	$(REMOVE) *.o.d
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) $(SRC:.c=.i)
	$(REMOVE) InvalidEvents.tmp
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).srec


#	$(REMOVEDIR) $(OBJDIR)/
#	$(REMOVEDIR) $(OBJDIR)/
#	$(REMOVEDIR) $(OBJDIR)/

doxygen:
	@echo Generating Project Documentation...
	@doxygen Doxygen.conf
	@echo Documentation Generation Complete.

clean_doxygen:
	rm -rf Documentation

# Create object files directory
$(shell mkdir $(OBJDIR)/ 2>/dev/null)


# Include the dependency files.
#-include $(shell mkdir $(OBJDIR)/ 2>/dev/null) $(wildcard $(OBJDIR)//*)


# Listing of phony targets.
.PHONY : all checkinvalidevents showliboptions    \
showtarget begin finish end sizebefore sizeafter  \
gccversion build elf hex eep lss sym coff extcoff \
program dfu flip flip-ee dfu-ee clean debug       \
clean_list clean_binary gdb-config doxygen
