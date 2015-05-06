#if !defined SYMTAB_H
#define SYMTAB_H
//------------------------------------
//  symtab.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "serial.h"
#pragma warning (disable:4786)
#include <map>
#include <string>

class SymbolTable: public Serializable
{
public:
	enum { idNotFound = -1 };
	SymbolTable () : _id (0) {}
	int ForceAdd (std::string const & str);
	int Find (std::string const & str) const;
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
private:
	std::map<std::string, int> _dictionary;
	int _id;
};

#endif
