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

// 闭散列
namespace CloseHash
{
	// 记录每个数据的状态
	enum State
	{
		EMPTY, // 空
		EXITS, // 存在
		DELETE // 删除
	};

	// 每个位置存储的结构
	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv; // KV结构
		State _state = EMPTY; // 数据的状态（默认设为空）
	};

	// 哈希表
	template<class K, class V, class HashFunc = DefaultHash<K>>
	class HashTable
	{
		typedef HashData<K, V> Data;
	public:
		// 插入函数
		bool Insert(const pair<K, V>& kv)
		{
			// 1.判断哈希表中是否存在相同的键值对
			if (Find(kv.first))
			{
				return false; // 插入失败
			}

			// 2.调整负载因子，如果大于等于0.7，就扩容
			if (_tables.size() == 0 || _n * 10 / _tables.size() >= 7)
			{
				// 如果是空哈希表，那么初始化为10
				// 如果不是空哈希表，那么就扩大到原来的2倍
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

				// 扩容以后，需要重新映射
				HashTable<K, V, HashFunc> newHT;
				newHT._tables.resize(newSize);

				// 遍历旧表，将原哈希表当中的数据插入到新哈希表中
				for (auto& e : _tables)
				{
					if (e._state == EXITS)
					{
						newHT.Insert(e._kv);
					}
				}

				// 最后再交换新表和旧表中的数据
				newHT._tables.swap(_tables);
			}

			// 3.将键值对插入哈希表
			// a.先取模计算插入的位置
			HashFunc hf; // 用仿函数来判断key的类型
			size_t starti = hf(kv.first); // 拿到第一个数据
			starti %= _tables.size(); // 去模上表的容量（除数不能是capacity）

			size_t hashi = starti;
			size_t i = 1;

			// b.找到一个状态为EMPTY或DELETE的位置
			while (_tables[hashi]._state == EXITS)
			{
				hashi = starti + i; // 线性探测
				//hashi = starti + i * i; // 二次探测
				++i;
				hashi %= _tables.size(); // 防止下标超出哈希表范围
			}

			// c.将数据插入该位置，并将该位置的状态设置为EXIST
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXITS;
			_n++; // 哈希表中的有效元素个数加一

			// 插入成功
			return true;
		}

		// 查找函数
		Data* Find(const K& key)
		{
			// 1.如果哈希表大小为0，则查找失败
			if (_tables.size() == 0)
			{
				return nullptr;
			}

			// 2.开始查找
			HashFunc hf; // 用仿函数来判断key的类型
			size_t starti = hf(key);
			starti %= _tables.size();

			size_t hashi = starti;
			size_t i = 1;
			// 直到找到空位置就停下来
			while (_tables[hashi]._state != EMPTY)
			{
				// 如果该位置的状态不是DELETE，并且key值匹配，则查找成功
				if (_tables[hashi]._state != DELETE && _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi]; // 那么直接返回该位置的地址
				}

				hashi = starti + i; //线性探测
				//hashi = starti + i * i; // 二次探测
				++i;
				hashi %= _tables.size(); // 防止下标超出哈希表范围
			}

			// 直到找到空位置时，还没有找到目标元素，说明查找失败
			return nullptr;
		}

		// 删除函数
		bool Erase(const K& key)
		{
			// 1.查看哈希表中是否存在该键值的键值对
			Data* ret = Find(key);

			if (ret) // 如果存在
			{
				ret->_state = DELETE; // 则将该键值对所在位置的状态改为DELETE即可
				--_n; // 哈希表中的有效元素个数减一
				return true;
			}
			else // 如果不存在
			{
				return false; // 返回false
			}
		}
	private:
		vector<Data> _tables; // vector里面存的是一个结构体数组
		size_t _n = 0; // 存储关键字的个数
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
		string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

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

		HashTable<string, int> copy(countHT);
	}
}