#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Queen.h"

typedef int BTDataType;

//����������ʽ�ڵ�ṹ����
typedef struct BinaryTreeNode
{
	BTDataType data; //������
	struct BinaryTreeNode* left; //ָ�����ӵ�ָ��
	struct BinaryTreeNode* right; //ָ���Һ��ӵ�ָ��
}BTNode;


//����һ���ڵ�
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


//����һ�Ŷ�����
BTNode* CreatBinaryTree()
{
	BTNode* node1 = BuyBTNode(1);
	BTNode* node2 = BuyBTNode(2);
	BTNode* node3 = BuyBTNode(3);
	BTNode* node4 = BuyBTNode(4);
	BTNode* node5 = BuyBTNode(5);
	BTNode* node6 = BuyBTNode(6);

	//�ֶ�����ÿ���ڵ㣺 1->2->4->3->5->6
	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;

	//���ڵ�
	return node1;
}


//ǰ�����
void PrevOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL "); //�ѿ�Ҳ��ӡ����
		return;
	}
	printf("%d ", root->data);
	PrevOrder(root->left);
	PrevOrder(root->right);
}

//�������
void InOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);

}

//����
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
* ������ȱ�����DFS����ǰ�����򡢺���
* ������ȱ�����BFS��������
* ����Ĳ��������
* 1.�ȰѸ�����У��������У��Ƚ��ȳ�������
* 2.��һ��Ľڵ����ʱ�򣬴���һ��Ľڵ��ȥ
* �ܽ᣺������ڵ㣬��ʱ������������һ���ڵ�ģ��ж϶��в�Ϊ�գ��Ѹ��ڵ������ȡ������Ȼ���ڰѸ��ڵ�����ӽڵ���Һ������ȥ������ѭ��
* ��һ���ڵ�����Ժ󣬰�����������ҽڵ����ȥ
*/
void LevelOrder(BTNode* root) {
	Queue q;
	QueueInit(&q);
	
	//���в�Ϊ�գ������
	if (root) {
		QueuePush(&q, root);
	}

	//���в�Ϊ��,����ͷ������
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q); //ȡ��ͷ������
		QueuePop(&q); //Ȼ��Pop����������������ڵ��ָ��

		printf("%d ", front->data); //Ȼ�����data


		if (front->left) { //���front����������Ϊ�գ���ô�������
			QueuePush(&q, front->left);
		}

		if (front->right) { //���front����������Ϊ�գ���ô�������
			QueuePush(&q, front->right); 
		}
	}
}





/*
* �����ľ�˼·��
* 
//�����������ֵ�Ľ��ĸ���
//����Ҫ����һ��ȫ�ֵ�count�����Ǵ��ھ�̬���ģ�ע�⣺���ܶ���ֲ��ľ�̬����Ϊ�ڶ��ε��õ�ʱ��count������Ϊ0�����ǻ�̳���һ�ε�ֵ
int count = 0; //������������Ҳ���漰���̰߳�ȫ������
void BTreeSize(BTNode* root) {
	//���ﲻ�ܶ���ֲ�cout����Ϊ�ݹ��ջ֡�Ƕ����ģ��������Ժ󣬺�����������
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
* �����ĵڶ���˼·��
* 
//���������ܰ�ȫ��˼�룺����+����
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
* �����ĵ�����˼·������
* ���Σ��Ѹ��ӵ����⣬�ֳɸ�С��ģ�������⣬�������ٷֳɸ�С��ģ�������⣬ֱ�������ⲻ���ٷָֱ���ܳ����
* 1.����ǿ�������ô�ͷ���0
* 2.������ǿ�������ô�͵��ڣ��������ڵ����+�������ڵ����+1�����1�����Լ���
*/
int BTreeSize(BTNode* root) {
	return (root == NULL) ? (0) : (BTreeSize(root->left) + BTreeSize(root->right) + 1);
}


/*��Ҷ�ӽڵ�ĸ����� û���κ� �ӽڵ� �Ľڵ��ΪҶ�ӽڵ㣬Ҳ���Ƕ�Ϊ 0 �Ľڵ�
* ˼·һ������+����
* ˼·��������
*/
int BTreeLeafSize(BTNode* root) {
	//1.ֻҪ�Ҳ��ǿգ����Ҳ���Ҷ�ӣ��ͻ����µݹ�
	if (root == NULL) {
		return 0;
	}

	//2.����ҵ���������������Ϊ�գ���ô�Ҿ���Ҷ�ӽڵ�
	if (root->left == NULL && root->right == NULL) {
		return 1;
	}

	//3.Ҷ�ӽ��ĸ��� = ��������Ҷ�ӽ����� + ��������Ҷ�ӽ�����
	return BTreeLeafSize(root->left) + BTreeLeafSize(root->right);
}


