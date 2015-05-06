#if !defined SYMTAB_H
#define SYMTAB_H
// (c) Bartosz Milewski 2000
#include "serial.h"
#pragma warning (disable:4786)
#include <map>
#include <string>

class SymbolTable: public Serializable
{
public:
	typedef std::map<std::string, int>::const_iterator iterator;
public:
	SymbolTable () : _nextId (0) {}
	int ForceAdd (std::string const & str);
	int Find (std::string const & str) const;
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
	void Clear () 
	{ 
		_dictionary.clear ();
		_nextId = 0;
	}
	int GetSize () const { return _dictionary.size (); }
	iterator begin () const { return _dictionary.begin (); }
	iterator end () const { return _dictionary.end (); }
private:
	std::map<std::string, int> _dictionary;
	int _nextId;
};

#endif
