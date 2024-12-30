#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "BSTree.h"

#define MAX_TREE_ITEMS 15

int main()
{

	TreeItem* pRoot = NULL;
	srand( (unsigned int)time( NULL ) );
	for( int i = 0; i < MAX_TREE_ITEMS; i++ ) {
		pRoot = findAndInsert( pRoot, rand() % MAX_TREE_ITEMS );
	}
	inOrder( pRoot );
	FreeTree( pRoot );
	return 0;
}
