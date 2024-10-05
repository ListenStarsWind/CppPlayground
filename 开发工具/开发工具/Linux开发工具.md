# Linux开发工具

## sudo提权

之前我们说过，sudo指令是需要修改信任名单的，今天我们就来改一改。

在改之前，我们先看看不在信任白名单的用户使用sudo指令会怎样。

```shell
[wind@starry-sky ~]$ whoami
wind
[wind@starry-sky ~]$ sudo whoami
[sudo] password for wind: 
wind is not in the sudoers file.  This incident will be reported.
[wind@starry-sky ~]$ 

```

`用户"wind"不在sudo权限用户名单中，该事件将会被报告。`，另外说一下`sudo`全写是"superuser do"，即以超级用户的身份去执行。

`sudoers file`的路径是`/etc/sudoers/`，观察权限信息，可以发现它对拥有者和所属组有读权限，对其他人没有开放任何权限。尽管用vim能打开，但不显示具体内容。

```shell
[wind@starry-sky ~]$ ll /etc/sudoers
-r--r----- 1 root root 4328 Jan  8  2022 /etc/sudoers
[wind@starry-sky ~]$ vim /etc/sudoers
[wind@starry-sky ~]$ 
```

![image-20241002180327918](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410021803152.png)

接下来就要`root`登场了。

```shell
[root@starry-sky ~]# vim /etc/sudoers
```

![image-20241002180744303](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410021807453.png)

移动到100行这里。把`root    ALL=(ALL)       ALL`这行复制粘贴一下，然后把`root`改成信任用户就行了。

![image-20241002181105525](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410021811692.png)

最后再保存修改再退出。因为文件权限是只读，所以要以`wq!`的方式保存并退出。

![image-20241002181251804](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410021812896.png)

![image-20241002181322065](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410021813209.png)

此时用户`wind`就可以使用`sudo`指令了。

```shell
[wind@starry-sky ~]$ sudo whoami
[sudo] password for wind: 
root
[wind@starry-sky ~]$
```

 ## gcc/g++使用

gcc是C的编译器，而g++是C++的编译器，由于C++向下兼容C，所以，C代码既可以使用gcc编译，也可以使用g++编译，但考虑到效率，C代码还是应该用gcc编译；而对于C++来说，就只能使用g++编译器了。gcc和g++的使用方法是完全相同的，这里我们主要使用gcc。

gcc的基础用法——编译一个C源代码，生成可执行程序的指令很简单。`gcc 目标源文件`即可，可执行程序在Linux下默认名为`a.out`，如果想要指定名字，则使用`-o`选项，`-o`后紧跟指定名即可，"o"指"output"，即输出。尽管文件后缀名并不影响可执行程序可被执行的事实，但为了规范以及可被gcc等工具识别，还是要使用默认后缀。

突然发现没装g++，那就装一下。

```shell
[wind@starry-sky gcc使用]$ sudo yum install gcc-c++
[sudo] password for wind: 
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
base                                                                                                                 | 3.6 kB  00:00:00     
epel                                                                                                                 | 4.3 kB  00:00:00     
extras                                                                                                               | 2.9 kB  00:00:00     
updates                                                                                                              | 2.9 kB  00:00:00     
Resolving Dependencies
--> Running transaction check
---> Package gcc-c++.x86_64 0:4.8.5-44.el7 will be installed
--> Processing Dependency: libstdc++-devel = 4.8.5-44.el7 for package: gcc-c++-4.8.5-44.el7.x86_64
--> Running transaction check
---> Package libstdc++-devel.x86_64 0:4.8.5-44.el7 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

============================================================================================================================================
 Package                                Arch                          Version                             Repository                   Size
============================================================================================================================================
Installing:
 gcc-c++                                x86_64                        4.8.5-44.el7                        base                        7.2 M
Installing for dependencies:
 libstdc++-devel                        x86_64                        4.8.5-44.el7                        base                        1.5 M

Transaction Summary
============================================================================================================================================
Install  1 Package (+1 Dependent package)

Total download size: 8.7 M
Installed size: 25 M
Is this ok [y/d/N]: y
Downloading packages:
(1/2): libstdc++-devel-4.8.5-44.el7.x86_64.rpm                                                                       | 1.5 MB  00:00:00     
(2/2): gcc-c++-4.8.5-44.el7.x86_64.rpm                                                                               | 7.2 MB  00:00:00     
--------------------------------------------------------------------------------------------------------------------------------------------
Total                                                                                                        31 MB/s | 8.7 MB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : libstdc++-devel-4.8.5-44.el7.x86_64                                                                                      1/2 
  Installing : gcc-c++-4.8.5-44.el7.x86_64                                                                                              2/2 
  Verifying  : gcc-c++-4.8.5-44.el7.x86_64                                                                                              1/2 
  Verifying  : libstdc++-devel-4.8.5-44.el7.x86_64                                                                                      2/2 

Installed:
  gcc-c++.x86_64 0:4.8.5-44.el7                                                                                                             

Dependency Installed:
  libstdc++-devel.x86_64 0:4.8.5-44.el7                                                                                                     

Complete!

```

