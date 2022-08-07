#define _CRT_SECURE_NO_WARNINGS 1
#include "CQueue.h"


//环形队列初始化，设置队列长度为 k 
void CQueueInit(CQ* pcq, int k) {
	assert(pcq);

	pcq->a = (int*)malloc(sizeof(int) * (k + 1));
	pcq->head = pcq->tail = 0;
	pcq->size = k;
}


//入队列
void CQueuePush(CQ* pcq, CQDataType x) {
	assert(pcq);

	/*如果队列满了,那么肯定不能插入*/
	if (CQueueFull(pcq)) {
		printf("队满\n");
		exit(0);
	}

	/*当程序走到这里说明队列还没有满*/
	pcq->a[pcq->tail] = x; // 把x存到tail指向的位置

	/*如果队尾指针tail等于size,说明tail已经到边界了*/
	if (pcq->tail == pcq->size) { 
		pcq->tail = 0; // 把tail指向0的位置
	}
	else { /*如果tail不等于size,那么tail就向后挪动*/
		pcq->tail++;
	}
}

//出队列
void CQueuePop(CQ* pcq) {
	assert(pcq);

	/*如果队列为空, 那么肯定就不能删除*/
	if (CQueueEmpty(pcq)) {
		printf("队空\n");
		exit(0);
	}

	/*如果head等于size,那么head置为0*/
	if (pcq->head == pcq->size) {
		pcq->head = 0;
	}
	else { /*否则head就往后挪动*/
		pcq->head++;
	}
}

//获取队头元素
CQDataType CQueueFront(CQ* pcq) {
	assert(pcq);

	/*如果队列为空,那么直接返回*/
	if (CQueueEmpty(pcq)) {
		printf("队空\n");
		exit(0);
	}

	/*如果不为空,直接返回head的值*/
	return pcq->a[pcq->head];
}

//获取队尾元素
CQDataType CQueueBack(CQ* pcq) {
	assert(pcq);

	/*如果队列为空,那么直接返回*/
	if (CQueueEmpty(pcq)) {
		printf("队空\n");
		exit(0);
	}

	/*队尾有两种存在的方式*/
	if (pcq->tail == 0) {
		return pcq->a[pcq->size]; //如果tail在0的位置,那么tail的上一个位置应该是k
	}
	else {
		return pcq->a[pcq->tail - 1]; //如果tail不在0的位置，那么直接返回tail的上一个位置
	}
}

//检测队列是否为空
bool CQueueEmpty(CQ* pcq) {
	assert(pcq);

	return pcq->head == pcq->tail; //当head和tail指向同一个位置时,说明为空
}

//检测队列是否满了
bool CQueueFull(CQ* pcq) {
	assert(pcq);

	//1.当tail在最后一个位置(空),head在第一个位置,说明满了
	if (pcq->tail == pcq->size && pcq->head == 0) {
		return true;
	}
	else { //2.tail的下一个位置为head,说明满了
		return pcq->tail + 1 == pcq->head;
	}
}

//销毁队列
void CQueueDestroy(CQ* pcq) {
	assert(pcq);

	/*要free两次*/
	free(pcq->a); // 释放结构体
	free(pcq); // 释放结构体里面的数组
}
