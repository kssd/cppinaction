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
public:
	class Seq: public List::Seq
	{
	public:
		Seq (HTable const & htab, char const * str)
			: List::Seq (htab.Find (str)) {}
	};

	friend Seq;
private:
    List const & Find (char const * str) const;
    int hash (char const * str) const;

    List * _aList;
    int    _size;
};

#endif
