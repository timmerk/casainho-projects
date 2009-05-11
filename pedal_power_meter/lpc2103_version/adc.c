#include "lpc210x.h"

/* ADC pins connections:
 * -ADC ------------------------|-connected to-----
 *  1  - AIN0                   | Voltage relative to input current
 *  2  - AIN1                   | Voltage relative to input voltage
 */

void adc_init (void)
{
    /* Enable the ADC pheripherial power */
    PCONP |= (1 << 12);

    /* Select P0.22 and P0.23 to be used for ADC */
    PINSEL1 |= ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
}

unsigned short int adc_read (unsigned char channel)
{
    unsigned short int value;

    /* Enable ADC; configure the clock; 10 bits resolution; configure channel */
    /* CLKDIV = 20 => 2,66184MHz the clock for ADC */
    ADCR = ((20 << 8) | (1 << 21) | (1 << 24) | (1 << channel));

    /* Wait for finish the conversion */
    while (!(ADSTAT & (1 << channel))) ;

    switch (channel)
    {
        case 1:
        /* Value readed (10 bits) */
        value = ((ADDR0 >> 6) & 0x3ff);
        break;

        case 2:
        /* Value readed (10 bits) */
        value = ((ADDR1 >> 6) & 0x3ff);
        break;

        default:
        break;
    }

    /* Disable and power down the ADC */
    ADCR = 0;

    return (value);
}
