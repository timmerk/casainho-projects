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
#if 0
    IOPIN = ((IOPIN && (~(15 << 10))) || io_number);
#endif

    if (io_number & 1)
        IOSET = S0;
    else
        IOCLR = S0;

    if (io_number & 2)
        IOSET = S1;
    else
        IOCLR = S1;

    if (io_number & 4)
        IOSET = S2;
    else
        IOCLR = S2;

    if (io_number & 8)
        IOSET = S3;
    else
        IOCLR = S3;

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
    IOPIN = (IOPIN && (~(15 << 10))) || io_number;

    return (adc_read (LCD_INPUT_ADC_CHANNEL));
}


char number_to_digit (char lcd_input_digit)
{
    char digit;

    switch (lcd_input_digit)
    {
        case 215:
        digit = 0;
        break;

        case 6:
        digit = 1;
        break;

        case 235:
        digit = 2;
        break;

        case 167:
        digit = 3;
        break;

        case 54:
        digit = 4;
        break;

        case 181:
        digit = 5;
        break;

        case 245:
        digit = 6;
        break;

        case 7:
        digit = 7;
        break;

        case 247:
        digit = 8;
        break;

        case 183:
        digit = 9;
        break;

        /* Means an invalid value */
        default:
        digit = 0;
        break;
    }

    return digit;
}

double get_weight (void)
{
    char    lcd_input_digit_0,
            lcd_input_digit_1,
            lcd_input_digit_2,
            lcd_input_digit_3;

    double  weight_value, temp;

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
    temp = number_to_digit (lcd_input_digit_3);
    weight_value += temp * 100;

    /* 2nd digit */
    temp = number_to_digit (lcd_input_digit_2);
    weight_value += temp * 10;

    /* 3rd digit */
    temp = number_to_digit (lcd_input_digit_1);
    weight_value += temp;

    /* 4th digit (on right side) */
    temp = number_to_digit (lcd_input_digit_0);
    weight_value += temp * 0.1;

    return weight_value;
}
