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

void LCDSendInt(long a)
{
    int C[20];
    unsigned char Temp=0, NumLen = 0;
    if (a < 0)
    {
        LCDSendChar('-');
        a = -a;
    }
    do
    {
        Temp++;
        C[Temp] = a % 10;
        a = a/10;
    }
    while (a);
    NumLen = Temp;
    for (Temp = NumLen; Temp>0; Temp--) LCDSendChar(C[Temp] + 48);
}

void LCDSendFloat(float a)
{
    LCDSendInt ((int) a);
    LCDSendChar ('.');
    a = (int) a % 10;
    LCDSendChar ((int) a);
    a = (int) a % 10;
    LCDSendChar ((int) a);
}

void LCDSendStr(unsigned char *string)
{
    while (*string != 0)
    {
        LCDSendChar(*string);
        string++;
    }
}

/*
 * Prints a float on LCD like this: "98,7".
 */
void lcd_print_float_type1 (float value)
{
    float temp1, temp2, temp3;

    /* Calculate and send 1st digit, at right side */
    temp1 = (int) (value / 10);
    if (temp1)
        LCDSendChar(((unsigned char) temp1 + 48));
    else
        LCDSendChar(32); /* send a space when digit is 0 */

    /* Calculate and send 2nd digit */
    temp2 = (int) (value - (temp1 * 10));
    if (temp2)
        LCDSendChar(((unsigned char) temp2 + 48));
    else
        LCDSendChar('0');

    /* Send the "." char */
    LCDSendChar('.');

    /* Calculate and send the last digit */
    temp3 = (value - ((temp1 * 10) + temp2));
    temp3 = (int) (temp3 * 10);
    if (temp3)
        LCDSendChar(((unsigned char) temp3 + 48));
    else
        LCDSendChar('0');
}

/*
 * Prints a float on LCD like this: "987,6".
 */
void lcd_print_float_type2 (double value)
{
    double temp1, temp2, temp3, temp4;

    /* Calculate and send 1st digit, at right side */
    temp1 = (int) (value / 100);
    if (temp1)
        LCDSendChar(((unsigned char) temp1 + 48));
    else
        LCDSendChar(32); /* send a space when digit is 0 */

    /* Calculate and send 2nd digit */
    temp2 = (value - (temp1 * 100));
    temp2 = (int) (temp2 / 10);
    if (temp2)
        LCDSendChar(((unsigned char) temp2 + 48));
    else
        LCDSendChar(32); /* send a space when digit is 0 */

    /* Calculate and send 3rd digit */
    temp3 = (int) (value - ((temp1 * 100) + (temp2 * 10)));
    if (temp3)
        LCDSendChar(((unsigned char) temp3 + 48));
    else
        LCDSendChar('0');

    /* Send the "." char */
    LCDSendChar('.');

    /* Calculate and send the last digit */
    temp4 = (value - ((temp1 * 100) + (temp2 * 10) + temp3));
    temp4 = (int) (temp4 * 10);
    if (temp4)
        LCDSendChar(((unsigned char) temp4 + 48));
    else
        LCDSendChar('0');
}

void SmartUp(void)
{
  int i;
  for(i=0; i<40; i++)
      LCDSendCommand(CUR_RIGHT);
}

void SmartDown(void)
{
  int i;
  for(i=0; i<40; i++)
      LCDSendCommand(CUR_LEFT);
}


