

# Linux基本指令

上节课中我们介绍了Linux的历史背景，并简要说明了我们搭建Linux的方式——云服务器，认识了Linux最本质的特征——开源。以及介绍了我们操控云服务器的方式：`XShell` ，下面我们将开始Linux基本指令的学习。

注：下面使用的操作系统是`CentOS 7.9 64位`。

## 什么是操作系统

我们知道，计算机系统一般可以分为四个大类：

![image-20240915134635721](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151346945.png)

在其中，真正满足用户需求的是应用软件，下面的三层都是为了给应用软件提供一个良好的工作环境。操作系统负责管理计算机的各类软硬件资源，并为应用软件提供所需要的服务；设备驱动是操作系统与硬件沟通的桥梁，负责控制具体的某类硬件；硬件为上三层提供最基本的物理条件，并给出计算机与外界物理环境的交互方式。

## 开始

ls最基本的功能就是展示当前路径下的文件和文件夹。不过由于我这里什么都没有，所以什么都没有写。

![image-20240915142100079](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151421136.png)

那我这里到底是什么路径下呢？这就需要pwd指令，它用于查看当前路径

![image-20240915142230732](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151422783.png)

我们使用mkdir在当前路径下创建一个文件夹。

![image-20240915142451659](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151424717.png)

使用ls指令再次查看，发现文件夹已经创建成功。

文件夹创建好了，接下来就是进入了，这要是用cd指令，意为切换路径。

![image-20240915143128482](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151431531.png)

现在我们在这个文件夹下使用touch建立一个笔记本文件，然后再建立几个文件夹。

![image-20240915145141985](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151451037.png)

指令可以携带选项，用于实现更多子功能。比如使用ls -l展示文件详细信息。

![image-20240915145448437](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151454489.png)

total用于描述下面的信息有多少列，不重要，略过。文件夹使用蓝色字体强调。名字前面的那些就是对应的属性信息。

ls -l可简写成ll，选项可以多个选中

![image-20240915152853491](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151528540.png)

![image-20240915153107323](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151531358.png)

前面以d开头的，意思这是一个目录或者文件夹，以-开头的，意思就是这是一个普通文件。开头那两个以点为开头的路径，或者说文件夹" . " 和 " .. "是个什么东西？在Linux中，以.为开头的文件是隐藏文件，平常不可见，a是all的意思，所以用了-a 选项之后，就显示出来了。

之前我们也没有创建这两个以" . "为开头的文件夹，难道，每创立一个新的文件夹，里面都会自动创建" . "和" .. "路径吗？进入o1里看一看。

![image-20240915154910399](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151549442.png)

看来我们刚刚猜的好像没错。那这两个路径到底是往哪里指的？进去试一试，每进去一次，就定位一下，方便我们对照。

![image-20240915155359007](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151553044.png)

我们看到，每次进入" .. "路径后，所处的路径似乎都往上移了一级，而且移到这个" \ " 的路径后，好像就移不上去了。所以" .. "实际上是当前路径的上一级路径，方便你从某个目录里退出来的。

那只有一个点的路径是什么呢？其实，它就是这个文件夹的路径，这有什么用呢？这实际是方便你对文件夹中的文件进行指代的，比如之后我们用源代码编译产生可执行程序之后，想要执行这个程序，那就直接输入" ./name.out"回个车就行了，就会执行了。Linux中的可执行程序是以" .out "为后缀的，

ls还有许多选项，比如,ls -d 。进入某个文件夹后，使用ls查看这个文件夹下的文件夹时，我们发现，它显示的是这个子文件夹下的文件，如果我们只想看这个子文件夹本身，就用这个选项。

![image-20240915162147056](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151621102.png)

![image-20240915162318098](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151623136.png)

除此之外，还有一个F选项，它可以让文件以字符的形式展示自己的类型，比如，" \ "代表是路径或者说文件夹，" * "代表普通的可执行程序，普通文件就不带后缀，其它一些后缀现在用不上，就不说了。

![image-20240915163129563](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151631621.png)

除此之外，ls还有一些选项，但现在还用不上，就不说了。

![image-20240915163326615](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151633747.png)

-------

刚刚我们尝试" .. "的路径时，发现它到" / "就跑不上去了，这就牵扯到Linux的文件系统了。跑不上去意味着这就是Linux的根节点。我们看一下这个目录的信息。

![image-20240915164136645](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151641706.png)

之前我们学习树的时候，就提到了Linux的文件树：

![image-20240915164312135](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151643269.png)

刚刚我们cd后面的路径有些是相对路径，什么叫相对路径呢？就是与当前路径相对的路径，比如我们想进入当前文件夹下一个叫" one "的文件夹，那我可以cd后面直接接one（当然，要留空格的），相对路径与我当前所处的路径相关联，就像物理里把自己当成参考系；除此之外，还有一种绝对路径，绝对路径是以根节点为参考系的，不管我当前在哪里，这种路径都是准确的，比如，我们现在先进根节点下的home文件夹，然后用绝对路径进入o1那个文件夹。

![image-20240915165542959](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151655995.png)

日常我们用什么路径呢？一般是相对路径，因为有的路径太长了，不太好记住。当然如果你某个路径用多了，都把路径记得很牢，那就一步到位。总之，哪个路径好用就用哪个。

--------

接下来我们使用" whoami "看看我们当前登录的账号是谁。

![image-20240915171621892](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151716931.png)

是root，也就是超级用户，负责管理整个操作系统的。这也是我们之前刚登陆的时候在root这个文件夹下的原因。现在我们创建一个新的普通账号。

![image-20240915173146537](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151731594.png)

adduser wind：添加一个叫"wind"的账号（用户）；

password wind：为wind设置登录密码；

为了安全，Linux的密码并不显示，连星号都没有，输入后直接回车就行，这里我第一次输错了。

现在登录到这个账户

![image-20240915174228266](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151742381.png)

我们知道，安卓手机上划一下就可以回到主页，或者说桌面，其实安卓就是由Linux系统改出来的，那Linux怎么回到桌面，或者是home，那就用cd ~这个指令；除此之外，还有cd -，这个指令可以回到上一级历史路径，让我们来试一试：为了有足够权限，我先换回root账号

![image-20240915190302803](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151903859.png)

![image-20240915190622509](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151906573.png)

-----

touch指令本意为触摸，它也有很多选项，不过最常用的是创建一个文件，注意，只能创建文件，不能创建文件夹或者说路径，文件夹要用mkdir；其它的选项现在还用不上。

![image-20240915191654442](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151916488.png)

------

上面我们使用mkdir建立了叶节点，但有时候，我们要建立一个路径，或者说一棵子树，（当然一个节点也算树，这里说的是多个节点的树），就可以给mkdir 带上-p选项

![image-20240915192722471](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151927508.png)

指令tree可以展示目录的树结构，我这里没有装，需要先装一下

![image-20240915193519231](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409151935299.png)

------

文件和路径的创建都说完了，接下来就要说怎么删了。

文件和路径的删除有两个相关指令：rmdir和rm。rmdir和mkdir相对，只能删除叶节点的文件夹，一个子树，或者说普通文件它都删不了；我们平常使用的删除指令一般是rm，在不加选项时，rm既可以删除普通文件，也可以删除空文件夹，有时，特别是对于root用户来说，删除时它会让你确认一下，这时你输入" y "，它就删除了；如果加上选项" -r "，则表示递归式删除，此时就可以删除一棵子树了（子树是递归结构，文件夹里还有文件夹），如果你不想一个一个地确认删除，可以再添加选项" f "，这个选项的意思是本指令不要进行确认。 不过这里我主动询问是否要删除是因为我登录的是root账号，也在root的路径下，为了安全，对于此路径下的文件删除系统会默认询问，如果是普通账户，也不在敏感路径下，系统默认不会询问，如果想要询问，可以加上选项i。

![image-20240915200438453](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409152004585.png)

Linux的文件恢复非常麻烦，在Linux的初期学习阶段中，删东西一定要谨慎，代码写完了一定要及时提交到码云上，不过如果操作系统里有些东西不能泄露出来，紧急情况下直接rm -rf /直接把整个文件树删完也是不错的选择。

-----

为了方便叙述，下文中我们把文件夹都叫做路径。

------

接下来介绍通配符，通配符有很多内容，但现在我们只需要知道它表示所有。比如现在我就建立了四个文件：

![image-20240919174750685](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191747812.png)

*.c表示所有以.c结尾的文件，test\*表示所有以test开头的文件。

![image-20240919175500115](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191755171.png)

------

Linux里有很多东西，比如说什么基本指令，系统接口，C语言库等等。不好全部记住，于是就有了man指令，当有什么东西不太清楚，你就可以问一问这个man。

进入文档后，使用上下方向键移动文档内容；按下q键退出文档，返回控制台。

![image-20240919182102017](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191821111.png)

