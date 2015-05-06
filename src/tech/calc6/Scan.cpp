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
#include <iostream>
using std::cerr;

char Scanner::_whiteChars [] = " \t\n\r";

Scanner::Scanner (std::string const & buf)
: _buf (buf), _iLook (0), _iSymbol (0), _lenSymbol (0)
{
    Accept ();
}

void Scanner::EatWhite ()
{
	_iLook = _buf.find_first_not_of (_whiteChars, _iLook);
}

std::string Scanner::GetSymbolName ()
{
	return _buf.substr (_iSymbol, _lenSymbol);
}

EToken Scanner::Accept ()
{
    EatWhite ();
    switch (_buf[_iLook])
    {
    case '+':
        _token = tPlus;
        ++_iLook;
        break;
    case '-':
        _token = tMinus;
        ++_iLook;
        break;
    case '*':
        _token = tMult;
        ++_iLook;
        break;
    case '/':
        _token = tDivide;
        ++_iLook;
        break;
    case '(':
        _token = tLParen;
        ++_iLook;
        break;
    case ')':
        _token = tRParen;
        ++_iLook;
        break;
    case '=':
        _token = tAssign;
        ++_iLook;
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
    {
        _token = tNumber;
        char * p;
        _number = strtod (&_buf [_iLook], &p);
        _iLook = p - &_buf [0];
        break;
    }
    case 0: // end of input
        _token = tEnd;
        break;
    default:
        if (isalpha (_buf [_iLook]) || _buf [_iLook] == '_')
        {
            _token = tIdent;
            _iSymbol = _iLook;
            do {
                ++_iLook;
            } while (isalnum (_buf [_iLook]));

            _lenSymbol = _iLook - _iSymbol;
        }
        else
            _token = tError;
        break;
    }
	if (_iLook == _buf.length ())
		_iLook = std::string::npos;
    return Token ();
}

