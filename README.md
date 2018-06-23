# taco-monitor


Helpful info:
http://www.instructables.com/id/OBD-Pi/
https://lifehacker.com/everything-you-need-to-set-up-bluetooth-on-the-raspberr-1768482065


Depends:

WiringPi:
http://wiringpi.com/

I2C:
http://www.raspberry-projects.com/pi/programming-in-c/i2c/using-the-i2c-interface
sudo apt-get install i2c-tools

Python 3 Dev:
sudo apt-get install python3-dev

pyODB:
sudo apt-get install pyobd

Bluetooth:
sudo apt-get install pi-bluetooth

For 'serial' library
sudo apt install catkin



Setup pcf8523 RTC:
https://learn.adafruit.com/adding-a-real-time-clock-to-raspberry-pi/set-up-and-test-i2c

Set timezone:
sudo cp /usr/share/zoneinfo/US/Pacific /etc/localtime
