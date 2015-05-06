//------------------------------------
//  parse.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "scan.h"
#include "parse.h"
#include "symtab.h"
#include "store.h"
#include "funtab.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

const int maxBuf = 100;
const int maxSymbols = 40;

void main ()
{
    // Notice all these local objects.
    // A clear sign that there should be
    // a top level object, say, the Calculator.
    // Back to the drawing board!

    char buf [maxBuf];
    Status status;
    SymbolTable symTab (maxSymbols);
    FunctionTable funTab (symTab);
    Store store (maxSymbols, symTab);

	cerr << "\nEnter empty line to quit\n";
    do
    {
        cerr << "> ";  // prompt
        cin.getline (buf, maxBuf);
        Scanner scanner (buf);
		if (!scanner.IsEmpty ())
		{
			Parser  parser (scanner, store, funTab, symTab);
			status = parser.Parse ();
			if (status == stOk)
			{
				double result = parser.Calculate ();
				cout << result << endl;
			}
			else
			{
				cerr << "Syntax error.\n";
			}
		}
		else
		{
			break;
		}
    } while (status != stQuit);
}
