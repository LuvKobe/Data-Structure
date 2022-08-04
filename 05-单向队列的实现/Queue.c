#define _CRT_SECURE_NO_WARNINGS 1

#include "Queue.h"

// 初始化队列 
void QueueInit(Queue* pq) {
	assert(pq); //队列可以为空，但是管理队列的头指针和尾指针不能为空
	pq->head = NULL;
	pq->tail = NULL;
}

// 队尾入队列（尾插）
void QueuePush(Queue* pq, QDataType x) {
	assert(pq);

	/*开辟一个新结点*/
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL) {
		printf("malloc fail\n");
		exit(-1);
	}
	newnode->data = x; //把x赋给newnode的数据域
	newnode->next = NULL; //因为是尾插，所以尾部的结点的next要指向NULL

	/*如果头、尾都为空，那么说明队列还是空的，还没有结点*/
	if (pq->head == NULL && pq->tail == NULL) {
		assert(pq);
		pq->head = pq->tail = newnode;
	}
	else { //说明队列已经有结点了，直接到插入到尾部即可
		pq->tail->next = newnode; //把newnode链接到tail的next
		pq->tail = newnode; //然后让tail指向newnode
	}
}

// 队头出队列 
void QueuePop(Queue* pq) {
	assert(pq);
	assert(pq->head && pq->tail); //队列的head和tail不能为空,不然怎么头删呢？

	//如果head的next为空，那么说明只有一个结点
	if (pq->head->next == NULL) {
		free(pq->head); //直接释放掉head
		pq->head = pq->tail = NULL; //然后把head和tail 置为空
	}
	else {
		QNode* next = pq->head->next; //保存头结点的下一个结点地址
		free(pq->head); //释放掉head
		pq->head = next;
	}
}

// 获取队列头部元素 
QDataType QueueFront(Queue* pq) {
	assert(pq);
	assert(pq->head); //取队头的数据，那么head肯定不能为空

	return pq->head->data;
}

// 获取队列队尾元素 
QDataType QueueBack(Queue* pq) {
	assert(pq);
	assert(pq->tail); //取队尾的数据，那么tail肯定不能为空

	return pq->tail->data;
}

// 获取队列中有效元素个数 
// 这个函数是队列里面最慢的函数，时间复杂度为O(N)
int QueueSize(Queue* pq) {
	assert(pq);
	QNode* cur = pq->head; //使用cur遍历整个队列
	int count = 0; //统计队列元素个数
	while (cur) { //当cur不为空，就进入循环
		count++;
		cur = cur->next;
	}
	return count;
}

// 检测队列是否为空，如果为空返回非零结果，如果非空返回0 
bool QueueEmpty(Queue* pq) {
	assert(pq);

	//如果head或者tail等于空，说队列为空
	return pq->head == NULL && pq->tail == NULL;
}

// 销毁队列 
void QueueDestroy(Queue* pq) {
	assert(pq);
	QNode* cur = pq->head; //使用cur遍历整个队列
	QNode* next = cur->next; //存储cur的下一个结点
	while (cur) { //如果cur不为空
		free(cur); //释放掉cur
		cur = next; //把cur的下一个结点赋给cur
	}
	pq->head = pq->tail = NULL;
}