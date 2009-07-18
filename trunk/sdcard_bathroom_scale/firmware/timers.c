/*
 * SDCard Bathroom Scale
 *
 * Copyright (C) Jorge Pinto aka Casainho, 2009.
 *
 *   casainho [at] gmail [dot] com
 *     www.casainho.net
 *
 * Released under the GPL Licence, Version 3
 */

#include "lpc210x.h"

extern unsigned char timer1_run;

void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer1_init (void)
{
    /* Initialize VIC */
    VICINTSEL = 0; /* Timer 1 selected as IRQ */
    VICINTEN = 0x20; /* Timer 1 interrupt enabled */
    VICVECTCNTL0 = 0x25;
    VICVECTADDR0 = (unsigned long) timer1_int_handler; /* Address of the ISR */
}

void timer1_register (long int value_us)
{
    /* Timer/Counter 1 power/clock enable */
    PCONP |= (1 << 2);

    /* Initialize Timer 1 */
    TIMER1_TCR = 0;
    TIMER1_TC = 0; /* Counter register: Clear counter */
    TIMER1_PR = 0; /* Prescaler register: Clear prescaler */
    TIMER1_PC = 0; /* Prescaler counter register: Clear prescaler counter */

    /* Match register 0:
     * Fclk = 58982400Hz; 1us => 0,000001/(1/58982400); 1us => ~ 59 */
    TIMER1_MR0 = value_us * 59;
    TIMER1_MCR = 3; /* Reset and interrupt on match */

    /* Start timer */
    TIMER1_TCR = 1;

    timer1_run = 1;
}

void timer1_stop (void)
{
    /* Stop timer */
    TIMER1_TCR = 0;

    /* Timer/Counter 1 power/clock disable */
    PCONP &= ~(1 << 2);
}

void timer1_int_handler (void)
{
    /* Clear the interrupt flag */
    TIMER1_IR = 1;
    VICVECTADDR = 0xff;

    timer1_run = 0;
    timer1_stop ();
}
