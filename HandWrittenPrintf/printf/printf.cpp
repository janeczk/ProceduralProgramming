#include <stdio.h>
#include <stdarg.h>

#define MIN 1e-5

int Printf( const char* sFormat, ... );
int PrintfV( const char* sFormat, va_list va_arg );


void outDec( int );       // znakowo wypisuje liczbe calk
void outChar( char );     // wypisuje znak  // putchar()
void outStr( char* );     // wypisuje zanakowo string
void outDouble( double ); // wypisuje znakowow liczbe double    0.
void outNum( int x );     // wypisuje znakowo liczbe int >0     rekurencyjnie

int main( int argc, char* argv[] )
{
	int n = -0;
	char c = '$';
	double x = 12000000.34050000012;     // .0000012 <=1e-5
	double y = -.12;
	double z = -0.5;
	char* str = (char*)"to jest string";

    Printf( "%s\n\n", str );
    Printf( "%d\n\n", n );
    Printf( "%c\n\n", c );
    Printf( "%f\n\n", x );
    Printf( "%f\n\n", y );
    Printf( "%f\n\n", z );

	Printf( "%s\n%f%c  n=%d \\ \% /\ny=%f ` ` z=%%f\n\n\%", str, x, c, n, y, z );// ` -> '
    printf( "%s\n%f%c  n=%d \\ \% /\ny=%f ` ` z=%%f\n\n\%", str, x, c, n, y, z );
	return 0;
}
// implementacja uproszczonej funkcji "Printf": %c %d %f %s oraz 
// zamienia `(klawisz ~) na '( klawisz ")
// do wypisywania mozna uzyc JEDYNIE outChar() -


int Printf( const char* sFormat, ... )
{
    va_list args;// Initialize variable arguments 
    va_start( args, sFormat );// set the pointer at the beggining of the arg list and get the first argument from the args list
    int res = PrintfV( sFormat, args );
    va_end( args );// Reset variable arguments
	return res;
}

int PrintfV( const char* sFormat, va_list arg_list )
{
    char c;
    while( c=*sFormat++ )  //c = *ptr++
    {
        switch( c )
        {
        case '%':
            switch( c = *sFormat++ ){
                case 'd': outDec( va_arg( arg_list, int )); break;
                case 'f': outDouble( va_arg( arg_list, double )); break;
                case 's': outStr( va_arg( arg_list, char* )); break;
                case 'c': outChar( va_arg( arg_list, char )); break;
                default: 
                    outChar( '%' );
                    if( c && (c != '%') ) outChar( c );
                    else sFormat--;
            }
            break;
        case '`':  c = '\'';
        default: outChar( c );
        }
    }
    return 1;
}
void outChar( char c )
{
    putchar( c );
}
//-----------------------------------------------
void outStr( char* pStr )
{
    while( *pStr )outChar( *pStr++ );
}
//-----------------------------------------------
void outDec( int x )
{
    if( x < 0 ) {
        x = -x;
        outChar( '-' );
    }
    else if( !x ) {
        outChar( '0' );
    }
    outNum( x );
}

//-----------------------------------------------
void outDouble( double x )
{
    if( x < 0 ) {
        x = -x;
        outChar( '-' );
    }
    outDec( (int)x );
    outChar('.');
    x = x - (int)x;
    for( int i = 0; i < 6 && (x-(int)x)>MIN; i++) {
        x *= 10;
        //outNum( (int)x );
        outChar( (int)x%10 +'0');
        //x = x - (int)x;

    }

}
//-----------------------------------------------
void outNum( int x ) //rekurencyjny
{
    if( x > 0 ) {
        outNum( x / 10 );
        char c = x % 10 + 48;
        outChar( c );
    }
}
