#include <stdio.h>
#include <stdlib.h>
#include "PQueue.h"
#include <time.h>

#define SIZE 20
#define MAX 100

#define SIZE2 5

void PrintQueue( const void* );
int Comp( const void* item1, const void* item2 );
void FreeMem( const void* );
PQINFO* CreateInfo();


//funkcje pomocnicze do generowanie priorow
int contains( int* tab, int size, int value );
void geneartePrior( int* tab, int size );
int findMax(int* tab, int size);


int main()
{	

	PQueue* queue = PQCreate( SIZE );
	if( !queue ) {
		printf( "Error creating queue main1" );
		return -1;
	}

	int prior[8];
	geneartePrior( prior, 8 );//tablica losowych unikalnych priorytetow

	srand( (unsigned int)time( NULL ) );

	for( int i = 0; i < 6; i++ ) {
		PQINFO* pInfo = CreateInfo();
		if( !pInfo ) {
			printf( "error creating info1\n" );
			return -2;
		}
		if( !PQEnqueue( queue, pInfo, prior[i] ) ) {
			printf( "error enqueueing info1\n" );
			return -3;
		}
	}

	
	printf( "Po wygenerowaniu 6 losowych elemntow\n\n" );
	PQPrint( queue, 0, PrintQueue );
	printf( "\n\n" );

	
	PQINFO* ptr = PQDequeue( queue );

	if( !ptr ) {
		printf( "queue is empty!!\n" );
		//return -4;
	}
	else {
		//wypisac klucz usunietego// zwolnic pamiec
		printf(" key deleted :%d\n\n", ptr->nKey);
		FreeMem( ptr );
	}

	printf( "Po usunieciu elemntu z najwiekszym priorytetem:\n\n" );
	PQPrint( queue, 0, PrintQueue );
	printf( "\n\n" );
	

	PQINFO* pInfo7 = CreateInfo();
	if( !pInfo7 ) {
		printf( "error creating info8\n" );
		return -7;
	}
	pInfo7->nKey = 77;
	if( !PQEnqueue( queue, pInfo7, prior[6] ) ) {
		printf( "error enqueueing info7\n" );
		return -77;
	}


	PQINFO* pInfo8 = CreateInfo();
	if( !pInfo8 ) {
		printf( "error creating info8\n" );
		return -8;
	}
	pInfo8->nKey = 88;
	if( !PQEnqueue( queue, pInfo8, prior[7] ) ) {
		printf( "error enqueueing info8\n" );
		return -88;
	}

	printf( "po dodaniu dwoch (juz ustalonych elementow, zeby bylo latwiej wykonac nastepne kroki) elemntow o loswych priorytetach\n" );
	printf( "dodane elementy to nKey=77 i nKey=88\n\n" );
	PQPrint( queue, 0, PrintQueue );
	printf( "\n\n" );

	int n1 = PQFind( queue, pInfo7, Comp ); //wyszukiwanie nkey=77
	
	int i1 = 1;
	while( contains( prior, SIZE, prior[6]+i1 ) ) i1++; // zwiekszanie priorytetu na nKey=77 w taki sposob zeby byl unikalny

	if( !PQsetPrior( queue, n1, prior[6] + i1 ) ) {
		printf( "error setting new prior1!!\n" );
		return -9;
	}//spr!!!
	printf( "Zwiekszenie priorytetu nKey=77, na unikalny, wiekszy\n\n" );
	PQPrint( queue, 0, PrintQueue ); 
	printf( "\n\n" );



	int n2 = PQFind( queue, pInfo8, Comp ); //wyszukiwanie nkey=88

	int i2 = -1;
	while( contains( prior, SIZE, prior[7] + i2 ) ) i2--; // zmniejszenie priorytetu na nKey=88 w taki sposob zeby byl unikalny

	if( !PQsetPrior( queue, n2, prior[7] + i2 ) ) {
		printf( "error setting new prior2!!\n" );
		return -10;
	}
	printf( "Zmniejszenie priorytetu nKey=88, na unikalny, mniejszy\n\n" );
	PQPrint( queue, 0, PrintQueue );
	printf( "\n\n" );

	PQRelease( &queue, FreeMem );
	printf( "-----------------------------------------------------------------------------------\n\n" );
	///////---------------------------------koniec czesci oficjalnej----------------------/////////////

	PQueue* queue1 = PQCreate( SIZE );
	int prior1[SIZE2];
	geneartePrior( prior1, SIZE2 );//tablica losowych unikalnych priorytetow
	for( int i = 0; i < sizeof( prior1 ) / sizeof( int ); i++ ) printf( "%d ", prior1[i] );


	printf( "\n\nMax w prior1 to %d \n\n", findMax( prior1, SIZE2 ) );

	srand( (unsigned int)time( NULL ) );
	for( int i = 0; i < SIZE2; i++ ) {
		PQINFO* pInfo = CreateInfo();
		if( !pInfo ) {
			printf( "error creating info2\n" );
			return -11;
		}
		if( !PQEnqueue( queue1, pInfo, prior1[i] ) ) {
			printf( "error enqueueing info2\n" );
			return -13;
		}
	}
	PQPrint( queue1, 0, PrintQueue );
	printf( "\n\n" );

	PQINFO* pInfo77 = CreateInfo();
	pInfo77->nKey = 77;
	pInfo77->pTab[0] = rand() % SIZE;
	PQEnqueue( queue1, pInfo77, findMax( prior1, SIZE2 ) );
	PQINFO* pInfo88 = CreateInfo();
	pInfo88->nKey = 88;
	pInfo88->pTab[0] = rand() % SIZE;
	PQEnqueue( queue1, pInfo88, findMax( prior1, SIZE2 ) );

	PQPrint( queue1, 0, PrintQueue );
	printf( "\n\n" );

	PQDequeue( queue1 );
	PQPrint( queue1, 0, PrintQueue );
	printf( "\n\n" );
	PQDequeue( queue1 );
	PQPrint( queue1, 0, PrintQueue );
	printf( "\n\n" );
	PQDequeue( queue1 );
	PQPrint( queue1, 0, PrintQueue );
	printf( "\n\n" );


	PQRelease( &queue1, FreeMem );


	return 0;
}



