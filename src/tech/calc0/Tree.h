#if !defined TREE_H
#define TREE_H
//------------------------------------
//  tree.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

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
    UMinusNode (Node * pNode) : _pNode (pNode) {}
    ~UMinusNode () { delete _pNode; }
    double Calc () const;
private:
    Node * const _pNode;
};

typedef double (*PFun)(double); 

class FunNode: public Node
{
public:
    FunNode (PFun pFun, Node * pNode) : _pNode (pNode), _pFun (pFun) {}
    ~FunNode () { delete _pNode; }
    double Calc () const;
private:
    Node * const _pNode;
    PFun         _pFun;
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

const int MAX_CHILDREN = 8;
// Generic multiple node: an abstract class
class MultiNode: public Node
{
public:
    MultiNode (Node * pNode)
    : _isError (false)
    {
        _aChild [0] = pNode;
        _aIsPositive[0] = true;
        _iCur = 1;
    }
    ~MultiNode ();
    void AddChild (Node * pNode, bool isPositive)
    {
        if (_iCur == MAX_CHILDREN)
        {
            _isError = true;
            return;
        }
        _aChild [_iCur] = pNode;
        _aIsPositive [_iCur] = isPositive;
        ++_iCur;
    }
protected:
    bool     _isError;
    int      _iCur;
    Node   * _aChild [MAX_CHILDREN];
    bool     _aIsPositive [MAX_CHILDREN];
};

// Summing
class SumNode: public MultiNode
{
public:
    SumNode (Node * pNode)
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
    ProductNode (Node * pNode)
        : MultiNode (pNode) {}
    double Calc () const;
};

class BinNode: public Node
{
public:
    BinNode (Node * pLeft, Node * pRight)
    : _pLeft (pLeft), _pRight (pRight) {}
    ~BinNode ();
protected: 
    Node * const _pLeft;
    Node * const _pRight;
};

class AssignNode : public BinNode
{
public:
    AssignNode (Node * pLeft, Node * pRight)
        : BinNode (pLeft, pRight) {}
    double Calc () const;
};

#endif 
