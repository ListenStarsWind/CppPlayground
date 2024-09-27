# Linux权限

## 普通用户和超级用户

Linux下有两种用户：普通用户和超级用户（root）。普通用户在Linux下的操作受到限制，而root几乎可以在Linux下做任何事。当我们为root时，可以通过adduser指令创建普通用户。

```shell
[root@starry-sky ~]# whoami
root
[root@starry-sky ~]# 建立普通用户"whisper"^C
[root@starry-sky ~]# adduser whisper
[root@starry-sky ~]# 初始化"whisper"的密码^C
[root@starry-sky ~]# passwd whisper
Changing password for user whisper.
New password: 
Retype new password: 
Sorry, passwords do not match.
New password: 
Retype new password: 
passwd: all authentication tokens updated successfully.
[root@starry-sky ~]# 

```

## 切换用户

### 普通用户切换成root用户

普通用户切换成root用户有两种方法。

方法一：纯粹的身份切换，不会改变当前路径；方法二：在切换身份的同时会来到root的家目录

```shell
[wind@starry-sky ~]$ whoami
wind
[wind@starry-sky ~]$ 输入"su",然后回车即可^C
[wind@starry-sky ~]$ su
Password: 
[wind@starry-sky ~]$ 输入"su",然后回车，再输入root密码即可^C
[wind@starry-sky ~]$ su
Password: 
[root@starry-sky wind]# 此时我们所在的目录没有变化，依旧是在"wind"目录下^C
[root@starry-sky wind]# 指令"exit"或者快捷键"Ctrl+D"可以回退到原用户^C
[root@starry-sky wind]# exit
exit
[wind@starry-sky ~]$ pwd
/home/wind
[wind@starry-sky ~]$ 指令"su -"可以在切换用户的同时，来到root的家目录^C
[wind@starry-sky ~]$ su -
Password: 
Last login: Thu Sep 26 15:11:33 CST 2024 on pts/0
[root@starry-sky ~]# pwd
/root
[root@starry-sky ~]# logout
[wind@starry-sky ~]$ pwd
/home/wind
[wind@starry-sky ~]$ 

```

### 普通用户相互切换

```shell
[wind@starry-sky ~]$ whoami
wind
[wind@starry-sky ~]$ pwd
/home/wind
[wind@starry-sky ~]$ 没什么好说的，就是"su name"^C
[wind@starry-sky ~]$ su whisper
Password: 
[whisper@starry-sky wind]$ pwd
/home/wind
[whisper@starry-sky wind]$ exit
exit
[wind@starry-sky ~]$ su - whisper
Password: 
Last login: Thu Sep 26 15:25:32 CST 2024 on pts/0
[whisper@starry-sky ~]$ pwd
/home/whisper
[whisper@starry-sky ~]$ 

```

### root切换至普通用户

```shell
[root@starry-sky ~]# whoami
root
[root@starry-sky ~]# pwd
/root
[root@starry-sky ~]# 没什么好说的，root切换成普通用户不用输密码^C
[root@starry-sky ~]# su wind
[wind@starry-sky root]$ exit
exit
[root@starry-sky ~]# su - whisper
Last login: Thu Sep 26 15:26:05 CST 2024 on pts/0
[whisper@starry-sky ~]$ exit
logout
[root@starry-sky ~]# 

```

### 普通用户暂时提权

用户来回切换有时显得很麻烦，为此，Linux允许普通用户暂时提权，以`root`的身份运行某些指令

```shell
[wind@starry-sky ~]$ whoami
wind
[wind@starry-sky ~]$ 指令提权的方法是在其前面加上"sudo"修饰^C
[wind@starry-sky ~]$ sudo whoami
[sudo] password for wind: 
wind is not in the sudoers file.  This incident will be reported.
[wind@starry-sky ~]$ 注意，是输入自己的密码^C
[wind@starry-sky ~]$ 为什么我这里没有用呢？^C
[wind@starry-sky ~]$ 因为提权需要root用户的信任^C
[wind@starry-sky ~]$ 当然，不是root在线确认^C
[wind@starry-sky ~]$ 而是需要root修改系统配置文件，将信任用户写入信任名单文件中^C
[wind@starry-sky ~]$ 否则凭什么普通用户输入自己密码就能提权成root呢？^C
[wind@starry-sky ~]$ 现在我们对Linux的了解还不够，所以先不更改配置文件^C
[wind@starry-sky ~]$ 

```

