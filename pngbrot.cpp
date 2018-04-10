/*
** Attemp Mandelbrot set with PNGWriter output.
** JM Wed 26 Jul 2017 21:56:54 BST
*/
#include <iostream>
#include <chrono>

#include <complex>      // std::complex, std::abs
 
using namespace std ;
using namespace std::chrono;

#include <pngwriter.h>
/*
** Usage:
** pngwriter(int width, int height, int backgroundcolour, char * filename);
** void plot(int x, int y, int red, int green, int blue);
** void plot(int x, int y, double red, double green, double blue);
**
** If the colour coefficients are of type int, they go from 0 to
** 65535. If they are of type double, they go from 0.0 to 1.0. Tip:
** To plot using red, then specify plot(x, y, 1.0, 0.0, 0.0). To make
** pink, just add a constant value to all three coefficients, like
** this: plot(x, y, 1.0, 0.4, 0.4). 
**
** Compile with:
** g++ pngbrot.cpp -o br1.exe -I/usr/local/include -L/usr/local/lib -lpng -lpngwriter -DNO_FREETYPE 
*/

int main() {
    
high_resolution_clock::time_point t1 = high_resolution_clock::now();

double X_MIN = -2.0 ;
double X_MAX =  1.0 ;
double X     =  0.0 ;
double Y_MIN = -1.0 ;
double Y_MAX =  1.0 ;
double Y     =  0.0 ;
double Z     =  0.0 ;
double C     =  0.0 ;
double offset   = 0.01 ;
int maxiter     = 50   ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 1 ;
int y_pixel     = 1 ;

X_SIZE = ( X_MAX - X_MIN ) / offset ;
Y_SIZE = ( Y_MAX - Y_MIN ) / offset ;

cout << "X: " << X_SIZE << " Y: " << Y_SIZE << endl ;

pngwriter image( X_SIZE, Y_SIZE, 1.0, "brot6.png");

x_pixel = 1 ;
for ( X = X_MIN ; X <= X_MAX ; X += offset ) {
	y_pixel = 1 ;
	for ( Y = Y_MIN ; Y <= Y_MAX ; Y += offset ) {

		complex<double> Z( 0.0, 0.0 ) ;
		complex<double> C( X, Y ) ;
		iter_count  = 0 ;

		// cout << "X: " << X << " Y: " << Y << " Z: " << Z ; cout << " Abs: " << abs( Z ) << endl ;

		while ( abs( pow( Z, 2 ) ) < 4 && iter_count < maxiter ) {

			Z = pow( Z, 2 ) + C ;
			iter_count++ ;

		} // End while.

		//if ( iter_count < maxiter ) { }
		image.plot( x_pixel, y_pixel, 13 * iter_count, 1000 * iter_count, 33 * iter_count ) ;
		// image.plot( x_pixel, y_pixel, 1 / iter_count, 1 / iter_count, 1 / iter_count ) ; // solid block !
                y_pixel += 1 ;

	} // End for Y.

//	cout << endl ;
	x_pixel += 1 ;

} // End for X.

cout << "XP: " << x_pixel << " YP: " << y_pixel << endl ;
image.close();

high_resolution_clock::time_point t2 = high_resolution_clock::now();

auto duration = duration_cast<microseconds>( t2 - t1 ).count();

cout << "Time Elapsed: " << duration << " microseconds" << endl ;

exit( 0 ) ;

} // End main.
