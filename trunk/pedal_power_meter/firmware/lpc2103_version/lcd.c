#include "lcd.h"
#include "lpc210x.h"

/* LCD pins connections:
 * -LCD ------------------------|-connected to-----
 *  1  - GND                    | GND
 *  2  - Vcc                    | Vcc ~= + 5 volts
 *  3  - Contrast               | 0,91V
 *  4  - _RS                    | P0.19
 *  5  - _R/W                   | P0.18
 *  6  - E                      | P0.17
 *  11 - DB4                    | P0.16
 *  12 - DB5                    | P0.15
 *  13 - DB6                    | P0.14
 *  14 - DB7                    | P0.13
 */

#define RS      (1 << 19)
#define RW      (1 << 18)
#define E       (1 << 17)
#define DB4     (1 << 16)
#define DB5     (1 << 15)
#define DB6     (1 << 14)
#define DB7     (1 << 13)

unsigned int data;
void Delay_mS (unsigned long a) { while (--a!=0); }

void E_Pulse(void)
{
    Delay_mS(LCD_CTRL_K_DLY);           /* delay */
    IOSET = E;   /* set E to high */
    Delay_mS(LCD_CTRL_K_DLY);           /* delay */
    IOCLR = E;   /* set E to low */
}

void LCDSendCommand(unsigned char byte)
{
    /* set RS port to 0 -> display set to comand mode */
    /* set RW port to 0 */
    IOCLR =  (RW | RS);
    Delay_mS(200*LCD_CTRL_K_DLY);         //delay for LCD char ~2ms

    IOCLR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte >> 4); /* Get the 4 high bits */
    /* set data */
    if (data & 1)
        IOSET = DB4;
    if (data & 2)
        IOSET = DB5;
    if (data & 4)
        IOSET = DB6;
    if (data & 8)
        IOSET = DB7;

    Delay_mS(200*LCD_CTRL_K_DLY);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */

    IOCLR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte & 0x0f); /* Get the 4 low bits */
    /* set data */
    if (data & 1)
        IOSET = DB4;
    if (data & 2)
        IOSET = DB5;
    if (data & 4)
        IOSET = DB6;
    if (data & 8)
        IOSET = DB7;

    Delay_mS(200*LCD_CTRL_K_DLY);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */
}

void LCDInit (void)
{
    /* Define all lines as outputs */
    IODIR = (RS | RW | E | DB4 | DB5 | DB6 | DB7);

    /* clear RS, E, RW */
    IOCLR      = (RS | E | RW);
    Delay_mS(5000*LCD_CTRL_K_DLY);     //delay ~50ms

    IOSET      = (DB4 | DB5); //set D4 and D5 port to 1
    E_Pulse();                   /* high->low to E port (pulse) */
    Delay_mS(1000*LCD_CTRL_K_DLY);     //delay ~10ms

    IOSET      = (DB4 | DB5); //set D4 and D5 port to 1
    E_Pulse();                   /* high->low to E port (pulse) */
    Delay_mS(1000*LCD_CTRL_K_DLY);     //delay ~10ms

    IOSET      = (DB4 | DB5); //set D4 and D5 port to 1
    E_Pulse();                   /* high->low to E port (pulse) */
    Delay_mS(1000*LCD_CTRL_K_DLY);                      //delay ~10ms

    IOCLR      = DB4; /* set D4 port to 0 */
    IOSET      = DB5; /* set D5 port to 1 */
    E_Pulse();                   /* high->low to E port (pulse) */

    LCDSendCommand(DISP_ON);
    LCDSendCommand(CLR_DISP);       //Clear Display
}

void LCDSendChar(unsigned char byte)
{
    /* set RS port to 1 -> display set to data mode */
    IOSET = RS;
    IOCLR = RW; /* set RW port to 0 */
    Delay_mS(200*LCD_CTRL_K_DLY);         //delay for LCD char ~2ms

    IOCLR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte >> 4); /* Get the 4 high bits */
    /* set data */
    if (data & 1)
        IOSET = DB4;
    if (data & 2)
        IOSET = DB5;
    if (data & 4)
        IOSET = DB6;
    if (data & 8)
        IOSET = DB7;

    Delay_mS(200*LCD_CTRL_K_DLY);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */

    IOCLR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte & 0x0f); /* Get the 4 low bits */
    /* set data */
    if (data & 1)
        IOSET = DB4;
    if (data & 2)
        IOSET = DB5;
    if (data & 4)
        IOSET = DB6;
    if (data & 8)
        IOSET = DB7;

    Delay_mS(200*LCD_CTRL_K_DLY);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */
}

void LCDSendInt(long number, unsigned char number_of_digits)
{
    volatile int C[17];
    volatile unsigned char Temp = 0, NumLen = 0, temp1, first_digit_non_zero = 0;

    number_of_digits--;
    temp1 = number_of_digits;
    do
    {
        Temp++;
        C[Temp] = number % 10;

        /* Decide to fill with "space" if digit is a 0 or fill with "0" */
        if (C[Temp] == 0)
        {
            if ((number_of_digits == temp1) || (number != 0))
                C[Temp] = 0; /* Print a "0" on right side of numbers and on
                                last one  */

            else
                C[Temp] = 239; /* Space char */
        }

        number = number/10;
    }
    while (number_of_digits--);

    NumLen = Temp;
    for (Temp = NumLen; Temp > 0; Temp--)
        LCDSendChar(C[Temp] + 48);
}

void LCDSendFloat(double number, unsigned char number_of_digits, \
        unsigned char number_of_floats)
{
    LCDSendInt ((int) number, number_of_digits);
    LCDSendChar ('.');

    number = (number - ((int) number));

    while (number_of_floats--)
    {
        number = number * 10;
        LCDSendChar (((int) number) + 48);
        number = (number - ((int) number));
    }
}

void LCDSendStr(unsigned char *string)
{
    while (*string != 0)
    {
        LCDSendChar(*string);
        string++;
    }
}
