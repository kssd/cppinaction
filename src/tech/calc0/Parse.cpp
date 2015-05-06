//------------------------------------
//  parse.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "parse.h"
#include "scan.h"
#include "tree.h"
#include "symtab.h"
#include "funtab.h"
#include "store.h"

#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>
using std::cerr;
using std::endl;

Parser::Parser (Scanner & scanner, 
        Store & store,
        FunctionTable & funTab,
        SymbolTable & symTab )
: _scanner (scanner), 
  _pTree (0), 
  _status (stOk), 
  _funTab (funTab),
  _store (store),
  _symTab (symTab)
{
}

Parser::~Parser ()
{
    delete _pTree;
}

Status Parser::Parse ()
{
    // Everything is an expression
    _pTree = Expr ();
    if (!_scanner.IsDone ())
        _status = stError;
    return _status;
}

double Parser::Calculate () const
{
    assert (_status == stOk);
    assert (_pTree != 0);
    return _pTree->Calc ();
}

Node * Parser::Expr ()
{
    // Parse a term
    Node * pNode = Term ();
    EToken token = _scanner.Token ();
    if (token == tPlus || token == tMinus)
    {
        // Expr := Term { ('+' | '-') Term }
        MultiNode * pMultiNode = new SumNode (pNode);
        do
        {
            _scanner.Accept ();
            Node * pRight = Term ();
            pMultiNode->AddChild (pRight, (token == tPlus));
            token = _scanner.Token ();
        } while (token == tPlus || token == tMinus);
        pNode = pMultiNode;
    }
    else if (token == tAssign)
    {
        _scanner.Accept ();
        // Expr := Term = Expr
        Node * pRight = Expr ();
        // provided the Term is an lvalue
        if (pNode->IsLvalue ())
        {
            // Assignment node
            pNode = new AssignNode (pNode, pRight);
        }
        else
        {
            _status = stError;
            delete pNode;
            pNode = Expr ();
        }
    }
    // otherwise Expr := Term
    return pNode;
}

Node * Parser::Term ()
{
    Node * pNode = Factor ();
    EToken token = _scanner.Token ();
    if (token == tMult || token == tDivide)
    {
        // Term := Factor { ('*' | '/') Factor }
        MultiNode * pMultiNode = new ProductNode (pNode);
        do
        {
            _scanner.Accept ();
            Node * pRight = Factor ();
            pMultiNode->AddChild (pRight, (token == tMult));
            token = _scanner.Token ();
        } while (token == tMult || token == tDivide);
        pNode = pMultiNode;
    }
    // otherwise Term := Factor
    return pNode;
}

Node * Parser::Factor ()
{
    Node * pNode;
    EToken token = _scanner.Token ();

    if (token == tLParen)
    {
        _scanner.Accept (); // accept '('
        pNode = Expr ();
        if (_scanner.Token () == tRParen)
	        _scanner.Accept (); // accept ')'
		else
            _status = stError;
    }
    else if (token == tNumber)
    {
        pNode = new NumNode (_scanner.Number ());
        _scanner.Accept ();
    }
    else if (token == tIdent)
    {
        char strSymbol [maxSymLen + 1];
        // copy the symbol into strSymbol
        int lenSym = _scanner.GetSymbolName (strSymbol, maxSymLen + 1);
        int id = _symTab.Find (strSymbol);
        _scanner.Accept ();
        if (_scanner.Token () == tLParen) // function call
        {
            _scanner.Accept (); // accept '('
            pNode = Expr ();
            if (_scanner.Token () == tRParen)
	            _scanner.Accept (); // accept ')'
			else
                _status = stError;
            if (id != idNotFound && id < _funTab.Size ())
            {
                pNode = new FunNode (
                    _funTab.GetFun (id), pNode);
            }
            else
            {
                cerr << "Unknown function \"";
                cerr << strSymbol << "\"" << endl;
            }
        }
        else
        {
			// Factor := Ident
            if (id == idNotFound)
			{
                id = _symTab.ForceAdd (strSymbol);
				if (id == idNotFound)    
				{
					cerr << "Error: Too many variables\n";
					_status = stError;
					pNode = 0;
				}
			}
			if (id != idNotFound)
				pNode = new VarNode (id, _store);
        }
    }
    else if (token == tMinus) // unary minus
    {
        _scanner.Accept (); // accept minus
        pNode = new UMinusNode (Factor ());
    }
    else
    {
        _scanner.Accept ();
        _status = stError;
        pNode = 0;
    }
    return pNode;
}
