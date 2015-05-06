//------------------------------------
//  stack1.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "stack2.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

void IStack::Push (int i)
{
    // Do not overflow.
    assert (_top < maxStack);
    _arr [_top] = i;
    ++_top;
}

int IStack::Pop ()
{
    // Do not Pop an empty stack
    assert (_top > 0);
    --_top;
    return _arr [ _top ];
}

// stack iterator

StackSeq::StackSeq (IStack const & stack)
    : _iCur (0), _stack (stack) // init reference
{}

bool StackSeq::AtEnd () const
{
    return _iCur == _stack._top;  // friend: can access _top
}

void StackSeq::Advance ()
{
    assert (!AtEnd());
    ++_iCur;
}

int StackSeq::GetNum () const
{
    return _stack._arr [_iCur]; // friend: can access _arr
}

void main ()
{
    IStack TheStack;
    TheStack.Push (1);
    TheStack.Push (2);
    TheStack.Push (3);

    for (StackSeq seq (TheStack);
         !seq.AtEnd();
         seq.Advance() )
    {
        cout << "    " << seq.GetNum () << endl;
    }
}
