#if !defined STORE_H
#define STORE_H
// (c) Bartosz Milewski 2000
#include "serial.h"
#include "status.h"
#include <cassert>
#include <vector>

class SymbolTable;

class Store: public Serializable
{
	class Cell
	{
	public:
		Cell () : _value (0.0), _isInit (0), _isChanged (0) {}
		bool IsChanged () const { return _isChanged != 0; }
		void ResetChange () { _isChanged = 0; }
		bool IsInit () const { return _isInit != 0; }
	public:
		double	_value;
		short	_isInit:1;
		short	_isChanged:1;
	};
public:
    explicit Store (SymbolTable & symTab);
	void AddConsts (SymbolTable & symTab);
	void Clear () 
	{
		_cells.clear ();
		_firstVarId = 0;
	}
	int Size () const { return _cells.size (); }
	bool HasVariables () const { return _cells.size () > _firstVarId; }
    bool IsInit (int id) const
    {
		assert (id >= 0);
        return id < _cells.size () && _cells [id].IsInit ();
    }
	bool IsChanged (int id)
	{
		assert (id >= 0 && id < _cells.size ());
		return _cells [id].IsChanged ();
	}
	void ResetChange (int id)
	{
		_cells [id].ResetChange ();
	}
	int FindChanged () const;
    double Value (int id) const
    {
		assert (id >= 0);
        assert (IsInit (id));
        return _cells [id]._value;
    }
    void SetValue (int id, double val)
    {
		assert (id >= 0);
        if (id < _cells.size ())
        {
            _cells [id]._value = val;
            _cells [id]._isInit = 1;
            _cells [id]._isChanged = 1;
        }
        else
        {
            AddValue (id, val);
        }
    }

    void AddValue (int id, double val)
    {
		assert (id >= 0);
		_cells.resize (id + 1);
        _cells [id]._value = val;
        _cells [id]._isInit = 1;
        _cells [id]._isChanged = 1;
    }
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
private:
    std::vector<Cell> _cells;
	int	_firstVarId;
};

#endif
