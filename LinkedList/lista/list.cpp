#include "list.h"
#include <stdio.h>
#include <memory.h>
#include <malloc.h>

ListItem* CreateList() {
	return (ListItem*)calloc( 1, sizeof( ListItem ) );
}

int       Insert( ListItem* pAfter, LISTINFO* pInfo ) {
	if( !pAfter ) return 0;
	ListItem* ptemp = (ListItem*)calloc( 1, sizeof( ListItem ) );
	if( !ptemp ) return 0;
	ptemp->pInfo = pInfo;
	ptemp->pNext = pAfter->pNext;
	pAfter->pNext = ptemp;
	return 1;
} // insert po elemencie wskazywanym przez pAfter


LISTINFO* Remove( ListItem* pAfter ) {
	if( IsEmpty(pAfter) ) return NULL;
	ListItem* temp = pAfter->pNext;
	ListInfo* w = temp->pInfo;
	pAfter->pNext = temp->pNext;
	free( temp );
	return w;
}     // usun element po elemencie wsk przez pAfter

LISTINFO* Front( ListItem* pList ) {
	return !IsEmpty( pList ) ? pList->pNext->pInfo : NULL;
}        // zwraca wsk do informacji pierwszego (jak top() w stosie)

int       IsEmpty( ListItem* pList ) {
	return !pList || !(pList->pNext);
}     // 1 pusta,  0 -nie pusta  - nie uzywac if!

void      ClearList( ListItem* pList, void( __cdecl* FreeMem )(const void*) ) {
	if( !pList || !FreeMem ) {
		printf( "Error in clearList, no list or freemem \n" );
		return;
	}
	while( !IsEmpty( pList )) FreeMem( Remove( pList ) );
}
void      RemoveList( ListItem** pListA, void( __cdecl* FreeMem )(const void*) ) {
	if( !pListA || !*pListA ) {
		printf( "List doesnt exist in remove\n" );
		return;
	}
	ClearList( *pListA, FreeMem );
	free( *pListA );
	*pListA = NULL;
}
// after removing, set list as NULL

void      SortList( ListItem* pList, int( __cdecl* Comp )(const void*, const void*) ) {
	if( !Comp ) {
		printf( "Error in SortList, no compare function!!\n" );
		return;
	}
	ListItem* pFirst = pList;
	while( !IsEmpty( pFirst ) ) {
		ListItem* pMin = pFirst;
		ListItem* pCurr = pMin->pNext;
		while( !IsEmpty( pCurr ) ) {
			if( Comp( (const void*)(pMin->pNext->pInfo), (const void*)(pCurr->pNext->pInfo) ) == 1 ) pMin = pCurr;
			pCurr = pCurr->pNext;
		}
		if( pMin != pFirst ) {
			pCurr = pMin->pNext->pNext;
			pMin->pNext->pNext = pFirst->pNext;
			pFirst->pNext = pMin->pNext;
			pMin->pNext = pCurr;
		}
		pFirst = pFirst->pNext;
		}
}

ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl* Comp )(const void*, const void*) ) {
	if( !Comp ) return *pPrev = NULL;
	*pPrev = pList;
	while( !IsEmpty( *pPrev ) ) {
		if( Comp( (const void*)((*pPrev)->pNext->pInfo), pInfo ) == 0 ) return (*pPrev)->pNext;
		*pPrev = (*pPrev)->pNext;
	}return *pPrev = NULL; 
}
