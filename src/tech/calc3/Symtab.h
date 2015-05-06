#if !defined SYMTAB_H
#define SYMTAB_H
//------------------------------------
//  symtab.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "htab.h"
#include "strbuf.h"
#include "dynarr.h"

// String table maps strings to ints
// and ints to strings

class SymbolTable
{
    // Private embedded anonymous enum
    enum { cSymInit = 64 };
public:
    // Public embedded anonymous enum
    enum { idNotFound = -1 };
    SymbolTable ();
    int ForceAdd (char const * str);
    int Find (char const * str) const;
    char const * GetString (int id) const;
private:
    int               _curId;
    HTable            _htab;
    DynArray<int>     _aOffStr; // offsets of strings in buffer
    StringBuffer      _bufStr;
};

#endif
