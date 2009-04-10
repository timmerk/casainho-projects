//  *****************************************************************************
//   						timerisr.c
//
//     Timer 0 Interrupt Service Routine
//
//	   entered when Timer0 RC compare interrupt asserts (200 msec period)
//     blinks LED2 (pin PA2)
//
//  Author:  James P Lynch  May 12, 2007
//  *****************************************************************************

#include "at91sam7s256.h"
#include "board.h"

void Timer0IrqHandler (void) {

	volatile AT91PS_TC 		pTC = AT91C_BASE_TC0;		// pointer to timer channel 0 register structure
	volatile AT91PS_PIO		pPIO = AT91C_BASE_PIOA;		// pointer to PIO register structure
	unsigned int 			dummy;						// temporary

	dummy = pTC->TC_SR;									// read TC0 Status Register to clear it							// increment the tick count

	if  ((pPIO->PIO_ODSR & LED) == LED)
		pPIO->PIO_CODR = LED; /* turn LED on */
	else
		pPIO->PIO_SODR = LED; /* turn LED off */
}
