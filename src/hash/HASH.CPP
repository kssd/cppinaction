//------------------------------------
//  hash.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "hash.h"
#include <cassert>


List::List ()
    : _pHead(0)
{}

List::~List ()
{
    // free linked list
    while (_pHead != 0)
    {
        Link * pLink = _pHead;
        _pHead = _pHead->Next();
        delete pLink;
    }
}

void List::Add (int id)
{
    // add in front of the list
    Link* pLink = new Link (_pHead, id);
    _pHead = pLink;
}

// Find the list in hash table that may contain
// the id of the string we are looking for

List const & HTable::Find (char const * str) const
{
    int i = hash(str);
    return _aList[i];
}

void HTable::Add (char const * str, int id)
{
    int i = hash (str);
    _aList[i].Add (id);
}

// Private hashing function

int HTable::hash (char const * str) const
{
    // no empty strings, please
    assert (str[0] != 0);
    // must be unsigned, hash should return positive number
    unsigned h = str [0];
    for (int i = 1; str [i] != 0; ++i)
        h = (h << 4) + str [i];
    return h % sizeHTable;
}

StringTable::StringTable ()
: _curId (0)
{}

// Add string without looking for duplicates

int StringTable::ForceAdd (char const * str)
{
    int len = strlen (str);
    // is there enough space?
    if (_curId == maxStrings || !_strBuf.WillFit (len))
    {
        return idNotFound;
    }
    // point to place where the string will be stored
    _offStr [_curId] = _strBuf.GetOffset ();
    _strBuf.Add (str);
    // add to hash table
    _htab.Add (str, _curId);
    ++_curId;
    return _curId - 1;
}

int StringTable::Find (char const * str) const
{
    // Get a short list from hash table
    List const & list = _htab.Find (str);
    // Iterate over this list
    for (Link const * pLink = list.GetHead ();
        pLink != 0;
        pLink = pLink->Next ())
    {
        int id = pLink->Id ();
        int offStr = _offStr [id];
        if (_strBuf.IsEqual (offStr, str))
            return id;
    }
    return idNotFound;
}

// map integer into string. Must be valid id

char const * StringTable::GetString (int id) const
{
    assert (id >= 0);
    assert (id < _curId);
    int offStr = _offStr [id];
    return _strBuf.GetString (offStr);
}

#include <iostream>
using std::cout;
using std::endl;

void main ()
{
    StringTable strTable;
    strTable.ForceAdd ("One");
    strTable.ForceAdd ("Two");
    strTable.ForceAdd ("Three");

    int id = strTable.Find ("One");
    cout << "One at " << id << endl;
    id = strTable.Find ("Two");
    cout << "Two at " << id << endl;
    id = strTable.Find ("Three");
    cout << "Three at " << id << endl;
    id = strTable.Find ("Minus one");
    cout << "Minus one at " << id << endl;;

    cout << "String 0 is " << strTable.GetString (0) << endl;
    cout << "String 1 is " << strTable.GetString (1) << endl;
    cout << "String 2 is " << strTable.GetString (2) << endl;
}
