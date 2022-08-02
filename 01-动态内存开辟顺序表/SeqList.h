#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;

typedef struct SeqList
{
	SLDataType* a;
	int size; //元素个数
	int capacity; //元素容量
}SeqList;

//初始化顺序表
void SListInit(SeqList* ps);

//打印顺序表
void SListPrint(SeqList* ps);

//尾插
void SListPushBack(SeqList* ps, SLDataType x);

//尾删
void SListPopBack(SeqList* ps);

//头插
void SListPushFront(SeqList* ps, SLDataType x);

//头删
void SListPopFront(SeqList* ps);

//顺序表查找
int SListFind(SeqList* ps, SLDataType x);

//顺序表在pos位置插入x
void SListInsert(SeqList* ps, int pos, SLDataType x);

//顺序表删除在pos位置的值
void SListErase(SeqList* ps, int pos);

void SListModify(SeqList* ps, int pos, SLDataType x);

//顺序表销毁
void SListDestroy(SeqList* ps);
