//------------------------------------
//  list.cpp
//  (c) Bartosz Milewski, 1996
//------------------------------------

#include "list.h"

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

Link::~Link ()
{
    cout << "Delete " << _id << endl;
    delete _pNext;  // <- recursion
}

List::List ()
    : _pHead(0)
{}

List::~List ()
{
    delete _pHead;
}

void List::Add (int id)
{
    // add in front of the list
    Link * pLink = new Link (_pHead, id);
    _pHead = pLink;
}


void main ()
{
    List list;
    list.Add (1);
    list.Add (2);
    cout << "Deleting the list\n";
}
