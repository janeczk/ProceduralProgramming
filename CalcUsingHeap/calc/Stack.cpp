#include "Stack.h"  // "" bo moj plik nagl
#include <memory.h>
#include <stdio.h>
#include<stdlib.h>

//#define MAXSTACK   10

//int Stack[MAXSTACK] = { 0 };
//int nHead = 0; // indeks pierwszego wolnego miesca na stosie

StackItem* createStack() {
    return NULL;
}

void push( StackItem** pStack, char x ) // wloz na stos
{
    StackItem* p = (StackItem*)malloc( sizeof( StackItem ) );//alokacja pamieci na nowy lelement stosu
    if( !p ) {
        perror( "Allocation error:StackItem" );
        return;
    }//sprawdzenie czy sie powioedlo-komunkat o bledzie alkoacjii i wyjscie
    p->key = x;//wstawienie x do klucza
    p->pNext = *pStack;//dowiazanie na szczyt stosu
    *pStack = p;
}

char pop( StackItem** pStack )          // zdejmij i zwroc szczytowy eleme stosu
{
  if( !isEmpty(*pStack) )
  {
     char x = top( *pStack );
     del(pStack);
     return x;
  }
  perror("Stack underflow1!\n");
  return 0;
}

char top( StackItem* pStack )          // zwroc szczytowy elem stosu
{
    if( !isEmpty(pStack) )
        return pStack->key;//pole key lementu wsk przez wskaznik stosu;
  //perror("Stack underflow2!\n");
  return 0;

}
void del( StackItem** pStack )         // usun szczytowy (zdejmij)
{
  if( !isEmpty(*pStack) )
  {  
      StackItem* p = *pStack;
     //zlapac szczyt stosu dodatkowym wsk
     
      *pStack = p->pNext; //przewiazac stos na nas element
      free( p );//zwolnic pamiec
     return;
  }
  perror("Stack underflow!\n");
}
int isEmpty( StackItem* pStack )      // zwraca true jesli stos pusty - else false
{
  return !pStack;
}
