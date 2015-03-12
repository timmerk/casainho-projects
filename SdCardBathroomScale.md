

# Introduction #

**2012 January**

I am now near 100kg :-( I really need to go down on that value...

I hacked a cheap bathroom scale(20€) and added to it Bluetooth communications(55€) so I can track my weight on my Android Smart Phone.

I also hacked Weight Chart Open Source software on Android and added the functionality for receiving the weight data coming from the bathroom scale, show it and finally save it.

I created a new project page for this new bathroom scale which I am calling the **SmartScale**.


---


**2010.03.17**

On 2010.03.17 I bought on local Decatlhon shop the [Beurer BG 16](http://www.beurer.com/) bathroom scale for 20€ that measures weight, percentage of fat, percentage of water and percentage of muscle.

I hope to hack this scale and do the same as I did for the others ;-)

Pictures of the scale:

![http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-02_800x-20100317.jpg](http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-02_800x-20100317.jpg)

![http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-05_800x-20100317.jpg](http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-05_800x-20100317.jpg)

![http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-07_800x-20100317.jpg](http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-07_800x-20100317.jpg)

![http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-08_800x-20100317.jpg](http://casainho-projects.googlecode.com/svn-history/r147/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16/beurer-bg_16-08_800x-20100317.jpg)

More pictures on [here](http://code.google.com/p/casainho-projects/source/browse/#svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-beurer_bg_16).



---


On this project I hacked a digital bathroom scale, for write (log) my weight variations over time, on a memory SD Card. I write the information (time date + weight) on a comma separated values (.CSV) file so I can quickly build a graph using OpenOffice, Gnuplot or some other capable program.

If anyone want to build a scale like this one, I can help, my e-mail is: casainho@gmail.com. I can also build a personalized system, please contact me for price and details. I would like to see this project grow, I would like to be able to buy on the market an Open Hardware and Open Source scale like this one - please contact me if you ave any ideas.

Here is a picture of me using the scale:

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-03.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-03.jpg)

Click on the next image to see a video that shows the scale working:

[![](http://a.images.blip.tv/Jpcasainho-sdcard_bathroom_scalefagor_bb_9020090902640.jpg)](http://blip.tv/file/get/Jpcasainho-sdcard_bathroom_scalefagor_bb_9020090902135.ogg)

Here is a picture of a graph made using OpenOffice (my own weight log):

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/weight_vs_time_graph-20090826.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/weight_vs_time_graph-20090826.jpg)

And here is a picture of a graph made using Gnuplot (my own weight log):

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/weight_graph_gnuplot-20090902.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/weight_graph_gnuplot-20090902.jpg)

Firmware source code, schematics sources, pictures of current work, Gnuplot scripts,  can be found on [SVN](http://code.google.com/p/casainho-projects/source/browse/trunk/sdcard_bathroom_scale/).

## Media coverage ##

  * [Hackaday - "Logging weight changes" on 2009.08.14](http://hackaday.com/2009/08/14/logging-weight-changes/)
  * [Hacked Gadgets - "Weight Logging Bathroom Scale" on 2009.10.08](http://hackedgadgets.com/2009/10/08/weight-logging-bathroom-scale/)

## Observations and things to improve ##
The system works perfectly. Although there are some things I would like to improve:

  * The size of the characters on LCD are very small for this application, since my eyes are far from it when I am weighting myself. Maybe I can find another LCD?

  * Me and my girlfriend, we both need to lost weight, we both use the scale. Luckily our weight values are very different and I can differ them on system and have 2 different files on SD Card to register our weights separately. I would prefer to have some way to identify each person, so more people could use the scale if needed;

### Ideas for a future version ###
I would like to have the bathroom scale sending by wireless the weight values. On a display console (running embedded GNU/linux) attached to bathroom wall, the wireless signal would be received and a graph would be shown to user with the last values of the last 2 weeks - on this way the user can have a clear picture of his weight progression.

The display console would also be able to store the time date and weight values on a memory SD Card or any other media.

The display console could also have a way to identify different users, maybe by using a biometric finger print (USB mouser with fingerprint ?).

# Technical details -- Scale Fagor BB-90 #
## The original cheap scale I bought on market ##
I bought the cheapest digital bathroom scale I could found on market, it were 20€, Fagor model BB-90. Other scales just looks the same, because they have the same number of LCD digits and the system appears to behave in the same way.

Picture:

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090703-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090703-01.jpg)

## How to get the weight value ##
First I thought that I could read the sensors and got an analog voltage relative to weight but I couldn't find a way to do it. Next a friend at work give me the idea to try read the signals that went to original LCD, and it was a simple and easy way to have what I need :-)

The original LCD have 15 pins, 3 backplanes and 12 segments. I did understand how the LCD signals works reading this [application note](http://casainho-projects.googlecode.com/svn-history/r71/trunk/sdcard_bathroom_scale/docs/lcd-an0162.pdf).

The segments signals have voltage that can be read directly by the LPC2103. The backplanes signals can't be ready directly by the LPC2103 (I think) and then I made a very simple voltage detector using a LM258 opamp so I get a "trigger" signal every time the backplane signal get near is maximum value. Since all the signals are sequential and have the same period of time, I just look for one backplane signal (just one voltage detector circuit with the LM258 opamp).

The next 2 pictures shows a backplane signal and 2 segments signals.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/osci_image-20090605-10.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/osci_image-20090605-10.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/osci_image-20090605-11.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/osci_image-20090605-11.jpg)

The next picture shows a backplane signal and a "trigger" signal I got using an LM258 opamp working as a comparator, like a signal value detector.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/osci_image-20090615-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/osci_image-20090615-01.jpg)

### Understanding the logic of each signal ###
After I saw on oscilloscope each signal that went to the original LCD, I quickly understand that 3 were backplanes and 12 were segments, because backplanes have always the same shape while the others varies with the segments on/off, with the weight value.

I had to understand which segments were turned on/off to represent each number on the original LCD, and not having the original LCD working any more, I had to make some tests to figure the information I were looking for.

I decided to write on LCD module HD44780 the state of each segment (synchronized with each backplane signal) and then try a few different known weight, so I had a known digits:

```
             0.0 kg

          backplane a:   0 0 0 . 0 0 0 . 0 1 1 . 0 1 1

          backplane b:   0 0 0 . 0 0 0 . 1 0 1 . 1 0 1

          backplane c:   0 0 0 . 1 0 0 . 0 1 1 . 1 1 1

--------------------------------------------------

             1xx.x kg

          backplane a:   0 0 1 . x x x . x x x . x x x
                                               
          backplane b:   0 0 1 . x x x . x x x . x x x

          backplane c:   0 0 0 . x x x . x x x . x x x

--------------------------------------------------

             2x.x kg

          backplane a:   0 0 0 . 0 1 1 . x x x . x x x

          backplane b:   0 0 0 . 0 1 0 . x x x . x x x

          backplane c:   0 0 0 . 1 1 1 . x x x . x x x

--------------------------------------------------

             6x.x kg

          backplane a:   0 0 0 . 0 1 0 . x x x . x x x

          backplane b:   0 0 0 . 1 1 1 . x x x . x x x

          backplane c:   0 0 0 . 1 1 1 . x x x . x x x
```

After reading about [7 segments displays on wikipedia](http://en.wikipedia.org/wiki/Seven-segment_display), turned out in my head that the segments are:

```
               a          y a b   <-- backplane a
             f   b        f g c   <-- backplane b
               g          z e d   <-- backplane c
             e   c
               d
```

Example of number 6, all segments turned on except segment b.:

```
             6x.x kg

          backplane a:   0 0 0 . 0 1 0 . x x x . x x x

          backplane b:   0 0 0 . 1 1 1 . x x x . x x x

          backplane c:   0 0 0 . 1 1 1 . x x x . x x x
                  
               a          y a b   <-- backplane a
             f   b        f g c   <-- backplane b
               g          z e d   <-- backplane c
             e   c
               d
```

### Schematic ###
![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-original_lcd.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-original_lcd.jpg)

## Selection of microcontroller ##
Arduino/Atmel AVR, or ARM? - I really like Arduino, mainly because it's Open Hardware/Firmware and there is a lot of Open Hardware modules for it. I prefer to use ARM instead of Arduino/AVR because I have the same Free Software tools PLUS cheap, Open JTAG debugger! I don't really like the fact that Atmel have a closed, proprietary, debugger.

I am being using ARM7 LPC2103 which is the cheaper on this times and have all the functionalities and working power that I need. I decided to use Olimex dev. board [LPC-H2103](http://www.olimex.com/dev/lpc-h2103.html).

## LCD module added ##
I needed to use another LCD since I couldn't maintain the original one. I decided to try the cheap ones based on [HD44780](http://en.wikipedia.org/wiki/HD44780_Character_LCD), since I have experience with them and I got some with me. Luckily, this LCD just enters perfect in the place of the original :-)

On the next picture we can see the LCD module and also the connections I made to original PCB using flat cable, on the pads that connected to original LCD.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090703-08.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090703-08.jpg)

### Schematic ###
![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-lcd_module.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-lcd_module.jpg)

## SD Card and FAT library ##
I decide to use SD Card memory to hold the data because I had good experiences in past with this kind of memory card, using SPI BUS. Also I can find relative cheap cards easily.

My reference page about SD Cards is this one: [How to Use MMC/SDC by ChaN](http://elm-chan.org/docs/mmc/mmc_e.html).

### Schematic ###
![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-sd_card.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-sd_card.jpg)

### Fat file system library ###
I use [FatFs by ChaN](http://elm-chan.org/fsw/ff/00index_e.html) file system drivers which have a Free Software license, are very complete and have good documentation.
### Data written to SD Card ###
Here is some real data recorded on SD Card "weight.csv" file:
```
12-8-2009 23:48:28,"092,1"
12-8-2009 23:48:55,"092,3"
12-8-2009 23:57:46,"092,4"
12-8-2009 23:58:14,"092,0"
12-8-2009 23:58:40,"092,0"
12-8-2009 23:59:05,"092,0"
12-8-2009 23:59:44,"094,0"
13-8-2009 07:15:57,"091,5"
13-8-2009 07:36:54,"091,5"
13-8-2009 07:37:44,"091,5"
13-8-2009 20:15:02,"092,0"
13-8-2009 20:15:28,"091,9"
13-8-2009 21:22:53,"091,6"
```

## Real Time Clock ##
Since I want to also register the time date, I need to have a Real Time Clock(RTC). LPC2103 have one RTC and the board I am using, have the RTC working.

Since I need to setup the clock with correct time date and I do not want to add buttons to the system just for doing it. I implemented the following idea: Every time that system boots, if on root of SD Card there is a file called "time.txt", read the time data from it and setup the clock; finally, delete the file.

The time.txt file should have a string with the following format (without square brackets):
```
[year][month][month day][week day][hour][minutes][seconds]
Example: [2009][08][01][6][12][00][00]; string "200908016120000".
```

I am using 2 X AAA NiMh low discharge batteries to power the RTC, I hope it lasts at least 1 year.

### Schematic ###
![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-power_rtc.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-power_rtc.jpg)

## Power down the system ##
After finish the prototype, I verified that the LPC2103 board + LCD module HD44780 were using about 140mA.

I worked to found a way to disable the circuit when the original scale circuits are not working. I verified that when original scale is off, there is no signals to the original LCD. I ended up by using a mosfet that is turned on when there a signal on the backplane 1 line.

I also control that mosfet with a signal from the LPC2103, so the system can keep with power turned on and shut off himself when desired.

### Schematic ###
![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-power.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090817-power.jpg)

On the next image, we can see the signals before and after D1 BAS85. Yellow line is at point LCD\_pin13 and blue at gate of Q1 BSS138.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090818-power_module_oscilloscope_image.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/20090818-power_module_oscilloscope_image.jpg)

## Pictures taken on 2009.09.02 ##
![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-01.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-03.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-03.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-fagor_bb_90/sdcard_bathroom_scale-20090902-02.jpg)

# Technical details -- Scale Jata Hogar 490 #

I bought another bathroom scale. The model is "Jata Hogar 490", looks like it is from a [Spanish company](http://www.jata.es/).

## Status ##

Working correctly as on 2009.10.05. Firmware Open Source code is on [SVN](http://code.google.com/p/casainho-projects/source/browse/).

## Some pictures from original scale ##

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-01.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-02.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-03.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-03.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-04.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-04.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-06.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-06.jpg)

## Technical explanation of the hack ##
I will just document the differences from the other [first bathroom scale I did hack](http://code.google.com/p/casainho-projects/wiki/SdCardBathroomScale), all the rest is equal.

I am using the ADC on LPC2103 for be able to read and sync with the LCD signals. Since the LPC2103 don't have 13 ADC channels, I used an external analog multiplexer of 16 channels, the 74HC4067 IC.

There is 13 pins that connects on the original LCD. There is 4 backplanes signals, which are the pins 10, 11, 12 and 13. Each other pins holds 4 bits.

Pin 1 holds bit data for kg and lb symbols. Pin 2 and 3 holds bit data for most significant digit of weight value. Pin 8 and 9 holds bit data for least significant (decimal) digit of weight value.

## Oscilloscope images from the pins that connects to original LCD ##

Each one of the following 13 images, shows the signal at each pin, when the scale starts and shows 0.0 kg on LCD. First image shows the signal at line 1 and last image shows the signal at line 13.

The blue line is a signal I used to trigger the oscilloscope. I got that trigger signal as a reference for the first backplane signal (line 10).

Here is the sequence of bits on pin signals and the correspondence to the segments on the LCD:
```
Pin 1 of 2: degf
Pin 2 of 2: xcba

             a
           f   b
             g
           e   c
             d   x

Examples:
                  degfxcba
Number 0: 11010111
Number 9: 10110111
Number 6: 11110101
Number 2: 11100011
Number 1: 00000110
```

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-01.jpg)
1st line: 4th bit is on - this is the bit that turns on the "kg" segment.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-02.jpg)
2nd line: 1st, 2nd and 3rd bits are on, for the "cba" segments of "0" number. 4th bit would be the "." bit that is never turned on.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-03.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-03.jpg)
3rd line: here just the "g" segment is turned off from the "degf" segments of "0" number.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-04.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-04.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-05.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-05.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-06.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-06.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-07.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-07.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-08.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-08.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-09.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-09.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-10.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-10.jpg)
10th line: Backplane 1 signal.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-11.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-11.jpg)
11th line: Backplane 2 signal.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-12.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-12.jpg)
12th line: Backplane 3 signal.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-13.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-oscilloscope-20091005-13.jpg)
13th line: Backplane 4 signal.

## Final pictures ##

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-01.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-01.jpg))

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-02.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-02.jpg))

Now all the electronics inside a black plastic box and glued to the scale:

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-inside-20091009-800x.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-inside-20091009-800x.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-inside-20091009.jpg))

The next pictures were taken at the anniversary of my girlfriend. I did offer as a gift this scale to her, since he wanted to register his weight variations over time because he is pregnant and do not want to get fat.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-01-800x.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-01-800x.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-01.jpg))

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-02-800x.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-02-800x.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-02.jpg))

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-03-800x.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-03-800x.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-girlfriend_gift-20091009-03.jpg))