/* Global variables */
volatile double voltage, current, wattage, wattage_hour;
long int tick_update_lcd;

/* Constante value to multiply the ADC value of voltage */
#define k_voltage       0.049642857

/* Constante value to multiply the ADC value of current */
#define k_current       0.01953125
