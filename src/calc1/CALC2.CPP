//------------------------------------
//  calc2.cpp
//  Implementing some stubs
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <cctype>
#include <cstdlib>
#include <cassert>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

const int maxBuf = 100;

enum Status
{
    stOk,
    stQuit,
    stError
};

enum EToken
{
    tEnd,
    tError,
    tNumber,
    tPlus,
    tMult
};

class Scanner
{
public:
    Scanner (char const * buf);
    EToken  Token () const { return _token; }
    EToken  Accept ();
    double Number ()
    {
        assert (_token == tNumber);
        return _number;
    }
private:
    void EatWhite ();

    char const * const  _buf;
    int                 _iLook;
    EToken              _token;
    double              _number;
};

Scanner::Scanner (char const * buf )
: _buf (buf), _iLook (0)
{
    cout << "Scanner with \"" << buf << "\"" << endl;
    Accept ();
}

void Scanner::EatWhite ()
{
    while (isspace (_buf [_iLook]))
        _iLook++;
}

EToken Scanner::Accept ()
{
    EatWhite ();
    switch (_buf [_iLook])
    {
    case '+':
        _token = tPlus;
        _iLook++;
        break;
    case '*':
        _token = tMult;
        _iLook++;
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        _token = tNumber;
        _number = atoi (&_buf [_iLook]);
        while (isdigit (_buf [_iLook]))
            _iLook++;
        break;
    case 0: // end of input
        _token = tEnd;
        break;
    default:
        _token = tError;
        break;
    }
    return Token ();
}


class SymbolTable
{
public:
    SymbolTable () {}
};

class Parser
{
public:
    Parser (Scanner & scanner, SymbolTable & symTab);
    ~Parser ();
    Status Eval ();
private:
    Status Parse ();
    void Execute ();

    Scanner &        _scanner;
    SymbolTable &    _symTab;
};

Parser::Parser (Scanner & scanner, SymbolTable & symTab)
: _scanner (scanner), _symTab (symTab)
{
    cout << "Parser created\n";
}

Parser::~Parser ()
{
    cout << "Destroying parser\n";
}

Status Parser::Eval ()
{
    cout << "Parser eval\n";
    Status status = Parse ();
    if (status == stOk)
        Execute ();
    return status;
}

void Parser::Execute ()
{
    cout << "Execute\n";
}

Status Parser::Parse ()
{
    for (EToken token = _scanner.Token ();
        token != tEnd;
        token = _scanner.Accept ())
    {
        switch (token)
        {
        case tMult:
            cout << "Times\n";
            break;
        case tPlus:
            cout << "Plus\n";
            break;
        case tNumber:
            cout << "Number: " << _scanner.Number () << "\n";
            break;
        case tError:
            cout << "Error\n";
            return stQuit;
        default:
            cout << "Error: bad token\n";
            return stQuit;
        }
    }
    return stOk;
}

void main ()
{
    char buf [maxBuf];
    Status status;
    SymbolTable symTab;
    do
    {
        cout << "> ";  // prompt
        cin.getline (buf, maxBuf);
        Scanner scanner (buf);
        Parser  parser (scanner, symTab);
        status = parser.Eval ();
    } while (status != stQuit);
}
