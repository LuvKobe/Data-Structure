#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"
// .c放定义，用于具体实现

// 打印顺序表
void SeqListPrint(SeqList* psl) {
	assert(psl);
	for (int i = 0; i < psl->size; ++i) {
		printf("%d ", psl->a[i]);
	}
	printf("\n");
}

// 初始化顺序表
void SeqListInit(SeqList* psl) {
	assert(psl);

	psl->a = NULL;
	psl->size = 0;
	psl->capacity = 0;
}


// 扩容顺序表
void SeqListCheckCapacity(SeqList* psl) {
	if (psl->size == psl->capacity) {
		size_t newCapacity = (psl->capacity == 0) ? (4) : (psl->capacity * 2);
		SLDataType* tmp = realloc(psl->a, sizeof(SLDataType) * newCapacity);
		if (tmp == NULL) {
			printf("realloc fail\n");
			exit(-1); // 终止程序
		}
		else {
			psl->a = tmp;
			psl->capacity = newCapacity;
		}
	}
}


// 在顺序表尾部插入数据
void SeqListPushBack(SeqList* psl, SLDataType x) {
	assert(psl);

	// 如果满了，要扩容
	SeqListCheckCapacity(psl);
	psl->a[psl->size] = x;
	psl->size++;

}
// 在顺序表尾部删除数据
void SeqListPopBack(SeqList* psl) {
	assert(psl);
	// 判断数据的个数
	if (psl->size > 0) {
		//如果大于0，直接把个数减1
		psl->size--;
	}
}


// 在顺序表头部插入数据
void SeqListPushFront(SeqList* psl, SLDataType x) {
	assert(psl); // 进行断言

	// 如果满了，要扩容
	SeqListCheckCapacity(psl);

	// 从后往前挪动，腾出头部空间
	int end = psl->size - 1; //最后一个数的下标
	while (end >= 0) {
		psl->a[end + 1] = psl->a[end]; 
		--end;
	}

	psl->a[0] = x;
	psl->size++;
}


// 在顺序表头部删除数据
void SeqListPopFront(SeqList* psl) {
	assert(psl);

	if (psl->size > 0) {
		int begin = 1; // 顺序表的第2个数的下标
		while (begin < psl->size) {
			// 把第2个数赋值给第1个数
			psl->a[begin - 1] = psl->a[begin];
			++begin;
		}
		--psl->size;
	}
}


// 在pos位置插入x
void SeqListInsert(SeqList* psl, size_t pos, SLDataType x) {
	assert(psl); // 检查psl是否为空

	//assert(pos > psl->size); // 检查pos是否越界（暴力检查）
	
	//检查pos是否越界（温和检查）
	if (pos > (psl->size)) {
		printf("%d 越界", pos);
		return;
	}

	// 如果满了，要扩容
	SeqListCheckCapacity(psl);

	size_t end = psl->size;
	while (end > pos) {
		psl->a[end] = psl->a[end - 1];
		--end;
	}
	psl->a[pos] = x;
	psl->size++;
}


//删除pos位置的数据
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

// 查找元素
int SeqListFind(SeqList* psl, SLDataType x) {
	assert(psl);

	for (int i = 0; i < psl->size; ++i) {
		if (psl->a[i] == x) {
			return i;
		}
	}
	return -1;
}

// 修改顺序表中的元素
//void SeqListModify(SeqList* psl, size_t pos, SLDataType x) {
//	saaert(psl);
//	assert(pos < psl->size);
//
//	psl->a[pos] = x;
//}
