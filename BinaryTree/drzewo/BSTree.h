#pragma once


typedef struct tagTreeItem{
	int nKey;
	tagTreeItem* pLeft;
	tagTreeItem* pRight;
}TreeItem;

tagTreeItem* findAndInsert(TreeItem* pRoot, int value);

void preOrder( TreeItem* pRoot );
void inOrder( TreeItem* pRoot );
void postOrder( TreeItem* pRoot );

void FreeTree( TreeItem* pRoot );

