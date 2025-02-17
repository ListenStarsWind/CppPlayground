#include<map>
#include<set>
#include<string>
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include"HashTable.h"
#include"unordered_set.h"
#include"unordered_map.h"
#include"bitset.h"

using namespace std;


//void Intuitive_feeling()
//{
//	unordered_set<int> s;
//	s.insert(3);
//	s.insert(1);
//	s.insert(5);
//	s.insert(3);
//	s.insert(8);
//	s.insert(2);
//
//	unordered_set<int>::iterator it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	unordered_map<string, int> count;
//	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
//	"苹果", "香蕉", "苹果", "香蕉" };
//	for (const auto& e : arr)
//	{
//		count[e]++;
//	}
//	for (const auto& e : count)
//	{
//		cout << e.first << ":" << e.second << endl;
//	}
//}
//
//void Performance_Comparison()
//{
//	const size_t N = 10000000;
//	vector<int> v(N);
//	srand(time(nullptr));  // 最多生成32768个随机数 
//	for (size_t i = 0; i < N; i++)
//	{
//		//v.push_back(rand());	 // N较大时 含有较多重复项
//		//v.push_back(rand() + i); // 重复项相对少
//		v.push_back(i);          // 没有重复项 但非常有序
//	}
//
//	set<int> s;
//	size_t begin1 = clock();
//	for (auto e : v)
//	{
//		s.insert(e);
//	}
//	size_t end1 = clock();
//
//
//	size_t begin2 = clock();
//	for (auto e : v)
//	{
//		s.find(e);
//	}
//	size_t end2 = clock();
//
//
//	size_t size1 = s.size();
//
//
//	size_t begin3 = clock();
//	for (auto e : v)
//	{
//		s.erase(e);
//	}
//	size_t end3 = clock();
//
//	cout << "set::" << endl;
//	cout << "插入个数" << size1 << endl;
//	cout << "插入时间" << end1 - begin1 <<"ms"<< endl;
//	cout << "查找时间" << end2 - begin1 <<"ms"<< endl;
//	cout << "删除时间" << end3 - begin3 <<"ms"<< endl<<endl;
//
//	unordered_set<int> us;
//	size_t begin4 = clock();
//	for (auto e : v)
//	{
//		us.insert(e);
//	}
//	size_t end4 = clock();
//
//
//	size_t begin5 = clock();
//	for(auto e : v)
//	{
//		us.find(e);
//	}
//	size_t end5 = clock();
//
//
//	size_t size2 = us.size();
//
//
//	size_t begin6 = clock();
//	for (auto e : v)
//	{
//		us.erase(e);
//	}
//	size_t end6 = clock();
//
//	cout << "unordered_set::" << endl;
//	cout << "插入个数" << size2 << endl;
//	cout << "插入时间" << end4 - begin4 << "ms" << endl;
//	cout << "查找时间" << end5 - begin5 << "ms" << endl;
//	cout << "删除时间" << end6 - begin6 << "ms" << endl;
//}

void test1()
{
	wind::HashTable<int, int> ht;
	ht.insert(std::make_pair(2, 0));
	ht.insert(std::make_pair(12, 0));
	ht.insert(std::make_pair(22, 0));
	ht.insert(std::make_pair(32, 0));
	ht.insert(std::make_pair(42, 0));
	ht.print();
	//ht.insert(std::make_pair(-3, 0));
	//ht.insert(std::make_pair(13, 0));
	//ht.insert(std::make_pair(23, 0));
	//ht.insert(std::make_pair(33, 0));
	//ht.insert(std::make_pair(43, 0));
	//ht.print();
	///*ht.erase(2);
	//ht.print();*/
	ht.erase(32);
	ht.print();
	std::cout << ht.find(32) << endl;
	//std::cout << "================" << std::endl;
	ht.insert(std::make_pair(32, 0));
	ht.print();
	//std::cout << "================" << std::endl;
	//ht.insert(std::make_pair(53, 0));
	//ht.print();
	///*ht.erase(22);
	//ht.print();
	//ht.erase(43);
	//ht.print();*/
}

void test2()
{
	wind::HashTable<std::string, int> ht;
	std::vector<std::string> v{ "apple", "banana", "cherry", "date", "elderberry" };
	for (auto e : v)
	{
		if (ht.find(e) == -1)
			ht.insert(std::make_pair(e, 0));
	}
	ht.print();
}

