#!/usr/bin/env python3
#
# Program to configure (graphically) Google Chromebook Pixel 2013 backlight and key lighting
#  found at http://github.com/alfille/pixel2013
#  Note that setuid programs p2013dim must be installd=ed to make the actual changes 
#
# 2021 Paul H Alffille

try:
    import tkinter as tk
    from tkinter import ttk
    from tkinter import messagebox
except:
    print( "Cannot load TKinter (graphics) module, which should be part of the python standard distribution\n" )
    raise

try:
    import sys
except:
    print( "Cannot load sys module, which should be part of the python standard distribution\n" )
    raise

try:
    import signal
except:
    print( "Cannot load signal module, which should be part of the python standard distribution\n" )
    raise

try:
    from pathlib import Path
except:
    print( "Cannot load pathlib/Path module, which should be part of the python standard distribution\n" )
    raise

def signal_handler(signal, frame):
    sys.exit(0)

mainwindow = None

class device:
    
    basedir = "/sys/class/"
    
    def __init__( self, devdir ):
        self.syspath = Path( type(self).basedir ) . joinpath( devdir )
        self.choices = [ d for d in self.syspath.iterdir() if d.is_dir() and d.joinpath('brightness').exists() and d.joinpath('max_brightness').exists() ]
        self.choice = None
        self.default()

    def default( self ):
        if self.choices == []:
            # ERROR no choices
            self.choice = None
            return
        for d in self.choices:
            t = d.joinpath('type')
            if t.exists() and t.read_text().strip('\n') =='raw' :
                self.control = d.stem
                return
        self.control = d[0]

    @property
    def max( self ):
        if self.choice is None:
            return 1
        return self._max

    @property
    def brightness( self ):
        if self.choice is None:
            return 1
        return int( self.bright.read_text().strip('\n') )
    
    @brightness.setter
    def brightness( self, b ):
        if self.choice is not None:
            self.bright.write_text( "{}\n".format(str(b)) ) 
            print( "{}\n".format(str(b)) ) 

    @property
    def control( self ):
        if self.choice is None:
            return None
        return self.choice.stem

    @control.setter
    def control( self, stem ):
        if stem not in [ d.stem for d in self.choices ]:
            # ERROR bad choice, set to default
            return self.default()
        self.choice = Path( self.syspath ) . joinpath( stem )
        self._max = int( self.choice.joinpath('max_brightness').read_text().strip('\n') )
        self.bright = self.choice.joinpath('brightness')

class tab:
    tabcontrol = None
    
    def __init__( self, devdir, devname ):
        self.title = devname

        # Notebook if doesn't exist
        if type(self).tabcontrol is None :
            global mainwindow
            type(self).tabcontrol = ttk.Notebook( mainwindow )

        # This Tab
        self.device = device( devdir ) # Set device directory
        print( self.device )
        self.tab = ttk.Frame( type(self).tabcontrol )
        type(self).tabcontrol.add(self.tab, text = self.title )
        type(self).tabcontrol.pack( expand=1, fill="both" )

        # Test Control validity
        if self.device.control is None:
            self.bad = ttk.Label( self.tab, text = "{} control not found at {}".format(devname, devdir) )
            self.bar.pack( expand = 1, fill="both", padx=10, pady=10 )
            return

        # Scale (slider)
        # possibly get settings from init file
        self.scale = tk.Scale( self.tab, from_=0, to=self.device.max, orient="horizontal", resolution=self.device.max/50., bd=5, width=20, showvalue=0 )
        self.scale.set(self.device.brightness)
        self.scale.config(command=self.setlevel )
        self.scale.pack( expand=1, fill="both", padx=5, pady=5 )

    def setlevel( self, val ):
        self.device.brightness = val
        
def main(args):
    global mainwindow
    
    # keyboard interrupt
    signal.signal(signal.SIGINT, signal_handler)

    mainwindow = tk.Tk()
    mainwindow.title("Google Pixel 2013")
    tab("backlight","Backlight")
#    tab("keylights")
    mainwindow.mainloop()

if __name__ == "__main__":
    # execute only if run as a script
    sys.exit(main(sys.argv))
