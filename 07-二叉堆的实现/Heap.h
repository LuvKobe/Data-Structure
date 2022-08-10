#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int HPDataType; //���д洢���ݵ�����

typedef struct Heap
{
	HPDataType* a; //���ڴ洢���ݵ�����
	int size; //��¼��������Ԫ�ظ���
	int capacity; //��¼�ѵ�����
}HP;

// �ѵĳ�ʼ��
void HeapInit(HP* php);

// �ѵĴ�ӡ
void HeapPrint(HP* php);

// �ڵ㽻��
void Swap(HPDataType* pa, HPDataType* pb);


//���ϵ��� --> ��С��
void AdjustUp1(HPDataType* a, int child);

//���ϵ��� --> �����
void AdjustUp2(HPDataType* a, int child);

// �ѵĲ���
void HeapPush(HP* php, HPDataType x);


// ���µ��� --> ��С��
void AdjustDown1(HPDataType* a, int size, int root);

// ���µ��� --> �����
void AdjustDown2(HPDataType* a, int size, int root);

// �ѵ�ɾ��
void HeapPop(HP* php);


// ȡ�Ѷ�������
HPDataType HeapTop(HP* php);

// �ѵ����ݸ���
int HeapSize(HP* php);

// �ѵ��п�
bool HeapEmpty(HP* php);

// �ѵ�����
void HeapDestory(HP* php);
