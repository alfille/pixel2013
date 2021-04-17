# pixel2013
Google Chromebook Pixel 2013 control

By Paul H Alfille 2021
MIT license

# Summary
Simple controls for laptop backlight and keyboard lights under linux

# Design
Some of the controls are exposed by the operating system in a virtual filesystem:
> * /sys/class/backlight/xxxxx/backlight
> * /sys/class/leds/xxxxx/backlight

## Security
The controls require root access and so are setsuid programs (which is a security risk), but take no 

