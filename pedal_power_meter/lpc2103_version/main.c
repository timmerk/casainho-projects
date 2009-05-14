#include "lpc210x.h"
#include "main.h"
#include "system.h"
#include "lcd.h"
#include "adc.h"
#include "timers.h"
#include "buttons.h"
#include "isrsupport.h"

int main (void)
{
    unsigned cpsr_temp;
    volatile double voltage_temp, current_temp;
    unsigned short int nr_adc_reads_temp;

    /* Initialize variables */
    voltage             = 0;
    current             = 0;
    wattage             = 0;
    wattage_hour        = 0;
    tick_update_lcd     = 0;
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
        if (tick_update_lcd >= 50)
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

            LCDSendCommand(DD_RAM_ADDR); /* LCD set first row */
            LCDSendFloat ((voltage_temp/nr_adc_reads_temp) * k_voltage, 2, 1);
            LCDSendChar (' ');
            LCDSendChar ('V');
            LCDSendChar ('o');
            LCDSendChar ('l');
            LCDSendChar ('t');
            LCDSendChar ('s');

            LCDSendCommand(DD_RAM_ADDR2); /* LCD set 2nd row */
            LCDSendFloat ((current_temp/nr_adc_reads_temp) * k_current, 2, 1);
            LCDSendChar (' ');
            LCDSendChar ('A');
            LCDSendChar ('m');
            LCDSendChar ('p');
            LCDSendChar ('s');
        }
    }
}
