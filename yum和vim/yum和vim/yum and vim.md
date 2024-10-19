# yum和vim

## yum

### Linux的软件安装方式

Linux有多种安装方式，包括源代码安装，

1. 源代码安装

   将源代码克隆下来直接编译，生成软件，自己安装，自己卸载。缺点：对用户要求过高，除了写代码之外全都要自己干，而且为了成功编译代码，需要安装各种各样的工具。

2. rpm安装

   尽管只要下载二进制文件（独立安装包）就行了，不用自己编译，但这种方式只安装用户需要的软件，不安装软件需要的其它软件，于是就容易出现依赖项问题，为了A软件可以使用，要去安装B软件，为了B软件可以使用，要去下C软件·······除此之外，还要考虑个软件的版本兼容问题。

3. yum安装

   这是用户需要的独立软件安装包和该软件所需要的所有软件安装包的集合体，如果用户没有前置软件，那就装对应的版本，如果前置软件版本不对，自动帮你改版本，用户只需要用root权限敲一行指令即可安装成功，且可以正常使用。

下面我们只说yum安装。

yum安装有两种方式：本地安装和在线安装。本地安装由用户提供集合安装包，在线则根据对应的yum源去下载集合安装包。这两种方式都要root权限，下面只说在线安装。

示例：rzsz

rzaz用于 windows 机器和远端的 Linux 机器通过 XShell 互传文件 。

`yum list`指令可以展示我们当前环境下所能支持的所有软件，可以使用管道文件将这些信息输送给`grep`指令，查看软件列表中是否有我们需要的软件。

```shell
[root@starry-sky ~]# yum list | grep rzsz
lrzsz.x86_64                             0.12.20-36.el7                base     
[root@starry-sky ~]# 搜索成功，将全名"lrzsz.x86_64"复制下来^C
[root@starry-sky ~]# 

```

![image-20240929103654020](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291036275.png)

使用找到的全名进行安装

```shell
[root@starry-sky ~]# yum install lrzsz.x86_64
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
base                                                                                                                 | 3.6 kB  00:00:00     
epel                                                                                                                 | 4.3 kB  00:00:00     
extras                                                                                                               | 2.9 kB  00:00:00     
updates                                                                                                              | 2.9 kB  00:00:00     
Resolving Dependencies
--> Running transaction check
---> Package lrzsz.x86_64 0:0.12.20-36.el7 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

============================================================================================================================================
 Package                        Arch                            Version                                 Repository                     Size
============================================================================================================================================
Installing:
 lrzsz                          x86_64                          0.12.20-36.el7                          base                           78 k

Transaction Summary
============================================================================================================================================
Install  1 Package

Total download size: 78 k
Installed size: 181 k
Is this ok [y/d/N]: y
Downloading packages:
lrzsz-0.12.20-36.el7.x86_64.rpm                                                                                      |  78 kB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : lrzsz-0.12.20-36.el7.x86_64                                                                                              1/1 
  Verifying  : lrzsz-0.12.20-36.el7.x86_64                                                                                              1/1 

Installed:
  lrzsz.x86_64 0:0.12.20-36.el7                                                                                                             

Complete!
[root@starry-sky ~]# 

```

卸载则是`yum remove 全名`

```shell
[root@starry-sky ~]# yum remove lrzsz.x86_64
Loaded plugins: fastestmirror
Resolving Dependencies
--> Running transaction check
---> Package lrzsz.x86_64 0:0.12.20-36.el7 will be erased
--> Finished Dependency Resolution

Dependencies Resolved

============================================================================================================================================
 Package                       Arch                           Version                                   Repository                     Size
============================================================================================================================================
Removing:
 lrzsz                         x86_64                         0.12.20-36.el7                            @base                         181 k

Transaction Summary
============================================================================================================================================
Remove  1 Package

Installed size: 181 k
Is this ok [y/N]: y
Downloading packages:
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Erasing    : lrzsz-0.12.20-36.el7.x86_64                                                                                              1/1 
  Verifying  : lrzsz-0.12.20-36.el7.x86_64                                                                                              1/1 

Removed:
  lrzsz.x86_64 0:0.12.20-36.el7                                                                                                             

Complete!
[root@starry-sky ~]# 

```

