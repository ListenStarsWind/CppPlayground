# [找两个单身狗](https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/description/)

![image-20240918145235156](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409181452455.png)

这我真的没什么思路。所以我打算看看评论

然后从题解里挖出了[这篇文章](https://blog.csdn.net/m0_46202073/article/details/119539633?fromshare=blogdetail&sharetype=blogdetail&sharerId=119539633&sharerefer=PC&sharesource=venti0411&sharefrom=from_link)虽说是用C++写的，但作者对思路做了详细说明，所以写出来了。

思路就是依据两位单身狗的不同，把它们分到两个数组里，然后分别在这两个数组里找单身狗就行了。如何找到它们的不同呢？将所有成员都异或一下，得到的结果就是那两个单身狗结合的产物，由于异或是相同为0，不同为1.所以就可以知道它们两个哪一位是不同的。



