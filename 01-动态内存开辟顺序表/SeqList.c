#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

//初始化顺序表
void SListInit(SeqList* ps) {
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

//打印顺序表
void SListPrint(SeqList* ps) {
	assert(ps);
	for (int i = 0; i < ps->size; ++i) {
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

//插入数据之前，先扩容顺序表
void SeqListCheckCapacity(SeqList* ps) {
	if (ps->size == ps->capacity) {
		int newcapacity = (ps->capacity == 0) ? (4) : (ps->capacity * 2);
		SLDataType* tmp = (SLDataType*)realloc(ps->a, newcapacity * sizeof(SLDataType));
		if (tmp == NULL) {
			printf("realloc fail\n");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newcapacity;
	}
}

//尾插
void SListPushBack(SeqList* ps, SLDataType x) {
	assert(ps);

	/*检查容量*/
	SeqListCheckCapacity(ps);

	/*进行尾插*/
	ps->a[ps->size] = x; //在尾插插入x
	ps->size++; //size++
}

//尾删
void SListPopBack(SeqList* ps) {
	assert(ps);
	assert(ps->size > 0); //尾删之前，确保元素个数是大于0的

	ps->size--; //直接把元素个数减一
}

//头插
void SListPushFront(SeqList* ps, SLDataType x) {
	assert(ps);

	/*检查容量*/
	SeqListCheckCapacity(ps);

	/*进行头插*/
	int end = ps->size - 1;
	while (end >= 0) {
		ps->a[end + 1] = ps->a[end]; //把数据依次向后挪动
		--end;
	}

	/*此时头部的结点已经空出来了*/
	ps->a[0] = x; //在第一节点插入x
	ps->size++; //元素个数加一
}

//头删
void SListPopFront(SeqList* ps) {
	assert(ps);
	assert(ps->size > 0); //头删之前，确保元素个数是大于0的

	/*头删, 从下标为 1 的位置开始，依次将数据 向前覆盖*/
	int begin = 1;
	while (begin < ps->size) {
		ps->a[begin - 1] = ps->a[begin];
		++begin;
	}
	ps->size--; //元素个数减一
}

//顺序表查找
int SListFind(SeqList* ps, SLDataType x) {
	assert(ps);

	/*直接遍历顺序表,如果找到了x，直接返回x的下标*/
	for (int i = 0; i < ps->size; ++i) {
		if (x == ps->a[i]) {
			return i;
		}
	}

	return -1; //没找到就返回-1
}

//顺序表在pos位置插入x
void SListInsert(SeqList* ps, int pos, SLDataType x) {
	assert(ps);
	assert((pos >= 0) && (pos <= ps->size)); //pos是下标,那么它的范围必须在0-size之间

	/*把pos位置及后⾯的元素向后移动*/
	int end = ps->size - 1;
	while (end >= pos) {
		ps->a[end + 1] = ps->a[end];
		--end;
	}
	/*此时pos位置空出来了，那么之间插入*/
	ps->a[pos] = x; //在pos位置插入x
	ps->size++; //元素个数加一
}

//顺序表删除在pos位置的值
void SListErase(SeqList* ps, int pos) {
	assert(ps); //保证顺序表不能为空
	assert((pos >= 0) && (pos <= ps->size)); //删除之前保证pos的下标是在范围内的

	/*删除的元素位于数组中间，其后的元素依次 向前覆盖 即可*/
	int begin = pos + 1;
	while (begin < ps->size) {
		ps->a[begin - 1] = ps->a[begin];
		++begin;
	}
	ps->size--; //元素个数减一
}

//顺序表修改在pos位置的数据
void SListModify(SeqList* ps, int pos, SLDataType x) {
	assert(ps);
	assert(pos >= 0 && pos < ps->size);//检查输入下标的合法性
	ps->a[pos] = x; // 直接修改数据
}

//顺序表销毁
void SListDestroy(SeqList* ps) {
	free(ps->a);
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}
