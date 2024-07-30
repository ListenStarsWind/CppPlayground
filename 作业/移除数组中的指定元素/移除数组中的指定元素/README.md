# [移除数组中的指定元素](https://leetcode.cn/problems/remove-element/)

![image-20240730110132344](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407301101543.png)

之前也写过了，我不知道什么时候写的，不过这个很简单。还是用快慢指针，`scr`遍历数组，去找不等于`val`的元素，找到了就把这个元素copy到`dest`，然后两个一起++。
