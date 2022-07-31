#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// .h ���������������������

// assert���� -->  ����Ϊ�棬��ûʲô�£��������Ϊ�٣�����ֹ���򲢱����ᾫȷ�ĸ����㣬�Ǹ��ļ�����һ�г�����
// return;  --> ��������
// exit(-1) --> ��������


// Ҫ��洢�������Ǵ�0��ʼ�����������洢
// ��̬��˳���
// ���⣺��С�ˣ������ã������ˣ������˷�

//#define N 100
//struct SeqList
//{
//	int a[N]; 
//	int size; // ��¼�洢�˶��ٸ�����
//};


// SL��SeqList����д
// DataType����������
typedef int SLDataType;

// ��̬��˳���
typedef struct SeqList
{
	SLDataType* a; // ָ��̬���ٵ�����
	int size; // �洢�����ݸ���
	int capacity; // �洢�ռ�Ĵ�С
}SeqList;


// ��ӡ˳���
void SeqListPrint(SeqList* psl);

// ˳����ʼ��
void SeqListInit(SeqList* psl);


// β���βɾ��ʱ�临�Ӷ�O(1)
// ˳���β��
void SeqListPushBack(SeqList* psl, SLDataType x);
// ˳���βɾ
void SeqListPopBack(SeqList* psl);


// ͷ���ͷɾ��ʱ�临�Ӷ�O(N)
// ˳���ͷ��
void SeqListPushFront(SeqList* psl, SLDataType x);
// ˳���ͷɾ
void SeqListPopFront(SeqList* psl);

// ���ռ䣬������ˣ���������
void SeqListCheckCapacity(SeqList* psl);

// ��posλ�ò���x
void SeqListInsert(SeqList* psl, size_t pos, SLDataType x);
//ɾ��posλ�õ�����
void SeqListErase(SeqList* psl, size_t pos);

// ˳������
int SeqListFind(SeqList* psl, SLDataType x);
// ˳����޸�
//void SeqListModify(SeqList* psl, size_t pos, SLDataType x);

// ˳�������
void SeqListDestroy(SeqList* psl);