```shell
[wind@starry-sky gcc使用]$ ls
code.c  code.cpp
[wind@starry-sky gcc使用]$ cat code.c
#include <stdio.h>

int main()
{
    int i = 0;
    for( ; i < 20; i++ )
    {
        printf("gcc:%d\n",i);
    }
    return 0;
}
[wind@starry-sky gcc使用]$ cat code.cpp
#include <iostream>

int main()
{
    int i = 0;
    for(; i < 20; i++)
    {
        std::cout<<"g++:"<<i<<std::endl;
    }
    return 0;
}
[wind@starry-sky gcc使用]$ gcc code.c
[wind@starry-sky gcc使用]$ g++ code.cpp -o b.out
[wind@starry-sky gcc使用]$ ll
total 32
-rwxrwxr-x 1 wind wind 8360 Oct  2 19:44 a.out
-rwxrwxr-x 1 wind wind 9024 Oct  2 19:44 b.out
-rw-rw-r-- 1 wind wind  131 Oct  2 19:27 code.c
-rw-rw-r-- 1 wind wind  141 Oct  2 19:35 code.cpp
[wind@starry-sky gcc使用]$ g++ code.c -o c.out
[wind@starry-sky gcc使用]$ ll
total 44
-rwxrwxr-x 1 wind wind 8360 Oct  2 19:44 a.out
-rwxrwxr-x 1 wind wind 9024 Oct  2 19:44 b.out
-rw-rw-r-- 1 wind wind  131 Oct  2 19:27 code.c
-rw-rw-r-- 1 wind wind  141 Oct  2 19:35 code.cpp
-rwxrwxr-x 1 wind wind 8360 Oct  2 19:47 c.out
[wind@starry-sky gcc使用]$

```

