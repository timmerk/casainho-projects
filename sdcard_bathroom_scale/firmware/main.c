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
LCD input
Pin nr  | LPC2103 pin
---------------------
 1  | P0.0
 2  | P0.1
 3  | P0.2
 4  | P0.3
 5  | P0.8
 6  | P0.9
 7  | P0.10
 8  | P0.11
 9  | P0.12
10  | P0.13
11  | P0.14
12  | P0.15
13  | P0.16 (EINT0 - external interrupt used. This is a signal from backplane 1)
 */

#include "lpc210x.h"
#include "main.h"
#include "system.h"
#include "lcd.h"
#include "timers.h"
#include "buttons.h"
#include "isrsupport.h"

/* Global variables */

int main (void)
{
    /* Initialize variables */

	/* Initialize the system */
    system_init ();

    /* Initialize the LCD */
    lcd_init ();

#if 0
    /* Initialize the Timer0 */
    timer1_init ();
    enableIRQ ();
#endif

    while (1)
    {
        lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
        lcd_send_char ('a');
        lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
        lcd_send_char ('b');
    }

    /* Go to idle mode to save power. System leaves idle mode on interrupt, so,
     * at each 5ms interrupt from Timer 1.
     */
    /* UNCOMENT IN THE END - NOT POSSIBLE TO DEBUG WITH IDLE MODE */
#if 0
    system_go_idle ();
    }
#endif
}
