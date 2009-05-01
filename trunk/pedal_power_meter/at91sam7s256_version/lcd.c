#include "lcd.h"
#include "at91sam7s256.h"

/* LCD pins connections:
 * -LCD ------------------------|-connected to-----
 *  1  - GND                    | GND
 *  2  - Vcc                    | Vcc    ~= + 5 volts
 *  3  - Contrast               | GND
 *  4  - _RS                    | PA0
 *  5  - _R/W                   | PA1
 *  6  - E                      | PA2
 *  11 - DB4                    | PA3
 *  12 - DB5                    | PA4
 *  13 - DB6                    | PA5
 *  14 - DB7                    | PA6
 */

#define RS      AT91C_PIO_PA0
#define RW      AT91C_PIO_PA1
#define E       AT91C_PIO_PA2
#define DB4     AT91C_PIO_PA3
#define DB5     AT91C_PIO_PA4
#define DB6     AT91C_PIO_PA5
#define DB7     AT91C_PIO_PA6

// POINTER
AT91PS_PIO    l_pPio   = AT91C_BASE_PIOA;

unsigned int data;
void Delay_mS (unsigned long a) { while (--a!=0); }

void SetPinsOnly(unsigned long pin) {
  l_pPio->PIO_SODR = l_pPio->PIO_ODSR | pin;
}

void ClearPinsOnly(unsigned long pin) {
  l_pPio->PIO_CODR = (~l_pPio->PIO_ODSR) | pin;
}

void E_Pulse()
{
    Delay_mS(50);           /* delay */
    l_pPio->PIO_SODR = E;   /* set E to high */
    Delay_mS(50);           /* delay */
    l_pPio->PIO_CODR = E;   /* set E to low */
}

void LCDSendCommand(unsigned char byte)
{
    /* set RS port to 0 -> display set to comand mode */
    /* set RW port to 0 */
    l_pPio->PIO_CODR =  (RW | RS);
    Delay_mS(20000);         //delay for LCD char ~2ms

    l_pPio->PIO_CODR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte >> 4); /* Get the 4 high bits */
    l_pPio->PIO_SODR = (unsigned int) (data << 3) ; /* set data */

    Delay_mS(20000);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */

    l_pPio->PIO_CODR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte & 0x0f); /* Get the 4 low bits */
    l_pPio->PIO_SODR = (unsigned int) (data << 3) ; /* set data */

    Delay_mS(20000);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */
}

void LCDInit (void)
{
    l_pPio->PIO_PER     = (RS | RW | E | DB4 | DB5 | DB6 | DB7);
    l_pPio->PIO_OER     = (RS | RW | E | DB4 | DB5 | DB6 | DB7);
    l_pPio->PIO_CODR    = (RS | RW | E | DB4 | DB5 | DB6 | DB7);

    /* clear RS, E, RW */
    l_pPio->PIO_CODR      = (RS | E | RW);
    Delay_mS(500000);     //delay ~50ms

    l_pPio->PIO_SODR      = (DB4 | DB5); //set D4 and D5 port to 1
    E_Pulse();                   /* high->low to E port (pulse) */
    Delay_mS(100000);     //delay ~10ms

    l_pPio->PIO_SODR      = (DB4 | DB5); //set D4 and D5 port to 1
    E_Pulse();                   /* high->low to E port (pulse) */
    Delay_mS(100000);     //delay ~10ms

    l_pPio->PIO_SODR      = (DB4 | DB5); //set D4 and D5 port to 1
    E_Pulse();                   /* high->low to E port (pulse) */
    Delay_mS(100000);                      //delay ~10ms

    l_pPio->PIO_CODR      = DB4; /* set D4 port to 0 */
    l_pPio->PIO_SODR      = DB5; /* set D5 port to 1 */
    E_Pulse();                   /* high->low to E port (pulse) */

    LCDSendCommand(DISP_ON);
    LCDSendCommand(CLR_DISP);       //Clear Display
}

void LCDSendChar(unsigned char byte)
{
    /* set RS port to 1 -> display set to data mode */
    l_pPio->PIO_SODR = RS;
    l_pPio->PIO_CODR = RW; /* set RW port to 0 */
    Delay_mS(20000);         //delay for LCD char ~2ms

    l_pPio->PIO_CODR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte >> 4); /* Get the 4 high bits */
    l_pPio->PIO_SODR = (unsigned int) (data << 3) ; /* set data */

    Delay_mS(20000);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */

    l_pPio->PIO_CODR = (DB4 | DB5 | DB6 | DB7); //clear D4-D7
    data = (unsigned int) (byte & 0x0f); /* Get the 4 low bits */
    l_pPio->PIO_SODR = (unsigned int) (data << 3) ; /* set data */

    Delay_mS(20000);         //delay for LCD char ~2ms
    E_Pulse();                   /* high->low to E port (pulse) */
}

void LCDSendInt(long number, unsigned char number_of_digits)
{
    int C[number_of_digits];
    unsigned char Temp=0, NumLen = 0, temp1;

    if (number < 0)
    {
        LCDSendChar('0');
        number = -number;
    }

    number_of_digits--;
    temp1 = number_of_digits;
    do
    {
        Temp++;
        C[Temp] = number % 10;

        /* Fill with "space" if digit is a 0 */
        if (C[Temp] == 0)
        {
            if (number_of_digits == temp1)
                C[Temp] = 0;

            else
                C[Temp] = 239;
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
