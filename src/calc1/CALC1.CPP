//------------------------------------
//  calc1.cpp
//  Stubbed implementation
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

const int maxBuf = 100;

enum Status {
    stOk,
    stQuit,
    stError
};

class Scanner {
public:
    Scanner (char const * buf );
private:
    char const * const _buf;
};

Scanner::Scanner (char const * buf) : _buf (buf) {
    cout << "Scanner with \"" << buf << "\"" << endl;
}

class SymbolTable {
public:
    SymbolTable () {}
};

class Parser {
public:
    Parser (Scanner & scanner, SymbolTable & symTab );
    ~Parser ();
    Status Eval ();
private:
    Scanner &       _scanner;
    SymbolTable &   _symTab;
};

Parser::Parser (Scanner & scanner, SymbolTable & symTab )
    : _scanner (scanner), _symTab (symTab) {
    cout << "Parser created\n";
}

Parser::~Parser () {
    cout << "Destroying parser\n";
}

Status Parser::Eval () {
    cout << "Parser eval\n";
    return stQuit;
}

void main () {
    char buf [maxBuf];
    Status status;
    SymbolTable symTab;
    do {
        cout << "> ";  // prompt
        cin.getline (buf, maxBuf);
        Scanner scanner (buf);
        Parser  parser (scanner, symTab);
        status = parser.Eval ();
    }
    while (status != stQuit);
}


