#define _CRT_SECURE_NO_WARNINGS 1
#include "Heap.h"

//����С��
void TestHeap1() {
	HP hp; //�����ѵĽṹ
	HeapInit(&hp); //��ʼ����

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

	HeapPrint(&hp); //��ӡ

	HeapPop(&hp); //ɾ���Ѷ�������

	HeapPrint(&hp); //��ӡ
}

//���Դ��
void TestHeap2() {
	HP hp; //�����ѵĽṹ
	HeapInit(&hp); //��ʼ����

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