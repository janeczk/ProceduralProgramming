#include "Util.h"
#include <stdio.h>
#include <math.h>


#define MIN_DBL 1e-100

void skipSpaces();
int isDigit( char c );




//------------------
int isOper( char c ) {//switch
    switch( c ) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^': return 1;
    }
    return 0;
}
char getOper() {
	skipSpaces();
	return getchar();
}
int prior( char c ) {//switch
    switch( c ) {
    case '+':
    case '-':return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    }
    return 0;
}
double getNum() {
    double num = 0.0;
    int c;
    while( isDigit( c = getchar() ) ) {
      num = num * 10.0 + (c - '0');
    }
    if( c == '.' ) {
        double coef = 0.1;
        while( isDigit(c=getchar()) )
        {
            num += coef * ( c - '0' );
            coef *= 0.1;
        }
    }
    ungetc( c, stdin );
    return num;
}
double Eval( double arg1, double arg2, char oper ) {//switch
    switch( oper ) {
    case '+':return arg1 + arg2;
    case '-':return arg1 - arg2;
    case '*':return arg1 * arg2;
    case '/':if( !arg2 ) return MIN_DBL; return (double)(arg1 / arg2);
    case '^':return pow( arg1, arg2 );
    }
    return 0;
}
void skipSpaces() {
    int c;
    do {
        c = getchar();
    } while( c == ' ' || c == '\t' );
    ungetc( c, stdin );
}
int isDigit( char c ) {
    return (c >= '0') && (c <= '9');
}