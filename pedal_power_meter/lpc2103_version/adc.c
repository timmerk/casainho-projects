#include "lpc210x.h"

/* ADC pins connections:
 * -ADC ------------------------|-connected to-----
 *  1  - AIN0                   | Voltage relative to input voltage
 *  2  - AIN1                   | Voltage relative to input current
 */

void adc_init (void)
{
    /* Enable the ADC pheripherial clock */
    PCON |= (1 << 12);

    /* Select P0.22 and P0.23 to be used for ADC */
    PINSEL1 |= ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));

    /* Enable ADC; configure the clock; 10 bits resolution */
    ADCR = ((20 << 8) | (1 << 21)); /* CLKDIV = 20 => 2,66184MHz
                                     the clock for ADC */
}

unsigned short int adc_read (unsigned char channel)
{
    /* Start ADC conversion */
    ADCR |= ((1 << channel) | (1 << 24));

    /* Wait for finish the conversion */
    while (!(ADSTAT & (1 << channel))) ;

    /* Return the value (10 bits) */
    return ((ADGDR >> 6) & 0x3ff);
}
