#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

//为了避免空和满 混淆，无法区分，那么可以多开一个空间
// head == tail时，就为空
// tail的下一个位置是head时，就是满。

//环形队列这里使用数组实现
//链表实现的话，找尾不好找

typedef int CQDataType;

typedef struct CircularQueue
{
	int* a; //队列
	int head; //头
	int tail; //尾
	int size; //存储数据个数
}CQ;

//环形队列初始化，设置队列长度为 k 
void CQueueInit(CQ* pcq, int k);

//入队列
void CQueuePush(CQ* pcq, CQDataType x);

//出队列
void CQueuePop(CQ* pcq);

//获取队头元素
CQDataType CQueueFront(CQ* pcq);

//获取队尾元素
CQDataType CQueueBack(CQ* pcq);

//检测队列是否为空
bool CQueueEmpty(CQ* pcq);

//检测队列是否满了
bool CQueueFull(CQ* pcq);

//销毁队列
void CQueueDestroy(CQ* pcq);