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

int main (void)
{
    /* Initialize variables */
    unsigned long int temp = 0;

	/* Initialize the system */
    system_init ();

    /* Initialize the IOs */
    ios_init ();

    /* Initialize the LCD */
    lcd_init ();
#if 0
    /* Initialize the Timer0 */
    timer1_init ();
    enableIRQ ();
#endif
    while (1)
    {
        if (io_is_set(LCD_PIN_13))
        {
            temp = get_ios ();
            lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
            while (io_is_set(LCD_PIN_13)) ;

            if ((temp >> LCD_PIN_01) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_02) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_03) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_04) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_05) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_06) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_07) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_08) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_09) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_10) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_11) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            if ((temp >> LCD_PIN_12) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');

            lcd_send_char (' ');
            lcd_send_char (' ');
            if ((temp >> LCD_PIN_13) & 1)
                lcd_send_char ('1');
            else
                lcd_send_char ('0');
        }

        else
        {
            lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
            for (temp = 0; temp < 14; temp++)
                lcd_send_command (CUR_RIGHT);

            lcd_send_char ('0');
        }
    }

    /* Go to idle mode to save power. System leaves idle mode on interrupt. */
    /* UNCOMENT IN THE END - NOT POSSIBLE TO DEBUG WITH IDLE MODE */
#if 0
    system_go_idle ();
    }
#endif
}