![image-20240919182211452](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191822584.png)

![image-20240919182304677](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191823829.png)

![image-20240919182359132](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191823179.png)

![image-20240919182437486](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191824622.png)

查询man自己，我们会发现，我这里一共有9个手册。我们当前只关心前三个：1.可执行程序或 shell 命令（基本指令） 2.系统调用（内核提供的功能）（系统接口） 3. 程序库调用（程序库内的功能）（主要指C语言），其它的现在我们用不到。

如果不指定，man会从第一个手册查起，查不到就查第二个手册，直到查到，把文档显示出来，或者没查到提示查不到。不过，有些东西，比如说printf，它既是基本指令，也是C语言标准库中的函数，（同名是因为功能相似）如果不指定，他只会把第一个手册里的基本指令printf文档显示给你看，所以如果要查询C中的printf，就要指定第三个手册。

![image-20240919183623797](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191836867.png)

![image-20240919183647673](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191836799.png)

![image-20240919183713271](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191837314.png)

![image-20240919185147856](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191851950.png)

我们发现它找不到，那可能是我的系统里man手册被精简过，不全。我们换回root账号更新一下。

CentOS用`sudo yum install -y man-pages`,Ubuntu用`sudo apt-get install -y man-pages`；记得用root账户安装。

![image-20240919185509853](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191855111.png)

再来试一试：

![image-20240919185840697](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191858761.png)

成功了

![image-20240919185933951](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409191859099.png)

如果都想看的话，用-a选项，这样就会先把前面的文档给你看，文档退出后，再回车，会给你看后面的文档，直到所有手册都找完了。

------

接下来我们看看文件拷贝，为了让现象更加明显，我们先创建一个空文件，然后向里面写点东西。

```shell
[wind@starry-sky study]$ pwd
/home/wind/study
[wind@starry-sky study]$ touch source.txt
[wind@starry-sky study]$ ll
total 0
-rw-rw-r-- 1 wind wind 0 Sep 19 20:00 source.txt
[wind@starry-sky study]$ echo "hello Linux"
hello Linux
[wind@starry-sky study]$ echo hello Linux
hello Linux
[wind@starry-sky study]$ printf "hello Linux"
hello Linux[wind@starry-sky study]$ 
[wind@starry-sky study]$ echo "hello Linux" > source.txt
[wind@starry-sky study]$ ll
total 4
-rw-rw-r-- 1 wind wind 12 Sep 19 20:02 source.txt
[wind@starry-sky study]$ cat source.txt
hello Linux
[wind@starry-sky study]$ 

```

指令echo在默认情况下，会把其后的内容识别为字符串（不论有没有双引号），然后再把这个字符串输出到屏幕上。后面那个">"是个什么东西呢？这叫重定向符，为什么有“重”呢？意思是重新，echo原本是把字符串往屏幕上输的（当然，对比指令printf可以更清楚地认识到还有个换行符），">"把echo的输出目的地重新修改（重新定位，重新定向）到了一个地方，什么地方呢？就是后面的那个文件source.txt。cat可以查看文件内容。

接下来就要拷贝了，拷贝指令cp一般用法是后面跟两个文件，前面的是源，后面的是目的；为了保证文件完整路径的唯一性，同一个路径中不能出现同名文件，不同的路径倒是可以。目的文件没有的话会被创建。

```shell
[wind@starry-sky study]$ cp source.txt destination.txt
[wind@starry-sky study]$ ll
total 8
-rw-rw-r-- 1 wind wind 12 Sep 19 20:34 destination.txt
-rw-rw-r-- 1 wind wind 12 Sep 19 20:02 source.txt
[wind@starry-sky study]$ source source.txt ../destination，txt
-bash: hello: command not found
[wind@starry-sky study]$ cp source.txt ../destination.txt
[wind@starry-sky study]$ ll ..
total 8
-rw-rw-r-- 1 wind wind   12 Sep 19 20:36 destination.txt
drwxrwxr-x 2 wind wind 4096 Sep 19 20:34 study

```

cp也可以拷贝路径，不过由于路径是递归形式的，所以需要带上选项-r。如果害怕目的文件已经存在，拷贝覆写破坏目的文件的旧内容，就带上选项-i，这样，目的文件若已经存在，它会向你确认。

```shell
[wind@starry-sky study]$ clear
[wind@starry-sky study]$ pwd
/home/wind/study
[wind@starry-sky study]$ tree ..
..
├── destination.txt
├── source.txt
└── study
    ├── destination.txt
    └── source.txt

1 directory, 4 files
[wind@starry-sky study]$ cd ~
[wind@starry-sky ~]$ pwd
/home/wind
[wind@starry-sky ~]$ ll
total 12
-rw-rw-r-- 1 wind wind   12 Sep 19 20:36 destination.txt
-rw-rw-r-- 1 wind wind   12 Sep 19 20:54 source.txt
drwxrwxr-x 2 wind wind 4096 Sep 19 20:34 study
[wind@starry-sky ~]$ cp -r study s
[wind@starry-sky ~]$ tree .
.
├── destination.txt
├── s
│   ├── destination.txt
│   └── source.txt
├── source.txt
└── study
    ├── destination.txt
    └── source.txt

2 directories, 6 files
[wind@starry-sky ~]$ cd -
/home/wind/study
[wind@starry-sky study]$ ll
total 8
-rw-rw-r-- 1 wind wind 12 Sep 19 20:34 destination.txt
-rw-rw-r-- 1 wind wind 12 Sep 19 20:02 source.txt
[wind@starry-sky study]$ cp -i source.txt ../source.txt
cp: overwrite ‘../source.txt’? y
[wind@starry-sky study]$ 

```

root账号下的cp指令行为可能和普通账号不同，这里以普通账号为主。

-----

指令mv可以修改文件名，或者对文件进行剪切。如果不跨路径的话就是重命名，如果跨路径的话，就是剪切，跨路径时，不输新名字就会以原名剪切过去，输新名字就会剪切过去后重命名。这样的话，如果要统一的话，也可以认为不跨路径是先剪切到当前路径下，然后重命名。如果是目录，也可以重命名。

```shell
[wind@starry-sky study]$ clear
[wind@starry-sky study]$ pwd
/home/wind/study
[wind@starry-sky study]$ cd ~
[wind@starry-sky ~]$ tree .
.
├── destination.txt
├── s
│   ├── destination.txt
│   └── source.txt
├── source.txt
└── study
    ├── destination.txt
    └── source.txt

2 directories, 6 files
[wind@starry-sky ~]$ rm -rf s
[wind@starry-sky ~]$ rm destination.txt
[wind@starry-sky ~]$ tree .
.
├── source.txt
└── study
    ├── destination.txt
    └── source.txt

1 directory, 3 files
[wind@starry-sky ~]$ mv source.txt source_backup.txt
[wind@starry-sky ~]$ tree .
.
├── source_backup.txt
└── study
    ├── destination.txt
    └── source.txt

1 directory, 3 files
[wind@starry-sky ~]$ mv source_backup.txt study/
[wind@starry-sky ~]$ tree .
.
└── study
    ├── destination.txt
    ├── source_backup.txt
    └── source.txt

1 directory, 3 files
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ mv source_backup.txt ../sour.txt
[wind@starry-sky study]$ tree ..
..
├── sour.txt
└── study
    ├── destination.txt
    └── source.txt

1 directory, 3 files
[wind@starry-sky ~]$ mv study st
[wind@starry-sky ~]$ tree .
.
├── sour.txt
└── st
    ├── destination.txt
    └── source.txt

1 directory, 3 files
[wind@starry-sky ~]$ mv st study
[wind@starry-sky ~]$ mv study study/s
mv: cannot move ‘study’ to a subdirectory of itself, ‘study/s’
[wind@starry-sky ~]$ mv study study/
mv: cannot move ‘study’ to a subdirectory of itself, ‘study/study’
[wind@starry-sky ~]$ cd ..
[wind@starry-sky home]$ mkdir -r d1/d2/d3
mkdir: invalid option -- 'r'
Try 'mkdir --help' for more information.
[wind@starry-sky home]$ man mkdir
[wind@starry-sky home]$ mkdir -p d1/d2/d3
mkdir: cannot create directory ‘d1’: Permission denied
[wind@starry-sky home]$ mkdir -p ./d1/d2/d3
mkdir: cannot create directory ‘./d1’: Permission denied
[wind@starry-sky home]$ pwd
/home
[wind@starry-sky home]$ ll
total 4
drwx------ 5 wind wind 4096 Sep 19 21:52 wind
[wind@starry-sky home]$ cd wind
[wind@starry-sky ~]$ pwd
/home/wind
[wind@starry-sky ~]$ tree .
.
├── sour.txt
└── study
    ├── destination.txt
    └── source.txt

1 directory, 3 files
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ mkdir -p d1/d2/d3
[wind@starry-sky study]$ tree ..
..
├── sour.txt
└── study
    ├── d1
    │   └── d2
    │       └── d3
    ├── destination.txt
    └── source.txt

4 directories, 3 files
[wind@starry-sky study]$ mv d1 ../d
[wind@starry-sky study]$ tree ..
..
├── d
│   └── d2
│       └── d3
├── sour.txt
└── study
    ├── destination.txt
    └── source.txt

4 directories, 3 files
[wind@starry-sky study]$ 

```

