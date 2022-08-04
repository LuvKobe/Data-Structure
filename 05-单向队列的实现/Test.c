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
		printf("%d ", QueueFront(&q)); //��ӡ��ͷ������
		QueuePop(&q); //Ȼ��Ѷ�ͷ������ɾ��
	}
	printf("\n");

}

int main()
{
	TestQueue();
	return 0;
}