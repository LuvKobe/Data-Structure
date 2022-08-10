#define _CRT_SECURE_NO_WARNINGS 1
#include "Heap.h"

//测试小堆
void TestHeap1() {
	HP hp; //创建堆的结构
	HeapInit(&hp); //初始化堆

	HeapPush(&hp, 27);
	HeapPush(&hp, 15);
	HeapPush(&hp, 19);
	HeapPush(&hp, 18);
	HeapPush(&hp, 28);
	HeapPush(&hp, 34);
	HeapPush(&hp, 65);
	HeapPush(&hp, 49);
	HeapPush(&hp, 25);
	HeapPush(&hp, 37);

	HeapPrint(&hp); //打印

	HeapPop(&hp); //删除堆顶的数据

	HeapPrint(&hp); //打印
}

//测试大堆
void TestHeap2() {
	HP hp; //创建堆的结构
	HeapInit(&hp); //初始化堆

	HeapPush(&hp, 27);
	HeapPush(&hp, 15);
	HeapPush(&hp, 19);
	HeapPush(&hp, 18);
	HeapPush(&hp, 28);
	HeapPush(&hp, 34);
	HeapPush(&hp, 65);
	HeapPush(&hp, 49);
	HeapPush(&hp, 25);
	HeapPush(&hp, 37);

	HeapPrint(&hp);
}


int main()
{
	TestHeap1();
	return 0;
}