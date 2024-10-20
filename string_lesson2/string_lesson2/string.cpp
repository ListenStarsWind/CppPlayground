#include"string.h"
const size_t wind::string::npos = -1;

wind::string::string(const char* str)
	:_str(nullptr)
	,_size(strlen(str))
	,_capacity(_size)
{
	// 注意，_capacity指的是可以容纳的有效字符个数
	// 它与开辟空间的大小不是同一概念
	// 为了兼容C语言，开辟空间的最后一个字符必须是'\0'
	// 而char* str身为C中的字符串最后一位就是'\0'
	// 所以_capacity的初始化是就是char* str的长度

	_str = new char[_capacity + 1];
	// 留一个成员空间，用来放`\0`

	strcpy(_str, str);
	// 严格来说，应该用memcpy，但既然确定
	// 不使用模版而使用char来写
	// 那就用C中的字符串相关函数
}

/*
// 因为初始化列表的初始化顺序是按照声明来写的
// 所以会先执行_str(new char[_capacity + 1])
// 但此时_size还未被定义
// 从而引发错误
wind::string::string(const char* str)
	:_size(strlen(str))
	,_capacity(_size + 1)
	,_str(new char[_capacity + 1])
{
	// 略
}
*/

// 这真的没什么好说的
wind::string::~string()
{
	delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}

wind::string::string()
	:_str(new char[1] {0})
	,_size(0)
	,_capacity(0)
{
	// C语言规定字符串的最后一位是'\0'
	// 这对空字符串仍然使用，所以要再
	// 开辟一个成员空间存放'\0'
	
	// 前面说过，我们的STL是SGI版本的
	// 之前我们试过，P.J.版本的string
	// 无参构造是会开辟多个空间的
	// 很明显打印P.J.版本的空string
	// 对象是不会打印出任何东西的
	// 所以个人猜测P.J.版本的空string
	// 对象最起码开头也要上道保险性质的'\0'
	// 防止打印出其它内容
}

size_t wind::string::size()const
{
	return _size;
}

size_t wind::string::capacity()const
{
	return _capacity;
}

char& wind::string::operator[](size_t pos)
{
	assert(pos < _size);
	return _str[pos];
}

const char& wind::string::operator[](size_t pos)const
{
	assert(pos < _size);
	return _str[pos];
}

wind::string::iterator wind::string::begin()
{
	return _str;
}

wind::string::iterator wind::string::end()
{
	return _str + _size;
}

wind::string::const_iterator wind::string::begin()const
{
	return _str;
}

wind::string::const_iterator wind::string::end()const
{
	return _str + _size;
}

void wind::string::reserve(size_t n)
{
	// 以前试过的，对于小于当前容量的参数
	// SGI和P.J.函数都不作处理
	if (n > _capacity)
	{
		// 注意，_capacity指的是可容纳的有效数据个数
		// 不是开辟空间的成员个数，要额外加一存'\0'

		// C++没原地扩容
		// 所以就new出来一个新空间
		// 然后再从原空间里拷贝内容

		auto p = new char[n + 1];
		strcpy(p, _str);
		delete[] _str;
		_str = p;
		_capacity = n;
	}
}

void wind::string::push_back(const char ch)
{
	if (_size == _capacity)
	{
		// 为了防止_capacity初始值为0
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}

void wind::string::append(const char* str)
{
	size_t len = strlen (str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}
	strcpy(_str + _size, str);
	_size += len;
}

wind::string& wind::string::operator+=(const char ch)
{
	this->push_back(ch);
	return *this;
}

wind::string& wind::string::operator+=(const char* str)
{
	this->append(str);
	return *this;
}

wind::string& wind::string::insert(size_t pos, const char* str)
{
	// 插入位置合法性检查
	assert(pos <= _size);
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}
	size_t source = _size;
	size_t destination = _capacity;

	// 因为下标使用无符号整型
	// 所以很容易出现((size_t)-1) > ((size_t)others)

	// 强制类型转换或者把sour和dest用int类型也不行
	// 一是可能存在int溢出危险
	// 二是C++和C都有一个“算数转换”的说法：
	// 如果某个操作符的各个操作数属于不同的类型，那么
	// 除⾮其中⼀个操作数的转换为另⼀个操作数的类型
	// 否则操作就⽆法进⾏
	// 当int与size_t作比较时，int会被自动强转为size_t

	// 亦不能使用strcpy，因为待填充的空间可能与有限成员空间重叠
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// 退出循环，无非是两种情况：
	// source == 0：source已经处于临界值，再减就要变成最大值了
	// source < pos：不用再拷贝了
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// strcpy有'\0'，所以不能用
	memcpy(_str + pos, str, strlen(str));


	_size += len;

	return *this;
} 

