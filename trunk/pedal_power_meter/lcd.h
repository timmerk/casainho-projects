#define		CLR_DISP	   0x00000001
#define		DISP_ON		   0x0000000C
#define		DISP_OFF	   0x00000008
#define		CUR_HOME       0x00000002
#define		CUR_OFF 	   0x0000000C
#define     CUR_ON_UNDER   0x0000000E
#define     CUR_ON_BLINK   0x0000000F
#define     CUR_LEFT       0x00000010
#define     CUR_RIGHT      0x00000014
#define		CUR_UP  	   0x00000080
#define		CUR_DOWN	   0x000000C0
#define     ENTER          0x000000C0
#define		DD_RAM_ADDR    0x00000080
#define		DD_RAM_ADDR2   0x000000C0

void E_Pulse();
void LCDInit();
void LCDSendCommand(unsigned char byte);
void SmartUp(void);
void SmartDown(void);
void LCDSendChar(unsigned char byte);
void LCDSendInt(long a);
void LCDSendStr(unsigned char *string);
void LCDSendFloat(float a);
void lcd_print_float_type1 (float value);
void lcd_print_float_type2 (double value);