安装时带上`-y`选项表示同意，不需要再询问，卸载也同理。

```shell
[root@starry-sky ~]# yum install -y lrzsz.x86_64
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Resolving Dependencies
--> Running transaction check
---> Package lrzsz.x86_64 0:0.12.20-36.el7 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

============================================================================================================================================
 Package                        Arch                            Version                                 Repository                     Size
============================================================================================================================================
Installing:
 lrzsz                          x86_64                          0.12.20-36.el7                          base                           78 k

Transaction Summary
============================================================================================================================================
Install  1 Package

Total download size: 78 k
Installed size: 181 k
Downloading packages:
lrzsz-0.12.20-36.el7.x86_64.rpm                                                                                      |  78 kB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : lrzsz-0.12.20-36.el7.x86_64                                                                                              1/1 
  Verifying  : lrzsz-0.12.20-36.el7.x86_64                                                                                              1/1 

Installed:
  lrzsz.x86_64 0:0.12.20-36.el7                                                                                                             

Complete!
[root@starry-sky ~]# 

```

此时，就可以使用`rz`指令将本地文件传送到云服务器，使用`sz`指令将云端文件传送到本地。`rzsz`的更多指令，请自行去网上查找。

### yum源

yum源是yum下载软件的来源，yum源有多种，包括官方版本和非官方版本等，可以在`/etc/yum.repos.d/`路径下查看其配置文件。

```shell
[wind@starry-sky ~]$ ls /etc/yum.repos.d/
CentOS-Base.repo  epel.repo  epel.repo.rpmnew  epel-testing.repo
[wind@starry-sky ~]$ ^C
[wind@starry-sky ~]$ 

```

`base`代表它是官方yum源，打开后，可以看到如下信息。

```
[base]                                                                                                                                  
  2 name=CentOS-$releasever
  3 enabled=1
  4 failovermethod=priority
  5 baseurl=http://mirrors.cloud.aliyuncs.com/centos/$releasever/os/$basearch/
  6 gpgcheck=1
  7 gpgkey=http://mirrors.cloud.aliyuncs.com/centos/RPM-GPG-KEY-CentOS-7
  8 
  9 [updates]
 10 name=CentOS-$releasever
 11 enabled=1
 12 failovermethod=priority
 13 baseurl=http://mirrors.cloud.aliyuncs.com/centos/$releasever/updates/$basearch/
 14 gpgcheck=1
 15 gpgkey=http://mirrors.cloud.aliyuncs.com/centos/RPM-GPG-KEY-CentOS-7
 16 
 17 [extras]
 18 name=CentOS-$releasever
 19 enabled=1
 20 failovermethod=priority
 21 baseurl=http://mirrors.cloud.aliyuncs.com/centos/$releasever/extras/$basearch/
 22 gpgcheck=1
 23 gpgkey=http://mirrors.cloud.aliyuncs.com/centos/RPM-GPG-KEY-CentOS-7

```

里面都是各种各样的下载链接。

但对于那些不是很正规的软件，官方yum源就不一定有了。此时就要去非官方yum源，即`epel`(扩展)yum源。安装扩展yum源的指令为`yum install -y epel-release`。

示例：sl

sl是一个娱乐性质的小软件，安装后，输入`sl`会出现由字符组成的小火车跑动的动画。

