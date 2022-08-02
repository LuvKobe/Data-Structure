#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void TestSList1() {
	SeqList s;

	SListInit(&s); //��ʼ���ṹ��

	/*β��*/
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);

	/*ͷ��*/
	SListPushFront(&s, 6);
	SListPushFront(&s, 5);
	SListPushFront(&s, 4);

	/*��ӡ*/
	SListPrint(&s);
}

void TestSList2() {
	SeqList s;

	SListInit(&s); //��ʼ���ṹ��

	/*β��*/
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);

	/*ͷ��*/
	SListPushFront(&s, 6);
	SListPushFront(&s, 5);
	SListPushFront(&s, 4);

	/*��ӡ*/
	SListPrint(&s);

	/*��1��ǰ��λ�ò���10*/
	int pos = SListFind(&s, 1);
	SListInsert(&s, pos, 10);

	/*��ӡ*/
	SListPrint(&s);

	/*ɾ����1��ǰ��λ�ò����10*/
	SListErase(&s, pos);

	/*��ӡ*/
	SListPrint(&s);

	/*ʹ�����Ժ�����˳���*/
	SListDestroy(&s);
}

int main()
{
	TestSList2();
	return 0;
}