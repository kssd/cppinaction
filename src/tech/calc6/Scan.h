#if !defined SCAN_H
#define SCAN_H
//------------------------------------
//  scan.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
#pragma warning (disable:4786)
#include <string>
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
	Scanner (std::string const & buf);
	bool IsDone () const { return _iLook == std::string::npos; }
	bool IsEmpty () const { return _buf.length () == 0; }
	EToken	Token () const { return _token; }
	EToken	Accept ();
	std::string GetSymbolName ();
	double Number ()
	{
		assert (_token == tNumber);
		return _number;
	}
private:
	void EatWhite ();
	typedef std::string::size_type size_type;

	std::string const & _buf;
	size_type 			_iLook;
	EToken				_token;
	double				_number;
	size_type 			_iSymbol;
	size_type 			_lenSymbol;
	static char			_whiteChars [];
};
#endif
