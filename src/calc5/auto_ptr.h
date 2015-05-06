#if !defined AUTO_PTR_H
#define AUTO_PTR_H
//------------------------------------
//  auto_ptr
//  This file is for reference only
//  (c) Bartosz Milewski, 1998
//------------------------------------
	
template<class T>
class auto_ptr
{
	template<class U> struct auto_ptr_ref
	{
		auto_ptr<U> & _ap;
		auto_ptr_ref (auto_ptr<U> & p) : _ap (p) {}
	};
public:
	typedef T element_type;

	explicit auto_ptr (T * p = 0) : _p (p) {}
	// "transfer" constructor
	auto_ptr (auto_ptr & pSrc)
	{
		_p = pSrc._p;
		pSrc._p = 0;
	}

	auto_ptr & operator= (auto_ptr & pSrc)
	{
		if (this != &pSrc)
		{
			_p = pSrc._p;
			pSrc._p = 0;
		}
		return *this;
	}
	// "transfer" from derived class
	template<class U> 
	auto_ptr (auto_ptr<U> & pSrc)
	{
		_p = pSrc.release ();
	}

	// assignment of derived class
	template<class U> 
	auto_ptr & operator= (auto_ptr<U> & pSrc)
	{
		if (this != &pSrc)
			_p = pSrc.release ();
		return *this;
	}

	~auto_ptr () 
	{ 
		delete _p; 
	}

	T & operator* () const { return *_p; }

	T * operator-> () const { return _p; }

	T * get () const { return _p; }

	T * release ()
	{
		T * tmp = _p;
		_p = 0;
		return tmp;
	}

	void reset (T * p = 0)
	{
		if (p != _p)
		{
			delete _p;
			_p = p;
		}
	}

	auto_ptr (auto_ptr_ref<T> apr)
		: _p (apr._ap.release ())
	{}

	template<class U>
	operator auto_ptr_ref<U> ()
	{
		return auto_ptr_ref<U> (*this);
	}

	template<class U>
	operator auto_ptr<U> ()
	{
		return auto_ptr<U> (release ());
	}
private:
	T * _p;
};

#endif