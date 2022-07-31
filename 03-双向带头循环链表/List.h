#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
/*
< >: ��ʾֱ���ڿ����������õ�ͷ�ļ�
" ": ��ʾ�����ڵ�ǰĿ¼�������õ�ͷ�ļ�������Ҳ�������ȥ��������
*/


typedef int LTDataType; // �洢����������

typedef struct ListNode
{
	LTDataType data; // ������
	struct ListNode* next; // ����ָ��
	struct ListNode* prev; // ǰ��ָ��
}LTNode;

//��ʼ��1
//void ListInit(LTNode** phead); //ʵ�δ���������һ��ָ��ĵ�ַ,�β�Ҫ�ö���ָ�����

//˫�����ʼ��
LTNode* ListInit();

//˫�����ӡ
void ListPrint(LTNode* phead);

//����һ���ڵ�
LTNode* BuyLTNode(LTDataType x);

//˫����β��
void ListPushBack(LTNode* phead, LTDataType x);

//˫����βɾ
void ListPopBack(LTNode* phead);

//˫����ͷ��
void ListPushFront(LTNode* phead, LTDataType x);

//˫����ͷɾ
void ListPopFront(LTNode* phead);

//˫���������
LTNode* ListFind(LTNode* phead, LTDataType x);

//˫��������pos��ǰ����в���
void ListInsert(LTNode* pos, LTDataType x);

//˫������ɾ��posλ�õĽڵ�
void ListErase(LTNode* pos);

//˫�����п�
bool ListEmpty(LTNode* phead);

//��ȡ˫�����е�Ԫ�ظ���
int ListSize(LTNode* phead);

//����˫����
void ListDestory(LTNode* phead);



/*
˳�����ŵ㣺

1������ռ��������ģ��������±��������

2��CPU���ٻ��������ʻ����


˳����ȱ�㣺

1��������Ҫ����ռ��������ռ䲻����Ҫ���ݡ�������ݻ��ƻ�����һ���Ŀռ��˷�

2��ͷ�������в����롢ɾ����Ų������Ч�ʵ� O(N)

����������������������������������������������������������������������������������������������������������������

������ŵ㣺

1������������ͷſռ�
2������λ�ò��롢ɾ������Ч�ʸ� O(1)

�����ȱ�㣺

��֧���±��������ʡ���Щ�㷨���ʺ�����������С��磺���֡������
*/

