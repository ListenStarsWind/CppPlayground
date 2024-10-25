#include<vector>
#include<string>
#include<string.h>

using namespace std;

class Solution {
    const char* map[10] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
public:
    void combine(vector<string>& finishingPoint, const string& digits, string putTogether = string(), int digitsAccess = 0) {
        if (digitsAccess == digits.size())
        {
            finishingPoint.push_back(putTogether);
            return;
        }
        string tmp = map[digits[digitsAccess] - '0'];
        for (auto e : tmp)
        {
            combine(finishingPoint, digits, putTogether + e, digitsAccess + 1);
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> v;
        if (digits.empty())
            return v;
        combine(v, digits);
        return v;
    }
};


// https://leetcode.cn/problems/letter-combinations-of-a-phone-number
int main()
{
    string s("23");
    Solution().letterCombinations(s);
    return 0;
}

// 下面以"23"为例文字说一下函数栈帧

/*

首先进入表函数letterCombinations，首先创建了一个空的字符串容器v，作为返回值
接着判断输入的数字字符是否为空，若为空，则v应以空的状态返回
接着进入里函数，里函数是一个递归函数，它将以递归的方式遍历排列的种种可能
里函数有两个缺省参数：putTogether and digitsAccess， digitsAccess将是里函数
访问数字字符串的方式，putTogether则负责拼接字符，并最终把结果拼接到v里，由于
v只在终止条件里才被访问，所以，我将它叫做终点finishingPoint
里函数将通过映射数组与数字所指代的字符串建立关系，并把读取到的字符放在局部string
对象 tmp中，随后对tmp进行遍历，由此得到种种可能

首先"23"的第0位被访问，读到数字2，于是有了字符串"abc"，很明显它将经过三次for循环以
遍历全部元素

第一层里函数栈帧的第一次for循环
选中元素'a'，并以加的形式进入第二层栈帧
注意这里用的是"+"，所以该层的putTogether仍就为空

第二层函数栈帧
首先依据数字3,选中字符串"def"，很明显，它会有三次for循环
为方便描述，我们下面对函数栈帧的定位使用[x,y]形式
比如第二层函数栈帧的第一层for循环位于[2,1]

[2,1]
此时的putTogether为"a"，选中字符'd'，进入第三层栈帧

[3,1]
触发终止条件，字符"ad"被录入finishingPoint
返回

[2,2]
此时的putTogether为"a"，选中字符'e'，进入第三层栈帧

[3,1]
触发终止条件，字符"ae"被录入finishingPoint
返回

[2,3]
此时的putTogether为"a"，选中字符'f'，进入第三层栈帧

[3,1]
触发终止条件，字符"af"被录入finishingPoint
返回

第二层函数栈帧全部执行完成，返回

[1,2]
此时的putTogether为""，选中字符'b'，进入第二层栈帧

[2,1]
此时的putTogether为"b"，选中字符'd'，进入第三层栈帧

[3,1]
触发终止条件，字符"bd"被录入finishingPoint
返回

[2,2]
此时的putTogether为"b"，选中字符'e'，进入第三层栈帧

[3,1]
触发终止条件，字符"be"被录入finishingPoint
返回

[2,3]
此时的putTogether为"b"，选中字符'f'，进入第三层栈帧

[3,1]
触发终止条件，字符"bf"被录入finishingPoint
返回

第二层函数栈帧全部执行完成，返回

[1,2]
此时的putTogether为""，选中字符'c'，进入第二层栈帧

[2,1]
此时的putTogether为"c"，选中字符'd'，进入第三层栈帧

[3,1]
触发终止条件，字符"cd"被录入finishingPoint
返回

[2,2]
此时的putTogether为"c"，选中字符'e'，进入第三层栈帧

[3,1]
触发终止条件，字符"ce"被录入finishingPoint
返回

[2,3]
此时的putTogether为"c"，选中字符'f'，进入第三层栈帧

[3,1]
触发终止条件，字符"cf"被录入finishingPoint
返回

第二层函数栈帧全部执行完成，返回

第一层函数栈帧全部执行完毕，返回

里函数全部执行完毕，返回

表函数v已收录全部可能，返回


*/