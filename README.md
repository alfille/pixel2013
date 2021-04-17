# pixel2013
Google Chromebook Pixel 2013 control

By Paul H Alfille 2021
MIT license

# Summary
Simple controls for laptop backlight and keyboard lights under linux

![Pixel picture](https://upload.wikimedia.org/wikipedia/commons/6/63/Chromebook_Pixel_%28WiFi%29_open.JPG)

# Project has moved
* This version works well for the 2013 Google Pixel Chromebook, but the scope has expanded to all laptops with controls exposed in /sys/class
* New name **backlighter**
* See [backlighter](http://github.com/alfille/backlighter)

# Install
* Download source `git clone http://github.com/alfille/pixel2013`
* Compile `make all`
* Install `sudo make install`
* This wil; install
 * command line tools
 * graphics tools
 * menu entry 	
* Full script:

```
git clone http://github.com/alfille/pixel2013
cd pixel2013
make all
sudo make install
```
* The following python3 modules are required (but fortunately are part of the standard distribution)
 * sys
 * signal
 * tkinter tkinter.ttk tkinter.font
 * pathlib.Path

# Usage
## command line tool
`p2013dim number` -- in range 0 (dark) to 750 (full)

```
p2013dim -- set the backlight level level for the Google Pixel Chromebook (2013)

Writes to /sys/class/backlight/intel_backlight/brightness -- needs root privileges
by Paul H Alfille 2021

	p2013dim -h -- this help
	p2013dim -f -- control File name (/sys/class/backlight/intel_backlight/brightness)
	p2013dim -c -- what is being Controlled (backlight level)
	p2013dim -g -- Current state, 3 values-> min,current,max
	p2013dim 200 -- brightness 200 (choose your value)```

```
## graphical tool



Some of the controls are exposed by the operating system in a virtual filesystem:
> * /sys/class/backlight/xxxxx/backlight
> * /sys/class/leds/xxxxx/backlight

## Security
The controls require root access and so are setsuid programs (which is a security risk), but allow very circumscribed and sanitized input.
## 

