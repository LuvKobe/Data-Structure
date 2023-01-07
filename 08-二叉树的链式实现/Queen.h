#pragma once
/*
����ṹ��1  2  3  4

��ʽ�ṹ��1   2   3   4
		��ͷ         ��β����¼һ��βָ�룩
		������       �����
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//ǰ�����������߱�����������һ���ṹ�壬�ȸ������������Ķ����������ط���������ȥ�Ҿ���Ķ���
struct BinaryTreeNode;

typedef struct BinaryTreeNode* QDataType;

//����Ƕ���Ľڵ㣬���ڱ�ʾ��������
typedef struct QueueNode
{
	QDataType data;
	struct QueneNode* next;
}QNode;

//����Ƕ����ͷָ���βָ�룬�����ͷ�����ݣ���β������
typedef struct Queue
{
	QNode* head;
	QNode* tail;
}Queue;


void QueueInit(Queue* pq); //��ʼ��

void QueueDestory(Queue* pq); //����

void QueuePush(Queue* pq, QDataType x); //β�壨��β�����ݣ�

void QueuePop(Queue* pq); //ͷɾ����ͷ�����ݣ�

bool QueueEmpty(Queue* pq); //�п�

size_t QueueSize(Queue* pq); //����Ԫ�ظ���

QDataType QueueFront(Queue* pq); //��ȡ��ͷ����

QDataType QueueBack(Queue* pq); //��ȡ��β����


