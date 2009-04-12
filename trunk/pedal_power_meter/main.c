#include "at91sam7s256.h"
#include "board.h"
#include "lcd.h"
#include "adc.h"

int main (void)
{
    unsigned char str_volts[] = " Volts";
    unsigned char str_amps[] = " Amps";

    /* Initialize the Atmel AT91SAM7S256 (watchdog, PLL clock, default
    interrupts, etc.) */
    LowLevelInit();

    /* Initialize the LCD */
    LCDInit();

    /* Endless blink loop */
    while (1)
    {
        LCDSendCommand(DD_RAM_ADDR); /* LCD set first row */

        LCDSendInt (1234, 6);
        LCDSendCommand(DD_RAM_ADDR2); /* LCD set 2nd row */
        LCDSendFloat (1234.567, 6, 5);

#if 0
        unsigned int i;
        for (i = 0; i < 2000 ; i++)
        {
            voltage += adc_read(4);
        }

        /* Constant to multiply for ADC voltage reading value: 0.035810811 */
        lcd_print_float_type1 ((float) ((voltage/2000) * 0.035810811));
        //voltage = 0;
        LCDSendStr ((void *) str_volts);

        //LCDSendCommand(DD_RAM_ADDR2); /* LCD set 2nd row */

        /* Constant to multiply for ADC voltage reading value: 0.035810811 */
        //lcd_print_float_type2 ((double) ((voltage/2000) * 0.035810811));
        voltage = 0;
        //LCDSendStr ((void *) str_volts);
#endif

#if 0
        for (i = 0; i < 2000 ; i++)
        {
            current += adc_read(5);
        }

        /* Constant to multiply for ADC current reading value: ?? */
        lcd_print_float_type1 ((float) ((current/2000) * 0.035810811));
        current = 0;
        LCDSendStr ((void *) str_amps);
#endif
    }
}
