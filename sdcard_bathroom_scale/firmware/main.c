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
#include "main.h"
#include "system.h"
#include "lcd.h"
#include "timers.h"
#include "ios.h"
#include "isrsupport.h"

/* Global variables */
unsigned long int           back_plane_a,
                            back_plane_b,
                            back_plane_c;

int main (void)
{
    /* Initialize variables */
    volatile unsigned char temp_char = 0;
    volatile float temp_float = 0;
    unsigned char state = 0;

	/* Initialize the system */
    system_init ();

    /* Initialize the IOs */
    ios_init ();

    /* Initialize the LCD */
    lcd_init ();

    /* Initialize the Timer1 */

    timer1_init ();
    enableIRQ ();

    while (1)
    {
        if (io_is_set(LCD_PIN_13))
        {
            /* Acquire the signals from the LCD input */
            back_plane_c = get_ios ();
            while (io_is_set(LCD_PIN_13)) ;

            timer1_register (1750);
            while (timer1_run) ;
            back_plane_b = get_ios ();

            timer1_register (3500);
            while (timer1_run) ;
            back_plane_a = get_ios ();

            lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
            temp_float = get_weight (back_plane_a, back_plane_b, back_plane_c);
            lcd_send_float (temp_float, 3, 1);
            lcd_send_char (' ');
            lcd_send_char ('K');
            lcd_send_char ('g');

            state = 0;
        }

        else
        {
            switch (state)
            {
                case 0:
                timer1_register (100000);
                state = 1;
                break;

                case 1:
                if (!timer1_run)
                    lcd_send_command (CLR_DISP);
                break;
            }
        }
    }

    /* Go to idle mode to save power. System leaves idle mode on interrupt. */
    /* UNCOMENT IN THE END - NOT POSSIBLE TO DEBUG WITH IDLE MODE */
#if 0
    system_go_idle ();
    }
#endif
}
