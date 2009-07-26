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
extern unsigned char timer1_run;

void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));
void timer0_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer0_init (void)
{
    /* Initialize VIC */
    VICINTSEL &= ~(1 << 4); /* Timer 0 selected as IRQ */
    VICINTEN |= (1 << 4); /* Timer 0 interrupt enabled */
    VICVECTCNTL0 = 0x25;
    VICVECTADDR0 = (unsigned long) timer0_int_handler; /* Address of the ISR */
}

void timer0_register (long int value_us)
{
    /* Timer/Counter 0 power/clock enable */
    PCONP |= (1 << 1);

    /* Initialize Timer 0 */
    TIMER0_TCR = 0;
    TIMER0_TC = 0; /* Counter register: Clear counter */
    TIMER0_PR = 1000; /* Prescaler register value: 1000 */
    TIMER0_PC = 0; /* Prescaler counter register: Clear prescaler counter */

    /* Match register 0:
     * Fclk = 58982400Hz; 10ms => 0,001/((1*1000)/58982400); 10ms => ~ 590 */
    TIMER0_MR0 = 590;
    TIMER0_MCR = 3; /* Reset and interrupt on match */

    /* Start timer */
    TIMER0_TCR = 1;
}

void timer1_init (void)
{
    /* Initialize VIC */
    VICINTSEL &= ~(1 << 5); /* Timer 1 selected as IRQ */
    VICINTEN |= (1 << 5); /* Timer 1 interrupt enabled */
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

void timer0_int_handler (void)
{
    /* Clear the interrupt flag */
    //TIMER0_IR = 1;
    //VICVECTADDR = 0xff;

    /* Call MMC/SD Card drivers "Device Timer Interrupt Procedure" */
    //disk_timerproc ();
}
