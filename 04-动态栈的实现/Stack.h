#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STDataType;

// ֧�ֶ�̬������ջ
typedef struct Stack
{
	STDataType* a;
	int top; //ջ��
	int capacity; //����
}ST;

//��ʼ��ջ
void StackInit(ST* ps);

//��ջ
void StackPush(ST* ps, STDataType x);

//��ջ
void StackPop(ST* ps);

//��ȡջ��Ԫ��
STDataType StackTop(ST* ps);

// ��ȡջ����ЧԪ�ظ���
int StackSize(ST* ps);

//���ջ�Ƿ�Ϊ�գ����Ϊ�շ��ط������������Ϊ�շ���0 
bool StackEmpty(ST* ps);

//����ջ
void StackDestroy(ST* ps);