下面我们简要说一说C/C++源代码到可执行程序所经过的四个过程：预处理，编译，汇编，链接。详细的说明我在[CSDN上](https://blog.csdn.net/venti0411/article/details/139509975?fromshare=blogdetail&sharetype=blogdetail&sharerId=139509975&sharerefer=PC&sharesource=venti0411&sharefrom=from_link)已有文章。

### 预处理

预处理的标准Linux后缀是`.i`，要使gcc仅生成`.i`文件需要带上选项`-E`，`E`取自"preprocess"。格式为`gcc 源文件 -E -o name.i`，不指定输出文件会直接在控制台上打印文件内容。

```shell
[wind@starry-sky gcc使用]$ gcc -E code.c -o code.i
```

可以使用vim对两个文件进行比较：

![image-20241002203656934](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410022036158.png)

我们可以看到`code.c`只有21行，而`code.i`却已经有843行了，这多出来的行主要就是头文件展开所贡献的，除此之外，预处理干的事还包括删除注释，进行宏替换，执行条件编译。

Linux的头文件放在`/usr/include/`路径下：

```shell
[wind@starry-sky gcc使用]$ ls /usr/include/
aio.h        cpio.h      features.h      gshadow.h   math.h      netipx      pwd.h        sgtty.h        sysexits.h   utime.h
aliases.h    cpufreq.h   fenv.h          iconv.h     mcheck.h    netiucv     python2.7    shadow.h       syslog.h     utmp.h
alloca.h     crypt.h     fmtmsg.h        ieee754.h   memory.h    netpacket   python3.6m   signal.h       tar.h        utmpx.h
a.out.h      ctype.h     fnmatch.h       ifaddrs.h   misc        netrom      rdma         sound          termio.h     values.h
argp.h       dirent.h    fpu_control.h   inttypes.h  mntent.h    netrose     re_comp.h    spawn.h        termios.h    video
argz.h       dlfcn.h     fstab.h         langinfo.h  monetary.h  nfs         regex.h      stab.h         tgmath.h     wait.h
ar.h         drm         fts.h           lastlog.h   mqueue.h    nl_types.h  regexp.h     stdc-predef.h  thread_db.h  wchar.h
arpa         elf.h       ftw.h           libgen.h    mtd         nss.h       resolv.h     stdint.h       time.h       wctype.h
asm          endian.h    _G_config.h     libintl.h   net         obstack.h   rpc          stdio_ext.h    ttyent.h     wordexp.h
asm-generic  envz.h      gconv.h         libio.h     netash      paths.h     rpcsvc       stdio.h        uapi         xen
assert.h     err.h       getopt.h        limits.h    netatalk    poll.h      sched.h      stdlib.h       uchar.h      xlocale.h
bits         errno.h     glob.h          link.h      netax25     printf.h    scsi         string.h       ucontext.h
byteswap.h   error.h     gnu             linux       netdb.h     protocols   search.h     strings.h      ulimit.h
c++          execinfo.h  gnu-versions.h  locale.h    neteconet   pthread.h   semaphore.h  sys            unistd.h
complex.h    fcntl.h     grp.h           malloc.h    netinet     pty.h       setjmp.h     syscall.h      ustat.h
[wind@starry-sky gcc使用]$
```

这就是我们当初把VS下下来之后，还要配置组件的原因，配置组件其实就是给VS安装相应语言库文件，头文件，使其具备该语言的开发能力。

工具->获取工具和功能->修改  进入该界面。

![image-20241002211255699](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410022112841.png)

下面说说题外话，条件编译主要用来干什么呢？举一个例子。我们知道VS有社区版和专业版两种版本，那微软是两个版本分别维护吗？当然不是，社区版提供基本的开发功能顺便占占市场份额，让大家知道有VS这个东西，而且社区版就挺好用的，并且VS还有专业版，有更多，更丰富的功能，满足开发人员的多种需求，但微软是这两个版本分别维护吗？不是，一个版本修好了bug，还要试试另一个版本，还有什么同步，太麻烦了，所以微软只维护同一份代码，是专业版的，然后用条件编译跳过某些功能，裁剪一下内容，就有社区版了。

条件编译的另一用处是适配多种机型。比如C标准库里的函数，为了能够在多种平台上跑起来，有多种版本，这个版本用来给Windows系统用，那个给Linux或者嵌入式平台用，这就是用条件编译进行选择的。

### 编译

编译的选项是`-S`,取自"assemble"，负责生成汇编代码。源文件既可以使用`.i`也可以使用`.c`，汇编在Linux上的标准后缀是`.s`。

```shell
[wind@starry-sky gcc使用]$ gcc -S code.i -o code.s
```

![image-20241002213614630](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410022136760.png)

汇编代码我不熟，就不说了。

### 汇编

这个汇编是动词，负责把汇编代码转换成机器码。选项是`-c`，取自"compile"，生成的目标文件标准后缀是`.o`。

```shell
[wind@starry-sky gcc使用]$ gcc -c code.s -o code.o
```

由于它已经是机器码了，所以用文本编辑器，如vim打开之后是乱码。

![image-20241002214227538](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410022142701.png)

`od`指令可以查看机器码文件内容;

```shell
[wind@starry-sky gcc使用]$ od code.o
0000000 042577 043114 000402 000001 000000 000000 000000 000000
0000020 000001 000076 000001 000000 000000 000000 000000 000000
0000040 000000 000000 000000 000000 001250 000000 000000 000000
0000060 000000 000000 000100 000000 000000 000100 000015 000014
0000100 044125 162611 164276 000003 137400 000000 000000 000270
0000120 000000 164000 000000 000000 000270 000000 056400 050303
0000140 067562 062546 071563 067551 060556 026154 062045 000012
0000160 043400 041503 020072 043450 052516 020051 027064 027070
0000200 020065 030062 032461 033060 031462 024040 062522 020144
0000220 060510 020164 027064 027070 026465 032064 000051 000000
0000240 000024 000000 000000 000000 075001 000122 074001 000420
0000260 006033 004007 000620 000000 000034 000000 000034 000000
0000300 000000 000000 000037 000000 040400 010016 001206 006503
0000320 055006 003414 000010 000000 000000 000000 000000 000000
0000340 000000 000000 000000 000000 000000 000000 000000 000000
0000360 000001 000000 000004 177761 000000 000000 000000 000000
0000400 000000 000000 000000 000000 000000 000000 000003 000001
0000420 000000 000000 000000 000000 000000 000000 000000 000000
0000440 000000 000000 000003 000003 000000 000000 000000 000000
0000460 000000 000000 000000 000000 000000 000000 000003 000004
0000500 000000 000000 000000 000000 000000 000000 000000 000000
0000520 000000 000000 000003 000005 000000 000000 000000 000000
0000540 000000 000000 000000 000000 000000 000000 000003 000007
0000560 000000 000000 000000 000000 000000 000000 000000 000000
0000600 000000 000000 000003 000010 000000 000000 000000 000000
0000620 000000 000000 000000 000000 000000 000000 000003 000006
0000640 000000 000000 000000 000000 000000 000000 000000 000000
0000660 000010 000000 000022 000001 000000 000000 000000 000000
0000700 000037 000000 000000 000000 000015 000000 000020 000000
0000720 000000 000000 000000 000000 000000 000000 000000 000000
0000740 061400 062157 027145 000143 060555 067151 070000 064562
0000760 072156 000146 000000 000000 000012 000000 000000 000000
0001000 000012 000000 000005 000000 000000 000000 000000 000000
0001020 000024 000000 000000 000000 000002 000000 000012 000000
0001040 177774 177777 177777 177777 000040 000000 000000 000000
0001060 000002 000000 000002 000000 000000 000000 000000 000000
0001100 027000 074563 072155 061141 027000 072163 072162 061141
0001120 027000 064163 072163 072162 061141 027000 062562 060554
0001140 072056 074145 000164 062056 072141 000141 061056 071563
0001160 027000 067562 060544 060564 027000 067543 066555 067145
0001200 000164 067056 072157 027145 047107 026525 072163 061541
0001220 000153 071056 066145 027141 064145 063137 060562 062555
0001240 000000 000000 000000 000000 000000 000000 000000 000000
*
0001340 000000 000000 000000 000000 000040 000000 000001 000000
0001360 000006 000000 000000 000000 000000 000000 000000 000000
0001400 000100 000000 000000 000000 000037 000000 000000 000000
0001420 000000 000000 000000 000000 000001 000000 000000 000000
0001440 000000 000000 000000 000000 000033 000000 000004 000000
0001460 000100 000000 000000 000000 000000 000000 000000 000000
0001500 000770 000000 000000 000000 000060 000000 000000 000000
0001520 000012 000000 000001 000000 000010 000000 000000 000000
0001540 000030 000000 000000 000000 000046 000000 000001 000000
0001560 000003 000000 000000 000000 000000 000000 000000 000000
0001600 000137 000000 000000 000000 000000 000000 000000 000000
0001620 000000 000000 000000 000000 000001 000000 000000 000000
0001640 000000 000000 000000 000000 000054 000000 000010 000000
0001660 000003 000000 000000 000000 000000 000000 000000 000000
0001700 000137 000000 000000 000000 000000 000000 000000 000000
0001720 000000 000000 000000 000000 000001 000000 000000 000000
0001740 000000 000000 000000 000000 000061 000000 000001 000000
0001760 000002 000000 000000 000000 000000 000000 000000 000000
0002000 000137 000000 000000 000000 000021 000000 000000 000000
0002020 000000 000000 000000 000000 000001 000000 000000 000000
0002040 000000 000000 000000 000000 000071 000000 000001 000000
0002060 000060 000000 000000 000000 000000 000000 000000 000000
0002100 000160 000000 000000 000000 000056 000000 000000 000000
0002120 000000 000000 000000 000000 000001 000000 000000 000000
0002140 000001 000000 000000 000000 000102 000000 000001 000000
0002160 000000 000000 000000 000000 000000 000000 000000 000000
0002200 000236 000000 000000 000000 000000 000000 000000 000000
0002220 000000 000000 000000 000000 000001 000000 000000 000000
0002240 000000 000000 000000 000000 000127 000000 000001 000000
0002260 000002 000000 000000 000000 000000 000000 000000 000000
0002300 000240 000000 000000 000000 000070 000000 000000 000000
0002320 000000 000000 000000 000000 000010 000000 000000 000000
0002340 000000 000000 000000 000000 000122 000000 000004 000000
0002360 000100 000000 000000 000000 000000 000000 000000 000000
0002400 001050 000000 000000 000000 000030 000000 000000 000000
0002420 000012 000000 000010 000000 000010 000000 000000 000000
0002440 000030 000000 000000 000000 000001 000000 000002 000000
0002460 000000 000000 000000 000000 000000 000000 000000 000000
0002500 000330 000000 000000 000000 000410 000000 000000 000000
0002520 000013 000000 000011 000000 000010 000000 000000 000000
0002540 000030 000000 000000 000000 000011 000000 000003 000000
0002560 000000 000000 000000 000000 000000 000000 000000 000000
0002600 000740 000000 000000 000000 000024 000000 000000 000000
0002620 000000 000000 000000 000000 000001 000000 000000 000000
0002640 000000 000000 000000 000000 000021 000000 000003 000000
0002660 000000 000000 000000 000000 000000 000000 000000 000000
0002700 001100 000000 000000 000000 000141 000000 000000 000000
0002720 000000 000000 000000 000000 000001 000000 000000 000000
0002740 000000 000000 000000 000000
0002750
[wind@starry-sky gcc使用]$
```

### 链接

链接就是将刚刚生成的`.o`目标文件（全称是可重定位目标二进制文件）与其它二进制文件相链接，以此生成可执行程序。它不需要选项。格式就是平常生成可执行程序的格式。

```shell
[wind@starry-sky gcc使用]$ gcc code.o -o code.out
```

有人说，除了`code.o`这也没看到其它文件呀，这链接的是什么其它文件？好的，我们需要链接对应语言的库文件，我们知道头文件里包含的只是函数的声明，不是函数的定义，那这定义放在哪里呢？就放在库文件里，库文件放在系统的特定目录下，当执行上面的链接指令时，编译器就会在这个目录下寻找需要的库文件，将它与你给的源文件链接起来；即使我们的main函数没调用任何函数，链接时仍需要库文件，因为库文件还包含着程序运行的必要操作，比如开辟函数栈帧，压栈，出栈什么的。

Linux下的库文件后缀包括两种：一种是以`.so`为结尾的，称为动态库，一种以`.a`为结尾的，称为静态库。而对于Windows来说，`.dll`是动态库，`.lib`是静态库。

对于Linux来说库的命名有固定格式：`libname.后缀.版本号`，"lib"表示这是一个库文件，"name"是库的名字，"后缀是so或者a"。所以只看"name"部分就可知道库的用途。

Linux的库文件位于"/usr/lib64/"或"/lib64/"路径下，我们只要看c库就行。

```shell
[wind@starry-sky gcc使用]$ ls /usr/lib64/libc.*
/usr/lib64/libc.so  /usr/lib64/libc.so.6
[wind@starry-sky gcc使用]$ ls /lib64/libc.*
/lib64/libc.so  /lib64/libc.so.6
[wind@starry-sky gcc使用]$
```

系统默认只安装c动态库，没有静态库，静态库的安装指令为`sudo yum install -y glibc-static`，C++是`sudo yum install -y libstdc++-static`。

动态链接（又称共享链接）时，编译器记录程序所需的库信息。程序运行时，系统不会一次性加载所有库，而是等到实际需要时，根据记录逐步加载相关库，经过一系列操作后，程序便能使用这些库。

而在静态链接中，编译器将所需的库直接拷贝到程序中。程序运行时，包含所有库的可执行文件会一次性加载到内存中，从而实现正常运行。

因此，动态链接生成的程序相对占用资源较少，但因为需要的时候才加载库，所以运行速度稍慢，并且依赖于系统中的库。而静态链接生成的程序资源占用较大，但运行速度更快，且可以独立于系统中的库运行。

Linux中的大部分指令都是用C写的动态链接程序，所以绝对不要删系统的C动态库。

gcc默认情况下，会先尝试使用动态链接，若失败，则尝试使用静态链接；加上选项`-static`，gcc就会直接尝试使用静态链接，失败就报错。`ldd`指令可以显示程序所需要的动态链接库。静态链接和动态链接的库不能混用。`file`指令可以查看链接方式。

```shell
[wind@starry-sky gcc使用]$ sudo yum install -y glibc-static
[sudo] password for wind: 
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
base                                                                                                                 | 3.6 kB  00:00:00     
epel                                                                                                                 | 4.3 kB  00:00:00     
extras                                                                                                               | 2.9 kB  00:00:00     
updates                                                                                                              | 2.9 kB  00:00:00     
Resolving Dependencies
--> Running transaction check
---> Package glibc-static.x86_64 0:2.17-326.el7_9.3 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

============================================================================================================================================
 Package                            Arch                         Version                                Repository                     Size
============================================================================================================================================
Installing:
 glibc-static                       x86_64                       2.17-326.el7_9.3                       updates                       1.6 M

Transaction Summary
============================================================================================================================================
Install  1 Package

Total download size: 1.6 M
Installed size: 7.6 M
Downloading packages:
glibc-static-2.17-326.el7_9.3.x86_64.rpm                                                                             | 1.6 MB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : glibc-static-2.17-326.el7_9.3.x86_64                                                                                     1/1 
  Verifying  : glibc-static-2.17-326.el7_9.3.x86_64                                                                                     1/1 

Installed:
  glibc-static.x86_64 0:2.17-326.el7_9.3                                                                                                    

Complete!
[wind@starry-sky gcc使用]$ ls
a.out  b.out  code.c  code.cpp  code.i  code.o  code.out  code.s  c.out
[wind@starry-sky gcc使用]$ rm code.out
[wind@starry-sky gcc使用]$ rm code.i code.s code.o
[wind@starry-sky gcc使用]$ ls
a.out  b.out  code.c  code.cpp  c.out
[wind@starry-sky gcc使用]$ gcc code.c -o code.out
[wind@starry-sky gcc使用]$ gcc -static code.c -o code-static.out
[wind@starry-sky gcc使用]$ ll -a
total 908
drwxrwxr-x 2 wind wind   4096 Oct  3 11:59 .
drwxrwxr-x 5 wind wind   4096 Oct  2 19:24 ..
-rwxrwxr-x 1 wind wind   8360 Oct  2 19:44 a.out
-rwxrwxr-x 1 wind wind   9024 Oct  2 19:44 b.out
-rw-rw-r-- 1 wind wind    231 Oct  2 20:34 code.c
-rw-rw-r-- 1 wind wind    141 Oct  2 19:35 code.cpp
-rwxrwxr-x 1 wind wind   8360 Oct  3 11:58 code.out
-rwxrwxr-x 1 wind wind 861216 Oct  3 11:59 code-static.out
-rwxrwxr-x 1 wind wind   8360 Oct  2 19:47 c.out
[wind@starry-sky gcc使用]$ ldd code.out
	linux-vdso.so.1 =>  (0x00007fff11f2b000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f801e29d000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f801e66b000)
[wind@starry-sky gcc使用]$ ldd code-static.out
	not a dynamic executable
[wind@starry-sky gcc使用]$ file code.out
code.out: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.32, BuildID[sha1]=792735bce25130e495c461fcd4da4d1ecff256e7, not stripped
[wind@starry-sky gcc使用]$ file code-static.out
code-static.out: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), statically linked, for GNU/Linux 2.6.32, BuildID[sha1]=490dd34af282d0c74dcd6cfa7bc62fc01ed4d626, not stripped
[wind@starry-sky gcc使用]$
```
-----------

怎么记忆选项和对应后缀呢？`-E   -S   -c`合起来就是“ESc”，就是键盘左上角的退出键，`i   s   o`合起来就是"iso"，是Windows镜像文件的后缀。

## make/Makefile

make/Makefile是Linux下的一款项目自动化构建工具。make是一个具体的命令行工具，而Makefile是项目中的一个文本文件，当运行make工具时，make会依据Makefile中的各种信息，对项目进行一系列操作，比如，编译，清理等。make的好处是将开发人员从繁琐的开发工具命令中解脱出来，仅仅输入一两个单词就可以对项目进行各种操作。

make把项目中的各种操作抽象成两个要素：依赖关系和依赖方法。依赖关系描述了这个操作进行的前提条件及其它信息，比如对于编译来说，要有源代码才能进行，编译生成的可执行程序该叫做什么则是与该操作相关的其它信息。对于删除可执行程序来说，理论上要先有可执行程序才能被删，但由于实际中，删除指令`rm`一般都会带`-f`选项，`-f`选项会忽略文件不存在的错误，所以，删除这个操作的依赖关系是空的；依赖方法则描述这个操作具体怎么实现，比如编译就是`gcc *.c -o project.out`，而删除就是`rm -f project.out`。另外，为了图方便，`.out`一般也省略不写。

```shell
[wind@starry-sky make]$ ls
[wind@starry-sky make]$ touch code.c
[wind@starry-sky make]$ touch Makefile
[wind@starry-sky make]$ vim Makefile
```

![image-20241005170805059](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410051708277.png)

```shell
[wind@starry-sky make]$ cat code.c
#include<stdio.h>

int main()
{
    printf("test\n");
    return 0;
}
[wind@starry-sky make]$ make 操作名（就是依赖关系冒号前面的那个），就能执行操作^C
[wind@starry-sky make]$ make project
gcc code.c -o project
[wind@starry-sky make]$ ./project
test
[wind@starry-sky make]$ ls
code.c  Makefile  project
[wind@starry-sky make]$ make clean
rm -f project
[wind@starry-sky make]$ ls
code.c  Makefile
[wind@starry-sky make]$ 由于第一个操作是默认操作，所以编译不写操作名也行^C
[wind@starry-sky make]$ make
gcc code.c -o project
[wind@starry-sky make]$ ls
code.c  Makefile  project
[wind@starry-sky make]$
```

下面为了展现一下make的运行逻辑，我们把编译这个操作拆成预处理，编译，汇编，链接这四个小操作。

```shell
[wind@starry-sky make]$ Makefile的第一个字母也可以小写^C
[wind@starry-sky make]$ mv Makefile makefile
[wind@starry-sky make]$ vim makefile
```

![image-20241005174028369](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410051740475.png)

```shell
[wind@starry-sky make]$ ls
code.c  makefile
[wind@starry-sky make]$ make
gcc -E code.c -o code.i
gcc -S code.i -o code.s
gcc -c code.s -o code.o
gcc code.o -o out
[wind@starry-sky make]$ ls
code.c  code.i  code.o  code.s  makefile  out
[wind@starry-sky make]$ make clean
rm -f code.i code.s code.o out
[wind@starry-sky make]$ ls
code.c  makefile
[wind@starry-sky make]$
```

默认操作是链接，可没有源文件"code.o"，于是make全局搜索一下，看看有没有什么操作能把"code.o"给生成出来，恰好，下一个操作就是生成"code.o"，但"code.s"没有，于是make又全局搜索一下，发现下下个操作是生成"code.s"的方法，可生成"code.s"所需要的"code.i"也没有，make就会再来一次全局搜索，尝试生成"code.i"，于是就在上个操作中发现了生成"code.i"的方法，而且依赖的源文件"code.c"也是有的，于是就生成了"code.i"，有了"code.i"，就能生成"code.s"，有了"code.s"就能生成"code,o"，有了"code.o"就能生成"out"，于是链接这个操作就完成了，在完成链接这个操作的过程中顺手生成了三个中间文件。

好的，改一下makefile，我们要说说其它东西。

![image-20241005180139553](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410051801701.png)

```shell
[wind@starry-sky make]$ make
[wind@starry-sky make]$ ls
code.c  makefile  out
[wind@starry-sky make]$ make clean
[wind@starry-sky make]$ ls
code.c  makefile
[wind@starry-sky make]$
```

为了提高编译效率，在已有可执行程序之后，make会通过某些方法判断源代码是否有更新，当源代码没有更新时，就不允许再次编译。

```shell
[wind@starry-sky make]$ ls
code.c  makefile
[wind@starry-sky make]$ make 
[wind@starry-sky make]$ ls
code.c  makefile  out
[wind@starry-sky make]$ make
make: `out' is up to date.
[wind@starry-sky make]$ echao "// abc" >> code.c
-bash: echao: command not found
[wind@starry-sky make]$ echo "// abc" >> code.c
[wind@starry-sky make]$ make
[wind@starry-sky make]$
```

这是怎么实现的呢？实际上，它是通过比对源代码文件与可执行程序的修改时间来实现的，make会把源代码文件的修改时间和可执行程序的修改时间转化成时间戳，通过时间戳的比对，判断源代码文件和可执行程序的先后关系，如果源代码文件的修改时间晚于可执行程序的修改时间，就证明，源代码文件在可执行程序生成后更新过，所以重新编译是有效的，否则make会认为重新编译是无意义的，拒绝重新编译。

### 文件时间

`stat`指令可以查看文件的详细时间信息。

```shell
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 77        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:03:54.164659215 +0800
Modify: 2024-10-05 19:03:50.773524890 +0800
Change: 2024-10-05 19:03:50.773524890 +0800
 Birth: -
[wind@starry-sky make]$
```

文件就像是容器，它分为两部分，一是文件本身这个框架，二是文件内存储的相关信息。对于文本文件来说，文本内容就是文件内存储的信息，除此之外，文件还有自身的信息——用于描述文件的相关属性，比如文件的名字，文件的大小，文件的权限关系等。

`stat`展示了三种时间："Access   Modify   Change"。"Access"描述了最近的访问时间；"Modify"描述了文件内信息的最近修改时间；"Change"描述了文件本身属性的最近修改时间。

只要用到了文件，那就访问了这个文件。“Access”理论上就应该被修改。可以预见到，它会更改地非常频繁，这意味这系统要频繁地去修改磁盘上的信息（文件存在磁盘上），这会让系统变得低效，所以为了提高效率，正常情况下，只有当"Modify"和"Change"被修改了一定次数之后，“Access”才会被更新。

`touch`可以对已存在的文件强制刷新为当前时间。

```shell
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 77        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:03:54.164659215 +0800
Modify: 2024-10-05 19:03:50.773524890 +0800
Change: 2024-10-05 19:03:50.773524890 +0800
 Birth: -
[wind@starry-sky make]$ clear
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 77        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:03:54.164659215 +0800
Modify: 2024-10-05 19:03:50.773524890 +0800
Change: 2024-10-05 19:03:50.773524890 +0800
 Birth: -
[wind@starry-sky make]$ ll code.c
-rw-rw-r-- 1 wind wind 77 Oct  5 19:03 code.c
[wind@starry-sky make]$ chmod o-r code.c
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 77        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0660/-rw-rw----)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:03:54.164659215 +0800
Modify: 2024-10-05 19:03:50.773524890 +0800
Change: 2024-10-05 19:36:09.861336541 +0800
 Birth: -
