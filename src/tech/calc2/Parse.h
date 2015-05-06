#if !defined PARSE_H
#define PARSE_H
//------------------------------------
//  parse.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "tree.h"

enum Status
{
    stOk,
    stQuit,
    stError
};

class Node; // forward declaration
class Scanner;
class Store;
class SymbolTable;
namespace Function
{
	class Table;
}

class Parser
{
public:
    Parser (Scanner & scanner,
        Store & store,
		Function::Table & funTab,
        SymbolTable & symTab );
    ~Parser ();
    Status Parse ();
	double Calculate () const;
private:
    Node * Expr();
    Node * Term();
    Node * Factor();
    void Execute ();

    Scanner &    _scanner;
    Node *       _pTree;
    Status       _status;
    Store &      _store;
	Function::Table &  _funTab;
    SymbolTable &    _symTab;
};
#endif
