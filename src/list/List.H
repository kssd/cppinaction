#if !defined LIST_H
#define LIST_H
//------------------------------------
//  list.h
//  Linked List -- recursive destructor
//  (c) Bartosz Milewski, 1994
//------------------------------------

// stores integer id in a link

class Link
{
public:
    Link (Link * pNext, int id)
        : _pNext (pNext), _id (id) {}
    ~Link ();

    Link *  Next () const { return _pNext; }
    int     Id () const { return _id; }
private:
    Link *      _pNext;
    const int   _id;
};

// Linked list of id's stored in links

class List
{
public:
    List ();
    ~List ();
    void Add (int id);
    Link const * GetHead () const { return _pHead; }
private:
    Link * _pHead;
};

#endif
