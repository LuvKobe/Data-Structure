#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;

typedef struct SeqList
{
	SLDataType* a;
	int size; //Ԫ�ظ���
	int capacity; //Ԫ������
}SeqList;

//��ʼ��˳���
void SListInit(SeqList* ps);

//��ӡ˳���
void SListPrint(SeqList* ps);

//β��
void SListPushBack(SeqList* ps, SLDataType x);

//βɾ
void SListPopBack(SeqList* ps);

//ͷ��
void SListPushFront(SeqList* ps, SLDataType x);

//ͷɾ
void SListPopFront(SeqList* ps);

//˳������
int SListFind(SeqList* ps, SLDataType x);

//˳�����posλ�ò���x
void SListInsert(SeqList* ps, int pos, SLDataType x);

//˳���ɾ����posλ�õ�ֵ
void SListErase(SeqList* ps, int pos);

void SListModify(SeqList* ps, int pos, SLDataType x);

//˳�������
void SListDestroy(SeqList* ps);
