//------------------------------------
//  symtab.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "symtab.h"

#include <cassert>
#include <cstring>
#include <iostream>

SymbolTable::SymbolTable ()
   :_htab (cSymInit + 1)
{}

// Add string without looking for duplicates

int SymbolTable::ForceAdd (char const * str)
{
    int offset = _bufStr.AddString (str);
	int id = _aOffStr.size ();
	_aOffStr.push_back (offset);
	_htab.Add (str, id);
	return id;
}

int SymbolTable::Find (char const * str) const
{
    // Iterate over a short list from hash table
	for (HTable::Seq seq (_htab, str);
        !seq.AtEnd ();
		seq.Advance ())
	{
        int id = seq.GetValue ();
        int offStr = _aOffStr [id];
        char const * strStored = _bufStr.GetString (offStr);
        if (strcmp (str, strStored) == 0) // they're equal
        {
            return id;  // success!
        }
    }
    return idNotFound;
}

// map integer into string. Must be valid id

char const * SymbolTable::GetString (int id) const
{
    assert (id >= 0);
    assert (id < _aOffStr.size ());
    int offStr = _aOffStr [id];
    return _bufStr.GetString (offStr);
}