/*
* ��k��Ľڵ�ĸ�����k>=1��k��1��ʼ�ģ�
* ˼�룺
* 1.����������0
* 2.�ǿգ���k==1������1
* 3.�ǿգ���k>1����ת���ɣ�������k-1��ڵ���� + ������k-1��ڵ����
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
* �����������ȣ��߶ȣ�
* �����÷��Σ��������߶� �� �������߶��У�����Ǹ���Ȼ����+1
* ΪʲôҪ��1�أ���Ϊ���и��ڵ���һ�㣡
*/
int BTreeDepth(BTNode* root) {
	//�����߶�Ϊ0
	if (root == NULL) {
		return 0;
	}

	int leftDepth = BTreeDepth(root->left);
	int rightDepth = BTreeDepth(root->right);

	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}


/*
* ����������ֵΪx�Ľڵ㣬Ȼ�󷵻ؽڵ��ָ��
* ���ؿյ���������Լ����ˣ�������ˣ��ұ����ˣ���û���ҵ�����ô�ͷ��ؿ�
* 
*/
BTNode* BTreeFind(BTNode* root, BTDataType x) {
	//������ڵ�Ϊ��������ô��ֱ�ӷ��ؿ�
	if (root == NULL) {
		return NULL;
	}

	//�����ǰ��data����x����ô�ͷ��ص�ǰ�ڵ�ָ��
	if (root->data == x) {
		return root;
	}

	//�����ǰ�ڵ㲻�ǣ���ô��ȥ����ң��ҵ��˾ͷ���
	BTNode* ret1 = BTreeFind(root->left, x);
	if (ret1) {
		return ret1;
	}

	//�������Ҳ�������ȥ�ұ��ң��ҵ��˾ͷ���
	BTNode* ret2 = BTreeFind(root->right, x);
	if (ret2) {
		return ret2;
	}

	//�����ߺ��ұ߶�û���ҵ�����ô�ͷ��ؿ�
	return NULL;
}


/*
* �����������٣���ȡ����ʽ�������ټ���
*/
void BTreeDestory(BTNode* root) {
	if (root == NULL) {
		return;
	}

	BTreeDestory(root->left); //����������
	BTreeDestory(root->right); //����������
	free(root);
}



/*
* �ж�һ�Ŷ������ǲ�����ȫ����������������ı��Σ�
* ʲô����ȫ��������ǰn-1�㶼�����ģ����һ�㲻�������Ǵ����������������ġ�
* ˼·��
* 1.����������սڵ�Ҳ������
* 2.�����սڵ��Ժ󣬳��������������ݣ����ȫ�ǿգ�������ȫ������������зǿգ��Ͳ���
* 
* ��ȫ���������ǿսڵ㶼�����ˣ���ô�������Ժ󣬶��к���϶�ȫ�ǿ�
*/
bool BTreeComplete(BTNode* root) {
	Queue q;
	QueueInit(&q);

	//���в�Ϊ�գ������
	if (root) {
		QueuePush(&q, root);
	}

	//���в�Ϊ��,����ͷ������
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q); //ȡ��ͷ������
		QueuePop(&q);

		//��������գ���ô������ѭ����������һ��ѭ�����жϺ��滹��û�����ݣ�
		if (front == NULL) {
			break;
		}
	
		QueuePush(&q, front->left);
		QueuePush(&q, front->right);
	}

	//��break�Ժ�ȥ�ж�
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q); //ȡ��ͷ������
		QueuePop(&q);

		//��������ǿգ���ô˵��������ȫ������
		if (front) {
			return false;
		}
	}

	//���ٶ���
	QueueDestory(&q);
	return true;
}




int main()
{
	BTNode* tree = CreatBinaryTree();
	PrevOrder(tree); //ǰ��
	printf("\n");

	InOrder(tree); //����
	printf("\n");

	PostOrder(tree); //����
	printf("\n");

	LevelOrder(tree); //����
	printf("\n");

	//size --> ˼·һ������̰߳�ȫ������
	/*BTreeSize(tree);
	printf("size��%d\n", count);*/


	/*int count1 = 0; --> ˼·��
	BTreeSize(tree, &count1);
	printf("size��%d\n", count1);*/

	//˼·��������˼��
	printf("size��%d\n", BTreeSize(tree));

	//Ҷ�ӽڵ����
	printf("Ҷ�ӽڵ㣺%d\n", BTreeLeafSize(tree));

	//��k��Ľڵ�ĸ���
	int k = 3;
	printf("��%d��Ľڵ����Ϊ��%d\n", k, BTreeLeafSize(tree));

	//�������߶�
	printf("�������߶ȣ�%d\n", BTreeDepth(tree));


	//���Ҳ���
	for (int i = 1; i <= 7; ++i) {
		printf("Find��%d, %p\n", i, BTreeFind(tree, i));
	}
	//�ҵ�ֵΪ5�Ľڵ㣬���ѽڵ��ֵ�޸�Ϊ50
	BTNode* ret = BTreeFind(tree, 5);
	if (ret) {
		ret->data = 50;
	}
	PrevOrder(tree);
	printf("\n");


	//�ж���ȫ������
	// 0���Ǽ٣���0������
	if (BTreeComplete(tree)) {
		printf("����ȫ������\n");
	}
	else {
		printf("������ȫ������\n");

	}
	printf("bool��%d\n", BTreeComplete(tree));

	//����������
	BTreeDestory(tree);
	tree = NULL; //�ÿ�
}