//------------------------------------
//  funtab.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "funtab.h"
#include "symtab.h"

#include <cassert>
#include <cstring>
#include <cmath>
#include <iostream>
using std::cerr;
using std::endl;

double CoTan (double x) 
{
    double y = tan (x);
    if (y == 0)
    {
        cerr << "cotan of " << x << " undefined\n";
        return HUGE_VAL;
    }
    return 1.0 / y;
}

class FunctionEntry
{
public:
    PFun pFun;
    char* strFun;
};

static FunctionEntry FunctionArray [] =
{ 
    log,  "log",
    log10,"log10",
    exp,  "exp",
    sqrt, "sqrt",
    sin,  "sin",
    cos,  "cos",
    tan,  "tan",
    CoTan,"cotan",
    sinh, "sinh",
    cosh, "cosh",
    tanh, "tanh",
    asin, "asin",
    acos, "acos",
    atan, "atan",
};

FunctionTable::FunctionTable (SymbolTable & symTab)
    : _size(sizeof FunctionArray / sizeof FunctionArray [0])
{
	_pFun = new PFun [_size];
    for (int i = 0; i < _size; ++i)
    {
        int len =  strlen (FunctionArray [i].strFun);
        _pFun [i] = FunctionArray [i].pFun;
        cerr << FunctionArray[i].strFun << endl;
        int j = symTab.ForceAdd (FunctionArray[i].strFun);
        assert (i == j);
    }
}

