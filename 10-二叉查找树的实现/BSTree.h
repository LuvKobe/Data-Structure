#pragma once
#include <iostream>
using namespace std;

// 节点类
template<class K>
struct BSTreeNode
{
	K _key; // 节点值
	BSTreeNode<K>* _left; // 左指针
	BSTreeNode<K>* _right; // 右指针

	// 构造函数
	BSTreeNode(const K& key)
		:_key(key)
		,_left(nullptr)
		,_right(nullptr)
	{}
};

// BST类
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node; // 把节点重定义成Node
private:
	// 拷贝树
	Node* CopyTree(Node* root)
	{
		// 如果是空树，直接返回空
		if (root == nullptr)
			return nullptr;

		Node* copyNode = new Node(root->_key); // 拷贝根结点
		copyNode->_left = CopyTree(root->_left); // 拷贝左子树
		copyNode->_right = CopyTree(root->_right); // 拷贝右子树

		return copyNode; // 返回拷贝的树
	}

	// 销毁函数(递归实现的子函数)
	void DestroyTree(Node* root)
	{
		// 如果是空树，直接返回空
		if (root == nullptr)
			return;

		DestroyTree(root->_left); // 递归释放左子树中的节点
		DestroyTree(root->_right); // 递归释放右子树中的节点
		delete root; // 删除根结点
	}

	// 查找函数(递归实现的子函数)
	bool _FindR(Node* root, const K& key)
	{
		// 如果是空树，那么直接返回空
		if (root == nullptr)
			return false;
		
		if (root->_key < key) // 如果key值大于根节点的值
		{
			return _FindR(root->_right, key); // 就去当根节点的右子树当中查找
		}
		else if (root->_key > key) // 如果key值小于根节点的值
		{
			return _FindR(root->_left, key); // 就去当根节点的左子树当中查找
		}
		else // 如果key值等于根节点的值
		{
			return true; // 查找成功，返回true
		}
	}

	// 插入函数(递归实现的子函数)
	bool _InsertR(Node*& root, const K& key) // 引用传参，root是_root的别名
	{
		if (root == nullptr) // 如果是空树
		{
			root = new Node(key); // 直接把key节点作为树的根结点
			return true; // 插入成功，返回true
		} 

		// 如果不是空树
		if (root->_key < key) // 如果key大于当前节点的值
		{
			return _InsertR(root->_right, key); // 把key插入到右子树当中
		}
		else if (root->_key > key) // 如果key小于当前节点的值
		{
			return _InsertR(root->_left, key); // 把key插入到左子树当中
		}
		else // 如果key等于当前节点的值
		{
			return false; // 插入失败，直接返回false
		}
	}

	// 删除函数(递归实现的子函数)
	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr) // 如果是空树
			return false; // 删除失败，直接返回false

		if (root->_key < key) // 如果key大于根节点的值
		{
			return _EraseR(root->_right, key); // 那么待删除节点在根的左子树当中
		}
		else if (root->_key > key) // 如果key小于根节点的值
		{
			return _EraseR(root->_left, key); // 那么待删除节点在根的右子树当中
		}
		else // 找到了待删除节点
		{
			Node* del = root; // 先保存根节点
			if (root->_left == nullptr) // 如果待删除节点的左子树为空
			{
				root = root->_right; // 那么根的右子树作为二叉树新的根节点
			}
			else if (root->_right == nullptr) // 如果待删除节点的右子树为空
			{
				root = root->_left; // 那么根的左子树作为二叉树新的根节点
			}
			else // 如果待删除节点的左右子树均不为空
			{
				Node* minRight = root->_right; // 记录根节点右子树当中值最小的节点
				while (minRight->_left) // 寻找根节点右子树当中值最小的节点
				{
					minRight = minRight->_left; // 右子树当中值最小的节点一定是在最左边，所以一直往左查找
				}
				// 找到以后，把根节点的值和minRight的值交换
				swap(root->_key, minRight->_key);
				return _EraseR(root->_right, key); // 此时，就转换成在根的右子树当中去删除这个key，这里删除这个key一定会走作为空的场景。
			}
			delete del; // 释放根节点
			return true; // 删除成功，返回true
		}
	}

	// 中序遍历(递归实现的子函数)
	void _InOrder(Node* root)
	{
		if (root == nullptr) // 如果是空树，直接返回空
			return;
		_InOrder(root->_left); // 递归遍历左子树
		cout << root->_key << " "; // 打印每个节点的值
		_InOrder(root->_right); // 递归遍历右子树
	}
