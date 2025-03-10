# C++IO

“流”即是流动的意思，是物质从一处向另一处流动的过程，是对一种有序连续且具有方向性的数据（ 其单位可以是bit,byte,packet ）的抽象描述。

C++流是指信息从外部输入设备（如键盘）向计算机内部（如内存）输入和从内存向外部输出设备（显示器）输出的过程。这种输入输出的过程被形象的比喻为“流”。

它的特性是：有序连续、具有方向性

为了实现这种流动，C++定义了I/O标准类库，这些每个类都称为流/流类，用以完成某方面的功能

![image-20250308210029337](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250308210029472.png)

`istream`对标的是`printf, scanf`, `fstream`对标的是`fprintf, fscanf`, `sstream`对标的是`sprintf, sscanf`

我们可以很明显地看出, 这里面有菱形继承, 所以这里面也是有虚拟继承的, 

----------------------------

下面我们借着IO库来说说自定义类型如何转化为内置类型.

先看一个代码

```cpp
int main()
{
	string str;
	while (cin >> str)
	{
		cout << str << endl;
	}
	return 0;
}
```

这段代码就是一份回显.  如果要结束这个程序, 有两种方式, 一是`ctrl c`, 终止进程, 二是`ctrl z enter`, 这样能跳出循环

我们知道`istrem::operator>>`返回的是自身的引用, 那它凭什么能做循环条件的?   答案就是它借助于`operator bool`实现了自身到布尔类型的转换.让我们回顾一下别的类型转换.

```cpp
class A
{
public:
	// 由于返回的就是type  所以它的语法省略了类型
	// 类型转换重载
	operator int()
	{
		return 3;
	}

	operator string()
	{
		return "asdfgh";
	}
};

int main()
{
	// 内置类型之间, 相近类型可转换
	int i = 1.25;
	// 构造函数可以支持不相关的类型进行妆转换
	// 内置类型也可以认为有构造, 但我们写不了
	// 构造函数是内置类型转换为自定义类型的渠道
	string str("asdfg");
	// 构造函数也可以把自定义类型转换成自定义类型

	// 自定义类型也可以通过operator type 实现其向内置类型type 的转换
	A a;
	i = a;
	// 这里语义有歧义, 所以显式调了
	str = a.operator std::string();
	cout << i << endl;
	cout << str << endl;

	return 0;
}
```

![image-20250308215259690](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250308215259770.png)

对于`cin`来说, 它本身有一个标志位, 它通过标志位的检测, 判断返回的是真还是假, 当`ctrl z enter`被敲下后, 标志位被改变, 因而返回假, 跳出循环.

------------

下面我们说一说`sync_with_stdio`这个接口., `sync`是`synchronization`的缩写, 其意为同步. 同步`stdio`, 也就是C语言的那个输入输出流. C/C++都有自己的输入输出流, 默认情况下, 它们是同步的, 所谓同步, 就是C/C++输入输出接口可以混着用, 彼此之间不会互相干扰, 但这种同步是由C++额外处理而获得的, 会有多余的性能开销.  `sync_with_stdio`是一个静态成员函数, 它的默认缺省参数为`true`, 表示开启同步, 如果设置为`false`, 那就是关闭同步.

```cpp
bool sync_with_stdio (bool sync = true);
```

```cpp
int main()
{
	// 同步开启, 能保证不乱序
	int i, j;
	cin >> i;
	scanf("%d", &j);
	cout << "i:" << i << " j:" << j << endl;

	// 同步关闭, 结果未知, 需要结合具体实现
	cin.sync_with_stdio(false);
	int m, n;
	cin >> m;
	scanf("%d", &n);
	cout << "m:" << m << " n:" << n << endl;

	return 0;
}
```

![image-20250310133059313](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310133059403.png)

`VS`这边没什么事, `g++`那边同样代码出事了, 因为`g++`的实现方式往往更加简洁,效果很明显, `VS`喜欢写很多封装, 效果就不明显

```shell
[wind@starry-sky ~]$ vim test.cc
[wind@starry-sky ~]$ g++ test.cc
[wind@starry-sky ~]$ ./a.out
12 34 56 78
i:12 j:34
56
m:56 n:56
[wind@starry-sky ~]$
```

---------------

下面我们说文件流

![image-20250308210029337](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250308210029472.png)

我们从之前的这张图上可以看到, `ifstream`是负责读文件的, 读文件, 数据从文件到内存, 所以是`in`, `ofstream`是负责写文件的, 数据从内存到文件, 所以是`out`, 不过我们也可以直接用`fstream`, 它既可以入, 也可以出.

`printf, scanf`这类C语言输入输出接口, 尽管很简洁, 但对于C++这类面向对象的语言来说, 有一个致命的缺陷, 那就是无法对自定义对象进行输入输出操作, 此时就需要我们通过`operator>>   operator<<`的类型重载, 对自定义对象实现输入输出.

比如, 我们这里写个描述服务信息的自定义类

