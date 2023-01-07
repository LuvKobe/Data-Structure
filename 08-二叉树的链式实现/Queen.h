#pragma once
/*
数组结构：1  2  3  4

链式结构：1   2   3   4
		对头         队尾（记录一个尾指针）
		出队列       入队列
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//前置声明：告诉编译器，这是一个结构体，先给个声明，它的定义在其他地方，后面再去找具体的定义
struct BinaryTreeNode;

typedef struct BinaryTreeNode* QDataType;

//这个是定义的节点，用于表示整个队列
typedef struct QueueNode
{
	QDataType data;
	struct QueneNode* next;
}QNode;

//这个是定义的头指针和尾指针，方便队头出数据，队尾入数据
typedef struct Queue
{
	QNode* head;
	QNode* tail;
}Queue;


void QueueInit(Queue* pq); //初始化

void QueueDestory(Queue* pq); //销毁

void QueuePush(Queue* pq, QDataType x); //尾插（队尾入数据）

void QueuePop(Queue* pq); //头删（队头出数据）

bool QueueEmpty(Queue* pq); //判空

size_t QueueSize(Queue* pq); //队列元素个数

QDataType QueueFront(Queue* pq); //获取队头数据

QDataType QueueBack(Queue* pq); //获取队尾数据


