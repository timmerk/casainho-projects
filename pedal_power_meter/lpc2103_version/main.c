#include "lpc210x.h"
#include "system.h"
#include "timers.h"

int main (void)
{
    int j;

	/* Initialize the system */
    system_init ();

	//timer1_init ();


	// set io pins for led P0.20
	IODIR |= (1 << 20);	// pin P0.20 is an output
	IOCLR =  (1 << 20);	// led on

	// endless loop to toggle the red  LED P0.26
	while (1)
	{
        IOCLR = (1 << 20);
        for (j = 0; j < 500000; j++ );		// wait 500 msec
        IOSET = (1 << 20);
        for (j = 0; j < 300000; j++ );
	}
}
