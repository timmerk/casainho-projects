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

extern volatile unsigned short int timer1_counter;

void timer0_init (void);
void timer0_register (void);
void timer1_init (void);
void timer1_register (long int value_us);
void timer1_stop (void);
void timer2_init (void);
void timer2_register (void);
