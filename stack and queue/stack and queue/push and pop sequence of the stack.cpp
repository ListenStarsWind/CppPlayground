#include<vector>
#include<stack>

using namespace std;

class Solution {
public:
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        stack<int> s;
        auto in = pushV.begin();
        auto out = popV.begin();
        auto it = pushV.begin();
        auto in_end = pushV.end();
        auto out_end = popV.end();
        while (in != in_end) {
            s.push(*in);
            ++in;
            while (!s.empty() && out != out_end && s.top() == *out) {
                ++out;
                s.pop();
            }
        }
        return s.empty();
    }
};