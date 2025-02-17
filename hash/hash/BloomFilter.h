#pragma once

#include<bitset>

struct BKDRHash
{
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		for (auto e : key)
		{
			hash *= 131;
			hash += e;
		}
		return hash;
	}
};

struct RSHash
{
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		size_t magic = 63689;
		for (auto ch : key)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

struct APHash
{
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		size_t ch = 0;
		for (size_t i = 0; i < key.size(); i++)
		{
			ch = key[i];
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

template<size_t N, class type = std::string, class HashFcn1 = BKDRHash, class HashFcn2 = RSHash, class HashFcn3 = APHash>
class BloomFilter
{
private:
	std::bitset<4 * N> _bits;

public:
	void set(const type& key)
	{
		size_t i = HashFcn1()(key) % N;
		size_t j = HashFcn2()(key) % N;
		size_t k = HashFcn3()(key) % N;

		_bits.set(i);
		_bits.set(j);
		_bits.set(k);
	}

	bool test(const type& key)
	{
		size_t i = HashFcn1()(key) % N;
		if (!_bits.test(i)) return false;

		size_t j = HashFcn2()(key) % N;
		if (!_bits.test(j)) return false;

		size_t k = HashFcn3()(key) % N;
		if (!_bits.test(k)) return false;

		return true;
	}
};