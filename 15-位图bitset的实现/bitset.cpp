#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>

using namespace std;

// N������λ��λͼ
template<size_t N>
class BitSet
{
public:
	// ���캯��
	BitSet()
	{
		// +1��֤���㹻�ı���λ������˷�8��
		_bits.resize(N / 8 + 1, 0);
	}

	// ����ָ��λ����xӳ���λ��ǳ�1��
	void set(size_t x)
	{
		// xӳ��ı���λ�ڵڼ���char����
		size_t i = x / 8;

		// x��char�ڼ�������λ
		size_t j = x % 8;

		// �����ƣ��ٽ��л�����
		_bits[i] |= (1 << j);
	}

	// ���ָ��λ����xӳ���λ��ǳ�0��
	void reset(size_t x)
	{
		// xӳ��ı���λ�ڵڼ���char����
		size_t i = x / 8;

		// x��char�ڼ�������λ
		size_t j = x % 8;

		// �����ƣ��ٰ�λȡ����������������
		_bits[i] &= (~(1 << j));
	}

	// ��ȡָ��λ��״̬
	bool test(size_t x)
	{
		// xӳ��ı���λ�ڵڼ���char����
		size_t i = x / 8;

		// x��char�ڼ�������λ
		size_t j = x % 8;

		// �����ƣ��ٽ��������㣬���ֱ�ӷ���������Ľ������
		return _bits[i] & (1 << j);
	}

	// ���ɵı���λ�ĸ���
	size_t size()
	{
		return N;
	}

	//��ӡ����
	void Print()
	{
		int count = 0;
		size_t n = _bits.size();

		// �ȴ�ӡǰn-1����
		for (size_t i = 0; i < n - 1; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				if (_bits[i] & (1 << j)) //��λ������
					cout << "1";
				else //��λδ������
					cout << "0";
				count++;
			}
		}

		// �ٴ�ӡ���һ������ǰ(N%8)λ
		for (size_t j = 0; j < N % 8; j++)
		{
			if (_bits[n - 1] & (1 << j)) //��λ������
				cout << "1";
			else //��λδ������
				cout << "0";
			count++;
		}
		cout << "\n" << count << endl; //��ӡ�ܹ���ӡ��λ�ĸ���
	}
private:
	vector<char> _bits; // vector������������һ��char����
};

void test_bit_set1()
{
	BitSet<40> bs;
	bs.set(18);

	// ����18
	if (bs.test(18))
		cout << "18����" << endl;
	else
		cout << "18������" << endl;

	// ����19
	if (bs.test(19))
		cout << "19����" << endl;
	else
		cout << "19������" << endl;
}


int main()
{
	test_bit_set1();

	return 0;
}


