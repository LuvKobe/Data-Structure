#define _CRT_SECURE_NO_WARNINGS 1

#include "Queen.h"

//初始化
void QueueInit(Queue* pq) {
	assert(pq);
	pq->head = pq->tail = NULL;
}

//销毁
void QueueDestory(Queue* pq) {
	assert(pq);

	QNode* cur = pq->head;
	while (cur) {
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = pq->tail = NULL;
}

//尾插（队尾入数据）
void QueuePush(Queue* pq, QDataType x) {
	assert(pq);

	//先申请一个节点
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL) {
		printf("malloc fail\n");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;

	//当队列为空的情况
	if (pq->head == NULL && pq->tail == NULL) {
		pq->head = pq->tail = newnode;
	}
	else {
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
}

//头删（队头出数据）
void QueuePop(Queue* pq) {
	assert(pq);
	assert(pq->head && pq->tail); //头指针和尾指针不能为空，否则不能尾删

	//当队列只有一个节点的情况
	if (pq->head->next == NULL) {
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else { //当队列有多个节点的情况
		QNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}

//判空
bool QueueEmpty(Queue* pq) {
	assert(pq);

	//当队列的头指针和尾指针为空的时候，说明队列为空
	return pq->head == NULL && pq->tail == NULL;
}

//队列元素个数
size_t QueueSize(Queue* pq) {
	assert(pq);

	//遍历整个队列队列
	QNode* cur = pq->head;
	size_t size = 0;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return size;
}

//获取队头数据
QDataType QueueFront(Queue* pq) {
	assert(pq);
	assert(pq->head); //头指针不能为空

	return pq->head->data;
}

//获取队尾数据
QDataType QueueBack(Queue* pq) {
	assert(pq);
	assert(pq->tail); //尾指针不能为空

	return pq->tail->data;
}