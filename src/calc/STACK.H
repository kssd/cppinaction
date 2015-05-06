#if !defined STACK_H
#define STACK_H
//------------------------------------
//  stack.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

const int maxStack = 16;

class IStack
{
    friend class StackSeq; // give it access to private members
public:
    IStack (): _top (0) {}
    void Push ( int i );
    int  Pop ();
    int  Top () const;
    bool IsFull () const;
    bool IsEmpty () const;
private:
    int _arr [maxStack];
    int _top;
};

class StackSeq
{
public:
    StackSeq (IStack const & stack);
    int AtEnd () const;
    void Advance ();
    int GetNum () const;
private:
    IStack const & _stack;  // reference to stack
    int     _iCur;   // current index into stack
};
#endif
