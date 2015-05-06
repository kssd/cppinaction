//------------------------------------
//  parse.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "scan.h"
#include "parse.h"
#include "calc.h"
#include "CmdParser.h"
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

		Status status;
		Calculator calc;

		cerr << "\n!q to quit\n";
		do
		{
			cerr << "> ";  // prompt
			Scanner scanner (cin);

			if (!scanner.IsEmpty ())
			{
				if (scanner.IsCommand())
				{
					CommandParser parser (scanner, calc);
					status = parser.Execute ();
				}
				else
				{
					Parser  parser (scanner, calc);
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