const char* wind::string::c_str()
{
	return _str;
}

const char* wind::string::c_str()const
{
	return _str;
}

wind::string& wind::string::insert(size_t pos, const string& s)
{
	this->insert(pos, s._str);
	return *this;
}

wind::string& wind::string::insert(size_t pos, const char ch)
{
	assert(pos <= _size);
	if (_size == _capacity)
	{
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	size_t source = _size;
	size_t destination = source + 1;
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	_str[pos] = ch;
	_size++;
	return *this;
}

bool wind::operator>(const wind::string& s1, const wind::string& s2)
{
	// 模版当然不是这样写的，可能是以迭代器或者[]重载的形式
	// 一个个比较成员，但我们这里不是用模版的，所以就直接用
	if (strcmp(s1.c_str(), s2.c_str()) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) > 0)
		return true;
	else
		return false;
}


bool wind::operator==(const wind::string& s1, const wind::string& s2)
{
	if (strcmp(s1.c_str(), s2.c_str()) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) == 0)
		return true;
	else
		return false;
}


bool wind::operator<(const wind::string& s1, const wind::string& s2)
{
	if (s1 > s2 || s1 == s2)
		return false;
	else
		return true;
}

bool wind::operator<(const wind::string& s, const char* str)
{
	if (s > str || s == str)
		return false;
	else
		return true;
}

bool wind::operator<(const char* str, const string& s)
{
	if (str > s || str == str)
		return false;
	else
		return true;
}

std::ostream& wind::operator<<(std::ostream& out, const string& s)
{
	for (auto ch : s)
	{
		out << ch;
	}
	return out;
}

std::istream& wind::operator>>(std::istream& in, string& s)
{
	s.clear();
	// 为了区分多个对象的流提取
	// C++或者C默认以空格和换行为分隔符
	// 但这也为包含空格字符串的提取
	// 造成了困难，istream中的成员
	// 函数get可以自定义分隔符


	//// 空格和换行会被默认为分隔符
	//// 所以不会被提取
	//// 这会使得程序进入死循环
	//char ch;
	//in >> ch;
	//while (ch != ' ' && ch != '\n')
	//{
	//	s += ch;
	//}

	
	/*
	char ch;
	ch = in.get();
	while (ch != ' ' && ch != '\n')
	{
		s += ch;
	}
	这种写法虽然可行
	但扩容频繁效率较低
	*/

	// 字符缓冲区
	char buff[16];
	int curr = 0;
	char tmp;
	do
	{
		// 字符先存储入缓冲区
		tmp = in.get();
		buff[curr++] = tmp;

		// 当缓冲区满后
		// 一次性存入
		if (curr == 15)
		{
			buff[curr] = '\0';
			curr = 0;
			s += buff;
		}
	}while (tmp != ' ' && tmp != '\n');

	// 跳出循环，说明上一个位是
	// 终止位，将其改为'\0'
	buff[curr - 1] = '\0';
	s += buff;

	return in;
}

wind::string& wind::string::get(char delim, std::istream& in)
{
	char buff[16];
	int curr = 0;
	char tmp;
	do
	{
		tmp = in.get();
		buff[curr++] = tmp;

		if (curr == 15)
		{
			buff[curr] = '\0';
			curr = 0;
			*this += buff;
		}
	} while (tmp != delim);

	buff[curr - 1] = '\0';
	*this += buff;

	return *this;
}

