#if !defined STORE_H
#define STORE_H
//------------------------------------
//  store.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include <cassert>
#include <vector>
class SymbolTable;

class Store
{
public:
    explicit Store (SymbolTable & symTab);
    bool IsInit (int id) const
    {
		assert (id >= 0);
        return id < _aIsInit.size () && _aIsInit [id];
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
        if (id < _aCell.size ())
        {
            _aCell [id] = val;
            _aIsInit [id] = true;
        }
        else
        {
            AddValue (id, val);
        }
    }

    void AddValue (int id, double val)
    {
		assert (id >= 0);
		_aCell.resize (id + 1);
		_aIsInit.resize (id + 1);
        _aCell [id] = val;
        _aIsInit [id] = true;
    }
private:
    std::vector<double>  _aCell;
    std::vector<bool>    _aIsInit;
};

#endif
