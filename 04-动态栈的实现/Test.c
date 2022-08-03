#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"

void TestStack1() {
	ST st;
	StackInit(&st);
	StackPush(&st, 1);
	StackPush(&st, 2);
	StackPush(&st, 3);
	StackPush(&st, 4);
	StackPush(&st, 5);

	/*���ջ��Ϊ�գ��ͷ���ջ��Ԫ��*/
	while (!StackEmpty(&st)) {
		printf("%d ", StackTop(&st)); //�ȷ���ջ����Ԫ��
		StackPop(&st); //Ȼ��ɾ��ջ����Ԫ��,���ܷ�����һ��
	}
	printf("\n");

	StackDestroy(&st); //����ջ
}


int main()
{
	TestStack1();
	return 0;
}