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
#include "ios.h"

void ios_init (void)
{
    /* IOs are automatically configured as GPIO ports */

    /* IOs are automatically configured as inputs after
     *  reset of system */
}

unsigned char io_is_set (unsigned char io_number)
{
    if ((IOPIN >> io_number) & 1)
        return 1;

    else
        return 0;
}

//weight_value += (number_to_digit (temp));
unsigned long int get_ios (void)
{
    return IOPIN;
}

unsigned char number_to_digit (unsigned short int number)
{
    char weight_value;

    switch (number)
    {
        case 16:
        weight_value = 0;
        break;

        case 179:
        weight_value = 1;
        break;

        case 40:
        weight_value = 2;
        break;

        case 34:
        weight_value = 3;
        break;

        case 131:
        weight_value = 4;
        break;

        case 66:
        weight_value = 5;
        break;

        case 64:
        weight_value = 6;
        break;

        case 51:
        weight_value = 7;
        break;

        case 0:
        weight_value = 8;
        break;

        case 2:
        weight_value = 9;
        break;

        default:
        weight_value = 0;
        break;
    }

    return weight_value;
}

unsigned long int format_back_plane (unsigned long int back_plane)
{
    unsigned long int temp = 0;

    if (back_plane & (1 << LCD_PIN_01))
        temp |= 2048;
    else
        temp &= ~2048;

    if (back_plane & (1 << LCD_PIN_02))
        temp |= 1024;
    else
        temp &= ~1024;

    if (back_plane & (1 << LCD_PIN_03))
        temp |= 512;
    else
        temp &= ~512;

    if (back_plane & (1 << LCD_PIN_04))
        temp |= 256;
    else
        temp &= ~256;

    if (back_plane & (1 << LCD_PIN_05))
        temp |= 128;
    else
        temp &= ~128;

    if (back_plane & (1 << LCD_PIN_06))
        temp |= 64;
    else
        temp &= ~64;

    if (back_plane & (1 << LCD_PIN_07))
        temp |= 32;
    else
        temp &= ~32;

    if (back_plane & (1 << LCD_PIN_08))
        temp |= 16;
    else
        temp &= ~16;

    if (back_plane & (1 << LCD_PIN_09))
        temp |= 8;
    else
        temp &= ~8;

    if (back_plane & (1 << LCD_PIN_10))
        temp |= 4;
    else
        temp &= ~4;

    if (back_plane & (1 << LCD_PIN_11))
        temp |= 2;
    else
        temp &= ~2;

    if (back_plane & (1 << LCD_PIN_12))
        temp |= 1;
    else
        temp &= ~1;

    return temp;
}

double get_weight (unsigned long int back_plane_a,
        unsigned long int back_plane_b,
        unsigned long int back_plane_c)
{
    double weight_value = 0;
    volatile unsigned long int temp = 0;

    /* Put all the bits on a sequencial order */
    back_plane_a = format_back_plane (back_plane_a);
    back_plane_b = format_back_plane (back_plane_b);
    back_plane_c = format_back_plane (back_plane_c);

    /* 1st digit (on left side) */
    temp =  (((back_plane_a & mask_1st_digit_bpa) >> 3) +
            ((back_plane_b & mask_1st_digit_bpb) >> 6) +
            ((back_plane_c & mask_1st_digit_bpc) >> 9));

    weight_value += (number_to_digit (temp)) * 100;

    /* 2nd digit */
    temp = ((back_plane_a & mask_2nd_digit_bpa) +
            ((back_plane_b & mask_2nd_digit_bpb) >> 3) +
            ((back_plane_c & mask_2nd_digit_bpc) >> 6));

    weight_value += (number_to_digit (temp)) * 10;

    /* 3rd digit */
    temp =  (((back_plane_a & mask_3rd_digit_bpa) << 3) +
            (back_plane_b & mask_3rd_digit_bpb) +
            ((back_plane_c & mask_3rd_digit_bpc) >> 3));

    weight_value += number_to_digit (temp);

    /* 4th digit (on right side) */
    temp = (((back_plane_a & mask_4th_digit_bpa) << 6) +
            ((back_plane_b & mask_4th_digit_bpb) << 3) +
            (back_plane_c & mask_4th_digit_bpc));

    weight_value += (number_to_digit (temp)) * 0.1;

    return weight_value;
}

