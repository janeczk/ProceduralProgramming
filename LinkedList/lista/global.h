#pragma once

typedef struct{
	int nKey;
	int* p;
}ListInfo;
#define LISTINFO ListInfo

void  FreeMem( const void* );
int Comp( const void*, const void* );
