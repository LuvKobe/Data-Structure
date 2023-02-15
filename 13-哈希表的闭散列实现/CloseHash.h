#pragma once

#include <iostream>
using namespace std;

#include <vector>

// Ĭ�����޷������͵ķº���
template<class K>
struct DefaultHash
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// �ַ����º���
// ��key��string��ʱ��default�����ػ��汾�Ĺ�ϣ
template<>
struct DefaultHash<string>
{
	size_t operator()(const string& key)
	{
		// �����һ���ַ�������Ҫ�Ȱ���ת������
		size_t hash = 0;
		for (auto ch : key)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

// ��ɢ��
namespace CloseHash
{
	// ��¼ÿ�����ݵ�״̬
	enum State
	{
		EMPTY, // ��
		EXITS, // ����
		DELETE // ɾ��
	};

	// ÿ��λ�ô洢�Ľṹ
	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv; // KV�ṹ
		State _state = EMPTY; // ���ݵ�״̬��Ĭ����Ϊ�գ�
	};

	// ��ϣ��
	template<class K, class V, class HashFunc = DefaultHash<K>>
	class HashTable
	{
		typedef HashData<K, V> Data;
	public:
		// ���뺯��
		bool Insert(const pair<K, V>& kv)
		{
			// 1.�жϹ�ϣ�����Ƿ������ͬ�ļ�ֵ��
			if (Find(kv.first))
			{
				return false; // ����ʧ��
			}

			// 2.�����������ӣ�������ڵ���0.7��������
			if (_tables.size() == 0 || _n * 10 / _tables.size() >= 7)
			{
				// ����ǿչ�ϣ����ô��ʼ��Ϊ10
				// ������ǿչ�ϣ����ô������ԭ����2��
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

				// �����Ժ���Ҫ����ӳ��
				HashTable<K, V, HashFunc> newHT;
				newHT._tables.resize(newSize);

				// �����ɱ���ԭ��ϣ���е����ݲ��뵽�¹�ϣ����
				for (auto& e : _tables)
				{
					if (e._state == EXITS)
					{
						newHT.Insert(e._kv);
					}
				}

				// ����ٽ����±�;ɱ��е�����
				newHT._tables.swap(_tables);
			}

			// 3.����ֵ�Բ����ϣ��
			// a.��ȡģ��������λ��
			HashFunc hf; // �÷º������ж�key������
			size_t starti = hf(kv.first); // �õ���һ������
			starti %= _tables.size(); // ȥģ�ϱ������������������capacity��

			size_t hashi = starti;
			size_t i = 1;

			// b.�ҵ�һ��״̬ΪEMPTY��DELETE��λ��
			while (_tables[hashi]._state == EXITS)
			{
				hashi = starti + i; // ����̽��
				//hashi = starti + i * i; // ����̽��
				++i;
				hashi %= _tables.size(); // ��ֹ�±곬����ϣ��Χ
			}

			// c.�����ݲ����λ�ã�������λ�õ�״̬����ΪEXIST
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXITS;
			_n++; // ��ϣ���е���ЧԪ�ظ�����һ

			// ����ɹ�
			return true;
		}

		// ���Һ���
		Data* Find(const K& key)
		{
			// 1.�����ϣ���СΪ0�������ʧ��
			if (_tables.size() == 0)
			{
				return nullptr;
			}

			// 2.��ʼ����
			HashFunc hf; // �÷º������ж�key������
			size_t starti = hf(key);
			starti %= _tables.size();

			size_t hashi = starti;
			size_t i = 1;
			// ֱ���ҵ���λ�þ�ͣ����
			while (_tables[hashi]._state != EMPTY)
			{
				// �����λ�õ�״̬����DELETE������keyֵƥ�䣬����ҳɹ�
				if (_tables[hashi]._state != DELETE && _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi]; // ��ôֱ�ӷ��ظ�λ�õĵ�ַ
				}

				hashi = starti + i; //����̽��
				//hashi = starti + i * i; // ����̽��
				++i;
				hashi %= _tables.size(); // ��ֹ�±곬����ϣ��Χ
			}

			// ֱ���ҵ���λ��ʱ����û���ҵ�Ŀ��Ԫ�أ�˵������ʧ��
			return nullptr;
		}

		// ɾ������
		bool Erase(const K& key)
		{
			// 1.�鿴��ϣ�����Ƿ���ڸü�ֵ�ļ�ֵ��
			Data* ret = Find(key);

			if (ret) // �������
			{
				ret->_state = DELETE; // �򽫸ü�ֵ������λ�õ�״̬��ΪDELETE����
				--_n; // ��ϣ���е���ЧԪ�ظ�����һ
				return true;
			}
			else // ���������
			{
				return false; // ����false
			}
		}
	private:
		vector<Data> _tables; // vector��������һ���ṹ������
		size_t _n = 0; // �洢�ؼ��ֵĸ���
	};

	// ���Ժ���һ
	void TestHT1()
	{
		int a[] = { 20, 5, 8, 99999, 10, 30, 50 };
		//HashTable<int, int, DefaultHash<int>> ht;
		HashTable<int, int> ht;

		if (ht.Find(10))
		{
			cout << "�ҵ���10" << endl;
		}

		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		// ��������
		ht.Insert(make_pair(15, 15));
		ht.Insert(make_pair(5, 5));
		ht.Insert(make_pair(15, 15));

		if (ht.Find(50))
		{
			cout << "�ҵ���50" << endl;
		}

		if (ht.Find(10))
		{
			cout << "�ҵ���10" << endl;
		}

		ht.Erase(10);
		ht.Erase(10);

		if (ht.Find(50))
		{
			cout << "�ҵ���50" << endl;
		}

		if (ht.Find(10))
		{
			cout << "�ҵ���10" << endl;
		}
	}

	// ���Ժ�����
	void TestHT2()
	{
		string arr[] = { "ƻ��", "����", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };

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