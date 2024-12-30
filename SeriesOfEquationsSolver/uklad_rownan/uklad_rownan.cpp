#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include "matrix.h"
#include <math.h>

#define	_DEBUG_

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );
int CreateTab( double** pVec, int nDim );
void printVector( double* pVec, int nDim );

int main( int argc, char* argv[] )
{
	// sprwdzic argumenty main
	if( argc != 2 ) {
		printf( "USAGE: %s <plik_we>\n", argv[0] );
		return 1;
	}
	// odtworzyc plik do odczytu (tekstowy)
	FILE* fin = NULL;
	if( (fin = fopen( argv[1], "rt" ) ) == NULL ) {  //zdefiniowac _CRT_SECURE_NO_WARNINGS
		printf( "Error opening the file %s <plik_we>\n", argv[0] );
		return 4;
	}
	// odczytac rozmiar nDim   fscanf( fin, "%d\n", &nDim ); // nDim param WY   fin plik po otwarciu do odczytu
	int nDim = 0;
	fscanf( fin, "%d\n", &nDim );
#ifdef _DEBUG_
	printf( "nDim= %d\n\n", nDim );
#endif
	// wykreowac macierz pMatrix ukladu nDim x nDim					
	double** pMatrix = NULL;
	if( !CreateMatrix( &pMatrix, nDim ) ) {
		perror( "Matrix creation error\n" );
		return 2;
	}
	// wykreowac wektor wyrazow wolnych b						 
	double* b = NULL;
	//wykreowac createTab( &b, nDFim );
	if( !CreateTab( &b, nDim ) ) {
		printf( "Blad w tworzeniu wektora wyrazów wolnych b\n" );
		return -3;
	}
	// wczytac dane ( ReadData() )
	ReadData( fin, pMatrix, b, nDim );
	//wydruk kontrolny (warunkowa kompilacja)
#ifdef _DEBUG_
	printf( "Wczytana macierz:\n" );
	PrintMatrix( pMatrix, nDim );
	printf( "Wektor wyrazow wolnych b:\n" );
	printVector( b, nDim );
#endif
	// obl wyznacznik
	double det = Det( pMatrix, nDim );//dla znanych przypadkow zwrocic wartosc
	if( !floor(det) ) {
		printf( "Macierz jest osobliwa.\n" );
		return -4;
	}
	//wydruk kontrolny (warunkowa kompilacja)
#ifdef _DEBUG_
	printf( "\nwyznacznik to:%f\n\n", det );
#endif
	// obrocic macierz
	double** Inv = NULL;
	if( !CreateMatrix( &Inv, nDim ) ) {
		printf( "Blad w tworzeniu Inv\n" );
		return -5;
	}
	InverseMatrix( Inv, pMatrix, nDim, det );
	//wydruk kontrolny  (warunkowa kompilacja)
#ifdef _DEBUG_
	printf( "macierz odwrotna:\n\n" );
	PrintMatrix( Inv, nDim );
#endif
	// wykreowac wektor wynikowy
	double* vecRes = NULL;
	if( !CreateTab( &vecRes, nDim ) ) {
		printf( "Blad w tworzeniu vecRes\n" );
		return -6;
	}
	// rozwiazac ukl
	LayoutEqu( Inv, b, vecRes, nDim );
	// wyniki
	printf( "Wektor wynikowy:\n" );
	printVector( vecRes, nDim );
	// zwolnic pamiec !!!
	DeleteMatrix( &pMatrix, nDim );
	DeleteMatrix( &Inv, nDim );
	free( b );
	free( vecRes );
	return 0;
}




void ReadData( FILE* fin, double** pMatrix, double* b, int nDim ) {	
	for( int i = 0; i < nDim; i++ ){
		double* v = *pMatrix++;
		for( int j = 0; j < nDim; j++ ) fscanf( fin, "%lf ", v++ );
		fscanf( fin, "%lf", b++ );
	}
}

int CreateTab( double** pVec, int nDim ) {
	*pVec = (double*)malloc( nDim * sizeof( double ) );
	if( !*pVec ) return 0;
	memset( *pVec, 0, nDim * sizeof( double ) );
	return 1;
}


void printVector( double* pVec, int nDim ) {
	for( int i = 0; i < nDim; i++ ) printf( "%.2lf \n", *pVec++ );
	printf( "\n" );
}