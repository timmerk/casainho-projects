
typedef struct {
	unsigned short	year;	/* 1..4095 */
	unsigned char	month;	/* 1..12 */
	unsigned char	mday;	/* 1.. 31 */
	unsigned char	wday;	/* 1..7 */
	unsigned char	hour;	/* 0..23 */
	unsigned char	min;	/* 0..59 */
	unsigned char	sec;	/* 0..59 */
} RTC;

unsigned char rtc_gettime (RTC *rtc); /* Get time */
unsigned char rtc_settime (const RTC *rtc); /* Set time */

