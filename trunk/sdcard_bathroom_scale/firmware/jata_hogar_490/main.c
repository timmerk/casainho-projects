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

#include "lpc210x.h"
#include "system.h"
#include "isrsupport.h"
#include "lcd.h"
#include "timers.h"
#include "lcd_input.h"
#include "spi.h"
#include "../fatfs/diskio.h"
#include "../fatfs/ff.h"
#include "err.h"
#include "rtc.h"

#ifndef NULL
#define NULL    0
#endif

#define ON 1
#define OFF 0

/* Global variables */
volatile unsigned short int         lcd_input_digit_0,
                                    lcd_input_digit_1,
                                    lcd_input_digit_2,
                                    lcd_input_digit_3;

volatile unsigned short int timer1_counter = 0;
volatile unsigned char new_time = 0;

/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */


unsigned long get_fattime ()
{
    /* Pack date and time into a DWORD variable */
    return    ((unsigned long)(2009 - 1980) << 25)
            | ((unsigned long) 01 << 21)
            | ((unsigned long) 01 << 16)
            | ((unsigned long) 0 << 11)
            | ((unsigned long) 0 << 5)
            | ((unsigned long) 0 >> 1);
}

void power_switch (unsigned char state)
{
    if (state)
    {
        IODIR |= (1 << 26); /* Power control switch io pin as input */
        IOSET = (1 << 26); /* Turn on power for scale (the other
        switch controlled by hardware should be on until this time) */
    }

    else
    {
        IODIR |= (1 << 26);
        IOCLR = (1 << 26); /* Turning off the power for scale */
    }
}

