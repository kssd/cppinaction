//#pragma warning (disable:4786)
#include "symtab.h"
// (c) Bartosz Milewski 2000
#include "SerStream.h"
#include "status.h"

// Add string without looking for duplicates

int SymbolTable::ForceAdd (std::string const & str)
{
	_dictionary [str] = _nextId;
	// Or, equivalently:
	// std::pair<std::string, int> p (str, _id);
	// _dictionary.insert (p);
	return _nextId++;
}

int SymbolTable::Find (std::string const & str) const
{
	std::map<std::string, int>::const_iterator it;
	it = _dictionary.find (str);
	if (it != _dictionary.end ())
		return it->second;
	return idNotFound;
}

void SymbolTable::Serialize (Serializer & out) const
{
	out.PutLong (_dictionary.size ());
	std::map<std::string, int>::const_iterator it;
	for (it = _dictionary.begin (); it != _dictionary.end (); ++it)
	{
		std::string const & name = it->first;
		int id = it->second;
		out.PutString (name);
		out.PutLong (id);
	}
	out.PutLong (_nextId);
}

void SymbolTable::DeSerialize (DeSerializer & in)
{
	_dictionary.clear ();
	int len = in.GetLong ();
	for (int i = 0; i < len; ++i)
	{
		std::string str = in.GetString ();
		int id = in.GetLong ();
		_dictionary [str] = id;
	}
	_nextId = in.GetLong ();
}

