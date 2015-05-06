//------------------------------------
//  vlist.cpp
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include "vlist.h"

List::List ()
    : _pHead(0)
{}

List::~List ()
{
    // free linked list
    while (_pHead != 0)
    {
        Link * pLink = _pHead;
        _pHead = _pHead->Next();
        delete pLink;
    }
}

void List::Add (int id)
{
    // add in front of the list
    Link * pLink = new Link (_pHead, id);
    _pHead = pLink;
}

