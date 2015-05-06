#if !defined CALC_H
#define CALC_H
//------------------------------------
//  calc.h
//  A simple stack based calculator
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "stack.h"
#include "input.h"

class Calculator
{
public:
    bool Execute (Input const & input);
    // give access to stack
    IStack const & GetStack () { return _stack; }
private:
    int Calculate (int n1, int n2, int token) const;

    IStack  _stack;
};
#endif
