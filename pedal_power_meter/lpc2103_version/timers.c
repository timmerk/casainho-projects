#include "lpc210x.h"

//void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer1_int_handler (void)
{
    TIMER1_IR = 1;
    VICVECTADDR = 0xff;
}

void timer1_init (void)
{
    /* Initialize VIC */
    VICCNTL0 = 0x25;
    VICVECTADDR0 = (unsigned long) timer1_int_handler; /* Address of the ISR */
    VICINTSEL = 0; /* Timer 1 selected as IRQ */
    VICINTEN = (1 << 5); /* Timer 1 interrupt enabled */

    /* Initialize Timer 1 */
    TIMER1_TC = 0; /* Counter register: Clear counter */
    TIMER1_PR = 0; /* Prescaler register: Clear prescaler */
    TIMER1_PC = 0; /* Prescaler counter register: Clear prescaler counter */

    /* Match register 0: We want an interrupt every 5 ms. Fclk = 53.2368 Mhz. */
    TIMER1_MR0 = 263157; /* 0,005/(1/53236800) ~= 263157 */

    TIMER1_MCR |= 3; /* Reset and interrupt on match */

    /* Start timer */
    TIMER1_TCR = 1;
}
