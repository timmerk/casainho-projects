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

#include "lcd.h"

void die (const char *string)
{
    lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
    lcd_send_string (string);
    for (;;) ;
}
