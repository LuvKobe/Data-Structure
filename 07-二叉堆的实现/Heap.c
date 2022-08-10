#define _CRT_SECURE_NO_WARNINGS 1
#include "Heap.h"

// 堆的初始化
void HeapInit(HP* php) {
	assert(php);

	php->a = NULL;
	php->size = 0;
	php->capacity = 0;
}

// 堆的打印
void HeapPrint(HP* php) {
	assert(php);

	for (int i = 0; i < php->size; ++i) {
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

//交换变量
void Swap(HPDataType* pa, HPDataType* pb) {
	HPDataType tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

//向上调整 --> 建小堆
void AdjustUp1(HPDataType* a, int child) {
	int parent = (child - 1) / 2;

	while (child > 0) { // 调整到根结点的位置截止
		if (a[child] < a[parent]) { // 孩子结点的值小于父结点的值
			Swap(&a[child], &a[parent]); // 将父结点与孩子结点交换
			child = parent; // 继续向上进行调整
			parent = (child - 1) / 2;
		}
		else {
			break; // 已经是小堆了，直接跳出循环
		}
	}
}

//向上调整 --> 建大堆
void AdjustUp2(HPDataType* a, int child) {
	int parent = (child - 1) / 2;

	while (child > 0) { // 调整到根结点的位置截止
		if (a[child] > a[parent]) { // 孩子结点的值大于父结点的值
			Swap(&a[child], &a[parent]); // 将父结点与孩子结点交换
			child = parent; // 继续向上进行调整
			parent = (child - 1) / 2;
		}
		else {
			break; // 已经是大堆了，直接跳出循环
		}
	}
}

// 堆的插入
void HeapPush(HP* php, HPDataType x) {
	assert(php);

	if (php->size == php->capacity) {
		int newCapacity = php->capacity == (0) ? (4) : (php->capacity * 2);

		HPDataType* tmp = realloc(php->a, sizeof(HPDataType) * newCapacity);
		if (tmp == NULL) {
			printf("realloc fail\n");
			exit(-1);
		}

		php->a = tmp;
		php->capacity = newCapacity;
	}

	php->a[php->size] = x;
	php->size++;

	//创建小堆
	AdjustUp1(php->a, php->size - 1);
}


// 向下调整 --> 调小堆
void AdjustDown1(HPDataType* a, int size, int root) {
	int parent = root;

	//child记录的是左右孩子中值较小的孩子的下标
	int child = parent * 2 + 1; // 首先默认child为左孩子，并且是左右当中最小的孩子
	while (child < size) {
		//1、选出左右孩子中小的那个
		//在孩子存在的前提下，如果右孩子比 【默认的左孩子】 还要小，那么就把 child+1 指向右孩子；
		//如果右孩子比左孩子大，那么就不进入if语句
		if (child + 1 < size && a[child + 1] < a[child]) { //左孩子的下标加1，就是右孩子
			++child;
		}

		//2、如果孩子小于父亲，则交换，并继续往下调整
		if (a[child] < a[parent]) {
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}


// 向下调整 --> 调大堆
void AdjustDown2(HPDataType* a, int size, int root) {
	int parent = root;

	//child记录的是左右孩子中值较大的孩子的下标
	int child = parent * 2 + 1; // 首先默认child为左孩子，并且是左右当中最大的孩子
	while (child < size) {
		//1、选出左右孩子中较大的那个孩子
		//在孩子存在的前提下，如果右孩子比 【默认的左孩子】 还要大，那么就把 child+1 指向右孩子；
		//如果右孩子比左孩子小，那么就不进入if语句
		if (child + 1 < size && a[child + 1] > a[child]) { //左孩子的下标加1，就是右孩子
			++child;
		}

		//2、如果孩子大于父亲，则交换，并继续往下调整
		if (a[child] > a[parent]) {
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}


// 堆的删除
void HeapPop(HP* php) {
	assert(php);
	assert(php->size > 0);

	Swap(&php->a[0], &php->a[php->size - 1]); //把堆顶的数据和最后一个位置的数据互换
	php->size--; //删除最后一个节点（也就是删除原来堆顶的元素）

	//向下调整（调小堆）
	AdjustDown1(php->a, php->size, 0);
}


// 取堆顶的数据
HPDataType HeapTop(HP* php) {
	assert(php);
	assert(php->size > 0);

	return php->a[0];
}


// 堆的数据个数
int HeapSize(HP* php) {
	assert(php);

	return php->size;
}


// 堆的判空
bool HeapEmpty(HP* php) {
	assert(php);

	//如果size等于0就为空，不等于0就不为空
	return php->size == 0;
}


// 堆的销毁
void HeapDestory(HP* php) {
	assert(php);

	free(php->a);
	php->a = NULL;
	php->size = php->capacity = 0;
}