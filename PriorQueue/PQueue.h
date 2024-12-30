#pragma once

#include "global.h"


#define PRIOR_ERROR INT_MIN
#define POS_ERROR -1

typedef struct   tagPQItem // zachowac oryginalne nazwy!!!!!!  
{
    PQINFO* pInfo;// pInfo;       // Ptr to user info  
    int nPrior;// nPrior;      // prior value (int) for the user info  
} PQItem;         // type of the queue item


typedef struct tagPQueue  // zachowac oryginalne nazwy!!!!!!
{
    PQItem* pPQueue;// pPQueue     // kolejka realizowana w postaci stogu  (dynamiczna tablica)
    int nPQSize;// nPQSize      // rozmiar calkowity kolejki priorytetowej
	int nPQCurrSize;// nPQCurrSize  // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce) 

} PQueue;

PQueue* PQCreate(int nSize);   // kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad

int PQisEmpty(PQueue* pQueue);  // zwraca 0 -nie pusta lub 1 - kolejka pusta

int PQSize( PQueue* pQueue );     // zwraca ilosc elementow w kolejce

int PQMaxPrior( PQueue* pQueue ); // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR

int PQEnqueue( PQueue* pQueue, PQINFO* pInfo, int nPrior );  // wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)

PQINFO* PQDequeue( PQueue* pQueue );  // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie

void PQClear( PQueue* pQueue, void( __cdecl* FreeMem )(const void*) );   
            // czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura 
              // do zwolnienia dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 

void PQRelease( PQueue** pQueue, void( __cdecl* FreeMem )(const void*) );
                // usuwa cala kolejke, zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto 
              // wczesniej (czyszczenie kolejki)

void PQPrint( PQueue* pQueue, int i, void( __cdecl* PrintQueue )(const void*) );
              // drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowaæ info uzytkownika 
              // przekazac trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach 
              // oraz pozycje w  kolejce w kwadratowych nawiasach

int PQSetPrior( PQueue* pQueue, PQINFO* pInfo, int nPrior, int( __cdecl* Comp )(const void*, const void*) );
                // ustawia nowy priorytet dla zadanej informacji uzytkownika, nie znana struktura informacji, która trzeba 
              // wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. 
              // Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR 

int PQsetPrior( PQueue* pQueue, int pos, int newP );
            // ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce 
              // (indeks w tablicy). Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR 

int PQGetPrior( PQueue* pQueue, PQINFO* pInfo, int( __cdecl* Comp )(const void*, const void*) ); // zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nie znana struktura informacji, która 
              // trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika  

int PQgetPrior( PQueue* pQueue, int pos ); // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR

int PQFind( PQueue* pQueue, PQINFO* pInfo, int( __cdecl* Comp )(const void*, const void*) ); 
                // zwraca indeks wyszukiwanej informacji uzytkownika, nie znana struktura informacji uzytkownika dlatego
                // przekazac trzeba funkjce porownujaca informacje uzytkownika
                // Zwaraca POS_ERROR jesli nie ma info w kolejce