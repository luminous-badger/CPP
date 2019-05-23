/*
** Basic Mandelbrot.
** Compile with:
   g++ -o xmb3.exe mb_lc.cpp EasyBMP.cpp
** Include EasyBMP.cpp and rest of EBMP files in directory.
** Test of incluing colour list from header file based on Python colour list.
** JM Wed 22 May 15:31:16 BST 2019
*/
#include <iostream>
#include <chrono>
#include <complex>      // std::complex, std::abs
 
#include "EasyBMP.h"

using namespace std ;
using namespace std::chrono;
#include "header_lc.h"

int main() {

high_resolution_clock::time_point t1 = high_resolution_clock::now();

double X_MIN = -2.0 ;
double X_MAX =  0.8 ;
double X     =  0.0 ;
double Y_MIN = -1.2 ;
double Y_MAX =  1.2 ;
double Y     =  0.0 ;
double Z     =  0.0 ;
double C     =  0.0 ;
double elptm    = 0.0 ;
double offset   = 0.001 ;
int maxiter     = 250 ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 0 ;
int y_pixel     = 0 ;
int duration    = 0 ;
int Rval        = 0 ;
int Gval        = 0 ;
int Bval        = 0 ;
int rnum        = 93 ;  
char fname[ 20 ]    ;
 
X_SIZE = 1 + ( X_MAX - X_MIN ) / offset ;
Y_SIZE = 1 + ( Y_MAX - Y_MIN ) / offset ;

cout << "X: " << X_SIZE << " Y: " << Y_SIZE << endl ;


//declare a bitmap
BMP mandel;
mandel.SetSize( X_SIZE, Y_SIZE );
mandel.SetBitDepth(24);

int lenlc = sizeof(colour_list)/sizeof(colour_list[0]);

x_pixel = 0 ;
for ( X = X_MIN ; X <= X_MAX ; X += offset ) {
        y_pixel = 0 ;
	for ( Y = Y_MIN ; Y <= Y_MAX ; Y += offset ) {

		complex<double> Z( 0.0, 0.0 ) ;
		complex<double> C( X, Y ) ;
		iter_count  = 0 ;

		while ( abs( pow( Z, 2 ) ) < 4 && iter_count < maxiter ) {

			Z = pow( Z, 2 ) + C ;
			iter_count++ ;

		} // End while.

		if ( iter_count < maxiter ) {

		   if ( iter_count + rnum  >= lenlc ) {
			   Rval = colour_list[ iter_count % lenlc ][ 0 ] ;
			   Gval = colour_list[ iter_count % lenlc ][ 1 ] ;
			   Bval = colour_list[ iter_count % lenlc ][ 2 ] ;
		   } else {
			   Rval = colour_list[ iter_count + rnum ][ 0 ] ;
			   Gval = colour_list[ iter_count + rnum ][ 1 ] ;
			   Bval = colour_list[ iter_count + rnum ][ 2 ] ;
		   }
		   mandel( x_pixel, y_pixel )->Red   = (ebmpBYTE) ( Rval ) ;
		   mandel( x_pixel, y_pixel )->Green = (ebmpBYTE) ( Gval ) ; 
		   mandel( x_pixel, y_pixel )->Blue  = (ebmpBYTE) ( Bval ) ;
			
		} else {
		
		   mandel( x_pixel, y_pixel )->Red   = (ebmpBYTE) ( 100 ) ;
		   mandel( x_pixel, y_pixel )->Green = (ebmpBYTE) ( 100 ) ; 
		   mandel( x_pixel, y_pixel )->Blue  = (ebmpBYTE) ( 155 ) ;

		} // End if.
		y_pixel += 1 ;

	} // End for Y.
        x_pixel += 1 ;

} // End for X.

high_resolution_clock::time_point t2 = high_resolution_clock::now();

duration = duration_cast<microseconds>( t2 - t1 ).count();
elptm = duration / 1000000.0 ;

strncpy( fname , "mag7.bmp" , sizeof( "mag5.bmp" ) ) ;
//strlcpy( fname , "magl2.bmp" , sizeof( "mag2.bmp" ) ) ;

cout << "X_MIN: " << X_MIN << " X_MAX: " << X_MAX << " Y_MIN: " << Y_MIN << " Y_MAX: " << Y_MAX << endl ;
cout << "Rval: " << Rval << " Gval: " << Gval << " Bval: " << Bval << endl ;
cout << "Fname: " << fname << endl ;

cout << "Time Elapsed: " << elptm << " seconds" << endl ;
mandel.WriteToFile( fname  );

exit( 0 ) ;

} // End main.
