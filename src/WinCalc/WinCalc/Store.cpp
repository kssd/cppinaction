#include "store.h"
// (c) Bartosz Milewski 2000
#include "symtab.h"
#include "SerStream.h"
#include <cmath>

Store::Store (SymbolTable & symTab)
{
	AddConsts (symTab);
}

void Store::AddConsts (SymbolTable & symTab)
{
    // add predefined constants
    // Note: if more needed, do a more general job
    int id = symTab.ForceAdd ("e");
    AddValue (id, exp (1));
    id = symTab.ForceAdd ("pi");
    AddValue (id, 2 * acos (0.0));
	_firstVarId = id + 1;
}

int Store::FindChanged () const
{
	int size = Size ();
	for (int i = 0; i < size; ++i)
	{
		if (_cells [i].IsChanged () && _cells [i].IsInit ())
			return i;
	}
	return idNotFound;
}


void Store::Serialize (Serializer & out) const
{
	int len = _cells.size ();
	out.PutLong (len);
	for (int i = 0; i < len; ++i)
	{
		out.PutDouble (_cells [i]._value);
		out.PutBool (_cells [i]._isInit != 0);
	}
}

void Store::DeSerialize (DeSerializer & in)
{
	_cells.clear ();
	int len = in.GetLong ();
	_cells.resize (len);
	for (int i = 0; i < len; ++i)
	{
		_cells [i]._value = in.GetDouble ();
		_cells [i]._isInit = in.GetBool ()? 1: 0;
		_cells [i]._isChanged = 1;
	}
}

