#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*
栈：用动态内存开辟的数组实现

队列：用单链表实现。

单链表尾删、尾插，最大的问题在于，要找到尾，
所以我们可以记录一个尾指针，进行尾插
*/


// 队列用 "链式结构"，因为是在【队头】进行【出队列】；在【队尾】进行【入队列】
// 换句话说就是：头删，尾插

/*
栈：用来解决括号匹配、逆波兰表达式求解、递归改为非递归

队列：用来进行公平排队、广度优先遍历
*/

typedef int QDataType;

// 链式结构：表示队列（记录每个结点）
typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QNode;

// 队列的结构 （找到队列的头和尾的）
//我们要控制队列，队列里面不止一个值，而是有多个值，要方便头删和尾插
typedef struct Queue
{
	QNode* head; // 队列的头指针
	QNode* tail; // 队列的尾指针
}Queue;

/*
定义两个结构体的原因：
1、一个是在定义结点
2、那么结点定义出来了，我们需要表示我们的队列，所以需要一个头指针和尾指针，方便队尾入数据，队头出数据
*/


// 初始化队列 
void QueueInit(Queue* pq);

// 队尾入队列 
void QueuePush(Queue* pq, QDataType x);

// 队头出队列 
void QueuePop(Queue* pq);

// 获取队列头部元素 
QDataType QueueFront(Queue* pq);

// 获取队列队尾元素 
QDataType QueueBack(Queue* pq);

// 获取队列中有效元素个数 
int QueueSize(Queue* pq);

// 检测队列是否为空，如果为空返回非零结果，如果非空返回0 
bool QueueEmpty(Queue* pq);

// 销毁队列 
void QueueDestroy(Queue* pq);