## Linux权限管理

权限，是Linux对普通用户的约束，用来规定他们能做什么，不能做什么。`root`身为权限规则的制定者和贯彻者，不受权限规则的约束，所以root在Linux里几乎可以做任何事。

### 权限的相对性

之前我们说过，Linux下一切皆文件。对于Linux来说，它的种种行为都可以被抽象成用户与文件这两个对象的交互。用户对文件能做什么，又不能做什么，不仅和用户本身有关，也和他所操作的文件有关，所以说，权限具有相对性。

#### 文件权限

文件权限是文件属性的一部分，之前我们在学习Linux基本指令的时候，我们说指令`ll`展示了文件的相关属性，其实这种说法是不准确的，`ll`真正展示的，主要是文件的权限。文件属性具有绝对性，对于文本文件来说，不可执行是它属性的一部分，不论它的权限怎样修改，这个文本文件都是不能被执行的。文件权限就不同了，它描述的是自己与用户的相对关系，因此，即使是一个文本文件，也可以设置为可被执行的权限。

```shell
[wind@starry-sky test]$ whoami
wind
[wind@starry-sky test]$ pwd
/home/wind/study/test
[wind@starry-sky test]$ ll
total 16
-rwxrwxr-x 1 wind wind 8360 Sep 23 21:18 a.out
-rw-rw-r-- 1 wind wind  128 Sep 23 21:18 test.c
[wind@starry-sky test]$ mkdir a
[wind@starry-sky test]$ ll
total 20
drwxrwxr-x 2 wind wind 4096 Sep 26 16:47 a
-rwxrwxr-x 1 wind wind 8360 Sep 23 21:18 a.out
-rw-rw-r-- 1 wind wind  128 Sep 23 21:18 test.c
[wind@starry-sky test]$ 

```

下面我们说一说`ll`展示的这些信息到底是什么意思。我们先看最前面的那个字符。也就是`drwxrwxr-x`中的`d`；`-rwxrwxr-x`中从左往右的的第一个`-`；`-rw-rw-r--`中从左往右的第一个`-`。这些字符描述对应文件的类型：

```
d：目录文件(文件夹)
-：普通文件（诸如可执行程序，库文件，文本文件等）
l：软链接
b：块设备文件
p：管道文件
c：字符设备文件
······
```

我们现在只需要看前两个就行了，也就是`d`和`-`，这两类文件在Linux总文件的占比超过九成，其它类型我们之后会说。Linux系统本身正是依据这些字符判断文件的类型，而不是像windows那样依靠后缀名判断类型。

```shell
[wind@starry-sky test]$ pwd
/home/wind/study/test
[wind@starry-sky test]$ ll
total 16
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a.out
-rw-rw-r-- 1 wind wind  128 Sep 26 17:10 test.c
[wind@starry-sky test]$ mkdir b
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a.out
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind wind  128 Sep 26 17:10 test.c
[wind@starry-sky test]$ 也就是说，后缀名对Linux本身没有多大意义^C
[wind@starry-sky test]$ mv a.out a.exe
[wind@starry-sky test]$ exe是windows可执行文件后缀名，out是Linux可执行文件后缀名^C
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a.exe
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind wind  128 Sep 26 17:10 test.c
[wind@starry-sky test]$ ./a.exe
hello nano
[wind@starry-sky test]$ mv a.exe a
[wind@starry-sky test]$ ls
a  b  test.c
[wind@starry-sky test]$ ./a
hello nano
[wind@starry-sky test]$ mv test.c test.out
[wind@starry-sky test]$ ls
a  b  test.out
[wind@starry-sky test]$ ./test.out
-bash: ./test.out: Permission denied
[wind@starry-sky test]$ mv test.out test.c
[wind@starry-sky test]$ 不过，后缀名只是对Linux系统本身没多大意义而已，对其它文件是有很大意义的^C
[wind@starry-sky test]$ 比如，gcc身为Linux中的C代码编译器，它是可执行文件^C
[wind@starry-sky test]$ 我们让gcc编译一下test.c^C
[wind@starry-sky test]$ gcc test.c
[wind@starry-sky test]$ ls
a  a.out  b  test.c
[wind@starry-sky test]$ 看，编译出了可执行文件——a.out^C
[wind@starry-sky test]$ rm a.out
[wind@starry-sky test]$ ls
a  b  test.c
[wind@starry-sky test]$ mv test.c test.txt
[wind@starry-sky test]$ ls
a  b  test.txt
[wind@starry-sky test]$ gcc test.txt
test.txt: file not recognized: File format not recognized
collect2: error: ld returned 1 exit status
[wind@starry-sky test]$ 可以看到，变成txt后，gcc就无法编译代码了^C
[wind@starry-sky test]$ 

```

