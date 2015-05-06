//------------------------------------
//  store.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "store.h"
#include "symtab.h"
#include "SerStream.h"
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

void Store::Serialize (Serializer & out) const
{
	int len = _aCell.size ();
	out.PutLong (len);
	for (int i = 0; i < len; ++i)
	{
		out.PutDouble (_aCell [i]);
		out.PutBool (_aIsInit [i]);
	}
}

void Store::DeSerialize (DeSerializer & in)
{
	_aCell.clear ();
	_aIsInit.clear ();
	int len = in.GetLong ();
	_aCell.resize (len);
	_aIsInit.resize (len);
	for (int i = 0; i < len; ++i)
	{
		_aCell [i] = in.GetDouble ();
		_aIsInit [i] = in.GetBool ();
	}
}

