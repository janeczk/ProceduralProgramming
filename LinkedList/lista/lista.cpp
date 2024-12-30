#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

LISTINFO* CreateInfo( int i );
void PrintList( ListItem* pList );


int main()
{	
	ListItem* pList = CreateList();
	if( !pList ) { printf( "error creating list" ); return -1; }

	srand( (unsigned int)time( NULL ) );
	for( int i = 0; i < 20; i++ ) {
		LISTINFO* pInfo = CreateInfo(i);
		if( !pInfo ) { printf( "error creating info1" ); return -2; }
		if( i == 9 ) {
			pInfo->nKey = 2000; //wsadznie nKey na indeksie 9
			pInfo->p[0] = i;
		}
		if( !Insert( pList, pInfo ) ) {
			printf( "Error inserting info in main1\n" );
			return 2;
		}
	}
	//-------------------------------------
	printf( "Wygenerowana tablica:\n" );
	PrintList( pList );
	//---------------------------
	SortList( pList, Comp );	//posortować
	//-------------------------
	printf( "Posortowana tablica:\n" );
	PrintList( pList );
	//----------------------------
	LISTINFO* Key = CreateInfo(0);
	if( !Key ) { printf( "error creating Key" ); return -3; }
	Key->nKey = 2000;

	ListItem* pPrev = NULL;
	if( ListItem* pFind = Find( pList, Key, &pPrev, Comp ) ) {
		printf( "Znaleziony element to %d o indeksie %d\n\n", pFind->pInfo->nKey, pFind->pInfo->p[0] );
		if( !pFind->pInfo ) printf( "Znaleziony element jest pierwszy na lisice\n" );
		else printf( "Znaleziony element przed 2000 to %d o indeksie %d\n\n", pPrev->pInfo->nKey, pPrev->pInfo->p[0] );
	}  //szukanie elementu 2000

	LISTINFO* pInsert = CreateInfo(0);
	if( !pInsert ) { printf( "error creating insert" ); return -4; }
	pInsert->nKey = 3000;

	if( !Insert( pPrev, pInsert ) ) {//wstawianie 3000 przed 2000
		printf( "Error inserting info in main2\n" );
		return 3;
	}
	//-----------------------------
	printf( "Po wstawieniu 3000 przed 2000:\n" );
	PrintList( pList );
	//---------------------------
	Remove( pPrev->pNext );//usuniecie elementu po 3000 (czyli 2000)
	//-------------------------
	printf( "Po usunieciu 2000:\n" );
	PrintList( pList );
	//-------------------------
	ClearList( pList, FreeMem );//wyczyszczenie listy
	//---------------------------
	for( int i = 0; i < 2; i++ ) {
		LISTINFO* pInfo = CreateInfo(i);
		if( !pInfo ) { printf( "error creating info2" ); return -5; }
		if( !Insert( pList, pInfo ) ) {
			printf( "Error inserting info in main3" );
			return 4;
		}
	}
	//----------------
	printf( "Lista po wstawieniu dwoch lowosych elementow i wczesniejszym wyczyszczeniu listy:\n" );
	PrintList( pList );
	//-----------------
	RemoveList( &pList, FreeMem );
}


void FreeMem( const void* item ) {
	free( ((LISTINFO*)item)->p );
	free( (LISTINFO*)item );
}

int Comp( const void* item1, const void* item2 ) {//Function returns:
	if( ((LISTINFO*)item1)->nKey < ((LISTINFO*)item2)->nKey )return -1;//*-1 if the first item is less then the second one
	if( ((LISTINFO*)item1)->nKey == ((LISTINFO*)item2)->nKey )return 0;//* 0 if both items are equels
	return 1;//* 1 if the first item is greater than the second one
}

void PrintList( ListItem* pList ) {
	ListItem* temp = pList;
	while( !IsEmpty( temp ) ) {
		temp = temp->pNext;
		printf( "Item%d = %d\n", temp->pInfo->p[0], temp->pInfo->nKey);
	}
	printf( "\n\n" );
}

LISTINFO* CreateInfo( int i ) {
	LISTINFO* ptemp = (LISTINFO*)calloc( 1, sizeof( LISTINFO ) );
	if( !ptemp ) return NULL;
	ptemp->p = (int*)calloc( 2, sizeof( int ) );
	if( !(ptemp->p) )return NULL;
	ptemp->nKey = rand() % 50;
	ptemp->p[0] = i;
	return ptemp;
}