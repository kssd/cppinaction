#if !defined HASH_H
#define HASH_H
//------------------------------------
//  hash.h
//  Open hash table
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <cstring>

// stores integer id in a link
class Link
{
public:
    Link (Link * pNext, int id)
        : _pNext(pNext), _id(id) {}

    Link *  Next () const { return _pNext; }
    int     Id () const { return _id; }
private:
    Link *      _pNext;
    const int   _id;
};

// Linked list of id's stored in links

class List
{
public:
    List ();
    ~List ();
    void Add (int id);
    const Link * GetHead () const { return _pHead; }
private:
    Link * _pHead;
};

const int sizeHTable = 127;

// Hash table of strings

class HTable
{
public:
    List const & Find (char const * str) const;
    void Add (char const * str, int id);
private:
    int hash (char const * str) const;

    List _aList [sizeHTable];
};

const int idNotFound = -1;

const int maxStrings = 100;
const int maxBufSize = 500;
       
class StringBuffer
{
public:
    StringBuffer () : _curOffset (0) {}
    bool WillFit (int len) const
    {
        return _curOffset + len + 1 < maxBufSize;
    }
    void Add (char const * str)
    {
        strcpy (&_buf[_curOffset], str);
        _curOffset += strlen (str) + 1;
    }
    int GetOffset () const
    {
        return _curOffset;
    }
    bool IsEqual (int offStr, char const * str) const
    {
        // char const * strStored = &_strBuf [offStr];
        char const * strStored = _buf + offStr;
        return strcmp (str, strStored) == 0;
    }
    char const * GetString (int offStr) const
    {
        //return &_buf [offStr];
        return _buf + offStr;
    }
private:
    char    _buf [maxBufSize];
    int     _curOffset;
};

// String table maps strings to ints
// and ints to strings

class StringTable
{
public:
    StringTable ();
    int ForceAdd (char const * str);
    int Find (char const * str) const;
    char const * GetString (int id) const;
private:
    HTable      _htab;
    int         _offStr [maxStrings]; // positions of strings in buffer
    int         _curId;
    StringBuffer    _strBuf;
};

#endif
