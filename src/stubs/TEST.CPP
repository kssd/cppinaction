//------------------------------------
//  test.cpp
//  Stubbed implementation
//  of the calculator
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <iostream>
using std::cout;
using std::endl;

class IStack {};

class StackSeq
{
public:
    StackSeq (IStack const & stack ): _stack (stack), _done (false)
    {
        cout << "Stack sequencer created\n";
    }
    bool AtEnd () const { return _done; }
    void Advance () { _done = true; }
    int GetNum () const { return 13; }
private:
    IStack const &	_stack;
    bool			_done;
};

class Input
{
public:
    Input ()
    {
        cout << "Input created\n";
    }
};

class Calculator
{
public:
    Calculator () : _done (false)
    {
        cout << "Calculator created\n";
    }
    bool Execute (Input & input)
    {
        cout << "Calculator::Execute\n";
        return !_done;
    }
    IStack const & GetStack ()
    {
        _done = true;
        return _stack;
    }
private:
    IStack  _stack;
    bool    _done;
};

void main ()
{
    Calculator TheCalculator;
    bool status;
    do
    {
        // Prompt for input
        cout << "> ";
        Input input;
        status = TheCalculator.Execute (input);
        if ( status )
        {
             for (StackSeq seq (TheCalculator.GetStack ());
                   !seq.AtEnd ();
                    seq.Advance () )
             {
                 cout << "    " << seq.GetNum () << endl;
             }
        }
    } while (status);
}
