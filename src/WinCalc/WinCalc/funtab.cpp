#include "funtab.h"
// (c) Bartosz Milewski 2000
#include "symtab.h"
#include "status.h"

#include <cassert>
#include <cstring>
#include <cmath>
#include <sstream>

namespace Function
{
	double CoTan (double x) 
	{
		double y = tan (x);
		if (y == 0)
		{
			std::ostringstream out;
			out << "cotan of " << x << " undefined";
			TheOutput.Error (out.str ());
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
		: _size(sizeof Array / sizeof Array [0]), _pFun (0)
	{
		Init (symTab);
	}

	void Table::Init (SymbolTable & symTab)
	{
		delete _pFun;
		_pFun = new PFun [_size];
		for (int i = 0; i < _size; ++i)
		{
			int len =  strlen (Array [i].strFun);
			_pFun [i] = Array [i].pFun;
			int j = symTab.ForceAdd (Array[i].strFun);
			assert (i == j);
		}
	}

}