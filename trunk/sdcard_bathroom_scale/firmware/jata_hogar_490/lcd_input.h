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

/*
 * LCD input
 * Pin nr  | Analog mux pin
 * ---------------------
 *  1  | y0
 *  2  | y1
 *  3  | y2
 *  4  | y3
 *  5  | y4
 *  6  | y5
 *  7  | y6
 *  8  | y7
 *  9  | y8
 * 10  | y9
 * 11  | y10
 * 12  | y11
 * 13  | y12
 *
 * Mux output pin | LPC2103 input pin
 * ----------------------------
 * z  |  P0.25 (ADC input channel 6)
 *
 *
 * Mux output pin | LPC2103 input pin
 * ----------------------------
 * S0  |  P0.10
 * S1  |  P0.11
 * S2  |  P0.12
 * S3  |  P0.13
 *
 */

/* LCD input signals */
/*
 *
 * Number 0: 11010111
 * Number 9: 10110111
 * Number 6: 11110101
 * Number 2: 11100011
 * Number 1: 00000110
 * Number
 *  general: degfxcba
 *
 *             a
 *           f   b
 *             g
 *           e   c
 *             d   x
 */

#define LCD_INPUT_ADC_CHANNEL 6

#define S0 (1 << 10)
#define S1 (1 << 11)
#define S2 (1 << 12)
#define S3 (1 << 13)

void lcd_input_init (void);
unsigned char lcd_input_is_set (unsigned char io_number);
unsigned short int lcd_input_adc_value (unsigned char io_number);
char number_to_digit (char lcd_input_digit);
double get_weight (void);