void test3()
{
	whisper::HashBucker<int, int> bt;
	bt.insert(make_pair(2, 0));
	bt.insert(make_pair(12, 0));
	bt.insert(make_pair(22, 0));
	bt.insert(make_pair(32, 0));
	bt.insert(make_pair(42, 0));
	bt.insert(make_pair(52, 0));
	bt.insert(make_pair(62, 0));
	bt.insert(make_pair(72, 0));
	bt.insert(make_pair(82, 0));
	bt.insert(make_pair(92, 0));
	bt.insert(make_pair(112, 0));
	bt.insert(make_pair(122, 0));
	bt.insert(make_pair(132, 0));
}

void test4()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	whisper::HashBucker<string, int> countMap;
	for (const auto& str : arr)
	{
		auto link = countMap.find(str);
		if (link == nullptr)
			countMap.insert(make_pair(str, 1));
		else
			link->_value.second++;
	}
	countMap.print();
}

void test5()
{
	const size_t N = 1000000;

	vector<int> v(N);               // 初始化为 N 个默认值
	srand(time(nullptr));           // 最多生成 32768 个随机数
	for (size_t i = 0; i < N; i++)
	{
		// v[i] = rand();            // N 较大时含有较多重复项
		v[i] = rand() + i;          // 重复项相对少
		// v[i] = i;                 // 没有重复项但非常有序
	}

	map<int, int> map_set;
	size_t insert_start = clock();
	for (auto key : v)
	{
		map_set.insert(make_pair(key, 0));
	}
	size_t insert_end = clock();

	size_t find_start = clock();
	for (auto key : v)
	{
		map_set.find(key);
	}
	size_t find_end = clock();

	size_t map_set_size = map_set.size();

	size_t erase_start = clock();
	for (auto key : v)
	{
		map_set.erase(key);
	}
	size_t erase_end = clock();

	cout << "set::" << endl;
	cout << "插入个数: " << map_set_size << endl;
	cout << "插入时间: " << insert_end - insert_start << "ms" << endl;
	cout << "查找时间: " << find_end - insert_start << "ms" << endl;
	cout << "删除时间: " << erase_end - erase_start << "ms" << endl << endl;

	unordered_map<int, int> unordered_map;
	size_t um_insert_start = clock();
	for (auto key : v)
	{
		unordered_map.insert(make_pair(key, 0));
	}
	size_t um_insert_end = clock();

	size_t um_find_start = clock();
	for (auto key : v)
	{
		unordered_map.find(key);
	}
	size_t um_find_end = clock();

	size_t um_size = unordered_map.size();
	size_t um_bucket_count = unordered_map.bucket_count();

	size_t max_bucket_size = 0;
	size_t non_empty_buckets_size = 0;
	for (size_t i = 0; i < um_bucket_count; i++)
	{
		size_t bucket_size = unordered_map.bucket_size(i);
		if (bucket_size > 0) non_empty_buckets_size++;
		max_bucket_size = max(max_bucket_size, bucket_size);
	}

	double load_factor = unordered_map.load_factor();
	double max_load_factor = unordered_map.max_load_factor();

	size_t um_erase_start = clock();
	for (auto key : v)
	{
		unordered_map.erase(key);
	}
	size_t um_erase_end = clock();

	cout << "unordered_map::" << endl;
	cout << "尝试插入个数: " << N << endl;
	cout << "当前最大个数: " << um_bucket_count << endl;
	cout << "成功插入个数: " << um_size << endl;
	cout << "整体插入时间: " << um_insert_end - um_insert_start << "ms" << endl;
	cout << "整体查找时间: " << um_find_end - um_find_start << "ms" << endl;
	cout << "整体删除时间: " << um_erase_end - um_erase_start << "ms" << endl;
	cout << "非空链表个数: " << non_empty_buckets_size << endl;
	cout << "最长链表长度: " << max_bucket_size << endl;
	cout << "最大负载因子: " << max_load_factor << endl;
	cout << "负载因子大小: " << load_factor << endl;
	cout << "链表平均长度: " << static_cast<double>(um_size) / static_cast<double>(non_empty_buckets_size) << endl;
	cout << endl;

	whisper::HashBucker<int, int> custom_hash;
	size_t hash_insert_start = clock();
	for (auto key : v)
	{
		custom_hash.insert(make_pair(key, 0));
	}
	size_t hash_insert_end = clock();

	size_t hash_find_start = clock();
	for (auto key : v)
	{
		custom_hash.find(key);
	}
	size_t hash_find_end = clock();

	size_t max_bucket_count_custom = 0, current_bucket_count = 0, list_count = 0, max_list_length = 0;
	double hash_load_factor = 0.0f, max_hash_load_factor = 0.0f, avg_list_length = 0.0f;

	custom_hash.bucketStats(max_bucket_count_custom, current_bucket_count, list_count, max_list_length, avg_list_length, hash_load_factor, max_hash_load_factor);

	size_t hash_erase_start = clock();
	for (auto key : v)
	{
		custom_hash.erase(key);
	}
	size_t hash_erase_end = clock();

	cout << "HashBucker::" << endl;
	cout << "尝试插入个数: " << N << endl;
	cout << "当前最大个数: " << max_bucket_count_custom << endl;
	cout << "成功插入个数: " << current_bucket_count << endl;
	cout << "整体插入时间: " << hash_insert_end - hash_insert_start << "ms" << endl;
	cout << "整体查找时间: " << hash_find_end - hash_find_start << "ms" << endl;
	cout << "整体删除时间: " << hash_erase_end - hash_erase_start << "ms" << endl;
	cout << "非空链表个数: " << list_count << endl;
	cout << "最长链表长度: " << max_list_length << endl;
	cout << "最大负载因子: " << max_hash_load_factor << endl;
	cout << "负载因子大小: " << hash_load_factor << endl;
	cout << "链表平均长度: " << avg_list_length << endl;
}