-----------

ctrl + c

之前我们在VS敲代码的时候，有时候会遇到死循环，此时我们都是按下`ctrl`+`c`，就能强行终止程序。同样的，Linux中也有类似的操作，当有些指令执行后妨碍我们后续输入时，可以直接按下`ctrl`+`c`强行终止这个指令。

比如可以执行下面的指令：

```shell
[wind@starry-sky ~]$ while  :; do echo "hello Linux" ; done
```

我们发现，执行这个指令后，控制台在不停地打印"hello Linux\n"，按什么键都没法反应，那就直接按下按下`ctrl`+`c`，指令就能被强行终止。(有极少数指令不能用`ctrl`+`c`终止)

```shell
······
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux
^C
[wind@starry-sky ~]$ 
```

`ctrl`+`c`的另外用法是当我们手抖了，一不小心敲错了，指令又很长，那就可以直接`ctrl`+`c`，那这个指令就不会被执行。或者指令你也不知道怎么输的，不知道跑到什么地方了，那也可以`ctrl`+`c`；注意`ctrl`+`c`不能恢复指令已经执行的部分，如果你用rm删一些东西，删一半终止了，删了的部分就是删了，恢复不了。

--------

指令是什么？

前面说过，指令就是要被执行的那个东西，所以指令实际简单的说，就是可执行程序。

我们可以在根目录下的user/bin路径下查看这些程序。

```c
[wind@starry-sky ~]$ ls /usr/bin
```

![image-20240920092105819](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409200921026.png)

所以，指令在被执行前，会在这个目录下进行寻找，找到就执行，找不到那就不执行。如果我把自己写的程序移到这个路径下，那它就可以直接当成指令来用；当然，这只是说说而已，这种行为会造成路径污染，让人分不清哪些程序是是自己写的，哪些是系统自己的，到时候就麻烦了。这种行为就是最简单的安装行为，同理，直接删除这个路径下的程序，就是最简单的卸载行为。

-------

我们在上面的路径下，可能找不到某些指令，比如ll，但ll又是可以被执行的，这是什么情况呢？前面说过，ll实际上是ls -l的简写，我们可以用`which`寻找指令的目录。

```shell
[wind@starry-sky ~]$ ls /usr/bin/ll
ls: cannot access /usr/bin/ll: No such file or directory
[wind@starry-sky ~]$ which ll
alias ll='ls -l --color=auto'
	/usr/bin/ls
[wind@starry-sky ~]$ which ls
alias ls='ls --color=auto'
	/usr/bin/ls
[wind@starry-sky ~]$ which pwd
/usr/bin/pwd
[wind@starry-sky ~]$ which cp
/usr/bin/cp
[wind@starry-sky ~]$ which mv
/usr/bin/mv
[wind@starry-sky ~]$ 

```

我们看到which对ll的应答是：`alias ll='ls -l --color=auto'`,其中的`alias`是重命名指令，于是`ls -l`就被重命名成了`ll`，当然你用原来名字当然也是可以的。后面的color是配色方案。

当然，你也可以自己对某个指令进行重命名，如果直接在控制台上输入重命名指令，那在这个终端下这个重命名就是有效的，但下次重新登录这个重命名就失效了。怎么持久化呢？像ll那样，写在配置文件里就行了，直接在控制台输入重命名指令相当于在内存中临时约定，写成文件才能持久化。不过对于初学者不建议这样用，容易分不清谁是谁。

------

下面我们接触一下Linux系统里的重要概念：Linux里一切皆文件。即使对于什么屏幕，键盘什么硬件设备，系统也视为文件。之前我们说过，操作系统一共有四层：应用，系统，驱动，硬件。而且我们说过，而且不能跨层交流。硬件只能与驱动交流，驱动直接对硬件操作，以及接收来自硬件的信息，硬件又怎么与系统交流呢？硬件把来自硬件的信息，写到某个类似文件的东西（接口）里，然后由系统读这个文件（接口）；同样的，系统要给硬件的信息或者说操作，都会写在另一个类似文件的东西（接口）里，硬件会读这个文件（接口），然后执行里面的命令，去满足系统的要求。所以说，对于系统来说，即使是屏幕，键盘这种硬件，对于系统来说，就是文件。

---------

现在回到之前那个话题：使用echo指令和重定向符">"写文件。让我们把这个指令分解一下。

```shell
[wind@starry-sky ~]$ ls
d  sour.txt  study
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ ls
destination.txt  source.txt
[wind@starry-sky study]$ cat source.txt
hello Linux
[wind@starry-sky study]$ echo "hello woeld" > source.txt
[wind@starry-sky study]$ cat source.txt
hello woeld
[wind@starry-sky study]$ ??^C
[wind@starry-sky study]$ echo "hello world" > source.txt
[wind@starry-sky study]$ cat source.txt
hello world
[wind@starry-sky study]$ 我们可以看到，对于已经存在的文件，这种操作会覆写文件中原有的内容^C
[wind@starry-sky study]$ 也就是说，上面的操作可以分为两步：^C
[wind@starry-sky study]$ 1.打开文件，将其清空^C
[wind@starry-sky study]$ 2.写入新内容^C
[wind@starry-sky study]$ 

```

所以重定向符“>”还有一种用法，由于它打开文件后会刷新文件，所以如果我不提供新内容，文件就相当于被清空了。如果想续写，就用这个重定向符">>"(追加重定向)，它打开文件之后，不会清空文件。

```shell
[wind@starry-sky study]$ > source.txt
[wind@starry-sky study]$ cat source.txt
[wind@starry-sky study]$ mv destination.txt dest.txt
[wind@starry-sky study]$ cat dest.txt
hello Linux
[wind@starry-sky study]$ echo "hello world" >> dest.txt
[wind@starry-sky study]$ cat dest.txt
hello Linux
hello world
[wind@starry-sky study]$ 如果不想换行，可以使用printf指令^C
[wind@starry-sky study]$ printf ""^C
[wind@starry-sky study]$ mv source.txt sour.txt
[wind@starry-sky study]$ printf "qwer" >> sour.txt
[wind@starry-sky study]$ printf "tyui" >> sour.txt
[wind@starry-sky study]$ cat sour.txt
qwertyui[wind@starry-sky study]$ > sour.txt
[wind@starry-sky study]$ 

```

前面说过，cat指令可以用来读一个文件的内容，然后把内容输出到控制台上；实际上，我也可以不给cat文件，此时cat就会去找系统默认文件，什么默认文件呢？从结果上可以看出，这个默认文件就是键盘。

```shell
[wind@starry-sky ~]$ whoami
wind
[wind@starry-sky ~]$ pwd
/home/wind
[wind@starry-sky ~]$ cat
a
a
b
b
c
c
d
d
e
e
^C
[wind@starry-sky ~]$ 此时，也可以对cat指令使用输入重定向符"<",这样就可以改变输入文件了^C
[wind@starry-sky ~]$ ls
d  sour.txt  study
[wind@starry-sky ~]$ cat sour.txt
hello Linux
[wind@starry-sky ~]$ cat < sour.txt
hello Linux
[wind@starry-sky ~]$ 这两种方法其实是有些区别的，但对于初学者来说，认为它们一样也是可以的^C
[wind@starry-sky ~]$ 如果重定向符的目的文件不存在的话，就会被创建，所以重定向符也可以用来创建文件^C
[wind@starry-sky ~]$ ls
d  sour.txt  study
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ ls
dest.txt  sour.txt
[wind@starry-sky study]$ > newf.txt
[wind@starry-sky study]$ ls
dest.txt  newf.txt  sour.txt
[wind@starry-sky study]$ 

```

我们在学习C语言文件管理的时候，不是学到了文件流的概念吗，重定向符就是改变了文件流。

-------

cat也是有选项的，"-b"可以给非空行写行号，'-n'对所有行写行号，'-s'可以将相邻的多个空行压缩成一行。让我们来试一试。

