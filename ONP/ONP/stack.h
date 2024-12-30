#ifndef _STACK_H
#define _STACK_H

// naglowki funkcji publicznych modulu

int isOper( char c );
int prior( char c );
void ONP();
void push( int x ); // wloz na stos
int pop();          // zdejmij i zwroc szczytowy eleme stosu
int top();          // zwroc szczytowy elem stosu
void del();         // usun szczytowy (zdejmij)
int isEmpty();      // zwraca true jesli stos pusty - else false

#endif
