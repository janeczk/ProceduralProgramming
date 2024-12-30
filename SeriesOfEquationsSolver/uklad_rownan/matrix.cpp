#include "matrix.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define WHATSGN(a) ( a % 2 ) ? -1 : 1
#define REVSGN(a) a = -a


// wycina wiersz i kolumne z tablicy we pTabI i reszte kopiuje do 
// tabl wyjsciowej pTabO (o rozmiarze nDim-1)
// nalezy uzyc dwa razu continue pomijajac wiersz nRow i kolumne nCol
void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim ) {
	for( int i = 0; i < nDim; i++, pTabI++ ){
		if( i == nRow ) continue;
		double* w = *pTabO++;
		double* v = *pTabI;
		for( int j = 0; j < nDim; j++, v++ ){
			if( nCol == j ) continue;
			*w++ = *v;
		}
	}
}

//macierz dopelnien
//---------------------------------------------------------------------//
// oblicza macierz dopelnien pTabD na podstawie tablic wejsc pTab
void ComplMatrix( double** pTabD, double** pTab, int nDim ) {
	double** pTemp = NULL;
	if( !CreateMatrix( &pTemp, nDim ) ) {
		printf("Blad tworzenia pTemp w ComplMatrix()\n");
		return;
	}
	for( int i = 0; i < nDim; i++ ) {
		int sgn = WHATSGN( i );
		double* p = *pTabD++;
		for( int j = 0; j < nDim; j++ ) {
			Complement( pTemp, pTab, i, j, nDim );
			*p++ = Det( pTemp, nDim - 1 ) * sgn;
			REVSGN(sgn);
		}
	}
	DeleteMatrix( &pTemp, nDim - 1 );
}

//---------------------------------------------------------------------//
void TransMatrix( double** pTab, int nDim ) {
	double** n = pTab;
	for( int i = 0; i < nDim - 1; i++ ) {
		double* k = *n++ + i + 1;
		for( int j = i + 1; j < nDim; j++ ) {
			double t = *k;
			*k++ = pTab[j][i];
			pTab[j][i] = t;
		}
	}
}//transponowanie

//---------------------------------------------------------------------//
int CreateMatrix( double*** pTab, int nDim ) {//stworz macierz
	*pTab = (double**)malloc( nDim * sizeof( double* ) );//tablica adresow
	if( !*pTab ) return 0;
	memset( *pTab, 0, nDim * sizeof(double*) );
	double** pTemp = *pTab;
	for( int i = 0; i < nDim; i++,pTemp++ ) {//na kazdy adres tworzymy tablice
		*pTemp = (double*)malloc( nDim * sizeof( double ) ); 
		if( !*pTemp )return 0;
		memset( *pTemp, 0, nDim * sizeof( double ) );
	}
	return 1;
}

//---------------------------------------------------------------------//
void DeleteMatrix( double*** pTab, int nDim ) {//usun macierz
	double** v = *pTab;
	for( int i = 0; i < nDim; i++ ) free( *v++ );
	free( *pTab );
	*pTab = NULL;
}

//---------------------------------------------------------------------//
double Det( double** pTab, int nDim ){//wyznacznik //rozwiniecie wzgl 0-go wiersza 
	if( nDim == 1 )return **pTab;
	if( nDim == 2 ) return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];// dla 2x2 uzyc znanego wzoru - mozna zaindeksowac
	double** t = NULL;
	if( !CreateMatrix( &t, nDim - 1 ) ) {
		printf( "Blad w tworzeniu tablicy pomocniczej w funkcji det()\n" );
		return 0;
	}
	double det = 0;
	double sgn = 1;
	double* p = *pTab;
	for( int i = 0; i < nDim; i++ ) {
		Complement( t, pTab, 0, i, nDim );
		det += *p++ * Det( t, nDim - 1 ) * sgn;//wyznacznik laplace rekurencyjnie
		REVSGN( sgn );
	}
	DeleteMatrix( &t, nDim - 1 );
	return det;
} 

//---------------------------------------------------------------------//
void InverseMatrix( double** pInv, double** pTab, int nDim, double det ) {
	ComplMatrix( pInv, pTab, nDim );
	TransMatrix( pInv, nDim );
	for( int i = 0; i < nDim; i++ ) {
		double* p = *pInv++;
		for( int j = 0; j < nDim; j++ ) *p++ /= det;
	}
}// macierz odwrotna, na we obliczony wczesniej w main() det  (tu w funkcji juz na pewno musi byc det!=0)

//---------------------------------------------------------------------//
void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim ) {
	for( int i = 0; i < nDim; i++, pRes++ ) {
		double* p = *pInv++;
		double* pT = pB;
		for( int j = 0; j < nDim; j++ ) *pRes +=  *(pT++) * *(p++);
	}
}  // rozwiazuje ukl rownan

//---------------------------------------------------------------------//
void PrintMatrix( double** pTab, int nDim ) {
	for( int i = 0; i < nDim; i++ ) {
		double* k = *pTab++;
		for( int j = 0; j < nDim; j++ ) {
			printf( "%.2lf ", *k++ );
		} printf( "\n" );
	} printf( "\n" );
}