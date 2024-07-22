# 随笔——贪吃蛇

## 看看效果

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407221544521.mp4"></video>

## 控制台程序

平常我们运行起来的黑框程序其实就是控制台程序，我们的贪吃蛇就是在控制台程序上显示的，为了满足贪吃蛇的某些需求，我们需要对控制台程序进行一些设置。如何设置呢？我们可以使用`cmd`命令来设置控制台。

比如，设置控制台窗口的长宽：设置控制台窗口的大小，30行，30列

`mode con cols=30 lines=30  `      

其中mode是一个 Windows 命令,用于配置或显示系统设备的状态；con是一个特殊的关键词,表示要设置的是控制台窗口(Console)；cols=30意为设置控制台窗口的列数(宽度)为30个字符，lines=30意为设置控制台窗口的行数(高度)为30行。

在“开始”菜单中搜索`cmd`，右键“以管理员身份运行”，即可打开控制台程序：

![image-20240717092139807](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407170921884.png)

输入命令，回车后即可发现控制台窗口大小发生了变化。

![image-20240717092541784](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407170925830.png)

另外我们可以看到，尽管行列数都被设置为30，但窗口大小却不是一个正方形，这是因为这里的30都是以（英文）字符长度为单位的，英文字符和汉字不同，它的长和宽是不相同的。

又或者我们可以对控制台程序进行重名：

`title 贪吃蛇  `

title在该语境下就是重命名的意思，我们把这个指令输入到控制台上，然后回车，就会发现，控制台左上方的名字变了：

![image-20240717093817867](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407170938946.png)

那很明显，在实际写贪吃蛇的时候，我们肯定不能直接在控制台上输入`cmd`指令，实际上，这些能在控制台窗口执行的命令，也可以调用C语言函数system来执行。

注意，VS的默认窗口（如下图）并不是`cmd`窗口，也就是说，VS默认窗口无法执行 system() 命令，这是因为这个默认窗口是VS自己的控制台窗口，而不是Windows操作系统的控制台窗口，system() 只对真正的操作系统控制台窗口才有效。

![image-20240717095834395](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407170958597.png)

所以接下来我们要对VS的默认窗口进行修改：

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171004930.mp4"></video>

必须改成下面这种样子使用system()才有效。

![image-20240717100727606](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171007683.png)

当然，如果你用不惯这个窗口，而项目中也不会用到system()函数，那你可以再改回去：

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171012926.mp4"></video>

我不太喜欢它这配色方案，所以自己改了一下：

![image-20240717102340160](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171023225.png)

![image-20240717102412903](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171024012.png)

修改之后看起来就好看多了：

![image-20240717102453352](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171024431.png)

然后就可以使用system了：

![image-20240717103137826](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171031956.png)

这种窗口大小不太好看名字，换一个：

![image-20240717103310319](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171033457.png)

但我们看到名字并没有被更改，这是因为我们写的这个C程序已经结束了，所以看不到这个效果，解决方案也很简单，找个方法让程序卡住，不结束就行了。

比如写个死循环：

![image-20240717103712843](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171037044.png)

读个字符（我不输入字符，程序就一直在读，然后就相当于卡住了）

![image-20240717104249494](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171042696.png)

当然，也有专门的`cmd`命令可以让程序暂停：

`pause`

![image-20240717104638764](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171046973.png)

好，控制台的相关内容就结束了，接下来讲`Win32API`。

## `Win32API`

Windows操作系统除了协调应用程序的执行、分配内存、管理资源之外，它同时也是⼀个很大的服务中心，调用这个服务中心的各种服务（每⼀种服务就是⼀个函数），可以帮应用程序达到开启视窗、描绘图形、使用周边设备等目的，由于这些函数服务的对象是应用程序(Application)，所以便称之为Application Programming Interface，简称`API`函数。`WIN32API`也就是Microsoft Windows 32位平台的应用程序编程接口。为了实现贪吃蛇小游戏的某些功能，我们需要对 `Win32API`有所了解。

### 控制台屏幕上的坐标[`COORD`](https://learn.microsoft.com/zh-cn/windows/console/coord-str)

在贪吃蛇小游戏中，显而易见的，为了打印蛇和食物，我们需要对某些特定位置进行描述。如何描述呢？`Win32API`使用坐标系来描述控制台中的特定位置。

`COORD`是`Windows API `中定义的⼀个结构体，表示⼀个字符在控制台屏幕幕缓冲区上的坐标，坐标系(0，0)的原点位于缓冲区的顶部左侧单元格。  

![image-20240717110412835](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171104961.png)

`COORD`类型的声明：  

```c
typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD, *PCOORD;
```



### [`GetStdHandle`](https://learn.microsoft.com/zh-cn/windows/console/getstdhandle)  

`GetStdHandle`是⼀个`WindowsAPI`函数。它用于从⼀个特定的标准设备（标准输入、标准输出或标准错误）中取得⼀个句柄（用来标识不同设备的数值），使用这个句柄可以操作设备。  

```c
HANDLE GetStdHandle(DWORD nStdHandle);
```

试想一下，假如我们现在要操作AB两种设备，该如何区分它们呢？那就用不同的句柄去一一对应不同的设备，之后便能通过操作句柄去操作对应的设备。句柄`HANDLE`的实质是个void\*的指针，就像之前我们在顺序表中对int重命名为`SListDataType`一样，看似是重命名，实际是对int类型进行更细致的划分，以后与顺序表有关的int都写作`SListDataType`；微软则把void\*又重命名成了`HANDLE`，相当于对void\*作更细致的划分，这种名叫`HANDLE`的void\*，以后将专门用于`API`中，从而方便管理区分。

 `DWORD`的实质其实是无符号整型，可以将它们理解成一系列编号，用来指代计算机中的各种东西。不过编号不好理解，不好记忆，不好区分，于是人们又对这些编号进行了重命名。

