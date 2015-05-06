//------------------------------------
//  store.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "store.h"
#include "symtab.h"
#include <cmath>
#include <iostream>
using std::cerr;
using std::endl;

Store::Store (SymbolTable & symTab)
{
    // add predefined constants
    // Note: if more needed, do a more general job
    cerr << "e = " << exp (1) << endl;
    int id = symTab.ForceAdd ("e");
    AddValue (id, exp (1));
    cerr << "pi = " << 2 * acos (0.0) << endl;
    id = symTab.ForceAdd ("pi");
    AddValue (id, 2 * acos (0.0));
}
