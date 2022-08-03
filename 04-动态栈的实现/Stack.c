#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"

//初始化栈
void StackInit(ST* ps) {
	assert(ps);
	ps->a = NULL;
	ps->top = 0; // 如果top初始化的时候为0，那么它表示栈顶元素的最后一个位置
	ps->capacity = 0;
}

//入栈
void StackPush(ST* ps, STDataType x) {
	assert(ps);

	//满了扩容
	if (ps->top == ps->capacity) { // 当top等于capacity的时候，就需要扩容

		/*capacity第一次等于0，然后直接扩到4；第二次进来，直接扩2倍*/
		int newCapacity = ps->capacity == (0) ? (4) : (ps->capacity * 2);

		/*realloc是要给总空间的大小*/
		ps->a = (STDataType*)realloc(ps->a, newCapacity * sizeof(STDataType));
		/*检查是否扩容成功*/
		if (ps->a == NULL) {
			printf("realloc fail\n");
			exit(-1);
		}
		ps->capacity = newCapacity;
	}
	ps->a[ps->top] = x; // 把x插入到top的位置
	ps->top++; // 然后top再指向下一个位置

	/*简化*/
	//ps->a[ps->top++];
}

//出栈
void StackPop(ST* ps) {
	assert(ps);
	assert(ps->top > 0); //出栈之前，要确保top不为空
	--ps->top;
}

//获取栈顶元素
STDataType StackTop(ST* ps) {
	assert(ps);
	assert(ps->top > 0); //如果top为0，那么栈就为空了，所以top不能为0

	/*top是指向栈顶元素的后一个位置，top-1才是栈顶元素*/
	return ps->a[ps->top - 1];
}

// 获取栈中有效元素个数
int StackSize(ST* ps) {
	assert(ps);

	/*因为top是指向栈顶元素的最后一个位置
	假设元素为：1，2，3，4，5，那么top肯定是指向5的后一个位置
	又因为top是从0开始累加的，所以此时top肯定为5，刚好就是元素个数	
	*/
	return ps->top;
}

//检测栈是否为空，如果为空返回非零结果，如果不为空返回0 
/*
	注意，判空是判断栈是否为空！
	如果栈不为空，那么就是false
	如果栈为空，那么就是true
*/
bool StackEmpty(ST* ps) {
	assert(ps);

	/*如果top等于0，就为真，就是空；如果top不等于0，就为假，就不是空*/
	return ps->top == 0; 

	/*
	因为top的定义有两种方式：
	一种是初始化为0，此时top指向栈顶元素的后一个位置，那么判空方式就是：top等于0
	另外一种是初始化为-1，此时top指向栈顶元素，那么判空方式就是：top等于-1
	*/
}

//销毁栈
void StackDestroy(ST* ps) {
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->capacity = ps->top = 0;
}