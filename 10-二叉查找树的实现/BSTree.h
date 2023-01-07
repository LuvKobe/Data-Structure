#pragma once
#include <iostream>
using namespace std;

// �ڵ���
template<class K>
struct BSTreeNode
{
	K _key; // �ڵ�ֵ
	BSTreeNode<K>* _left; // ��ָ��
	BSTreeNode<K>* _right; // ��ָ��

	// ���캯��
	BSTreeNode(const K& key)
		:_key(key)
		,_left(nullptr)
		,_right(nullptr)
	{}
};

// BST��
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node; // �ѽڵ��ض����Node
private:
	// ������
	Node* CopyTree(Node* root)
	{
		// ����ǿ�����ֱ�ӷ��ؿ�
		if (root == nullptr)
			return nullptr;

		Node* copyNode = new Node(root->_key); // ���������
		copyNode->_left = CopyTree(root->_left); // ����������
		copyNode->_right = CopyTree(root->_right); // ����������

		return copyNode; // ���ؿ�������
	}

	// ���ٺ���(�ݹ�ʵ�ֵ��Ӻ���)
	void DestroyTree(Node* root)
	{
		// ����ǿ�����ֱ�ӷ��ؿ�
		if (root == nullptr)
			return;

		DestroyTree(root->_left); // �ݹ��ͷ��������еĽڵ�
		DestroyTree(root->_right); // �ݹ��ͷ��������еĽڵ�
		delete root; // ɾ�������
	}

	// ���Һ���(�ݹ�ʵ�ֵ��Ӻ���)
	bool _FindR(Node* root, const K& key)
	{
		// ����ǿ�������ôֱ�ӷ��ؿ�
		if (root == nullptr)
			return false;
		
		if (root->_key < key) // ���keyֵ���ڸ��ڵ��ֵ
		{
			return _FindR(root->_right, key); // ��ȥ�����ڵ�����������в���
		}
		else if (root->_key > key) // ���keyֵС�ڸ��ڵ��ֵ
		{
			return _FindR(root->_left, key); // ��ȥ�����ڵ�����������в���
		}
		else // ���keyֵ���ڸ��ڵ��ֵ
		{
			return true; // ���ҳɹ�������true
		}
	}

	// ���뺯��(�ݹ�ʵ�ֵ��Ӻ���)
	bool _InsertR(Node*& root, const K& key) // ���ô��Σ�root��_root�ı���
	{
		if (root == nullptr) // ����ǿ���
		{
			root = new Node(key); // ֱ�Ӱ�key�ڵ���Ϊ���ĸ����
			return true; // ����ɹ�������true
		} 

		// ������ǿ���
		if (root->_key < key) // ���key���ڵ�ǰ�ڵ��ֵ
		{
			return _InsertR(root->_right, key); // ��key���뵽����������
		}
		else if (root->_key > key) // ���keyС�ڵ�ǰ�ڵ��ֵ
		{
			return _InsertR(root->_left, key); // ��key���뵽����������
		}
		else // ���key���ڵ�ǰ�ڵ��ֵ
		{
			return false; // ����ʧ�ܣ�ֱ�ӷ���false
		}
	}

	// ɾ������(�ݹ�ʵ�ֵ��Ӻ���)
	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr) // ����ǿ���
			return false; // ɾ��ʧ�ܣ�ֱ�ӷ���false

		if (root->_key < key) // ���key���ڸ��ڵ��ֵ
		{
			return _EraseR(root->_right, key); // ��ô��ɾ���ڵ��ڸ�������������
		}
		else if (root->_key > key) // ���keyС�ڸ��ڵ��ֵ
		{
			return _EraseR(root->_left, key); // ��ô��ɾ���ڵ��ڸ�������������
		}
		else // �ҵ��˴�ɾ���ڵ�
		{
			Node* del = root; // �ȱ�����ڵ�
			if (root->_left == nullptr) // �����ɾ���ڵ��������Ϊ��
			{
				root = root->_right; // ��ô������������Ϊ�������µĸ��ڵ�
			}
			else if (root->_right == nullptr) // �����ɾ���ڵ��������Ϊ��
			{
				root = root->_left; // ��ô������������Ϊ�������µĸ��ڵ�
			}
			else // �����ɾ���ڵ��������������Ϊ��
			{
				Node* minRight = root->_right; // ��¼���ڵ�����������ֵ��С�Ľڵ�
				while (minRight->_left) // Ѱ�Ҹ��ڵ�����������ֵ��С�Ľڵ�
				{
					minRight = minRight->_left; // ����������ֵ��С�Ľڵ�һ����������ߣ�����һֱ�������
				}
				// �ҵ��Ժ󣬰Ѹ��ڵ��ֵ��minRight��ֵ����
				swap(root->_key, minRight->_key);
				return _EraseR(root->_right, key); // ��ʱ����ת�����ڸ�������������ȥɾ�����key������ɾ�����keyһ��������Ϊ�յĳ�����
			}
			delete del; // �ͷŸ��ڵ�
			return true; // ɾ���ɹ�������true
		}
	}

	// �������(�ݹ�ʵ�ֵ��Ӻ���)
	void _InOrder(Node* root)
	{
		if (root == nullptr) // ����ǿ�����ֱ�ӷ��ؿ�
			return;
		_InOrder(root->_left); // �ݹ����������
		cout << root->_key << " "; // ��ӡÿ���ڵ��ֵ
		_InOrder(root->_right); // �ݹ����������
	}