[wind@starry-sky make]$ echo "// 123" >> code.c
[wind@starry-sky make]$ ll code.c
-rw-rw---- 1 wind wind 84 Oct  5 19:36 code.c
[wind@starry-sky make]$ 修改了内容，间接修改了文件大小^C
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 84        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0660/-rw-rw----)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:03:54.164659215 +0800
Modify: 2024-10-05 19:36:55.773155206 +0800
Change: 2024-10-05 19:36:55.773155206 +0800
 Birth: -
[wind@starry-sky make]$ 看Access还没修改^C
[wind@starry-sky make]$ chmod o+r code.c
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 84        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:03:54.164659215 +0800
Modify: 2024-10-05 19:36:55.773155206 +0800
Change: 2024-10-05 19:38:28.692835952 +0800
 Birth: -
[wind@starry-sky make]$ Access还没修改^C
[wind@starry-sky make]$ echo "// a" >> code.c
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 89        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:03:54.164659215 +0800
Modify: 2024-10-05 19:39:28.021186073 +0800
Change: 2024-10-05 19:39:28.021186073 +0800
 Birth: -
[wind@starry-sky make]$ 不尝试了^C
[wind@starry-sky make]$ touch code.c
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 89        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:40:30.743670644 +0800
Modify: 2024-10-05 19:40:30.743670644 +0800
Change: 2024-10-05 19:40:30.743670644 +0800
 Birth: -
