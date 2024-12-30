#include "PQueue.h"
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>



#define ISPQEMPTY( pQueue, Action ) ((!pQueue) ? (PRIOR_ERROR) : (Action))


void UpdateDown( PQItem* pTab, int l, int p );  // update heap down between index l and p  <--- modified Update() from HeapSort 
void UpdateUp( PQItem* pTab, int l, int p );    // update heap up between index l and p  




PQueue* PQCreate( int nSize ) {
    if( nSize < 1 ) return NULL;
    PQueue* Prior = (PQueue*)calloc( 1, sizeof(PQueue) );
    if( !Prior ) return NULL;
    Prior->pPQueue = (PQItem*)calloc( nSize, sizeof( PQItem ) );
    if( !(Prior->pPQueue) ) return NULL;
    Prior->nPQSize = nSize;
    return Prior;
}   // kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad

int PQisEmpty( PQueue* pQueue ) {
    return (!pQueue || !(pQueue->nPQCurrSize)); 
}  // zwraca 0 -nie pusta lub 1 - kolejka pusta

int PQSize( PQueue* pQueue ) {
    return ISPQEMPTY( pQueue, pQueue->nPQCurrSize );
}     // zwraca ilosc elementow w kolejce

int PQMaxPrior( PQueue* pQueue ) {
    return ISPQEMPTY( pQueue, PQgetPrior( pQueue, 0 ) );
} // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR

int PQEnqueue( PQueue* pQueue, PQINFO* pInfo, int nPrior ) {
    if( !pQueue ) return 0;
    int n = PQSize( pQueue );
    if( n >= pQueue->nPQSize ) return 0;
    pQueue->pPQueue[n].nPrior = nPrior;// wstawic na koncu
    pQueue->pPQueue[n].pInfo = pInfo;
    if( n > 0 )UpdateUp( pQueue->pPQueue, 0, n);// uaktualnic w gore 
    ++(pQueue->nPQCurrSize);
    return 1;
} // wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)

PQINFO* PQDequeue( PQueue* pQueue ) {
    if( PQisEmpty( pQueue ) ) return NULL;
    int n = --(pQueue->nPQCurrSize);
    PQINFO* res = pQueue->pPQueue[0].pInfo;
    if( n > 0 )pQueue->pPQueue[0] = pQueue->pPQueue[n];
    memset( pQueue->pPQueue + n, 0, sizeof( PQItem ) );
    if( PQSize( pQueue ) > 1 )UpdateDown( pQueue->pPQueue, 0, n -1);
    return res;
}  // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie
  

void PQClear( PQueue* pQueue, void( __cdecl* FreeMem )(const void*) ) {
    if( !pQueue || !FreeMem ) { printf( "There is no queue or FreeMem (PQClear)\n" ); return; }
    while( PQisEmpty( pQueue ) ) FreeMem( PQDequeue( pQueue ) );
}
// czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura 
  // do zwolnienia dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 

void PQRelease( PQueue** pQueue, void( __cdecl* FreeMem )(const void*) ) {
    if( !pQueue || !(*pQueue) ) { printf( "There is no Queue(Release)\n" ); return; }
    PQClear( *pQueue, FreeMem );
    free( (*pQueue)->pPQueue );
    free( *pQueue );
    *pQueue = NULL;
}
// usuwa cala kolejke, zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto 
// wczesniej (czyszczenie kolejki)

void PQPrint( PQueue* pQueue, int i, void( __cdecl* PrintQueue )(const void*) ) {
    if( i < 0 ) { printf( "Size can't be negative!(print)\n" ); return; }
    if( !pQueue || !PrintQueue ) { printf( "Queue doesn't exist(print) or no PrintFunc\n" ); return; }
    if( i < PQSize( pQueue ) ) {
        PrintQueue( (const void*)pQueue->pPQueue[i].pInfo );
        printf( "Prior of element: (%d) , Position of element: [%d]\n", pQueue->pPQueue[i].nPrior, i );
        PQPrint( pQueue, 2 * i + 1, PrintQueue );
        PQPrint( pQueue, 2 * i + 2, PrintQueue );
    }
}
// drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowaæ info uzytkownika 
// przekazac trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach 
// oraz pozycje w  kolejce w kwadratowych nawiasach

