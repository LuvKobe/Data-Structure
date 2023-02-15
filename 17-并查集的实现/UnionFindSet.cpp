#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>

using namespace std;

// 并查集的实现
class UnionFindSet
{
public:
	// 构造函数
	UnionFindSet(size_t n)
		:_ufs(n, -1)
	{}

	// 查询操作（找到x所在树的根节点）
	int FindRoot1(int x)
	{
		int parent = x; // x下标存储的值是它父亲的下标
		while (_ufs[parent] >= 0) // 当父亲位置的值是一个非负数，那么需要寻找根节点
		{
			// 那么parent变成parent新的父节点继续进行查找操作
			parent = _ufs[parent];
		}
		// 程序走到这里，说明父亲位置里面存的是一个负数，即x的根节点
		return parent;
	}

	// 查询操作（路径压缩）
	size_t FindRoot2(int x)
	{
		// 先找到x的根节点节点
		int root = x;
		while (_ufs[root] >= 0)
			root = _ufs[root];

		// 路径压缩
		// 从上面查找x根节点的路径开始更新
		while (_ufs[x] >= 0) // 直到更新到 根节点！
		{
			//记录x的parnet，避免被修改
			int parent = _ufs[x];

			//直接让x作为root的子节点
			_ufs[x] = root;

			x = parent;
		}
		return x;
	}

	// 以下方面会溢出
	/*
	// 查询操作（路径压缩）
	int FindRoot2(int x)
	{
		int parent = x; // x下标存储的值是它父亲的下标
		while (_ufs[parent] >= 0) // 当父亲位置的值是一个非负数，那么需要寻找根节点
		{
			// 在查询中嵌入一个路径压缩操作
			// parent元素不再选择原来的父亲节点，而是直接选择父亲节点的父亲节点来做为自己新的一个父亲节点
			_ufs[parent] = _ufs[_ufs[parent]];

			// parent压缩完毕后且parent并不是根节点
			// 那么parent变成parent新的父节点继续进行查找和压缩的同时操作
			parent = _ufs[parent];
		}
		// 程序走到这里，说明父亲位置里面存的是一个负数，即x的根节点
		return parent;
	}*/

	// 合并操作（合并x1和x2）
	void Union(int x1, int x2)
	{
		int root1 = FindRoot2(x1); // 找到x1的根节点
		int root2 = FindRoot2(x2); // 找到x2的根节点

		// 如果root1和root2相等，说明它俩本身就是在一个集合，那么就没必要合并了
		if (root1 == root2)
			return;

		// 把小的根节点合并到大的根节点里面去
		// 默认root2大，root1小
		if (root1 > root2) // 如果root1大，root2小
			swap(root1, root2); // 那么就交换

		_ufs[root1] += _ufs[root2]; // 把root2所在树的节点个数添加到root1里面去
		_ufs[root2] = root1; // root2位置存在的根节点为root1
	}

	// 判断操作（判断x1和x2是否在同一个集合内）
	bool InSet(int x1, int x2)
	{
		// 直接返回结果即可
		return FindRoot2(x1) == FindRoot2(x2);
	}

	// 集合个数（找到这个数组有多少个集合）
	size_t SetSize()
	{
		size_t size = 0; // 统计集合的个数
		for (size_t i = 0; i < _ufs.size(); ++i) // 遍历真个数组
		{
			if (_ufs[i] < 0) // 如果i下标存储的元素小于0，说明就是一集合
			{
				++size; // 个数加1
			}
		}
		return size; // 返回集合的个数
	}
private:
	vector<int> _ufs; // 数组
};


int main()
{
	;
	return 0;
}









