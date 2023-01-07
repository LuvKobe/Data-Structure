#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Queen.h"

typedef int BTDataType;

//二叉树的链式节点结构定义
typedef struct BinaryTreeNode
{
	BTDataType data; //数据域
	struct BinaryTreeNode* left; //指向左孩子的指针
	struct BinaryTreeNode* right; //指向右孩子的指针
}BTNode;


//创建一个节点
BTNode* BuyBTNode(BTDataType x) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	if (node == NULL) {
		printf("malloc fail\n");
		exit(-1);
	}
	node->data = x;
	node->left = NULL;
	node->right = NULL;

	return node;
}


//构建一颗二叉树
BTNode* CreatBinaryTree()
{
	BTNode* node1 = BuyBTNode(1);
	BTNode* node2 = BuyBTNode(2);
	BTNode* node3 = BuyBTNode(3);
	BTNode* node4 = BuyBTNode(4);
	BTNode* node5 = BuyBTNode(5);
	BTNode* node6 = BuyBTNode(6);

	//手动链接每个节点： 1->2->4->3->5->6
	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;

	//根节点
	return node1;
}


//前序遍历
void PrevOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL "); //把空也打印出来
		return;
	}
	printf("%d ", root->data);
	PrevOrder(root->left);
	PrevOrder(root->right);
}

//中序遍历
void InOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);

}

//后序
void PostOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}

/*
* 深度优先遍历（DFS）：前序、中序、后序
* 广度优先遍历（BFS）：层序
* 这里的层序遍历：
* 1.先把根入队列，借助队列，先进先出的性质
* 2.上一层的节点出的时候，带下一层的节点进去
* 总结：先入根节点，此时队列里面是有一个节点的，判断队列不为空，把根节点的数据取出来，然后在把根节点的左孩子节点和右孩子入进去，依次循环
* 上一个节点出来以后，把它下面的左右节点带进去
*/
void LevelOrder(BTNode* root) {
	Queue q;
	QueueInit(&q);
	
	//队列不为空，入队列
	if (root) {
		QueuePush(&q, root);
	}

	//队列不为空,出队头的数据
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q); //取队头的数据
		QueuePop(&q); //然后Pop掉队列里面存的这个节点的指针

		printf("%d ", front->data); //然后访问data


		if (front->left) { //如果front的左子树不为空，那么就入队列
			QueuePush(&q, front->left);
		}

		if (front->right) { //如果front的右子树不为空，那么就入队列
			QueuePush(&q, front->right); 
		}
	}
}





/*
* 计数的旧思路：
* 
//计算二叉树有值的结点的个数
//所以要定义一个全局的count，它是存在静态区的，注意：不能定义局部的静态，因为第二次调用的时候，count不会置为0，还是会继承上一次的值
int count = 0; //但是这种做法也会涉及到线程安全的问题
void BTreeSize(BTNode* root) {
	//这里不能定义局部cout，因为递归的栈帧是独立的，调用完以后，函数就销毁了
	//int count = 0; 
	if (root == NULL) {
		return;
	}
	++count;
	BTreeSize(root->left);
	BTreeSize(root->right);
}
*/

/*
* 计数的第二种思路：
* 
//这种做法很安全，思想：遍历+计数
void BTreeSize(BTNode* root, int* pCount) {
	if (root == NULL) {
		return;
	}
	++(*pCount);
	BTreeSize(root->left);
	BTreeSize(root->right);
}
*/

/*
* 计数的第三种思路：分治
* 分治：把复杂的问题，分成更小规模的子问题，子问题再分成更小规模的子问题，直到子问题不可再分割，直接能出结果
* 1.如果是空树，那么就返回0
* 2.如果不是空树，那么就等于：左子树节点个数+右子树节点个数+1（这个1就是自己）
*/
int BTreeSize(BTNode* root) {
	return (root == NULL) ? (0) : (BTreeSize(root->left) + BTreeSize(root->right) + 1);
}


/*求叶子节点的个数： 没有任何 子节点 的节点称为叶子节点，也就是度为 0 的节点
* 思路一：遍历+计数
* 思路二：分治
*/
int BTreeLeafSize(BTNode* root) {
	//1.只要我不是空，并且不是叶子，就会向下递归
	if (root == NULL) {
		return 0;
	}

	//2.如果我的左子树和右子树为空，那么我就是叶子节点
	if (root->left == NULL && root->right == NULL) {
		return 1;
	}

	//3.叶子结点的个数 = 左子树的叶子结点个数 + 右子树的叶子结点个数
	return BTreeLeafSize(root->left) + BTreeLeafSize(root->right);
}