#### 用户权限

实际上，我们上面说的文件相关信息最开头的那个字符，其实并不是用来描述文件权限的，而是描述文件绝对信息的，接下来我们要说的才是真正的文件权限，那为什么把文件权限归类到用户权限这个标题下呢？因为文件权限是相对用户来说的，所以脱离用户是说不了文件权限的。

让我们把思绪调整到`ll`展示的文件信息那里

```shell
drwxrwxr-x 2 wind wind 4096 Sep 26 16:47 a
-rwxrwxr-x 1 wind wind 8360 Sep 23 21:18 a.out
-rw-rw-r-- 1 wind wind  128 Sep 23 21:18 test.c
```

最开头的字符我们已经看过了，接下来我们看看它后面的九个字符，也就是`rwxrwxr-x  rwxrwxr-x  rw-rw-r--`，其中的`r`表示可被读，`w`表示可被写，`x`表示可被执行；而且我们还看到，有些字符是重复出现的，为什么会重复出现呢？因为它们是对不同种类的用户来说的，就拿`rwxrwxr-x`来举例，它可以分成三个小组：第一组：`rwx`，第二组：`rwx`，第三组`r-x`，对于第一组代表的用户来说，这个文件可以被读，被写，被执行（当然，前提是文件绝对属性允许）;那对于第二组代表的用户来说，这个文件可以被读，被写，被执行；对于第三组代表的用户来说，这个文件可以被读，不可被写，可以执行。也就是说，这九个字符中的`-`代表对应用户不能读/写/执行；这三种用户，既可以是普通用户，也可以是root，但要注意，尽管root可以充当这三种用户的某一个或者某几个，但这些规则约束都对root不起作用；只要这个文件的绝对属性可以被执行，那root就可以执行它，读写更不用说了，毕竟只要root愿意，甚至可以从根目录`/`开始，把整个系统删了，当然，某些正在被系统使用的文件可能暂时不会被删除，但这个系统绝对报废了，只能重装了。

这三种用户，具体来说，是拥有者，所属组，其他人。拥有者好理解，就是这个文件的所有人，这个文件是他的，那他就是所有人，所属组呢，那就是和拥有者有些关系的那一类人，比如，你所在那个小组的其他成员，或者说你的上级领导什么的，当然，我说的不是竞争对手的那种关系；其他人就是除此之外的人。

有些人可能会问，我怎么会和我的竞争对手合用同一台服务器，这不一定呦。有些企业，他们喜欢把同一个项目交给不同的小组来做，让这些小组卷一卷，公司最后会选更好的那组的成果，如果企业还比较小，那同一公司中的不同组用同一台服务器就更大可能了。不过也有些公司严厉禁止这种不同组干同样项目的事情发生。

那文件怎么看它的所有人和所属组呢？那就是文件信息中那两个名字的作用，对于`drwxrwxr-x 2 wind wind 4096 Sep 26 16:47 a`来说，它的第一个`wind`描述的是这个文件的拥有者，第二个`wind`描述的是文件的所属组，因为我没有把`wind`这个用户分到任何组里，实际上，我这台服务器没有一个组，所以这台服务器中的每个人都自成一组，那可能会有人问，如果此时拥有人的权限和所属组的权限不一样，会不会冲突呢？不会的，系统会按照拥有者，所属组，的顺序依次比对当前登录的账号，如果当前账号是拥有者，用的就是拥有者的权限，如果不是，就看当前账号是不是所属组，如果是的话，就用所属组的权限，如果还不是，那就用其他人的权限。

