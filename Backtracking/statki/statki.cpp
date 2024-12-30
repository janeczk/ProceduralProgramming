#include "ship.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define DEPTH_MIN 5
#define N 10
#define M 10

int** CreateTab2D( int nCol, int nRow );
void PrintTab( int** pTab, int nCol, int nRow );
void DelTab( int*** pTab );

int main( int argc, char* argv[]) {

	if( argc != 2 ) {
		printf( "Usage: %s <input_file>\n", argv[0] );
		return 1;
	}//!!argc


	int** pTab = CreateTab2D( N, M );
	if( !pTab ) {
		printf( "Blad w tworzeniu pTab\n" );
		return 2;
	}
	int** pRoot = CreateTab2D( N, M );
	if( !pRoot ) {
		printf( "Blad w tworzeniu pRoot\n" );
		return 3;
	}//Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary)
	// wykorzystac funkcje z matrixa ale dodac parametr z drugim wymiarem
	
	// wczytac dane (sprawdzic argc)  glebokosci 
	if( setTab( argv[1], pTab, N, M ) == 0 ) {
		printf( "Blad w otwarciu pliku%s <input_file>\n", argv[0]);
		return 4;
	}
	printf( "Tablica glebokosci morza odczytana z pliku\n" );
	PrintTab( pTab, N, M );


	if( root( pTab, N, M, DEPTH_MIN, 0, 0, pRoot, N-1, M-1 ) == 0 ) {
		printf( "Nie ma mozliwosci doplynac do portu!!\n\n" );
	}
		// Jezeli nie znaleziono drogi od (0,0) do (N,M)- funkcja rekur root - wypisac
		//"** Nie ma mozliwosci doplynac do portu!!\n\n";
	else {
		printf( "Trasa statku to:\n" );
		PrintTab( pRoot, N, M );
	}
	// jesli ok to wypisac trase
	DelTab( &pTab );
	DelTab( &pRoot );
	//zwolnic pamiec!!

	return 0;
}


int** CreateTab2D( int nCol, int nRow ) {
	int** pTab = (int**)malloc( nRow * sizeof( int* ) );
	if( !pTab ) return NULL;
	memset( pTab, 0, nRow * sizeof( int* ) );

	*pTab = (int*)malloc( nRow * nCol * sizeof( int ) );
	if( !*pTab ) {
		free( pTab );
		return NULL;
	}
	memset( *pTab, 0, nRow * nCol * sizeof( int ) ); 

	int** v = pTab + 1;
	int* p = *pTab + nCol;
	for( int i = 1; i < nRow; i++, p += nCol ) *v++ = p;
	return pTab;
}

void PrintTab( int** pTab, int nCol, int nRow ) {
	for( int i = 0; i < nRow; i++ ) {
		int* v = *pTab++;
		for( int j = 0; j < nCol; j++ ) {
			printf( "%2d ", *v++ );
		}
		printf( "\n" );
	}
	printf( "\n" );
}



void DelTab( int*** pTab ) {
	free( **pTab );
	free( *pTab );
	*pTab = NULL;
}