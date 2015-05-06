#if !defined SYMTAB_H
#define SYMTAB_H
//------------------------------------
//  symtab.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "htab.h"
#include <cstring>

// String table maps strings to ints
// and ints to strings

class SymbolTable
{
public:
	enum { idNotFound = -1 };    

	explicit SymbolTable (int size);
    ~SymbolTable ();
    int ForceAdd (char const * str);
    int Find (char const * str) const;
    char const * GetString (int id) const;
private:
    HTable  _htab;
    int *   _offStr; // offsets of strings in buffer
    int     _size;
    int     _curId;
    char *  _strBuf;
    int     _bufSize;
    int     _curStrOff;
};
#endif
