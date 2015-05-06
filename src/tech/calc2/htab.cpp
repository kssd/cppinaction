//------------------------------------
//  htab.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "htab.h"

#include <cassert>
#include <cstring>

// Find the list in hash table that may contain
// the id of the string we are looking for

List<int> const & HTable::Find (char const * str) const
{
    int i = hash (str);
    assert (i >= 0 && i < _size);
    return _aList [i];
}

void HTable::Add (char const * str, int id)
{
    int i = hash (str);
    assert (i >= 0 && i < _size);
    _aList [i].Add (id);
}

// Private hashing function

int HTable::hash (char const * str) const
{
    // must be unsigned, hash should return positive number
    unsigned h = str [0];
	assert (h != 0); // no empty strings, please
    for (int i = 1; str [i] != 0; ++i)
        h = (h << 4) + str [i];
    return h % _size;  // small positive integer
}

