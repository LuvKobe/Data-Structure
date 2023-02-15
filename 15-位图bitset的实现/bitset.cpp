#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>

using namespace std;

// N个比特位的位图
template<size_t N>
class BitSet
{
public:
	// 构造函数
	BitSet()
	{
		// +1保证了足够的比特位，最多浪费8个
		_bits.resize(N / 8 + 1, 0);
	}

	// 设置指定位（将x映射的位标记成1）
	void set(size_t x)
	{
		// x映射的比特位在第几个char对象
		size_t i = x / 8;

		// x在char第几个比特位
		size_t j = x % 8;

		// 先左移，再进行或运算
		_bits[i] |= (1 << j);
	}

	// 清空指定位（将x映射的位标记成0）
	void reset(size_t x)
	{
		// x映射的比特位在第几个char对象
		size_t i = x / 8;

		// x在char第几个比特位
		size_t j = x % 8;

		// 先左移，再按位取反，最后进行与运算
		_bits[i] &= (~(1 << j));
	}

	// 获取指定位的状态
	bool test(size_t x)
	{
		// x映射的比特位在第几个char对象
		size_t i = x / 8;

		// x在char第几个比特位
		size_t j = x % 8;

		// 先左移，再进行与运算，最后直接返回与运算的结果即可
		return _bits[i] & (1 << j);
	}

	// 容纳的比特位的个数
	size_t size()
	{
		return N;
	}

	//打印函数
	void Print()
	{
		int count = 0;
		size_t n = _bits.size();

		// 先打印前n-1个数
		for (size_t i = 0; i < n - 1; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				if (_bits[i] & (1 << j)) //该位被设置
					cout << "1";
				else //该位未被设置
					cout << "0";
				count++;
			}
		}

		// 再打印最后一个数的前(N%8)位
		for (size_t j = 0; j < N % 8; j++)
		{
			if (_bits[n - 1] & (1 << j)) //该位被设置
				cout << "1";
			else //该位未被设置
				cout << "0";
			count++;
		}
		cout << "\n" << count << endl; //打印总共打印的位的个数
	}
private:
	vector<char> _bits; // vector数组里面存的是一个char类型
};

void test_bit_set1()
{
	BitSet<40> bs;
	bs.set(18);

	// 查找18
	if (bs.test(18))
		cout << "18存在" << endl;
	else
		cout << "18不存在" << endl;

	// 查找19
	if (bs.test(19))
		cout << "19存在" << endl;
	else
		cout << "19不存在" << endl;
}


int main()
{
	test_bit_set1();

	return 0;
}


