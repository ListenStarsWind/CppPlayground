#include"stack.h"

wind::stack::stack(size_t sz, p_stack_data pArr)
{
    _capacity = sz;
    if (pArr == nullptr)
    {
        p_stack_data p = (p_stack_data)realloc(nullptr, sizeof(stack_data) * _capacity);
        if (p == nullptr)
        {
            perror("wind::stack::stack realloc fail");
            exit(-1);
        }
        _p = p;
        _top = 0;
    }
    else
    {
        _p = pArr;
        _top = _capacity;
    }
}


wind::stack::~stack()
{
    //std::cout << "~stack()" << std::endl;
    free(_p);
    _p = nullptr;
    _top = _capacity = 0;
}

wind::stack::stack(const stack& s)
{
    _top = s._top;
    _capacity = s._capacity;
    _p = (p_stack_data)malloc(sizeof(stack_data) * _capacity);
    if (_p == nullptr)
    {
        perror("stack copy fail");
        exit(-1);
    }
    memcpy(_p, s._p, sizeof(stack_data) * _top);
}

void wind::stack::Ext()
{
    size_t newCapacity = _capacity == 0 ? 2 : _capacity * 2;
    p_stack_data p = (p_stack_data)realloc(_p, sizeof(stack_data) * newCapacity);
    if (p == nullptr)
    {
        perror("stack.Ext realloc fail");
        return;
    }
    _p = p;
    _capacity = newCapacity;
}

void wind::stack::push(stack_data val)
{
    if (_top == _capacity)
    {
        Ext();
    }
    _p[_top++] = val;
}

bool wind::stack::IsEmpty()
{
    if (_top == 0)
        return true;
    else
        return false;
}

bool wind::stack::ReadTop(stack_data& val)
{
    if (IsEmpty())
        return false;
    else
    {
        val = _p[_top - 1];
        return true;
    }
}

bool wind::stack::Pop()
{
    if (IsEmpty())
        return false;
    else
    {
        _top--;
        return true;
    }
}

bool wind::stack::ReadPop(stack_data& val)
{
    if (IsEmpty())
        return false;
    else
    {
        ReadTop(val);
        return Pop();
    }
}