对于`GetStdHandle`，其对应的`DWORD`参数如下

|                 值                  | 含义                                                      |
| :---------------------------------: | --------------------------------------------------------- |
| **STD_INPUT_HANDLE**`((DWORD)-10)`  | 标准输入设备。 最初，这是输入缓冲区 `CONIN$` 的控制台。   |
| **STD_OUTPUT_HANDLE**`((DWORD)-11)` | 标准输出设备。 最初，这是活动控制台屏幕缓冲区 `CONOUT$`。 |
| **STD_ERROR_HANDLE**`((DWORD)-12)`  | 标准错误设备。 最初，这是活动控制台屏幕缓冲区 `CONOUT$`。 |

就比如说，`(DWORD)-10`就被重命名成了`STD_INPUT_HANDLE`。注意，这里的负号没写错，它就是有负号的，它是先把(-10)当成int，其补码就是11111111111111111111111111100110 ，然后这32个比特位就被当成无符号整型去转化成十进制，变成了4294967286。这其实就是微软那个备注的意思。不过直接把4294967286当做参数输入似乎是不行的。

```c
HANDLE hOutput = NULL;
//获取标准输出的句柄(⽤来标识不同设备的数值)
hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
```

### [`GetConsoleCursorInfo `](https://learn.microsoft.com/zh-cn/windows/console/getconsolecursorinfo) 

检索有关指定控制台屏幕缓冲区的光标大小和可见性的信息 

```c 
BOOL WINAPI GetConsoleCursorInfo(
    _In_  HANDLE               hConsoleOutput,
    _Out_ PCONSOLE_CURSOR_INFO lpConsoleCursorInfo
);
```

第一个参数就是标准输出的句柄，第二个参数是一个指向`CONSOLE_CURSOR_INFO`的指针，`CONSOLE_CURSOR_INFO`是一个结构体类型，该结构接收有关控制台游标的信息，下面是`CONSOLE_CURSOR_INFO`的声明：

```c
typedef struct _CONSOLE_CURSOR_INFO {
    DWORD dwSize;
    BOOL  bVisible;
} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO;
```

类型为`DWORD`的变量`dwSize`用来描述光标大小的百分比，类型为`BOOL`的变量`bVisible`用来描述光标的可见性，当`bVisible`为`TRUE`时，光标可见。

`GetConsoleCursorInfo `的返回值也是`BOOL`类型，其本质是32 位整数,当取值为 TRUE (非零值) 时说明函数成功，而当返回 FALSE (零值)时函数失败。要获得更多的错误信息，可以调用 `GetLastError`函数。

使用实例：

```c
HANDLE hOutput = NULL;
//获取标准输出的句柄(⽤来标识不同设备的数值)
hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO CursorInfo;
GetConsoleCursorInfo(hOutput, &CursorInfo);//获取控制台光标信息
```

我们可以打印一下看看：

```c
#include<Windows.h>
#include<stdio.h>

int main()
{
	HANDLE hOutput = NULL;
	//获取标准输出的句柄(⽤来标识不同设备的数值)
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);//获取控制台光标信息
	printf("%u\n", CursorInfo.dwSize);
	printf("%d\n", CursorInfo.bVisible);
	return 0;
}
```

![image-20240717142831129](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171428183.png)

按任意键关闭此窗口后面的光标就是`CONSOLE_CURSOR_INFO`描述的光标，另一个光标是我手动点的，用来做对比，你可以看到，前一个光标的大小是后一个的25%，光标是可见的，所以第二个打印的数字是1，为真。

我们把`CONSOLE_CURSOR_INFO`查出来肯定不是只看看值，而是要对其进行修改。那直接修改就可以吗？

![image-20240717143714774](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171437906.png)

看起来似乎不行，（想想就知道不行，句柄都没有）这就需要用到下一个`API`函数了

### [`SetConsoleCursorInfo  `](https://learn.microsoft.com/zh-cn/windows/console/setconsolecursorinfo)

设置指定控制台屏幕缓冲区的光标的大小和可见性

```c  
BOOL WINAPI SetConsoleCursorInfo(
    _In_       HANDLE              hConsoleOutput,
    _In_ const CONSOLE_CURSOR_INFO *lpConsoleCursorInfo
);
```

接口的统一性，使用方式都差不多，前面的那个\_In\_表示信息是流入函数的，同理，若是\_Out\_,则表示信息是从函数里流出的，这里可能害怕使用指针误改变`CONSOLE_CURSOR_INFO`的内容，所以用`const`修饰了。使用实例如下：

```c
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	HANDLE hOutput = NULL;
	//获取标准输出的句柄(⽤来标识不同设备的数值)
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);//获取控制台光标信息
	CursorInfo.dwSize = 50;
	SetConsoleCursorInfo(hOutput, &CursorInfo);
	system("pause");
	return 0;
}
```

![image-20240717150116207](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171501384.png)

可以看到，这光标确实变大了。

现在，我们将光标隐藏：

```c
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main()
{
	HANDLE hOutput = NULL;
	//获取标准输出的句柄(⽤来标识不同设备的数值)
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);//获取控制台光标信息
	CursorInfo.dwSize = 50;
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo);
	system("pause");
	return 0;
}
```

![image-20240717150904880](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171509096.png)

看，已经没有光标了。

### [`SetConsoleCursorPosition`](https://learn.microsoft.com/zh-cn/windows/console/setconsolecursorposition)

