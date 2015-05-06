//------------------------------------
//  parse.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "scan.h"
#include "parse.h"
#include "symtab.h"
#include "store.h"
#include "funtab.h"
#include "params.h"

#include <new.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

class bad_alloc {};

int NewHandler (size_t size)
{
    throw bad_alloc ();
    return 0;
}

void main ()
{
	_set_new_handler (NewHandler);
	try
	{
		// Notice all these local objects.
		// A clear sign that there should be
		// a top level object, say, the Calculator.
		// Back to the drawing board!

		char buf [maxBuf+1];
		Status status;
		SymbolTable symTab;
		Function::Table funTab (symTab);
		Store store (symTab);

		cerr << "\nEnter empty line to quit\n";
		do
		{
			cerr << "> ";  // prompt
			cin.getline (buf, maxBuf+1);

			if (strlen (buf) == maxBuf)
			{    
				cerr << "Error: Input buffer overflow\n";
				status = stError;
				break;
			}
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
	catch (bad_alloc)
	{
		cerr << "Out of memory!\n";
	}
	catch (...)
	{
		cerr << "Internal error\n";
	}
}
