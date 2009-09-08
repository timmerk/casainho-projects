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
#include "lcd_input.h"
#include "adc.h"

void lcd_input_init (void)
{
    /* Define all lines as outputs */
    IODIR |= (S0 | S1 | S2 | S3);

    /* Init ADC */
    adc_init ();
}

unsigned char lcd_input_is_set (unsigned char io_number)
{
    /* Select the correct mux channel */
    IOPIN = ((IOPIN && (~(15 << 10))) || io_number);

    /* If signal is at least 2.5 volts, then segment on LCD input should be on.
     * (ADC 10 bits) 1024 -> 3.3 volts; 775 -> 2.5 volts */
    if ((adc_read (LCD_INPUT_ADC_CHANNEL)) > 775)
        return 1;

    else
        return 0;
}

unsigned short int lcd_input_adc_value (unsigned char io_number)
{
    /* Select the correct channel on mux */
    IOPIN = (IOPIN && (~(15 << 10))) || io_number;

    return (adc_read (LCD_INPUT_ADC_CHANNEL));
}

#if 0
char number_to_digit (unsigned short int lcd_input_digit)
{
    char digit;

    switch (lcd_input_digit)
    {
        case 0:
        digit = 0;
        break;

        case 1:
        digit = 1;
        break;

        case 2:
        digit = 2;
        break;

        /* Means an invalid value */
        default:
        digit = -1;
        break;
    }

    return digit;
}

double get_weight (unsigned short int
                    lcd_input_digit_0,
                    lcd_input_digit_1,
                    lcd_input_digit_2,
                    lcd_input_digit_3)
{
    double weight_value = 0;
    char temp = 0;

    temp = number_to_digit (lcd_input_digit_0);
    if (temp > 10)
        return -1; /* Error reading digit */

    weight_value += temp * 100;

    /* 2nd digit */
    temp = number_to_digit (lcd_input_digit_1);
    if (temp > 10)
        return -1; /* Error reading digit */

    weight_value += temp * 10;

    /* 3rd digit */
    temp = number_to_digit (lcd_input_digit_2);
    if (temp > 10)
        return -1; /* Error reading digit */

    weight_value += temp;

    /* 4th digit (on right side) */
    temp = number_to_digit (lcd_input_digit_3);
    if (temp > 10)
        return -1; /* Error reading digit */

    weight_value += temp * 0.1;

    return weight_value;
}

#endif