```sh
[wind@starry-sky study]$ pwd
/home/wind/study
[wind@starry-sky study]$ ls
dest.txt  newf.txt  sour.txt
[wind@starry-sky study]$ cat newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "" >>newf.txt
[wind@starry-sky study]$ echo "" >>newf.txt
[wind@starry-sky study]$ echo "" >>newf.txt
[wind@starry-sky study]$ echo "" >>newf.txt
[wind@starry-sky study]$ echo "" >>newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ cat newf.txt
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux





hello Linux
hello Linux
hello Linux
[wind@starry-sky study]$ cat -n newf.txt
     1	hello Linux
     2	hello Linux
     3	hello Linux
     4	hello Linux
     5	hello Linux
     6	
     7	
     8	
     9	
    10	
    11	hello Linux
    12	hello Linux
    13	hello Linux
[wind@starry-sky study]$ cat -b newf.txt
     1	hello Linux
     2	hello Linux
     3	hello Linux
     4	hello Linux
     5	hello Linux





     6	hello Linux
     7	hello Linux
     8	hello Linux
[wind@starry-sky study]$ cat -s newf.txt
hello Linux
hello Linux
hello Linux
hello Linux
hello Linux

hello Linux
hello Linux
hello Linux
[wind@starry-sky study]$ cat -sb newf.txt
     1	hello Linux
     2	hello Linux
     3	hello Linux
     4	hello Linux
     5	hello Linux

     6	hello Linux
     7	hello Linux
     8	hello Linux
[wind@starry-sky study]$ 

```

------

有时，我们需要读很多很长的文本内容，此时cat就不好用了，我们就需要用到more指令。

为了方便，我们先生成一份长文本内容。

```bash
cnt=1; while [ $cnt -le 10000 ]; do echo "hello Linux $cnt";let cnt++; done > newf.txt
```

```sh
[wind@starry-sky study]$ pwd
/home/wind/study
[wind@starry-sky study]$ ls
dest.txt  newf.txt  sour.txt
[wind@starry-sky study]$ cnt=1; while [ $cnt -le 10000 ]; do echo "hello Linux $cnt";let cnt++; done > newf.txt
[wind@starry-sky study]$ ll
total 172
-rw-rw-r-- 1 wind wind     24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind 168894 Sep 20 15:10 newf.txt
-rw-rw-r-- 1 wind wind      0 Sep 20 12:31 sour.txt
[wind@starry-sky study]$ 

```

此时用cat看文件就会很难受。

more的用法和cat类似，不过它不是一次性全部显示出来，而是显示一部分，然后用回车看下面的部分（看不了上面的部分），推出按Q键（ctrl + C也可以）；也可以带选项，比如"-5000"，就会来到5000行（当然，前提是文本够5000行）。

但实际上，我们不太用more指令（因为不能往上走），而是用另一个指令查看长文本文件。在more指令执行的过程中，也可以再敲"/ + 行数"，定位到目标行。

--------

less指令是Linux的正统文本查看指令，它可以上下移动（用上下方向键，向下也可以回车），除此之外，它也有很多指令。而且less还可以去搜索文本中的指定内容；怎么搜索呢？在more中，"/ + 内容"是定位到内容行，而在less中，是自当前位置往下面搜索（没加选项的，默认情况下的），如果有多个地方符合内容，按下"n"移动到下一符合内容，按下"N"移动到上一符合内容。而且less强行推出只能用Q，ctrl + c没用。

除此之外，还有head指令，用于显示文本开头的一定行数内容，默认为10行；tail指令，用于显示文本末尾的一定行数内容，默认也是10行，它们都通过选项"-行数"来更改。

-------

有时，我们只想看文本中间的一段内容，比如说文件一共有10000行，我现在只想看到5000到5020这21行，其它都不要，怎么办呢？一种方法是先用head截个5020行，定向到一个文件里，然后再用tail截个21行输出到控制台或者另一个文件里。

有没有其它方法呢？当然是有的，这就要说说管道文件了。很明显，打印一个文件中的文本内容需要先把文件读到内存里，然后指令才能把文本打印出来。管道文件并不是真的就存在硬盘里的文件，而是指文件内容已经被读到内存中的那个状态的“文件”，管道文件写作"|"，“|”前面的内容会被视为已经读到内存中的那个文件状态，后面则是对前面的内容进行操作，因为它有一种传输信息的感觉所以叫做“管道文件”。

```sh
[wind@starry-sky study]$ ls
dest.txt  newf.txt  sour.txt
[wind@starry-sky study]$ ll
total 172
-rw-rw-r-- 1 wind wind     24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind 168894 Sep 20 15:10 newf.txt
-rw-rw-r-- 1 wind wind      0 Sep 20 12:31 sour.txt
[wind@starry-sky study]$ head -5020 newf.txt | tail -21
hello Linux 5000
hello Linux 5001
hello Linux 5002
hello Linux 5003
hello Linux 5004
hello Linux 5005
hello Linux 5006
hello Linux 5007
hello Linux 5008
hello Linux 5009
hello Linux 5010
hello Linux 5011
hello Linux 5012
hello Linux 5013
hello Linux 5014
hello Linux 5015
hello Linux 5016
hello Linux 5017
hello Linux 5018
hello Linux 5019
hello Linux 5020
[wind@starry-sky study]$ head -5020 newf.txt | tail -21 > report.txt
[wind@starry-sky study]$ cat report.txt
hello Linux 5000
hello Linux 5001
hello Linux 5002
hello Linux 5003
hello Linux 5004
hello Linux 5005
hello Linux 5006
hello Linux 5007
hello Linux 5008
hello Linux 5009
hello Linux 5010
hello Linux 5011
hello Linux 5012
hello Linux 5013
hello Linux 5014
hello Linux 5015
hello Linux 5016
hello Linux 5017
hello Linux 5018
hello Linux 5019
hello Linux 5020
[wind@starry-sky study]$ 什么？你说管道不是横着的吗？横着容易和选项的"-"混淆^C
[wind@starry-sky study]$ 

```

----------

对于操作系统来说，时间是一个特别重要的概念。下面我们来学习Linux中与时间相关的指令。

date可以以指定格式显示本地时间。格式为`date +%Y:%m:%d`；其中的"%Y"指年份，“%m”指月份，“%d”指日，其中的":"为分割符，可以替换成其它符号，所以说可以以指定格式显示。除了"%Y %m %d"之外，date还有其它时间占位符。

%H : 小时
%M : 分钟
%S : 秒
%X : 相当于 %H:%M:%S
%d : 日 
%m : 月份
%Y : 年份 
%F : 相当于 %Y-%m-%d

```bash
[wind@starry-sky ~]$ date +%Y
2024
[wind@starry-sky ~]$ date +%Y/%m
2024/09
[wind@starry-sky ~]$ date +%Y/%m/%d
2024/09/23
[wind@starry-sky ~]$ date +%Y/%m/%d-%H:%M:%S
2024/09/23-15:06:35
[wind@starry-sky ~]$ date +%Y-%m-%d_%H/%M/%S
2024-09-23_15/07/15
[wind@starry-sky ~]$ 

```

  除了显示本地时间外，date还可以显示时间戳。时间戳是从格林威治时间1970年1月1日午夜12点开始所经过的秒数，它为计算机提供了一个统一的参考时间，地球上的不同地区有不同的本地时间，但时间戳是绝对唯一的。date查看时间戳的用法是`date +%s`；把时间戳转化为本地时间的语法是`date -d@时间戳`；默认为英语时间格式，可以指定格式做本地化适应。

```bash
[wind@starry-sky ~]$ date +%s
1727076076
[wind@starry-sky ~]$ date -d@1727076076
Mon Sep 23 15:21:16 CST 2024
[wind@starry-sky ~]$ date -d@1727076076
Mon Sep 23 15:21:16 CST 2024
[wind@starry-sky ~]$ date -d@1727076076 +%Y/%m/%d-%H:%M:%S
2024/09/23-15:21:16
[wind@starry-sky ~]$ date +%s
1727076328
[wind@starry-sky ~]$ date -d@0
Thu Jan  1 08:00:00 CST 1970
[wind@starry-sky ~]$ date -d@0 +%Y/%m/%d-%H:%M:%S
1970/01/01-08:00:00
[wind@starry-sky ~]$ 转化成的是本地时间，在这里，是北京时间，所以0是8点^C
[wind@starry-sky ~]$ 所以说，时间戳是唯一的，而各地有各自的时间^C
[wind@starry-sky ~]$ 

```

当然，时间戳作为一个变量是存在溢出可能的，但这不是我们要担心的。会有人解决的。

接下来是cal，cal指令其实没什么用，就是看日历的，带"-3"的选项表示查看前月本月下月的日历，"-j"显示今日为本年的第几日，"-y"显示今年所有月份的日历。

