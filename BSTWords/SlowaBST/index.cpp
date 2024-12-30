#include "index.h"
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

tagTreeItem* findAndInsert( TreeItem* pRoot, char* value, int line );
tagTreeItem* CreateRoot( TreeItem* pRoot, char* value, int line );

int StrCmp( char* word1, char* word2 );

char* allocateWord( int size );
int relocate( char** word, int size );

int IsLetter( char c );
int IsAlpha( char c );
int IsDigit( char c );




void WriteToTree( TreeItem** pRoot, FILE* fin ) {
	int line = 1;
	int ch;
	while( (ch = fgetc( fin )) != EOF ) {//poczatek _Aa w srodku _aA1
		if( ch != '\n' ) {
			if( IsLetter( ch ) ) {

				char* word = allocateWord( SIZE );
				int i = 0;
				int size = 10;
				

				while( IsAlpha( ch ) ) {
					word[i++] = ch;
					ch = fgetc( fin );
					if( strlen( word ) % SIZE == 9 ) {
						int oSize = size;
						size += relocate( &word, size );
						if( oSize == size ) break;
						//size += SIZE;
						
					}
				}

				word[strlen( word )] = 0;
				*pRoot = findAndInsert( *pRoot, word, line );
				free( word );
			}
		} else line++;
	}
}

void Visit( TreeItem* pRoot, int line ) {
	pRoot->count++;

	if( line == pRoot->lines.pLast->line ) return; // wywalanie powtorzen

	ListItem* newItem = (ListItem*)calloc( 1, sizeof( ListItem ) );
	if( !newItem ) return;
	newItem->line = line;
	pRoot->lines.pLast->pNext = newItem;
	pRoot->lines.pLast = newItem;

}


TreeItem* CreateRoot( TreeItem* pRoot, char* value, int line ) {
	pRoot = (TreeItem*)calloc( 1, sizeof( TreeItem ) );//createRoot()
	if( !pRoot ) return NULL;
	pRoot->count = 1;

	pRoot->lines.pFirst = (ListItem*)calloc( 1, sizeof( ListItem ) );
	if( !pRoot->lines.pFirst ) return NULL;
	pRoot->lines.pFirst->line = line;
	pRoot->lines.pLast = pRoot->lines.pFirst;

	pRoot->pWord = allocateWord( (int)strlen( value ) + 1 );
	strcpy( pRoot->pWord, value );
	return pRoot;
}


TreeItem* findAndInsert(TreeItem* pRoot, char* value, int line) {
	if( !pRoot ) pRoot = CreateRoot( pRoot, value, line );
	else if( StrCmp( value, pRoot->pWord ) < 0 ) pRoot->pLeft = findAndInsert( pRoot->pLeft, value, line );
	else if( StrCmp( value, pRoot->pWord ) > 0 ) pRoot->pRight = findAndInsert( pRoot->pRight, value, line );
	else Visit( pRoot, line );
	return pRoot;
}

void FreeTree( TreeItem* pRoot ) {
	if( !pRoot )return;
	FreeTree( pRoot->pLeft );
	FreeTree( pRoot->pRight );
	free( pRoot->pWord );

	ListItem* curr = pRoot->lines.pFirst;
	while( curr ) {
		ListItem* next = curr->pNext;
		free( curr );
		curr = next;
	}

	free( pRoot );
}

int StrCmp( char* word1, char* word2 ) {
	char* copy1 = allocateWord( (int)strlen( word1 ) + 1 );
	char* copy2 = allocateWord( (int)strlen( word2 ) + 1 );

	strcpy( copy1, word1 );
	strcpy( copy2, word2 );

    copy1 = _strupr( copy1 );
    copy2 = _strupr( copy2 );

    int result = strcmp( copy1, copy2 );

	free( copy1 );
	free( copy2 );

    return result;
}

char* allocateWord( int size ) {
	return (char*)calloc( size , sizeof( char ) );
}

int relocate( char** word, int size ) {
	char* ptemp = *word;
	*word = (char*)realloc( *word, (size + SIZE) * sizeof( char ) );
	if( *word ) {
		memset( *word + size, 0, 10 * sizeof( char ) );
		//strcpy( *word, ptemp );
		return 10;
	}
	*word = ptemp;
	return 0;
}

void printInOnder( TreeItem* pRoot ) {
	if( !pRoot ) return;
	printInOnder( pRoot->pLeft );

	printf( "%-25s amount: %-7d Lines no.[", pRoot->pWord, pRoot->count );
	ListItem* curr = pRoot->lines.pFirst;
	int i = 0;
	while( curr ) {
		printf( " %d ", curr->line );
		if( curr->pNext ) printf( "," );
		curr = curr->pNext;
		if( i++ % 10 == 9 ) {
			printf( "\n %54d ", curr->line );
			if( curr->pNext ) printf( "," );
			curr = curr->pNext;
		}
	}
	printf( "]\n" );

	printInOnder( pRoot->pRight );
}
/*if( curr->pNext ) printf( "," );
		
		if( i++ % 10 == 9 ) {
			printf( "\n" );
			printf( " %-40d ", curr->line );
			curr = curr->pNext;
			continue;
		}
		printf( " %d ", curr->line );
		curr = curr->pNext;*/
void writeInOrder( TreeItem* pRoot, FILE* file ) {
	if( !pRoot ) return;

	static int first = 1;
	if( first ) {
		fprintf( file, "Slowo                | Ilosc wystapien |         | numery linii\n" );
		first = 0;
	}

	writeInOrder( pRoot->pLeft, file );
	fprintf( file, "%-30s %-15d [", pRoot->pWord, pRoot->count );
	ListItem* curr = pRoot->lines.pFirst;
	while( curr ) {
		fprintf( file, " %d ", curr->line );
		if( curr->pNext ) fprintf( file, "," );
		curr = curr->pNext;
	}
	fprintf( file, "]\n" );
	writeInOrder( pRoot->pRight, file );
}



int IsLetter( char c ) {
	return (c >= 'A') && (c <= 'Z') || (c >= 'a') && (c <= 'z') || (c == '_');
}

int IsAlpha( char c ) {
	return IsLetter( c ) || IsDigit( c );
}

int IsDigit( char c ) {
	return (c >= '0') && (c <= '9');
}

