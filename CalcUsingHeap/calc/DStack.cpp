#include "DStack.h"  // "" bo moj plik nagl
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define MAXDSTACK   20

//int DStack[MAXDSTACK] = { 0 };
//int nDHead = 0; // indeks pierwszego wolnego miesca na stosie

DStackItem* createDStack() {
    return NULL;
}

void dpush( DStackItem** pStack, double x ) // wloz na stos
{
    DStackItem* p = (DStackItem*)malloc( sizeof( DStackItem ) );//alokacja pamieci na nowy lelement stosu
    if( !p ) {
        perror( "Allocation error:DStackItem" );
        return;
    }//sprawdzenie czy sie powioedlo-komunkat o bledzie alkoacjii i wyjscie
    p->key = x;//wstawienie x do klucza
    p->pNext = *pStack;//dowiazanie na szczyt stosu
    *pStack = p;
}

double dpop( DStackItem** pStack )          // zdejmij i zwroc szczytowy eleme stosu
{
    if( !isDEmpty( *pStack ) )
    {
        double x = dtop( *pStack );
        ddel( pStack );
        return x;
    }
    perror( "dpop: DStack underflow1!\n" );
    return 0;
}

double dtop( DStackItem* pStack )          // zwroc szczytowy elem stosu
{
    if( !isDEmpty( pStack ) )
        return pStack->key;//pole key lementu wsk przez wskaznik stosu;
    perror( "DStack underflow2!\n" );
    return 0;

}
void ddel( DStackItem** pStack )         // usun szczytowy (zdejmij)
{
    if( !isDEmpty( *pStack ) )
    {
        DStackItem* p = *pStack;
        //zlapac szczyt stosu dodatkowym wsk

        *pStack = p->pNext; //przewiazac stos na nas element
        free( p );//zwolnic pamiec
        return;
    }
    perror( "DStack underflow!\n" );
}
int isDEmpty( DStackItem* pStack )      // zwraca true jesli stos pusty - else false
{
    return !pStack;
}