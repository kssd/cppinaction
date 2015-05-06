#if !defined PARSE_H
#define PARSE_H
// (c) Bartosz Milewski 2000
#include "tree.h"

class Node; // forward declaration
class Scanner;
class Calculator;

class Parser
{
public:
    Parser (Scanner & scanner, Calculator & calc);
    void Parse ();
	double Calculate () const;
private:
	auto_ptr<Node> Expr();
    auto_ptr<Node> Term();
    auto_ptr<Node> Factor();
    void Execute ();

    Scanner		  & _scanner;
    auto_ptr<Node>	_pTree;
	Calculator	  & _calc;
};
#endif