```bash
[wind@starry-sky ~]$ cal
   September 2024   
Su Mo Tu We Th Fr Sa
 1  2  3  4  5  6  7
 8  9 10 11 12 13 14
15 16 17 18 19 20 21
22 23 24 25 26 27 28
29 30

[wind@starry-sky ~]$ cal -3
     August 2024         September 2024         October 2024    
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa
             1  2  3   1  2  3  4  5  6  7         1  2  3  4  5
 4  5  6  7  8  9 10   8  9 10 11 12 13 14   6  7  8  9 10 11 12
11 12 13 14 15 16 17  15 16 17 18 19 20 21  13 14 15 16 17 18 19
18 19 20 21 22 23 24  22 23 24 25 26 27 28  20 21 22 23 24 25 26
25 26 27 28 29 30 31  29 30                 27 28 29 30 31      
                                                                
[wind@starry-sky ~]$ cal -y
                               2024                               

       January               February                 March       
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
    1  2  3  4  5  6                1  2  3                   1  2
 7  8  9 10 11 12 13    4  5  6  7  8  9 10    3  4  5  6  7  8  9
14 15 16 17 18 19 20   11 12 13 14 15 16 17   10 11 12 13 14 15 16
21 22 23 24 25 26 27   18 19 20 21 22 23 24   17 18 19 20 21 22 23
28 29 30 31            25 26 27 28 29         24 25 26 27 28 29 30
                                              31
        April                   May                   June        
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
    1  2  3  4  5  6             1  2  3  4                      1
 7  8  9 10 11 12 13    5  6  7  8  9 10 11    2  3  4  5  6  7  8
14 15 16 17 18 19 20   12 13 14 15 16 17 18    9 10 11 12 13 14 15
21 22 23 24 25 26 27   19 20 21 22 23 24 25   16 17 18 19 20 21 22
28 29 30               26 27 28 29 30 31      23 24 25 26 27 28 29
                                              30
        July                  August                September     
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
    1  2  3  4  5  6                1  2  3    1  2  3  4  5  6  7
 7  8  9 10 11 12 13    4  5  6  7  8  9 10    8  9 10 11 12 13 14
14 15 16 17 18 19 20   11 12 13 14 15 16 17   15 16 17 18 19 20 21
21 22 23 24 25 26 27   18 19 20 21 22 23 24   22 23 24 25 26 27 28
28 29 30 31            25 26 27 28 29 30 31   29 30

       October               November               December      
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
       1  2  3  4  5                   1  2    1  2  3  4  5  6  7
 6  7  8  9 10 11 12    3  4  5  6  7  8  9    8  9 10 11 12 13 14
13 14 15 16 17 18 19   10 11 12 13 14 15 16   15 16 17 18 19 20 21
20 21 22 23 24 25 26   17 18 19 20 21 22 23   22 23 24 25 26 27 28
27 28 29 30 31         24 25 26 27 28 29 30   29 30 31


[wind@starry-sky ~]$ cal -j
       September 2024      
Sun Mon Tue Wed Thu Fri Sat
245 246 247 248 249 250 251
252 253 254 255 256 257 258
259 260 261 262 263 264 265
266 267 268 269 270 271 272
273 274

[wind@starry-sky ~]$ cal 2025
                               2025                               

       January               February                 March       
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
          1  2  3  4                      1                      1
 5  6  7  8  9 10 11    2  3  4  5  6  7  8    2  3  4  5  6  7  8
12 13 14 15 16 17 18    9 10 11 12 13 14 15    9 10 11 12 13 14 15
19 20 21 22 23 24 25   16 17 18 19 20 21 22   16 17 18 19 20 21 22
26 27 28 29 30 31      23 24 25 26 27 28      23 24 25 26 27 28 29
                                              30 31
        April                   May                   June        
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
       1  2  3  4  5                1  2  3    1  2  3  4  5  6  7
 6  7  8  9 10 11 12    4  5  6  7  8  9 10    8  9 10 11 12 13 14
13 14 15 16 17 18 19   11 12 13 14 15 16 17   15 16 17 18 19 20 21
20 21 22 23 24 25 26   18 19 20 21 22 23 24   22 23 24 25 26 27 28
27 28 29 30            25 26 27 28 29 30 31   29 30

        July                  August                September     
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
       1  2  3  4  5                   1  2       1  2  3  4  5  6
 6  7  8  9 10 11 12    3  4  5  6  7  8  9    7  8  9 10 11 12 13
13 14 15 16 17 18 19   10 11 12 13 14 15 16   14 15 16 17 18 19 20
20 21 22 23 24 25 26   17 18 19 20 21 22 23   21 22 23 24 25 26 27
27 28 29 30 31         24 25 26 27 28 29 30   28 29 30
                       31
       October               November               December      
Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa   Su Mo Tu We Th Fr Sa
          1  2  3  4                      1       1  2  3  4  5  6
 5  6  7  8  9 10 11    2  3  4  5  6  7  8    7  8  9 10 11 12 13
12 13 14 15 16 17 18    9 10 11 12 13 14 15   14 15 16 17 18 19 20
19 20 21 22 23 24 25   16 17 18 19 20 21 22   21 22 23 24 25 26 27
26 27 28 29 30 31      23 24 25 26 27 28 29   28 29 30 31
                       30

[wind@starry-sky ~]$ 

```

--------

下面是Linux中一个很重要的指令find。find指令有很多选项，顾名思义，它是用来找文件的。find的选项太多了，这里我们只说一种用法。find可以在指定路径下查找指定文件，格式为`find 路径 -name 文件名`

```bash
[wind@starry-sky ~]$ find ~ -name *.txt
/home/wind/study/sour.txt
/home/wind/sour.txt

```

使用find要注意账号权限，有些路径普通用户无法查找。权限不足。

```bash
[wind@starry-sky ~]$ find /root -name *.txt
find: ‘/root’: Permission denied
[wind@starry-sky ~]$ 

```

相比之下，which的路径是定死的，就是指令目录。除此之外还有一个叫whereis的指令，是在系统特殊路径，比如指令路径，手册路径，头文件路径什么的。

```bash
[wind@starry-sky ~]$ whereis stdlib.h
stdlib: /usr/include/stdlib.h
[wind@starry-sky ~]$ 

```

-------

下面介绍grep指令，grep可以在文件中寻找指定字符串，并把符合要求的行打印出来，它是一个行文本过滤工具。

```bash
[wind@starry-sky ~]$ clear
[wind@starry-sky ~]$ ll
total 12
drwxrwxr-x 3 wind wind 4096 Sep 19 21:57 d
-rw-rw-r-- 1 wind wind   12 Sep 19 20:59 sour.txt
drwxrwxr-x 2 wind wind 4096 Sep 20 16:52 study
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ ll
total 176
-rw-rw-r-- 1 wind wind     24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind 168894 Sep 20 15:10 newf.txt
-rw-rw-r-- 1 wind wind    357 Sep 20 16:52 report.txt
-rw-rw-r-- 1 wind wind      0 Sep 20 12:31 sour.txt
[wind@starry-sky study]$ grep '921' newf.txt
hello Linux 921
hello Linux 1921
hello Linux 2921
hello Linux 3921
hello Linux 4921
hello Linux 5921
hello Linux 6921
hello Linux 7921
hello Linux 8921
hello Linux 9210
hello Linux 9211
hello Linux 9212
hello Linux 9213
hello Linux 9214
hello Linux 9215
hello Linux 9216
hello Linux 9217
hello Linux 9218
hello Linux 9219
hello Linux 9921
[wind@starry-sky study]$ 只有包含"921"的行才会被打印出来^C
[wind@starry-sky study]$ 为了方面实验，现在对newf.txt覆写些新内容^C
[wind@starry-sky study]$ > newf.txt
[wind@starry-sky study]$ ll
total 8
-rw-rw-r-- 1 wind wind  24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind   0 Sep 23 17:12 newf.txt
-rw-rw-r-- 1 wind wind 357 Sep 20 16:52 report.txt
-rw-rw-r-- 1 wind wind   0 Sep 20 12:31 sour.txt
[wind@starry-sky study]$ echo "hello world" >> newf.txt
[wind@starry-sky study]$ echo "hello Linux" >> newf.txt
[wind@starry-sky study]$ echo "welcom to wind" >> newf.txt
[wind@starry-sky study]$ echo "hello WorLD" >> newf.txt
[wind@starry-sky study]$ echo "" >> newf.txt
[wind@starry-sky study]$ echo "hello LINUX" >> newf.txt
[wind@starry-sky study]$ echo "12345678" >> newf.txt
[wind@starry-sky study]$ cat newf.txt
hello world
hello Linux
welcom to wind
hello WorLD

hello LINUX
12345678
[wind@starry-sky study]$ grep "world" newf.txt
hello world
[wind@starry-sky study]$ 带上"-v"选项反向筛选^C
[wind@starry-sky study]$ grep -v "world" newf.txt
hello Linux
welcom to wind
hello WorLD

hello LINUX
12345678
[wind@starry-sky study]$ 带上"-n"选项打印行号^C
[wind@starry-sky study]$ grep -vn "world" newf.txt
2:hello Linux
3:welcom to wind
4:hello WorLD
5:
6:hello LINUX
7:12345678
[wind@starry-sky study]$ cat -n newf.txt
     1	hello world
     2	hello Linux
     3	welcom to wind
     4	hello WorLD
     5	
     6	hello LINUX
     7	12345678
[wind@starry-sky study]$ 空字符则全部选中^C
[wind@starry-sky study]$ grep -n "" newf.txt
1:hello world
2:hello Linux
3:welcom to wind
4:hello WorLD
5:
6:hello LINUX
7:12345678
[wind@starry-sky study]$ 选项"-i"忽略大小写^C
[wind@starry-sky study]$ grep -n "world" newf.txt
1:hello world
[wind@starry-sky study]$ grep -ni "world" newf.txt
1:hello world
4:hello WorLD
[wind@starry-sky study]$ grep -ni "linux" newf.txt
2:hello Linux
6:hello LINUX
[wind@starry-sky study]$ cat newf.txt | grep -ni "linux"
2:hello Linux
6:hello LINUX
[wind@starry-sky study]$ 另外，grep也是可以对路径进行筛选，不过要加"-R"选项^C
[wind@starry-sky study]$ 此时它会把该路径下的所有携带指定字符串的文件中的满足行号显示出来，我这里没什么文件，就不做示例了^C
[wind@starry-sky study]$ 

```

