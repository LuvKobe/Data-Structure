#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int HPDataType; //堆中存储数据的类型

typedef struct Heap
{
	HPDataType* a; //用于存储数据的数组
	int size; //记录堆中已有元素个数
	int capacity; //记录堆的容量
}HP;

// 堆的初始化
void HeapInit(HP* php);

// 堆的打印
void HeapPrint(HP* php);

// 节点交换
void Swap(HPDataType* pa, HPDataType* pb);


//向上调整 --> 建小堆
void AdjustUp1(HPDataType* a, int child);

//向上调整 --> 建大堆
void AdjustUp2(HPDataType* a, int child);

// 堆的插入
void HeapPush(HP* php, HPDataType x);


// 向下调整 --> 调小堆
void AdjustDown1(HPDataType* a, int size, int root);

// 向下调整 --> 调大堆
void AdjustDown2(HPDataType* a, int size, int root);

// 堆的删除
void HeapPop(HP* php);


// 取堆顶的数据
HPDataType HeapTop(HP* php);

// 堆的数据个数
int HeapSize(HP* php);

// 堆的判空
bool HeapEmpty(HP* php);

// 堆的销毁
void HeapDestory(HP* php);
