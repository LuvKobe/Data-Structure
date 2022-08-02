#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void TestSList1() {
	SeqList s;

	SListInit(&s); //初始化结构体

	/*尾插*/
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);

	/*头插*/
	SListPushFront(&s, 6);
	SListPushFront(&s, 5);
	SListPushFront(&s, 4);

	/*打印*/
	SListPrint(&s);
}

void TestSList2() {
	SeqList s;

	SListInit(&s); //初始化结构体

	/*尾插*/
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);

	/*头插*/
	SListPushFront(&s, 6);
	SListPushFront(&s, 5);
	SListPushFront(&s, 4);

	/*打印*/
	SListPrint(&s);

	/*在1的前面位置插入10*/
	int pos = SListFind(&s, 1);
	SListInsert(&s, pos, 10);

	/*打印*/
	SListPrint(&s);

	/*删除在1的前面位置插入的10*/
	SListErase(&s, pos);

	/*打印*/
	SListPrint(&s);

	/*使用完以后，销毁顺序表*/
	SListDestroy(&s);
}

int main()
{
	TestSList2();
	return 0;
}