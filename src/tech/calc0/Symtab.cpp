//------------------------------------
//  symtab.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "symtab.h"

#include <cassert>
#include <cstring>
#include <iostream>

SymbolTable::SymbolTable (int size)
    : _size (size), _curId (0), _curStrOff (0), _htab (size + 1)
{
    _offStr = new int [size];
    _bufSize = size * 10;
    _strBuf = new char [_bufSize];
}

SymbolTable::~SymbolTable()
{
    delete []_offStr;
    delete []_strBuf;
}

// Add string without looking for duplicates

int SymbolTable::ForceAdd (char const * str)
{
	int len = strlen (str);
	assert (len > 0);
    // is there enough space?
    if (_curId == _size
        || _curStrOff + len + 1 >= _bufSize)
    {
        return idNotFound;
    }
    // point to place where the string will be stored
    _offStr [_curId] = _curStrOff;
    // copy the string there
    strncpy (&_strBuf [_curStrOff], str, len);
    // calculate new offset
    _curStrOff += len;
    _strBuf [_curStrOff] = 0;  // null terminate
    ++_curStrOff;
    // add to hash table
    _htab.Add (str, _curId);
    ++_curId;
    return _curId - 1;
}

int SymbolTable::Find (char const * str) const
{
    // Iterate over a short list from hash table
	for (IdSeq seq (_htab, str);
        !seq.AtEnd ();
		seq.Advance ())
	{
        int id = seq.GetId ();
        int offStr = _offStr [id];
        // char const * strStored = &_strBuf [ offStr ];
        char const * strStored = _strBuf + offStr;
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
    int offStr = _offStr [id];
    return &_strBuf [offStr];
    // return _strBuf + offStr;
}
