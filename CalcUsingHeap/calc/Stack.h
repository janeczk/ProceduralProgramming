
#ifndef _STACK_H
#define _STACK_H

// naglowki funkcji publicznych modulu

//zdefiniowac ty strukturalny StackItem dla elementu stosu (element listy prostej)
//pola:key oraz pNext(point na nast)

typedef struct tagStackItem {
	char key;
	tagStackItem* pNext;
}StackItem;


//dodac parametr-przekaz stos do funkcji

StackItem* createStack();
void push( StackItem** pStack, char x ); // wloz na stos
char pop( StackItem** pStack );          // zdejmij i zwroc szczytowy eleme stosu
char top( StackItem* pStack );          // zwroc szczytowy elem stosu
void del( StackItem** pStack );         // usun szczytowy (zdejmij)
int isEmpty( StackItem* pStack );      // zwraca true jesli stos pusty - else false

#endif
