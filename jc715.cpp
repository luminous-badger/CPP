/*
** Basic Mandelbrot set with EasyBMP output.
** Need to plot X,Y to get antenna on horiz axis.
** JM Mon 23 Apr 2018 18:11:55 BST
*/
#include <iostream>
#include <chrono>
#include <complex>      // std::complex, std::abs
 
#include "EasyBMP.h"

using namespace std ;
using namespace std::chrono;

int main() {

high_resolution_clock::time_point t1 = high_resolution_clock::now();

double X_MIN = -1.8 ;
double X_MAX =  1.8 ;
double X     =  0.0 ;
double Y_MIN = -1.2 ;
double Y_MAX =  1.2 ;
double Y     =  0.0 ;
double Z     =  0.0 ;
//double C     =  0.0 ;
double elptm    =  0.0 ;
double offset   = 0.005 ;
int maxiter     = 950 ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 0 ;
int y_pixel     = 0 ;
int duration    = 0 ;
complex<double> C( -0.751, 0.15 ) ;

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

		//complex<double> Z( 0.0, 0.0 ) ;
		complex<double> Z( X, Y ) ;
		iter_count  = 0 ;

		while ( abs( pow( Z, 2 ) ) < 4 && iter_count < maxiter ) {

			Z = pow( Z, 2 ) + C ;
			iter_count++ ;

		} // End while.

		if ( iter_count < maxiter ) {

		   mandel( x_pixel, y_pixel )->Red   = (ebmpBYTE) ( iter_count * 13 ) ;
		   mandel( x_pixel, y_pixel )->Green = (ebmpBYTE) ( iter_count * 203 ) ; 
		   mandel( x_pixel, y_pixel )->Blue  = (ebmpBYTE) ( iter_count * 303 ) ;
			
		} else {
		
		   mandel( x_pixel, y_pixel )->Red   = (ebmpBYTE) ( 200 ) ;
		   mandel( x_pixel, y_pixel )->Green = (ebmpBYTE) ( 200 ) ; 
		   mandel( x_pixel, y_pixel )->Blue  = (ebmpBYTE) ( 200 ) ;

		} // End if.
		y_pixel += 1 ;

	} // End for Y.
        x_pixel += 1 ;

} // End for X.

mandel.WriteToFile("ejc715b.bmp");

high_resolution_clock::time_point t2 = high_resolution_clock::now();

//auto duration = duration_cast<microseconds>( t2 - t1 ).count();
duration = duration_cast<microseconds>( t2 - t1 ).count();
elptm = duration / 1000000.0 ;

cout << "Julia Set for Z^2 and C: " << C << endl ;

cout << "X_MIN: " << X_MIN << " X_MAX: " << X_MAX << " Y_MIN: " << Y_MIN << " Y_MAX: " << Y_MAX << endl ;

cout << "Time Elapsed: " << elptm << " seconds" << endl ;

exit( 0 ) ;

} // End main.
