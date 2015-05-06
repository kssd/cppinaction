//------------------------------------
//  symtab.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------
//#pragma warning (disable:4786)
#include "symtab.h"

#include <iostream>

// Add string without looking for duplicates

int SymbolTable::ForceAdd (std::string const & str)
{
	_dictionary [str] = _id;
	// Or, equivalently:
	// std::pair<std::string, int> p (str, _id);
	// _dictionary.insert (p);
	return _id++;
}

int SymbolTable::Find (std::string const & str) const
{
	std::map<std::string, int>::const_iterator it;
	it = _dictionary.find (str);
	if (it != _dictionary.end ())
		return it->second;
	return idNotFound;
}