设置指定控制台屏幕缓冲区中的光标位置，我们将想要设置的坐标信息放在`COORD`类型的`pos`中，调用`SetConsoleCursorPosition`函数将光标位置设置到指定的位置。  

```c
BOOL WINAPI SetConsoleCursorPosition(
    _In_ HANDLE hConsoleOutput,
    _In_ COORD  dwCursorPosition
);
```

第一个参数，好理解，就是句柄，第二个参数，也好理解，就是用来描述光标位置的结构体`COORD`，我们最开始就讲过了。

![image-20240717152829186](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171528383.png)

实际上，刚开始光标是在“请”这个字的位置上的，只不过打印了“请按任意键继续. . .”后光标就到后面了，我们用`getchar`来卡住看看：![image-20240717153219962](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171532226.png)

然后呢，我们的贪吃蛇小游戏默认是标准输出设备的，所以可以稍微封装一下，只要输入一个坐标就可以把光标重定位了。

![image-20240717154115176](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171541394.png)

### [`GetAsyncKeyState  `](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-getasynckeystate)

贪吃蛇是有交互的，该如何去检测按键状态呢？就是通过这个函数

```c
SHORT GetAsyncKeyState(
  [in] int vKey
);
```

`vkey`是类型为int的变量，它是一系列编号，称为[虚拟键码](https://learn.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes)，用来表示各个按键。这个函数的使用方法就是，输入一个虚拟键码，通过该函数的返回值去判断这个按键的状态。

`GetAsyncKeyState` 的返回值是SHORT，其实质是short类型，在上⼀次调用`GetAsyncKeyState` 函数后，如果返回的16位的short数据中，最高位是1，说明按键的状态是按下，如果最高是0，说明按键的状态是抬起；如果最低位被置为1则说明，该按键被按过，否则为0。  至于short的其它位数，在此场景下不会被使用。

我们只需要判断按键有没有按下即可，或者说看函数返回值最低位为1即可。由于这个按键检测动作代码较少，使用频率又较高，可以以宏的形式去封装。

```c
#define KEY_PRESS(VK) ( (GetAsyncKeyState(VK) & 0x01) ? 1 : 0 )
```

后面就是一个三目操作符，由于按位与是全真则真，而`0x01`只有最低位是真，所以当`GetAsyncKeyState` 的返回值最低位为1时，前面的表达式就为真，于是就返回1了，反之如果为假，返回0。多打几个括号防止执行顺序被打乱。以前我也说过。

![image-20240717164621133](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171646350.png)

```c
#include<Windows.h>
#include<stdio.h>

#define KEY_PRESS(VK) ( (GetAsyncKeyState(VK) & 0x01) ? 1 : 0 )

void Postion(short x, short y)
{
	COORD postion = { x, y };
	HANDLE hOutput = NULL;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, postion);
}

int main()
{
	int n = 0;
	do
	{
		Sleep(1000);
		if (KEY_PRESS(VK_F4))
		{
			printf("检测到F4被按下\n");
		}
		Sleep(1000);
		if (KEY_PRESS(VK_F1))
		{
			printf("检测到F1被按下\n");
		}
	} while (!n++);
	/*Postion(5, 20);
	getchar();
	system("pause");*/
	return 0;
}
```

循环两次或许不太明显？改成一直循环。

```c
int main()
{
	while (1)
	{
		if (KEY_PRESS(VK_F4))
		{
			printf("检测到F4被按下\n");
		}
		if (KEY_PRESS(VK_F1))
		{
			printf("检测到F1被按下\n");
		}
	}
	/*Postion(5, 20);
	getchar();
	system("pause");*/
	return 0;
}
```

![image-20240717165306915](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407171653990.png)

## 贪吃蛇游戏设计与分析

在正式开始贪吃蛇的游戏设计之前，我们还需要做些准备。

### 如何打印宽字符？

在游戏效果展示中，我们看到，蛇食物墙都是用宽字符打印的，我们平常打印的那些字符，比如说`abcde`之类，都是窄字符，窄字符不像汉字那样方方正正，而控制台单位长度是以这些窄字符为标准的，所以，当行列都被设置为30时，控制台大小并不是正方形。作为一种由英语母语国家发明出的计算机语言，它最开始并不适用于非英语母语国家，也打印不出来宽字符，于是C语言开始了一系列的国际化进程。

```引用
C语言字符默认是采用ASCII编码的，ASCII字符集采用的是单字节编码，且只使用了单字节中的低7位，最高位是没有使用的，可表示为0xxxxxxxx；可以看到，ASCII字符集共包含128个字符，在英语国家中，128个字符是基本够用的，但是，在其他国家语言中，比如，在法语中，字母上方有注音符号，它就无法用ASCII码表示。于是，⼀些欧洲国家就决定，利用字节中闲置的最高位编入新的符号。比如，法语中的é的编码为130（⼆进制10000010）。这样⼀来，这些欧洲国家使用的编码体系，可以表示最多256个符号。但是，这里又出现了新的问题。不同的国家有不同的字母，因此，哪怕它们都使用256个符号的编码方式，代表的字母却不⼀样。比如，130在法语编码中代表了é，在希伯来语编码中却代表了字母Gimel，在俄语编码中又会代表另⼀个符号。但是不管怎样，所有这些编码方式中，0--127表示的符号是一样的，不⼀样的只是128--255的这⼀段。
至于亚洲国家的文字，使用的符号就更多了，汉字就多达10万左右。⼀个字节只能表示256种符号，肯定是不够的，就必须使用多个字节表达⼀个符号。比如，简体中文常见的编码方式是GB2312，使用两个字节表示⼀个汉字，所以理论上最多可以表示256x256=65536个符号。  
```

后来为了使C语言适应国际化，C语言的标准中不断加⼊了国际化的支持。比如：加入了宽字符的类型`wchar_t `和宽字符的输入和输出函数，加入了`<locale.h>`头文件，其中提供了允许程序员针对特定地区（通常是国家或者说某种特定语言的地理区域）调整程序行为的函数。

 #### `<locale.h>`本地化  

`<locale.h>`提供的函数用于控制C标准库中对于不同的地区会产生不一样行为的部分。哪些部分呢？包含以下一个方向：

- 数字量的格式  
- 货币量的格式  
- 字符集 
- 日期和时间的表示形式 

通过修改地区，程序可以改变它的行为来适应世界的不同区域。但地区的改变可能会影响库的许多部分，其中⼀部分可能是我们不希望修改的。所以C语言支持针对不同的类项进行修改，为了便于管理，这些类项随后又被封装成宏：

- `LC_COLLATE`：影响字符串比较函数` strcoll() `和` strxfrm() `。  
- `LC_CTYPE`：影响字符处理函数的行为。  
- `LC_MONETARY`：影响货币格式。 
- `LC_NUMERIC`：影响 `printf()` 的数字格式。  
- `LC_TIME`：影响时间格式 `strftime() `和 `wcsftime()` 。
- `LC_ALL`: 针对所有类项修改，将以上所有类别设置为给定的语言环境。 

[详细说明，请参考官方文档](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/setlocale-wsetlocale?view=msvc-170)    

#### [`setlocale  `](https://legacy.cplusplus.com/reference/clocale/setlocale/?kw=setlocale)

```c
char* setlocale (int category, const char* locale);
```

`setlocale`函数有两个用法：

-  查询当前地区
-  修改当前地区

`setlocale`的第⼀个参数就是前面说的那些以`LC_`开头的宏；在进行地区修改时，第二个参数仅定义了2种可能取值：<span style="color:blue">"C"</span>（正常模式）和<span style="color:blue">" "</span>（本地模式)，设置失败返回NULL；若想查询当前地区，第二个参数置为<span style="color:blue">“NULL”</span>（空），接收返回值即可。