------

下面我们谈谈Linux中的打包压缩操作，Linux支持的压缩格式非常多，这里只说一两个。

```bash
[wind@starry-sky study]$ 为什么计算机要进行打包和压缩呢？^C
[wind@starry-sky study]$ 打包是为了让多个文件变为一个文件^C
[wind@starry-sky study]$ 这可以减少文件缺失的可能^C
[wind@starry-sky study]$ 如果一个项目有很多文件，结果传输过后，偏偏少一个文件，那就不好了^C
[wind@starry-sky study]$ 压缩可以让文件存储空间变小^C
[wind@starry-sky study]$ 这样进行传输的时候就能少等一会时间，也能减少服务器的存储开销^C
[wind@starry-sky study]$ 我们先介绍Linux下的zip压缩，因为zip在windows里常见，方便服务器与windows交流^C
[wind@starry-sky study]$ 然后再介绍tar,它是Linux里的主流打包压缩指令^C
[wind@starry-sky study]$ 我先创建一个子树，用来做实验材料^C
[wind@starry-sky study]$ pwd
/home/wind/study
[wind@starry-sky study]$ ll
total 12
-rw-rw-r-- 1 wind wind  24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind  73 Sep 23 17:17 newf.txt
-rw-rw-r-- 1 wind wind 357 Sep 20 16:52 report.txt
-rw-rw-r-- 1 wind wind   0 Sep 20 12:31 sour.txt
[wind@starry-sky study]$ mkdir -r d1/d2/d3/d4
mkdir: invalid option -- 'r'
Try 'mkdir --help' for more information.
[wind@starry-sky study]$ mkdir -p d1/d2/d3/d4
[wind@starry-sky study]$ tree .
.
├── d1
│   └── d2
│       └── d3
│           └── d4
├── dest.txt
├── newf.txt
├── report.txt
└── sour.txt

4 directories, 4 files
[wind@starry-sky study]$ ll
total 16
drwxrwxr-x 3 wind wind 4096 Sep 23 18:05 d1
-rw-rw-r-- 1 wind wind   24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind   73 Sep 23 17:17 newf.txt
-rw-rw-r-- 1 wind wind  357 Sep 20 16:52 report.txt
-rw-rw-r-- 1 wind wind    0 Sep 20 12:31 sour.txt
[wind@starry-sky study]$ cp report.txt ./d1/d2/f1.txt
[wind@starry-sky study]$ cd d1
[wind@starry-sky d1]$ touch f2.txt
[wind@starry-sky d1]$ cd d2/d3
[wind@starry-sky d3]$ touch f3.txt
[wind@starry-sky d3]$ cd ~
[wind@starry-sky ~]$ ll
total 12
drwxrwxr-x 3 wind wind 4096 Sep 19 21:57 d
-rw-rw-r-- 1 wind wind   12 Sep 19 20:59 sour.txt
drwxrwxr-x 3 wind wind 4096 Sep 23 18:05 study
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ ls
d1  dest.txt  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ tree .
.
├── d1
│   ├── d2
│   │   ├── d3
│   │   │   ├── d4
│   │   │   └── f3.txt
│   │   └── f1.txt
│   └── f2.txt
├── dest.txt
├── newf.txt
├── report.txt
└── sour.txt

4 directories, 7 files
[wind@starry-sky study]$ cat ./d1/d2/f1.txt
hello Linux 5000
hello Linux 5001
hello Linux 5002
hello Linux 5003
hello Linux 5004
hello Linux 5005
hello Linux 5006
hello Linux 5007
hello Linux 5008
hello Linux 5009
hello Linux 5010
hello Linux 5011
hello Linux 5012
hello Linux 5013
hello Linux 5014
hello Linux 5015
hello Linux 5016
hello Linux 5017
hello Linux 5018
hello Linux 5019
hello Linux 5020
[wind@starry-sky study]$ zip --version
Copyright (c) 1990-2008 Info-ZIP - Type 'zip "-L"' for software license.
This is Zip 3.0 (July 5th 2008), by Info-ZIP.
Currently maintained by E. Gordon.  Please send bug reports to
the authors using the web page at www.info-zip.org; see README for details.

Latest sources and executables are at ftp://ftp.info-zip.org/pub/infozip,
as of above date; see http://www.info-zip.org/ for other sites.

Compiled with gcc 4.8.5 20150623 (Red Hat 4.8.5-11) for Unix (Linux ELF) on Nov  5 2016.

Zip special compilation options:
	USE_EF_UT_TIME       (store Universal Time)
	BZIP2_SUPPORT        (bzip2 library version 1.0.6, 6-Sept-2010)
	    bzip2 code and library copyright (c) Julian R Seward
	    (See the bzip2 license for terms of use)
	SYMLINK_SUPPORT      (symbolic links supported)
	LARGE_FILE_SUPPORT   (can read and write large files on file system)
	ZIP64_SUPPORT        (use Zip64 to store large files in archives)
	UNICODE_SUPPORT      (store and read UTF-8 Unicode paths)
	STORE_UNIX_UIDs_GIDs (store UID/GID sizes/values using new extra field)
	UIDGID_NOT_16BIT     (old Unix 16-bit UID/GID extra field not used)
	[encryption, version 2.91 of 05 Jan 2007] (modified for Zip 3)

Encryption notice:
	The encryption code of this program is not copyrighted and is
	put in the public domain.  It was originally written in Europe
	and, to the best of our knowledge, can be freely distributed
	in both source and object forms from any country, including
	the USA under License Exception TSU of the U.S. Export
	Administration Regulations (section 740.13(e)) of 6 June 2002.

Zip environment options:
             ZIP:  [none]
          ZIPOPT:  [none]
[wind@starry-sky study]$ 好的，看样子这个系统上是有zip的^C
[wind@starry-sky study]$ 对路径进行压缩需要带上选项"-r"^C
[wind@starry-sky study]$ ls
d1  dest.txt  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ zip -r d1.zip d1
  adding: d1/ (stored 0%)
  adding: d1/d2/ (stored 0%)
  adding: d1/d2/f1.txt (deflated 79%)
  adding: d1/d2/d3/ (stored 0%)
  adding: d1/d2/d3/f3.txt (stored 0%)
  adding: d1/d2/d3/d4/ (stored 0%)
  adding: d1/f2.txt (stored 0%)
[wind@starry-sky study]$ ls
d1  d1.zip  dest.txt  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ mv d1.zip ..
[wind@starry-sky study]$ cd ..
[wind@starry-sky ~]$ ls
d  d1.zip  sour.txt  study
[wind@starry-sky ~]$ tree d
d
└── d2
    └── d3

2 directories, 0 files
[wind@starry-sky ~]$ rm -rf d
[wind@starry-sky ~]$ 接下来是解压缩^C
[wind@starry-sky ~]$ unzip d1.zip
-bash: unzip: command not found
[wind@starry-sky ~]$ ls
d1.zip  sour.txt  study
[wind@starry-sky ~]$ unzip d1.zip
-bash: unzip: command not found
[wind@starry-sky ~]$ which unzip
/usr/bin/which: no unzip in (/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/wind/.local/bin:/home/wind/bin)
[wind@starry-sky ~]$ which zip
/usr/bin/zip
[wind@starry-sky ~]$ 好的，没有unzip,看来要安装一下^C
[wind@starry-sky ~]$ 我们换回rott账号，安装一下^C
[wind@starry-sky ~]$ 哦，是root,打错了^C
[wind@starry-sky ~]$ su -root
su: invalid option -- 'r'

Usage:
 su [options] [-] [USER [arg]...]

Change the effective user id and group id to that of USER.
A mere - implies -l.   If USER not given, assume root.

Options:
 -m, -p, --preserve-environment  do not reset environment variables
 -g, --group <group>             specify the primary group
 -G, --supp-group <group>        specify a supplemental group

 -, -l, --login                  make the shell a login shell
 -c, --command <command>         pass a single command to the shell with -c
 --session-command <command>     pass a single command to the shell with -c
                                 and do not create a new session
 -f, --fast                      pass -f to the shell (for csh or tcsh)
 -s, --shell <shell>             run shell if /etc/shells allows it

 -h, --help     display this help and exit
 -V, --version  output version information and exit

For more details see su(1).
[wind@starry-sky ~]$ su
Password: 
[root@starry-sky wind]# 直接输入su回车后输root密码^C
[root@starry-sky wind]# yum install zip unzip
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Package zip-3.0-11.el7.x86_64 already installed and latest version
Resolving Dependencies
--> Running transaction check
---> Package unzip.x86_64 0:6.0-24.el7_9 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

=============================================================================================================================================
 Package                        Arch                            Version                               Repository                        Size
=============================================================================================================================================
Installing:
 unzip                          x86_64                          6.0-24.el7_9                          updates                          172 k

Transaction Summary
=============================================================================================================================================
Install  1 Package

Total download size: 172 k
Installed size: 369 k
Is this ok [y/d/N]: y
Downloading packages:
unzip-6.0-24.el7_9.x86_64.rpm                                                                                         | 172 kB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : unzip-6.0-24.el7_9.x86_64                                                                                                 1/1 
  Verifying  : unzip-6.0-24.el7_9.x86_64                                                                                                 1/1 

Installed:
  unzip.x86_64 0:6.0-24.el7_9                                                                                                                

Complete!
[root@starry-sky wind]# which unzip
/usr/bin/unzip
[root@starry-sky wind]# OK,好的，安装上了，切回普通账号^C
[root@starry-sky wind]# su wind
[wind@starry-sky ~]$ ls
d1.zip  sour.txt  study
[wind@starry-sky ~]$ unzip d1.zip
Archive:  d1.zip
   creating: d1/
   creating: d1/d2/
  inflating: d1/d2/f1.txt            
   creating: d1/d2/d3/
 extracting: d1/d2/d3/f3.txt         
   creating: d1/d2/d3/d4/
 extracting: d1/f2.txt               
[wind@starry-sky ~]$ ls
d1  d1.zip  sour.txt  study
[wind@starry-sky ~]$ tree d1
d1
├── d2
│   ├── d3
│   │   ├── d4
│   │   └── f3.txt
│   └── f1.txt
└── f2.txt

3 directories, 3 files
[wind@starry-sky ~]$ cat ./d1/d2/f1.txt
hello Linux 5000
hello Linux 5001
hello Linux 5002
hello Linux 5003
hello Linux 5004
hello Linux 5005
hello Linux 5006
hello Linux 5007
hello Linux 5008
hello Linux 5009
hello Linux 5010
hello Linux 5011
hello Linux 5012
hello Linux 5013
hello Linux 5014
hello Linux 5015
hello Linux 5016
hello Linux 5017
hello Linux 5018
hello Linux 5019
hello Linux 5020
[wind@starry-sky ~]$ 没问题，没丢东西。^C
[wind@starry-sky ~]$ rm d1.zip
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ ls
d1  dest.txt  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ 也可以路径文件一块打包压缩^C
[wind@starry-sky study]$ zip -r d.zip d1 dest.txt
  adding: d1/ (stored 0%)
  adding: d1/d2/ (stored 0%)
  adding: d1/d2/f1.txt (deflated 79%)
  adding: d1/d2/d3/ (stored 0%)
  adding: d1/d2/d3/f3.txt (stored 0%)
  adding: d1/d2/d3/d4/ (stored 0%)
  adding: d1/f2.txt (stored 0%)
  adding: dest.txt (deflated 8%)
[wind@starry-sky study]$ ls
d1  dest.txt  d.zip  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ rm -rf d1
[wind@starry-sky study]$ rm -f dest.txt
[wind@starry-sky study]$ ls
d.zip  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ unzip d.zip
Archive:  d.zip
   creating: d1/
   creating: d1/d2/
  inflating: d1/d2/f1.txt            
   creating: d1/d2/d3/
 extracting: d1/d2/d3/f3.txt         
   creating: d1/d2/d3/d4/
 extracting: d1/f2.txt               
  inflating: dest.txt                
[wind@starry-sky study]$ ls
d1  dest.txt  d.zip  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ mkdir test
[wind@starry-sky study]$ ls
d1  dest.txt  d.zip  newf.txt  report.txt  sour.txt  test
[wind@starry-sky study]$ 也可以解压到指定路径下^C
[wind@starry-sky study]$ unzip d.zip -d ./test
Archive:  d.zip
   creating: ./test/d1/
   creating: ./test/d1/d2/
  inflating: ./test/d1/d2/f1.txt     
   creating: ./test/d1/d2/d3/
 extracting: ./test/d1/d2/d3/f3.txt  
   creating: ./test/d1/d2/d3/d4/
 extracting: ./test/d1/f2.txt        
  inflating: ./test/dest.txt         
[wind@starry-sky study]$ tree ./test
./test
├── d1
│   ├── d2
│   │   ├── d3
│   │   │   ├── d4
│   │   │   └── f3.txt
│   │   └── f1.txt
│   └── f2.txt
└── dest.txt

4 directories, 4 files
[wind@starry-sky study]$ rm -rf test
[wind@starry-sky study]$ rm d.zip
[wind@starry-sky study]$ cd ..
[wind@starry-sky ~]$ ls
d1  sour.txt  study
[wind@starry-sky ~]$ tree d1
d1
├── d2
│   ├── d3
│   │   ├── d4
│   │   └── f3.txt
│   └── f1.txt
└── f2.txt

3 directories, 3 files
[wind@starry-sky ~]$ rm -rf d1
[wind@starry-sky ~]$ ll
total 8
-rw-rw-r-- 1 wind wind   12 Sep 19 20:59 sour.txt
drwxrwxr-x 3 wind wind 4096 Sep 23 18:34 study
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ ls
d1  dest.txt  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ ll
total 16
drwxrwxr-x 3 wind wind 4096 Sep 23 18:10 d1
-rw-rw-r-- 1 wind wind   24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind   73 Sep 23 17:17 newf.txt
-rw-rw-r-- 1 wind wind  357 Sep 20 16:52 report.txt
-rw-rw-r-- 1 wind wind    0 Sep 20 12:31 sour.txt
[wind@starry-sky study]$ 

```

