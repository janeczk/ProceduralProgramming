
#ifndef _DSTACK_H_
#define _DSTACK_H_

// naglowki funkcji publicznych modulu

typedef struct tagDStackItem {
	double key;
	tagDStackItem* pNext;
}DStackItem;

DStackItem* createDStack();
void dpush( DStackItem** pStack, double x ); // wloz na stos
double dpop( DStackItem** pStack );          // zdejmij i zwroc szczytowy eleme stosu
double dtop( DStackItem* pStack );          // zwroc szczytowy elem stosu
void ddel( DStackItem** pStack );         // usun szczytowy (zdejmij)
int isDEmpty( DStackItem* pStack );      // zwraca true jesli stos pusty - else false

#endif