在任意程序开始执行之前，都会隐藏地执行:  

```c
setlocale(LC_ALL, "C");
```

当地区设置为"C"时，库函数按正常方式执行；当程序运行起来后想改变地区， 就需要调用`setlocale`函数，用" "作为第2个参数，这样就会把对应的类项改为本地模式运行。

`C libary`里有一段示例代码，可以执行下看看：

```c     
/* setlocale example */
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */
#include <locale.h>     /* struct lconv, setlocale, localeconv */

int main()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	struct lconv* lc;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	int twice = 0;

	do {
		printf("Locale is: %s\n", setlocale(LC_ALL, NULL));

		strftime(buffer, 80, "%c", timeinfo);
		printf("Date is: %s\n", buffer);

		lc = localeconv();
		printf("Currency symbol is: %s\n-\n", lc->currency_symbol);

		setlocale(LC_ALL, "");
	} while (!twice++);

	return 0;
}
```

![image-20240718113848095](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407181138255.png)

那个`do while`的条件是为了只让程序执行两遍，先执行一遍，再判断，前置++先使用，0取反后变为真，然后自加变成1，第二次循环之后，1取反变为0，为假，跳出循环。

在将地区模式变为本地后，就可以输出宽字符了。

宽字符常量要使用`wchar_t`类型的变量来承接，承接时，要在宽字符的字面量前面加上L，以向编译器强调，后面的字符是宽字符，如果不加，编译器就会把后面的字符识别为窄字符，从而出现问题；宽字符使用`wprintf`来打印，宽字符及字符串使用`%lc%ls`来作占位符，另外，在占位符前面也要标记L。

```c
#include<locale.h>
#include<stdio.h>

int main()
{
	setlocale(LC_ALL, "");
	char a = 'a';
	char b = 'b';
	printf("%c%c\n", a, b);

	wchar_t w1 = L'听';
	wchar_t w2 = L'风';
	wchar_t w3 = L'若';
	wchar_t w4 = L'依';
	wprintf(L"%lc\n", w1);
	wprintf(L"%lc\n", w2);
	wprintf(L"%lc\n", w3);
	wprintf(L"%lc\n", w4);
	return 0;
}
```

![image-20240718122149567](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407181221679.png)

```c
#include<locale.h>
#include<stdio.h>

int main()
{
	setlocale(LC_ALL, "");
	char a = 'a';
	char b = 'b';
	printf("%c%c\n", a, b);

	wprintf(L"%ls\n", L"□★●");

	wchar_t w1 = L'听';
	wchar_t w2 = L'风';
	wchar_t w3 = L'若';
	wchar_t w4 = L'依';
	wprintf(L"%lc%lc%lc%lc\n", w1, w2, w3, w4);
	return 0;
}
```

![image-20240718123421518](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407181234614.png)

□★●是用输入法的特殊字符写出来的。

![image-20240718132251059](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407181322323.png)

 解决了宽字符问题之后，就可以正式进入游戏设计环节了。



### 搭建游戏框架

还是像之前那样，整个贪吃蛇项目分为四个文件：文档文件（也就是本文件`README.md`），测试代码`test.c`，游戏代码`Snake.c`,游戏头文件`Snake.h`，我们先在`test.c`中搭建游戏框架，或者说，大纲？

```c
#include<locale.h>
#include<Snake.h>

//实现游戏主逻辑
void test()
{
	//创建贪吃蛇

	//游戏初始化

	//开始游戏

	//游戏结束，资源回收
}

//搭建游戏运行环境
int main()
{
	//设置窗口大小
	system("mode con cols=110 lines=30");
	//重命名con窗口名
	system("title 贪吃蛇");
	//设置本地化
	setlocale(LC_ALL, "");
	//光标隐藏
	HANDLE hOutput = NULL;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);     //获取句柄
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);    //检索光标信息
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo);    //设置光标属性
    
    srand((unsigned int)time(NULL));               //设置“种子”

	test();

	system("pause");

	return 0;
}
```

