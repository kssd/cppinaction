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
#include "dbnew.h"
using std::cerr;
using std::endl;

namespace Function
{
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

	class Entry
	{
	public:
		PFun pFun;
		char* strFun;
	};

	Entry Array [] =
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

	Table::Table (SymbolTable & symTab)
		: _size(sizeof Array / sizeof Array [0])
	{
		_pFun = new PFun [_size];
		for (int i = 0; i < _size; ++i)
		{
			int len =  strlen (Array [i].strFun);
			_pFun [i] = Array [i].pFun;
			cerr << Array[i].strFun << endl;
			int j = symTab.ForceAdd (Array[i].strFun);
			assert (i == j);
		}
	}

	Table::~Table ()
	{ 
		delete []_pFun;
	}

}