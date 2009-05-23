/* Values I did measure with an ampmeter:
 *  ADC value   | current (Amps)
 *  ----------------------------
 *  14          | 0,2756
 *  32          | 0,5585
 *  41          | 0,7517
 *  60          | 1,0934
 *  76          | 1,3535
 *  ----------------------------
 * (current / ADC value) ~= 0.01830 ==> K_CURRENT
 */

#define K_CURRENT 0.01830



#define K_VOLTAGE 0.035965432098765432098765432099


#define MENU_SHOW_POWER 0
#define MENU_SHOW_VOLTAGE_CURRENT 1
#define MENU_SHOW_DEBUG 99



