# [用两个队列实现栈](https://leetcode.cn/problems/implement-stack-using-queues/description/)

![image-20240812141155694](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408121411027.png)

这个题目很奇怪。可能是纯粹为了加深对栈和队列的理解而存在的，似乎没有什么实际应用场景。

思路是什么呢？入栈就是入队，出栈就是先把队里的除去最后一个的节点全弹到另一个队里，然后再去读最后一个节点。

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408121448429.mp4"></video>

代码规模较大，细节要小心。