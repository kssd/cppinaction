//------------------------------------
//  calc.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include "calc.h"
#include "input.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

// Act depending on input:
// if it's a number, push it on the stack,
// if it's a binary operator, pop two numbers ,
// execute the operation and push the result.
// Returns true if success, false if error.

bool Calculator::Execute (Input const & input) {
    int token = input.Token ();
    bool status = false; // assume failure

    if (token == tokError) {
        cout << "Unknown token\n";
    } else if (token == tokNumber) {
        if (_stack.IsFull ()) {
            cout << "Stack is full\n";
        }
        else {
            _stack.Push (input.Number());
            status = true;
        }
    }
    else {
        assert (token == '+' || token == '-'
                || token == '*' || token == '/');

        if (_stack.IsEmpty()) {
            cout << "Stack is empty\n";
        }
        else {
            int num2 = _stack.Pop ();
            int num1;

            // Special case when only one number on the stack:
            // use this number for both operands.

            if ( _stack.IsEmpty () )
                num1 = num2;
            else
                num1 = _stack.Pop ();

            _stack.Push (Calculate (num1, num2, token));
            status = true;
        }
    }
    return status;
}

// Private method used to perform binary operation on operands

int Calculator::Calculate (int num1, int num2, int token) const {
    int result;

    if (token == '+')
        result = num1 + num2;
    else if (token == '-')
        result = num1 - num2;
    else if (token == '*')
        result = num1 * num2;
    else if (token == '/') {
        if (num2 == 0) {
            cout << "Division by zero\n";
            result = 0;
        }
        else
            result = num1 / num2;
    }
    return result;
}

void main () {
    Calculator TheCalculator;
    bool status;
    do {
        // Prompt for input
        cout << "> ";
        Input input;
        status = TheCalculator.Execute (input);
        if (status) {
            for (StackSeq seq (TheCalculator.GetStack ());
                    !seq.AtEnd ();
                    seq.Advance () ) {
                cout << "    " << seq.GetNum () << endl;
            }
        }
    }
    while (status);
}