[wind@starry-sky make]$ 三种时间都被强制更新了^C
[wind@starry-sky make]$ make clean
[wind@starry-sky make]$ ls
code.c  makefile
[wind@starry-sky make]$ make 
[wind@starry-sky make]$ ls
code.c  makefile  out
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 89        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:41:28.111943124 +0800
Modify: 2024-10-05 19:40:30.743670644 +0800
Change: 2024-10-05 19:40:30.743670644 +0800
 Birth: -
[wind@starry-sky make]$ stat out
  File: ‘out’
  Size: 8360      	Blocks: 24         IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057084     Links: 1
Access: (0775/-rwxrwxr-x)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:41:28.158944985 +0800
Modify: 2024-10-05 19:41:28.158944985 +0800
Change: 2024-10-05 19:41:28.158944985 +0800
 Birth: -
[wind@starry-sky make]$ 这回Access终于自己刷新了^C
[wind@starry-sky make]$ chmod o+r code.c
[wind@starry-sky make]$ stat
stat: missing operand
Try 'stat --help' for more information.
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 89        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:41:28.111943124 +0800
Modify: 2024-10-05 19:40:30.743670644 +0800
Change: 2024-10-05 19:42:58.236513159 +0800
 Birth: -
[wind@starry-sky make]$ make是用Modify判断的^C
[wind@starry-sky make]$ make
make: `out' is up to date.
[wind@starry-sky make]$ touch code.c
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 89        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:44:45.601766159 +0800
Modify: 2024-10-05 19:44:45.601766159 +0800
Change: 2024-10-05 19:44:45.601766159 +0800
 Birth: -
[wind@starry-sky make]$ stat out
  File: ‘out’
  Size: 8360      	Blocks: 24         IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057084     Links: 1
Access: (0775/-rwxrwxr-x)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:41:28.158944985 +0800
Modify: 2024-10-05 19:41:28.158944985 +0800
Change: 2024-10-05 19:41:28.158944985 +0800
 Birth: -
[wind@starry-sky make]$ 没有修改内容，但用touch强制刷新时间骗过了make^C
[wind@starry-sky make]$ make
[wind@starry-sky make]$ 没有报错^C
-bash: $'没有报错\003': command not found
[wind@starry-sky make]$
```

