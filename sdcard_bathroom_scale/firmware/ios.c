/*
 * Pedal Power Meter
 *
 * Copyright (C) Jorge Pinto aka Casainho, 2009.
 *
 *   casainho [at] gmail [dot] com
 *     www.casainho.net
 *
 * Released under the GPL Licence, Version 3
 */

#include "lpc210x.h"
#include "ios.h"

void ios_init (void)
{
    /* IOs are automatically configured as GPIO ports */

    /* IOs are automatically configured as inputs after
     *  reset of system */
}

unsigned char io_is_set (unsigned char io_number)
{
    /* The IO to where ??? are attatched have a pullup resistor so logic
     * is inverse */
    if ((IOPIN >> io_number) & 1)
        return 1;

    else
        return 0;
}

unsigned long int get_ios (void)
{
    return IOPIN;
}