/*
* 第k层的节点的个数，k>=1（k从1开始的）
* 思想：
* 1.空树，返回0
* 2.非空，且k==1，返回1
* 3.非空，且k>1，就转换成：左子树k-1层节点个数 + 右子树k-1层节点个数
*/
int BTreeKLevelSize(BTNode* root, int k) {
	assert(k >= 1);

	if (root == NULL) {
		return 0;
	}
	
	if (root != NULL && k == 1) {
		return 1;
	}

	return BTreeKLevelSize(root->left, k - 1) + BTreeKLevelSize(root->right, k - 1);
}

/*
* 求二叉树的深度（高度）
* 还是用分治：左子树高度 和 右子树高度中，大的那个，然后再+1
* 为什么要加1呢？因为还有根节点这一层！
*/
int BTreeDepth(BTNode* root) {
	//空树高度为0
	if (root == NULL) {
		return 0;
	}

	int leftDepth = BTreeDepth(root->left);
	int rightDepth = BTreeDepth(root->right);

	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}


/*
* 二叉树查找值为x的节点，然后返回节点的指针
* 返回空的情况：你自己找了，左边找了，右边找了，都没有找到，那么就返回空
* 
*/
BTNode* BTreeFind(BTNode* root, BTDataType x) {
	//如果根节点为空树，那么就直接返回空
	if (root == NULL) {
		return NULL;
	}

	//如果当前的data等于x，那么就返回当前节点指针
	if (root->data == x) {
		return root;
	}

	//如果当前节点不是，那么就去左边找，找到了就返回
	BTNode* ret1 = BTreeFind(root->left, x);
	if (ret1) {
		return ret1;
	}

	//如果左边找不到，就去右边找，找到了就返回
	BTNode* ret2 = BTreeFind(root->right, x);
	if (ret2) {
		return ret2;
	}

	//如果左边和右边都没有找到，那么就返回空
	return NULL;
}


/*
* 二叉树的销毁：采取后序方式遍历销毁即可
*/
void BTreeDestory(BTNode* root) {
	if (root == NULL) {
		return;
	}

	BTreeDestory(root->left); //先销毁左树
	BTreeDestory(root->right); //再销毁右树
	free(root);
}



/*
* 判断一颗二叉树是不是完全二叉树（层序遍历的变形）
* 什么是完全二叉树：前n-1层都是满的，最后一层不满，但是从左到右依次是连续的。
* 思路：
* 1.层序遍历，空节点也进队列
* 2.出到空节点以后，出队列种所有数据，如果全是空，就是完全二叉树，如果有非空，就不是
* 
* 完全二叉树：非空节点都出完了，那么遇到空以后，队列后面肯定全是空
*/
bool BTreeComplete(BTNode* root) {
	Queue q;
	QueueInit(&q);

	//队列不为空，入队列
	if (root) {
		QueuePush(&q, root);
	}

	//队列不为空,出队头的数据
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q); //取队头的数据
		QueuePop(&q);

		//如果出到空，那么就跳出循环，进入下一个循环，判断后面还有没有数据？
		if (front == NULL) {
			break;
		}
	
		QueuePush(&q, front->left);
		QueuePush(&q, front->right);
	}

	//出break以后，去判断
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q); //取队头的数据
		QueuePop(&q);

		//如果出到非空，那么说明不是完全二叉树
		if (front) {
			return false;
		}
	}

	//销毁队列
	QueueDestory(&q);
	return true;
}




int main()
{
	BTNode* tree = CreatBinaryTree();
	PrevOrder(tree); //前序
	printf("\n");

	InOrder(tree); //中序
	printf("\n");

	PostOrder(tree); //后续
	printf("\n");

	LevelOrder(tree); //层序
	printf("\n");

	//size --> 思路一：设计线程安全的问题
	/*BTreeSize(tree);
	printf("size：%d\n", count);*/


	/*int count1 = 0; --> 思路二
	BTreeSize(tree, &count1);
	printf("size：%d\n", count1);*/

	//思路三：分治思想
	printf("size：%d\n", BTreeSize(tree));

	//叶子节点个数
	printf("叶子节点：%d\n", BTreeLeafSize(tree));

	//第k层的节点的个数
	int k = 3;
	printf("第%d层的节点个数为：%d\n", k, BTreeLeafSize(tree));

	//二叉树高度
	printf("二叉树高度：%d\n", BTreeDepth(tree));


	//查找测试
	for (int i = 1; i <= 7; ++i) {
		printf("Find：%d, %p\n", i, BTreeFind(tree, i));
	}
	//找到值为5的节点，并把节点的值修改为50
	BTNode* ret = BTreeFind(tree, 5);
	if (ret) {
		ret->data = 50;
	}
	PrevOrder(tree);
	printf("\n");


	//判断完全二叉树
	// 0就是假，非0就是真
	if (BTreeComplete(tree)) {
		printf("是完全二叉树\n");
	}
	else {
		printf("不是完全二叉树\n");

	}
	printf("bool：%d\n", BTreeComplete(tree));

	//二叉树销毁
	BTreeDestory(tree);
	tree = NULL; //置空
}