这里注意一下，本来为了隐藏光标，我们似乎只要设置光标属性，而不用检索光标信息，但在实际编程中，我们发现，若没有光标信息检索这一步，下面的光标属性修改就是无效的，这是为什么呢？这是因为，为了安全，`SetConsoleCursorInfo `函数中包含了对输入参数数据合法性的检查，检索光标信息相当于给`CursorInfo`中的成员进行了初始化，使得其内部参数确实是合法的，若没有信息的检索，并且创建`CursorInfo`时也没有初始化成合法数据，在输入`SetConsoleCursorInfo` 函数后，该函数就会认为这个变量是无效的，为了防止操作后发生不可预料的后果，对于数据非法的`CursorInfo`，`SetConsoleCursorInfo` 选择不作为。试想一下，我们写顺序表，链表的时候，那些操作函数是不是也包括了对输入数据合法性的检查？

### 创建贪吃蛇

我们使用单链表管理蛇身坐标的数据，所以需要在`Snake.h`中定义一个相应的结构体类型;

```c
typedef struct SnakeNode
{
	SHORT x;
	SHORT y;
	struct SnakeNode* next;
}SnakeNode, * PSnakeNode;
```

注意后面的`, * PSnakeNode`是对这个结构体的指针进行重命名，其中的逗号表示的是并列关系：

```c
typedef struct SnakeNode
{
	SHORT x;
	SHORT y;
	struct SnakeNode* next;
}SnakeNode;

typedef SnakeNode* PSnakeNode;

//或者
typedef struct SnakeNode
{
	SHORT x;
	SHORT y;
	struct SnakeNode* next;
}SnakeNode;

typedef struct SnakeNode
{
	SHORT x;
	SHORT y;
	struct SnakeNode* next;
}* PSnakeNode;
```

在整个项目中，我们可能会用到多个变量，这些变量如果随手创建将不好管理，就像旅行时行李随手拿一样，所以我们把这些变量全部都封装在一个结构体中，就像把行李放到行李箱里一样。这便是面向对象的思想。为了区分，也为了防止重名，结构体中的成员名都以"_"开头。类型的定义我们写在头文件中：

```c
typedef enum direction
{
	Up,
	Down,
	Left,
	Right
}direction;

typedef enum VitalStatus
{
	Alive,
	Died_By_Wall,
	Died_By_Oneself,
	Stop
}VitalStatus;

typedef int score,dealy;

typedef struct Snake
{
	PSnakeNode _PSnake;          //蛇头的指针
	PSnakeNode _PFood;           //食物的指针
	direction _ward;             //运动的方向
	VitalStatus _status;         //蛇的状态
	score _Food_Weight;          //食物的分数
	score _Total;				//游戏的总分数
	dealy _speed;                //用延迟的方式控制运动速度
}Snake, * PSnake;
```

我们只会创建一个类型为Snake的变量（或者说对象），随后仅用这一个对象来维护整个游戏。

```c
void test()
{
	//创建贪吃蛇
	Snake snake = {0};
	//游戏初始化
	GameStart(&snake);
	//开始游戏
	//GameRun();
	//游戏结束，资源回收
	//GameEnd();
}
```

下面我们就将完成`GameStart`函数

### `GameStart`

```c
static void WelcomeToGame()
{

}

void GameStart(_In_ PSnake ps)
{
	//显示欢迎界面
	//显示说明界面
	WelcomeToGame();

	//绘制地图
    //CreateMap();

	//初始化蛇
	//InitSnake(ps);
    
	//创建食物
    //CreateFood(ps);

	//设置游戏相关信息
}
```

#### `WelcomeToGame`

```c
//光标重定位
void SetPos(_In_ SHORT x, _In_ SHORT y)
{
	if ((x >= 0 && x < 100) && (y >= 0 && y < 30))
	{
		HANDLE hOutput = NULL;
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD postion = { x, y };
		SetConsoleCursorPosition(hOutput, postion);
	}
	else
	{
		return;
	}
}

static void WelcomeToGame()
{
	SetPos(40, 14);
	wprintf(L"%ls", L"欢迎来到贪吃蛇小游戏");
	SetPos(41, 20);
	system("pause");
	system("cls");//清屏
	SetPos(30, 14);
	wprintf(L"%ls", L"用 ↑ ↓ ← → 控制贪吃蛇的移动方向；");
	SetPos(27, 15);
	wprintf(L"%ls", L"F3为加速，F4为减速，加速可以获得更高的分数。");
	SetPos(38, 20);
	system("pause");
	system("cls");//清屏
}
```

#### `CreateMap`

依据控制台窗口大小去绘制地图，为了便于理解，我们把墙的字符`L'□'`封装成宏WALL

```c
static void CreateMap()
{
	int i = 0;
	SetPos(0, 0);
	for (i = 0; i < 29; i++)
	{
		wprintf(L"%lc",WALL);
	}
	SetPos(0, 26);
	for (i = 0; i < 29; i++)
	{
		wprintf(L"%lc", WALL);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}
    SetPos(65, 20);
    wprintf(L"%ls", L"不能穿墙，不能撞到自己");
    SetPos(65, 21);
    wprintf(L"%ls", L"用 ↑ ↓ ← → 控制贪吃蛇的移动方向；");
    SetPos(65, 22);
    wprintf(L"%ls", L"F3为加速，F4为减速，加速可以获得更高的分数。");
    SetPos(65, 23);
    wprintf(L"%ls", L"ESC为退出，空格为暂停");
    SetPos(65, 25);
    wprintf(L"%ls", L"作者：听风若依");
}
```

