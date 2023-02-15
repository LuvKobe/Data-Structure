#pragma once

#include <iostream>
#include <vector>
using namespace std;

// 定义结点的颜色
enum Colour
{
	RED,
	BLACK,
};

// 红黑树结点的定义
template<class K, class V>
struct RBTreeNode
{
	// 三叉链
	RBTreeNode<K, V>* _left; // 节点的左孩子
	RBTreeNode<K, V>* _right; // 节点的右孩子
	RBTreeNode<K, V>* _parent; // 节点的双亲（红黑树需要旋转，为了实现简单给出该字段）

	// 存储的键值对
	pair<K, V> _kv;

	// 结点的颜色
	Colour _col;

	// 构造函数
	RBTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)
	{}
};

// 红黑树
template<class K, class V>
struct RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	// 插入函数
	bool Insert(const pair<K, V>& kv)
	{
		// 如果红黑树是空树，把插入节点直接作为根节点
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK; // 根结点必须是黑色
			return true; // 插入成功
		}

		// 1.按照二叉搜索树的规则插入
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first) // 待插入节点的key值大于当前节点的key值
			{
				// 往右子树走
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first) // 待插入节点的key值小于当前节点的key值
			{
				// 往左子树走
				parent = cur;
				cur = cur->_left;
			}
			else // 待插入节点的key值等于当前节点的key值
			{
				return false; // 插入失败，返回false
			}
		}

		// 2.当循环结束，说明cur找到了空的位置，那么就插入
		cur = new Node(kv); // 构造一个新节点
		cur->_col = RED; // 插入结点的颜色设置为红色
		if (parent->_kv.first < kv.first) // 如果新节点的key值大于当前parent节点的key值
		{
			// 就把新节点链接到parent的右边
			parent->_right = cur;
		}
		else // 如果新节点的key值小于当前parent节点的key值
		{
			// 就把新节点链接到parent的左边
			parent->_left = cur;
		}
		cur->_parent = parent; // 别忘了把新节点里面的_parent指向parent(因为我们定义的是一个三叉链)

		// 3.若插入结点的父结点是红色的，则需要对红黑树进行调整（存在连续红色节点的情况）
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent; // 如果parent是红色，那么其父结点一定存在

			if (grandfather->_left == parent) // 当parent是grandfather的左孩子
			{
				Node* uncle = grandfather->_right; // uncle一定是grandfather的右孩子

				//情况一：uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					// 调整颜色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上调整
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 情况二 + 情况三：uncle不存在 + uncle存在且为黑
				{
					if (cur == parent->_left) 
					{
						//     g
						//   p
						// c
						RotateR(grandfather); //右单旋

						// 颜色调整
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else // cur == parent->_right
					{
						//     g
						//   p
						//     c 
						// 左右双旋
						RotateL(parent);
						RotateR(grandfather);

						// 颜色调整
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					// 子树旋转后，该子树的根变成了黑色，无需继续往上进行处理 
					break;
				}
			}
			else // parent是grandfather的右孩子
			{
				Node* uncle = grandfather->_left; // uncle是grandfather的左孩子

				// 情况一：uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					// 变色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 情况二 + 情况三：uncle不存在 + uncle存在且为黑
				{
					if (cur == parent->_right)
					{
						// g
						//   p
						//     c 
						RotateL(grandfather); // 左单旋

						// 颜色调整
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else // cur == parent->_left
					{
						// g
						//   p
						// c

						// 右左双旋
						RotateR(parent);
						RotateL(grandfather);

						// 颜色调整
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					// 子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					break;
				}
			}
		}
		_root->_col = BLACK; // 根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		return true; // 插入成功
	}

	// 左单旋（右边高需要左单旋）
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent; // 先保存parent的parent

		// 1.建立parent和subRL之间的关系
		parent->_right = subRL;
		if (subRL) // 如果subRL节点不为空，那么要更新它的parent
		{
			subRL->_parent = parent;
		}

		// 2.建立subR和parent之间的关系
		subR->_left = parent;
		parent->_parent = subR;

		// 3.建立ppNode和subR之间的关系（分情况讨论parent是整颗树的根，还是局部子树）
		if (parent == _root) // 当parent是根节点时
		{
			_root = subR; // subR就变成了新的根节点
			_root->_parent = nullptr; // 根节点的的parent为空
		}
		else // 当parent是整个树的局部子树时
		{
			if (parent == ppNode->_left) // 如果parent在ppNode的左边
			{
				ppNode->_left = subR; // 那么subR就是parent的左子树
			}
			else // 如果parent在ppNode的右边
			{
				ppNode->_right = subR; // 那么subR就是parent的右子树
			}
			subR->_parent = ppNode; // subR的parent还要指向ppNode
		}
	}

	// 右单旋（左边高就右单旋）
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		//Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		// 1.建立parent和subLR之间的关系
		parent->_left = subLR;
		if (subLR) // 如果subLR节点不为空，那么要更新它的parent
		{
			subLR->_parent = parent;
		}

		// 2.建立subL和parent之间的关系
		subL->_right = parent;
		parent->_parent = subL;

		// 3.建立ppNode和subL之间的关系（分情况讨论parent是整颗树的根，还是局部子树）
		if (parent == _root) // 当parent是根节点时
		{
			_root = subL; // subL就变成了新的根节点
			_root->_parent = nullptr; // 根节点的的parent为空
		}
		else // 当parent是整个树的局部子树时
		{
			if (parent == ppNode->_left) // 如果parent在ppNode的左边
			{
				ppNode->_left = subL; // 那么subL就是parent的左子树
			}
			else // 如果parent在ppNode的右边
			{
				ppNode->_right = subL; // 那么subL就是parent的右子树
			}
			subL->_parent = ppNode; // subR的parent还要指向ppNode
		}
	}

	// 中序遍历（子函数）（子函数）
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}

	// 计算红黑色的最长路径（子函数）
	int _maxHeight(Node* root)
	{
		if (root == nullptr)
			return 0;

		int lh = _maxHeight(root->_left);
		int rh = _maxHeight(root->_right);

		return lh > rh ? lh + 1 : rh + 1;
	}

	// 计算红黑色的最短路径（子函数）
	int _minHeight(Node* root)
	{
		if (root == nullptr)
			return 0;

		int lh = _minHeight(root->_left);
		int rh = _minHeight(root->_right);

		return lh < rh ? lh + 1 : rh + 1;
	}

	// 判断是否为红黑树（子函数）
	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		//走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}

		// 统计黑色节点的个数
		if (BLACK == pRoot->_col)
			k++;

		// 检测当前节点与其双亲是否都为红色
		if (RED == pRoot->_col && pRoot->_parent && pRoot->_parent->_col == RED)
		{
			cout << "违反性质三：存在连在一起的红色节点" << endl;
			return false;
		}

		return _IsValidRBTree(pRoot->_left, k, blackCount) &&
			_IsValidRBTree(pRoot->_right, k, blackCount);
	}

	// 查找函数
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key) // key值大于该结点的值
			{
				cur = cur->_left; // 在该结点的右子树当中查找
			}
			else if (cur->_kv.first < key) // key值小于该结点的值
			{
				cur = cur->_right; // 在该结点的左子树当中查找
			}
			else // 当前节点的值等于key值
			{
				return cur; //返回该结点
			}
		}
		return nullptr; //查找失败
	}
public:
	// 中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	// 计算高度
	void Height()
	{
		cout << "最长路径:" << _maxHeight(_root) << endl;
		cout << "最短路径:" << _minHeight(_root) << endl;
	}

	// 判断是否为红黑树
	bool IsBalanceTree()
	{
		// 检查红黑树几条规则

		Node* pRoot = _root;
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;

		// 检测根节点是否满足情况
		if (BLACK != pRoot->_col)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}

		// 获取任意一条路径中黑色节点的个数 -- 比较基准值
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_col)
				blackCount++;

			pCur = pCur->_left;
		}

		// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
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
	cout << "是否平衡?" << t.IsBalanceTree() << endl;
	t.Height();

	t.InOrder();
}