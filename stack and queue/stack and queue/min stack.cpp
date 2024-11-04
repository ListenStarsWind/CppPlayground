#include<stack>
#include<iostream>

using namespace std;
template <class T> struct __node {
    T _val;
    size_t _size;

    typedef __node<T> self;

    __node(const T& val = T()) : _val(val), _size(1) {}

    self& operator++() {
        _size++;
        return *this;
    }

    self& operator--() {
        _size--;
        return *this;
    }

    bool invalid() {
        if (_size == 0)
            return true;
        else
            return false;
    }
};

class MinStack {
    typedef __node<int> Node;

public:
    MinStack() {}

    void push(int val) {
        if (_min.empty()) {
            _min.push(Node(val));
        }
        else if (_min.top()._val > val) {
            _min.push(Node(val));
        }
        else if (_min.top()._val == val) {
            ++_min.top();
        }
        _s.push(val);
    }

    void pop() {
        if (_s.top() == _min.top()._val) {
            --_min.top();
            if (_min.top().invalid()) {
                _min.pop();
            }
        }
        _s.pop();
    }

    int top() { return _s.top(); }

    int getMin() { return _min.top()._val; }

private:
    stack<int> _s;
    stack<Node> _min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */