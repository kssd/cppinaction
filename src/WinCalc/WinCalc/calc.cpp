#include "calc.h"
// (c) Bartosz Milewski 2000
#include "SerStream.h"
#include "Exception.h"
#include <algorithm>

class IsEqualId
{
public:
	IsEqualId (int id) : _id (id) {}
	bool operator () (std::pair<std::string const, int> const & it) const
	{
		return it.second == _id;
	}
private:
	int _id;
};

std::string Calculator::GetVariableName (int id)
{
	SymbolTable::iterator it = std::find_if (_symTab.begin (), 
											 _symTab.end (), 
											 IsEqualId (id));
	if (it == _symTab.end ())
		throw Win::Exception ("Internal error: missing entry in symbol table");
	return it->first;
}

bool Calculator::HasValueChanged (int id)
{
	return _store.IsChanged (id);
}

void Calculator::Serialize (Serializer & out) const
{
    _symTab.Serialize (out);
    _store.Serialize (out);
}

void Calculator::DeSerialize (DeSerializer & in)
{
    _symTab.DeSerialize (in);
    _store.DeSerialize (in);
}

void Calculator::ClearMemory ()
{
	_symTab.Clear ();
	_store.Clear ();
	_funTab.Init (_symTab);
	_store.AddConsts (_symTab);
}
