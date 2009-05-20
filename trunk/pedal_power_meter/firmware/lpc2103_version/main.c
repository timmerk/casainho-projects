#include "lpc210x.h"
#include "main.h"
#include "system.h"
#include "lcd.h"
#include "adc.h"
#include "timers.h"
#include "buttons.h"
#include "isrsupport.h"

/* Global variables */
double voltage, current, wattage, wattage_hour;
short tick_update_lcd, nr_adc_reads;

int main (void)
{
    unsigned char
                            menu = MENU_SHOW_VOLTAGE_CURRENT;

    static unsigned char
                            button_state = 0;

    unsigned cpsr_temp;
    volatile double voltage_temp, current_temp, wattage_temp;
    unsigned short int nr_adc_reads_temp;

    /* Initialize variables */
    voltage             = 0;
    current             = 0;
    wattage             = 0;
    wattage_hour        = 0;
    tick_update_lcd     = 1;
    nr_adc_reads        = 0;

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
        switch (menu)
        {
            case MENU_SHOW_POWER:

            if (button_is_set(BUTTON_01) && !button_state)
            {
                menu = MENU_SHOW_VOLTAGE_CURRENT;
                button_state = 1;
            }

            if (!button_is_set(BUTTON_01))
                button_state = 0;

            if (tick_update_lcd > 50) /* Execute on every 50 * 5ms */
            {
                /* Disable the IRQ for avoid change on global variables used on
                * Timer1 IRQ handler code */
                cpsr_temp = disableIRQ ();
                wattage_temp = wattage;
                wattage = 0;
                voltage = 0;
                current = 0;
                nr_adc_reads_temp = nr_adc_reads;
                nr_adc_reads = 0;
                tick_update_lcd = 1;
                /* Restore the IRQ */
                restoreIRQ (cpsr_temp);

                LCDSendCommand (DD_RAM_ADDR); /* LCD set first row */
                LCDSendChar (' ');
                LCDSendFloat ((wattage_temp/nr_adc_reads_temp), 3, 1);
                LCDSendChar (' ');
                LCDSendChar ('W');
                LCDSendChar ('a');
                LCDSendChar ('t');
                LCDSendChar ('t');
                LCDSendChar ('s');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');

                LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                LCDSendChar (' ');
                LCDSendFloat (20, 2,1);
                LCDSendChar (' ');
                LCDSendChar ('W');
                LCDSendChar ('/');
                LCDSendChar ('h');
                LCDSendChar ('o');
                LCDSendChar ('u');
                LCDSendChar ('r');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');
            }

            break;

            case MENU_SHOW_VOLTAGE_CURRENT:

            if (button_is_set(BUTTON_01) && !button_state)
            {
                menu = MENU_SHOW_POWER;
                button_state = 1;
            }

            if (!button_is_set(BUTTON_01))
                button_state = 0;

            if (tick_update_lcd > 50) /* Execute on every 50 * 5ms */
            {
                /* Disable the IRQ for avoid change on global variables used on
                 * Timer1 IRQ handler code */
                cpsr_temp = disableIRQ ();
                voltage_temp = voltage;
                voltage = 0;
                current_temp = current;
                current = 0;
                nr_adc_reads_temp = nr_adc_reads;
                nr_adc_reads = 0;
                tick_update_lcd = 1;
                /* Restore the IRQ */
                restoreIRQ (cpsr_temp);

                LCDSendCommand (DD_RAM_ADDR); /* LCD set first row */
                LCDSendInt ((voltage_temp/nr_adc_reads_temp), 4);
                LCDSendChar (' ');
                LCDSendFloat ((voltage_temp/nr_adc_reads_temp) *K_VOLTAGE, 2,1);
                LCDSendChar (' ');
                LCDSendChar ('V');
                LCDSendChar ('o');
                LCDSendChar ('l');
                LCDSendChar ('t');
                LCDSendChar ('s');
                LCDSendChar (' ');

                LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                LCDSendInt ((current_temp/nr_adc_reads_temp), 4);
                LCDSendChar (' ');
                LCDSendFloat ((current_temp/nr_adc_reads_temp) *K_CURRENT, 2,1);
                LCDSendChar (' ');
                LCDSendChar ('A');
                LCDSendChar ('m');
                LCDSendChar ('p');
                LCDSendChar ('s');
                LCDSendChar (' ');
                LCDSendChar (' ');
            }

            break;

            default:
            break;
        }
    }
}