```shell
[root@starry-sky ~]# yum install -y sl
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Resolving Dependencies
--> Running transaction check
---> Package sl.x86_64 0:5.02-1.el7 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

============================================================================================================================================
 Package                      Arch                             Version                                 Repository                      Size
============================================================================================================================================
Installing:
 sl                           x86_64                           5.02-1.el7                              epel                            14 k

Transaction Summary
============================================================================================================================================
Install  1 Package

Total download size: 14 k
Installed size: 17 k
Downloading packages:
sl-5.02-1.el7.x86_64.rpm                                                                                             |  14 kB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : sl-5.02-1.el7.x86_64                                                                                                     1/1 
  Verifying  : sl-5.02-1.el7.x86_64                                                                                                     1/1 

Installed:
  sl.x86_64 0:5.02-1.el7                                                                                                                    

Complete!
[root@starry-sky ~]# 

```

因为是动画，就不展示效果了。

示例：cowsay

```shell
[root@starry-sky ~]# yum install -y cowsay
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Resolving Dependencies
--> Running transaction check
---> Package cowsay.noarch 0:3.04-4.el7 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

============================================================================================================================================
 Package                         Arch                            Version                                Repository                     Size
============================================================================================================================================
Installing:
 cowsay                          noarch                          3.04-4.el7                             epel                           42 k

Transaction Summary
============================================================================================================================================
Install  1 Package

Total download size: 42 k
Installed size: 77 k
Downloading packages:
cowsay-3.04-4.el7.noarch.rpm                                                                                         |  42 kB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : cowsay-3.04-4.el7.noarch                                                                                                 1/1 
  Verifying  : cowsay-3.04-4.el7.noarch                                                                                                 1/1 

Installed:
  cowsay.noarch 0:3.04-4.el7                                                                                                                

Complete!
[root@starry-sky ~]# cowsay "hello"
 _______
< hello >
 -------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
[root@starry-sky ~]# 

```

`yum`源配置文件也可以自己写，比如，原装的Linux系统yum源是外网的，下起来可能比较慢，此时就可以把yum源配置文件打开，改成国内的镜像链接。云服务器就不用担心这个，云服务器的Linux做了本地化适配，yum源就是国内的。

yum，其实不止yum，所有的系统其软件安装/卸载都是一个接一个来的，有的系统看起来能多个软件同时安装/卸载，其实它本质还是一个一个操作的，只不过它有一个安装/卸载列表，所以看起来可以多个软件一起来。

## vim

### vim操作

vim是Linux下的一款编辑器，其实它并不是很好用，但非常经典，所以还是值得学一学的。

vim有多种模式，但今天我们只说命令模式（默认模式），插入模式，末行模式。其它模式现在暂且不说。

使用vim打开文本文件的指令是`vim 文本文件名`，这里的文本文件可以不存在，但只有在vim里保存之后，这个文件才能留在磁盘上。

```shell
[wind@starry-sky d1]$ touch f.txt
[wind@starry-sky d1]$ ls
f.txt
[wind@starry-sky d1]$ vim f.txt

```

回车之后，就会进入vim的默认模式，又称命令模式。在此模式下，vim会把用户所有的输入都当做命令，所以可能按下什么键都没有一点反应。

![image-20240929144055691](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291440886.png)

命令模式的各种命令需要文本有内容才好操作，所以我们接下来先按下`i`，即可进入插入模式，此时即可对文本进行编辑。

![image-20240929144307587](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291443729.png)

先写一段代码

![image-20240929144614258](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291446408.png)

之后是保存修改并退出。此时我们需要按下`esc`回退到命令模式下。

![image-20240929144920850](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291449994.png)

此时我们在命令模式下，想要保存修改并退出需要切换到末行模式，又叫底行模式，切换方式是输入一个`:`（冒号），`:`怎么输呢？按下组合键“shirt”+“;”(分号)即可输入`:`号

![image-20240929145449775](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291454924.png)

然后输入`w`（写入，即保存修改）和`q`（退出）,然后按下回车就能保存并退出了。如果光输`q`那就是只退出不保存。

![image-20240929145723096](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291457236.png)

