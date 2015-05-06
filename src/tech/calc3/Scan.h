#if !defined SCAN_H
#define SCAN_H
//------------------------------------
//  scan.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <cassert>

enum EToken
{
    tEnd,
    tError,
    tNumber,
    tPlus,
    tMult,
    tMinus,
    tDivide,
    tLParen,
    tRParen,
    tAssign,
    tIdent
};

class Scanner
{
public:
    Scanner (char const * buf);
	bool IsDone () const { return _buf [_iLook] == '\0'; }
	bool IsEmpty () const { return _buf [0] == '\0'; }
    EToken  Token () { return _token; }
    EToken  Accept ();
    int GetSymbolName (char * strOut, int lenBuf);
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
    int                 _iSymbol;
    int                 _lenSymbol;
};
#endif
