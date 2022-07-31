#define _CRT_SECURE_NO_WARNINGS 1
#include "List.h"

//增加一个节点
LTNode* BuyLTNode(LTDataType x) {
	LTNode* newnode = (LTNode*)malloc(sizeof(LTNode));
	if (newnode == NULL) {
		printf("malloc fail\n");
		exit(-1); // 终止程序
	}
	newnode->data = x;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}

//初始化1
/*
void ListInit(LTNode** pphead) {
	assert(pphead);
	//当只有一个节点时, 这个节点的前驱、后驱指针都指向自己
	*pphead = BuyLTNode(0);
	(*pphead)->next = *pphead;
	(*pphead)->prev = *pphead;
}*/

//双链表初始化
LTNode* ListInit() {
	LTNode* phead = BuyLTNode(0); // 申请一个头结点，不存储有效数据

	/*起始时只有头结点，让它的前驱和后继都指向自己*/
	phead->next = phead;
	phead->prev = phead;
	return phead; // 返回头结点
}

//双链表打印
void ListPrint(LTNode* phead) {
	assert(phead);

	LTNode* cur = phead->next; // 从头结点的后一个结点开始打印
	while (cur != phead) { // 当cur指针指向头结点时，说明链表全部打印完成
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

//双链表尾插
void ListPushBack(LTNode* phead, LTDataType x) {
	assert(phead);

	LTNode* tail = phead->prev; //尾节点就是头节点的前驱指针
	LTNode* newnode = BuyLTNode(x); // 申请一个结点，数据域赋值为x

	/*建立新结点与头结点之间的双向关系*/
	newnode->next = phead;
	phead->prev = newnode;

	//建立新结点与tail结点之间的双向关系
	tail->next = newnode;
	newnode->prev = tail;
}

//尾插2-升级
/*
void ListPushBack(LTNode* phead, LTDataType x) {
	assert(phead);

	//在phead前面插入一个，相当于尾插
	ListInsert(phead, x);
}*/

//双链表尾删
void ListPopBack(LTNode* phead) {
	assert(phead);
	assert(phead->next != phead); //检查链表是否为空

	LTNode* tail = phead->prev;
	LTNode* newTail = tail->prev;

	free(tail);
	tail = NULL;

	newTail->next = phead;
	phead->prev = newTail;
}

//尾删2-升级
/*
void ListPopBack(LTNode* phead) {
	assert(phead);
	ListErase(phead->prev);
}*/


//双链表头插
void ListPushFront(LTNode* phead, LTDataType x)
{
	assert(phead);

	LTNode* newnode = BuyLTNode(x); // 申请一个结点，数据域赋值为 x
	LTNode* after = phead->next; // 记录头结点的后一个结点位置

	/*建立新结点与头结点之间的双向关系*/
	phead->next = newnode;
	newnode->prev = phead;

	//建立新结点与beHind结点之间的双向关系
	newnode->next = after;
	after->prev = newnode;
}

//头插2-升级
/*
void ListPushFront(LTNode* phead, LTDataType x) {
	assert(phead);
	ListInsert(phead->next, x);
}*/


//双链表头删
void ListPopFront(LTNode* phead)
{
	assert(phead);
	assert(phead->next != phead);

	LTNode* after = phead->next; // 记录头结点的后一个结点
	LTNode* newAfter = after->next; // 记录after结点的后一个结点

	/*建立头结点与newAfter结点之间的双向关系*/
	phead->next = newAfter;
	newAfter->prev = phead;

	free(after); // 释放after结点
}

//头删2-升级
/*
void ListPopFront(LTNode* phead) {
	assert(phead);
	assert(phead->next != NULL); //只有一个节点的时候，就别删了

	ListErase(phead->next);
}*/


//双向链表查找
LTNode* ListFind(LTNode* phead, LTDataType x) {
	assert(phead);

	LTNode* cur = phead->next; // 从头结点的后一个结点开始查找
	while (cur != phead) { // 从头结点的后一个结点开始查找
		if (cur->data == x) {
			return cur; // 返回目标结点的地址
		}
		cur = cur->next;
	}
	return NULL; // 没有找到目标结点
}


//双向链表在pos的前面进行插入
void ListInsert(LTNode* pos, LTDataType x) {
	assert(pos);

	LTNode* newnode = BuyLTNode(x); // 申请一个结点，数据域赋值为x
	LTNode* posPrev = pos->prev; // 记录 pos 指向结点的前一个结点

	/*建立新结点与posPrev结点之间的双向关系*/
	posPrev->next = newnode;
	newnode->prev = posPrev;


	/*建立新结点与pos指向结点之间的双向关系*/
	newnode->next = pos;
	pos->prev = newnode;
}


//双向链表删除pos位置的节点
void ListErase(LTNode* pos) {
	assert(pos); //pos不为空

	LTNode* posPrev = pos->prev; // 记录pos指向结点的前一个结点
	LTNode* posNext = pos->next; // 记录pos指向结点的后一个结点

	free(pos); //free是把指针指向的节点还给操作系统
	pos = NULL;

	/*建立posPrev结点与posNext结点之间的双向关系*/
	posPrev->next = posNext;
	posNext->prev = posPrev;
}

//双向链表判空
bool ListEmpty(LTNode* phead)
{
	assert(phead);
	return phead->next == phead; // 当链表中只有头结点时为空
}

//获取双链表中的元素个数
int ListSize(LTNode* phead)
{
	assert(phead);

	int count = 0; // 记录元素个数
	LTNode* cur = phead->next; // 从头结点的后一个结点开始遍历
	while (cur != phead) // 当cur指向头结点时，遍历完毕，头结点不计入总元素个数
	{
		count++;
		cur = cur->next;
	}
	return count; //返回元素个数
}

//双链表销毁
void ListDestory(LTNode* phead) {
	assert(phead);
	LTNode* cur = phead->next; // 从头结点后一个结点开始释放空间

	while (cur != phead) {
		LTNode* next = cur->next; // 释放之前先保存cur的后一个结点位置
		free(cur);
		cur = next; // 把cur的下一个赋给cur
	}
	free(phead); // 最后释放哨兵结点
	phead = NULL;
}
