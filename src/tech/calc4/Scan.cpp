//------------------------------------
//  scan.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "scan.h"
#include "symtab.h"
#include "params.h"

#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>
using std::cerr;

Scanner::Scanner (char const * buf)
: _buf (buf), _iLook (0), _iSymbol (0), _lenSymbol (0)
{
    Accept ();
}

void Scanner::EatWhite ()
{
    while (isspace (_buf[_iLook]))
        ++_iLook;
}

int Scanner::GetSymbolName (char * strOut, int lenBuf)
{
    assert (lenBuf > maxSymLen);
    assert (_lenSymbol < lenBuf);

    strncpy (strOut, &_buf [_iSymbol], _lenSymbol);
    strOut [_lenSymbol] = 0;
    return _lenSymbol;
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
        _iLook = p - _buf;
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
			if (_lenSymbol > maxSymLen)
			{
				cerr << "Warning: Variable name truncated\n";
				_lenSymbol = maxSymLen;
			}
        }
        else
            _token = tError;
        break;
    }
    return Token ();
}