`4096`就不说了，是文件大小；`Sep 26 16:47`是最近修改日期，`a`是文件名，还有一个东西，`2`我们先不考虑。

#### 文件权限的修改

不考虑root的话，文件的拥有者有权修改文件权限。

```shell
[wind@starry-sky test]$ pwd
/home/wind/study/test
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind wind  128 Sep 26 17:10 test.txt
[wind@starry-sky test]$ 指令"chmod"可以修改文件权限^C
[wind@starry-sky test]$ 'u'的意思是拥有者（user）^C
[wind@starry-sky test]$ 'g'的意思是所属组（group）^C
[wind@starry-sky test]$ 'o'是其他人（others）^C
[wind@starry-sky test]$ '-'是减的意思^C
[wind@starry-sky test]$ '+'是加的意思^C
[wind@starry-sky test]$ chmod u-rw,g-rw,o-r test.txt
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
---------- 1 wind wind  128 Sep 26 17:10 test.txt
[wind@starry-sky test]$ cat test.txt
cat: test.txt: Permission denied
[wind@starry-sky test]$ echo "//abcd" >> test.txt
-bash: test.txt: Permission denied
[wind@starry-sky test]$ 

```

当然，尽管root对于`test.txt`是其他人，但root不受约束

```shell
[root@starry-sky ~]# whoami
root
[root@starry-sky ~]# cd /home/wind/study/test
[root@starry-sky test]# ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
---------- 1 wind wind  128 Sep 26 17:10 test.txt
[root@starry-sky test]# cat test.txt
#include<stdio.h>

int main()
{
//记事本就不要那么讲究了
//Ctrl+x保存并退出
 printf("hello nano\n");return 0;
}
[root@starry-sky test]# echo "//abc" >> test.txt
[root@starry-sky test]# cat test.txt
#include<stdio.h>

int main()
{
//记事本就不要那么讲究了
//Ctrl+x保存并退出
 printf("hello nano\n");return 0;
}
//abc
[root@starry-sky test]# chmod g+rw,o+r test.txt
[root@starry-sky test]# ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
----rw-r-- 1 wind wind  134 Sep 26 19:53 test.txt
[root@starry-sky test]# 

```

回到`wind`

