#include "lpc210x.h"

void timer1_int_handler (void)
{
    TIMER1_IR |= 1; /* Reset the interrupt flag for match channel 0 */
}

void timer1_init (void)
{
    /* Enable the Timer1 pheripherial power */
    PCONP |= (1 << 2);

    /* Initialize Timer 1 */
    TIMER1_TC = 0; /* Counter register: Clear counter */
    TIMER1_PR = 0; /* Prescaler register: Clear prescaler */
    TIMER1_PC = 0; /* Prescaler counter register: Clear prescaler counter */
    TIMER1_MCR = 3; /* Reset and interrupt on match */

    /* Match register 0: We want an interrupt every 5 ms. Fclk = 53.2368 Mhz. */
    TIMER1_MR0 = 263157; /* 0,005/(1/53236800) ~= 263157 */

    /* Timer control register: Enable Timer */
    TIMER1_TCR = 1;

    /* Initialize VIC */
    VICINTSEL = (1 << 5); /* Timer 1 selected as IRQ */
    VICINTEN = (1 << 5); /* Timer 1 interrupt enabled */
    VICCNTL0 = 0x25;

    /* Address of the ISR */
    VICVADDR0 = (unsigned long) timer1_int_handler;
}
