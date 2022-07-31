#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"
// .c�Ŷ��壬���ھ���ʵ��

// ��ӡ˳���
void SeqListPrint(SeqList* psl) {
	assert(psl);
	for (int i = 0; i < psl->size; ++i) {
		printf("%d ", psl->a[i]);
	}
	printf("\n");
}

// ��ʼ��˳���
void SeqListInit(SeqList* psl) {
	assert(psl);

	psl->a = NULL;
	psl->size = 0;
	psl->capacity = 0;
}


// ����˳���
void SeqListCheckCapacity(SeqList* psl) {
	if (psl->size == psl->capacity) {
		size_t newCapacity = (psl->capacity == 0) ? (4) : (psl->capacity * 2);
		SLDataType* tmp = realloc(psl->a, sizeof(SLDataType) * newCapacity);
		if (tmp == NULL) {
			printf("realloc fail\n");
			exit(-1); // ��ֹ����
		}
		else {
			psl->a = tmp;
			psl->capacity = newCapacity;
		}
	}
}


// ��˳���β����������
void SeqListPushBack(SeqList* psl, SLDataType x) {
	assert(psl);

	// ������ˣ�Ҫ����
	SeqListCheckCapacity(psl);
	psl->a[psl->size] = x;
	psl->size++;

}
// ��˳���β��ɾ������
void SeqListPopBack(SeqList* psl) {
	assert(psl);
	// �ж����ݵĸ���
	if (psl->size > 0) {
		//�������0��ֱ�ӰѸ�����1
		psl->size--;
	}
}


// ��˳���ͷ����������
void SeqListPushFront(SeqList* psl, SLDataType x) {
	assert(psl); // ���ж���

	// ������ˣ�Ҫ����
	SeqListCheckCapacity(psl);

	// �Ӻ���ǰŲ�����ڳ�ͷ���ռ�
	int end = psl->size - 1; //���һ�������±�
	while (end >= 0) {
		psl->a[end + 1] = psl->a[end]; 
		--end;
	}

	psl->a[0] = x;
	psl->size++;
}


// ��˳���ͷ��ɾ������
void SeqListPopFront(SeqList* psl) {
	assert(psl);

	if (psl->size > 0) {
		int begin = 1; // ˳���ĵ�2�������±�
		while (begin < psl->size) {
			// �ѵ�2������ֵ����1����
			psl->a[begin - 1] = psl->a[begin];
			++begin;
		}
		--psl->size;
	}
}


// ��posλ�ò���x
void SeqListInsert(SeqList* psl, size_t pos, SLDataType x) {
	assert(psl); // ���psl�Ƿ�Ϊ��

	//assert(pos > psl->size); // ���pos�Ƿ�Խ�磨������飩
	
	//���pos�Ƿ�Խ�磨�ºͼ�飩
	if (pos > (psl->size)) {
		printf("%d Խ��", pos);
		return;
	}

	// ������ˣ�Ҫ����
	SeqListCheckCapacity(psl);

	size_t end = psl->size;
	while (end > pos) {
		psl->a[end] = psl->a[end - 1];
		--end;
	}
	psl->a[pos] = x;
	psl->size++;
}


//ɾ��posλ�õ�����
void SeqListErase(SeqList* psl, size_t pos) {
	assert(psl);
	assert(pos < (psl->size));

	rsize_t begin = pos + 1;
	while (begin <= psl->size) {
		psl->a[begin - 1] = psl->a[begin];
		++begin;
	}

	--psl->size;
}

// ����Ԫ��
int SeqListFind(SeqList* psl, SLDataType x) {
	assert(psl);

	for (int i = 0; i < psl->size; ++i) {
		if (psl->a[i] == x) {
			return i;
		}
	}
	return -1;
}

// �޸�˳����е�Ԫ��
//void SeqListModify(SeqList* psl, size_t pos, SLDataType x) {
//	saaert(psl);
//	assert(pos < psl->size);
//
//	psl->a[pos] = x;
//}