#### `InitSnake`

为了好看，我们的蛇初始长度就是5，蛇身的每个节点由'●'构成，在固定的⼀个坐标处，比如(24,5)处开始出现蛇，连续5个节点。那么另外四个节点坐标就是 (26,5)，(28,5)，(30,5)，(32,5)。这里要注意，蛇身体的横坐标x必须是二的倍数，这样才便于对齐，从而避免出现身体一半在墙上，一半不在墙上的情况。

食物也是这样，横坐标x必须是二的倍数。

![image-20240719141200547](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407191412004.png)

我们将用循环的方式去创建这五个节点，然后再采用头插的方式将新创建的蛇身节点挂载到`_PSnake`上，为此，需要创建一个指向新节点的指针`ptraverse`,这里之所以把它取名为遍历，是因为它将逐个指向这五个节点，循环结束后，将指向头结点（这里说的不是哨兵位的头结点），然后再让它往后遍历，从而访问这些节点中存储的坐标数据，打印蛇身。为了便于理解，我们把第一个节点的坐标封装成`INITIAL_X`和`INITIAL_Y`；由于这里的链表没有哨兵位，所以之后的头插环节需要分成头节点为空和头节点不为空两种情况，当头结点为空时，直接把新节点的`next`置为空，然后挂载到头结点上，如果头结点不为空，则先要让新节点的`next`指向头节点的`next`，然后在把新节点挂载到头结点上。这里另外要说明一下，`NULL`的宏展开就是`((void*)0)`,而我们之间在创建对象时就已经把其初始化成了{0}，这会使得结构中的成员全部被初始化成0，所以不用担心刚开始的头节点不是空。

五个节点创建并挂载到头结点的代码如下：

```c
PSnakeNode ptraverse = NULL;
int i = 0;
for (i = 0; i < 5; i++)
{
	ptraverse = (PSnakeNode)malloc(sizeof(SnakeNode));
	if (ptraverse == NULL)
	{
		perror("InitSnake_malloc");
	}
	ptraverse->x = INITIAL_X + i * 2;
	ptraverse->y = INITIAL_Y;
	if (ps->_PSnake == NULL)
	{
		ptraverse->next = NULL;
		ps->_PSnake = ptraverse;
	}
	else
	{
		ptraverse->next = ps->_PSnake;
		ps->_PSnake = ptraverse;
	}
}
```

之后是打印蛇身，同样的，也把蛇身字符`L'●'`封装成宏`BODY`

```c
while (ptraverse)
{
	SetPos(ptraverse->x, ptraverse->y);
	wprintf(L"%lc", BODY);
	ptraverse = ptraverse->next;
}
```

接下来，是把对象中的其它成员赋个初始值

```c
ps->_ward = Right;
ps->_status = Alive;
ps->_Food_Weight = 10;
ps->_Total = 0;
ps->_speed = 200;
```



最后，`InitSnake`整体如下：

```c
static void InitSnake(_In_ PSnake ps)
{
	PSnakeNode ptraverse = NULL;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		ptraverse = (PSnakeNode)malloc(sizeof(SnakeNode));
		if (ptraverse == NULL)
		{
			perror("InitSnake_malloc");
			return;
		}
		ptraverse->x = INITIAL_X + i * 2;
		ptraverse->y = INITIAL_Y;
		if (ps->_PSnake == NULL)
		{
			ptraverse->next = NULL;
			ps->_PSnake = ptraverse;
		}
		else
		{
			ptraverse->next = ps->_PSnake;
			ps->_PSnake = ptraverse;
		}
	}

	while (ptraverse)
	{
		SetPos(ptraverse->x, ptraverse->y);
		wprintf(L"%lc", BODY);
		ptraverse = ptraverse->next;
	}

	ps->_ward = Right;
	ps->_status = Alive;
	ps->_Food_Weight = 10;
	ps->_Total = 0;
	ps->_speed = 200;
}
```

#### `CreateFood`

接下来是创建食物了，我们使用`rand`来创建伪随机数，之后再对生成的坐标检查，如果坐标是合法的，那就载入对象，并打印食物，否则重新生成随机数。

函数`rand`可以为我们生成一个范围为`0~RNAD_MAX`的伪随机数，它的返回值就是生成的随机数。绝大部分编译器将`RNAD_MAX`定义为`0x7fff`的十六进制数（32767），它的头文件是`stdlib.h`.之所以说它是一个伪随机数，是因为它是依靠某种算法产生的“随机数”，这种算法又根据两个变量去生成随机数，他们分别是被称为“种子”的算法基准值和使用该函数的次数；“种子”的值默认为数字“1”，“种子”又可以由函数`srand`（头文件也是`stdlib.h`）来进行更改，注意：`srand`的参数必须是严格的无符号整型。严格意义来说只有“种子”也是随机值之后，`rand`所产生的随机数才是真正的随机数，不过实际上我们一般将“时间戳”作为“种子”，“时间戳”可由函数`time`的返回值来表现。`time`的头文件是`time.h`，“时间戳”实际上是个整型，当把`time`的参数设置为“NULL”时，即`time(NULL)`的形式，它就会返回当前时间与1970年1月1日0时0秒的差值（以秒为单位），这个实际上就是时间戳。但要注意时间戳是一个整型，而`srand`的参数必须是严格的无符号整型，因此必须要进行类型强制转换：`(unsigned int)`数字，这样我们就得到了一个0~32767的“伪随机数”。