int main (void)
{
    /* Initialize variables */
    volatile float weight = 0,
                   last_weight = 0;
    unsigned char state = 0;

    FATFS fs;       /* Work area (file system object) for logical drive */
    FIL file;       /* file object */
    FRESULT res;    /* FatFs function common result code */

    RTC rtc;

	/* Initialize the system */
    system_init ();

    /* Initialize the system for the LCD input */
    lcd_input_init ();

    /* Turn the power switch ON. Power should be ON on this stage because the
     * other hardware switch should be ON for at least 4 seconds. */
    power_switch (ON);

    /* Initialize the LCD */
    lcd_init ();

    spi_init ();

    /* Initialize the Timer1 */
    timer1_init ();
    enableIRQ ();
#if 0
    /*
     * Verify if time.txt file exist so system should update
     * RTC time with that info on the file.
     *
     * The time.txt file should have a string with the following format
     * (without square brackets):
     * [year][month][month day][week day][hour][minutes][seconds]
     * Example:
     * [2009][08][01][6][12][00][00]; string "200908016120000".
     */

    /* Register a work area for logical drive 0 */
    res = f_mount(0, &fs);
    if (res)
        debug ("Err mount fs");

    /* Open time.txt file */
    res = f_open(&file, "time.txt", FA_OPEN_EXISTING | FA_READ);
    if (!res) /* File time.txt exist, update system time now */
    {
        char string [15];
        /* Get the data from file */
        f_gets (&string[0], 15 + 1, &file);

        /* Setup RTC with the new value */
        rtc.sec = (((string[13] - 48) * 10) + (string[14] - 48));
        rtc.min = (((string[11] - 48) * 10) + (string[12] - 48));
        rtc.hour = (((string[9] - 48) * 10) + (string[10] - 48));
        rtc.wday = (string[8] - 48);
        rtc.mday = (((string[6] - 48) * 10) + (string[7] - 48));
        rtc.month = (((string[4] - 48) * 10) + (string[5] - 48));
        rtc.year = (((string[0] - 48) * 1000) + ((string[1] - 48) * 100) +
                    ((string[2] - 48) * 10) + (string[3] - 48));
        rtc_settime (&rtc);

        res = f_unlink ("time.txt");
        if (res)
        {
            lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
            debug ("Err delete file");
            timer1_counter = 20000;
            while (timer1_counter) ;
        }

        lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
        lcd_send_string ("Date changed");
        timer1_counter = 50000;
        while (timer1_counter) ;
    }
    /***************************************************************************
     **************************************************************************/
#endif
    for (;;)
    {
        /* Syncronize with LCD input pin 0. 465 on ADC should equal
         *                                                       to 1,5 volts */
        /* Wait for the end of sync impulse */
        while (lcd_input_adc_value (0) > 465) ;

        /* Wait for the start of sync impulse */
        if (lcd_input_adc_value (0) > 465)
        {
            unsigned char i;
            lcd_input_digit_0 = 0;
            for (i = 0; i < 13; i++)
            {
                /* Acquire the signals from the LCD input */
                lcd_input_digit_0 |= ((lcd_input_is_set (i)) << i);
            }

            /* Make a delay to go for the middle of next data bit */
            timer1_counter = 24; /* wait 2,4 ms */
            while (timer1_counter) ;
            lcd_input_digit_1 = 0;
            for (i = 0; i < 13; i++)
            {
                /* Acquire the signals from the LCD input */
                lcd_input_digit_1 |= ((lcd_input_is_set (i)) << i);
            }

            /* Make a delay to go for the middle of next data bit */
            timer1_counter = 16; /* wait 1,6 ms */
            while (timer1_counter) ;
            lcd_input_digit_2 = 0;
            for (i = 0; i < 13; i++)
            {
                /* Acquire the signals from the LCD input */
                lcd_input_digit_2 |= ((lcd_input_is_set (i)) << i);
            }

            /* Make a delay to go for the middle of next data bit */
            timer1_counter = 16; /* wait 1,6 ms */
            while (timer1_counter) ;
            lcd_input_digit_3 = 0;
            for (i = 0; i < 13; i++)
            {
                /* Acquire the signals from the LCD input */
                lcd_input_digit_3 |= ((lcd_input_is_set (i)) << i);
            }

            lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
            lcd_sent_int (lcd_input_digit_0, 8);
            lcd_sent_int (lcd_input_digit_1, 8);
            lcd_send_command (DD_RAM_ADDR2);
            lcd_sent_int (lcd_input_digit_2, 8);
            lcd_sent_int (lcd_input_digit_3, 8);
        }

        else
        {
            lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
            lcd_sent_string ("*");
            lcd_send_command (DD_RAM_ADDR2);
            lcd_sent_string ("*");
        }
    }
}





