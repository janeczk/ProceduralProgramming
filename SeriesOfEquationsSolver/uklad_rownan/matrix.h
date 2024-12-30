#ifndef MATRIX_H
#define MATRIX_H


void TransMatrix( double** pTab, int nDim );//transponowanie
int  CreateMatrix( double*** pTab, int nDim );
void DeleteMatrix( double*** pTab, int nDim );
double Det( double** pTab, int nDim ); //wyznacznik laplace rekurencyjnie// dla 2x2 uzyc znanego wzoru - mozna zaindeksowac
void InverseMatrix( double** pInv, double** pTab, int nDim, double det );//// macierz odwrotna, na we obliczony wczesniej w main() det  (tu w funkcji juz na pewno musi byc det!=0)
void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim );  // rozwiazuje ukl rownan
void PrintMatrix( double** pTab, int nDim );



#endif
