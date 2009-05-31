#include "lpc210x.h"
#include "main.h"
#include "system.h"
#include "lcd.h"
#include "adc.h"
#include "timers.h"
#include "buttons.h"
#include "isrsupport.h"

/* Global variables */
volatile double             wattage, wattage_hour_user, wattage_hour_system;

volatile long int           voltage,
                            current,
                            tick_update_lcd, nr_adc_reads;

int main (void)
{
    unsigned char           menu = MENU_SHOW_USER_POWER;

    static unsigned char    button_state = 0, counter_button = 0;

    unsigned                cpsr_temp;
    volatile double         voltage_temp,
                            current_temp,
                            wattage_hour_temp,
                            wattage_temp;

    unsigned short int      nr_adc_reads_temp;

    /* Initialize variables */
    voltage                             = 0;
    current                             = 0;
    wattage                             = 0;
    wattage_hour_user                   = 0;
    wattage_hour_system                 = 0;
    tick_update_lcd                     = 0;
    nr_adc_reads                        = 0;

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
            case MENU_SHOW_USER_POWER:

            if (button_is_set(BUTTON_01) && !button_state)
            {
                menu = MENU_SHOW_SYSTEM_POWER;
                button_state = 1;
                counter_button = 0;
            }

            if (!button_is_set(BUTTON_01))
                button_state = 0;

            if (tick_update_lcd >= 50) /* Execute on every 50 * 5ms */
            {
                /* Disable the IRQ for avoid change on global variables used on
                * Timer1 IRQ handler code */
                cpsr_temp = disableIRQ ();
                wattage_temp = wattage;
                wattage = 0;
                wattage_hour_temp = wattage_hour_user;
                voltage = 0;
                current = 0;
                nr_adc_reads_temp = nr_adc_reads;
                nr_adc_reads = 0;
                tick_update_lcd = 0;
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
                LCDSendFloat (wattage_hour_temp, 3, 3);
                LCDSendChar (' ');
                LCDSendChar ('W');
                LCDSendChar ('/');
                LCDSendChar ('h');
                LCDSendChar ('o');
                LCDSendChar ('u');
                LCDSendChar ('r');
                LCDSendChar (' ');

                /* Verify if we need to reset the wattage_hour_user */
                if (button_is_set(BUTTON_02))
                {
                    if (++counter_button >= 8)
                    {
                        while (button_is_set(BUTTON_02))
                        {
                            LCDSendCommand (DD_RAM_ADDR);/* LCD set first row */
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar ('W');
                            LCDSendChar ('a');
                            LCDSendChar ('t');
                            LCDSendChar ('t');
                            LCDSendChar ('s');
                            LCDSendChar (' ');
                            LCDSendChar ('h');
                            LCDSendChar ('o');
                            LCDSendChar ('u');
                            LCDSendChar ('r');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');

                            LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar ('r');
                            LCDSendChar ('e');
                            LCDSendChar ('s');
                            LCDSendChar ('e');
                            LCDSendChar ('t');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                        }

                        /* Disable the IRQ for avoid change on global variables used on
                        * Timer1 IRQ handler code */
                        cpsr_temp = disableIRQ ();
                        wattage_hour_user = 0;
                        tick_update_lcd = 0;
                        /* Restore the IRQ */
                        restoreIRQ (cpsr_temp);

                        counter_button = 0;
                    }
                }
            }

            break;

            case MENU_SHOW_SYSTEM_POWER:

            if (button_is_set(BUTTON_01) && !button_state)
            {
                menu = MENU_SHOW_USER_POWER;
                button_state = 1;
                counter_button = 0;
            }

            if (!button_is_set(BUTTON_01))
                button_state = 0;

            if (tick_update_lcd >= 50) /* Execute on every 50 * 5ms */
            {
                /* Disable the IRQ for avoid change on global variables used on
                * Timer1 IRQ handler code */
                cpsr_temp = disableIRQ ();
                wattage_temp = wattage;
                wattage = 0;
                wattage_hour_temp = wattage_hour_system;
                voltage = 0;
                current = 0;
                nr_adc_reads_temp = nr_adc_reads;
                nr_adc_reads = 0;
                tick_update_lcd = 0;
                /* Restore the IRQ */
                restoreIRQ (cpsr_temp);

                LCDSendCommand (DD_RAM_ADDR); /* LCD set first row */
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar ('T');
                LCDSendChar ('o');
                LCDSendChar ('t');
                LCDSendChar ('a');
                LCDSendChar ('l');
                LCDSendChar (' ');
                LCDSendChar ('p');
                LCDSendChar ('o');
                LCDSendChar ('w');
                LCDSendChar ('e');
                LCDSendChar ('r');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');

                LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                LCDSendChar (' ');
                LCDSendFloat (wattage_hour_temp, 4, 3);

                LCDSendChar (' ');
                LCDSendChar ('W');
                LCDSendChar ('/');
                LCDSendChar ('h');
                LCDSendChar ('o');
                LCDSendChar ('u');
                LCDSendChar ('r');

                /* Verify if we need to go on the advanced menus */
                if (button_is_set(BUTTON_02))
                {
                    if (++counter_button >= 20)
                    {
                        while (button_is_set(BUTTON_02))
                        {
                            LCDSendCommand (DD_RAM_ADDR);/* LCD set first row */
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar ('G');
                            LCDSendChar ('o');
                            LCDSendChar ('i');
                            LCDSendChar ('n');
                            LCDSendChar ('g');
                            LCDSendChar (' ');
                            LCDSendChar ('t');
                            LCDSendChar ('o');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');

                            LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                            LCDSendChar (' ');
                            LCDSendChar ('a');
                            LCDSendChar ('d');
                            LCDSendChar ('v');
                            LCDSendChar ('a');
                            LCDSendChar ('n');
                            LCDSendChar ('c');
                            LCDSendChar ('e');
                            LCDSendChar ('d');
                            LCDSendChar (' ');
                            LCDSendChar ('m');
                            LCDSendChar ('e');
                            LCDSendChar ('n');
                            LCDSendChar ('u');
                            LCDSendChar ('s');
                            LCDSendChar (' ');
                        }

                        menu = MENU_SHOW_VOLTAGE_CURRENT;

                        counter_button = 0;
                    }
                }
            }

            break;

            case MENU_SHOW_VOLTAGE_CURRENT:

            if (button_is_set(BUTTON_01) && !button_state)
            {
                menu = MENU_SHOW_ADC_READINGS;
                button_state = 1;
                counter_button = 0;
            }

            if (!button_is_set(BUTTON_01))
                button_state = 0;

            if (tick_update_lcd >= 50) /* Execute on every 50 * 5ms */
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
                tick_update_lcd = 0;
                /* Restore the IRQ */
                restoreIRQ (cpsr_temp);

                LCDSendCommand (DD_RAM_ADDR); /* LCD set first row */
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendFloat ((voltage_temp/nr_adc_reads_temp) *K_VOLTAGE, 2,1);
                LCDSendChar (' ');
                LCDSendChar ('V');
                LCDSendChar ('o');
                LCDSendChar ('l');
                LCDSendChar ('t');
                LCDSendChar ('s');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');

                LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendFloat ((current_temp/nr_adc_reads_temp) *K_CURRENT, 2,1);
                LCDSendChar (' ');
                LCDSendChar ('A');
                LCDSendChar ('m');
                LCDSendChar ('p');
                LCDSendChar ('s');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');
                LCDSendChar (' ');

                /* Verify if we need to go on the normal menus */
                if (button_is_set(BUTTON_02))
                {
                    if (++counter_button >= 20)
                    {
                        while (button_is_set(BUTTON_02))
                        {
                            LCDSendCommand (DD_RAM_ADDR);/* LCD set first row */
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar ('L');
                            LCDSendChar ('e');
                            LCDSendChar ('a');
                            LCDSendChar ('v');
                            LCDSendChar ('i');
                            LCDSendChar ('n');
                            LCDSendChar ('g');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');
                            LCDSendChar (' ');

                            LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                            LCDSendChar (' ');
                            LCDSendChar ('a');
                            LCDSendChar ('d');
                            LCDSendChar ('v');
                            LCDSendChar ('a');
                            LCDSendChar ('n');
                            LCDSendChar ('c');
                            LCDSendChar ('e');
                            LCDSendChar ('d');
                            LCDSendChar (' ');
                            LCDSendChar ('m');
                            LCDSendChar ('e');
                            LCDSendChar ('n');
                            LCDSendChar ('u');
                            LCDSendChar ('s');
                            LCDSendChar (' ');
                        }

                        menu = MENU_SHOW_USER_POWER;

                        counter_button = 0;
                    }
                }
            }

            break;

            case MENU_SHOW_ADC_READINGS:

            disableIRQ ();
            LCDSendCommand (CLR_DISP);

            while (1)
            {
                LCDSendCommand (DD_RAM_ADDR); /* LCD set first row */
                LCDSendChar ('A');
                LCDSendChar ('D');
                LCDSendChar ('C');
                LCDSendChar (' ');
                LCDSendChar ('v');
                LCDSendChar ('o');
                LCDSendChar ('l');
                LCDSendChar ('t');
                LCDSendChar ('a');
                LCDSendChar ('g');
                LCDSendChar ('e');
                LCDSendChar (':');
                int i;
                for (i = 0; i < 5000; i++)
                    voltage += adc_read (6);
                LCDSendInt (voltage/5000, 4);
                voltage = 0;

                LCDSendCommand (DD_RAM_ADDR2); /* LCD set 2nd row */
                LCDSendChar ('A');
                LCDSendChar ('D');
                LCDSendChar ('C');
                LCDSendChar (' ');
                LCDSendChar ('c');
                LCDSendChar ('u');
                LCDSendChar ('r');
                LCDSendChar ('r');
                LCDSendChar ('e');
                LCDSendChar ('n');
                LCDSendChar ('t');
                LCDSendChar (':');
                for (i = 0; i < 5000; i++)
                    current += adc_read (2);
                LCDSendInt (current/5000, 4);
                current = 0;

                if (button_is_set(BUTTON_01) && !button_state)
                {
                    menu = MENU_SHOW_VOLTAGE_CURRENT;
                    button_state = 1;
                    counter_button = 0;
                    voltage = 0;
                    current = 0;
                    restoreIRQ (cpsr_temp);
                    break;
                    break;
                }

                if (!button_is_set(BUTTON_01))
                    button_state = 0;
            }

            break;

            default:
            break;
        }

    /* Go to idle mode to save power. System leaves idle mode on interrupt, so,
     * at each 5ms interrupt from Timer 1.
     */
    /* UNCOMENT IN THE END - NOT POSSIBLE TO DEBUG WITH IDLE MODE */
    //system_go_idle ();
    }
}
