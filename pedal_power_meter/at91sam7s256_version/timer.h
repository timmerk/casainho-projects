/* Global variables */
double voltage, current, wattage, wattage_hour;
long int tick_update_lcd;

void timer0_irq_handler (void);
void timer0_setup (void);
