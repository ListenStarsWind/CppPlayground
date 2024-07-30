# 作业

这个项目源自于一个作业，这个作业的要求如下：

写一个宏，可以将一个整数的二进制位的奇数位和偶数位交换。

可能这道题对之前的我太难了，没有思路，但现在想想，也不过三件事：

- 把二进制整数奇数位提取出来
- 把二进制整数偶数位提取出来
- 把上述二进制串移位后合并

```c
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define OddEvenSwap(parameter)             \
	{                                      \
		int odd = parameter & 0x55555555;   \
		int even = parameter & 0xAAAAAAAA; \
		int oddnew = even >> 1;            \
		int evennew = odd << 1;            \
		parameter = oddnew | evennew;       \
	}

int main()
{
	unsigned int number = 0x12345678;
	OddEvenSwap(number);
	printf("%u\n",number);
	return 0;
}

//0001 0010 0011 0100 0101 0110 0111 1000
//odd 01 00 01 10 11 10 11 00
//even 00 01 01 00 00 01 01 10
//
//
//
//0010 0001 0011 1000 1010 1001 1011 0100
//odd 00 01 01 00 00 01 01 10
//even 01 00 01 10 11 10 11 00
```

![image-20240730100214563](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407301002759.png)
