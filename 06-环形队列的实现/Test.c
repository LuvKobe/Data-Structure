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
	CQ cq; //������нṹ��

	CQueueInit(&cq, 3);//��ʼ������,���ó���Ϊ3

	/*�ڶ����в�������Ԫ��*/
	CQueuePush(&cq, 3);
	CQueuePush(&cq, 1);
	CQueuePush(&cq, 5);

	//CQueuePush(&cq, 9); //�������4��Ԫ��ʱ,��ʾ��������

	printf("%d\n", CQueueFront(&cq)); //��ӡ��ͷԪ��
	printf("%d\n", CQueueBack(&cq)); //��ӡ��βԪ��

	//��ӡ��������Ԫ��
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