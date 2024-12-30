#pragma once


#include "global.h"

typedef struct tagListItem {
	LISTINFO* pInfo;
	tagListItem* pNext;
}ListItem;


ListItem* CreateList();

int       Insert( ListItem* pAfter, LISTINFO* pInfo ); // insert po elemencie wskazywanym przez pAfter

LISTINFO* Remove( ListItem* pAfter );      // usun element po elemencie wsk przez pAfter

LISTINFO* Front( ListItem* pList );        // zwraca wsk do informacji pierwszego (jak top() w stosie)

int       IsEmpty( ListItem* pList );     // 1 pusta,  0 -nie pusta  - nie uzywac if!

void      ClearList( ListItem* pList, void( __cdecl* FeeMem )(const void*) );
void      RemoveList( ListItem** pListA, void( __cdecl* FreeMem )(const void*) );
// after removing, set list as NULL

void      SortList( ListItem* pList, int( __cdecl* Comp )(const void*, const void*) );

ListItem* Find( ListItem* pList, const void* pInfo, ListItem** pPrev, int( __cdecl* Comp )(const void*, const void*) );
