#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*
ջ���ö�̬�ڴ濪�ٵ�����ʵ��

���У��õ�����ʵ�֡�

������βɾ��β�壬�����������ڣ�Ҫ�ҵ�β��
�������ǿ��Լ�¼һ��βָ�룬����β��
*/


// ������ "��ʽ�ṹ"����Ϊ���ڡ���ͷ�����С������С����ڡ���β�����С�����С�
// ���仰˵���ǣ�ͷɾ��β��

/*
ջ�������������ƥ�䡢�沨�����ʽ��⡢�ݹ��Ϊ�ǵݹ�

���У��������й�ƽ�Ŷӡ�������ȱ���
*/

typedef int QDataType;

// ��ʽ�ṹ����ʾ���У���¼ÿ����㣩
typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QNode;

// ���еĽṹ ���ҵ����е�ͷ��β�ģ�
//����Ҫ���ƶ��У��������治ֹһ��ֵ�������ж��ֵ��Ҫ����ͷɾ��β��
typedef struct Queue
{
	QNode* head; // ���е�ͷָ��
	QNode* tail; // ���е�βָ��
}Queue;

/*
���������ṹ���ԭ��
1��һ�����ڶ�����
2����ô��㶨������ˣ�������Ҫ��ʾ���ǵĶ��У�������Ҫһ��ͷָ���βָ�룬�����β�����ݣ���ͷ������
*/


// ��ʼ������ 
void QueueInit(Queue* pq);

// ��β����� 
void QueuePush(Queue* pq, QDataType x);

// ��ͷ������ 
void QueuePop(Queue* pq);

// ��ȡ����ͷ��Ԫ�� 
QDataType QueueFront(Queue* pq);

// ��ȡ���ж�βԪ�� 
QDataType QueueBack(Queue* pq);

// ��ȡ��������ЧԪ�ظ��� 
int QueueSize(Queue* pq);

// �������Ƿ�Ϊ�գ����Ϊ�շ��ط�����������ǿշ���0 
bool QueueEmpty(Queue* pq);

// ���ٶ��� 
void QueueDestroy(Queue* pq);