int PQSetPrior( PQueue* pQueue, PQINFO* pInfo, int nPrior, int( __cdecl* Comp )(const void*, const void*) ) {
    //if( ISPQEMPTY( pQueue, 1 ) == 1) {
    //   return PQsetPrior( pQueue, PQFind( pQueue, pInfo, Comp ), nPrior );
    //}return PRIOR_ERROR;
    return PQsetPrior( pQueue, PQFind( pQueue, pInfo, Comp ), nPrior );// ladniej :)
}
// ustawia nowy priorytet dla zadanej informacji uzytkownika, nie znana struktura informacji, która trzeba 
// wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. 
// Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR 

int PQsetPrior( PQueue* pQueue, int pos, int newP ) {
    if( PQisEmpty(pQueue) ) return PRIOR_ERROR;
    int res = PQgetPrior( pQueue, pos );
    if( res == POS_ERROR ) return PRIOR_ERROR;
    pQueue->pPQueue[pos].nPrior = newP;
    if( newP < res )UpdateDown( pQueue->pPQueue, pos, PQSize( pQueue ) - 1 );
    else if( newP > res )UpdateUp( pQueue->pPQueue, 0, pos );
    return 1;
}
// ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce 
  // (indeks w tablicy). Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR 

int PQGetPrior( PQueue* pQueue, PQINFO* pInfo, int( __cdecl* Comp )(const void*, const void*) ) {

    return PQgetPrior( pQueue, PQFind( pQueue, pInfo, Comp ) );
}
// zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nie znana struktura informacji, która 
  // trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika  

int PQgetPrior( PQueue* pQueue, int pos ) {
    if( PQisEmpty(pQueue) )return PRIOR_ERROR;
    if( pos < 0 || pos > pQueue->nPQCurrSize ) return POS_ERROR;
    return  pQueue->pPQueue[pos].nPrior;
} // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR

int PQFind( PQueue* pQueue, PQINFO* pInfo, int( __cdecl* Comp )(const void*, const void*) ) {
    if( !pQueue ) return PRIOR_ERROR;
    if( !Comp ) return POS_ERROR;
    for( int i = 0; i < PQSize( pQueue ); i++ ) {
        if( Comp( (const void*)pInfo, (const void*)pQueue->pPQueue[i].pInfo ) == 0 ) return i;
    }
    return POS_ERROR;
}
// zwraca indeks wyszukiwanej informacji uzytkownika, nie znana struktura informacji uzytkownika dlatego
// przekazac trzeba funkjce porownujaca informacje uzytkownika
// Zwaraca POS_ERROR jesli nie ma info w kolejce

void UpdateUp( PQItem* pTab, int l, int p ) {
    if( l >= p )return;
    int i = p;
    int j = (i - 1) / 2;
    PQItem temp = pTab[i];
    while( j >= l && pTab[j].nPrior < temp.nPrior ) {
        pTab[i] = pTab[j];
        i = j;
        j = (i + 1) / 2 - 1;//musi byc -1, bo indeksy zaczynaja sie od 0 i chcemy zlapac rodzica, a bez -1 petla bedzie nieskonczona bo nie zlapiemy j=-1 dla i=0
    }
    pTab[i] = temp;
}

void UpdateDown( PQItem* tab, int l, int p )
{
    if( l >= p ) return;
    int i = l;
    int j = 2 * i + 1;
    PQItem temp = tab[i];
    while( j <= p ){
        if( j < p && tab[j].nPrior < tab[j + 1].nPrior ) j++;
        if( temp.nPrior > tab[j].nPrior ) break;
        tab[i] = tab[j];
        i = j;
        j = 2 * i + 1;
    }
    tab[i] = temp;
}
