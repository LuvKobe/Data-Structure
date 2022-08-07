#define _CRT_SECURE_NO_WARNINGS 1
#include "CQueue.h"

void CQTest1() {
	CQ cq;
	CQueueInit(&cq, 10);

	CQueuePush(&cq, 1);
	CQueuePush(&cq, 2);
	CQueuePush(&cq, 3);
	CQueuePush(&cq, 4);
	CQueuePush(&cq, 5);
	CQueuePush(&cq, 6);
	CQueuePush(&cq, 7);

	while (!CQueueEmpty(&cq)) {
		printf("%d ", CQueueFront(&cq));
		CQueuePop(&cq);
	}
	printf("\n");

}

void CQTest2() {
	CQ cq; //定义队列结构体

	CQueueInit(&cq, 3);//初始化队列,设置长度为3

	/*在队列中插入三个元素*/
	CQueuePush(&cq, 3);
	CQueuePush(&cq, 1);
	CQueuePush(&cq, 5);

	//CQueuePush(&cq, 9); //当插入第4个元素时,提示队列满了

	printf("%d\n", CQueueFront(&cq)); //打印队头元素
	printf("%d\n", CQueueBack(&cq)); //打印队尾元素

	//打印整个队列元素
	while (!CQueueEmpty(&cq)) {
		printf("%d ", CQueueFront(&cq));
		CQueuePop(&cq);
	}

}

int main()
{
	CQTest2();
	return 0;
}