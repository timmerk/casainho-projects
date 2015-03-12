# Introduction #

I bought another bathroom scale. The model is "Jata Hogar 490", looks like it is from a [Spanish company](http://www.jata.es/).

# Status #

Working correctly as on 2009.10.05. Firmware Open Source code is on [SVN](http://code.google.com/p/casainho-projects/source/browse/).

# Some pictures from original scale #

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-01.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-02.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-03.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-03.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-04.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-04.jpg)

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-06.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20090902-06.jpg)

# Technical explanation of the hack #
I will just document the differences from the other [first bathroom scale I did hack](http://code.google.com/p/casainho-projects/wiki/SdCardBathroomScale), all the rest is equal.

I am using the ADC on LPC2103 for be able to read and sync with the LCD signals. Since the LPC2103 don't have 13 ADC channels, I used an external analog multiplexer of 16 channels, the 74HC4067 IC.

There is 13 pins that connects on the original LCD. There is 4 backplanes signals, which are the pins 10, 11, 12 and 13. Each other pins holds 4 bits.

Pin 1 holds bit data for kg and lb symbols. Pin 2 and 3 holds bit data for most significant digit of weight value. Pin 8 and 9 holds bit data for least significant (decimal) digit of weight value.

# Oscilloscope images from the pins that connects to original LCD #

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

# Final pictures #

On the next pictures, all the system is working. I will just need to cut the board and put it with all other parts inside a box that will be glued to the wood plate of the scale.

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-01.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-01.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-01.jpg))

![http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-02.jpg](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-800x-02.jpg) ([high resolution version](http://casainho-projects.googlecode.com/svn/trunk/sdcard_bathroom_scale/images/bathroom_scale-jata_hogar_490/jata_hogar_490-20091005-02.jpg))