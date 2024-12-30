#include "sort.h"

void update( int* pTab, int l, int p );
void quicksort( int* pTab, int l, int p );

void BubbleSort( int* pTab, int nSize ) {
	for ( int i = 0; i < nSize-1; i++ ) {
		for ( int j = nSize - 1; j > i; j-- ) {
			if ( pTab[j] < pTab[j - 1] ) {
				int temp = pTab[j];
				pTab[j] = pTab[j - 1];
				pTab[j - 1] = temp;
			}
		}
	}
}
void SimpleInsertionSort( int* pTab, int nSize ) {
	for ( int i = 1; i < nSize; i++ ) {
		int j = i - 1;
		int x = pTab[i];
		while ( j >= 0 && pTab[j] > x ) pTab[j + 1] = pTab[j--];
		pTab[j + 1] = x;
	}
}
void SimpleSelectionSort( int* pTab, int nSize ) {
	for ( int i = 0; i < nSize; i++ ) {
		int min = pTab[i];
		int ix = i;
		for ( int j = i + 1; j < nSize; j++ ) {
			if ( pTab[j] < min ) {
				min = pTab[j];
				ix = j;
			}
		}
		pTab[ix] = pTab[i];
		pTab[i] = min;
	}
}

void HalfInsertionSort( int* pTab, int nSize ) {
	for( int i = 1; i < nSize - 1; i++ ) {
		int temp = pTab[i];
		int p = i - 1;
		int j = 0;
		while( j <= p ) {
			int m = (j + p) / 2;
			if( temp < pTab[m] ) p = m - 1;
			else j = m + 1;
		}
		for( int k = i - 1; k >= j; k-- ) {
			pTab[k + 1] = pTab[k];
		}
		pTab[j] = temp;
	}
}

void MixedSort( int* pTab, int nSize ) {
	int k = nSize;
	int l = 1;
	int p = nSize - 1;
	do {
		for( int j = p; j >= l; j-- ) {
			if( pTab[j - 1] > pTab[j] ) {
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}
		l = k + 1;
		for( int j = l; j <= p; j++ ) {
			if( pTab[j - 1] > pTab[j] ) {
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}
		p = k - 1;
	} while( l <= p );
}
void HeapSort( int* pTab, int nSize ) {
	int p = nSize - 1;
	for( int i = nSize / 2; i >= 0; i-- ) update( pTab, i, p );
	for( ; p > 0; p-- ) {
		int temp = pTab[0];
		pTab[0] = pTab[p];
		pTab[p] = temp;
		update( pTab, 0, p - 1 );
	}
}
void QuickSort( int* pTab, int nSize ) {
	quicksort( pTab, 0, nSize - 1 );
}

void update( int* pTab, int l, int p ) {
	if( l > p ) return;
	int i = l;
	int j = 2 * i + 1;
	int temp = pTab[i];
	while( j <= p ) {
		if( j < p ) if( pTab[j] > pTab[j + 1] ) j++; 
		if( temp <= pTab[j] ) break; 
		pTab[i] = pTab[j];
		i = j;
		j = 2 * i + 1;
	}
	pTab[i] = temp;
}
void quicksort( int* pTab, int l, int p ) {
	int j = p;
	int i = l;
	int temp = pTab[(l + p) / 2];

	do {
		while( pTab[i] < temp ) i++;
		while( temp < pTab[j] ) j--;
		if( i <= j ) {
			int w = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = w;
			i++;
			j--;
		}
	} while( i <= j );
	if( j > l ) quicksort( pTab, l, j );
	if( i < p ) quicksort( pTab, i, p );
}

