/*
** First attempt at using PNGWriter. Copied from manual.
** Compile with:
** g++ pngwriter1.cpp -o pn1.exe -I/usr/local/include -L/usr/local/lib -lpng -lpngwriter -DNO_FREETYPE 
** JM Wed 26 Jul 2017 21:20:46 BST
*/

/*
void filledtriangle( int x1,int y1,int x2,int y2,int x3,int y3, int red, int green, int blue ) ;
*/

#include <pngwriter.h>

int main() {
          pngwriter image(200, 300, 1.0, "out.png");
          image.plot(30, 40, 1.0, 0.4, 0.4);
          image.plot(90, 90, 100, 904, 904);
          image.line( 190, 190, 290,290, 100, 904, 904);
	image.filledtriangle( 10, 100, 100, 150 , 159, 200, 100 , 200, 200 ) ;
          image.close();
return 0; }


