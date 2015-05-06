//------------------------------------
//  stack.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "stack.h"
#include <assert.h>

//compile with NDEBUG=1 to get rid of assertions

void IStack::Push ( int i ) {
    // Do not overflow.
    assert ( _top < maxStack );
    _arr [ _top ] = i;
    ++_top;
}

int IStack::Pop () {
    // Do not Pop an empty stack
    assert ( _top > 0 );
    --_top;
    return _arr [ _top ];
}

int IStack::Top () const {
    // Don't call Top on an empty stack
    assert ( _top > 0 );
    return _arr [ _top - 1 ];
}

bool IStack::IsFull () const {
    assert (_top <= maxStack);
    return _top == maxStack;
}

bool IStack::IsEmpty () const {
    assert (_top >= 0);
    return _top == 0;
}

// stack sequencer
StackSeq::StackSeq (IStack const & stack )
    : _iCur (0), _stack (stack) {
}

int StackSeq::AtEnd () const {
    return _iCur == _stack._top;  // friend: can access _top
}

void StackSeq::Advance () {
    assert (!AtEnd ());
    ++_iCur;
}

int StackSeq::GetNum () const {
    return _stack._arr [_iCur];
}

