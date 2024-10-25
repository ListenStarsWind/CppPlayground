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

// ������"23"Ϊ������˵һ�º���ջ֡

/*

���Ƚ������letterCombinations�����ȴ�����һ���յ��ַ�������v����Ϊ����ֵ
�����ж�����������ַ��Ƿ�Ϊ�գ���Ϊ�գ���vӦ�Կյ�״̬����
���Ž����ﺯ�����ﺯ����һ���ݹ麯���������Եݹ�ķ�ʽ�������е����ֿ���
�ﺯ��������ȱʡ������putTogether and digitsAccess�� digitsAccess�����ﺯ��
���������ַ����ķ�ʽ��putTogether����ƴ���ַ��������հѽ��ƴ�ӵ�v�����
vֻ����ֹ������ű����ʣ����ԣ��ҽ��������յ�finishingPoint
�ﺯ����ͨ��ӳ��������������ָ�����ַ���������ϵ�����Ѷ�ȡ�����ַ����ھֲ�string
���� tmp�У�����tmp���б������ɴ˵õ����ֿ���

����"23"�ĵ�0λ�����ʣ���������2�����������ַ���"abc"��������������������forѭ����
����ȫ��Ԫ��

��һ���ﺯ��ջ֡�ĵ�һ��forѭ��
ѡ��Ԫ��'a'�����Լӵ���ʽ����ڶ���ջ֡
ע�������õ���"+"�����Ըò��putTogether�Ծ�Ϊ��

�ڶ��㺯��ջ֡
������������3,ѡ���ַ���"def"�������ԣ�����������forѭ��
Ϊ������������������Ժ���ջ֡�Ķ�λʹ��[x,y]��ʽ
����ڶ��㺯��ջ֡�ĵ�һ��forѭ��λ��[2,1]

[2,1]
��ʱ��putTogetherΪ"a"��ѡ���ַ�'d'�����������ջ֡

[3,1]
������ֹ�������ַ�"ad"��¼��finishingPoint
����

[2,2]
��ʱ��putTogetherΪ"a"��ѡ���ַ�'e'�����������ջ֡

[3,1]
������ֹ�������ַ�"ae"��¼��finishingPoint
����

[2,3]
��ʱ��putTogetherΪ"a"��ѡ���ַ�'f'�����������ջ֡

[3,1]
������ֹ�������ַ�"af"��¼��finishingPoint
����

�ڶ��㺯��ջ֡ȫ��ִ����ɣ�����

[1,2]
��ʱ��putTogetherΪ""��ѡ���ַ�'b'������ڶ���ջ֡

[2,1]
��ʱ��putTogetherΪ"b"��ѡ���ַ�'d'�����������ջ֡

[3,1]
������ֹ�������ַ�"bd"��¼��finishingPoint
����

[2,2]
��ʱ��putTogetherΪ"b"��ѡ���ַ�'e'�����������ջ֡

[3,1]
������ֹ�������ַ�"be"��¼��finishingPoint
����

[2,3]
��ʱ��putTogetherΪ"b"��ѡ���ַ�'f'�����������ջ֡

[3,1]
������ֹ�������ַ�"bf"��¼��finishingPoint
����

�ڶ��㺯��ջ֡ȫ��ִ����ɣ�����

[1,2]
��ʱ��putTogetherΪ""��ѡ���ַ�'c'������ڶ���ջ֡

[2,1]
��ʱ��putTogetherΪ"c"��ѡ���ַ�'d'�����������ջ֡

[3,1]
������ֹ�������ַ�"cd"��¼��finishingPoint
����

[2,2]
��ʱ��putTogetherΪ"c"��ѡ���ַ�'e'�����������ջ֡

[3,1]
������ֹ�������ַ�"ce"��¼��finishingPoint
����

[2,3]
��ʱ��putTogetherΪ"c"��ѡ���ַ�'f'�����������ջ֡

[3,1]
������ֹ�������ַ�"cf"��¼��finishingPoint
����

�ڶ��㺯��ջ֡ȫ��ִ����ɣ�����

��һ�㺯��ջ֡ȫ��ִ����ϣ�����

�ﺯ��ȫ��ִ����ϣ�����

����v����¼ȫ�����ܣ�����


*/