void FreeMem( const void* Info ) {
	free( ((PQINFO*)Info)->pTab );
	free( (PQINFO*)Info );
}

int Comp( const void* item1, const void* item2 ) {
	if( ((PQINFO*)item1)->nKey < ((PQINFO*)item2)->nKey )return -1;//*-1 if the first item is less then the second one
	if( ((PQINFO*)item1)->nKey == ((PQINFO*)item2)->nKey )return 0;//* 0 if both items are equels
	return 1;//* 1 if the first item is greater than the second one
}

void PrintQueue( const void* pTab ) {
	PQINFO* n = (PQINFO*)pTab;
	printf( "nKey: %d, 1st element: %d  ", n->nKey, n->pTab[0] );
}

PQINFO* CreateInfo() {
	PQINFO* p = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
	if( !p ) {
		printf( "ERROR CREATING INFO1" );
		return NULL;
	}
	p->pTab = (int*)calloc( 2, sizeof( int ) );
	if( !(p->pTab) ) {
		printf( "ERROR CREATING INFO2" );
		return NULL;
	}
	p->nKey = rand() % MAX;
	p->pTab[0] = rand() % SIZE;
	return p;
}
// naglowek funkcji drukujacej info uzytkownika (parametr typu const void* )
// naglowek funkcji porownujacej info uzytkowniak. Zwraca -1 pierwszy mniejszy, 1 jesli pierwszy wiekszy else 0.
//          (parametry const void* )
// naglowek funkcji zwalniajacej pamiec (parametr typu const void* )



//funkcje pomocnicze do generowanie losowych unikalnych priorytetow
int findMax(int* tab, int size) {
	int max = *tab;
	while( --size > 0 ) if( *++tab > max ) max = *tab;
	return max;
}

int contains( int* tab, int size, int value ) {
	for( int i = 0; i < size; i++ ) if( *tab++ == value ) return 1;
	return 0;
}
void geneartePrior( int* tab, int size ){
	srand( (unsigned int)time( NULL ) );
	for( int i = 0; i < size; i++ ) {
		int random;
		do random = rand() % SIZE; while( contains( tab , i, random ) );
		tab[i] = random;
	}
}