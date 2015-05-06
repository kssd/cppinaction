//------------------------------------
//  scan.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "scan.h"
#include "symtab.h"

#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>

Scanner::Scanner (std::istream & in)
: _in (in)
{
    Accept ();
	_isEmpty = (Token () == tEnd);
}

void Scanner::ReadChar ()
{
	_look = _in.get ();
	while (_look == ' ' || _look == '\t')
		_look = _in.get ();
}

std::string Scanner::GetSymbolName ()
{
	return _symbol;
}

void Scanner::Accept ()
{
    ReadChar ();

    switch (_look)
    {
    case '+':
        _token = tPlus;
        break;
    case '-':
        _token = tMinus;
        break;
    case '*':
        _token = tMult;
        break;
    case '/':
        _token = tDivide;
        break;
    case '(':
        _token = tLParen;
        break;
    case ')':
        _token = tRParen;
        break;
    case '=':
        _token = tAssign;
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
    {
        _token = tNumber;
		_in.putback (_look);
		_in >> _number;
        break;
    }
    case '\n': // end of input
	case '\r':
	case EOF:
        _token = tEnd;
        break;
    default:
        if (isalpha (_look) || _look == '_')
        {
            _token = tIdent;
			_symbol.erase ();
            do {
				_symbol += _look;
				_look = _in.get ();
            } while (isalnum (_look));
			_in.putback (_look);
        }
        else
            _token = tError;
        break;
    }
}

