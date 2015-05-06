#if !defined PARSE_H
#define PARSE_H
//------------------------------------
//  parse.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "tree.h"
#include "status.h"

class Node; // forward declaration
class Scanner;
class Calculator;

class Parser
{
public:
    Parser (Scanner & scanner, Calculator & calc);
    Status Parse ();
	double Calculate () const;
private:
	auto_ptr<Node> Expr();
    auto_ptr<Node> Term();
    auto_ptr<Node> Factor();
    void Execute ();

    Scanner		  & _scanner;
    auto_ptr<Node>	_pTree;
    Status			_status;
	Calculator	  & _calc;
};
#endif
