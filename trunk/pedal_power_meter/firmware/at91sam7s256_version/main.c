#include "at91sam7s256.h"
#include "board.h"
#include "lcd.h"
#include "adc.h"
#include "main.h"

extern unsigned enableIRQ(void);

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


    /* Initialize the Atmel AT91SAM7S256 (watchdog, PLL clock, default
    interrupts, etc.) */
    LowLevelInit();

    /* Initialize the LCD */
    LCDInit();

    /* Initialize the Timer0 */
    //timer0_setup ();
    //enableIRQ ();

    /* Endless blink loop */
    while (1)
    {
        //if (tick_update_lcd >= 50)
        //{
            LCDSendCommand(DD_RAM_ADDR); /* LCD set first row */
            voltage_temp = (double) adc_read(0);
            LCDSendInt (voltage_temp, 4);
            LCDSendChar (' ');
            LCDSendChar (' ');
            LCDSendChar (' ');
            LCDSendFloat (voltage_temp * k_voltage, 2, 1);

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
