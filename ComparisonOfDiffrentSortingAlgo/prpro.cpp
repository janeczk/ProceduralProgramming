#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include "sort.h"

#define MAXTAB 50
#define MAXLINE 10
#define PRINT_TAB


typedef void (*pF)(int*, int);

void copyTab( int* pDest, int* pSource, int nSize );
void initTab( int* pTab, int nSize );
void printTab( int* pTab, int nSize );
double getTime();
void returnTime(double start);
int createTab( int** pTab, int nSize );//pTab wyjsciowy


int main( int argc, char* argv[] )
{
	if( argc != 2 ) {
		printf( "usage: %s <tab_size>\n", argv[0] );
		return 1;
	}

	int nSize = atoi( argv[1] );  //nSize str to int - jako argument 

	int* pPattern = NULL;

	if( !createTab( &pPattern, nSize ) ) { //tworzenie tablicy o danej wielkosci i przygotowanie miejsca
		perror( "Allocation error" );
		return 2;
	}

	int* pTab = NULL;

	if( !createTab( &pTab, nSize ) ) {
		perror( "Allocation error" );
		return 2;
	}
	//zdefiniowac tablice wzorcowa
	//int pattern[MAXTAB] = { 0 };

	//zainicjowac losowo tablice wzorcowa
	initTab( pPattern, nSize );

	//zdefiniowac tablice do sortowania
	//int tab[MAXTAB] = { 0 };


	const char* pn[] = {"BubbleSort", "SimpleInsertionSort", "SimpleSelectionSort", "HalfInsertionSort", "MixedSort", "HeapSort","QuickSort"};
	pF fa[] = { BubbleSort, SimpleInsertionSort, SimpleSelectionSort, HalfInsertionSort, MixedSort, HeapSort, QuickSort };


	for( int i = 0; i < (sizeof(fa)/sizeof(fa[i])); i++ ) {
		copyTab( pTab, pPattern, nSize );
		printf( "\n%s\n", pn[i] );
		double time_s = getTime();
		fa[i]( pTab, nSize );
		returnTime( time_s );
#ifdef PRINT_TAB
		printTab( pTab, (nSize < MAXTAB) ? nSize : MAXTAB );
#endif
	}
	//porownanie sortowan
	
	//printf( "Sortowanie babelkowe\n" );//wypisac rodzaj sortowan (od nowej linii)
	
	//copyTab( pTab, pPattern, nSize );//wkopiowac wzorcowa do tab
		
	//double time_s = getTime();//oczytac czas

	//HalfInsertionSort( pTab, nSize );//posortowac
		
	//returnTime( time_s );//wczytac czas i wypisac(milisek)

	//printTab( pTab, ( nSize<MAXTAB ) ? nSize : MAXTAB );//wypisac tablice

	free( pPattern );
	free( pTab );
	return 0;
}
int createTab( int** pTab, int nSize ) {
	*pTab = (int*)malloc( nSize * sizeof( int ) );
	if( !*pTab ) return 0;
	memset( *pTab, 0, nSize * sizeof( int ) );
	return 1;
}

double getTime() {
	return clock();
}

void returnTime( double start ) {
	double final_t = (double)(clock() - start) / CLOCKS_PER_SEC;
	printf( "%f\n", final_t );
}

void copyTab( int* pDest, int* pSource, int nSize ) {
	memcpy( pDest, pSource, nSize * sizeof(int) );
}

void initTab( int* pTab, int nSize ) {
	srand( (unsigned int)time(NULL) );
	for (int i = 0; i < nSize; i++) {
		*pTab++ = rand() % nSize;
	}
}

void printTab( int* pTab, int nSize ) {
	for (int i = 0; i < nSize; i++) {
		printf( "%d ", pTab[i] );
		if ( (i + 1) % MAXLINE == 0 ) printf("\n");
	}
}
