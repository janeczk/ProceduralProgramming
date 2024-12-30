#include "stack.h"  // "" bo moj plik nagl
#include <iostream>
#include <stdio.h>

using namespace std;

#define MAXSTACK   10

int Stack[MAXSTACK] = { 0 };
int nHead = 0; // indeks pierwszego wolnego miesca na stosie

int prior( char c ) {
    switch( c ) {
        case '+':
        case '-':return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return 0;
}

int isOper( char c ) {
    switch( c ) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^': return 1;
    }
    return 0;
}




void ONP() {
    char c;
    while( isOper( c = getchar() ) ) {
        while( prior( c ) <= prior( top() ) ) {
            putchar( pop() );
        }
        push( c );
        printf( "%c", c ); // wypisanie znaku na wyjœcie
    }
    while( !isEmpty() ) {
        putchar( pop() );
    }
}


void push( int x ) // wloz na stos
{
    if( nHead >= MAXSTACK )
    {
        cerr << "Stack overflow!\n";
        return;
    }
    Stack[nHead++] = x;
}

int pop()          // zdejmij i zwroc szczytowy eleme stosu
{
    if( !isEmpty() ) {
        int x = top();
        del();
        return x;
    }
    cerr << "Stack underflow1!\n";
    return 0;
}

int top()          // zwroc szczytowy elem stosu
{
    if( !isEmpty() ) return Stack[nHead - 1];
    cerr << "Stack underflow2!\n";
    return 0;

}
void del()         // usun szczytowy (zdejmij)
{
    if( !isEmpty() ) {
        nHead--;
        return;
    }
    cerr << "Stack underflow!\n";
}
int isEmpty()      // zwraca true jesli stos pusty - else false
{
    return !nHead;
}
