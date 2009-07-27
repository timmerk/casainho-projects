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

extern void disk_timerproc (void);
extern unsigned short int timer1_counter;

void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer1_init (void)
{
    /* Initialize VIC */
    VICINTSEL &= ~(1 << 5); /* Timer 1 selected as IRQ */
    VICINTEN |= (1 << 5); /* Timer 1 interrupt enabled */
    VICVECTCNTL1 = 0x25;
    VICVECTADDR1 = (unsigned long) timer1_int_handler; /* Address of the ISR */

    /* Timer/Counter 1 power/clock enable */
    PCONP |= (1 << 2);

    /* Initialize Timer 1 */
    TIMER1_TCR = 0;
    TIMER1_TC = 0; /* Counter register: Clear counter */
    TIMER1_PR = 0; /* Prescaler register: Clear prescaler */
    TIMER1_PC = 0; /* Prescaler counter register: Clear prescaler counter */

    /* Match register 0:
     * Fclk = 58982400Hz; 100us => 0,0001/(1/58982400); 100us => ~ 5900 */
    TIMER1_MR0 = 5900;
    TIMER1_MCR = 3; /* Reset and interrupt on match */

    /* Start timer */
    TIMER1_TCR = 1;
}

/* This interrupt handler happens every 100us */
void timer1_int_handler (void)
{
    static char counter = 0;

    /* Clear the interrupt flag */
    TIMER1_IR = 1;
    VICVECTADDR = 0xff;

    if (timer1_counter > 0)
        timer1_counter--;

    if (++counter > 100)
    {
        counter = 0;
        disk_timerproc (); /* Call every 10ms */

    }
}
