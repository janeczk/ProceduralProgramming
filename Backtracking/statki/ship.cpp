#include "ship.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


int move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot );//funkcja lokalna



int move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot ) {
    // x  y - wsporzedne skad robimy nowy ruch
    //  wykonac kolejny ruch w kierunku move obliczajac nowe wspolrzedne *px *py
    //(switch)
    switch( move ) {
    case UP: *px = x - 1; *py = y; break;
    case DOWN: *px = x + 1; *py = y; break;
    case RIGHT: *px = x; *py = y + 1; break;
    case LEFT: *px = x; *py = y - 1; break;
    }
    //sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
    if( *px<0 || *px>=nRow || *py<0 || *py>=nCol )return 0;
    // a nastepnie sprawdzic warunek czy nie jest za plytko ">=nDepth " oraz
    if( pTab[*px][*py] <= nDepth )return 0;
    // czy nie bylo sie juz w lokalizacji (*px,*py) - wg tabl pRoot (wart 0 w nowej lokalicacji)
    if( pRoot[*px][*py] ) return 0;
    //    jesli wszystkie warunki poprawne to zwracamy 1
    return 1;
}

int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest ) {
    // tabl pRoot pamieta droge   -   numer ruchu pole przez ktore odwiedzono (plynie statek) 
    //                                0 pole nie odwiedzone
    // wstawic do tablicy pRoot kolejny numer ruchu
    static int n = 1;
    pRoot[x][y] = n++;
    if( x == x_dest && y == y_dest ) return 1;
    //else
// zdefiniowac nowe wspolrzende
    int px = x;
    int py = y;
     // sprwadzic wszystkie mozliwosci ruchu
        //jesli ruch jest mozliwy w zadanym kierunku 
           //jesli wykonanie kolejnego kroku sie powiodlo - rekurencyjnie root()
    for( int i = RIGHT; i <= LEFT; i++ ) {
        if( move( pTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) == 1 ) {
            if( root( pTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) == 1 )return 1;
        }
    }
    pRoot[x][y] = 0;
    n--;
    // jesli wracamy to ustawiamy w pRoot ze ruch byl zly
    return 0;

}

void clearRoot( int** pRoot, int nRow, int nCol ) {
    memset( pRoot, 0, nRow * nCol );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol ) {
    FILE* fin = NULL;
    if( (fin = fopen( sFile, "r" )) == NULL ) return 0;
    for( int i = 0; i < nRow; i++ ) {
        int* p = *pTab++;
        for( int j = 0; j < nCol; j++ ) fscanf( fin, "%d ", p++ );
    }
    fclose( fin );
    return 1;
}
