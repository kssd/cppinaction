#if !defined SIMPLE_STRING
#define SIMPLE_STRING
//------------------------------------
//  (c) Bartosz Milewski, 1998
//------------------------------------

#include <cstring>
#include <cctype>
#include <cassert>

//
// A string with value semantics
//

class StringVal
{
public:
    StringVal (char const * cstr)
        :_buf (0)
    {
        if (cstr != 0)
            Init (cstr);
    }
    StringVal (StringVal const & str)
        :_buf (0)
    {
        if (str.c_str () != 0)
            Init (str.c_str ());
    }
    ~StringVal ()
    {
        delete _buf;
    }
    StringVal & operator= (StringVal const & str)
    {
        if (this != & str)
        {
            char const * cstr = str.c_str ();
            if (cstr == 0)
            {
                delete _buf;
                _buf = 0;
            }
            else
            {
                size_t len = strlen (cstr);
                if (_buf == 0 || strlen (_buf) < len)
                {
                    delete _buf;
                    Init (cstr);
                }
                else
                    strcpy (_buf, cstr);
            }
        }
        return *this;
    }
    char const * c_str () const { return _buf; }
    void Upcase ()
    {
        if (_buf)
        {
            int len = strlen (_buf);
            for (int i = 0; i < len; ++i)
                _buf [i] = toupper (_buf [i]);
        }
    }
private:
    void Init (char const * cstr)
    {
        assert (cstr != 0);
        _buf = new char [strlen (cstr) + 1];
        strcpy (_buf, cstr);
    }

    char  * _buf;
};

//
// Generic reference counted class
//
class RefCounted
{
public:
    RefCounted () : _count (1) {}
    int GetRefCount () const { return _count; }
    void IncRefCount () const { _count++; }
    int DecRefCount () const { return --_count; }
private:
    mutable int _count;
};

//
// Pointer to reference counted object
//
template <class T>
class RefPtr
{
public:
    RefPtr (RefPtr<T> const & p)
    {
        _p = p._p;
        _p->IncRefCount ();
    }
    ~RefPtr ()
    {
        Release ();
    }
    RefPtr const & operator= (RefPtr const & p)
    {
        if (this != &p)
        {
            Release ();
            _p = p._p;
            _p->IncRefCount ();
        }
        return *this;
    }
protected:
    RefPtr (T * p) : _p (p) {}
    void Release ()
    {
        if (_p->DecRefCount () == 0)
            delete _p;
    }

    T * _p;
};

//
// String representation: reference counted
//
class StringRep: public RefCounted
{
public:
    StringRep (char const * cstr)
        :_string (cstr)
    {}
    char const * c_str () const { return _string.c_str (); }
    void Upcase ()
    {
        _string.Upcase ();
    }
private:
    StringVal _string;
};

//
// A string class with reference counted representation
//
class StringRef: public RefPtr<StringRep>
{
public:
    StringRef (char const * cstr)
        : RefPtr<StringRep> (new StringRep (cstr))
    {}
    StringRef (StringRef const & str)
        : RefPtr<StringRep> (str)
    {}
    char const * c_str () const { return _p->c_str (); }
    void Upcase ()
    {
        _p->Upcase ();
    }
};

//
// A string class with Copy-On-Write semantics
//
class StringCow: public RefPtr<StringRep>
{
public:
    StringCow (char const * cstr)
        : RefPtr<StringRep> (new StringRep (cstr))
    {}
    StringCow (StringCow const & str)
        : RefPtr<StringRep> (str)
    {}
    char const * c_str () const { return _p->c_str (); }
    void Upcase ()
    {
        Cow ();
        _p->Upcase ();      
    }
private:
    void Cow ()
    {
		if (_p->GetRefCount () > 1)
		{
			// clone it
			StringRep * rep = new StringRep (_p->c_str ());
			Release ();
			_p = rep;
		}
    }
};

#endif
