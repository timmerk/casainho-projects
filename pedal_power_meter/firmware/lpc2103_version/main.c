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
#include "main.h"
#include "system.h"
#include "lcd.h"
#include "adc.h"
#include "timers.h"
#include "buttons.h"
#include "isrsupport.h"

/* Global variables */
double              wattage = 0,
                    wattage_hour_user = 0,
                    wattage_hour_system = 0;

long int            voltage = 0,
                    current = 0,
                    tick_update_lcd = 0,
                    nr_adc_reads = 0;

int main (void)
{
    unsigned char           menu = MENU_SHOW_USER_POWER;

    static unsigned char    button_state = 0, counter_button = 0;

    unsigned                cpsr_temp;
    double                  voltage_temp,
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
    lcd_init ();

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

                lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
                lcd_send_char (' ');
                lcd_send_float ((wattage_temp/nr_adc_reads_temp), 3, 1);
                lcd_send_char (' ');
                lcd_send_char ('W');
                lcd_send_char ('a');
                lcd_send_char ('t');
                lcd_send_char ('t');
                lcd_send_char ('s');
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');

                lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
                lcd_send_char (' ');
                lcd_send_float (wattage_hour_temp, 3, 3);
                lcd_send_char (' ');
                lcd_send_char ('W');
                lcd_send_char ('/');
                lcd_send_char ('h');
                lcd_send_char ('o');
                lcd_send_char ('u');
                lcd_send_char ('r');
                lcd_send_char (' ');

                /* Verify if we need to reset the wattage_hour_user */
                if (button_is_set(BUTTON_02))
                {
                    if (++counter_button >= 8)
                    {
                        while (button_is_set(BUTTON_02))
                        {
                            lcd_send_command (DD_RAM_ADDR);
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char ('W');
                            lcd_send_char ('a');
                            lcd_send_char ('t');
                            lcd_send_char ('t');
                            lcd_send_char ('s');
                            lcd_send_char (' ');
                            lcd_send_char ('h');
                            lcd_send_char ('o');
                            lcd_send_char ('u');
                            lcd_send_char ('r');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');

                            lcd_send_command (DD_RAM_ADDR2);
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char ('r');
                            lcd_send_char ('e');
                            lcd_send_char ('s');
                            lcd_send_char ('e');
                            lcd_send_char ('t');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
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

                lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char ('T');
                lcd_send_char ('o');
                lcd_send_char ('t');
                lcd_send_char ('a');
                lcd_send_char ('l');
                lcd_send_char (' ');
                lcd_send_char ('p');
                lcd_send_char ('o');
                lcd_send_char ('w');
                lcd_send_char ('e');
                lcd_send_char ('r');
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');

                lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
                lcd_send_char (' ');
                lcd_send_float (wattage_hour_temp, 4, 3);

                lcd_send_char (' ');
                lcd_send_char ('W');
                lcd_send_char ('/');
                lcd_send_char ('h');
                lcd_send_char ('o');
                lcd_send_char ('u');
                lcd_send_char ('r');

                /* Verify if we need to go on the advanced menus */
                if (button_is_set(BUTTON_02))
                {
                    if (++counter_button >= 20)
                    {
                        while (button_is_set(BUTTON_02))
                        {
                            lcd_send_command (DD_RAM_ADDR);
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char ('G');
                            lcd_send_char ('o');
                            lcd_send_char ('i');
                            lcd_send_char ('n');
                            lcd_send_char ('g');
                            lcd_send_char (' ');
                            lcd_send_char ('t');
                            lcd_send_char ('o');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');

                            lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
                            lcd_send_char (' ');
                            lcd_send_char ('a');
                            lcd_send_char ('d');
                            lcd_send_char ('v');
                            lcd_send_char ('a');
                            lcd_send_char ('n');
                            lcd_send_char ('c');
                            lcd_send_char ('e');
                            lcd_send_char ('d');
                            lcd_send_char (' ');
                            lcd_send_char ('m');
                            lcd_send_char ('e');
                            lcd_send_char ('n');
                            lcd_send_char ('u');
                            lcd_send_char ('s');
                            lcd_send_char (' ');
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

                lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_float ((((voltage_temp/nr_adc_reads_temp) * \
                                                K_VOLTAGE) + M_VOLTAGE), 2,1);

                lcd_send_char (' ');
                lcd_send_char ('V');
                lcd_send_char ('o');
                lcd_send_char ('l');
                lcd_send_char ('t');
                lcd_send_char ('s');
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');

                lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');
          /* First 3 values from ADC_current should not be used since they are
           *  very non linear.
           */
                current_temp = (current_temp/nr_adc_reads_temp);
                if (current_temp < 3)
                {
                    lcd_send_float (0, 2, 1);
                }

                if (current_temp >= 3 && current_temp < 60)
                {
                    current_temp = \
                   ((-0.000004 * current_temp * current_temp * current_temp) + \
                   (0.0005 * current_temp * current_temp) - \
                   (0.0028 * current_temp) + 0.356);
                    lcd_send_float (current_temp, 2, 1);
                }

                if (current_temp >= 60)
                {
                    lcd_send_float (((current_temp * K_CURRENT) + \
                            M_CURRENT),2,1);
                }

                lcd_send_char (' ');
                lcd_send_char ('A');
                lcd_send_char ('m');
                lcd_send_char ('p');
                lcd_send_char ('s');
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');
                lcd_send_char (' ');

                /* Verify if we need to go on the normal menus */
                if (button_is_set(BUTTON_02))
                {
                    if (++counter_button >= 20)
                    {
                        while (button_is_set(BUTTON_02))
                        {
                            lcd_send_command (DD_RAM_ADDR);
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char ('L');
                            lcd_send_char ('e');
                            lcd_send_char ('a');
                            lcd_send_char ('v');
                            lcd_send_char ('i');
                            lcd_send_char ('n');
                            lcd_send_char ('g');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');
                            lcd_send_char (' ');

                            lcd_send_command (DD_RAM_ADDR2);
                            lcd_send_char (' ');
                            lcd_send_char ('a');
                            lcd_send_char ('d');
                            lcd_send_char ('v');
                            lcd_send_char ('a');
                            lcd_send_char ('n');
                            lcd_send_char ('c');
                            lcd_send_char ('e');
                            lcd_send_char ('d');
                            lcd_send_char (' ');
                            lcd_send_char ('m');
                            lcd_send_char ('e');
                            lcd_send_char ('n');
                            lcd_send_char ('u');
                            lcd_send_char ('s');
                            lcd_send_char (' ');
                        }

                        menu = MENU_SHOW_USER_POWER;

                        counter_button = 0;
                    }
                }
            }

            break;

            case MENU_SHOW_ADC_READINGS:

            disableIRQ ();
            lcd_send_command (CLR_DISP);

            while (1)
            {
                lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
                lcd_send_char ('A');
                lcd_send_char ('D');
                lcd_send_char ('C');
                lcd_send_char (' ');
                lcd_send_char ('v');
                lcd_send_char ('o');
                lcd_send_char ('l');
                lcd_send_char ('t');
                lcd_send_char ('a');
                lcd_send_char ('g');
                lcd_send_char ('e');
                lcd_send_char (':');
                int i;
                for (i = 0; i < 5000; i++)
                    voltage += adc_read (6);
                lcd_send_int (voltage/5000, 4);
                voltage = 0;
                lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
                lcd_send_char ('A');
                lcd_send_char ('D');
                lcd_send_char ('C');
                lcd_send_char (' ');
                lcd_send_char ('c');
                lcd_send_char ('u');
                lcd_send_char ('r');
                lcd_send_char ('r');
                lcd_send_char ('e');
                lcd_send_char ('n');
                lcd_send_char ('t');
                lcd_send_char (':');
                for (i = 0; i < 5000; i++)
                    current += adc_read (2);
                lcd_send_int (current/5000, 4);
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
    system_go_idle ();
    }
}
