#if !defined STACK_H
#define STACK_H
//------------------------------------
//  stack.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

const int initStack = 1;

class IStack
{
public:
    IStack ();
    ~IStack ();
    void Push (int i);
    int  Pop ();
    int  Top () const;
    bool IsEmpty () const;
private:
    void Grow ();

    int* _arr;
    int  _capacity; // size of the array
    int  _top;
};

#endif
