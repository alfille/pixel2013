// p2013dim
// Pixel 2013 backlight command
// Paul Alfille 2021
// github.com/alfille/pixel2013

// MIT license

#include <stdlib.h>
#include <getopts.h>

#define ControlFile "/system/class/backlight/intel_backlight/brightness"
#define ControlItem "backlight brightness"

void help( char * prog )
{
	fprintf( stderr, "%s -- set the %s level for the Google Pixel Chromebook (2013)\n" , prog , CoontrolItem ) ;
	fprintf( stderr, "\n") ;
	fprintf( stderr, "Writes to %s -- needs root privileges\n", ControlFile ) ;
	fprintf( stderr, "by Paul H Alfille 2021\n") ;
	fprintf( stderr, "\n") ;
	fprintf( stderr, "\t%s -h -- this help\n", prog ) ;
	fprintf( stderr, "\t%s -f -- control File name (%s)\n", prog, ControlFile ) ;
	fprintf( stderr, "\t%s -c -- what is being Controlled (%s)\n", prog, ControlItem ) ;
	fprintf( stderr, "\t%s 200 -- brightness 200 (choose your value)\n", prog ) ;
}

int main( int argc, char **argv )
{
    // Arguments
    int c;
    while ( (c = getopt( argc, argv, "hf" )) != -1 ) {
        switch ( c ) {
        case 'h':
            help(argv[0]) ;
            exit(0) ;
		case 'f':
            printf("%s\n", ControlFile );
            exit(0) ;
		case 'c':
            printf("%s\n", ControlItem );
            exit(0) ;
        default:
			break ;
    }
    if ( optind >= argc ) {
		help(argv[0] ;
		fprintf( stderr, "\nNeeds a numeric argument\n");
		exit(1) ;
	}
}