```shell
[wind@starry-sky d1]$ cat f.txt
#include<stdio.h>

int main()
{
    printf("hello vim\n");
    return 0;
}
[wind@starry-sky d1]$ 

```

底行模式如何切换成命令模式呢？还是输入`esc`。

------------------------

现在我们再次使用vim打开文本文件，说一说默认模式的各种命令。

![image-20240929150507762](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291505922.png)

Linux是纯命令行操作，最起码对于云服务器是纯命令行操作，没有图形化界面，所以无法用鼠标调整光标，接下来我们先介绍一下如何使用命令操作光标。

输入`gg`即可让光标跳转到文本最开头。

![image-20240929151238428](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291512581.png)

输入`G`即可让光标跳转到文本最后。`G`的输入有两种方法，一是键盘小写模式下，按下"CAPS"，锁定大写之后按下"g"；二是在键盘小写模式下，按下"shirt"+"g"。不过一般采用第二种，因为这样不用切换大小写。

![image-20240929152020392](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291520521.png)

输入`数字 G`即可切换到文本的对应行。同样的，有两种方式：第一种，锁定大写之后，同时按下"数字"和“g”，或者先按下"数字"再按下"g"；第二种，先按下"数字"，在小写模式下再按下"shirt"+"g"即可，当然，第二种也可以同时按，但不太好操作。比如这里我在小写模式下，先按下"5"，再按下"shirt"+“g”。

![image-20240929153350951](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291533052.png)

按下`yy`即可拷贝光标所在行，随后按下`p`就可以把拷贝内容写到光标到下一行。比如，我们现在处于第五行，按下`yy p`之后，第六行就被插入了拷贝内容。

![image-20240929154523894](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291545027.png)

按下`u`可以撤回。

![image-20240929154600165](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291546311.png)

`yy 数字 p`可以把拷贝内容粘贴"数字"行。比如，我现在在第五行，我们先`yy`拷贝一下第五行，然后使用`2 G `切换到第二行，然后`3 p`，就会从第三行开始粘贴三行拷贝内容。

![image-20240929155058160](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291550305.png)

`yy`前也可以有数字前缀，比如，我们先按下`u`回撤，然后按下`3 yy`，再`1 G`，把光标跳转到第一行，然后`5 p`。

![image-20240929155459838](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291554989.png)

![image-20240929155731524](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291557613.png)

`dd`可以剪切，它也可以加数字前缀，如果不`p`的话，那就可以当做删除。比如这里`15 dd`。

![image-20240929160307935](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291603083.png)

诶呀，断网了，断网时，由于我没有退出vim，所以vim会自动创建一个隐藏文件，重新进入断网前打开的文本文件就会出现如下信息，此时只要选择`r`（恢复）即可。

![image-20240929162938266](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291629361.png)

然后主动退出，把这个隐藏文件删掉即可。否则vim会一直提示这个信息。

```shell
[wind@starry-sky d1]$ ll -a
total 24
drwxrwxr-x 2 wind wind  4096 Sep 29 16:31 .
drwxrwxr-x 4 wind wind  4096 Sep 23 18:53 ..
-rw-rw-r-- 1 wind wind    75 Sep 29 16:31 f.txt
-rw-r--r-- 1 wind wind 12288 Sep 29 16:03 .f.txt.swp
[wind@starry-sky d1]$ rm .f.txt.swp
[wind@starry-sky d1]$ ll -a
total 12
drwxrwxr-x 2 wind wind 4096 Sep 29 16:33 .
drwxrwxr-x 4 wind wind 4096 Sep 23 18:53 ..
-rw-rw-r-- 1 wind wind   75 Sep 29 16:31 f.txt
[wind@starry-sky d1]$ 

```

现在我们再次进入这个文本文件，为了方便展示，要给这个文本多写一些内容。

![image-20240929163533113](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291635267.png)

刚刚我们已经说过了光标的行定位。接下来我们要说光标的列定位。

