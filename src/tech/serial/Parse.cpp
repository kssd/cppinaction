//------------------------------------
//	parse.cpp
//	(c) Bartosz Milewski, 1994, 98
//------------------------------------

#include "parse.h"
#include "scan.h"
#include "tree.h"
#include "calc.h"

#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>
using std::cerr;
using std::endl;

class Syntax {};

Parser::Parser (Scanner & scanner, Calculator & calc)
: _scanner (scanner), 
  _pTree (0), 
  _status (stOk), 
  _calc (calc)
{
}

Status Parser::Parse ()
{
	try
	{
		// Everything is an expression
		_pTree = Expr ();
		if (!_scanner.IsDone ())
			_status = stError;
	}
	catch (Syntax)
	{
		_status = stError;
	}
	return _status;
}

double Parser::Calculate () const
{
	assert (_status == stOk);
	assert (_pTree.get () != 0);
	return _pTree->Calc ();
}

auto_ptr<Node> Parser::Expr ()
{
	// Parse a term
	auto_ptr<Node> pNode = Term ();

	EToken token = _scanner.Token ();
	if (token == tPlus || token == tMinus)
	{
		// Expr := Term { ('+' | '-') Term }
		auto_ptr<MultiNode> pMultiNode (new SumNode (pNode));
		do
		{
			_scanner.Accept ();
			auto_ptr<Node> pRight = Term ();
			pMultiNode->AddChild (pRight, (token == tPlus));
			token = _scanner.Token ();
		} while (token == tPlus || token == tMinus);
		// with member template support
		// pNode = pMultiNode;
		pNode = up_cast<Node> (pMultiNode);
	}
	else if (token == tAssign)
	{
		_scanner.Accept ();
		// Expr := Term = Expr
		auto_ptr<Node> pRight = Expr ();
		// provided the Term is an lvalue
		if (pNode->IsLvalue ())
		{
			// Assignment node
			pNode = auto_ptr<Node> (new AssignNode (pNode, pRight));
		}
		else
		{
			_status = stError;
			pNode = Expr ();
		}
	}
	// otherwise Expr := Term
	return pNode;
}

auto_ptr<Node> Parser::Term ()
{
	auto_ptr<Node> pNode = Factor ();

	EToken token = _scanner.Token ();
	if (token == tMult || token == tDivide)
	{
		// Term := Factor { ('*' | '/') Factor }
		auto_ptr<MultiNode> pMultiNode (new ProductNode (pNode));
		do
		{
			_scanner.Accept ();
			auto_ptr<Node> pRight = Factor ();
			pMultiNode->AddChild (pRight, (token == tMult));
			token = _scanner.Token ();
		} while (token == tMult || token == tDivide);
		// with member template support
		// pNode = pMultiNode;
		pNode = up_cast<Node> (pMultiNode);
	}
	// otherwise Term := Factor
	return pNode;
}

auto_ptr<Node> Parser::Factor ()
{
	auto_ptr<Node> pNode;
	EToken token = _scanner.Token ();

	if (token == tLParen)
	{
		_scanner.Accept (); // accept '('
		pNode = Expr ();

		if (_scanner.Token () == tRParen)
			_scanner.Accept (); // accept ')'
		else
			throw Syntax ();
	}
	else if (token == tNumber)
	{
		pNode = auto_ptr<Node> (new NumNode (_scanner.Number ()));
		_scanner.Accept ();
	}
	else if (token == tIdent)
	{
		std::string strSymbol = _scanner.GetSymbolName ();
		int id = _calc.FindSymbol (strSymbol);
		_scanner.Accept ();
		if (_scanner.Token () == tLParen) // function call
		{
			_scanner.Accept (); // accept '('
			pNode = Expr ();
			if (_scanner.Token () == tRParen)
				_scanner.Accept (); // accept ')'
			else
				throw Syntax ();
			if (id != SymbolTable::idNotFound && _calc.IsFunction (id))
			{
				pNode = auto_ptr<Node> (
					new FunNode (_calc.GetFun (id), pNode));
			}
			else
			{
				cerr << "Unknown function \"";
				cerr << strSymbol << "\"" << endl;
				throw Syntax ();
			}
		}
		else
		{
			// Factor := Ident
			if (id == SymbolTable::idNotFound)
			{
				id = _calc.AddSymbol (strSymbol);
			}
			pNode = auto_ptr<Node> (new VarNode (id, _calc.GetStore ()));
		}
	}
	else if (token == tMinus) // unary minus
	{
		_scanner.Accept (); // accept minus
		pNode = auto_ptr<Node> (new UMinusNode (Factor ()));
	}
	else
	{
		_scanner.Accept ();
		throw Syntax ();
	}
	return pNode;
}
