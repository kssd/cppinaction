#include "calc.h"
#include "SerStream.h"

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
