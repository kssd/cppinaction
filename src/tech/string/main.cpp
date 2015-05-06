//------------------------------------
//  (c) Bartosz Milewski, 1998
//------------------------------------
#include "SimpStr.h"
#include <iostream>
using std::cout;
using std::endl;

typedef StringCow String;

String ByValue ()
{
	String ret ("by value");
	return ret;
}

void main ()
{
	String str1 (0);
	String str2 (str1);
	str1 = "first string";
	str2 = ByValue ();
	String str3 = str1;
	String str4 = str3;
	str4.Upcase ();
	str1.Upcase ();
	cout << str1.c_str () << endl;
	cout << str2.c_str () << endl;
	cout << str3.c_str () << endl;
	cout << str4.c_str () << endl;
}
