#include "lpc210x.h"

void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));

void IRQ_Routine (void)
{
    while (1) ;
}

void FIQ_Routine (void)
{
    while (1) ;
}

void SWI_Routine (void)
{
    while (1) ;
}

void UNDEF_Routine (void)
{
    while (1) ;
}

void feed(void)
{
  PLLFEED=0xAA;
  PLLFEED=0x55;
}

#define PLOCK 0x400
void system_init (void)
{
    //              Setting the Phased Lock Loop (PLL)
    //               ----------------------------------
    //
    // Olimex LPC-H2103 has a 14.7456 mhz crystal
    //
    // We'd like the LPC2106 to run at 53.2368 Mhz (has to be an even multiple of crystal)
    //
    // According to the Philips LPC2106 manual:   M = cclk / Fosc   where:  M    = PLL multiplier (bits 0-4 of PLLCFG)
    //                                                                      cclk = 53236800 hz
    //                                                                      Fosc = 14745600 hz
    //
    // Solving: M = 53236800 / 14745600 = 3.6103515625
    //          M = 4 (round up)
    //
    //          Note: M - 1 must be entered into bits 0-4 of PLLCFG (assign 3 to these bits)
    //
    //
    // The Current Controlled Oscilator (CCO) must operate in the range 156 mhz to 320 mhz
    //
    // According to the Philips LPC2106 manual: Fcco = cclk * 2 * P    where:   Fcco = CCO frequency
    //                                                                          cclk = 53236800 hz
    //                                                                          P = PLL divisor (bits 5-6 of PLLCFG)
    //
    // Solving: Fcco = 53236800 * 2 * P
    //          P = 2  (trial value)
    //          Fcco = 53236800 * 2 * 2
    //          Fcc0 = 212947200 hz    (good choice for P since it's within the 156 mhz to 320 mhz range
    //
    // From Table 19 (page 48) of Philips LPC2106 manual    P = 2, PLLCFG bits 5-6 = 1  (assign 1 to these bits)
    //
    // Finally:      PLLCFG = 0  01  00011  =  0x23
    //
    // Final note: to load PLLCFG register, we must use the 0xAA followed 0x55 write sequence to the PLLFEED register
    //             this is done in the short function feed() below
    //

    // Setting Multiplier and Divider values
    PLLCFG=0x23;
    feed();

    // Enabling the PLL */
    PLLCON=0x1;
    feed();

    // Wait for the PLL to lock to set frequency
    while(!(PLLSTAT & PLOCK)) ;

    // Connect the PLL as the clock source
    PLLCON=0x3;
    feed();

    // Enabling MAM and setting number of clocks used for Flash memory fetch (4 cclks in this case)
    MAMCR=0x2;
    MAMTIM=0x4;

    // Setting peripheral Clock (pclk) to System Clock (cclk)
    VPBDIV=0x1;
}