```cpp
class Date
{
	friend ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
	}
	operator bool()
	{
		// 这里是随意写的，假设输入_year为0，则结束
		if (_year == 0)
			return false;
		else
			return true;
	}
private:
	int _year;
	int _month;
	int _day;
};


istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}

struct ServerInfo
{
	char _address[32];
	double _port;
	Date _date;
};
```

现在我们要求把内存中的`ServerInfo`对象写到文件上, 然后再读出来.

对于结构体对象的写入文件操作, 在C语言中有两个思路

- 直接把内存中对象的二进制数据写到文件上, 之后再读回来
- 把对象中的关键数据以字符串的形式写入文件, 之后再根据这些字符串, 在内存中还原原先的对象

我们先看第一种, 很简单, 但实际日常我们不会用

对于文件的打开, 我们有两种渠道, 一是在`ofstream`对象在被实例化后, 通过调用成员函数`open`来打开文件, 另一种方式是在构造函数直接打开文件, 在下面的代码中, 我们用的就是`ofstream (const char* filename, ios_base::openmode mode = ios_base::out);`.   第一个参数就是文件名, 第二个参数是文件的打开模式, 采用比特位传参方式, 这在Linux那边已经提过, 在这里不会再说.

| 成员常量(从基类ios_base继承) | 原型     | 说明                       |
| ---------------------------- | -------- | -------------------------- |
| in                           | input    | 将文件以读方式打开         |
| out                          | output   | 将文件以写方式打开         |
| binary                       | binary   | 以二进制方式打开           |
| ate                          | at end   | 位置从文件末尾开始         |
| app                          | append   | 追加, 原先内容会得到保留   |
| trunc                        | truncate | 截断, 原先内容不会得到保留 |

`read`和`write`进行二进制的读写.

```cpp
int main()
{
	ServerInfo winfo = { "192.0.0.1", 12.13, { 2022, 4, 10 } };
	ofstream bin("info.bin", ofstream::out | ofstream::binary);
	bin.write(reinterpret_cast<const char*>(&winfo), sizeof(winfo));
	// 可以主动关闭, 也可用析构自动关闭
	return 0;
}
```

我们来看看`winfo`的内存情况

![image-20250310145329726](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310145329783.png)

再把`info.bin`打开看看

![image-20250310145506384](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310145506424.png)

接下来我们读一下

```cpp
int main()
{
	ServerInfo rinfo;
	ifstream bin("info.bin", ios_base::in | ios_base::binary);
	bin.read(reinterpret_cast<char*>(&rinfo), sizeof(rinfo));
	return 0;
}
```

`read`之前

![image-20250310150337482](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310150337527.png)

之后

![image-20250310150354667](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310150354704.png)

我们可以看到二进制输入输出操作是很简单的, 但为什么实际不用呢? 一方面, 二进制的可读性差, 无法通过文件的直接打开来判断其中的数据是否正常, 另一方面, 二进制拷贝的是对象的本体, 如果这个对象含有深层结构, 用二进制读写就会出现问题.

我们以`string`为例, `string`在`VS`和`g++`的实现方式各有不同, `g++`用的是原生指针, 字符串数据就在堆上,   `VS`用的是引用计数, 而且每个对象自带一个`buff`, 当字符串较短时, 就直接存在`buff`里, 而当字符串很长时, 就存在堆上, 而弃用`buff`.

我们把`ServerInfo`里的地址类型改成`string`

```cpp
int main()
{
	ServerInfo winfo = { "192.0.0.1", 12.13, { 2022, 4, 10 } };
	ofstream bin("info.bin", ofstream::out | ofstream::binary);
	bin.write(reinterpret_cast<const char*>(&winfo), sizeof(winfo));
	bin.close();

	ServerInfo rinfo;
	ifstream bout("info.bin", ios_base::in | ios_base::binary);
	bout.read(reinterpret_cast<char*>(&rinfo), sizeof(rinfo));

	cout << rinfo._address << endl;
	cout << rinfo._date << endl;
	cout << rinfo._port << endl;

	return 0;
}
```

运行这份代码, 进程会异常退出, 其原因是两个对象中的`string`成员, 是完全相同的, 这相当于重复析构

![image-20250310153231734](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310153231776.png)

在日常情况下, 更多的是一个进程写, 另一个进程读, 此时, 若字符串的长度过大, `string`就会把它放在堆上, 这样连读都读不出来, 那个指针也是野指针了

```cpp
int main()
{
	/*ServerInfo winfo = { "https://legacy.cplusplus.com/reference/fstream/ofstream/ofstream/", 12.13, { 2022, 4, 10 } };
	ofstream bin("info.bin", ofstream::out | ofstream::binary);
	bin.write(reinterpret_cast<const char*>(&winfo), sizeof(winfo));
	bin.close();*/

	ServerInfo rinfo;
	ifstream bout("info.bin", ios_base::in | ios_base::binary);
	bout.read(reinterpret_cast<char*>(&rinfo), sizeof(rinfo));

	cout << rinfo._address << endl;
	cout << rinfo._date << endl;
	cout << rinfo._port << endl;

	return 0;
}
```

