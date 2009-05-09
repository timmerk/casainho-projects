#include "lpc210x.h"
#include "main.h"
#include "system.h"
#include "lcd.h"
#include "timers.h"
#include "buttons.h"
#include "isrsupport.h"

int main (void)
{
    unsigned char str_volts[] = " Volts";
    unsigned char str_amps[] = " Amps";

    volatile double voltage_temp, current_temp;

    /* Initialize variables */
    voltage             = 0;
    current             = 0;
    wattage             = 0;
    wattage_hour        = 0;
    tick_update_lcd     = 0;

	/* Initialize the system */
    system_init ();

    /* Initialize the LCD */
    LCDInit();

    /* Initialize the ADC */
    adc_init ();

    /* Initialize the buttons */
    buttons_init ();

    /* Initialize the Timer0 */
    timer1_init ();
    enableIRQ ();

    while (1)
    {
        LCDSendCommand(DD_RAM_ADDR); /* LCD set first row */

        if (button_is_set(BUTTON_01))
        {
            LCDSendChar ('1');
        }
        else
        {
            LCDSendChar ('0');
        }

        if (button_is_set(BUTTON_02))
        {
            LCDSendChar ('2');
        }
        else
        {
            LCDSendChar ('0');
        }



#if 0
        //if (tick_update_lcd >= 50)
        //{

            LCDSendCommand(DD_RAM_ADDR); /* LCD set first row */
            voltage_temp = (double) adc_read(1);
            //LCDSendInt (voltage_temp, 4);

            LCDSendInt (000110, 6);

            LCDSendChar (' ');
            LCDSendChar (' ');
            LCDSendChar (' ');

            LCDSendFloat (000.102, 3, 3);

            //LCDSendFloat (voltage_temp * k_voltage, 2, 1);


            LCDSendCommand(DD_RAM_ADDR2);
            current_temp = (double) adc_read(0);
            LCDSendInt (current_temp, 4);
            LCDSendChar (' ');
            LCDSendChar (' ');
            LCDSendChar (' ');
            LCDSendFloat (current_temp * k_current, 2, 1);

            //tick_update_lcd = 0;
        //}
#endif
    }
}
