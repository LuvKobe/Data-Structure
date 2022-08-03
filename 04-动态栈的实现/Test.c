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

	/*如果栈不为空，就访问栈顶元素*/
	while (!StackEmpty(&st)) {
		printf("%d ", StackTop(&st)); //先访问栈顶的元素
		StackPop(&st); //然后删除栈顶的元素,才能访问下一个
	}
	printf("\n");

	StackDestroy(&st); //销毁栈
}


int main()
{
	TestStack1();
	return 0;
}