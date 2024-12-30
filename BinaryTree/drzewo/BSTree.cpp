#include "BSTree.h"
#include <stdio.h>
#include <memory.h>
#include <malloc.h>


void Visit( TreeItem* pRoot ){} //wykonanie operacji na wierzcholku drzewa


TreeItem* findAndInsert( TreeItem* pRoot, int value ) {
	if( pRoot == NULL ) {
		pRoot = (TreeItem*)calloc( 1, sizeof( TreeItem ) );
		if( !pRoot ) return NULL;
		pRoot->nKey = value;
		//root->pLeft = root->pRight = NULL;   //calloc
		//return root;
	}
	else if( value < pRoot->nKey ) pRoot->pLeft = findAndInsert( pRoot->pLeft, value );
	else if( value > pRoot->nKey ) pRoot->pRight = findAndInsert( pRoot->pRight, value );
	else Visit( pRoot );

	return pRoot;
}

/*
void findAndInsert( TreeItem** pRoot, int value ) {
	if( *pRoot == NULL ) {
		*pRoot = (TreeItem*)calloc( 1, sizeof( TreeItem ) );
		if( !*pRoot ) return;
		(*pRoot)->nKey = value;
		//root->pLeft = root->pRight = NULL;   //calloc
	//	return root;
	}
	else if( value < pRoot->nKey ) findAndInsert( &((*pRoot)->pLeft), value );
	else if( value > pRoot->nKey ) findAndInsert( &((*pRoot)->pRight), value );
	else Visit( pRoot );
	//return pRoot;
}
*/

void preOrder( TreeItem* pRoot ) {
	if( !pRoot ) return;
	printf( "%d  ", pRoot->nKey );
	preOrder( pRoot->pLeft );
	preOrder( pRoot->pRight );
}
void inOrder( TreeItem* pRoot ) {
	if( !pRoot ) return;
	inOrder( pRoot->pLeft );
	printf( "%d  ", pRoot->nKey );
	inOrder( pRoot->pRight );

}
void postOrder( TreeItem* pRoot ) {
	if( !pRoot ) return;
	postOrder( pRoot->pLeft );
	postOrder( pRoot->pRight );
	printf( "%d  ", pRoot->nKey );
}

void FreeTree( TreeItem* pRoot ) {
	if( !pRoot )return;
	FreeTree( pRoot->pLeft );
	FreeTree( pRoot->pRight );
	free( pRoot );
}