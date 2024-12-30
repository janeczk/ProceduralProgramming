#pragma once

#include <stdio.h>


#define SIZE 10

typedef struct ListItem {
	int line;
	ListItem* pNext;
}ListItem;

typedef struct ListHead {
	ListItem* pFirst;
	ListItem* pLast;
}ListHead;


typedef struct tagTreeItem {
	char* pWord;
	int count;
	ListHead lines;
	tagTreeItem* pLeft;
	tagTreeItem* pRight;
}TreeItem;


void writeInOrder( TreeItem* pRoot, FILE* file );//

void WriteToTree( TreeItem** pRoot, FILE* fin );//

void FreeTree( TreeItem* pRoot );//

void printInOnder( TreeItem* pRoot );//