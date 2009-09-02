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

/* ADC pins connections:
 * -ADC ------------------------|-connected to-----
 *  1  - AIN6                   | Voltage relative to input voltage
 *  2  - AIN2                   | Voltage relative to input current
 */

void adc_init (void)
{
    /* Enable the ADC pheripherial power */
    PCONP |= (1 << 12);

    /* Select P0.24 and P0.25 to be used for ADC */
    PINSEL1 |= ((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19));
}

unsigned short int adc_read (unsigned char channel)
{
    /* Enable ADC; configure the clock; 10 bits resolution; configure channel */
    /* CLKDIV = 12 => 4.915200MHz the clock for ADC */
    /* Each conversion should take about 2,5us */
    ADCR = ((12 << 8) | (1 << 21) | (1 << 24) | (1 << channel));

    /* Wait for finish the conversion */
    while (!(ADGDR & (1 << 31))) ;

    /* Return the value (10 bits) */
    return ((ADGDR >> 6) & 0x3ff);
}
