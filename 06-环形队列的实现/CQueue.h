#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

//Ϊ�˱���պ��� �������޷����֣���ô���Զ࿪һ���ռ�
// head == tailʱ����Ϊ��
// tail����һ��λ����headʱ����������

//���ζ�������ʹ������ʵ��
//����ʵ�ֵĻ�����β������

typedef int CQDataType;

typedef struct CircularQueue
{
	int* a; //����
	int head; //ͷ
	int tail; //β
	int size; //�洢���ݸ���
}CQ;

//���ζ��г�ʼ�������ö��г���Ϊ k 
void CQueueInit(CQ* pcq, int k);

//�����
void CQueuePush(CQ* pcq, CQDataType x);

//������
void CQueuePop(CQ* pcq);

//��ȡ��ͷԪ��
CQDataType CQueueFront(CQ* pcq);

//��ȡ��βԪ��
CQDataType CQueueBack(CQ* pcq);

//�������Ƿ�Ϊ��
bool CQueueEmpty(CQ* pcq);

//�������Ƿ�����
bool CQueueFull(CQ* pcq);

//���ٶ���
void CQueueDestroy(CQ* pcq);