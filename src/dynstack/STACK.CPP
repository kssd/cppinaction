//------------------------------------
//  stack.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "stack.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

IStack::IStack ()
    : _top (0), _capacity (initStack)
{
    _arr = new int [initStack]; // allocate memory
}

IStack::~IStack ()
{
    delete []_arr; // free memory
}

void IStack::Push (int i)
{
    assert (_top <= _capacity);
    if (_top == _capacity)
        Grow();
    _arr [_top] = i;
    ++_top;
}

// private method
void IStack::Grow ()
{
    cout << "Doubling stack from " << _capacity << endl;
    // allocate new array
    int* arrNew = new int [2 * _capacity];
    // copy all entries
    for (int i = 0; i < _capacity; ++i)
        arrNew [i] = _arr [i];
    _capacity = 2 * _capacity;
    // free old memory
    delete []_arr;
    // substitute new array for old array
    _arr = arrNew;
}

int IStack::Pop ()
{
    // Do not Pop an empty stack
    assert (_top > 0);
    --_top;
    return _arr [_top];
}

int IStack::Top () const
{
    // Don't call Top on an empty stack
    assert (_top > 0);
    return _arr [_top - 1];
}

bool IStack::IsEmpty () const
{
    assert (_top >= 0);
    return _top == 0;
}

void main ()
{
    IStack stack;
    for (int i = 0; i < 5; ++i)
    {
        cout << "Push " << i << endl;
        stack.Push (i);
    }
    for (int j = 0; j < 5; ++j)
    {
        cout << "Pop " << stack.Pop () << endl;
    }
}
