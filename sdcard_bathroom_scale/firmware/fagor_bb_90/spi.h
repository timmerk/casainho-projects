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

#define SPCR_MSTR			5
#define SPSR_SPIF			7

void spi_init (void);
void spi_set_clock(unsigned char clock);
unsigned char spi_transfer_byte(unsigned char data);
