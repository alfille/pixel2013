// p2013dim
// Pixel 2013 backlight command
// Paul Alfille 2021
// github.com/alfille/pixel2013

// MIT license

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ControlFile "/sys/class/backlight/intel_backlight/brightness"
#define ControlItem "backlight brightness"

void help( char * prog )
{
    fprintf( stderr, "%s -- set the %s level for the Google Pixel Chromebook (2013)\n" , prog , ControlItem ) ;
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
    int c ;
    while ( (c = getopt( argc, argv, "hfc" )) != -1 ) {
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
    }

    if ( optind != argc-1 ) {
	help(argv[0] ) ;
	fprintf( stderr, "\nNeeds a single numeric argument\n");
	exit(1) ;
    }

    char * endptr ;
    long bright = strtol( argv[optind], &endptr, 10 ) ;
    if ( argv[optind] == endptr ) {
	help(argv[0] ) ;
	fprintf( stderr, "\nInvalid numeric argument: %s\n", argv[optind] );
	exit(1) ;
    }
    
    FILE * sys = fopen( ControlFile, "a" ) ;
    if ( sys == NULL ) {
	perror( "Cannot open "ControlFile ) ;
	exit(1) ;
    }
    if ( fprintf( sys, "%ld\n", bright ) < 1 ) {
	perror("Trouble writing to "ControlFile ) ;
    }
    fclose( sys ) ;
    return 0 ;
}
