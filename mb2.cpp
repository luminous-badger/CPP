/*
** Basic Mandelbrot.
** Compile with:
   g++ -o xmb2.exe mb2.cpp EasyBMP.cpp
** Include EasyBMP.cpp and rest of EBMP files in directory.
** JM Wed 25 Apr 2018 10:39:48 BST
*/
#include <iostream>
#include <chrono>
#include <complex>      // std::complex, std::abs
 
#include "EasyBMP.h"

using namespace std ;
using namespace std::chrono;

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
double offset   = 0.01 ;
int maxiter     = 50 ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 0 ;
int y_pixel     = 0 ;
int duration    = 0 ;
int Rval        = 0 ;
int Gval        = 0 ;
int Bval        = 0 ;
char fname[ 20 ]    ;
 
X_SIZE = 1 + ( X_MAX - X_MIN ) / offset ;
Y_SIZE = 1 + ( Y_MAX - Y_MIN ) / offset ;

cout << "X: " << X_SIZE << " Y: " << Y_SIZE << endl ;


//declare a bitmap
BMP mandel;
mandel.SetSize( X_SIZE, Y_SIZE );
mandel.SetBitDepth(24);

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

/*
                  mandel((int)(cr*2000+4000), (int)(ci*2000+4000))->Blue  = (ebmpBYTE) (255-(i/4));
                   mandel((int)(cr*2000+4000), (int)(ci*2000+4000))->Red   = (ebmpBYTE) (255-(i*1.25));
                   mandel((int)(cr*2000+4000), (int)(ci*2000+4000))->Green = (ebmpBYTE) (255-(i*1.25));
*/
		   Rval = 255 - iter_count / 5 ;
		   Gval = 255 - iter_count * 1.25 ;
		   Bval = 255 - iter_count * 1.35 ;
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

strncpy( fname , "mag5.bmp" , sizeof( "mag5.bmp" ) ) ;
//strlcpy( fname , "magl2.bmp" , sizeof( "mag2.bmp" ) ) ;

cout << "X_MIN: " << X_MIN << " X_MAX: " << X_MAX << " Y_MIN: " << Y_MIN << " Y_MAX: " << Y_MAX << endl ;
cout << "Rval: " << Rval << " Gval: " << Gval << " Bval: " << Bval << endl ;
cout << "Fname: " << fname << endl ;

cout << "Time Elapsed: " << elptm << " seconds" << endl ;
mandel.WriteToFile( fname  );

exit( 0 ) ;

} // End main.
