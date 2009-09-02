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
#include "spi.h"

void spi_init (void)
{
    /* Enable the SPI pheripherial power */
    PCONP |= (1 << 8);

	/* setup SCK pin P04 */
	PINSEL0 &= ~(3 << 8);
	PINSEL0 |= (1 << 8);
	/* setup MISO pin P05 */
	PINSEL0 &= ~(3 << 10);
	PINSEL0 |= (1 << 10);
	/* setup MOSI pin P06 */
	PINSEL0 &= ~(3 << 12);
	PINSEL0 |= (1 << 12);

	/* Enable P0.7 as ouput for use as SSEL */
	IODIR |= (1 << 7);

	/* set SPI at ~230 kHz */
	SPI_SPCCR = 254;
	/* set master mode, clock polarity and phase (CPHA=0, CPOL=0) */
	SPI_SPCR = (1 << SPCR_MSTR);
}

void spi_set_clock(unsigned char clock)
{
    SPI_SPCCR = clock;
}

unsigned char spi_transfer_byte(unsigned char data)
{
	/* write SPI data */
    SPI_SPDR = data;
	/* wait until SPI transfer completes */
	while(!(SPI_SPSR & (1 << SPSR_SPIF)));
	/* return received data */

	return SPI_SPDR;
}
