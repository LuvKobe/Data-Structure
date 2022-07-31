#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// 数据结构存数据都是在堆上动态申请的
// 栈的空间一般只有8M，大概800多万字节
// 堆的空间一般能上亿，32位下，堆一般有2G，也就是20几亿字节

typedef int SLTDateType;

typedef struct SListNode
{
	SLTDateType data;
	struct SListNode* next; // 指向下一个节点的指针
}SLTNode;

// 1.打印单链表
void SListPrint(SLTNode* phead);

// 2.单链表尾插
void SListPushBack(SLTNode** pphead, SLTDateType x); 

// 3.单链表头插
void SListPushFront(SLTNode** pphead, SLTDateType x);

// 4.单链表尾删
void SListPopBack(SLTNode** pphead);

// 5.单链表头删
void SListPopFront(SLTNode** pphead);

// 6.单链表查找
SLTNode* SListFind(SLTNode* phead, SLTDateType x);

// 7.在pos位置插入元素
void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDateType x);

// 8.删除pos位置的值
void SListErase(SLTNode** pphead, SLTNode* pos);

// 9.在pos位置的后面插入元素
void SListInsertAfter(SLTNode* pos, SLTDateType x);

// 10.删除pos位置后面的一个值
void SListEraseAfter(SLTNode* pos);

// 11. 单链表销毁
void SListDestroy(SLTNode** pphead);





