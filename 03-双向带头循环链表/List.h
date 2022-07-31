#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
/*
< >: 表示直接在库里面找引用的头文件
" ": 表示优先在当前目录下找引用的头文件，如果找不到，再去库里面找
*/


typedef int LTDataType; // 存储的数据类型

typedef struct ListNode
{
	LTDataType data; // 数据域
	struct ListNode* next; // 后驱指针
	struct ListNode* prev; // 前驱指针
}LTNode;

//初始化1
//void ListInit(LTNode** phead); //实参传过来的是一个指针的地址,形参要用二级指针接收

//双链表初始化
LTNode* ListInit();

//双链表打印
void ListPrint(LTNode* phead);

//增加一个节点
LTNode* BuyLTNode(LTDataType x);

//双链表尾插
void ListPushBack(LTNode* phead, LTDataType x);

//双链表尾删
void ListPopBack(LTNode* phead);

//双链表头插
void ListPushFront(LTNode* phead, LTDataType x);

//双链表头删
void ListPopFront(LTNode* phead);

//双向链表查找
LTNode* ListFind(LTNode* phead, LTDataType x);

//双向链表在pos的前面进行插入
void ListInsert(LTNode* pos, LTDataType x);

//双向链表删除pos位置的节点
void ListErase(LTNode* pos);

//双链表判空
bool ListEmpty(LTNode* phead);

//获取双链表中的元素个数
int ListSize(LTNode* phead);

//销毁双链表
void ListDestory(LTNode* phead);



/*
顺序表的优点：

1、物理空间是连续的，方便用下标随机访问

2、CPU高速缓存命中率会更高


顺序表的缺点：

1、由于需要物理空间连续，空间不够需要扩容。其次扩容机制还存在一定的空间浪费

2、头部或者中部插入、删除、挪动数据效率低 O(N)

————————————————————————————————————————————————————————

链表的优点：

1、按需申请和释放空间
2、任意位置插入、删除数据效率高 O(1)

链表的缺点：

不支持下标的随机访问。有些算法不适合在它上面进行。如：二分、排序等
*/

