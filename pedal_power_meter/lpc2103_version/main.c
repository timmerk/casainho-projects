#include "lpc210x.h"
#include "main.h"
#include "system.h"
#include "lcd.h"

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

    /* Initialize the Timer0 */
    //timer1_init ();
    //enableIRQ ();

    /* Endless blink loop */
    while (1)
    {
        //if (tick_update_lcd >= 50)
        //{

        LCDSendCommand(DD_RAM_ADDR); /* LCD set first row */
        LCDSendChar('1');
        LCDSendChar('2');


        //LCDSendCommand(DD_RAM_ADDR); /* LCD set first row */
            //voltage_temp = (double) adc_read(0);
            /* voltage_temp = (double) 511;

            LCDSendInt (voltage_temp, 4);
            LCDSendChar (' ');
            LCDSendChar (' ');
            LCDSendChar (' ');
            LCDSendFloat (voltage_temp * k_voltage, 2, 1); */


            //LCDSendCommand(DD_RAM_ADDR2);
            //voltage_temp = (double) adc_read(1);
            //LCDSendInt (current_temp, 4);
            //LCDSendChar (' ');
            //LCDSendChar (' ');
            //LCDSendChar (' ');
            //LCDSendFloat (current_temp * k_current, 2, 1);


            //tick_update_lcd = 0;
        //}
    }
}