下面说tar指令

```bas
[wind@starry-sky study]$ tar选项也挺多的，这里我一套一道地说，如果对压缩格式有特殊需求，去网上搜一下，带系统名去搜，比如我是CentOS^C
[wind@starry-sky study]$ tar czf^C
[wind@starry-sky study]$ c指创建，创建打包后的那一个文件；z以zip格式压缩；f命名压缩后的文件名^C
[wind@starry-sky study]$ tar压缩路径不用再带-r^C
[wind@starry-sky study]$ tar -czf d.tar.gz^C
[wind@starry-sky study]$ 算了，省略一下^C
[wind@starry-sky study]$ tar -czf d.tgz d1 dest.txt sour.txt
[wind@starry-sky study]$ ls
d1  dest.txt  d.tgz  newf.txt  report.txt  sour.txt
[wind@starry-sky study]$ mkdir test
[wind@starry-sky study]$ ls
d1  dest.txt  d.tgz  newf.txt  report.txt  sour.txt  test
[wind@starry-sky study]$ -t选项，预览压缩包里的文件，具体内容看不到^C
[wind@starry-sky study]$ 有些系统对于该指令似乎不支持选项前加"-"，可以把"-"去掉后再试一试^C
[wind@starry-sky study]$ tar -t d.tgz
^C
[wind@starry-sky study]$ tar -tzf d.tgz
d1/
d1/d2/
d1/d2/f1.txt
d1/d2/d3/
d1/d2/d3/f3.txt
d1/d2/d3/d4/
d1/f2.txt
dest.txt
sour.txt
[wind@starry-sky study]$ 解压缩格式：tar -xzf 压缩文件名^C
[wind@starry-sky study]$ x:解压缩，z:zip格式，f：后面接压缩文件名^C
[wind@starry-sky study]$ -C：解压到指定路径下^C
[wind@starry-sky study]$ tar -xzfC d.tgz test
tar (child): C: Cannot open: No such file or directory
tar (child): Error is not recoverable: exiting now
tar: Child returned status 2
tar: Error is not recoverable: exiting now
[wind@starry-sky study]$ ls test
[wind@starry-sky study]$ tar -xzf d.tgz -C ./test
[wind@starry-sky study]$ ls test
d1  dest.txt  sour.txt
[wind@starry-sky study]$ tree test
test
├── d1
│   ├── d2
│   │   ├── d3
│   │   │   ├── d4
│   │   │   └── f3.txt
│   │   └── f1.txt
│   └── f2.txt
├── dest.txt
└── sour.txt

4 directories, 5 files
[wind@starry-sky study]$ 好的，第二次解压缩成功了^C
[wind@starry-sky study]$ teee .
bash: teee: command not found
[wind@starry-sky study]$ 

```

