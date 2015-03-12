# Introduction #

This system measures the DC current and the DC voltage, calculates the instant power (in Watts) and the total generated power in KWh.

The system should be used with an electrical generator attached to a bicycle and people should pedal to generate the energy. Images of a pedal power system (without the energy meter):

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/andancas_2008-pedal_power-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/andancas_2008-pedal_power-01.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/andancas_2008-pedal_power-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/andancas_2008-pedal_power-02.jpg)

Picture of the pedal power meter prototype:

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/pedal_power_meter-prototye-20090619-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/pedal_power_meter-prototye-20090619-01.jpg)

Video showing the working prototype [here](http://blip.tv/file/get/Jpcasainho-pedal_power_meterprototye20090619156.ogg).

More pictures are available on [SVN](http://code.google.com/p/casainho-projects/source/browse/#svn/trunk/pedal_power_meter/images).

Electrical characteristics:
  * Vin max: 18 volts;
  * Iin max: 18 amps;
  * system starts measuring at about 0,1 volts and at about 0,3 amps.

# Hardware #

For measuring the voltage, a simple voltage divisor resistor is used. The output value is linear and is about 3,3V at Vin = 20V. See the [schematic and component values on SVN](http://code.google.com/p/casainho-projects/source/browse/#svn/trunk/pedal_power_meter/schematic_board).

For measure the current, the ZXCT1009 sensor where used. The max current should be about 20A and the initial values are not linear. The first value of current is at about 0,4A.

The voltages values relative to voltage and current are read using and ADC of an ARM7 microcontroller.
I started using the AT91SAM7S256 but since I did burn the ADC inputs of that IC, I changed to a more cheap one ARM7 microcontroller (but less powerful), the LPC2103.

The values of current and voltage are used to calculate the power by the ARM7 LPC2103 and the values are sent to an alphanumeric LCD module. The alphanumeric LCD module is that cheap one that everyone uses with the HD44780 controller, of 16x2 chars.

Two buttons are used to let users interact with the system, letting them reset the cumulative value in wattage hour. They can also go to a menu where total wattage hour is shown. Also there is possible to access two on two advanced menus where voltage, current and ADC value readings are shown.

The Olimex lpc-h2103 board were used. I also made the very simple board that holds the ZXCT1009 current sensor and voltage divider (to measure the voltage). I just wired all together, plus I used 2 push buttons with pullups resistors and simple RC filters for debounce. I used four NiMh AAA batteries directly to source the LCD module plus the Olimex lpc-h2103 board.

# Firmware #

[Firmware is available on SVN](http://code.google.com/p/casainho-projects/source/browse/#svn/trunk/pedal_power_meter/firmware/lpc2103_version%3Fstate%3Dclosed).

The system reads the voltage and current at every 5ms. A Timer interrupt is used for count that every 5ms.

The instantaneous power and cumulative power in watts hour are calculated using the voltage and current values, finally that values are sent to the LCD.

Two buttons are used for advance on menus and reset the cumulative wattage hour value.

# Some pictures #
**First menu** - this shows the instantaneous power on the first line and the cumulative power in watts hour on second line. This is the first screen after power the system on. Click on button 1 to go on the second menu.

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_01.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_01.jpg)

**Second menu** - this shows the total cumulative power in watts hour on second line. Click on button 1 to go on the first menu.

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_02.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_02.jpg)

**Reset the total power in watts hour** - while on first menu, click on button 2 for at least 3 seconds for reset the value.

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_03.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_03.jpg)

**Go to advanced menus** - while on second menu, click on button 2 for at least 10 seconds for going on advanced menus.

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_04.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_04.jpg)

**First advanced menu** - shows the voltage and current.

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_06.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_06.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/pedal_power_meter-prototye-20090619-06.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/pedal_power_meter-prototye-20090619-06.jpg)

**Second advanced menu** - shows the ADC values readings.

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_05.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_05.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/pedal_power_meter-prototye-20090619-07.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/pedal_power_meter-prototye-20090619-07.jpg)

**Leaving advanced menus** - while on first advanced menu, click on button 2 for at least 10 seconds for leaving on advanced menus.

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_07.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090607-menu_07.jpg)

**The internals** - a lot of wires :-)

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090608-prototype-01-500x.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090608-prototype-01-500x.jpg) ([Click here for a high quality version](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090608-prototype-01-500x.jpg))

**Zoom on the board that holds the current sensor circuit and voltage reading circuit**

![http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090608-prototype-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/pedal_power_meter/images/20090608-prototype-02.jpg)