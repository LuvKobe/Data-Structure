#pragma once

#include <iostream>
#include <vector>
using namespace std;

// ���������ɫ
enum Colour
{
	RED,
	BLACK,
};

// ��������Ķ���
template<class K, class V>
struct RBTreeNode
{
	// ������
	RBTreeNode<K, V>* _left; // �ڵ������
	RBTreeNode<K, V>* _right; // �ڵ���Һ���
	RBTreeNode<K, V>* _parent; // �ڵ��˫�ף��������Ҫ��ת��Ϊ��ʵ�ּ򵥸������ֶΣ�

	// �洢�ļ�ֵ��
	pair<K, V> _kv;

	// ������ɫ
	Colour _col;

	// ���캯��
	RBTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)
	{}
};

// �����
template<class K, class V>
struct RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	// ���뺯��
	bool Insert(const pair<K, V>& kv)
	{
		// ���������ǿ������Ѳ���ڵ�ֱ����Ϊ���ڵ�
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK; // ���������Ǻ�ɫ
			return true; // ����ɹ�
		}

		// 1.���ն����������Ĺ������
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first) // ������ڵ��keyֵ���ڵ�ǰ�ڵ��keyֵ
			{
				// ����������
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first) // ������ڵ��keyֵС�ڵ�ǰ�ڵ��keyֵ
			{
				// ����������
				parent = cur;
				cur = cur->_left;
			}
			else // ������ڵ��keyֵ���ڵ�ǰ�ڵ��keyֵ
			{
				return false; // ����ʧ�ܣ�����false
			}
		}

		// 2.��ѭ��������˵��cur�ҵ��˿յ�λ�ã���ô�Ͳ���
		cur = new Node(kv); // ����һ���½ڵ�
		cur->_col = RED; // ���������ɫ����Ϊ��ɫ
		if (parent->_kv.first < kv.first) // ����½ڵ��keyֵ���ڵ�ǰparent�ڵ��keyֵ
		{
			// �Ͱ��½ڵ����ӵ�parent���ұ�
			parent->_right = cur;
		}
		else // ����½ڵ��keyֵС�ڵ�ǰparent�ڵ��keyֵ
		{
			// �Ͱ��½ڵ����ӵ�parent�����
			parent->_left = cur;
		}
		cur->_parent = parent; // �����˰��½ڵ������_parentָ��parent(��Ϊ���Ƕ������һ��������)

		// 3.��������ĸ�����Ǻ�ɫ�ģ�����Ҫ�Ժ�������е���������������ɫ�ڵ�������
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent; // ���parent�Ǻ�ɫ����ô�丸���һ������

			if (grandfather->_left == parent) // ��parent��grandfather������
			{
				Node* uncle = grandfather->_right; // uncleһ����grandfather���Һ���

				//���һ��uncle������Ϊ��
				if (uncle && uncle->_col == RED)
				{
					// ������ɫ
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// �������ϵ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else // ����� + �������uncle������ + uncle������Ϊ��
				{
					if (cur == parent->_left) 
					{
						//     g
						//   p
						// c
						RotateR(grandfather); //�ҵ���

						// ��ɫ����
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else // cur == parent->_right
					{
						//     g
						//   p
						//     c 
						// ����˫��
						RotateL(parent);
						RotateR(grandfather);

						// ��ɫ����
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					// ������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д��� 
					break;
				}
			}
			else // parent��grandfather���Һ���
			{
				Node* uncle = grandfather->_left; // uncle��grandfather������

				// ���һ��uncle������Ϊ��
				if (uncle && uncle->_col == RED)
				{
					// ��ɫ
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// �������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else // ����� + �������uncle������ + uncle������Ϊ��
				{
					if (cur == parent->_right)
					{
						// g
						//   p
						//     c 
						RotateL(grandfather); // ����

						// ��ɫ����
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else // cur == parent->_left
					{
						// g
						//   p
						// c

						// ����˫��
						RotateR(parent);
						RotateL(grandfather);

						// ��ɫ����
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					// ������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
					break;
				}
			}
		}
		_root->_col = BLACK; // ��������ɫΪ��ɫ�����ܱ����һ����˺�ɫ����Ҫ��غ�ɫ��
		return true; // ����ɹ�
	}

	// �������ұ߸���Ҫ������
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent; // �ȱ���parent��parent

		// 1.����parent��subRL֮��Ĺ�ϵ
		parent->_right = subRL;
		if (subRL) // ���subRL�ڵ㲻Ϊ�գ���ôҪ��������parent
		{
			subRL->_parent = parent;
		}

		// 2.����subR��parent֮��Ĺ�ϵ
		subR->_left = parent;
		parent->_parent = subR;

		// 3.����ppNode��subR֮��Ĺ�ϵ�����������parent���������ĸ������Ǿֲ�������
		if (parent == _root) // ��parent�Ǹ��ڵ�ʱ
		{
			_root = subR; // subR�ͱ�����µĸ��ڵ�
			_root->_parent = nullptr; // ���ڵ�ĵ�parentΪ��
		}
		else // ��parent���������ľֲ�����ʱ
		{
			if (parent == ppNode->_left) // ���parent��ppNode�����
			{
				ppNode->_left = subR; // ��ôsubR����parent��������
			}
			else // ���parent��ppNode���ұ�
			{
				ppNode->_right = subR; // ��ôsubR����parent��������
			}
			subR->_parent = ppNode; // subR��parent��Ҫָ��ppNode
		}
	}

	// �ҵ�������߸߾��ҵ�����
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		//Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		// 1.����parent��subLR֮��Ĺ�ϵ
		parent->_left = subLR;
		if (subLR) // ���subLR�ڵ㲻Ϊ�գ���ôҪ��������parent
		{
			subLR->_parent = parent;
		}

		// 2.����subL��parent֮��Ĺ�ϵ
		subL->_right = parent;
		parent->_parent = subL;

		// 3.����ppNode��subL֮��Ĺ�ϵ�����������parent���������ĸ������Ǿֲ�������
		if (parent == _root) // ��parent�Ǹ��ڵ�ʱ
		{
			_root = subL; // subL�ͱ�����µĸ��ڵ�
			_root->_parent = nullptr; // ���ڵ�ĵ�parentΪ��
		}
		else // ��parent���������ľֲ�����ʱ
		{
			if (parent == ppNode->_left) // ���parent��ppNode�����
			{
				ppNode->_left = subL; // ��ôsubL����parent��������
			}
			else // ���parent��ppNode���ұ�
			{
				ppNode->_right = subL; // ��ôsubL����parent��������
			}
			subL->_parent = ppNode; // subR��parent��Ҫָ��ppNode
		}
	}

	// ����������Ӻ��������Ӻ�����
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}

	// ������ɫ���·�����Ӻ�����
	int _maxHeight(Node* root)
	{
		if (root == nullptr)
			return 0;

		int lh = _maxHeight(root->_left);
		int rh = _maxHeight(root->_right);

		return lh > rh ? lh + 1 : rh + 1;
	}

	// ������ɫ�����·�����Ӻ�����
	int _minHeight(Node* root)
	{
		if (root == nullptr)
			return 0;

		int lh = _minHeight(root->_left);
		int rh = _minHeight(root->_right);

		return lh < rh ? lh + 1 : rh + 1;
	}

	// �ж��Ƿ�Ϊ��������Ӻ�����
	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		//�ߵ�null֮���ж�k��black�Ƿ����
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "Υ�������ģ�ÿ��·���к�ɫ�ڵ�ĸ���������ͬ" << endl;
				return false;
			}
			return true;
		}

		// ͳ�ƺ�ɫ�ڵ�ĸ���
		if (BLACK == pRoot->_col)
			k++;

		// ��⵱ǰ�ڵ�����˫���Ƿ�Ϊ��ɫ
		if (RED == pRoot->_col && pRoot->_parent && pRoot->_parent->_col == RED)
		{
			cout << "Υ������������������һ��ĺ�ɫ�ڵ�" << endl;
			return false;
		}

		return _IsValidRBTree(pRoot->_left, k, blackCount) &&
			_IsValidRBTree(pRoot->_right, k, blackCount);
	}

	// ���Һ���
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key) // keyֵ���ڸý���ֵ
			{
				cur = cur->_left; // �ڸý������������в���
			}
			else if (cur->_kv.first < key) // keyֵС�ڸý���ֵ
			{
				cur = cur->_right; // �ڸý������������в���
			}
			else // ��ǰ�ڵ��ֵ����keyֵ
			{
				return cur; //���ظý��
			}
		}
		return nullptr; //����ʧ��
	}
