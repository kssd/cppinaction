//------------------------------------
//  input.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "input.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cassert>
using namespace std;

// get input from stdin, convert to token

Input::Input ()
{
    cin >> _buf;

    // first char of input is usually enough to decide
    // what token it is

    int c = _buf [0];

    if (isdigit (c))
        _token = tokNumber;
    else if (c == '+' || c == '*' || c == '/')
        _token = c;
    else if (c == '-') // allow entering negative numbers
    {
        if (isdigit (_buf[1]))
            _token = tokNumber;
        else
            _token = c;
    }
    else
        _token = tokError;
}

// call only when token is tokNumber to retrieve numeric value

int Input::Number () const
{
    assert (_token == tokNumber);
    return atoi (_buf);   // convert string to integer
}
