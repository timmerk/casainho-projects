#include "at91sam7s256.h"

/* Global variables */
extern double voltage, current, wattage, wattage_hour;
extern long int tick_update_lcd;

/* Each Timer0 interrupt happens at ~5ms (234 * 21.3092396896us) */
void timer0_irq_handler (void)
{
    short int   voltage_temp,
                current_temp,
                wattage_temp;

    /* Pointer to timer channel 0 register structure */
    volatile AT91PS_TC pTC = AT91C_BASE_TC0;

	unsigned int dummy; /* Temporary */
	dummy = pTC->TC_SR;	/* Read TC0 Status Register to clear it */

	/* Here we increment the various ticks */
	tick_update_lcd++; /* increment LCD tick */

	/* We read voltage and current at each 5ms, we do it here */
	/* Read voltage and accumulate it to the last values. It should take no
	 * more than 35us for read a value. */
	voltage_temp = adc_read(4);
	voltage += voltage_temp;

	/* Read current and accumulate it to the last values */
	current_temp = adc_read(5);
	current += current_temp;

	/* Calculate the wattage and accumulate, using the current and
	 *  volatge values */
	wattage_temp = voltage_temp * current_temp;
	wattage += wattage_temp;

	/* Calculate, integrate, the wattage per hour.
	 *
	 * There are 17950903,5114864 Timer0 interrupt in one hour, so we should
	 * accumulate the wattage relative to each piece of time -- integrate.
	 */
	wattage_hour += (wattage_temp / 17950903,5114864);
}

void timer0_setup (void)
{
    /* Enable the Timer0 peripheral clock */
    /* pointer to PMC data structure */
    volatile AT91PS_PMC pPMC = AT91C_BASE_PMC;
    /* enable Timer0 peripheral clock */
    pPMC->PMC_PCER = (1<<AT91C_ID_TC0);

    /* Set up the AIC  registers for Timer 0 */
    /* pointer to AIC data structure */
    volatile AT91PS_AIC pAIC = AT91C_BASE_AIC;
    /* disable timer 0 interrupt in AIC Interrupt Disable Command Register */
    pAIC->AIC_IDCR = (1<<AT91C_ID_TC0);
    /* Set the TC0 IRQ handler address in AIC Source */
    pAIC->AIC_SVR[AT91C_ID_TC0] = (unsigned int) timer0_irq_handler;
    /* Set the interrupt source type and priority */
    pAIC->AIC_SMR[AT91C_ID_TC0] =  (AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL | 0x4 );
    /* Clear the TC0 interrupt in AIC Interrupt Clear Command Register */
    pAIC->AIC_ICCR = (1<<AT91C_ID_TC0);
    /* Disable timer 0 interrupt in AIC Interrupt Disable Command Reg */
    pAIC->AIC_IDCR = (0<<AT91C_ID_TC0);
    /* Enable the TC0 interrupt in AIC Interrupt Enable Command Register */
    pAIC->AIC_IECR = (1<<AT91C_ID_TC0);

    /* Create a pointer to TC Global Register structure */
    AT91PS_TCB pTCB = AT91C_BASE_TCB;
    pTCB->TCB_BCR = 0; /* SYNC trigger not used */

    pTCB->TCB_BMR = 0x15; /* external clocks not used */

    /* Create a pointer to channel 0 Register structure */
    AT91PS_TC pTC = AT91C_BASE_TC0;
    pTC->TC_CCR = 0x5; /* enable the clock and start it */

    pTC->TC_CMR = 0x4004; /* TCCLKS = 1 (TIMER_CLOCK5) */
    /* CPCTRG = 1 (RC Compare resets the counter and restarts the clock) */
    /* WAVE   = 0 (Capture mode enabled) */

/*  Timer Calculation:   What count gives 5 msec time-out?
 *
 *    TIMER_CLOCK5 = MCK / 1024  = 48054841 / 1024  =  46928 hz
 *
 *     TIMER_CLOCK5 Period = 1 / 46928  =  21.309239686 microseconds
 *
 *     A little algebra:  5 msec = count * 21.3092396896*10**-6
 *                        count =  5 / 21.3092396896*10**-3
 *                        count ~=  234
 */
    pTC->TC_RC = 234;

    pTC->TC_IER = 0x10; /* enable RC compare interrupt */
    pTC->TC_IDR = 0xEF; /* disable all except RC compare interrupt */
}

