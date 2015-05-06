#if !defined VLIST_H
#define VLIST_H
//------------------------------------
//  vlist.h
//  (c) Bartosz Milewski, 1994
//------------------------------------
// stores integer id in a link
class Link
{
public:
    Link (Link * pNext, int id)
    : _pNext (pNext), _id (id) {}

    Link *  Next () const { return _pNext; }
    int     Id () const { return _id; }
private:
    Link *  _pNext;
    int     _id;
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

// List sequencer
// Usage:>
// for (ListSeq seq (list);
//      !seq.AtEnd ();
//      seq.Advance ())
// {
//      int id = seq.GetId ();
//        ...
// }

class ListSeq
{
public:
    ListSeq (List const & list)
        : _pLink (list.GetHead ()) {}
    bool AtEnd () const { return _pLink == 0; }
    void Advance () { _pLink = _pLink->Next (); }
    int GetId () const { return _pLink->Id (); }
private:
    Link const * _pLink; // current link
};
 
#endif