public:
	// ���캯����ǿ�Ʊ������Լ����ɣ�
	BSTree() = default;

	// �������죨�����
	BSTree(const BSTree<K>& t)
	{
		_root = CopyTree(t._root);
	}

	// ��ֵ����
	BSTree<K>& operator=(BSTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}

	// ��������
	~BSTree()
	{
		DestroyTree(_root); // �ͷŶ���������еĽڵ�
		_root = nullptr; // �Ѹ��ڵ���Ϊ��
	}

	// ���Һ���(�ǵݹ�ʵ��)
	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key) // ���keyֵ���ڵ�ǰ�ڵ��ֵ
			{
				cur = cur->_right; // ��ȥ��ǰ�ڵ�����������в���
			}
			else if (cur->_key > key) // ���keyֵС�ڵ�ǰ�ڵ��ֵ
			{
				cur = cur->_left; // ��ȥ��ǰ�ڵ�����������в���
			}
			else // ��ǰ�ڵ��ֵ����keyֵ
			{
				return true; // ˵���ҵ��ˣ�ֱ�ӷ���true
			}
		}
		// ��Ϊ�ջ����ʧ�ܣ�����false
		return false;
	}

	// ���Һ���(�ݹ�ʵ��)
	bool FindR(const K& key)
	{
		return _FindR(_root, key); // ȥ���ò��ҵ��Ӻ���
	}

	// ���뺯��(�ǵݹ�ʵ��)
	bool Insert(const K& key)
	{
		// ��һ�β��룬���ڵ�Ϊ��
		if (_root == nullptr)
		{
			_root = new Node(key); // ֱ�Ӱ�key�ڵ���Ϊ���ĸ����
			return true; // ����ɹ�������true
		}

		// �ڶ��β����ʱ��
		Node* parent = nullptr; // ��¼cur�ĸ��ڵ�
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key) // key���ڵ�ǰ�ڵ㣬cur���ұ���
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key) // keyС�ڵ�ǰ�ڵ㣬cur�������
			{
				parent = cur;
				cur = cur->_left;
			}
			else // key���ڵ�ǰ�ڵ��ֵ
			{
				return false; // ����ʧ�ܣ�����false
			}
		}

		// ��ѭ��������˵��cur�ҵ��˿յ�λ��
		cur = new Node(key);
		if (parent->_key < key) // ���keyֵ���ڵ�ǰparent�ڵ��ֵ
		{
			parent->_right = cur; // �Ͱ�key���ӵ�parent���ұ�
		}
		else // ���keyֵС�ڵ�ǰparent�ڵ��ֵ
		{
			parent->_left = cur; // �Ͱ�key���ӵ�parent�����
		}

		// ����ɹ�������true
		return true; 
	}

	// ���뺯��(�ݹ�ʵ��)
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	// ɾ������(�ǵݹ�ʵ��)
	bool Erase(const K& key)
	{
		Node* parent = nullptr; // ��¼��ɾ���ڵ�ĸ��ڵ�
		Node* cur = _root; // ��¼ɾ���ڵ�

		while (cur) // ���ҵ�Ҫɾ���Ľڵ�
		{
			if (cur->_key < key) // key���ڵ�ǰ�ڵ��ֵ�������ýڵ������������
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key) // keyС�ڵ�ǰ�ڵ��ֵ�������ýڵ������������
			{
				parent = cur;
				cur = cur->_left;
			}
			else // �ҵ���Ҫɾ���Ľڵ㣬�������������
			{
				if (cur->_left == nullptr) // �����ɾ���ڵ��������Ϊ��
				{
					if (cur == _root) // ���Ҫɾ����cur�Ǹ��ڵ㣨��ʱparentΪnullptr��
					{
						_root = cur->_right; // ��ôֱ�ӰѶ���������ĸ��ڵ��Ϊcur���Һ��Ӽ���
					}
					else // ���Ҫɾ����cur���Ǹ��ڵ㣨��ʱparent��Ϊnullptr��
					{
						if (cur == parent->_left) // �����ɾ���ڵ�(cur)���丸�ڵ�(parent)������
						{
							parent->_left = cur->_right; // ��ô���ø��ڵ�(parent)����ָ��(left)ָ��ɾ���ڵ�(cur)��������
						}
						else // �����ɾ���ڵ�(cur)���丸�ڵ�(parent)���Һ���
						{
							parent->_right = cur->_right; // ��ô���ø��ڵ�(parent)����ָ��(right)ָ��ɾ���ڵ�(cur)��������
						}
					}
					delete cur; // �ͷŴ�ɾ���ڵ�
				}
				else if (cur->_right == nullptr) // �����ɾ���ڵ��������Ϊ��
				{
					if (cur == _root) // ���Ҫɾ����cur�Ǹ��ڵ㣨��ʱparentΪnullptr��
					{
						_root = cur->_left; // ��ôֱ�ӰѶ���������ĸ��ڵ��Ϊcur�����Ӽ���
					}
					else // ���Ҫɾ����cur���Ǹ��ڵ㣨��ʱparent��Ϊnullptr��
					{
						if (cur == parent->_left) // �����ɾ���ڵ�(cur)���丸�ڵ�(parent)������
						{
							parent->_left = cur->_left; // ��ô���ø��ڵ�(parent)����ָ��(left)ָ���ɾ���ڵ�(cur)��������
						}
						else // �����ɾ���ڵ�(cur)���丸�ڵ�(parent)���Һ���
						{
							parent->_right = cur->_left; // ��ô���ø��ڵ�(parent)����ָ��(left)ָ���ɾ���ڵ�(cur)��������
						}
					}
					delete cur; // �ͷŴ�ɾ���ڵ�
				}
				else // �����ɾ���ڵ��������������Ϊ��
				{
					// ����ѡ��������������Сֵ�ڵ��滻���������������ֵҲ���ԣ�
					Node* minParent = cur; // ��¼��ɾ���ڵ�����������ֵ��С�ڵ�ĸ��ڵ�
					Node* minRight = cur->_right; // ��¼��ɾ���ڵ�����������ֵ��С�Ľڵ�
					while (minRight->_left) // Ѱ�Ҵ�ɾ���ڵ�����������ֵ��С�Ľڵ�
					{
						minParent = minRight;
						minRight = minRight->_left;
					}
					// ѭ��������˵���ҵ���
					cur->_key = minRight->_key; // �Ѵ�ɾ���ڵ��ֵ�滻��minRight��ֵ
					if (minParent->_left == minRight) // ���minRight���丸�ڵ������
					{
						minParent->_left = minRight->_right; // ���ø��ڵ����ָ��(left)ָ��minRight������������
					} 
					else // ���minRight���丸�ڵ���Һ���
					{
						minParent->_right = minRight->_right; // ���ø��ڵ����ָ��(right)ָ��minRight������������
					}

					delete minRight; // �ͷ�minRight�ڵ�
				}
				return true; // ɾ���ɹ�������true
			}
		}
		return false; // û���ҵ���ɾ���ڵ㣬��ɾ��ʧ�ܣ�����false
	}

	// ɾ������(�ݹ�ʵ��)
	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

	// �������(�ݹ�ʵ��)
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	Node* _root = nullptr;
};

