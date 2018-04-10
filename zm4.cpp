/*
** Plotting Sea Horse zoom.
** Need png writer as png output.
** Found that we get no more detail with iter > 1000.
** JM Fri  9 Mar 15:47:20 GMT 2018
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
g++ zm4.cpp -o xzm4.exe -I/usr/local/include -L/usr/local/lib -lpng -lpngwriter -DNO_FREETYPE -std=gnu++11
*/
int main() {

high_resolution_clock::time_point t1 = high_resolution_clock::now();

double X_MIN = -1.0  ;
double X_MAX = -0.65 ;
double X     =  0.0  ;
double Y_MIN = -0.25 ;
double Y_MAX =  0.0  ;
double Y     =  0.0  ;
double offset   = 0.001 ;
int maxiter     = 1000 ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 0 ;
int y_pixel     = 0 ;

X_SIZE = 1 + ( X_MAX - X_MIN ) / offset ;
Y_SIZE = 1 + ( Y_MAX - Y_MIN ) / offset ;

// Print size so plotting prog can use it.
cout << "X_SIZE  " << X_SIZE << ", Y_SIZE " << Y_SIZE << endl ;

// pngwriter image( X_SIZE, Y_SIZE, 1.0, "zoom_sh.png");
pngwriter image( X_SIZE, Y_SIZE, 65535, "zoom_sh3.png");
void plot(int x, int y, int red, int green, int blue);

x_pixel = 0 ;
for ( X = X_MIN ; X <= X_MAX ; X += offset ) {
	y_pixel = 0 ;
	for ( Y = Y_MIN ; Y <= Y_MAX ; Y += offset ) {

		complex<double> C( X, Y ) ;
		complex<double> Z( 0.0, 0.0 ) ;
		iter_count  = 0 ;

		while ( abs( pow( Z, 2 ) ) < 4 && iter_count < maxiter ) {

			Z = pow( Z, 2 ) + C ;
			iter_count++ ;

		} // End while.

		//image.plot( x_pixel, y_pixel, 12 * iter_count, 31 * iter_count, 42 * iter_count ) ;
		image.plot( x_pixel, y_pixel,  3 * iter_count, 25 * iter_count, 50 * iter_count ) ;
		// image.plotHSV( x_pixel, y_pixel, (double)0.656-(0.656* iter_count ), (double)(0.7)*(1.0 - iter_count ), 1.0 ) ;
		// Just gives a white square.
                y_pixel += 1 ;

	} // End for Y.

	x_pixel += 1 ;

} // End for X.

high_resolution_clock::time_point t2 = high_resolution_clock::now();

auto duration = duration_cast<microseconds>( t2 - t1 ).count();

cout << "Time Elapsed: " << duration << " microseconds" << endl ;

image.close();
} // End main.
