# Introduction #

I started to build my own 3D printer on November 2009. My 3D printer is based on [RepRap project](http://www.reprap.org/).

# Details #

Since I already own a CNC ([Zenbot Mini CNC Router](http://www.zenbotcnc.com/)), I decided to use it and add the [Thermoplastic Extruder](http://reprap.org/bin/view/Main/ThermoplastExtruder_2_0).

I use EMC2 on Linux Ubuntu to control my CNC and I need to use a set of scripts to let EMC2 "control" the Thermoplastic Extruder.
I am sharing all the files I use [here on SVN repository](http://code.google.com/p/casainho-projects/source/browse/#svn/trunk/emcrepstrap).

The original files are from [Sam Wong](http://www.hellosam.net/) and I got a lot of help from him to get my files working :-)

There is an [wiki page at RepRap site for this EMCRepStrap project](http://objects.reprap.org/wiki/Builders/EMCRepStrap).

Here [my blog dedicated to this project](http://casainho-emcrepstrap.blogspot.com/).

## My setup ##

I am using my Zenbot CNC machine, controlled by EMC2 on GNU/Linux Ubuntu.

I did build my [Thermoplastic Extruder](http://reprap.org/bin/view/Main/ThermoplastExtruder_2_0) and used the [Extruder Controller V2.2 board](http://dev.www.reprap.org/bin/view/Main/Extruder_Controller_2_2).

Here some pictures of it:

![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-01_small-20091228.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-01-20091228.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-02_small-20091228.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-02-20091228.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-03_small-20091228.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-03-20091228.jpg)

# Example of a usable object #
I needed to have video camera support for my bicycle. I start by taking physical measures and design the object in 3D, using [Blender](http://www.blender.org/):

![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/camera_holder_to_bicycle-00_small-20091228.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/camera_holder_to_bicycle-00-20091228.jpg)

After I just put the 3D file to print and get this while in the process:

![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/printing-01_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/printing-01-20091230.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/printing-02_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/printing-02-20091230.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/printing-03_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/printing-03-20091230.jpg)

Here is [a small video showing the printing process](http://blip.tv/file/get/Jpcasainho-reprap_3d_printer2009465.ogg).

And here the EMC2 GUI:

![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-04_small-20091228.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/zenbot_as_emcrepstrap-04-20091228.png)

And here the final piece:

![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-01_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-01-20091230.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-02_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-02-20091230.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-03_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-03-20091230.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-04_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-04-20091230.jpg) ![![](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-05_small-20091230.jpg)](http://casainho-projects.googlecode.com/svn/trunk/emcrepstrap/images/object_printed-05-20091230.jpg)

I [shared the 3D files for this piece on Thingiverse](http://www.thingiverse.com/thing:1501).