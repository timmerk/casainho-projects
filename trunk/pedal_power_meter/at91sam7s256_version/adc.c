#include "at91sam7s256.h"

void adc_init (void)
{
    /* Enable peripheral clock */
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_ADC;

    /* Reset the ADC controller */
    AT91C_BASE_ADC->ADC_CR = AT91C_ADC_SWRST;

    /* Disable all ADC interrupt sources */
    AT91C_BASE_ADC->ADC_IDR = 0xffffffff;

    /* Clear the register */
    AT91C_BASE_ADC->ADC_MR = 0;
    /* Write to the MR register */
    AT91C_BASE_ADC->ADC_MR =
        (AT91C_ADC_SLEEP /* Sleep mode */
        | ((23 << 8) & AT91C_ADC_PRESCAL) /* ADC clock ~= 1MHz */
        | ((4 << 16) & AT91C_ADC_STARTUP) /* Startup time ~= 1us */
        | ((4 << 24) & AT91C_ADC_SHTIM)); /* Sample and hold time ~= 1us */
    /* ADC should take no more than 35us to read a value:
     *      20us for return from idela mode;
     *      10 * 1us for conversion;
     *      1us for startup time;
     *      1us for sample and hold time.
     */
}

unsigned short int adc_read (unsigned char channel)
{
    unsigned short int data;

    /* Disable all channels */
    AT91C_BASE_ADC->ADC_CHDR = 0xffffffff;

    /* Enable the channel */
    AT91C_BASE_ADC->ADC_CHER = (unsigned long int) (1 << channel);

    /* Start ADC conversion */
    AT91C_BASE_ADC->ADC_CR = AT91C_ADC_START;

    /* Wait for finish the conversion */
    while (!(AT91C_BASE_ADC->ADC_SR & (1 << channel))) ;

    /* Get the data */
    switch(channel)
    {
        case 0: data = AT91C_BASE_ADC->ADC_CDR0; break;
        case 1: data = AT91C_BASE_ADC->ADC_CDR1; break;
        case 2: data = AT91C_BASE_ADC->ADC_CDR2; break;
        case 3: data = AT91C_BASE_ADC->ADC_CDR3; break;
        case 4: data = AT91C_BASE_ADC->ADC_CDR4; break;
        case 5: data = AT91C_BASE_ADC->ADC_CDR5; break;
        case 6: data = AT91C_BASE_ADC->ADC_CDR6; break;
        case 7: data = AT91C_BASE_ADC->ADC_CDR7; break;
    }

    return data;
}