![image-20250310153955686](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310153955735.png)

接下来说一下文本读写方式

此时我们打开文件就可以直接用缺省模式, 你要把对象中的核心数据转换成字符串, 然后写到文件里, 怎么把对象转换成字符串呢, 你可以显式的转换(使用各种格式转换接口), 然后往文件里写, 但我们一般用隐式操作, 

我们之前对`Date`写过`operator<<`重载

```cpp
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}
```

我们知道, `ofstream`继承了`ostream`, 所以它在这里可以直接复用`ostream::operator<<`,这就类似于多态和重定向, 我们在Linux那里说过重定向, 这里就不说了.

```cpp
int main()
{
	ServerInfo winfo = { "https://legacy.cplusplus.com/reference/fstream/ofstream/ofstream/", 12.13, { 2022, 4, 10 } };
	ofstream ofs("info.bin");
	ofs << winfo._address << " ";      // 调用 std::operator<< (string)
	ofs << winfo._date << " ";		   // 调用 operator << (Data)
	ofs << winfo._port << " ";         // 调用 std::operator<< (double)
	return 0;
}
```

![image-20250310164055465](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310164055527.png)

此时, 使用文本编辑器就可以看到里面的内容了.

```cpp
istream& operator>>(istream& in, ServerInfo& info)
{
	in >> info._address >> info._date >> info._port;
	return in;
}

int main()
{
	ServerInfo rinfo;
	ifstream ifs("info.bin");
	ifs >> rinfo;
	cout << rinfo._address << endl;
	cout << rinfo._date << endl;
	cout << rinfo._port << endl;
	return 0;
}
```

因为我们的`out`是带空格的, 在C/C++中, 会将空格和回车默认为多个值直接的分割, 所以我们就可以直接读.

![image-20250310164851490](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310164851537.png)

如果你在`out`的时候用的是别的分隔符, 那可以使用`getline`作适配, `delim`就是分隔符.

```cpp
istream& getline (char* s, streamsize n );
istream& getline (char* s, streamsize n, char delim );   
```

--------------

下面我们说说`stringstream`,   与`sprintf`相类似, 它们也主要是把其他数据转换成字符串

先让我们看个示例, 用C语言写一个`sq`语句是这样的, 写的不一定对, 我还没学

```cpp
int main()
{
	char sq1[128];
	char name[10];
	scanf("%s", name);
	sprintf(sq1, "select * from t_scroe where name = '%s'", name);
	printf("%s\n", sq1);
	return 0;
}
```

![image-20250310170602202](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310170602250.png)

C语言在这里的缺点还是不适配面向对象, 如果搜索项是`date`, 那不好处理.

此时就需要使用`stringstream`了, `ostringstream`中自带一个`string`成员, 可以通过`operator<<`将自定义类型字符串化写入成员`string`, 如果我们想要获得里面`string`成员存储的字符串, 可以调用`str`接口

```cpp
int main()
{
	string sq2;
	Date date;
	cin >> date;
	ostringstream oss;
	oss << date;

	sq2 += "select * from t_data where data = '";
	sq2 += oss.str();
	sq2 += "'";
	cout << sq2 << endl;

	return 0;
} 
```

![image-20250310173605057](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310173605103.png)

因为这是复用`operator<<(Date)`, 所以如果`operator<<(Date)`发生变化, 这里也会跟着变.

```cpp
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << "/" << d._month << "/" << d._day;
	return out;
}
```

![image-20250310174018948](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310174019000.png)

我们还可以再简化一些

```cpp
int main()
{
	Date date(2013, 5, 6);
	ostringstream sqloss;
	sqloss << "select * from t_data where data = '" << date << "'";
	cout << sqloss.str() << endl;

	return 0;
}
```

![image-20250310175321814](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250310175321855.png)

```cpp
struct ChatInfo
{
	string _name; // 名字
	int _id; // id
	Date _date; // 时间
	string _msg; // 聊天信息
};

int main()
{
	// 发送一个聊天消息
	ChatInfo winfo = { "张三", 135246, { 2022, 4, 10 }, "晚上一起看电影吧" };
	stringstream oss;
	oss << winfo._name << " ";
	oss << winfo._id << " ";
	oss << winfo._date << " ";
	oss << winfo._msg << " ";

	// 收到一个聊天消息
	ChatInfo rinfo;
	stringstream iss(oss.str());
	iss >> rinfo._name >> rinfo._id >> rinfo._date >> rinfo._msg;  // 注意把之前`Date`operator>>改回` `分割
	cout << rinfo._name << endl;
	cout << rinfo._id << endl;
	cout << rinfo._date << endl;
	cout << rinfo._msg << endl;
	

	return 0;
}
```

不过实际上这种格式转换更多的是用`josn`, 而不是`stringstream`.
