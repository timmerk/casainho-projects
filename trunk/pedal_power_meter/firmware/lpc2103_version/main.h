/*
 * Pedal Power Meter
 *
 * Copyright (C) Jorge Pinto aka Casainho, 2009.
 *
 *   casainho [at] gmail [dot] com
 *     www.casainho.net
 *
 * Released under the GPL Licence, Version 3
 */

/* Values I did measure with a voltmeter:
 *  ADC value   | voltage (Volts)
 *  ----------------------------
 *  1           | 0,09
 *  2           | 0,11
 *  3           | 0,13
 *  4           | 0,15
 *  5           | 0,17
 *  6           | 0,2
 *  7           | 0,22
 *  8           | 0,24
 *  9           | 0,25
 *  10          | 0,28
 *  68          | 1,46
 *  163         | 3,39
 *  309         | 6,38
 *  611         | 12,52
 *  823         | 16,84
 *  939         | 19,2
 *  ----------------------------
 */

/* y = K_VOLTAGE * Vin + M_VOLTAGE */
#define K_VOLTAGE 0.0204
#define M_VOLTAGE 0.06


/* Values I did measure with a ampmeter:
 *  ADC value   | current (Amps)
 *  ----------------------------
 *  1           | 0,3493
 *  3           | 0,3546
 *  6           | 0,3669
 *  9           | 0,3771
 *  11          | 0,3806
 *  16          | 0,4090
 *  20          | 0,4566
 *  27          | 0,5663
 *  32          | 0,6664
 *  46          | 0,8958
 *  60          | 1,1634
 *  75          | 1,4222
 *  87          | 1,6373
 *  111         | 2,1140
 *  134         | 2,5472
 *  156         | 2,9766
 *  183         | 3,4879
 *  225         | 4,3352
 *  282         | 5,4543
 *  315         | 6,1240
 */

/* On the first 60 ADC values, the system is very non linear. For the first 60
 * values, the function is this one:
 *                             y = -0.000004*x³ + 0.0005*x² - 0.0028*x + 0.3578
 *
 * After the first 60 values, the system is near linear and the function is this
 * one: y = 0.0192*x + 0.0245
 */

/* y = K_CURRENT * Iin + M_CURRENT */
#define K_CURRENT 0.01865
#define M_CURRENT 0.024


/* Timer1 interrupt happens at 0,005 seconds. One hour have
 * 720000 wattage measures and increments. The dt for
 * integration is: 1/720000 ~= 0,000001388888888888888888888889.
 */
#define WATTAGE_HOUR_DT 0.000001388888888888888888888889


#define MENU_SHOW_USER_POWER 0
#define MENU_SHOW_SYSTEM_POWER 1
#define MENU_SHOW_VOLTAGE_CURRENT 2
#define MENU_SHOW_ADC_READINGS 3
