//------------------------------------
//  symtab.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "symtab.h"

#include <cassert>
#include <cstring>
#include <iostream>

SymbolTable::SymbolTable ()
    : _curId (0), 
      _htab (cSymInit + 1),
      _aOffStr (0)
{}

// Add string without looking for duplicates

int SymbolTable::ForceAdd (char const * str)
{
    int offset = _bufStr.AddString (str);
    _aOffStr.Add (_curId, offset);
    _htab.Add (str, _curId);
    ++_curId;
    return _curId - 1;
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
    assert (id < _curId);
    int offStr = _aOffStr [id];
    return _bufStr.GetString (offStr);
}
