//------------------------------------
//  tree.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "tree.h"
#include "store.h"
#include <cmath>
#include <iostream>
using std::cerr;

BinNode::~BinNode ()
{
    delete _pLeft;
    delete _pRight;
}

double NumNode::Calc () const
{
    return _num;
}

double VarNode::Calc () const
{
	double x = 0.0;
    if (_store.IsInit (_id ))
        x = _store.Value (_id);
	else
		cerr << "Use of uninitialized variable\n";
    return x;
}

void VarNode::Assign (double val)
{
    _store.SetValue (_id, val);
}

bool VarNode::IsLvalue () const
{
    return true;
}

double UMinusNode::Calc () const
{
    return - _pNode->Calc();
}

double FunNode::Calc () const
{
    double val = 0;
    assert (_pFun != 0);
    val = (*_pFun)(_pNode->Calc());
    return val;
}

#if 0 // iterator version

MultiNode::~MultiNode ()
{
	typedef std::vector<Node *>::iterator NodeIter;
    for (NodeIter it = _aChild.begin (); it != _aChild.end (); ++it)
        delete *it;
	for (NodeSeq seq (_aChild); !seq.AtEnd (); seq.Advance ())
		delete seq.Get ();
}

#else // sequencer version

class NodeSeq
{
public:
	NodeSeq (std::vector<Node *> & vec)
		: _cur (vec.begin ()), _end (vec.end ())
	{}
	bool AtEnd () const { return _cur == _end; }
	void Advance () { ++_cur; }
	Node * Get () { return *_cur; }
private:
	std::vector<Node *>::iterator _cur;
	std::vector<Node *>::iterator _end;
};

MultiNode::~MultiNode ()
{
	for (NodeSeq seq (_aChild); !seq.AtEnd (); seq.Advance ())
		delete seq.Get ();
}

#endif // end versions

double AssignNode::Calc () const
{
    double x = _pRight->Calc ();
    _pLeft->Assign (x);
    return x;
}

double SumNode::Calc () const
{
    double sum = 0.0;
    for (int i = 0; i < _aChild.size (); ++i)
    {
        double val = _aChild [i]->Calc ();
        if (_aIsPositive [i])
            sum += val;
        else
            sum -= val;
    }
    return sum;
}

// Notice: the calculation is left associative
double ProductNode::Calc () const
{
    double prod = 1.0;
    for (int i = 0; i < _aChild.size (); ++i)
    {
        double val = _aChild [i]->Calc ();
        if (_aIsPositive [i])
            prod *= val;
        else if (val != 0.0)
        {
            prod /= val;
        }
        else
        {
            cerr << "Error: division by zero\n";
            return HUGE_VAL;
        }
    }
    return prod;
}