// 没迭代器前的功能测试
void test6()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	wind::unordered_map<string, int> countMap1;
	std::unordered_map<string, int> countMap2;
	for (const auto& str : arr)
	{
		countMap1[str]++;
		countMap2[str]++;
	}

	for (const auto& str : countMap2)
	{
		cout << str.first << "->";
		cout << countMap1[str.first] << endl;;
	}
}

// P.J 与 SGI STL区别
void test7()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	wind::unordered_map<string, int> countMap1;
	std::unordered_map<string, int> countMap2;
	for (const auto& str : arr)
	{
		countMap1[str]++;
		countMap2[str]++;
	}

	cout << "wind::" << endl;
	auto it1 = countMap1.begin();
	while (it1 != countMap1.end())
	{
		cout << it1->first << "->";
		cout << it1->second << endl;
		++it1;
	}

	cout << endl;

	cout << "std::" << endl;
	auto it2 = countMap2.begin();
	while (it2 != countMap2.end())
	{
		cout << it2->first << "->";
		cout << it2->second << endl;
		++it2;
	}
}

void test8()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	wind::unordered_map<string, int> countMap;
	for (const auto& str : arr)
	{
		countMap[str]++;
	}

	const wind::unordered_map<string, int>& ct = countMap;
	cout << "wind::" << endl;
	auto it = ct.begin();
	while (it != ct.end())
	{
		cout << it->first << "->";
		cout << it->second << endl;
		++it;
	}
}

void test9()
{
	wind::unordered_set<int> s;
	s.insert(3);
	s.insert(1);
	s.insert(5);
	s.insert(3);
	s.insert(8);
	s.insert(2);

	wind::unordered_set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	const auto& const_obj = s;
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
}

void test10()
{
	wind::bitset<100> bs;
	bs.set(40);
	bs.set(39);

	cout << bs.test(38) << endl;
	cout << bs.test(39) << endl;
	cout << bs.test(40) << endl;
	cout << bs.test(41) << endl;
	cout << bs.test(42) << endl << endl;

	bs.reset(40);

	cout << bs.test(38) << endl;
	cout << bs.test(39) << endl;
	cout << bs.test(40) << endl;
	cout << bs.test(41) << endl;
	cout << bs.test(42) << endl << endl;
}

void test11()
{
	wind::bitset<0x100000000u> bs;
	//wind::bitset<(unsigned int)-1 + 1> bs;
}

#include"BloomFilter.h"

#define N 1000000
#define TEST_SIZE 100000

string generate_random_string(size_t length) {
	static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string str(length, ' ');
	for (size_t i = 0; i < length; ++i) {
		str[i] = charset[rand() % (sizeof(charset) - 1)];
	}
	return str;
}

void simulation_test()
{
	srand(time(nullptr));
	BloomFilter<N> bf;
	unordered_set<string> test_data;
	for (size_t i = 0; i < N; i++)
	{
		test_data.insert(generate_random_string(rand() % 64 + 1));
	}

	for (const auto& str : test_data)
	{
		bf.set(str);
	}

	size_t false_positive_count = 0;
	for (size_t i = 0; i < TEST_SIZE; i++)
	{
		string str = generate_random_string(rand() % 64 + 1);
		if (bf.test(str) == true && test_data.count(str) == 0)
			false_positive_count++;
		if (bf.test(str) == false && test_data.count(str) == 1)
		{
			cout << "致命错误" << endl;
			return;
		}
	}

	cout << static_cast<double>(false_positive_count) / TEST_SIZE << endl;
}

int main()
{
	simulation_test();
	return 0;
}
