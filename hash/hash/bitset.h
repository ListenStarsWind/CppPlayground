#pragma once

#include<vector>

namespace wind
{
	
#define bitsizeof(type) (sizeof(type)*8)

	template<size_t N>
	class bitset
	{
		typedef int type;
		std::vector<type> _bits;

	public:
		bitset()
		{
			_bits.resize(N / bitsizeof(type) + 1);
		}

		// ��xӳ��ı���λ��Ϊ1
		void set(size_t x)
		{
			size_t i = x / bitsizeof(type);
			size_t j = x % bitsizeof(type);
			_bits[i] |= 1 << j;
		}

		// ��xӳ��ı���λ��Ϊ0
		void reset(size_t x)
		{
			size_t i = x / bitsizeof(type);
			size_t j = x % bitsizeof(type);
			_bits[i] &= (~(1 << j));
		}

		// ����xӳ�����λ��״̬
		bool test(size_t x)
		{
			size_t i = x / bitsizeof(type);
			size_t j = x % bitsizeof(type);
			return (_bits[i] >> j) & 1;
		}
	};

	template<size_t N>
	class twobitset
	{
		typedef bitset<N> bitset;

		bitset _bits1;
		bitset _bits2;

		/*
		00   û�г���
		01   ����һ��
		10   ��������
		11   �������
		*/

	public:
		void set(size_t x)
		{
			if (_bits1.test(x) == false && _bits2.test(x) == false)
			{
				_bits2.set(x);
			}
			else if (_bits1.test(x) == false && _bits2.test(x) == true)
			{
				_bits1.set(x);
				_bits2.reset(x);
			}
			else if (_bits1.test(x) == true && _bits2.test(x) == false)
			{
				_bits2.set(x);
			}
			else;
		}

		int count(size_t x)
		{
			bool m = _bits1.test(x);
			bool n = _bits2.test(x);

			if (m == false && n == false)
				return 0;
			else if (m == false && n == true)
				return 1;
			else if (m == true && n == false)
				return 2;
			else
				return -1;
		}
	};
}