public:
	// 构造函数（强制编译器自己生成）
	BSTree() = default;

	// 拷贝构造（深拷贝）
	BSTree(const BSTree<K>& t)
	{
		_root = CopyTree(t._root);
	}

	// 赋值重载
	BSTree<K>& operator=(BSTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}

	// 析构函数
	~BSTree()
	{
		DestroyTree(_root); // 释放二叉查找树中的节点
		_root = nullptr; // 把根节点置为空
	}

	// 查找函数(非递归实现)
	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key) // 如果key值大于当前节点的值
			{
				cur = cur->_right; // 就去当前节点的右子树当中查找
			}
			else if (cur->_key > key) // 如果key值小于当前节点的值
			{
				cur = cur->_left; // 就去当前节点的左子树当中查找
			}
			else // 当前节点的值等于key值
			{
				return true; // 说明找到了，直接返回true
			}
		}
		// 树为空或查找失败，返回false
		return false;
	}

	// 查找函数(递归实现)
	bool FindR(const K& key)
	{
		return _FindR(_root, key); // 去调用查找的子函数
	}

	// 插入函数(非递归实现)
	bool Insert(const K& key)
	{
		// 第一次插入，根节点为空
		if (_root == nullptr)
		{
			_root = new Node(key); // 直接把key节点作为树的根结点
			return true; // 插入成功，返回true
		}

		// 第二次插入的时候
		Node* parent = nullptr; // 记录cur的父节点
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key) // key大于当前节点，cur往右边走
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key) // key小于当前节点，cur往左边走
			{
				parent = cur;
				cur = cur->_left;
			}
			else // key等于当前节点的值
			{
				return false; // 插入失败，返回false
			}
		}

		// 当循环结束，说明cur找到了空的位置
		cur = new Node(key);
		if (parent->_key < key) // 如果key值大于当前parent节点的值
		{
			parent->_right = cur; // 就把key连接到parent的右边
		}
		else // 如果key值小于当前parent节点的值
		{
			parent->_left = cur; // 就把key连接到parent的左边
		}

		// 插入成功，返回true
		return true; 
	}

	// 插入函数(递归实现)
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	// 删除函数(非递归实现)
	bool Erase(const K& key)
	{
		Node* parent = nullptr; // 记录待删除节点的父节点
		Node* cur = _root; // 记录删除节点

		while (cur) // 先找到要删除的节点
		{
			if (cur->_key < key) // key大于当前节点的值，就往该节点的左子树查找
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key) // key小于当前节点的值，就往该节点的右子树查找
			{
				parent = cur;
				cur = cur->_left;
			}
			else // 找到了要删除的节点，分三种情况讨论
			{
				if (cur->_left == nullptr) // 如果待删除节点的左子树为空
				{
					if (cur == _root) // 如果要删除的cur是根节点（此时parent为nullptr）
					{
						_root = cur->_right; // 那么直接把二叉查找树的根节点改为cur的右孩子即可
					}
					else // 如果要删除的cur不是根节点（此时parent不为nullptr）
					{
						if (cur == parent->_left) // 如果待删除节点(cur)是其父节点(parent)的左孩子
						{
							parent->_left = cur->_right; // 那么就让父节点(parent)的左指针(left)指向删除节点(cur)的右子树
						}
						else // 如果待删除节点(cur)是其父节点(parent)的右孩子
						{
							parent->_right = cur->_right; // 那么就让父节点(parent)的右指针(right)指向删除节点(cur)的右子树
						}
					}
					delete cur; // 释放待删除节点
				}
				else if (cur->_right == nullptr) // 如果待删除节点的右子树为空
				{
					if (cur == _root) // 如果要删除的cur是根节点（此时parent为nullptr）
					{
						_root = cur->_left; // 那么直接把二叉查找树的根节点改为cur的左孩子即可
					}
					else // 如果要删除的cur不是根节点（此时parent不为nullptr）
					{
						if (cur == parent->_left) // 如果待删除节点(cur)是其父节点(parent)的左孩子
						{
							parent->_left = cur->_left; // 那么就让父节点(parent)的左指针(left)指向待删除节点(cur)的左子树
						}
						else // 如果待删除节点(cur)是其父节点(parent)的右孩子
						{
							parent->_right = cur->_left; // 那么就让父节点(parent)的右指针(left)指向待删除节点(cur)的左子树
						}
					}
					delete cur; // 释放待删除节点
				}
				else // 如果待删除节点的左右子树都不为空
				{
					// 这里选择用右子树的最小值节点替换（左子树当中最大值也可以）
					Node* minParent = cur; // 记录待删除节点右子树当中值最小节点的父节点
					Node* minRight = cur->_right; // 记录待删除节点右子树当中值最小的节点
					while (minRight->_left) // 寻找待删除节点右子树当中值最小的节点
					{
						minParent = minRight;
						minRight = minRight->_left;
					}
					// 循环结束，说明找到了
					cur->_key = minRight->_key; // 把待删除节点的值替换成minRight的值
					if (minParent->_left == minRight) // 如果minRight是其父节点的左孩子
					{
						minParent->_left = minRight->_right; // 就让父节点的左指针(left)指向minRight的右子树即可
					} 
					else // 如果minRight是其父节点的右孩子
					{
						minParent->_right = minRight->_right; // 就让父节点的右指针(right)指向minRight的右子树即可
					}

					delete minRight; // 释放minRight节点
				}
				return true; // 删除成功，返回true
			}
		}
		return false; // 没有找到待删除节点，即删除失败，返回false
	}

	// 删除函数(递归实现)
	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

	// 中序遍历(递归实现)
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	Node* _root = nullptr;
};

// 测试函数一
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

// 测试函数二
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

// 测试函数三
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

// 测试函数四
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

// 测试函数五
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

// 测试函数六
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




