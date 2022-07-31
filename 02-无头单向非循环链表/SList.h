#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// ���ݽṹ�����ݶ����ڶ��϶�̬�����
// ջ�Ŀռ�һ��ֻ��8M�����800�����ֽ�
// �ѵĿռ�һ�������ڣ�32λ�£���һ����2G��Ҳ����20�����ֽ�

typedef int SLTDateType;

typedef struct SListNode
{
	SLTDateType data;
	struct SListNode* next; // ָ����һ���ڵ��ָ��
}SLTNode;

// 1.��ӡ������
void SListPrint(SLTNode* phead);

// 2.������β��
void SListPushBack(SLTNode** pphead, SLTDateType x); 

// 3.������ͷ��
void SListPushFront(SLTNode** pphead, SLTDateType x);

// 4.������βɾ
void SListPopBack(SLTNode** pphead);

// 5.������ͷɾ
void SListPopFront(SLTNode** pphead);

// 6.���������
SLTNode* SListFind(SLTNode* phead, SLTDateType x);

// 7.��posλ�ò���Ԫ��
void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDateType x);

// 8.ɾ��posλ�õ�ֵ
void SListErase(SLTNode** pphead, SLTNode* pos);

// 9.��posλ�õĺ������Ԫ��
void SListInsertAfter(SLTNode* pos, SLTDateType x);

// 10.ɾ��posλ�ú����һ��ֵ
void SListEraseAfter(SLTNode* pos);

// 11. ����������
void SListDestroy(SLTNode** pphead);





