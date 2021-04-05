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
    import subprocess
except:
    print( "Cannot load subprocess module, which should be part of the python standard distribution\n" )
    raise

def signal_handler(signal, frame):
    sys.exit(0)

mainwindow = None

class tab:
    tabcontrol = None
    
    def __init__( self, progname ):
        self.progname = progname

        # Notebook if doesn't exist
        if type(self).tabcontrol is None :
            global mainwindow
            type(self).tabcontrol = ttk.Notebook( mainwindow )

        # This Tab
        self.controlname() # Get name
        self.tab = ttk.Frame( type(self).tabcontrol )
        type(self).tabcontrol.add(self.tab, text = self.name )
        type(self).tabcontrol.pack( expand=1, fill="both" )

        # Scale (slider)
        self.controlrange() # get min, current and max
        self.scale = tk.Scale( self.tab, from_=self.min, to=self.max, orient="horizontal", command=self.setlevel, resolution=(self.max-self.min)/50, bd=5, width=20, showvalue=0 )
        self.scale.set(self.start)
        self.scale.pack( expand=1, fill="both", padx=5, pady=5 )

    def setlevel( self, val ):
        try:
            r = subprocess.run([self.progname, int(val)], check = True )
        except:
            messagebox.showerror(message="Cannot run program {}".format(self.progname))
            raise
        
    def controlname( self ):
        try:
            r = subprocess.run([self.progname, '-c'], capture_output = True, text = True, check = True )
        except:
            messagebox.showerror(message="Cannot run program {}".format(self.progname))
            raise
        self.name = r.stdout.strip(" \n\t")
        
    def controlrange( self ):
        try:
            r = subprocess.run([self.progname, '-g'], capture_output = True, text = True, check = True )
        except:
            messagebox.showerror(message="Cannot run program {}".format(self.progname))
            raise
        self.min, self.start, self.max = [int(x) for x in r.stdout.strip(" \n\t").split(",")]        

def main(args):
    global mainwindow
    
    # keyboard interrupt
    signal.signal(signal.SIGINT, signal_handler)

    mainwindow = tk.Tk()
    mainwindow.title("Google Pixel 2013")
    tab("p2013dim")
    messagebox.showerror()
#    tab("keylights")
    mainwindow.mainloop()

if __name__ == "__main__":
    # execute only if run as a script
    sys.exit(main(sys.argv))
