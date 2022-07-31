#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// .h 放声明，用来看整个框架

// assert断言 -->  条件为真，就没什么事；如果条件为假，就终止程序并报错，会精确的告诉你，那个文件的那一行出错了
// return;  --> 结束函数
// exit(-1) --> 结束程序


// 要求存储的数据是从0开始，依次连续存储
// 静态的顺序表
// 问题：开小了，不够用；开大了，存在浪费

//#define N 100
//struct SeqList
//{
//	int a[N]; 
//	int size; // 记录存储了多少个数据
//};


// SL：SeqList的缩写
// DataType：数据类型
typedef int SLDataType;

// 动态的顺序表
typedef struct SeqList
{
	SLDataType* a; // 指向动态开辟的数组
	int size; // 存储的数据个数
	int capacity; // 存储空间的大小
}SeqList;


// 打印顺序表
void SeqListPrint(SeqList* psl);

// 顺序表初始化
void SeqListInit(SeqList* psl);


// 尾插和尾删：时间复杂度O(1)
// 顺序表尾插
void SeqListPushBack(SeqList* psl, SLDataType x);
// 顺序表尾删
void SeqListPopBack(SeqList* psl);


// 头插和头删：时间复杂度O(N)
// 顺序表头插
void SeqListPushFront(SeqList* psl, SLDataType x);
// 顺序表头删
void SeqListPopFront(SeqList* psl);

// 检查空间，如果满了，进行增容
void SeqListCheckCapacity(SeqList* psl);

// 在pos位置插入x
void SeqListInsert(SeqList* psl, size_t pos, SLDataType x);
//删除pos位置的数据
void SeqListErase(SeqList* psl, size_t pos);

// 顺序表查找
int SeqListFind(SeqList* psl, SLDataType x);
// 顺序表修改
//void SeqListModify(SeqList* psl, size_t pos, SLDataType x);

// 顺序表销毁
void SeqListDestroy(SeqList* psl);


