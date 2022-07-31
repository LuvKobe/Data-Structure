#define _CRT_SECURE_NO_WARNINGS 1
#include "SList.h"
/*
顺序表的优点：

1、支持随机访问（用下标直接访问第i个）

有些算法支持随机访问：二分、快排



顺序表的缺点：

1、空间不够了，需要扩容，扩容是有消耗的（原地增容 或者 异地增容）

2、头部、尾部或者中间位置的插入删除，需要挪动数据，挪动数据也是有消耗的。

3、为了避免频繁扩容，一次一般都是按倍数去扩容（2倍），但是也存在一定空间的浪费。

针对顺序表缺陷，设计出了链表

a[i] 等价于 *(a+i)
*/


/*
链表优点：

1、按需申请空间，不用了就释放空间（更合理的使用了空间）

2、头部或者中间插入删除数据，不需要挪动数据

链表缺点：

1、每存一个数据，都需要存一个指针去链接后面的数据节点

2、不支持随机访问（用下标直接访问第i个）

*/

void TestSList1() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushBack(&plist, 1); // 尾插
	SListPushBack(&plist, 2); // 尾插
	SListPushBack(&plist, 3); // 尾插
	SListPushBack(&plist, 4); // 尾插
	SListPrint(plist);
	printf("\n"); // 换行

	SListPushFront(&plist, 1); // 头插
	SListPushFront(&plist, 2); // 头插
	SListPushFront(&plist, 3); // 头插
	SListPushFront(&plist, 4); // 头插
	SListPrint(plist);

}

void TestSList2() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushBack(&plist, 1); // 尾插
	SListPushBack(&plist, 2); // 尾插
	SListPushBack(&plist, 3); // 尾插
	SListPushBack(&plist, 4); // 尾插
	SListPrint(plist);
	printf("\n"); // 换行

	//SListPopBack(&plist); // 尾删
	//SListPopBack(&plist); // 尾删
	//SListPopBack(&plist); // 尾删
	//SListPopBack(&plist); // 尾删
	//SListPopBack(&plist); // 尾删

	SListPopFront(&plist);
	SListPrint(plist);
	printf("\n"); // 换行

	SListPopFront(&plist);
	SListPrint(plist);
	printf("\n"); // 换行

	SListPopFront(&plist);
	SListPrint(plist);
	printf("\n"); // 换行

	SListPopFront(&plist);
	SListPrint(plist);
}

void TestSList3() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushFront(&plist, 1); // 头插
	SListPushFront(&plist, 2); // 头插
	SListPushFront(&plist, 3); // 头插
	SListPushFront(&plist, 4); // 头插
	SListPushFront(&plist, 2); // 头插

	// 查找多个2的情况
	SLTNode* pos = SListFind(plist, 2);
	int i = 1;
	while (pos) {
		printf("第%d个pos节点：%p->%d\n", i++, pos, pos->data);
		pos = SListFind(pos->next, 2);
	}

	// 把3修改为30
	pos = SListFind(plist, 3);
	if (pos) {
		pos->data = 30;
	}
	SListPrint(plist);

}

// 在pos之前插入
void TestSList4() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushFront(&plist, 4); // 头插
	SListPushFront(&plist, 3); // 头插
	SListPushFront(&plist, 2); // 头插
	SListPushFront(&plist, 1); // 头插

	// 在 3 的前面插入一个 30
	SLTNode* pos = SListFind(plist, 3);
	if (pos) {
		SListInsert(&plist, pos, 30);
	}
	SListPrint(plist);

	// 在 1 的前面插入一个 30
	pos = SListFind(plist, 1);
	if (pos) {
		SListInsert(&plist, pos, 30);
	}
	SListPrint(plist);

}

// 在pos之后插入
void TestSList5() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushBack(&plist, 1); // 尾插
	SListPushBack(&plist, 2); // 尾插
	SListPushBack(&plist, 3); // 尾插
	SListPushBack(&plist, 4); // 尾插

	// 在 3 的后面插入一个 30
	SLTNode* pos = SListFind(plist, 3);
	if (pos) {
		SListInsertAfter(pos, 30);
	}
	SListPrint(plist);

	// 在 4 的后面插入一个 30
	pos = SListFind(plist, 1);
	if (pos) {
		SListInsertAfter(pos, 30);
	}
	SListPrint(plist);
}

// 在pos之后插入
void TestSList6() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushBack(&plist, 1); // 尾插
	SListPushBack(&plist, 2); // 尾插
	SListPushBack(&plist, 3); // 尾插
	SListPushBack(&plist, 4); // 尾插

	// 在 3 的后面插入一个 30
	SLTNode* pos = SListFind(plist, 3);
	if (pos) {
		SListInsertAfter(pos, 30);
	}
	SListPrint(plist);

	// 在 4 的后面插入一个 30
	pos = SListFind(plist, 1);
	if (pos) {
		SListInsertAfter(pos, 30);
	}
	SListPrint(plist);
}

// 在pos位置前删除元素
void TestSList7() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushBack(&plist, 1); // 尾插
	SListPushBack(&plist, 2); // 尾插
	SListPushBack(&plist, 3); // 尾插
	SListPushBack(&plist, 4); // 尾插
	SListPrint(plist);

	// 删除
	SLTNode* pos = SListFind(plist, 3);
	if (pos) {
		SListErase(&plist, pos);
	}
	SListPrint(plist);
}

// 删除pos位置后一个元素
void TestSList8() {
	SLTNode* plist = NULL; // 初始化头节点
	SListPushBack(&plist, 1); // 尾插
	SListPushBack(&plist, 2); // 尾插
	SListPushBack(&plist, 3); // 尾插
	SListPushBack(&plist, 4); // 尾插

	// 在 1 的位置删除 2
	SLTNode* pos = SListFind(plist, 1);
	if (pos) {
		SListEraseAfter(pos);
	}
	SListPrint(plist);
}

int main()
{
	//TestSList4();
	TestSList8();
	//TestSList5();
	return 0;
}