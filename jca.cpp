/*
** Used count_numbers.py to count iters. Only need max = 400.
** Don't need png writer as no png output.
** Mod to write to csv file.
** JM Tue 20 Mar 2018 19:56:46 GMT
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
myfile.open( "jca001_995.csv" ) ;

double X_MIN = -1.6 ;
double X_MAX =  1.6 ;
double X     =  0.0 ;
double Y_MIN = -1.3 ;
double Y_MAX =  1.3 ;
double Y     =  0.0 ;
//double Z     =  0.0 ;
//double C     =  0.0 ;
double offset   = 0.001 ;
int maxiter     = 400 ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 0 ;
int y_pixel     = 0 ;
complex<double> C( -0.7, 0.28 ) ;

X_SIZE = 1 + ( X_MAX - X_MIN ) / offset ;
Y_SIZE = 1 + ( Y_MAX - Y_MIN ) / offset ;

cout << "X: " << X_SIZE << " Y: " << Y_SIZE << endl ;
// Print size so plotting prog can use it.
myfile << X_SIZE << "," << Y_SIZE << endl ;

x_pixel = 0 ;
for ( X = X_MIN ; X <= X_MAX ; X += offset ) {
	y_pixel = 0 ;
	for ( Y = Y_MIN ; Y <= Y_MAX ; Y += offset ) {

		complex<double> Z( X, Y ) ;
		iter_count  = 0 ;

		while ( abs( pow( Z, 2 ) ) < 4 && iter_count < maxiter ) {

			Z = pow( Z, 2 ) + C ;
			iter_count++ ;

		} // End while.

		myfile << x_pixel << "," << y_pixel << "," << iter_count << endl ;

                y_pixel += 1 ;

	} // End for Y.

	x_pixel += 1 ;

} // End for X.

cout << "XP: " << x_pixel << " YP: " << y_pixel << endl ;

high_resolution_clock::time_point t2 = high_resolution_clock::now();

auto duration = duration_cast<microseconds>( t2 - t1 ).count();

cout << "Time Elapsed: " << duration << " microseconds" << endl ;

myfile.close();

exit( 0 ) ;

} // End main.
