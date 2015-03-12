

# Introduction #

**Smart Scale** is a cheap ($75) and Open Source bathroom scale with wireless Bluetooth communications. It works just like a usual bathroom scale, where the user can use it and read the weight value on the LCD or the weight value is received automatically on user Android Smart Phone (which is sent by the scale wireless).

**[Smart Weight Chart](http://code.google.com/p/casainho-projects/wiki/SmartWeightChart)** is the Android software that receives the weight value from the scale and shows it in a graph. **[Smart Weight Chart](http://code.google.com/p/casainho-projects/wiki/SmartWeightChart)** is Free and Open Source software and is available [here on Android Market](https://market.android.com/details?id=net.casainho.smartweightchart).

In future I would like continue developing and building a fully (as possible) Open Source bathroom scale. I would prefer to do it in group with other developers and/or users - if you are motivated, contact me on the **[discussion group](http://groups.google.com/group/smart_scale_weight_chart)** (preferable) or by e-mail: casainho@gmail.com

## Some pictures ##

Showing the graph of my weight variation over time on the [Smart Weight Chart](http://code.google.com/p/casainho-projects/wiki/SmartWeightChart) Android software:

![https://github.com/casainho/Smart-Scale/raw/master/pictures/android_app-09.resized.png](https://github.com/casainho/Smart-Scale/raw/master/pictures/android_app-09.resized.png)

A picture of my little son using the scale:

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-06.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-06.redimensionado.jpg)

The enclosure and inside the DIY circuit I did:

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-04.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-04.redimensionado.jpg)

## Costs ##

All were done quick and with cheap price on mind. Total cost in materials were only about $75.

Material list and costs:

  * digital bathroom scale: $20
  * [ARM LPC2103 microcontroller board: $15.6](http://www.wayengineer.com/index.php?main_page=product_info&products_id=129)
  * [Bluetooth serial module: $6.6](http://www.dealextreme.com/p/wireless-bluetooth-rs232-ttl-transceiver-module-80711)
  * 16x2 LCD: $15
  * batteries and support: $5
  * various, like wires, etc: $12.5

## History ##

I started to hack my bathroom scale on Jun 2009 and on that time I added to it a SDCard and a Real Time Clock. The scale always logged my weight and the data/time on a CSV file on SDCard, later on my PC I could draw a graph using Open Office or Gnu Plot. Please see [SdCardBathroomScale](http://code.google.com/p/casainho-projects/wiki/SdCardBathroomScale) project page were all this begun.

## Future ##

In future I would like to develop and build a fully (as possible) Open Source bathroom scale. I would prefer to do it in group with other developers and/or users - contact me if you are motivated to participate: casainho@gmail.com

[Sparkfun is selling load cells used on bathroom scales and there is a lot of information on how to make the scale on the comments](http://www.sparkfun.com/products/10245).

## Open Source: the sources ##

I am sharing  the firmware, software and pictures on my github account for this project: https://github.com/casainho/Smart-Scale

Please note that I re-used most of the hardware and firmware from my initial [Fagor BB-90 SdCardBathroomScale](http://code.google.com/p/casainho-projects/wiki/SdCardBathroomScale).

# News / Tecnhical info / Archive #

**2012 February**

This project were featured on Hack a Day: [a dumb scale to your smartphone](http://hackaday.com/2012/02/13/connecting-a-dumb-scale-to-your-smartphone/|Connecting).

**2012 January**

I am now near 100kg :-( I really need to go down on that value...

On this days I use my Android Smartphone a lot and I always wanted to have the weight data on the Android instead on the SDCard on the scale.

I went to the market and found "wifi" scales for about 150€. Since I will probably need to use the scale all over my life, I prefer to build my own OpenSource scale instead of buying and stay limited with a proprietary one.

I have now experience with Android and cheap ($6) Bluetooth serial modules and I found two OpenSource softwares for Android for logging user's weight: [Weight Chart](http://code.google.com/p/weight-chart/) and [Droid Weight](http://code.google.com/p/droidweight/).

I decided to change/upgrade my Fagor BB-90 bathroom scale, by removing the SDCard and the batteries for the Real Time Clock (RTC). I added a cheap ($6.6) Bluetooth serial module to send the weight value data to my Android Smart Phone. I also added a 5V voltage regulator since I am now using only two Lithium batteries instead of the "old" four NiMh batteries.

Here some pictures (high resolution [here](https://github.com/casainho/Smart-Scale/tree/master/pictures)):

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-01.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-01.redimensionado.jpg)

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-02.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-02.redimensionado.jpg)

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-05.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-05.redimensionado.jpg)

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-03.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-03.redimensionado.jpg)

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-04.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-04.redimensionado.jpg)

And a picture of my little son using the scale :-)

![https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-06.redimensionado.jpg](https://github.com/casainho/Smart-Scale/raw/master/pictures/smart_scale-06.redimensionado.jpg)

Material list and costs:

  * digital bathroom scale: $20
  * ARM LPC2103 microcontroller board: $15.6
  * Bluetooth serial module: $6.6
  * 16x2 LCD: $15
  * batteries and support: $5
  * various, like wires, etc: $12.5

TOTAL: ~$75.

Later I hacked the [Weight Chart](http://code.google.com/p/weight-chart/) software on Android and added the functionality for receiving the weight data coming from the scale, show it and finally save it.

**I am sharing  the firmware, software and pictures on my github account: https://github.com/casainho/Smart-Scale**

I also found a [blog message of a hacker that decided as me, to use a Bluetooth module and an Android](http://www.keyboardmods.com/2010/05/bluetooth-wireless-bathroom-scale-with.html). The big difference is that he only uses the original load cells, then he uses and ADC to read them and almost the same hardware as me.

Also Sparkfun is selling the load cells used on bathroom scales and there is a lot of information on how to make the scale on the comments: http://www.sparkfun.com/products/10245

Maybe soon we will be able to buy on the market the load cells, make our electronic board and use a square piece of wood, then we will have our own fully OpenSource bathroom scale :-)