/*
** Print out xpix, ypix, iter_count for plotting Julia of C = complex ( -0.7691574125898175, 0.1167394219557992 )
** Don't need png writer as no png output.
** Mod to write to csv file.
** JM Wed 22 Nov 2017 21:11:49 GMT
** CPP to write x,y,i file for bbstar.py.
*/
#include <iostream>
#include <fstream>
#include <chrono>

#include <complex>      // std::complex, std::abs
 
using namespace std ;
using namespace std::chrono;


int main() {
    
high_resolution_clock::time_point t1 = high_resolution_clock::now();

ofstream myfile;
myfile.open( "crapstar2.csv" ) ;

double center_r=1.914621513551386e-07 ;
double r_width = 0.00415072 ;     // Seems to give similar size to pic on web page.
int    plot_height = 800 ;
double X_MIN =  0.0 ;
double X_MAX =  0.0 ;
double X     =  0.0 ;
double Y_MIN =  0.0 ;
double Y_MAX =  0.0 ;
double Y     =  0.0 ;
//double Z     =  0.0 ;
//double C     =  0.0 ;
double offset   = 0.0 ;
int maxiter     = 10000   ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 0 ;
int y_pixel     = 0 ;
complex<double> C( 0.2650393607207308, 0.003034021619132559 ) ;
X_MIN = 0.0 - r_width ;
X_MAX = 0.0 + r_width ;
Y_MAX = X_MAX ;
Y_MIN = X_MIN ;

offset     = ( X_MAX - X_MIN ) / plot_height ;
X_SIZE     = 1 + ( X_MAX - X_MIN ) / offset ;
Y_SIZE     = 1 + ( Y_MAX - Y_MIN ) / offset ;

cout << "X: " << X_SIZE << " Y: " << Y_SIZE << " Offset: " << offset << endl ;
// Print size so plotting prog can use it.
myfile << X_SIZE << "," << Y_SIZE << endl ;

x_pixel = 0 ;
for ( X = X_MIN ; X <= X_MAX ; X += offset ) {
	y_pixel = 0 ;
	for ( Y = Y_MIN ; Y <= Y_MAX ; Y += offset ) {

		complex<double> Z( X, Y ) ;
		iter_count  = 0 ;

		// cout << "X: " << X << " Y: " << Y << " Z: " << Z ; cout << " Abs: " << abs( Z ) << endl ;

		while ( abs( pow( Z, 2 ) ) < 4 && iter_count < maxiter ) {

			Z = pow( Z, 2 ) + C ;
			iter_count++ ;

		} // End while.

		//cout << "X: " << x_pixel << " Y: " << y_pixel << " Z: " << Z ; cout << " I: " << iter_count << endl ;

		myfile << x_pixel << "," << y_pixel << "," << iter_count << endl ;

                y_pixel += 1 ;

	} // End for Y.

//	cout << endl ;
	x_pixel += 1 ;

} // End for X.

cout << "XP: " << x_pixel << " YP: " << y_pixel << endl ;

high_resolution_clock::time_point t2 = high_resolution_clock::now();

auto duration = duration_cast<microseconds>( t2 - t1 ).count();

cout << "Time Elapsed: " << duration << " microseconds" << endl ;

myfile.close();

exit( 0 ) ;

} // End main.