public:
	// �������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	// ����߶�
	void Height()
	{
		cout << "�·��:" << _maxHeight(_root) << endl;
		cout << "���·��:" << _minHeight(_root) << endl;
	}

	// �ж��Ƿ�Ϊ�����
	bool IsBalanceTree()
	{
		// ���������������

		Node* pRoot = _root;
		// ����Ҳ�Ǻ����
		if (nullptr == pRoot)
			return true;

		// �����ڵ��Ƿ��������
		if (BLACK != pRoot->_col)
		{
			cout << "Υ����������ʶ������ڵ����Ϊ��ɫ" << endl;
			return false;
		}

		// ��ȡ����һ��·���к�ɫ�ڵ�ĸ��� -- �Ƚϻ�׼ֵ
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_col)
				blackCount++;

			pCur = pCur->_left;
		}

		// ����Ƿ��������������ʣ�k������¼·���к�ɫ�ڵ�ĸ���
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}
private:
	Node* _root = nullptr;
};

void TestRBTree1()
{
	//int a[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int a[] = { 30, 29, 28, 27, 26, 25, 24, 11, 8, 7, 6, 5, 4, 3, 2, 1 };
	RBTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}
	t.InOrder();
	t.Height();
}

void TestRBTree2()
{
	const size_t N = 100;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(rand());
		//v.push_back(i);
	}

	RBTree<int, int> t;
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
	}

	//t.levelOrder();
	//cout << endl;
	cout << "�Ƿ�ƽ��?" << t.IsBalanceTree() << endl;
	t.Height();

	t.InOrder();
}