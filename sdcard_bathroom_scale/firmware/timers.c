/*
 * Pedal Power Meter
 *
 * Copyright (C) Jorge Pinto aka Casainho, 2009.
 *
 *   casainho [at] gmail [dot] com
 *     www.casainho.net
 *
 * Released under the GPL Licence, Version 3
 */

#include "lpc210x.h"
#include "main.h"

void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer1_int_handler (void)
{

    /* Clear the interrupt flag */
    TIMER1_IR = 1;
    VICVECTADDR = 0xff;
}

void timer1_init (void)
{
    /* Timer/Counter 1 power/clock enable */
    PCONP |= (1 << 2);

    /* Initialize Timer 1 */
    TIMER1_TCR = 0;
    TIMER1_TC = 0; /* Counter register: Clear counter */
    TIMER1_PR = 0; /* Prescaler register: Clear prescaler */
    TIMER1_PC = 0; /* Prescaler counter register: Clear prescaler counter */

    /* Match register 0: We want an interrupt every 5 ms. Fclk = 58982400Hz. */
    TIMER1_MR0 = 294912; /* 0,005/(1/58982400) ~= 294912 (verified the 5ms using
    the oscilloscope on 29.05.2009)*/
    TIMER1_MCR = 3; /* Reset and interrupt on match */

    /* Initialize VIC */
    VICINTSEL = 0; /* Timer 1 selected as IRQ */
    VICINTEN = 0x20; /* Timer 1 interrupt enabled */
    VICVECTCNTL0 = 0x25;
    VICVECTADDR0 = (unsigned long) timer1_int_handler; /* Address of the ISR */

    /* Start timer */
    TIMER1_TCR = 1;
}
