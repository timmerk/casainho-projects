#include "lpc210x.h"
#include "adc.h"

extern volatile double voltage, current, wattage, wattage_hour;
extern long int tick_update_lcd;

void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer1_int_handler (void)
{
    short int   voltage_temp,
                current_temp,
                wattage_temp;

    /* Here we increment the various ticks */
    tick_update_lcd++; /* increment LCD tick */


    /* We read voltage and current at each 5ms, we do it here */
    /* Read voltage and accumulate it to the last values. It should take no
     * more than 35us(??) for read a value. */
    voltage_temp = adc_read(1);
    voltage += voltage_temp;

    /* Read current and accumulate it to the last values */
    current_temp = adc_read(0);
    current += current_temp;

    /* Calculate the wattage and accumulate, using the current and
     *  voltage values */
    wattage_temp = voltage_temp * current_temp;
    wattage += wattage_temp;

    /* Calculate, integrate, the wattage per hour.
     *
     * There are 17950903,5114864 Timer0 interrupt in one hour, so we should
     * accumulate the wattage relative to each piece of time -- integrate.
     */
    wattage_hour += (wattage_temp / 17950903.5114864);


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

    /* Match register 0: We want an interrupt every 5 ms. Fclk = 53.2368 Mhz. */
    TIMER1_MR0 = 263157; /* 0,005/(1/53236800) ~= 263157 */
    TIMER1_MCR = 3; /* Reset and interrupt on match */

    /* Initialize VIC */
    VICINTSEL = 0; /* Timer 1 selected as IRQ */
    VICINTEN = 0x20; /* Timer 1 interrupt enabled */
    VICVECTCNTL0 = 0x25;
    VICVECTADDR0 = (unsigned long) timer1_int_handler; /* Address of the ISR */

    /* Start timer */
    TIMER1_TCR = 1;
}
