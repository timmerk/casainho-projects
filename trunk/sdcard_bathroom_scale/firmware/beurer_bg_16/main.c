#include "LPC17xx.h"

extern uint32_t SystemCoreClock;

volatile unsigned long ticks; /* counts 100us ticks */


/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
  ticks++; /* increment counter necessary in ticks() */
}

/*------------------------------------------------------------------------------
  Returns number of ticks
 *------------------------------------------------------------------------------*/
unsigned long read_ticks (void)
{
    return ticks;
}

/*------------------------------------------------------------------------------
  Make a delay of number of ticks
 *------------------------------------------------------------------------------*/
void delay_ticks (unsigned long ticks)
{
    unsigned long initial_ticks = read_ticks();

    while (read_ticks() < (initial_ticks + ticks));
}


/*------------------------------------------------------------------------------
  configer LED pins
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Config(void) {
  // use USB_Connect pin which already has an LED - P1.18
  PINCON->PINSEL4 = ((0 << 20) | (0 << 19)); // set pin P1.18 as GPIO Pin (0b00)
  GPIO1->FIODIR = (1 << 20); // set pin P1.18 as output (Output = 1, Input = 0)
}

/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_On () {
  // set pin P1.18 to HIGH
  GPIO1->FIOPIN |=  (1 << 20);                  /* Turn On  LED */
}

/*------------------------------------------------------------------------------
  Switch off LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Off () {
  // clear pin P1.18 to LOW
  GPIO1->FIOPIN &= ~(1 << 20);                  /* Turn Off LED */
}


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {

  if (SysTick_Config(SystemCoreClock / 10000))
  { /* Setup SysTick Timer for 100 usec interrupts  */
    while (1);  /* Capture error */
  }

  LED_Config();                             

  while (1)
  {
    LED_On();            /* Turn on the LED. */
    delay_ticks (10000); /* delay  100 Msec */
    LED_Off();           /* Turn off the LED. */
    delay_ticks (10000); /* delay  100 Msec */
  }

}
