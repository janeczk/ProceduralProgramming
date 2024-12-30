#include "Stack.h"
#include "DStack.h"
#include <stdio.h>
#include "Util.h"

double ONP();

int main()
{
    printf( "Podaj wyrazenie:" );
    printf( "Wartosc wyrazenia = %.3lf\n", ONP() );
    return 0;
}

double ONP() {
    StackItem* pStack = createStack();//wykreowac stos znakowy
    DStackItem* pDStack = createDStack();//wykreowac stos liczbowy
    dpush( &pDStack, getNum() );//wczytac liczbe i na stos
    char c;
    while( isOper( c = getOper() ) ) {//wczytanie operatora
        while( prior( c ) <= prior( top( pStack ) ) ) {//jezeli prior wczytanego operatora jest<=prior szczyt stosu
            //putchar( pop(&pStack) );//zdejmujemy ze stosu liczbowego dwa argumenty i operator ze stosu znakowego
            double s = dpop( &pDStack );
            //double s2 = dpop( &pDStack );
            //char c1 = pop( &pStack );
            dpush( &pDStack, Eval( dpop( &pDStack ), s, pop( &pStack ) ) );//liczymy i wynik na stos liczbowy
        }
        push( &pStack, c );//wlozyc na stos znakowy znak operatora
        dpush( &pDStack, getNum() );//wczytac liczbe i na stos liczb
    }
    while( !isEmpty(pStack) ) {
        //double s1 = dpop( &pDStack );
        double s = dpop( &pDStack );
        //char c1 = pop( &pStack );
        dpush( &pDStack, Eval( dpop( &pDStack ), s, pop( &pStack ) ) );
    }//czyszczenie stosu operatora
    //zdejmujemy operator i dwa argumenty liczymy i wynik na stos liczbowy
    return dpop( &pDStack );

}