#if 0
            lcd_send_command (DD_RAM_ADDR); /* LCD set first row */
            weight = get_weight (   last_back_plane_a,
                                    last_back_plane_b,
                                    last_back_plane_c);

            lcd_send_string ("    ");
            lcd_send_float (weight, 3, 1);
            lcd_send_string (" Kg    ");

            /* Save the backplanes */
            last_back_plane_a = back_plane_a;
            last_back_plane_b = back_plane_b;
            last_back_plane_c = back_plane_c;

            state = 0;
        }

        else
        {
            switch (state)
            {
                case 0:
                timer1_counter = 5000;
                state = 1;

                case 1:
                if (new_time)
                {
                    new_time = 0;
                    /*
                     * Print current time on 2nd line of the LCD.
                     */
                    rtc_gettime (&rtc);
                    lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
                    lcd_send_string ("    ");
                    lcd_send_char ((rtc.hour / 10) + 48);
                    lcd_send_char ((rtc.hour - ((rtc.hour / 10) * 10)) + 48);
                    lcd_send_char (':');
                    lcd_send_char ((rtc.min / 10) + 48);
                    lcd_send_char ((rtc.min - ((rtc.min / 10) * 10)) + 48);
                    lcd_send_char (':');
                    lcd_send_char ((rtc.sec / 10) + 48);
                    lcd_send_char ((rtc.sec - ((rtc.sec / 10) * 10)) + 48);
                    lcd_send_string ("    ");
                }

                if (!timer1_counter)
                {
                   /* If weight is at least 40kg and
                    *  less then 110Kg(scale maximum limit = 150kg)... */
                    if (weight > 39 && weight < 111)
                    {
                        char error = 0;
                        /* Open source file */

                        /* Max Ana = 72kg = Min Jorge */
                        /* Identify by the interval of weight value, who is
                         * on the scale. I should take between 72kg to 110kg.
                         * My girlfriend Ana should take between 40kg and 72kg.
                         */
                        if (weight > 72)
                        {
                            res = f_open(&file, "w_jorge.csv",
                                                    FA_OPEN_ALWAYS | FA_WRITE);
                        }

                        else
                        {
                            res = f_open(&file, "w_ana.csv",
                                                    FA_OPEN_ALWAYS | FA_WRITE);
                        }

                        if (res)
                            error = 1;

                       /********************************************************
                        * Read from the weight.csv file, the last weight value.
                        *
                        *******************************************************/
                        if (file.fsize > 20 && !error)
                        {
                            char string [5];

                            /* Close the file */
                            res = f_close(&file);
                            if (res)
                                error = 1;

                            /* Open source file */
                            if (weight > 72)
                            {
                                res = f_open(&file, "w_jorge.csv",
                                                    FA_OPEN_EXISTING | FA_READ);
                            }

                            else
                            {
                                res = f_open(&file, "w_ana.csv",
                                                    FA_OPEN_EXISTING | FA_READ);
                            }

                            /* Seek to the place of the last weight value
                             * on the file */
                            res = f_lseek(&file, (file.fsize - 7));
                            if (res)
                                error = 1;

                            /* Get the data from file */
                            unsigned int counter;
                            f_read (&file, &string[0], 5, &counter);
                            if (counter != 5)
                            {
                                /* Couldn't read the 7 bytes that holds the
                                 * weight value. */
                                last_weight = 0;
                                break;
                                break;
                            }

                            /* Close the file */
                            res = f_close(&file);
                            if (res)
                                error = 1;

                            last_weight = (string[0] - 48) * 100;
                            last_weight += (string[1] - 48) * 10;
                            last_weight += (string[2] - 48);
                            last_weight += (float) (((float) (string[4] - 48))
                                                                / ((float) 10));

                            if (weight > 72)
                            {
                                res = f_open(&file, "w_jorge.csv",
                                                   FA_OPEN_EXISTING | FA_WRITE);
                            }

                            else
                            {
                                res = f_open(&file, "w_ana.csv",
                                                   FA_OPEN_EXISTING | FA_WRITE);
                            }

                            if (res)
                                error = 1;
                            /**************************************************/
                        }

                        /*******************************************************
                         * Write on "weight.csv" file the time and weight value,
                         * example: 12-8-2009 23:21:56,"092,1"
                         *
                         ******************************************************/
                        /* Move to end of the file to append data */
                        res = f_lseek(&file, file.fsize);
                        if (res)
                            error = 1;

                        /* Write the month day to the file */
                        res = f_printf(&file, "%d-", (int) rtc.mday);
                        if (res == EOF)
                            error = 1;

                        /* Write the month number to the file */
                        res = f_printf(&file, "%d-", (int) rtc.month);
                        if (res == EOF)
                            error = 1;

                        /* Write the year number to the file */
                        res = f_printf(&file, "%d ", (int) rtc.year);
                        if (res == EOF)
                            error = 1;

                        if (rtc.hour < 10)
                        {
                            /* Write the hour value to the file */
                            res = f_printf(&file, "0");
                            if (res == EOF)
                                error = 1;
                        }
                        /* Write the hour value to the file */
                        res = f_printf(&file, "%d:", (int) rtc.hour);
                        if (res == EOF)
                            error = 1;

                        if (rtc.min < 10)
                        {
                            /* Write the minute value to the file */
                            res = f_printf(&file, "0");
                            if (res == EOF)
                                error = 1;
                        }
                        /* Write the minute value to the file */
                        res = f_printf(&file, "%d:", (int) rtc.min);
                        if (res == EOF)
                            error = 1;

                        if (rtc.sec < 10)
                        {
                            /* Write the second value to the file */
                            res = f_printf(&file, "0");
                            if (res == EOF)
                                error = 1;
                        }
                        /* Write the second value to the file */
                        res = f_printf(&file, "%d,", (int) rtc.sec);
                        if (res == EOF)
                            error = 1;

                        /* Next, write the weight value, on the following
                         * format: "123,4"\r
                         */
                        /* Write the char '"' to the file */
                        res = f_printf(&file, "%c", '"');
                        if (res == EOF)
                            error = 1;

                        if (weight < 100)
                        {
                          /* Write the weight value to the file */
                            res = f_printf(&file, "0");
                            if (res == EOF)
                                error = 1;
                        }

                        if (weight < 10)
                        {
                            /* Write the weight value to the file */
                            res = f_printf(&file, "0");
                            if (res == EOF)
                                error = 1;
                        }

                        /* Write the weight value to the file */
                        res = f_printf(&file, "%d", (int) weight);
                        if (res == EOF)
                            error = 1;

                        /* Write the char ',' to the file */
                        res = f_printf(&file, "%c", ',');
                        if (res == EOF)
                            error = 1;

                        /* Write the weight value to the file */
                        res = f_printf(&file, "%d",
                                ((int) ((weight - ((int) weight)) * 10)));
                        if (res == EOF)
                            error = 1;

                        /* Write the char '"' to the file */
                        res = f_printf(&file, "%c", '"');
                        if (res == EOF)
                            error = 1;

                        /* Write the char "end of line" to the file */
                        res = f_printf(&file, "%c", '\r');
                        if (res == EOF)
                            error = 1;

                        /* Close the file */
                        res = f_close(&file);
                        if (res)
                            error = 1;

                        /* Unregister a work area before discard it */
                        res = f_mount(0, NULL);
                        if (res)
                            error = 1;
                        /*******************************************************
                         ******************************************************/

                        /*******************************************************
                         * Show the diference between last weight value.
                         *
                         ******************************************************/
                        if (last_weight > 39 && last_weight < 141)
                        {
                            lcd_send_command (DD_RAM_ADDR2);
                            if ((weight - last_weight) > 0.3)
                            {
                                lcd_send_string ("    +");
                                lcd_send_float ((weight - last_weight), 3, 1);
                                lcd_send_string ("kg");
                                lcd_send_string ("    ");
                            }

                            else if ((last_weight - weight) > 0.3)
                            {
                                lcd_send_string ("    -");
                                lcd_send_float ((last_weight - weight), 3, 1);
                                lcd_send_string ("kg");
                                lcd_send_string ("    ");
                            }

                            else
                            {
                                lcd_send_string (" No variations  ");
                            }

                            timer1_counter = 30000; /* wait 3 seconds */
                            while (timer1_counter) ;
                        }
                        /*******************************************************
                         ******************************************************/

                        /*
                         * If there was some error on saving on SD Card,
                         * warning about it.
                         */
                        lcd_send_command (DD_RAM_ADDR);
                        if (weight > 72)
                            lcd_send_string ("     Jorge      ");
                        else
                            lcd_send_string ("      Ana       ");

                        lcd_send_command (DD_RAM_ADDR2);
                        if (error)
                            lcd_send_string ("Weight not saved");
                        else
                            lcd_send_string ("  Weight saved  ");

                        timer1_counter = 15000; /* wait 1,5 second */
                        while (timer1_counter) ;
                    }

                    lcd_send_command (DD_RAM_ADDR2); /* LCD set 2nd row */
                    lcd_send_string ("Power down now..");

                    timer1_counter = 8000; /* wait 0,8 second */
                    while (timer1_counter) ;

                    /* Power switch OFF, the system shuts down himself */
                    power_switch (OFF);
                    for (;;) ;/* Hang here but system should shut off himself */
                }
                break;
            }
        }
    }
}
#endif
