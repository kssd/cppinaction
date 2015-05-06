#if !defined TREE_H
#define TREE_H
//------------------------------------
//	tree.h
//	(c) Bartosz Milewski, 1994
//------------------------------------
#include "auto_vector.h"
#include <vector>

#include <memory>
using std::auto_ptr;

// only if there's no member template support
template<class To, class From>
auto_ptr<To> up_cast (auto_ptr<From> & from)
{
	return auto_ptr<To> (from.release ());
}

class Node
{
public:
	virtual ~Node () {}
	virtual double Calc () const = 0;
	virtual bool IsLvalue () const { return false; }
	virtual void Assign (double value) {}
};

class NumNode: public Node
{
public:
	NumNode ( double num ) : _num (num ) {}
	double Calc () const;
private:
	const double _num;
};

class UMinusNode: public Node
{
public:
	UMinusNode (auto_ptr<Node> & pNode) : _pNode (pNode) {}
	double Calc () const;
private:
	auto_ptr<Node> _pNode;
};

typedef double (*PFun)(double); 

class FunNode: public Node
{
public:
	FunNode (PFun pFun, auto_ptr<Node> & pNode) : _pNode (pNode), _pFun (pFun) {}
	double Calc () const;
private:
	auto_ptr<Node> _pNode;
	PFun		   _pFun;
};

class Store;

class VarNode: public Node
{
public:
	VarNode (int id, Store & store)
		: _id (id), _store(store) {}
	double Calc () const;
	bool IsLvalue () const;
	void Assign (double val );
private:
	const int _id;
	Store & _store;
};

class MultiNode: public Node
{
public:
	MultiNode (auto_ptr<Node> & pNode)
	{
		AddChild (pNode, true);
	}
	void AddChild (auto_ptr<Node> & pNode, bool isPositive)
	{
		_aChild.push_back (pNode);
		_aIsPositive.push_back (isPositive);
	}
protected: 
	auto_vector<Node>  _aChild;
	std::vector<bool>  _aIsPositive;
};

// Summing
class SumNode: public MultiNode
{
public:
	SumNode (auto_ptr<Node> & pNode)
		: MultiNode (pNode) {}
	double Calc () const;
};

// Multiplying and dividing.
// Sign in this case refers to
// the exponent: positive means multiply,
// negative means divide
class ProductNode: public MultiNode
{
public:
	ProductNode (auto_ptr<Node> & pNode)
		: MultiNode (pNode) {}
	double Calc () const;
};

class BinNode: public Node
{
public:
	BinNode (auto_ptr<Node> & pLeft, auto_ptr<Node> & pRight)
	: _pLeft (pLeft), _pRight (pRight) {}
protected: 
	auto_ptr<Node> _pLeft;
	auto_ptr<Node> _pRight;
};

class AssignNode : public BinNode
{
public:
	AssignNode (auto_ptr<Node> & pLeft, auto_ptr<Node> & pRight)
	: BinNode (pLeft, pRight) {}

	double Calc () const;
};

#endif 