-----

bc指令，bc就是Linux的计算器，和Windows上的图形化计算器都是一样的。

```bash
[wind@starry-sky study]$ bc怎么用呢？^C
[wind@starry-sky study]$ 可以直接用，键入bc之后回车^C
[wind@starry-sky study]$ bc
bc 1.06.95
Copyright 1991-1994, 1997, 1998, 2000, 2004, 2006 Free Software Foundation, Inc.
This is free software with ABSOLUTELY NO WARRANTY.
For details type `warranty'. 
10 + 3
13
3.14 * 7
21.98
7 + 4
11
quit
[wind@starry-sky study]$ 输入quit回车后就可以退出了^C
[wind@starry-sky study]$ 不过实际上一般不这样用^C
[wind@starry-sky study]$ 一般把bc和管道文件结合^C
[wind@starry-sky study]$ echo "1+2+3" | bc
6
[wind@starry-sky study]$ echo "3.14*7" | bc
21.98
[wind@starry-sky study]$ echo "10/3" | bc
3
[wind@starry-sky study]$ bc好像也可以调一下精度，这样10/3就不是3了，但这里就不说了，计算器而已，大不了自己写一个程序^C
[wind@starry-sky study]$ 

```

------------

指令uname可以查看系统版本，电脑硬件相关信息。

a或–all 详细输出所有信息，依次为内核名称，主机名，内核版本号，内核版本，硬件名，处理器类型，硬件平台类型，操作系统名称  

![image-20240923202044129](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409232020364.png)

-----------

热键Tab，具有命令补全和档案补全功能

```bash
[wind@starry-sky study]$ 比如，输入“wh”之后，按两下Tab键^C
[wind@starry-sky study]$ wh
whatis    whereis   which     while     whiptail  who       whoami   
[wind@starry-sky study]$ 输入“whic”之后，再按一下Tab^C
[wind@starry-sky study]$ which ^C
[wind@starry-sky study]$ 他就可以自动补全指令^C
[wind@starry-sky study]$ 

```

热键ctrl+r，可以查询历史指令

```bash
(reverse-i-search)`tar': ^Cr -xzf d.tgz -C ./test
(reverse-i-search)`which': ^Cich pwd
[wind@starry-sky study]$ 键入Ctrl+R回车，就会出现(reverse-i-search)，然后你输指令就行，它会根据你的输入去查询最近1000多个历史指令^C
[wind@starry-sky study]$ 为什么是1000多个呢？因为再往前的已经被覆写掉了，Linux只保存最近的1000多行历史指令，不过有的只有500行^C
[wind@starry-sky study]$ 

```

指令histroy可以查询最近的历史指令，到底展示多少行视具体情况来定。

热键Ctrl+d可以退出xshell，第一次按下是退出当前账号，第二次是退出xshell本身。

------

```bash
[wind@starry-sky ~]$ 接下来我们了解一下Linux中的记事本——nano^C
[wind@starry-sky ~]$ 和Windows里的记事本一样，我们以后很少使用nano，所以说了解^C
[wind@starry-sky ~]$ 在使用nano之前，我们要先看看系统里到底有没有nano^C
[wind@starry-sky ~]$ which nano
/usr/bin/which: no nano in (/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/wind/.local/bin:/home/wind/bin)
[wind@starry-sky ~]$ 看来没有，那就安装一下吧^C
[wind@starry-sky ~]$ su -
Password: 
su: Authentication failure
[wind@starry-sky ~]$ su -
Password: 
Last login: Mon Sep 23 18:24:39 CST 2024 on pts/0
Last failed login: Mon Sep 23 21:01:36 CST 2024 on pts/0
There was 1 failed login attempt since the last successful login.
[root@starry-sky ~]# sudo yum install nano
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Resolving Dependencies
--> Running transaction check
---> Package nano.x86_64 0:2.3.1-10.el7 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

=============================================================================================================================================
 Package                        Arch                             Version                                Repository                      Size
=============================================================================================================================================
Installing:
 nano                           x86_64                           2.3.1-10.el7                           base                           440 k

Transaction Summary
=============================================================================================================================================
Install  1 Package

Total download size: 440 k
Installed size: 1.6 M
Is this ok [y/d/N]: y
Downloading packages:
nano-2.3.1-10.el7.x86_64.rpm                                                                                          | 440 kB  00:00:00     
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : nano-2.3.1-10.el7.x86_64                                                                                                  1/1 
  Verifying  : nano-2.3.1-10.el7.x86_64                                                                                                  1/1 

Installed:
  nano.x86_64 0:2.3.1-10.el7                                                                                                                 

Complete!
[root@starry-sky ~]# which nano
/bin/nano
[root@starry-sky ~]# 装好了^C
[root@starry-sky ~]# su wind
[wind@starry-sky root]$ 现在我们来用一下^C
[wind@starry-sky root]$ cd ~
[wind@starry-sky ~]$ cd study
[wind@starry-sky study]$ ll
total 24
drwxrwxr-x 3 wind wind 4096 Sep 23 18:10 d1
-rw-rw-r-- 1 wind wind   24 Sep 20 12:23 dest.txt
-rw-rw-r-- 1 wind wind  361 Sep 23 18:52 d.tgz
-rw-rw-r-- 1 wind wind   73 Sep 23 17:17 newf.txt
-rw-rw-r-- 1 wind wind  357 Sep 20 16:52 report.txt
-rw-rw-r-- 1 wind wind    0 Sep 20 12:31 sour.txt
drwxrwxr-x 3 wind wind 4096 Sep 23 19:13 test
[wind@starry-sky study]$ cd test
[wind@starry-sky test]$ ls
d1  dest.txt  sour.txt
[wind@starry-sky test]$ rm -rf d1 dest.txt 
[wind@starry-sky test]$ ls
sour.txt
[wind@starry-sky test]$ ll
total 0
-rw-rw-r-- 1 wind wind 0 Sep 20 12:31 sour.txt
[wind@starry-sky test]$ cat sour.txt
[wind@starry-sky test]$ mv sour.txt test.c
[wind@starry-sky test]$ ls
test.c
[wind@starry-sky test]$ nano test.c
[wind@starry-sky test]$ 代码写好之后，输入ctrl+x,输入y保存，回车退出^C
[wind@starry-sky test]$ cat test.c
#include<stdio.h>

int main()
{
//记事本就不要那么讲究了
//Ctrl+x保存并退出
 peintf("hello nano/n");return 0;
}
[wind@starry-sky test]$ 使用gcc编译一下^C
[wind@starry-sky test]$ gcc test.c
/tmp/ccWSLLNN.o: In function `main':
test.c:(.text+0xf): undefined reference to `peintf'
collect2: error: ld returned 1 exit status
[wind@starry-sky test]$ 敲错了，改一下^C
[wind@starry-sky test]$ nano test.c
[wind@starry-sky test]$ cat test.c
#include<stdio.h>

int main()
{
//记事本就不要那么讲究了
//Ctrl+x保存并退出
 printf("hello nano/n");return 0;
}
[wind@starry-sky test]$ gcc test.c
[wind@starry-sky test]$ ls
a.out  test.c
[wind@starry-sky test]$ 执行一下^C
[wind@starry-sky test]$ ./a.out
hello nano/n[wind@starry-sky test]$ 诶呀，换行符也敲错了，算了，就这样了^C
[wind@starry-sky test]$ 

```

-----------

下面我们大致说一说Linux里的指令是怎么运行的。Linux里的指令和其它操作系统，比如说安卓，苹果，Windows的图形化界面其实都发挥同样的功能：作为用户和操作系统沟通的桥梁，对于一般人来说，直接操作操作系统实在是太难了，所以就有了命令行解释器和图形化界面这类中间角色，它们将用户的需求翻译成具体的命令，通过调用系统提供的一系列接口完成特定的需求，然后再把操作系统的反馈翻译成用户能够理解的信息；除此之外，这类中间角色还可以避免用户直接对系统进行操作，从而变相的保护系统本身，当用户提出了危害系统的需求时，中间角色可以直接拦截用户需求，从而保护系统的正常运行。有点面向对象的感觉。

`shell`是对命令行解释器的统称，而`bash sh`则是具体的命令行解释器，在Linux里，这三个概念都可以认为是指代命令行解释器。

我们说的Linux，一般不是光指Linux本身，而是指包括Linux操作系统本身及基于Linux的各种软件。

# 完

