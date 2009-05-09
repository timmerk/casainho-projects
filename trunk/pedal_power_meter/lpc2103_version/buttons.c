#include "lpc210x.h"
#include "buttons.h"

void buttons_init (void)
{
    /* P0.0 and P0.1 are automatically configured as GPIO ports */

    /* P0.0 and P0.1 are automatically configured as inputs after
     *  reset of system */
}

unsigned char button_is_set (unsigned char button_number)
{
    /* The IO to where buttons are attatched have a pullup resistor so logic
     * is inverse */
    if ((IOPIN & (1 << button_number)) == 1)
        return 0;

    else if ((IOPIN & (1 << button_number)) == 2)
        return 0;

    else
        return 1;
}