// ���Ժ���һ
void TestBSTree1()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();

	t.Insert(16);
	t.Insert(9);

	t.InOrder();
}

// ���Ժ�����
void TestBSTree2()
{
	BSTree<int> t;
	int a[] = { 8, 7, 9, 12, 5, 19, 20, 30, 7, 12 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
}

// ���Ժ�����
void TestBSTree3()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();

	t.Erase(3);
	t.Erase(8);

	t.InOrder();
	t.Erase(14);
	t.Erase(7);
	t.InOrder();

	for (auto e : a)
	{
		t.Erase(e);
	}
	t.InOrder();
}

// ���Ժ�����
void TestBSTree4()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();

	BSTree<int> copy = t;
	copy.InOrder();
}

// ���Ժ�����
void TestBSTree5()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		t.InsertR(e);
	}
	t.InOrder();

	t.InsertR(9);

	BSTree<int> copy = t;
	copy.InOrder();
}

// ���Ժ�����
void TestBSTree6()
{
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		t.InsertR(e);
	}
	t.InOrder();
	t.EraseR(3);
	t.EraseR(8);

	t.InOrder();
	t.EraseR(14);
	t.EraseR(7);
	t.InOrder();

	for (auto e : a)
	{
		t.EraseR(e);
	}
	t.InOrder();
}




