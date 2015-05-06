#if !defined STRBUF_H
#define STRBUF_H
//------------------------------------
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <cassert>

class StringBuffer
{
public:
    StringBuffer ()
        : _strBuf (0), _bufSize (0), _curStrOff (0)
    {}
    ~StringBuffer ()
    {
        delete _strBuf;
    }
    int AddString (char const * str);
    char const * GetString (int off) const
    {
        assert (off < _curStrOff);
        return &_strBuf [off];
    }
private:
    void Reallocate (int addLen);

    char  * _strBuf;
    int     _bufSize;
    int     _curStrOff;
};

#endif