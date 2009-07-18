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

unsigned char timer1_run = 0;

void timer1_init (void);
void timer1_register (long int value_us);
void timer1_stop (void);
