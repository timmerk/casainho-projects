/* ****************************************************************************************************** */
/*   linker_script.cmd			LINKER  SCRIPT                                                */
/*                                                                                                        */
/*                                                                                                        */
/*   The Linker Script defines how the code and data emitted by the GNU C compiler and assembler are  	  */
/*   to be loaded into memory (code goes into FLASH, variables go into RAM).              			  	  */
/*                                                                                                        */
/*   Any symbols defined in the Linker Script are automatically global and available to the rest of the   */
/*   program.                                                                                             */
/*                                                                                                        */
/*   To force the linker to use this LINKER SCRIPT, just add the -T linker_script.cmd         */
/*   directive to the linker flags in the makefile. For example,                                          */
/*                                                                                                        */
/*   			LFLAGS  =  -Map main.map -nostartfiles -T linker_script.cmd                   */
/*                                                                                                        */
/*                                                                                                        */
/*   The order that the object files are listed in the makefile determines what .text section is          */
/*   placed first.                                                                                        */
/*                                                                                                        */
/*   For example:  $(LD) $(LFLAGS) -o main.out  crt.o main.o lowlevelinit.o                               */
/*                                                                                                        */
/*   			   crt.o is first in the list of objects, so it will be placed at address 0x00000000      */
/*                                                                                                        */
/*                                                                                                        */
/*   The top of the stack (_stack_end) is (last_byte_of_ram +1) - 4  				                      */
/*                                                                                                        */
/*   Therefore:   _stack_end = (0x00020FFFF + 1) - 4  =  0x00021000 - 4  =  0x0020FFFC                    */
/*                                                                                                        */
/*   Note that this symbol (_stack_end) is automatically GLOBAL and will be used by the crt.s             */
/*   startup assembler routine to specify all stacks for the various ARM modes                            */
/*  Author:  James P. Lynch    May 12, 2007                                                               */
/* Modified on March 2009 by Jorge "Casainho" Pinto */
/*                                                                                                        */
/* ****************************************************************************************************** */

/* identify the Entry Point  (_vec_reset is defined in file crt.s)  */
ENTRY(_vec_reset)

/* specify the AT91SAM7S256 memory areas  */
MEMORY 
{
	flash	: ORIGIN = 0,          LENGTH = 256K	/* FLASH EPROM		*/	
	ram		: ORIGIN = 0x00200000, LENGTH = 64K  	/* static RAM area	*/
}


/* define a global symbol _stack_end  (see analysis in annotation above) */
_stack_end = 0x20FFFC;

/* now define the output sections  */
SECTIONS 
{
	. = 0;								/* set location counter to address zero  */
	
	.text :								/* collect all sections that should go into FLASH after startup  */ 
	{
		*(.text)						/* all .text sections (code)  */
		*(.rodata)						/* all .rodata sections (constants, strings, etc.)  */
		*(.rodata*)						/* all .rodata* sections (constants, strings, etc.)  */
		*(.glue_7)						/* all .glue_7 sections  (no idea what these are) */
		*(.glue_7t)						/* all .glue_7t sections (no idea what these are) */
		_etext = .;						/* define a global symbol _etext just after the last code byte */
    } >ram                              /* put all the above into RAM */

	.data :								/* collect all initialized .data sections that go into RAM  */ 
	{
		_data = .;						/* create a global symbol marking the start of the .data section  */
		*(.data)						/* all .data sections  */
		_edata = .;						/* define a global symbol marking the end of the .data section  */
    } >ram                              /* put all the above into RAM */

	.bss :								/* collect all uninitialized .bss sections that go into RAM  */
	{
		_bss_start = .;					/* define a global symbol marking the start of the .bss section */
		*(.bss)							/* all .bss sections  */
	} >ram								/* put all the above in RAM (it will be cleared in the startup code */

	. = ALIGN(4);						/* advance location counter to the next 32-bit boundary */
	_bss_end = . ;						/* define a global symbol marking the end of the .bss section */
}
	_end = .;							/* define a global symbol marking the end of application RAM */