make的这种判断源代码文件是否被更新从而决定是否重新编译，更新可执行程序的策略对于其它操作也适用。

----------------

如果遇到某些情况，即使代码没有更新，也想重新编译怎么办呢？make提供了一个关键字`.PHONY`来解决这个问题。`.PHONY`的意思是，不要管那么多，我要重新进行这个操作，就重新进行这个操作。我们把这种注释叫做伪目标修饰。

![image-20241005200801845](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410052008083.png)

```shell
[wind@starry-sky make]$ ls
code.c  makefile  out
[wind@starry-sky make]$ make clean
[wind@starry-sky make]$ make
[wind@starry-sky make]$ ls
code.c  makefile  out
[wind@starry-sky make]$ stat code.c
  File: ‘code.c’
  Size: 70        	Blocks: 8          IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057081     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 19:54:13.316254717 +0800
Modify: 2024-10-05 19:54:10.387138688 +0800
Change: 2024-10-05 19:54:10.387138688 +0800
 Birth: -
[wind@starry-sky make]$ stat out
  File: ‘out’
  Size: 8360      	Blocks: 24         IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057084     Links: 1
Access: (0775/-rwxrwxr-x)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 20:08:34.400363459 +0800
Modify: 2024-10-05 20:08:34.400363459 +0800
Change: 2024-10-05 20:08:34.400363459 +0800
 Birth: -
[wind@starry-sky make]$ make
[wind@starry-sky make]$ stat out
  File: ‘out’
  Size: 8360      	Blocks: 24         IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 1057084     Links: 1
Access: (0775/-rwxrwxr-x)  Uid: ( 1000/    wind)   Gid: ( 1000/    wind)
Access: 2024-10-05 20:09:12.668879304 +0800
Modify: 2024-10-05 20:09:12.668879304 +0800
Change: 2024-10-05 20:09:12.668879304 +0800
 Birth: -
[wind@starry-sky make]$ 重新编译了^C
[wind@starry-sky make]$
```

不过一般不对编译使用伪目标修饰，而只对清理使用伪目标修饰，确保每次清理都会被执行。

![image-20241005201827470](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410052018675.png)

## gdb使用

我们知道，程序分为debug和release两个版本，debug版本的程序包含调试信息，因此允许调试，而release不包含调试信息，通过测试之后就可发布。gcc默认生成的是release版本，若要生成debug版本，需要带上`-g`选项。指令`readelf`可以显示ELF格式的文件信息，二进制文件中的二进制序列不是乱放的，而是以某种格式存放的，ELF就是Linux下的二进制文件格式。

```shell
[wind@starry-sky gcc使用]$ gcc -g code.c -o code-debug.out
[wind@starry-sky gcc使用]$ readelf -S code-debug.out | grep debug
  [27] .debug_aranges    PROGBITS         0000000000000000  00001061
  [28] .debug_info       PROGBITS         0000000000000000  00001091
  [29] .debug_abbrev     PROGBITS         0000000000000000  00001122
  [30] .debug_line       PROGBITS         0000000000000000  00001164
  [31] .debug_str        PROGBITS         0000000000000000  000011a2
[wind@starry-sky gcc使用]$
```

# 完