输入`$`可以将光标移动到所在行的最后一列。`$`的输入方式是"shirt"+"4"。

![image-20240929163919293](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291639417.png)

输入`^`可以把光标移动到所在行的最前列。`^`的输入方法是"shirt"+"6"。

![image-20240929164143222](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291641355.png)

这里要说一下，这里的最前最后列是对文本内容来说的。最前列和最后列有时被合成为“锚点”。 

`b`和`w`以单词为单位进行左右移动。不是单词就以字符为单位移动。可以跨行。`h` `j`  `k`  `l`则是以字符为单位移动，`h`是向左，`l`是向右，`j`是向下，`k`是向上，方向键也可以上下左右移动，但不推荐，显得你不专业，开玩笑的，为什么不推荐方向键上下左右移动呢？因为有的键盘没有方向键。

`~`可以进行大小写切换。`~`的输入方法是"shirt"+“ ` ”(上一撇)、比如，我想让第五行的大小写全都变一下，这时候，就只需要一直按下"shirt"不放，然后每按下一次波浪号就会对光标选中的字符进行转换。

![image-20240929192052657](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291920804.png)

先`r `再`替换`可以对光标选中的字符进行替换，比如我们用`6 G`定位到第六行，然后先按下`r `再按下`x`，第六行的第一个字符"p"就会被替换成"x"。

![image-20240929192940045](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291929165.png)

`r`前也可以加数字前缀，比如现在我们跳转到第七行开头，然后分别按下`5`,`r`,`x`就可以把包括光标选中的五个字符都变为"x"。

![image-20240929193443111](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409291934213.png)

按下`R`可以进入替换模式，在该模式下，你可以直接替换掉光标选中的字符。

![image-20240929202552462](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292025554.png)

同样的，按下`esc`键能回退到命令模式。

命令模式下，`x`可以对选中字符进行删除。同样的，前面加数字前缀可以一次删除多个。

![image-20240929203126647](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292031790.png)

按下`u`可以撤销

![image-20240929203233704](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292032844.png)

如果想要撤销撤销，或者说取消刚才的撤销，那就使用`Ctrl r`。

![image-20240929203426276](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292034398.png)

----------------

现在保存并退出，我们要说一说vim的多文件操作。

```shell
[wind@starry-sky d1]$ ls
f.txt
[wind@starry-sky d1]$ vim code.c
```

![image-20240929204008653](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292040797.png)

```shell
[wind@starry-sky d1]$ ls
code.c  f.txt
[wind@starry-sky d1]$
```

下面我们再次进入"code.c"，注意目录下现在没有"f.c"。

打开后，进入底行模式，输入`vs f.c`，此指令的意思是与"f.c"作比较，但"f.c"没有，和用vim打开不存在的文件一样，之后，如果不保存就退出"f.c"，"f.c"就不会被创建。光标在那个文件，就代表现在在那个文件。

![image-20240929204851268](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292048422.png)

`Ctrl w`可以切换选中文件。

![image-20240929205046336](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292050455.png)

现在我们从"code.c"开头起七行复制到"f.c"，然后保存退出。

![image-20240929205508021](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292055172.png)

就回到了单文件下。

![image-20240929205608686](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292056788.png)

------------

现在进入底行模式，如果vim卡住了，保存并退出`wq`的后面可以再加上`！`（感叹号），意为强制保存并退出。

![image-20240929210403169](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292104299.png)

除此之外，在底行模式下，若以`!`为开头，就可以在不退出vim的情况下执行外部命令。

先保存一下，确保修改内容真的存在文件里了。

![image-20240929210546158](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292105312.png)

编译代码。

![image-20240929210815648](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292108783.png)

先退到Linux命令行界面，表示执行了编译命令，然后按下回车后，回到vim界面

![image-20240929211041831](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292110934.png)

查看一下是否有可执行文件生成。

![image-20240929211150481](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292111578.png)

看到可执行文件已经成功生成。

![image-20240929211248347](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292112444.png)

回车，回到vim界面，执行"a.out"。

![image-20240929211419438](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292114550.png)

成功运行。

![image-20240929211507098](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292115193.png)

底行模式也支持搜索，搜索格式为`/字符`。

![image-20240929211803429](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292118578.png)

按下回车后。

![image-20240929211825750](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292118887.png)

底行模式下，输入`set nu`可显示行号。

![image-20240929212025307](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292120431.png)

`set nonu`去掉行号。

![image-20240929212128498](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292121644.png)

vim的批量化操作方式是命令模式下输入`ctrl v`，然后使用方向键`一定要用 j  k 方向键 `选中区域，接下来按`i`进行操作，比如这里我批量化注释。这是后补的，界面可能有所区别。

命令模式：

![image-20241019154315414](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191543530.png)

`ctrl v`：

![image-20241019154421373](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191544466.png)

用`j`选中几行：

![image-20241019154506415](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191545507.png)

输入`I`进入插入模式：

![image-20241019154716288](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191547425.png)

输入注释符`//`：

