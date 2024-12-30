#ifndef SHIP_H
#define SHIP_H

typedef enum { RIGHT, DOWN, UP, LEFT }Move;

int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest );

void clearRoot( int** pRoot, int nRow, int nCol );

int setTab( char* sFile, int** pTab, int nRow, int nCol );

#endif
