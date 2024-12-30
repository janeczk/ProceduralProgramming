
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "index.h"

#define DEBUG__

int main( int argc, char** argv )
{
	if( argc != 2 ) {
		printf( "USAGE: %s <plik_we>\n", argv[0] );
		return 1;
	}
	FILE* fin = NULL;
	if( (fin = fopen( argv[1], "rt" )) == NULL ) {  //zdefiniowac _CRT_SECURE_NO_WARNINGS
		printf( "Error opening the file %s <plik_we>\n", argv[0] );
		return 4;
	}
	TreeItem* pRoot = NULL;
	
	WriteToTree( &pRoot, fin );//tu sie dzieje wszystko
	
	fclose( fin );

#ifdef DEBUG__
    printInOnder( pRoot );//
#endif // DEBUG

    FILE* fout = fopen( "Indeks.txt", "w" );

    if( !fout ) {
        printf( "Error opening uotput file!!\n" );
        FreeTree( pRoot );
        return -4;
    }

    writeInOrder( pRoot, fout );//
	fclose( fout );

	FreeTree( pRoot );//
	return 0;
}
