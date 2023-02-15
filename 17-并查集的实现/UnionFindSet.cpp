#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>

using namespace std;

// ���鼯��ʵ��
class UnionFindSet
{
public:
	// ���캯��
	UnionFindSet(size_t n)
		:_ufs(n, -1)
	{}

	// ��ѯ�������ҵ�x�������ĸ��ڵ㣩
	int FindRoot1(int x)
	{
		int parent = x; // x�±�洢��ֵ�������׵��±�
		while (_ufs[parent] >= 0) // ������λ�õ�ֵ��һ���Ǹ�������ô��ҪѰ�Ҹ��ڵ�
		{
			// ��ôparent���parent�µĸ��ڵ�������в��Ҳ���
			parent = _ufs[parent];
		}
		// �����ߵ����˵������λ����������һ����������x�ĸ��ڵ�
		return parent;
	}

	// ��ѯ������·��ѹ����
	size_t FindRoot2(int x)
	{
		// ���ҵ�x�ĸ��ڵ�ڵ�
		int root = x;
		while (_ufs[root] >= 0)
			root = _ufs[root];

		// ·��ѹ��
		// ���������x���ڵ��·����ʼ����
		while (_ufs[x] >= 0) // ֱ�����µ� ���ڵ㣡
		{
			//��¼x��parnet�����ⱻ�޸�
			int parent = _ufs[x];

			//ֱ����x��Ϊroot���ӽڵ�
			_ufs[x] = root;

			x = parent;
		}
		return x;
	}

	// ���·�������
	/*
	// ��ѯ������·��ѹ����
	int FindRoot2(int x)
	{
		int parent = x; // x�±�洢��ֵ�������׵��±�
		while (_ufs[parent] >= 0) // ������λ�õ�ֵ��һ���Ǹ�������ô��ҪѰ�Ҹ��ڵ�
		{
			// �ڲ�ѯ��Ƕ��һ��·��ѹ������
			// parentԪ�ز���ѡ��ԭ���ĸ��׽ڵ㣬����ֱ��ѡ���׽ڵ�ĸ��׽ڵ�����Ϊ�Լ��µ�һ�����׽ڵ�
			_ufs[parent] = _ufs[_ufs[parent]];

			// parentѹ����Ϻ���parent�����Ǹ��ڵ�
			// ��ôparent���parent�µĸ��ڵ�������в��Һ�ѹ����ͬʱ����
			parent = _ufs[parent];
		}
		// �����ߵ����˵������λ����������һ����������x�ĸ��ڵ�
		return parent;
	}*/

	// �ϲ��������ϲ�x1��x2��
	void Union(int x1, int x2)
	{
		int root1 = FindRoot2(x1); // �ҵ�x1�ĸ��ڵ�
		int root2 = FindRoot2(x2); // �ҵ�x2�ĸ��ڵ�

		// ���root1��root2��ȣ�˵���������������һ�����ϣ���ô��û��Ҫ�ϲ���
		if (root1 == root2)
			return;

		// ��С�ĸ��ڵ�ϲ�����ĸ��ڵ�����ȥ
		// Ĭ��root2��root1С
		if (root1 > root2) // ���root1��root2С
			swap(root1, root2); // ��ô�ͽ���

		_ufs[root1] += _ufs[root2]; // ��root2�������Ľڵ������ӵ�root1����ȥ
		_ufs[root2] = root1; // root2λ�ô��ڵĸ��ڵ�Ϊroot1
	}

	// �жϲ������ж�x1��x2�Ƿ���ͬһ�������ڣ�
	bool InSet(int x1, int x2)
	{
		// ֱ�ӷ��ؽ������
		return FindRoot2(x1) == FindRoot2(x2);
	}

	// ���ϸ������ҵ���������ж��ٸ����ϣ�
	size_t SetSize()
	{
		size_t size = 0; // ͳ�Ƽ��ϵĸ���
		for (size_t i = 0; i < _ufs.size(); ++i) // �����������
		{
			if (_ufs[i] < 0) // ���i�±�洢��Ԫ��С��0��˵������һ����
			{
				++size; // ������1
			}
		}
		return size; // ���ؼ��ϵĸ���
	}
private:
	vector<int> _ufs; // ����
};


int main()
{
	;
	return 0;
}