由于“种子”只用设置一次，所以就把它写在`main`函数中，当成配置游戏环境。在得到0~32767的“伪随机数”后，很明显需要对其进行处理才能使用，若想让坐标在墙内，生成的横坐标随机数就要在2~54，纵坐标随机数就要在1~25；怎么得到这个区间的随机数呢？我们用取余的方式，比如说，把随机说取余53，就可以得到0~52的数字，然后再加2不就得到2~54的数字了吗？让坐标在墙内还不够，横坐标还必须是2的倍数，负责无法对齐，出现蛇身一半在食物上，另一半不再食物上的情况，最后，坐标还不能与蛇身重合，这三条，只要有一条不符合，那就是非法坐标，需要重新生成。

```c
static void CreateFood(_In_ PSnake ps)
{
	SHORT x = 0;
	SHORT y = 0;
again:
	do
	{
		x = rand() % 53 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);

	PSnakeNode ptraverse = ps->_PSnake;
	while (ptraverse)
	{
		if ((ptraverse->x == x) && (ptraverse->y == y))
		{
			goto again;
		}
		ptraverse = ptraverse->next;
	}

	PSnakeNode pfood = (PSnakeNode)malloc(sizeof(SnakeNode));
	if (pfood == NULL)
	{
		perror("CreateFood_malloc");
		return;
	}
	pfood->x = x;
	pfood->y = y;
	pfood->next = NULL;

	SetPos(x, y);
	wprintf(L"%lc", FOOD);

	ps->_PFood = pfood;
}
```

### `GameRun`

现在游戏正式开始了，`GameRun`的主体是个`do while`循环体，通过判断蛇的状态来决定游戏是否继续进行。

我们先把游戏的成绩信息打印一下：

```c
SetPos(65, 15);
printf("总分数：%hd   ", ps->_Total);
printf("单个食物分数：%hd", ps->_Food_Weight);
```

之后就是对按键的检测。对于方向键，我们的策略是当检测到按键按下之后，就修改`_ward`的值，至于逻辑与后面的条件是为了剔除无效数据，比如，蛇本来是向右走的，总不能按下左方向键，让蛇自己撞自己吧？对于这种按键的输入，我们视为无效信息，不予理睬。

```c
if (KEY_PRESS(VK_UP) && ps->_ward != Down)
{
	ps->_ward = Up;
}
else if (KEY_PRESS(VK_DOWN) && ps->_ward != Up)
{
	ps->_ward = Down;
}
else if (KEY_PRESS(VK_LEFT) && ps->_ward != Right)
{
	ps->_ward = Left;
}
else if (KEY_PRESS(VK_RIGHT) && ps->_ward != Left)
{
	ps->_ward = Right;
}
```

这里的`KEY_PRESS`的原型是`#define KEY_PRESS(VK) ( (GetAsyncKeyState(VK) & 0x01) ? 1 : 0 )`

当按下`ESC`时，就改变蛇的状态，从而让程序跳出`do while`循环，结束游戏。

```c
else if (KEY_PRESS(VK_ESCAPE))
{
	ps->_status = Quit;
}
```

当按下`SP`，也就是空格键之后，就让程序进入半死循环，通过不断循环的方式让程序一直卡着，从而实现游戏的暂停；这里之所以说“半死”，是因为这里只是暂停，不是永远停，当我再次按下空格键后，就能跳出循环，继续游戏。

```c
else if (KEY_PRESS(VK_SPACE))
{
	ps->_status = Stop;
	forever(ps);
}
```

```c
static forever(_In_ PSnake ps)
{
	while (ps->_status == Stop)
	{
		if (KEY_PRESS(VK_SPACE))
		{
			ps->_status = Alive;
		}
	}
}
```

当按下`F3F4`后，就调整食物的权重和延迟的毫秒数，当然，不能无限制的加速和减速，当加速和减速到一定程度后，就不允许再加速减速了。

```c
else if (KEY_PRESS(VK_F3))
{
	if (ps->_speed > 80)
	{
		ps->_speed -= 30;
		ps->_Food_Weight += 2;
	}
}
else if (KEY_PRESS(VK_F4))
{
	if (ps->_Food_Weight > 2)
	{
		ps->_Food_Weight -= 2;
		ps->_speed += 30;
	}
}
```

之后，依据贪吃蛇对象的信息，对贪吃蛇进行移动，移动之后，再通过睡眠的方式调整游戏运行的快慢。

```c
SnakeMove(ps);
Sleep(ps->_speed);
```

#### `SnakeMove`

对于`SnakeMove`，我们的主体策略是先创建一个新的节点，用来存储贪吃蛇将要移动的下一个位置，之后再依据下一个位置是不是食物来对蛇进行不同的调整。

```c
static void SnakeMove(_In_ PSnake ps)
{
	PSnakeNode NextNode = (PSnakeNode)malloc(sizeof(SnakeNode));
	if (NextNode == NULL)
	{
		perror("SnakeMove_malloc");
		return;
	}
	switch (ps->_ward)
	{
	case Up:
		NextNode->x = ps->_PSnake->x;
		NextNode->y = ps->_PSnake->y - 1;
		break;
	case Down:
		NextNode->x = ps->_PSnake->x;
		NextNode->y = ps->_PSnake->y + 1;
		break;
	case Left:
		NextNode->x = ps->_PSnake->x - 2;
		NextNode->y = ps->_PSnake->y;
		break;
	case Right:
		NextNode->x = ps->_PSnake->x + 2;
		NextNode->y = ps->_PSnake->y;
		break;
	}

	if (NextNodeIsFood())
	{
		EatFood(ps);
		free(NextNode);
		NextNode = NULL;
	}
	else
	{
		NotEat(NextNode, ps);
		NextNode = NULL;
	}
}
```

