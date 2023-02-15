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

// ��ɢ�У���ϣͰ��
namespace Bucket
{
	// ÿ����ϣͰ�д洢���ݵĽṹ
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		// ���캯��
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}
	};

	// ��ϣ��
	template<class K, class V, class HashFunc = DefaultHash<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		// ��������
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

		// ul��ʾunsigned long
		size_t GetNextPrime(size_t prime)
		{
			const int PRIMECOUNT = 28;
			static const size_t primeList[PRIMECOUNT] =
			{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
			};

			// ��ȡ��prime�����һ������
			size_t i = 0;
			for (; i < PRIMECOUNT; ++i)
			{
				if (primeList[i] > prime)
					return primeList[i];
			}
			return primeList[i];
		}

		// ���뺯��
		bool Insert(const pair<K, V>& kv)
		{
			// 1.�鿴��ϣ�����Ƿ���ڸü�ֵ�ļ�ֵ��
			if (Find(kv.first))
			{
				return false; // ������ڣ������ʧ��
			}

			// 2.�ж��Ƿ���Ҫ������ϣ��Ĵ�С
			if (_tables.size() == _n) // �����ϣ��Ĵ�С���ڱ��е�Ԫ�ظ���
			{
				// �ѹ�ϣ��Ĵ�С����Ϊ����
				// ��������Ҫ����ʱ�����ڸ������������ҵ���һ��������Ϊ��ϣ�����ݺ�Ĵ�С����
				size_t newSize = GetNextPrime(_tables.size());
				vector<Node*> newTable;
				newTable.resize(newSize, nullptr);

				// ��ԭ��ϣ����ÿ��λ�ô洢�ĵ�������뵽�¹�ϣ��
				HashFunc hf; // �÷º������ж�key������
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i]; // ��¼ԭ��ϣ���е�һ����ϣͰ�Ľڵ㣨��¼�������ͷ�ڵ㣩
					while (cur) // ��ϣͰ��Ϊ�գ�����ѭ����ͷ�ڵ㲻Ϊ�գ�Ҳ���ǵ�����Ϊ�գ�����ѭ����
					{
						Node* next = cur->_next; // ��¼cur����һ�����

						// ͨ����ϣ�������ҵ�ԭ��ϣ���У���һ����ϣͰ����ĵ�һ���ڵ㣬Ȼ��ͨ����ϣ�����ѽڵ�����ת��������
						// ���ż����������͵Ĺ�ϣ��ַ��Ҳ���Ƕ�Ӧ�Ĺ�ϣͰ���hashi
						size_t hashi = hf(cur->_kv.first) % newSize;

						cur->_next = newTable[hashi]; // ���ý��ͷ�嵽�¹�ϣ���б��Ϊhashi�Ĺ�ϣͰ��
						newTable[hashi] = cur;

						cur = next; // ȡԭ��ϣ���и�Ͱ����һ�����
					}
					// ��Ͱȡ��󽫸�Ͱ�ÿ�
					_tables[i] = nullptr;
				}
				// ������������ϣ��
				newTable.swap(_tables);
			}

			//3.����ֵ�Բ����ϣ��
			HashFunc hf; // �÷º������ж�key������
			size_t hashi = hf(kv.first); // ��ͨ����ϣ������keyתΪ����
			hashi %= _tables.size(); // Ȼ��������Ӧ�Ĺ�ϣͰ���

			// ͷ�嵽��Ӧ��Ͱ����
			Node* newnode = new Node(kv); // �¿���һ����������
			newnode->_next = _tables[hashi]; // ���ý��ͷ�嵽�¹�ϣ���б��Ϊhashi�Ĺ�ϣͰ��
			_tables[hashi] = newnode; // �ѹ�ϣͰ�е�һ���ڵ����Ϊ�ող���Ľڵ㣨��������ͷ�ڵ㣩

			// 4.��ϣ���е���ЧԪ�ظ�����һ
			++_n;

			return true; // ����ɹ�
		}

		//// ���뺯��
		//bool Insert(const pair<K, V>& kv)
		//{
		//	// 1.�鿴��ϣ�����Ƿ���ڸü�ֵ�ļ�ֵ��
		//	if (Find(kv.first))
		//	{
		//		return false; // ������ڣ������ʧ��
		//	}

		//	// 2.�ж��Ƿ���Ҫ������ϣ��Ĵ�С
		//	if (_tables.size() == _n) // �����ϣ��Ĵ�С���ڱ��е�Ԫ�ظ���
		//	{
		//		// �����ϣ���СΪ 0���򽫹�ϣ��ĳ�ʼ��С����Ϊ 10
		//		// Ȼ�󴴽�һ���µĹ�ϣ���¹�ϣ��Ĵ�С����Ϊԭ��ϣ���2��������ʼ��Ϊnullptr
		//		size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
		//		vector<Node*> newTable;
		//		newTable.resize(newSize, nullptr);

		//		// ��ԭ��ϣ����ÿ��λ�ô洢�ĵ�������뵽�¹�ϣ��
		//		for (size_t i = 0; i < _tables.size(); ++i)
		//		{
		//			Node* cur = _tables[i]; // ��¼ԭ��ϣ���е�һ����ϣͰ�Ľڵ㣨��¼�������ͷ�ڵ㣩
		//			while (cur) // ��ϣͰ��Ϊ�գ�����ѭ����ͷ�ڵ㲻Ϊ�գ�Ҳ���ǵ�����Ϊ�գ�����ѭ����
		//			{
		//				Node* next = cur->_next; // ��¼cur����һ�����

		//				// ͨ����ϣ�������ҵ�ԭ��ϣ���У���һ����ϣͰ����ĵ�һ���ڵ㣬Ȼ��ͨ����ϣ�����ѽڵ�����ת��������
		//				// ���ż����������͵Ĺ�ϣ��ַ��Ҳ���Ƕ�Ӧ�Ĺ�ϣͰ���hashi
		//				size_t hashi = hf(cur->_kv.first) % newSize; 

		//				cur->_next = newTable[hashi]; // ���ý��ͷ�嵽�¹�ϣ���б��Ϊhashi�Ĺ�ϣͰ��
		//				newTable[hashi] = cur;

		//				cur = next; // ȡԭ��ϣ���и�Ͱ����һ�����
		//			}
		//			// ��Ͱȡ��󽫸�Ͱ�ÿ�
		//			_tables[i] = nullptr;
		//		}
		//		// ������������ϣ��
		//		newTable.swap(_tables);
		//	}
		//
		//	//3.����ֵ�Բ����ϣ��
		//	HashFunc hf; // �÷º������ж�key������
		//	size_t hashi = hf(kv.first); // ��ͨ����ϣ������keyתΪ����
		//	hashi %= _tables.size(); // Ȼ��������Ӧ�Ĺ�ϣͰ���

		//	// ͷ�嵽��Ӧ��Ͱ����
		//	Node* newnode = new Node(kv); // �¿���һ����������
		//	newnode->_next = _tables[hashi]; // ���ý��ͷ�嵽�¹�ϣ���б��Ϊhashi�Ĺ�ϣͰ��
		//	_tables[hashi] = newnode; // �ѹ�ϣͰ�е�һ���ڵ����Ϊ�ող���Ľڵ㣨��������ͷ�ڵ㣩

		//	// 4.��ϣ���е���ЧԪ�ظ�����һ
		//	++_n;

		//	return true; // ����ɹ�
		//}

		// ���Һ���
		Node* Find(const K& key)
		{
			// 1.�����ϣ���СΪ0�������ʧ��
			if (_tables.size() == 0)
			{
				return nullptr;
			}

			// 2.��ʼ����
			HashFunc hf; // �÷º������ж�key������
			size_t hashi = hf(key); // ��ͨ����ϣ������keyתΪ����
			hashi %= _tables.size(); // Ȼ��������Ӧ�Ĺ�ϣͰ���
			Node* cur = _tables[hashi]; // ��¼��ϣͰ����ĵ�һ���ڵ㣬Ҳ���ǵ������ͷ�ڵ�
			
			// ��ʼ����������ϣͰ
			while (cur) 
			{
				if (cur->_kv.first == key) // ���keyֵƥ�䣬����ҳɹ�
				{
					return cur; // ���ؽڵ�ָ��
				}
				cur = cur->_next; 
			}
			// ����ѹ�ϣͰȫ�������껹û���ҵ�Ŀ��Ԫ�أ������ʧ��
			return nullptr;
		}

		// ɾ������
		bool Erase(const K& key)
		{
			// 1.�����ϣ��Ĵ�СΪ0����ɾ��ʧ��
			if (_tables.size() == 0)
			{
				return false;
			}

			// 2.�ڱ��Ϊhashi�Ĺ�ϣͰ��Ѱ�Ҵ�ɾ�����
			HashFunc hf; // �÷º������ж�key������
			size_t hashi = hf(key); // ��ͨ����ϣ������keyתΪ����
			hashi %= _tables.size(); // Ȼ��������Ӧ�Ĺ�ϣͰ���
			Node* prev = nullptr; // ����ǰ��ָ�룬��ʼ����
			Node* cur = _tables[hashi]; // ��¼��ϣͰ����ĵ�һ���ڵ㣬Ҳ���ǵ������ͷ�ڵ�
			
			// ��ʼ����������ϣͰ
			while (cur)
			{
				if (cur->_kv.first == key) // ���keyֵƥ�䣬˵���ҵ��˴�ɾ����㣬��ɾ���ý��
				{
					if (prev == nullptr) // �����ɾ������ǹ�ϣͰ�еĵ�һ�����
					{
						_tables[hashi] = cur->_next; // ����һ�����Ӹù�ϣͰ���Ƴ�
					}
					else // �����ɾ����㲻�ǹ�ϣͰ�ĵ�һ�����
					{
						prev->_next = cur->_next; // ����cur��ǰ���ڵ�ָ��cur����һ���ڵ�
					}

					// Ȼ���ͷŵ�cur 
					delete cur;

					// ɾ���ɹ�
					return true;
				}

				prev = cur; // ��ǰ���ڵ����Ϊcur

				cur = cur->_next; // curָ��������һ���ڵ�
			}
			// �����ϣͰȫ��������ϻ�û���ҵ���ɾ��Ԫ�أ���ɾ��ʧ��
			return false;
		}
	private:
		// ָ������
		vector<Node*> _tables; // ��ϣ��
		size_t _n = 0; // ��ϣ���е���ЧԪ�ظ���
	};
}





