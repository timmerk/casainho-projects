/*--------------------------------------------------------------------------*/
/*  RTC controls                                                            */

#include "lpc210x.h"
#include "rtc.h"

unsigned char rtc_gettime (RTC *rtc)
{
	unsigned long d, t;

	//do {
		t = RTC_CTIME0;
		d = RTC_CTIME1;
	//} while (t != RTC_CTIME0 || d != RTC_CTIME1);

	rtc->sec = t & 63;
	rtc->min = (t >> 8) & 63;
	rtc->hour = (t >> 16) & 31;
	rtc->wday = (t >> 24) & 7;
	rtc->mday = d & 31;
	rtc->month = (d >> 8) & 15;
	rtc->year = (d >> 16) & 4095;

	return 1;
}

unsigned char rtc_settime (const RTC *rtc)
{
    /* Enable The RTC power/clock pheripherial power */
    PCONP |= (1 << 9);

	/* Stop RTC */
	RTC_CCR = (1 << 1);

	/* Update RTC registers */
	RTC_SEC = rtc->sec;
	RTC_MIN = rtc->min;
	RTC_HOUR = rtc->hour;
	RTC_DOW = rtc->wday;
	RTC_DOM = rtc->mday;
	RTC_MONTH = rtc->month;
	RTC_YEAR = rtc->year;

	/* Start RTC with external XTAL */
	RTC_CCR = (1 << 4) | (1 << 0);

	return 1;
}