//wind::string& wind::get(std::istream& in, string& s, char delim)
//{
//	char buff[16];
//	int curr = 0;
//	char tmp;
//	do
//	{
//		tmp = in.get();
//		buff[curr++] = tmp;
//
//		if (curr == 15)
//		{
//			buff[curr] = '\0';
//			curr = 0;
//			s += buff;
//		}
//	} while (tmp != delim);
//
//	buff[curr - 1] = '\0';
//	s += buff;
//
//	return s;
//}

void wind::string::clear()
{
	_str[0] = '\0';
	_size = 0;
}

wind::string& wind::string::erase(size_t pos, size_t len)
{
	// 位置检查
	assert(pos < _size);
	// begin和end控制挪动的起始
	// 默认len不会超出有效区域
	size_t begin = pos + len;

	// len已经超出有效区域
	// 数据需要进行修正
	if (len == npos || pos + len >= _size)
	{
		// 修正起始位置
		begin = _size;
		// 修正丢弃字符个数
		len = begin - pos;
	}

	// end就是原终止位
	size_t end = _size;
	// 调整有效字符个数
	_size = _size - len;
	// 挪动未丢弃字符部分
	while (begin < end)
	{
		_str[pos++] = _str[begin++];
	}
	// 添加终止位
	_str[pos] = '\0';
	return *this;
}

void wind::string::resize(size_t len, char holder)
{
	// 保证空间足够
	reserve(len);
	// 设置填充起始位置
	size_t begin = _size;
	// 修正有效字符个数
	_size = len;
	// 末尾添加终止符
	_str[_size] = '\0';

	// 填充开始
	while (begin < _size)
	{
		_str[begin++] = holder;
	}
}

size_t wind::string::find(const char ch, size_t pos)const
{
	assert(pos < _size);
	size_t goal = npos;
	size_t begin;
	for(begin = pos; begin < _size; begin++)
	{
		if(_str[begin] == ch)
		{
			goal = begin;
			break;
		}
	}
	return goal;
}

size_t wind::string::find(const char* str, size_t pos)const
{
	assert(pos < _size);
	size_t goal = npos;
	const char* p = strstr(_str + pos, str);
	if (p)
	{
		goal = (size_t)(p - _str);
	}
	return goal;
}

size_t wind::string::find(const wind::string& s, size_t pos)const
{
	assert(pos < _size);
	return find(_str, pos);
}

void wind::string::swap(string& s)
{
	std::swap(_str, s._str);
	std::swap(_size, s._size);
	std::swap(_capacity, s._capacity);
}

//// 古典主义写法
//wind::string::string(const string& s)
//	:_str(new char[s._capacity + 1])
//	, _size(s._size)
//	, _capacity(s._capacity)
//{
//	strcpy(_str, s._str);
//}

// 现代主义写法
wind::string::string(const string& s)
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	string tmp(s._str);

	// this->swap(tmp);
	// 省略this->也行
	swap(tmp);
}

//// 古典主义写法
//wind::string& wind::string::operator=(const wind::string& s)
//{
//	// 防止自我赋值
//	if (this != &s)
//	{
//		// 为了避免空闲空间太大或不够
//		// 直接销毁被赋值对象
//		delete _str[];
//		_str = new char[s._capacity + 1];
//		_size = s._size;
//		_capacity = s._capacity;
//		strcpy(_str, s._str);
//	}
//	return *this;
//}

//// 现代主义写法
//wind::string& wind::string::operator=(const wind::string& s)
//{
//	if (this != &s)
//	{
//		string tmp(s._str);
//		swap(tmp);
//	}
//	return *this;
//}

// 后现代主义写法
wind::string& wind::string::operator=(wind::string s)
{
	swap(s);
	return *this;
}

wind::string wind::string::substr(size_t pos, size_t len)const
{
	assert(pos < _size);
	string tmp;
	if (len == npos || pos + len >= _size)
	{
		len = _size - pos;
	}
	tmp.reserve(len);
	tmp._size = len;
	tmp._str[len] = '\0';
	strncpy(tmp._str, _str + pos, len);
	return tmp;
}