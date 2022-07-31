#define _CRT_SECURE_NO_WARNINGS 1
#include "List.h"

void TestList1() {
	/*
	初始化1
	LTNode* phead = NULL;
	ListInit(&phead); //传地址过去
	*/

	//初始化2
	LTNode* plist = ListInit();
	//尾插↓
	ListPushBack(plist, 1);
	ListPushBack(plist, 2);
	ListPushBack(plist, 3);
	ListPushBack(plist, 4);
	ListPushBack(plist, 5);
	ListPushBack(plist, 6);
	//打印↓
	ListPrint(plist);

	//尾删
	ListPopBack(plist);
	ListPopBack(plist);
	ListPopBack(plist);
	ListPopBack(plist);
	ListPopBack(plist);
	ListPopBack(plist);
}


void TestList2() {
	LTNode* plist = ListInit();
	//尾插↓
	ListPushBack(plist, 1);
	ListPushBack(plist, 2);
	ListPushBack(plist, 3);
	ListPushBack(plist, 4);
	ListPushBack(plist, 5);
	ListPushBack(plist, 6);

	//在3的前面插入30
	LTNode* pos = ListFind(plist, 3);
	ListInsert(pos, 30);
	ListPrint(plist);
}

void TestList3() {
	LTNode* plist = ListInit();
	//尾插↓
	ListPushBack(plist, 1);
	ListPushBack(plist, 2);
	ListPushBack(plist, 3);
	ListPushBack(plist, 4);
	ListPushBack(plist, 5);
	ListPushBack(plist, 6);

	//删除3
	LTNode* pos = ListFind(plist, 3);
	ListErase(pos);
	ListPrint(plist);

}


void TestList4() {
	LTNode* plist = ListInit();
	//尾插↓
	ListPushBack(plist, 1);
	ListPushBack(plist, 2);
	ListPushBack(plist, 3);
	ListPushBack(plist, 4);
	ListPushBack(plist, 5);
	ListPushBack(plist, 6);

	//尾删 - 删除3
	ListPopBack(plist);
	ListPrint(plist);
}

void TestList5() {
	LTNode* plist = ListInit();
	//头插↓
	ListPushFront(plist, 1);
	ListPushFront(plist, 2);
	ListPushFront(plist, 3);
	ListPushFront(plist, 4);
	ListPushFront(plist, 5);
	ListPushFront(plist, 6);
	ListPrint(plist);

	//头删 - 删除1
	ListPopFront(plist);
	ListPrint(plist);

	ListDestory(plist);
	plist = NULL;
}

int main()
{
	TestList5();
	return 0;
}