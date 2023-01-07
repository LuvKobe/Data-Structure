#define _CRT_SECURE_NO_WARNINGS 1

#include "Queen.h"

//��ʼ��
void QueueInit(Queue* pq) {
	assert(pq);
	pq->head = pq->tail = NULL;
}

//����
void QueueDestory(Queue* pq) {
	assert(pq);

	QNode* cur = pq->head;
	while (cur) {
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->head = pq->tail = NULL;
}

//β�壨��β�����ݣ�
void QueuePush(Queue* pq, QDataType x) {
	assert(pq);

	//������һ���ڵ�
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL) {
		printf("malloc fail\n");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;

	//������Ϊ�յ����
	if (pq->head == NULL && pq->tail == NULL) {
		pq->head = pq->tail = newnode;
	}
	else {
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
}

//ͷɾ����ͷ�����ݣ�
void QueuePop(Queue* pq) {
	assert(pq);
	assert(pq->head && pq->tail); //ͷָ���βָ�벻��Ϊ�գ�������βɾ

	//������ֻ��һ���ڵ�����
	if (pq->head->next == NULL) {
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else { //�������ж���ڵ�����
		QNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}

//�п�
bool QueueEmpty(Queue* pq) {
	assert(pq);

	//�����е�ͷָ���βָ��Ϊ�յ�ʱ��˵������Ϊ��
	return pq->head == NULL && pq->tail == NULL;
}

//����Ԫ�ظ���
size_t QueueSize(Queue* pq) {
	assert(pq);

	//�����������ж���
	QNode* cur = pq->head;
	size_t size = 0;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return size;
}

//��ȡ��ͷ����
QDataType QueueFront(Queue* pq) {
	assert(pq);
	assert(pq->head); //ͷָ�벻��Ϊ��

	return pq->head->data;
}

//��ȡ��β����
QDataType QueueBack(Queue* pq) {
	assert(pq);
	assert(pq->tail); //βָ�벻��Ϊ��

	return pq->tail->data;
}