#if !defined STORE_H
#define STORE_H
//------------------------------------
//  store.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "dynarr.h"
#include <cassert>
class SymbolTable;

class Store
{
private:
    // private anonymous enum
    enum { stNotInit, stInit };
public:
    explicit Store (SymbolTable & symTab);
    bool IsInit (int id) const
    {
		assert (id >= 0);
        return _aStatus.InRange (id) && _aStatus [id] != stNotInit;
    }
    double Value (int id) const
    {
		assert (id >= 0);
        assert (IsInit (id));
        return _aCell [id];
    }
    void SetValue (int id, double val)
    {
		assert (id >= 0);
        if (_aCell.InRange (id))
        {
            _aCell [id] = val;
            _aStatus [id] = stInit;
        }
        else
        {
            AddValue (id, val);
        }
    }

    void AddValue (int id, double val)
    {
		assert (id >= 0);
        _aCell.Add (id, val);
        _aStatus.Add (id, stInit);
    }
private:
    DynArray<double>           _aCell;
    DynArray<unsigned char>    _aStatus;
};

#endif
