// p2013dim
// Pixel 2013 backlight command
// Paul Alfille 2021
// github.com/alfille/pixel2013

// MIT license

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ControlDir "/sys/class/backlight/intel_backlight/"
#define ControlMin 0
#define ControlCur "brightness"
#define ControlMax "max_brightness"
#define ControlItem "backlight level"

char * progname = "program" ; // should be redirected

void help( void )
{
    fprintf( stderr, "%s -- set the %s level for the Google Pixel Chromebook (2013)\n" , progname , ControlItem ) ;
    fprintf( stderr, "\n") ;
    fprintf( stderr, "Writes to %s -- needs root privileges\n", ControlDir ControlCur ) ;
    fprintf( stderr, "by Paul H Alfille 2021\n") ;
    fprintf( stderr, "\n") ;
    fprintf( stderr, "\t%s -h -- this help\n", progname ) ;
    fprintf( stderr, "\t%s -f -- control File name (%s)\n", progname, ControlDir ControlCur ) ;
    fprintf( stderr, "\t%s -c -- what is being Controlled (%s)\n", progname, ControlItem ) ;
    fprintf( stderr, "\t%s -g -- Current state, 3 values-> min,current,max\n", progname ) ;
    fprintf( stderr, "\t%s 200 -- brightness 200 (choose your value)\n", progname ) ;
}

FILE * file_open( char * name, char * mode )
{
    FILE * f = fopen( name, mode ) ;
    if ( f == NULL ) {
	fprintf( stderr, "Cannot open %s: ", name ) ;
	perror( NULL ) ;
	exit(1) ;
    }
    return f ;
}

long value_read( FILE * file )
{
    char buffer[64] ;
    char * str = fgets( buffer, sizeof(buffer), file ) ;
    if ( str == buffer ) {
	return strtol( buffer, NULL, 10 ) ;
    }
    perror("Trouble reading file" ) ;
    exit(1) ;
}
    
int main( int argc, char **argv )
{

    progname = argv[0] ; // point to invoked program name
    
    // Arguments
    int c ;
    while ( (c = getopt( argc, argv, "hfcg" )) != -1 ) {
	switch ( c ) {
	    case 'h':
		help() ;
		return 0 ;
	    case 'f':
		printf("%s\n", ControlDir ControlCur );
		exit(0) ;
	    case 'c':
		printf("%s\n", ControlItem );
		return 0 ;
	    case 'g':
	    {
		FILE * fcur = file_open( ControlDir ControlCur, "r" ) ;
		long current = value_read( fcur ) ;
		fclose( fcur ) ;
		
		FILE * fmax = file_open( ControlDir ControlMax, "r" ) ;    
		long maximum = value_read( fmax ) ;
		fclose( fmax ) ;

		long minimum = ControlMin ;

		printf("%ld,%ld,%ld\n", minimum,current,maximum );
		return 0 ;
	    }
	    default:
		break ;
	}
    }

    if ( optind != argc-1 ) {
	help() ;
	fprintf( stderr, "\nNeeds a single numeric argument\n");
	exit(1) ;
    }

    // read brightness value from command line
    char * endptr ;
    long bright = strtol( argv[optind], &endptr, 10 ) ;
    if ( argv[optind] == endptr ) {
	help() ;
	fprintf( stderr, "\nInvalid numeric argument: %s\n", argv[optind] );
	exit(1) ;
    }
    
    // write brightness to control file
    FILE * sys = file_open( ControlDir ControlCur, "a" ) ;
    if ( fprintf( sys, "%ld\n", bright ) < 1 ) {
	perror("Trouble writing to "ControlDir ControlCur ) ;
    }
    fclose( sys ) ;
    return 0 ;
}