![image-20241019154931284](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191549413.png)

按下`esc`：

![image-20241019155016337](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191550462.png)

取消块注释：

`ctrl v`：

![image-20241019155220372](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191552521.png)

使用`j`选中区域：

![image-20241019155257924](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191552051.png)

按下`d`：

![image-20241019155412745](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410191554879.png)

### vim配置

上面我们用的是原装vim，什么都没有，其实vim可以自己配置，最起码给我来个语法提示，自动缩进什么的。

在账号的家目录下，可能有一个隐藏文件，名为`.vimrc`，就是用于配置vim的，如果你没有，那就自己创建一个。

```shell
[wind@starry-sky d1]$ clear
[wind@starry-sky d1]$ cd ~
[wind@starry-sky ~]$ ll -a
total 52
drwx------  5 wind wind 4096 Sep 29 21:22 .
drwxr-xr-x. 4 root root 4096 Sep 26 14:39 ..
-rw-------  1 wind wind 7359 Sep 29 18:18 .bash_history
-rw-r--r--  1 wind wind   18 Nov 25  2021 .bash_logout
-rw-r--r--  1 wind wind  193 Nov 25  2021 .bash_profile
-rw-r--r--  1 wind wind  231 Nov 25  2021 .bashrc
drwxrwxr-x  3 wind wind 4096 Sep 18 17:33 .cache
-rw-------  1 wind wind   50 Sep 20 15:44 .lesshst
-rw-rw-r--  1 wind wind   16 Sep 27 10:14 sour.txt
drwxrwxr-x  4 wind wind 4096 Sep 23 18:53 study
-rw-------  1 wind wind 2450 Sep 29 21:22 .viminfo
drwxrwxr-x  5 wind wind 4096 Sep 28 20:14 .vscode-server
[wind@starry-sky ~]$ 看来没有^C
[wind@starry-sky ~]$ 那就创建一个^C
[wind@starry-sky ~]$ touch .vimrc
[wind@starry-sky ~]$ ls -a
.  ..  .bash_history  .bash_logout  .bash_profile  .bashrc  .cache  .lesshst  sour.txt  study  .viminfo  .vimrc  .vscode-server
[wind@starry-sky ~]$ 接下里就是往.vimrc里写各种东西了，比如^C
[wind@starry-sky ~]$ echo "set nu" >> .vimrc
[wind@starry-sky ~]$ cat .vimrc
set nu
[wind@starry-sky ~]$ 然后找个代码文件看一看^C
[wind@starry-sky ~]$ tree .
.
├── sour.txt
└── study
    ├── d1
    │   ├── a.out
    │   ├── code.c
    │   ├── f.c
    │   └── f.txt
    ├── dest.txt
    ├── d.tgz
    ├── newf.txt
    ├── report.txt
    ├── sour.txt
    └── test
        ├── a
        ├── b
        └── test.txt

4 directories, 12 files
[wind@starry-sky ~]$ vim ./study/d1/code.c

```

