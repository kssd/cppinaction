//------------------------------------
//  stack.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "stack.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

//compile with NDEBUG=1 to get rid of assertions

void IStack::Push (int i)
{
    assert (_top < maxStack);
    _arr [_top] = i;
    ++_top;
}

int IStack::Pop ()
{
    assert (_top > 0);
    --_top;
    return _arr [_top];
}

void main ()
{
    IStack stack;
    stack.Push (1);
    stack.Push (2);
    cout << "Popped " << stack.Pop() << endl;
    cout << "Popped " << stack.Pop() << endl;
}
