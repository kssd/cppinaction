//------------------------------------
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "strbuf.h"
#include <cstring>

int StringBuffer::AddString (char const * str)
{
    int len = strlen (str);
    int offset = _curStrOff;
    // is there enough space?
    if (_curStrOff + len + 1 >= _bufSize)
    {
        Reallocate (len + 1);
    }
    // copy the string there
    strncpy (&_strBuf [_curStrOff], str, len);
    // calculate new offset
    _curStrOff += len;
    _strBuf [_curStrOff] = 0;  // null terminate
    ++_curStrOff;
    return offset;
}

void StringBuffer::Reallocate (int addLen)
{
    int newSize = _bufSize * 2;
    if (newSize <= _curStrOff + addLen)
        newSize = _curStrOff + addLen;
    char * newBuf = new char [newSize];
    for (int i = 0; i < _curStrOff; ++i)
        newBuf [i] = _strBuf [i];
    delete []_strBuf;
    _strBuf = newBuf;
    _bufSize = newSize;
}
