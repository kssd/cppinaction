#if !defined HTAB_H
#define HTAB_H
//------------------------------------
//  htab.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "vlist.h"
#include <cstring>

// Hash table of strings

class HTable
{
	friend class IdSeq;
public:
    explicit HTable (int size): _size(size)
    {
        _aList = new List[size];
    }

    ~HTable ()
    {
        delete [] _aList;
    }

    void Add (char const * str, int id);
private:
    List const & Find (char const * str) const;
    int hash (char const * str) const;

    List * _aList;
    int    _size;
};

// The short list sequencer
// The client creates this sequencer
// to search for a given string
class IdSeq: public ListSeq
{
public:
    IdSeq (HTable const & htab, char const * str)
        : ListSeq (htab.Find (str)) {}
};

#endif