![image-20240929213116725](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292131873.png)

就自动带行号了。

然后去网上自己搜一搜，看看那些能用，自己配置。

我呢，就不自己配置了，我用我老师写的一键配置，对于CentOS7及以上版本有效。

以普通账号，普通账号，普通账号的身份去配置，不要对root的vim进行配置。vim配置只会影响对应的配置，root的配置不要动，别把系统弄出问题。

指令为：

```shell
curl -sLf https://gitee.com/HGtz2222/VimForCpp/raw/master/install.sh -o ./install.sh && bash ./install.sh
```

照着提示走，先输入root密码，然后配置成功后再手动执行`source ~/.bashrc`。

![image-20240929214324484](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292143659.png)

试试效果。

![image-20240929214432059](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292144198.png)

有什么自动补全，高亮提示，语法分析，自动缩进，多种主题什么的。

不想要的，不要删除，因为它只有一键安装，没有一键删除。

```shell
[wind@starry-sky ~]$ ll -a
total 80
drwx------  10 wind wind 4096 Sep 29 21:44 .
drwxr-xr-x.  4 root root 4096 Sep 26 14:39 ..
-rw-------   1 wind wind 7668 Sep 29 21:41 .bash_history
-rw-r--r--   1 wind wind   18 Nov 25  2021 .bash_logout
-rw-r--r--   1 wind wind  193 Nov 25  2021 .bash_profile
-rw-r--r--   1 wind wind  352 Sep 29 21:40 .bashrc
drwxrwxr-x   3 wind wind 4096 Sep 18 17:33 .cache
drwxrwxr-x   2 root root 4096 Sep 29 21:40 .config
lrwxrwxrwx   1 wind wind   49 Sep 29 21:40 .cquery -> /home/wind/.VimForCpp/cquery/config/cquery.config
-rw-rw-r--   1 wind wind  827 Sep 29 21:39 install.sh
-rw-------   1 wind wind   50 Sep 20 15:44 .lesshst
drwxrwxr-x   3 wind wind 4096 Sep 29 21:44 .LfCache
drwx------   3 wind wind 4096 Sep 29 21:44 .local
drwxrw----   3 wind wind 4096 Sep 29 21:39 .pki
-rw-rw-r--   1 wind wind   16 Sep 27 10:14 sour.txt
drwxrwxr-x   4 wind wind 4096 Sep 23 18:53 study
lrwxrwxrwx   1 wind wind   25 Sep 29 21:40 .vim -> /home/wind/.VimForCpp/vim
drwxrwxr-x   8 wind wind 4096 Sep 29 21:40 .VimForCpp
-rw-------   1 wind wind 3209 Sep 29 21:39 .viminfo
lrwxrwxrwx   1 wind wind   34 Sep 29 21:40 .vimrc -> /home/wind/.VimForCpp/vim/init.vim
-rw-rw-r--   1 wind wind    7 Sep 29 21:29 .vimrc.bak_0929
drwxrwxr-x   5 wind wind 4096 Sep 28 20:14 .vscode-server
lrwxrwxrwx   1 wind wind   39 Sep 29 21:40 .ycm_extra_conf.py -> /home/wind/.VimForCpp/ycm_extra_conf.py
[wind@starry-sky ~]$ 下了一堆插件^C
[wind@starry-sky ~]$ vim install.sh

```

这个配置的默认缩进是两个空格，可以改成四个，看着更舒服些。

```shell
[wind@starry-sky ~]$ vim .vimrc
```

底行模式下搜索2，就能找到。

![image-20240929220057581](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292200676.png)

把这三个2替换成4就行。

![image-20240929220205780](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409292202899.png)

保存退出。

其他东西自己探索吧。

# 完