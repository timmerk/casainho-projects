#include "lpc210x.h"
#include "adc.h"
#include "main.h"

extern volatile double              wattage, wattage_hour;

extern volatile long int            wattage_hour_number_increments,
                            voltage,
                            current,
                            tick_update_lcd, nr_adc_reads;

void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer1_int_handler (void)
{
    volatile short int  voltage_temp,
                        current_temp;

    volatile double     wattage_temp;

    /* Here we increment the various ticks */
    tick_update_lcd++; /* increment LCD tick */


    /* We read voltage and current at each 5ms, we do it here */
    /* Read voltage and accumulate it to the last values. It should take no
     * more than 2,5us for read a value. */
    voltage_temp = adc_read(2);
    voltage += voltage_temp;

    /* Read current and accumulate it to the last values */
    current_temp = adc_read(6);
    current += current_temp;

    /* Calculate the wattage and accumulate, using the current and
     *  voltage values */
    wattage_temp = (double) (((double) (voltage_temp * K_VOLTAGE)) * \
                   ((double) (current_temp * K_CURRENT)));
    wattage += wattage_temp;

    /* Integrate the wattage to have the wattage/hour value */
    wattage_hour += wattage * WATTAGE_HOUR_DT;

    /* Keep the track of the number of wattage/hour increments */
    wattage_hour_number_increments++;

    /* Keep the track of the number of ADC reads until we use them */
    nr_adc_reads++;


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
