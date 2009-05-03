#include "lpc210x.h"

void timer1_int_handler (void)
{

}

void timer1_init (void)
{
    /* Initialize Timer 1 */
    TIMER1_TCR = 0;
    TIMER1_TC = 0;
    TIMER1_PR = 0;
    TIMER1_PC = 0;

    /* We want an interrupt every 5 ms. Fclk = 53.2368 Mhz. */
    TIMER1_MR0 = 0x0; /* ?? */

    /* Reset and interrupt on match */
    TIMER1_MCR = 3;

    /* Initialize VIC */
    VICINTSEL = 0;        /* Timer 1 selected as IRQ */
    VICINTEN = 0;       /* Timer 1 interrupt enabled */
    VICCNTL0 = 0x25;

    /* Address of the ISR */
    VICVADDR0 = (unsigned long) timer1_int_handler;
}
