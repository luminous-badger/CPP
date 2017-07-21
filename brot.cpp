/*
** Basic Mandelbrot set with char output.
** JM Thu 20 Jul 2017 23:32:32 BST
*/
#include <iostream>

#include <complex>      // std::complex, std::abs
 
using namespace std ;

int main() {

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

for ( Y = Y_MIN ; Y <= Y_MAX ; Y += offset ) {
	for ( X = X_MIN ; X <= X_MAX ; X += offset ) {

		complex<double> Z( 0.0, 0.0 ) ;
		complex<double> C( X, Y ) ;
		iter_count  = 0 ;

		// cout << "X: " << X << " Y: " << Y << " Z: " << Z ; cout << " Abs: " << abs( Z ) << endl ;

		while ( abs( pow( Z, 2 ) ) < 4 && iter_count < maxiter ) {

			Z = pow( Z, 2 ) + C ;
			iter_count++ ;

		} // End while.

		if ( iter_count < maxiter ) {
			cout << " " ;
		} else {
			cout << "*" ;
		} // End if.

	} // End for X.

	cout << endl ;

} // End for Y.

exit( 0 ) ;

} // End main.