```shell
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
----rw-r-- 1 wind wind  134 Sep 26 19:53 test.txt
[wind@starry-sky test]$ chmod u+rwx test.txt
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rwxrw-r-- 1 wind wind  134 Sep 26 19:53 test.txt
[wind@starry-sky test]$ 'test.txt'的绝对文件属性是不可执行^C
[wind@starry-sky test]$ 所以即使权限改成可执行，也无法执行^C
[wind@starry-sky test]$ ./test.txt
./test.txt: line 3: syntax error near unexpected token `('
./test.txt: line 3: `int main()'
[wind@starry-sky test]$ chmod u-x test.txt
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind wind  134 Sep 26 19:53 test.txt
[wind@starry-sky test]$ a表示all^C
[wind@starry-sky test]$ chmod a-rwx test.txt
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
---------- 1 wind wind  134 Sep 26 19:53 test.txt
[wind@starry-sky test]$ 

```

不过我们平时不这样改权限，对于读来说，只有可以和不可以这两种选项，同样的，写和执行也只有两种可能，也就是说，读，写，执行这三位是二进制的，所以`r--`就是`100`(4)，`rw-`就是`110`(6)，`rwx`就是`111`(7)；即，有权限的位为1，无权限的位为0。这样的话，我们就可以用八进制表示三种用户的权限。

```shell
[wind@starry-sky test]$ 110 110 100——664^C
[wind@starry-sky test]$ chmod 664 test.txt
[wind@starry-sky test]$ ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind wind  134 Sep 26 19:53 test.txt
[wind@starry-sky test]$ 

```

#### 文件所有权转移

文件的拥有者可以转移，比较稳妥一点的方法是用root转移所有权，文件当前拥有者也可以转移所有权，但视具体系统而定，有些系统可能不需要被给予者的同意，有些需要同意，总之，root最稳妥。所有权转移指令为`chown`，默认修改拥有者，冒号后面的表示新的所属组。

```shell
[root@starry-sky test]# ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind wind  134 Sep 26 19:53 test.txt
[root@starry-sky test]# chown whisper test.txt
[root@starry-sky test]# ll
total 20
-rwxrwxr-x 1 wind    wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind    wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 whisper wind  134 Sep 26 19:53 test.txt
[root@starry-sky test]# chown root:root test.txt
[root@starry-sky test]# ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 root root  134 Sep 26 19:53 test.txt
[root@starry-sky test]# chown wind:wind test.txt
[root@starry-sky test]# ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind wind  134 Sep 26 19:53 test.txt
[root@starry-sky test]# chown :root test.txt
[root@starry-sky test]# ll
total 20
-rwxrwxr-x 1 wind wind 8360 Sep 26 17:10 a
drwxrwxr-x 2 wind wind 4096 Sep 26 17:13 b
-rw-rw-r-- 1 wind root  134 Sep 26 19:53 test.txt
[root@starry-sky test]# 

```

#### 目录文件的相关权限

前面我们说的都是普通文件，接下来就要说目录文件了

```shell
[wind@starry-sky study]$ ll
total 24
drwxrwxr-x 3 wind wind 4096 Sep 23 18:10 d1
-rw-rw-r-- 1 wind wind   24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind  361 Sep 23 18:52 d.tgz
-rw-rw-r-- 1 wind wind   73 Sep 23 17:17 newf.txt
-rw-rw-r-- 1 wind wind  357 Sep 20 16:52 report.txt
-rw-rw-r-- 1 wind wind    0 Sep 20 12:31 sour.txt
drwxrwxr-x 3 wind wind 4096 Sep 26 17:22 test
[wind@starry-sky study]$ 

```

我们看到，目录文件也是`rwx`这种权限，那这里的`r  w  x`到底各指什么呢？我们逐一实验。

`wind`

```shell
[wind@starry-sky home]$ whoami
wind
[wind@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwx------ 5 wind    wind    4096 Sep 23 18:34 wind
[wind@starry-sky home]$ 我们先来到home目录下^C
[wind@starry-sky home]$ 我们发现目录"wind"没有给others任何权限^C
[wind@starry-sky home]$ 我们先为others赋予读权限^C
[wind@starry-sky home]$ chmod 774 wind
[wind@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwxrwxr-- 5 wind    wind    4096 Sep 23 18:34 wind
[wind@starry-sky home]$ 

```

`whisper`

```shell
[whisper@starry-sky ~]$ whoami
whisper
[whisper@starry-sky ~]$ cd /home
[whisper@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwxrwxr-- 5 wind    wind    4096 Sep 23 18:34 wind
[whisper@starry-sky home]$ cd wind
-bash: cd: wind: Permission denied
[whisper@starry-sky home]$ 没有进入权限^C
[whisper@starry-sky home]$ ls wind
ls: cannot access wind/study: Permission denied
ls: cannot access wind/sour.txt: Permission denied
sour.txt  study
[whisper@starry-sky home]$ 虽然略有波折，但我们看到了"wind"下的文件^C
[whisper@starry-sky home]$ cat wind/sour.txt
cat: wind/sour.txt: Permission denied
[whisper@starry-sky home]$ 看来也仅限于看到有什么文件了^C
[whisper@starry-sky home]$ 看不到具体内容^C
[whisper@starry-sky home]$ 

```

`wind`

```shell
[wind@starry-sky home]$ 上面的实验证明，r不是目录进入权限^C
[wind@starry-sky home]$ 而是查看目录下文件相关信息的权限^C
[wind@starry-sky home]$ 那w,x哪一个是目录进入权限^C
[wind@starry-sky home]$ 感觉x更有可能^C
[wind@starry-sky home]$ chmod 441 wind
[wind@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
dr--r----x 5 wind    wind    4096 Sep 23 18:34 wind
[wind@starry-sky home]$ 

```

`whisper`

```shell
[whisper@starry-sky home]$ whoami
whisper
[whisper@starry-sky home]$ cd wind
[whisper@starry-sky wind]$ 可以进入^C
[whisper@starry-sky wind]$ ll
ls: cannot open directory .: Permission denied
[whisper@starry-sky wind]$ 不能查看文件相关信息^C
[whisper@starry-sky wind]$ 看来x是可被进入^C
[whisper@starry-sky wind]$ cd ..
[whisper@starry-sky home]$ 

```

`wind`

```shell
[wind@starry-sky home]$ whoami
wind
[wind@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
dr--r----x 5 wind    wind    4096 Sep 23 18:34 wind
[wind@starry-sky home]$ chmod 775 wind
[wind@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwxrwxr-x 5 wind    wind    4096 Sep 23 18:34 wind
[wind@starry-sky home]$ 

```

`whisper`

```shell
[whisper@starry-sky home]$ whoami
whisper
[whisper@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwxrwxr-x 5 wind    wind    4096 Sep 23 18:34 wind
[whisper@starry-sky home]$ cd wind
[whisper@starry-sky wind]$ ll
total 8
-rw-rw-r-- 1 wind wind   12 Sep 19 20:59 sour.txt
drwxrwxr-x 4 wind wind 4096 Sep 23 18:53 study
[whisper@starry-sky wind]$ cat sour.txt
hello Linux
[whisper@starry-sky wind]$ 看来r+x才能查看文件具体内容^C
[whisper@starry-sky wind]$ 

```

`whisper`

```shell
[whisper@starry-sky wind]$ w大概可以猜出来了^C
[whisper@starry-sky wind]$ 没有w不能创建文件^C
[whisper@starry-sky wind]$ mkdir abc
mkdir: cannot create directory ‘abc’: Permission denied
[whisper@starry-sky wind]$ 没有w不能删除文件^C
[whisper@starry-sky wind]$ ll
total 8
-rw-rw-r-- 1 wind wind   12 Sep 19 20:59 sour.txt
drwxrwxr-x 4 wind wind 4096 Sep 23 18:53 study
[whisper@starry-sky wind]$ rm sour.txt
rm: remove write-protected regular file ‘sour.txt’? y
rm: cannot remove ‘sour.txt’: Permission denied
[whisper@starry-sky wind]$ 不能移动文件^C
[whisper@starry-sky wind]$ mv sour.txt sour.txt
mv: ‘sour.txt’ and ‘sour.txt’ are the same file
[whisper@starry-sky wind]$ ll
total 8
-rw-rw-r-- 1 wind wind   12 Sep 19 20:59 sour.txt
drwxrwxr-x 4 wind wind 4096 Sep 23 18:53 study
[whisper@starry-sky wind]$ 不能复制文件^C
[whisper@starry-sky wind]$ cp sour.txt ..
cp: cannot create regular file ‘../sour.txt’: Permission denied
[whisper@starry-sky wind]$ cd ..
[whisper@starry-sky home]$ 

```

`wind`

```shell
[wind@starry-sky home]$ whoami
wind
[wind@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwxrwxr-x 5 wind    wind    4096 Sep 23 18:34 wind
[wind@starry-sky home]$ chmod 700 wind
[wind@starry-sky home]$ ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwx------ 5 wind    wind    4096 Sep 23 18:34 wind
[wind@starry-sky home]$ 尽管已经知道了结果^C
[wind@starry-sky home]$ 但我们还是试试root^C
[wind@starry-sky home]$ 

```

`root`

```shell
[root@starry-sky ~]# whoami
root
[root@starry-sky ~]# cd /home
[root@starry-sky home]# ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwx------ 5 wind    wind    4096 Sep 23 18:34 wind
[root@starry-sky home]# cd wind
[root@starry-sky wind]# ll
total 8
-rw-rw-r-- 1 wind wind   12 Sep 19 20:59 sour.txt
drwxrwxr-x 4 wind wind 4096 Sep 23 18:53 study
[root@starry-sky wind]# cat sour.txt
hello Linux
[root@starry-sky wind]# echo "abc" >> sour.txt
[root@starry-sky wind]# cat sour.txt
hello Linux
abc
[root@starry-sky wind]# cd ..
[root@starry-sky home]# chown root:root wind
[root@starry-sky home]# ll
total 8
drwx------ 2 whisper whisper 4096 Sep 26 15:24 whisper
drwx------ 5 root    root    4096 Sep 23 18:34 wind
[root@starry-sky home]# chown wind:wind wind
[root@starry-sky home]# 

```

所以普通文件能否被删除取决于它所在的文件夹。

### 文件权限的初始化

随手创建一个普通文件，我们发现它的初始权限是`664`，而对目录文件来说，初始权限为`775`。另外再说一下，Linux默认给普通文件的初始权限是`666`（因为普通文件中绝大多数是不可执行文件），目录文件是`777`（既然都创建了一个目录，自然要可查看，可更改，可进入），现在的问题是`666`是怎么变成`664`的，`777`又是怎么变成`775`的。

这就引出了Linux中的一个机制：权限掩码。权限掩码是一种筛选机制，凡是被权限掩码标记过的权限，都不会出现在最终默认权限中，可以通过`umask`查看权限掩码：

```shell
[wind@starry-sky test]$ umask
0002
[wind@starry-sky test]$ 

```

第一个0另有作用，我们先不看。`002`的意思就是不要让文件最终默认权限中的其他人有写入权限。

`最终默认权限 = 默认权限 & (~权限掩码)`

比如，普通文件默认权限为`666`，即`110 110 110`；权限掩码取反后是`111 111 101` ，再把二者按位与，就有了`110 110 100`，即`664`；目录文件默认权限为`777`，即`111 111 111`；权限掩码取反是`111 111 101`，按位与后就是`111 111 101`，即`775`。

权限掩码的修改方式是`umask 新权限掩码`

另外要注意，每个用户都有自己的权限掩码，普通用户的初始权限掩码为`0002`，而`root`是`0022`。

## 粘滞位

粘滞位是一种特殊的目录文件执行权限。它是为了让不同用户协同工作而设计的。

为了让不同用户协同工作，我们需要设计一个共享文件夹。这个共享文件夹可以允许多个用户访问，各个用户可以选择性地给别人展示或者修改自己的文件，而且他人无法删除自己的文件。

`root`

```shell
[root@starry-sky home]# cd /
[root@starry-sky /]# ll
total 60
lrwxrwxrwx.   1 root root     7 Jun 28 12:16 bin -> usr/bin
dr-xr-xr-x.   5 root root  4096 Jun 28 12:38 boot
drwxr-xr-x   19 root root  2980 Sep 12 17:11 dev
drwxr-xr-x.  80 root root  4096 Sep 26 14:56 etc
drwxr-xr-x.   4 root root  4096 Sep 26 14:39 home
lrwxrwxrwx.   1 root root     7 Jun 28 12:16 lib -> usr/lib
lrwxrwxrwx.   1 root root     9 Jun 28 12:16 lib64 -> usr/lib64
drwx------.   2 root root 16384 Jun 28 12:16 lost+found
drwxr-xr-x.   2 root root  4096 Apr 11  2018 media
drwxr-xr-x.   2 root root  4096 Apr 11  2018 mnt
drwxr-xr-x.   2 root root  4096 Apr 11  2018 opt
dr-xr-xr-x  100 root root     0 Sep 12 17:10 proc
dr-xr-x---.   6 root root  4096 Sep 15 20:02 root
drwxr-xr-x   25 root root   760 Sep 23 21:02 run
lrwxrwxrwx.   1 root root     8 Jun 28 12:16 sbin -> usr/sbin
drwxr-xr-x.   2 root root  4096 Apr 11  2018 srv
dr-xr-xr-x   13 root root     0 Sep 15 14:07 sys
drwxrwxrwt.   9 root root  4096 Sep 27 03:10 tmp
drwxr-xr-x.  13 root root  4096 Jun 28 12:16 usr
drwxr-xr-x.  19 root root  4096 Jun 28 04:21 var
[root@starry-sky /]# Linux自带一个共享文件夹——tmp^C
[root@starry-sky /]# 粘滞位用t表示^C
[root@starry-sky /]# 让我们先来感受一下不用粘滞位会怎么样^C
[root@starry-sky /]# mkdir mytmp
[root@starry-sky /]# chmod 777 mytmp
[root@starry-sky /]# ll mytmp
total 0
[root@starry-sky /]# ll -d mytmp
drwxrwxrwx 2 root root 4096 Sep 27 10:36 mytmp
[root@starry-sky /]# 

```

`wind`

```shell
[wind@starry-sky home]$ cd /mytmp
[wind@starry-sky mytmp]$ touch hello
[wind@starry-sky mytmp]$ echo "hello whisper" > hello
[wind@starry-sky mytmp]$ cat hello
hello whisper
[wind@starry-sky mytmp]$ ll
total 4
-rw-rw-r-- 1 wind wind 14 Sep 27 10:40 hello
[wind@starry-sky mytmp]$ others可以读，但不能改^C
[wind@starry-sky mytmp]$ 

```

`whisper`

```shell
[whisper@starry-sky home]$ cd /mytmp
[whisper@starry-sky mytmp]$ ll
total 4
-rw-rw-r-- 1 wind wind 14 Sep 27 10:40 hello
[whisper@starry-sky mytmp]$ cat hello
hello whisper
[whisper@starry-sky mytmp]$ 

```

`wind`

```shell
[wind@starry-sky mytmp]$ chmod o-r hello
[wind@starry-sky mytmp]$ ll
total 4
-rw-rw---- 1 wind wind 14 Sep 27 10:40 hello
[wind@starry-sky mytmp]$ 

```

`whisper`

```shell
[whisper@starry-sky mytmp]$ cat hello
cat: hello: Permission denied
[whisper@starry-sky mytmp]$ rm hello
rm: remove write-protected regular file ‘hello’? y
[whisper@starry-sky mytmp]$ ll
total 0
[whisper@starry-sky mytmp]$ 因为mytmp目录对others可以w^C
[whisper@starry-sky mytmp]$ 所以others可以互删别人文件^C
[whisper@starry-sky mytmp]$ ^C
[whisper@starry-sky mytmp]$ 

```

---------

有粘滞位的就不一样了

`root`

```shell
[root@starry-sky /]# chmod o+t mytmp
[root@starry-sky /]# ll -d mytmp
drwxrwxrwt 2 root root 4096 Sep 27 10:45 mytmp
[root@starry-sky /]# 

```

`wind`

```shell
[wind@starry-sky /]$ cd mytmp
[wind@starry-sky mytmp]$ touch a
[wind@starry-sky mytmp]$ echo "abc" >> a
[wind@starry-sky mytmp]$ ll
total 4
-rw-rw-r-- 1 wind wind 4 Sep 27 10:53 a
[wind@starry-sky mytmp]$ chmod o-r a
[wind@starry-sky mytmp]$ 

```

`whisper`

```shell
[whisper@starry-sky /]$ cd mytmp
[whisper@starry-sky mytmp]$ ll
total 4
-rw-rw---- 1 wind wind 4 Sep 27 10:53 a
[whisper@starry-sky mytmp]$ cat a
cat: a: Permission denied
[whisper@starry-sky mytmp]$ rm a
rm: remove write-protected regular file ‘a’? y
rm: cannot remove ‘a’: Operation not permitted
[whisper@starry-sky mytmp]$ 

```

当一个目录被设置为`粘滞位`时，该目录下下的文件只能由文件对应的所有者，root，该目录的所有者删除，当然，由于共享文件夹一般在根目录下，而根目录对任何人都没有写权限，所以一般root就是该目录的所有者。

```shell
[root@starry-sky /]# ll -d /
dr-xr-xr-x. 19 root root 4096 Sep 27 10:36 /
[root@starry-sky /]# 

```

# 完