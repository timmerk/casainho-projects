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
#include "timers.h"
#include "lcd.h"

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
    IOPIN = ((IOPIN & (0xFFFFC3FF)) | (io_number << 10));

    /* The next delay must happen! It's used for analog multiplexer put
                                                  signal correctly on output. */
    {
        char a;
        for (a = 0; a < 200; a++) ;
    }

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
    IOPIN = ((IOPIN & (0xFFFFC3FF)) | (io_number << 10));

    return (adc_read (LCD_INPUT_ADC_CHANNEL));
}


char number_to_digit (unsigned char *number, unsigned char *digit)
{
    switch (*number)
    {
        /* 166 = 0; 10100110 ??- 11010111
         *   1 = 4; 00000100 ??- 00000110
         * 102 = 9; 01100110 ??- 10110111
         *  98 = 4; 01100010 ??- 00110110
         */
        /* This case is when there is none segment ON */
        case 0:
        *digit = 0;
        break;

        /* This case is when 0 is lighted on original LCD  */
        case 215:
        *digit = 0;
        break;

        /* This case is when 1 is lighted on original LCD  */
        case 6:
        *digit = 1;
        break;

        /* This case is when 2 is lighted on original LCD  */
        case 235:
        *digit = 2;
        break;

        case 167:
        *digit = 3;
        break;

        case 54:
        *digit = 4;
        break;

        case 181:
        *digit = 5;
        break;

        case 245:
        *digit = 6;
        break;

        case 7:
        *digit = 7;
        break;

        case 247:
        *digit = 8;
        break;

        case 183:
        *digit = 9;
        break;

        /* Means an invalid value */
        default:
        return 1;
    }

    return 0;
}

char get_weight (float *weight)
{
    float weight_bck = *weight;
    unsigned char   lcd_input_digit_0,
                    lcd_input_digit_1,
                    lcd_input_digit_2,
                    lcd_input_digit_3,
                    digit;

    /* Make a delay to go for the middle of next data bit */
    timer1_counter = 5; /* wait 0,5 ms */
    while (timer1_counter) ;

    lcd_input_digit_0 = ((lcd_input_is_set (1)) << 0);
    lcd_input_digit_0 |= ((lcd_input_is_set (2)) << 4);
    lcd_input_digit_1 = ((lcd_input_is_set (3)) << 0);
    lcd_input_digit_1 |= ((lcd_input_is_set (4)) << 4);
    lcd_input_digit_2 = ((lcd_input_is_set (5)) << 0);
    lcd_input_digit_2 |= ((lcd_input_is_set (6)) << 4);
    lcd_input_digit_3 = ((lcd_input_is_set (7)) << 0);
    lcd_input_digit_3 |= ((lcd_input_is_set (8)) << 4);

    /* Make a delay to go for the middle of next data bit */
    timer1_counter = 12; /* wait 1,2 ms */
    while (timer1_counter) ;

    lcd_input_digit_0 |= ((lcd_input_is_set (1)) << 1);
    lcd_input_digit_0 |= ((lcd_input_is_set (2)) << 5);
    lcd_input_digit_1 |= ((lcd_input_is_set (3)) << 1);
    lcd_input_digit_1 |= ((lcd_input_is_set (4)) << 5);
    lcd_input_digit_2 |= ((lcd_input_is_set (5)) << 1);
    lcd_input_digit_2 |= ((lcd_input_is_set (6)) << 5);
    lcd_input_digit_3 |= ((lcd_input_is_set (7)) << 1);
    lcd_input_digit_3 |= ((lcd_input_is_set (8)) << 5);

    /* Make a delay to go for the middle of next data bit */
    timer1_counter = 10; /* wait 1 ms */
    while (timer1_counter) ;

    lcd_input_digit_0 |= ((lcd_input_is_set (1)) << 2);
    lcd_input_digit_0 |= ((lcd_input_is_set (2)) << 6);
    lcd_input_digit_1 |= ((lcd_input_is_set (3)) << 2);
    lcd_input_digit_1 |= ((lcd_input_is_set (4)) << 6);
    lcd_input_digit_2 |= ((lcd_input_is_set (5)) << 2);
    lcd_input_digit_2 |= ((lcd_input_is_set (6)) << 6);
    lcd_input_digit_3 |= ((lcd_input_is_set (7)) << 2);
    lcd_input_digit_3 |= ((lcd_input_is_set (8)) << 6);

    /* Make a delay to go for the middle of next data bit */
    timer1_counter = 9; /* wait 0,9 ms */
    while (timer1_counter) ;

    lcd_input_digit_0 |= ((lcd_input_is_set (2)) << 7);
    lcd_input_digit_1 |= ((lcd_input_is_set (4)) << 7);
    lcd_input_digit_2 |= ((lcd_input_is_set (6)) << 7);
    lcd_input_digit_3 |= ((lcd_input_is_set (8)) << 7);

    /* Calculate the weight value */
    /* 4th digit */
    if (number_to_digit (&lcd_input_digit_3, &digit))
    {
        *weight = weight_bck;
        return 1;
    }

    *weight = digit * 100;

    /* 3rd digit */
    if (number_to_digit (&lcd_input_digit_2, &digit))
    {
        *weight = weight_bck;
        return 1;
    }

    *weight += digit * 10;

    /* 2nd digit */
    if (number_to_digit (&lcd_input_digit_1, &digit))
    {
        *weight = weight_bck;
        return 1;
    }

    *weight += digit;

    /* 1st digit (on right side) */
    if (number_to_digit (&lcd_input_digit_0, &digit))
    {
        *weight = weight_bck;
        return 1;
    }

    *weight += digit * 0.1;

    return 0;
}
