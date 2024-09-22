#include"stack.h"

void wind::stack::Init()
{
    _p = nullptr;
    _top = _capacity = 0;
}

void wind::stack::Dest()
{
    free(_p);
    _p = nullptr;
    _top = _capacity = 0;
}

void wind::stack::Ext()
{
    int newCapacity = _capacity == 0 ? 2 : _capacity * 2;
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