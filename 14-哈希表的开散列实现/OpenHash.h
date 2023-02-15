#pragma once

#include <iostream>
using namespace std;

#include <vector>

// 默认是无符号整型的仿函数
template<class K>
struct DefaultHash
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 字符串仿函数
// 当key是string的时候，default就是特化版本的哈希
template<>
struct DefaultHash<string>
{
	size_t operator()(const string& key)
	{
		// 如果是一个字符串，需要先把它转成整数
		size_t hash = 0;
		for (auto ch : key)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

// 开散列（哈希桶）
namespace Bucket
{
	// 每个哈希桶中存储数据的结构
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		// 构造函数
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}
	};

	// 哈希表
	template<class K, class V, class HashFunc = DefaultHash<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		// 析构函数
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}

				_tables[i] = nullptr;
			}
		}

		// 插入函数
		bool Insert(const pair<K, V>& kv)
		{
			// 1.查看哈希表中是否存在该键值的键值对
			if (Find(kv.first))
			{
				return false; // 如果存在，则插入失败
			}

			// 2.判断是否需要调整哈希表的大小
			if (_tables.size() == _n) // 如果哈希表的大小等于表中的元素个数
			{
				// 如果哈希表大小为 0，则将哈希表的初始大小设置为 10
				// 然后创建一个新的哈希表，新哈希表的大小设置为原哈希表的2倍，并初始化为nullptr
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				vector<Node*> newTable;
				newTable.resize(newSize, nullptr);

				// 将原哈希表当中每个位置存储的单链表插入到新哈希表
				HashFunc hf; // 用仿函数来判断key的类型
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i]; // 记录原哈希表中第一个哈希桶的节点（记录单链表的头节点）
					while (cur) // 哈希桶不为空，进入循环（头节点不为空，也就是单链表不为空，进入循环）
					{
						Node* next = cur->_next; // 记录cur的下一个结点

						// 通过哈希函数，找到原哈希表中，第一个哈希桶里面的第一个节点，然后通过哈希函数把节点数据转换成整型
						// 接着计算出这个整型的哈希地址，也就是对应的哈希桶编号hashi
						size_t hashi = hf(cur->_kv.first) % newSize; 

						cur->_next = newTable[hashi]; // 将该结点头插到新哈希表中编号为hashi的哈希桶中
						newTable[hashi] = cur;

						cur = next; // 取原哈希表中该桶的下一个结点
					}
					// 该桶取完后将该桶置空
					_tables[i] = nullptr;
				}
				// 交换这两个哈希表
				newTable.swap(_tables);
			}
		
			//3.将键值对插入哈希表
			HashFunc hf; // 用仿函数来判断key的类型
			size_t hashi = hf(kv.first); // 先通过哈希函数把key转为整型
			hashi %= _tables.size(); // 然后计算出对应的哈希桶编号

			// 头插到对应的桶即可
			Node* newnode = new Node(kv); // 新开辟一个待插入结点
			newnode->_next = _tables[hashi]; // 将该结点头插到新哈希表中编号为hashi的哈希桶中
			_tables[hashi] = newnode; // 把哈希桶中第一个节点更新为刚刚插入的节点（更新链表头节点）

			// 4.哈希表中的有效元素个数加一
			++_n;

			return true; // 插入成功
		}

		// 查找函数
		Node* Find(const K& key)
		{
			// 1.如果哈希表大小为0，则查找失败
			if (_tables.size() == 0)
			{
				return nullptr;
			}

			// 2.开始查找
			HashFunc hf; // 用仿函数来判断key的类型
			size_t hashi = hf(key); // 先通过哈希函数把key转为整型
			hashi %= _tables.size(); // 然后计算出对应的哈希桶编号
			Node* cur = _tables[hashi]; // 记录哈希桶里面的第一个节点，也就是单链表的头节点

			// 开始遍历整个哈希桶
			while (cur)
			{
				if (cur->_kv.first == key) // 如果key值匹配，则查找成功
				{
					return cur; // 返回节点指针
				}
				cur = cur->_next;
			}
			// 如果把哈希桶全部遍历完还没有找到目标元素，则查找失败
			return nullptr;
		}

		// 删除函数
		bool Erase(const K& key)
		{
			// 1.如果哈希表的大小为0，则删除失败
			if (_tables.size() == 0)
			{
				return false;
			}

			// 2.在编号为hashi的哈希桶中寻找待删除结点
			HashFunc hf; // 用仿函数来判断key的类型
			size_t hashi = hf(key); // 先通过哈希函数把key转为整型
			hashi %= _tables.size(); // 然后计算出对应的哈希桶编号
			Node* prev = nullptr; // 定义前驱指针，初始化空
			Node* cur = _tables[hashi]; // 记录哈希桶里面的第一个节点，也就是单链表的头节点

			// 开始遍历整个哈希桶
			while (cur)
			{
				if (cur->_kv.first == key) // 如果key值匹配，说明找到了待删除结点，则删除该结点
				{
					if (prev == nullptr) // 如果待删除结点是哈希桶中的第一个结点
					{
						_tables[hashi] = cur->_next; // 将第一个结点从该哈希桶中移除
					}
					else // 如果待删除结点不是哈希桶的第一个结点
					{
						prev->_next = cur->_next; // 则让cur的前驱节点指向cur的下一个节点
					}

					// 然后释放掉cur 
					delete cur;

					// 删除成功
					return true;
				}

				prev = cur; // 把前驱节点更新为cur

				cur = cur->_next; // cur指向它的下一个节点
			}
			// 如果哈希桶全部遍历完毕还没有找到待删除元素，则删除失败
			return false;
		}
	private:
		// 指针数组
		vector<Node*> _tables; // 哈希表
		size_t _n = 0; // 哈希表中的有效元素个数
	};

	// 测试函数一
	void TestHT1()
	{
		int a[] = { 20, 5, 8, 99999, 10, 30, 50 };
		//HashTable<int, int, DefaultHash<int>> ht;
		HashTable<int, int> ht;

		if (ht.Find(10))
		{
			cout << "找到了10" << endl;
		}

		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		// 测试扩容
		ht.Insert(make_pair(15, 15));
		ht.Insert(make_pair(5, 5));
		ht.Insert(make_pair(15, 15));

		if (ht.Find(50))
		{
			cout << "找到了50" << endl;
		}

		if (ht.Find(10))
		{
			cout << "找到了10" << endl;
		}

		ht.Erase(10);
		ht.Erase(10);

		if (ht.Find(50))
		{
			cout << "找到了50" << endl;
		}

		if (ht.Find(10))
		{
			cout << "找到了10" << endl;
		}
	}

	// 测试函数二
	void TestHT2()
	{
		string arr[] = { "苹果", "柠檬", "苹果", "柠檬", "苹果", "苹果", "柠檬", "苹果", "香蕉", "苹果", "香蕉" };

		HashTable<string, int> countHT;

		for (auto& str : arr)
		{
			auto ret = countHT.Find(str);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				countHT.Insert(make_pair(str, 1));
			}
		}

		cout << endl;
	}
}






