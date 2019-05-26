/*
** Burning Ship Z^N Julia. Im abs only.
g++ -o xzbs31.exe zjbship31.cpp 
** JM Tue  9 Apr 12:23:53 BST 2019
*/
#include <iostream>
#include <fstream>

#include <complex>      // std::complex, std::abs
 
using namespace std ;

int main() {

double X_MIN = -0.54 ;
double X_MAX = -0.384 ;
double X     =  0.0 ;
double Y_MIN = -0.95 ;
double Y_MAX = -0.8 ;
double Y     =  0.0 ;
double Z     =  0.0 ;
double offset   = 0.0001 ;
double ZPower   = 1.7 ;
int maxiter     = 2000 ;
int iter_count  = 0 ;
float X_SIZE    = 0 ;
float Y_SIZE    = 0 ;
int x_pixel     = 0 ;
int y_pixel     = 0 ;
complex<double> C(  0.3,  0.1 ) ;

ofstream myfile;
myfile.open( "zjbs31c.csv" ) ;

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

		while ( abs( pow( Z, ZPower ) ) < 4 && iter_count < maxiter ) {

			Z = complex<double> (real(Z), abs(imag(Z))  ) ;
			Z = pow( Z , ZPower ) + C ;
			iter_count++ ;

		} // End while.

		myfile << x_pixel << "," << y_pixel << "," << iter_count << endl ;

                y_pixel += 1 ;


	} // End for Y.

	//cout << endl ;
	x_pixel += 1 ;

} // End for X.

cout << "XP: " << x_pixel << " YP: " << y_pixel << endl ;
myfile.close();

//exit( 0 ) ;

} // End main.