如果吃到食物的话，就把食物节点头插到贪吃蛇身体的链表上，刷新游戏得分，然后重新打印蛇和生成新食物。

```c
static void EatFood(_In_ PSnake ps)
{
	ps->_PFood->next = ps->_PSnake;
	ps->_PSnake = ps->_PFood;

	PSnakeNode ptraverse = ps->_PSnake;
	while (ptraverse)
	{
		SetPos(ptraverse->x, ptraverse->y);
		wprintf(L"%lc", BODY);
		ptraverse = ptraverse->next;
	}
	ps->_Total += ps->_Food_Weight;
	CreateFood(ps);
}
```

若是没有吃到食物，再把下一个位置节点装载到蛇身上，另外，因为没有吃到食物，所以要把最后一个节点用两个空格覆写掉，从而达到清除的目的，如果不覆写的话，原先打印的蛇身会留在屏幕上。

```c
static void NotEat(_In_ PSnakeNode pnext, _In_ PSnake ps)
{
	pnext->next = ps->_PSnake;
	ps->_PSnake = pnext;

	PSnakeNode ptraverse = ps->_PSnake;
	while (ptraverse->next->next)
	{
		SetPos(ptraverse->x, ptraverse->y);
		wprintf(L"%lc", BODY);
		ptraverse = ptraverse->next;
	}
    //跳出循环后是倒数第二个节点
	SetPos(ptraverse->x, ptraverse->y);
	wprintf(L"%lc", BODY);

	SetPos(ptraverse->next->x, ptraverse->next->y);
	printf("  ");
	free(ptraverse->next);
	ptraverse->next = NULL;
}
```

这时候游戏其实已经可以运行了，只是由于没有写死亡，所以无法死亡。

检测有没有撞墙和有没有撞到自己都很简单，对于撞墙就是看蛇头坐标还在不在墙内，如果不在，就改变蛇的状态；对于撞到自己，就检测蛇头坐标有没有和蛇身的其它坐标重叠，如果重叠了，就改变蛇的状态。

```c
KillByWall(ps);
KillByOneself(ps);
```

```c
static void KillByWall(_In_ PSnake ps)
{
	if (ps->_PSnake->x == 0 || ps->_PSnake->x == 56 ||
		ps->_PSnake->y == 0 || ps->_PSnake->y == 26)
	{
		ps->_status = Died_By_Wall;
	}
}

static void KillByOneself(_In_ PSnake ps)
{
	PSnakeNode ptraverse = ps->_PSnake;
	ptraverse = ptraverse->next;
	while (ptraverse)
	{
		if (ptraverse->x == ps->_PSnake->x && ptraverse->y == ps->_PSnake->y)
		{
			ps->_status = Died_By_Oneself;
            break;
		}
		ptraverse = ptraverse->next;
	}
}
```

### `GameEnd`

游戏结束后，就依据蛇的状态打印不同提示信息，然后再把以前动态开辟的内存块释放掉，就行了。

```c
void GameEnd(_In_ PSnake ps)
{
	switch (ps->_status)
	{
	case Died_By_Wall:
		SetPos(65, 10);
		wprintf(L"%ls", L"你撞到墙了！游戏结束。");
		break;
	case Quit:
		SetPos(65, 10);
		wprintf(L"%ls", L"游戏退出。");
		break;
	case Died_By_Oneself:
		SetPos(65, 10);
		wprintf(L"%ls", L"你撞到自己了！游戏结束。");
		break;
	}

	PSnakeNode die = ps->_PSnake;
	while (die)
	{
		ps->_PSnake = ps->_PSnake->next;
		free(die);
		die = ps->_PSnake;
	}
	free(ps->_PFood);
	ps->_PFood = NULL;
}
```

在游戏结束之后，或许我们可以再来一局：

```c
//实现游戏主逻辑
void test()
{
	int ch = 0;
	do {
		system("cls");
		//创建贪吃蛇
		Snake snake = { 0 };
		//游戏初始化
		GameStart(&snake);
		//开始游戏
		GameRun(&snake);
		//游戏结束，资源回收
		GameEnd(&snake);
		SetPos(54, 14);
		printf("%s", "要再来一局吗？（Y / N）：");
		ch = getchar();
		while (getchar() != '\n');
	} while (ch == 'y' || ch == 'Y');
}
```

`gechar`会从缓冲区中读取一个字符，就是你输入的'y/n'，`while (getchar() != '\n');`则是用来清除缓冲区，只要读取不到回车，就一直读。

但如果这样我们会发现程序有时是有问题的：

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407221506656.mp4"></video>

你看，第二次的时候，我没有输入'y'，但那里也出现了'y'。

出现这种情况的原因是向上键被误认成了普通字符'y'，如何解决呢？

```c
while (_kbhit())  
{
	_getch();
}
```

**`_kbhit`**函数检查控制台是否有最近的击键。如果该函数返回非零值，则表示击键正在缓冲区中等待。然后程序可以调用**`_getch`**或**`_getche`**来获取击键。`_kbhit()和_getch()`的头文件是`conio.h`。

修改之后变成了这样：

```c
void test()
{
	int ch = 0;
	do {
		system("cls");
		//创建贪吃蛇
		Snake snake = { 0 };
		//游戏初始化
		GameStart(&snake);
		//开始游戏
		GameRun(&snake);
		//游戏结束，资源回收  
		GameEnd(&snake);
		
		while (_kbhit())  
		{
			_getch();
		}
		SetPos(20, 14);
		printf("%s", "要再来一局吗？（Y / N）：");
		ch = getchar();
		while (getchar() != '\n');
	} while (ch == 'y' || ch == 'Y');
}
```

# 完
