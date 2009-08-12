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
#include "adc.h"
#include "main.h"

extern double       wattage,
                    wattage_hour_user,
                    wattage_hour_system,
                    user_time_wattage;

extern long int     voltage,
                    current,
                    tick_update_lcd,
                    nr_adc_reads;

void timer1_int_handler (void)   __attribute__ ((interrupt("IRQ")));

void timer1_int_handler (void)
{
    short int   voltage_temp,
                current_temp;

    double      wattage_temp,
                current_temp1,
                voltage_temp1;

    /* Here we increment the various ticks */
    tick_update_lcd++; /* increment LCD tick */


    /* We read voltage and current at each 5ms, we do it here */
    /* Read voltage and accumulate it to the last values. It should take no
     * more than 2,5us for read a value. */
    voltage_temp = adc_read (6);
    voltage += voltage_temp;

    /* Read current and accumulate it to the last values */
    current_temp = adc_read (7);
    current += current_temp;

    /* Keep the track of the number of ADC reads until we use them */
    nr_adc_reads++;

    /* Calculate the wattage and accumulate, using the current and
     *  voltage values.
     */
    /* First 3 values from ADC_current should not be used since they are
     * very non linear.
     */
    if (current_temp < 3)
    {
        current_temp1 = 0;
    }

    if (current_temp >= 3 && current_temp < 60)
    {
        current_temp1 = current_temp;
        current_temp1 = (double) \
       ((double) (-0.000004 * current_temp1 * current_temp1 * current_temp1) + \
        ((double) (0.0005 * current_temp1 * current_temp1)) - \
        ((double) (0.0028 * current_temp1) + 0.356));
    }

    if (current_temp >= 60)
    {
        current_temp1 = current_temp;
        current_temp1 = (double) ((double) (current_temp1 * K_CURRENT) \
                + M_CURRENT);
    }

    voltage_temp1 = (double) ((double) (voltage_temp * K_VOLTAGE) + M_VOLTAGE);
    wattage_temp = (double) (voltage_temp1 * current_temp1);

    wattage += wattage_temp;
    /* Only integrate if there is some wattage value */
    if (wattage_temp > 0)
    {
        /* Integrate the wattage "user" to have the wattage/hour "user" value */
        wattage_temp = wattage_temp * WATTAGE_HOUR_DT;
        wattage_hour_user += wattage_temp;

        user_time_wattage += wattage_temp;

        /* Integrate the wattage "user" to have the wattage/hour "user" value */
        wattage_hour_system += wattage_temp * WATTAGE_HOUR_DT;
    }

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
