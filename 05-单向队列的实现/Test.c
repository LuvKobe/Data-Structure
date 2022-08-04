#define _CRT_SECURE_NO_WARNINGS 1

#include "Queue.h"

void TestQueue() {
	Queue q;
	QueueInit(&q);

	QueuePush(&q, 1);
	QueuePush(&q, 2);
	QueuePush(&q, 3);
	QueuePush(&q, 4);
	QueuePush(&q, 5);

	while (!QueueEmpty(&q)) {
		printf("%d ", QueueFront(&q)); //打印队头的数据
		QueuePop(&q); //然后把队头的数据删掉
	}
	printf("\n");

}

int main()
{
	TestQueue();
	return 0;
}