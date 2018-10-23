# taco-monitor

A simple C++ app for Raspberry Pi Zero W that monitors and displays engine and environmental stats for my 2004 Tacoma.

6-character micro dot LED displays readings and allows cycling through a menu.  The app checks critical metrics and flashes the screen with audible alerts if something is out or range (coolant temp, batery voltage.)

Also has an RTC (since my Tacoma doesn't have a clock!), and uses an ambient light sensor to intelligently dim the display at night.

ECU comms is done via Bluetooth SPP with a [Chinese ELM327 knock-off](https://www.amazon.com/gp/product/B009NPAORC/ref=oh_aui_search_detailpage?ie=UTF8&psc=1).




**Depends:**

WiringPi:
http://wiringpi.com/

I2C:
http://www.raspberry-projects.com/pi/programming-in-c/i2c/using-the-i2c-interface
sudo apt-get install i2c-tools

Python 3 Dev:
sudo apt-get install python3-dev

Bluetooth:
sudo apt-get install pi-bluetooth

Button shim:
sudo apt-get install python3-buttonshim
sudo pip install evdev


**Random notes:**

For 'serial' library
sudo apt-get install catkin

Python interop:
sudo apt-get install libboost-tools-dev libboost-python-dev

Setup pcf8523 RTC:
https://learn.adafruit.com/adding-a-real-time-clock-to-raspberry-pi/set-up-and-test-i2c

Set timezone:
sudo cp /usr/share/zoneinfo/US/Pacific /etc/localtime

APA102 (button thim light, unused):
https://github.com/DirkWillem/libapa102
https://github.com/cyborg00222/APA102-Raspberry-Pi
Info: https://cpldcpu.wordpress.com/2014/08/27/apa102/
