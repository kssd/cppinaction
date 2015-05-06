#if !defined VLIST_H
#define VLIST_H
//------------------------------------
//  vlist.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

template<class T>
class List
{
public:
    List ();
    ~List ();
    void Add (T value);
private:
	class Link
	{
	public:
		Link (Link * pNext, T value)
			: _pNext (pNext), _value (value) {}

		Link *  Next () const { return _pNext; }
		T       GetValue () const { return _value; }
	private:
		Link *  _pNext;
		T       _value;
	};

public:
	class Seq
	{
	public:
		Seq (List const & list)
			: _pLink (list.GetHead ()) {}
		bool AtEnd () const { return _pLink == 0; }
		void Advance () { _pLink = _pLink->Next (); }
		T GetValue () const { return _pLink->GetValue (); }
	private:

		Link const * _pLink; // current link
	};

	friend Seq;
private:
    Link const * GetHead () const { return _pHead; }

    Link * _pHead;
};

template<class T>
List<T>::List ()
    : _pHead(0)
{}

template<class T>
List<T>::~List ()
{
    // free linked list
    while (_pHead != 0)
    {
        Link * pLink = _pHead;
        _pHead = _pHead->Next();
        delete pLink;
    }
}

template<class T>
void List<T>::Add (T value)
{
    Link * pLink = new Link (_pHead, value);
    _pHead = pLink;
}

#endif
