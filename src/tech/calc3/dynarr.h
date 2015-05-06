#if !defined DYN_ARRAY_H
#define DYN_ARRAY_H
//------------------------------------
//  (c) Bartosz Milewski, 1994
//------------------------------------
#include <cassert>

template <class T> 
class DynArray
{
    enum { initDynArray = 8 };
public:
    explicit DynArray (T const valDefault);
    ~DynArray ();
    void Add (int i, T const val);
    T operator [] (int i) const;
    T & operator [] (int i);
    int InRange (int i) const { return i < _capacity; }
private:
    void Grow (int i);

    T	  * _arr;
    int		_capacity; // size of the array
    T const _valDefault;
};

template <class T>
DynArray <T>::DynArray (T const valDefault)
    : _capacity (initDynArray), _valDefault (valDefault)
{
    _arr = new T [initDynArray]; // allocate memory
    for (int i = 0; i < initDynArray; ++i)
        _arr[i] = _valDefault;
}

template <class T>
DynArray <T>::~DynArray ()
{
    delete []_arr;
}

template <class T>
void DynArray <T>::Add (int i, T const val)
{
    if ( i >= _capacity )
        Grow(i);
    _arr [i] = val;
}

template <class T>
inline T DynArray<T>::operator [] (int i) const
{
    assert (i < _capacity);
    return _arr[i];
}

template <class T>
inline T & DynArray<T>::operator [] (int i)
{
    assert (i < _capacity);
    return _arr[i];
}

// private method
template <class T>
void DynArray <T>::Grow (int idxMax)
{
    int newSize = 2 * _capacity;
    if (idxMax >= newSize)
        newSize = idxMax + 1;
    // allocate new array
    T * arrNew = new T [newSize];
    // copy all entries
    int i;
    for (i = 0; i < _capacity; ++i)
        arrNew [i] = _arr [i];
    for (; i < newSize; ++i)
        arrNew [i] = _valDefault;
    _capacity = newSize;
    // free old memory
    delete []_arr;
    // substitute new array for old array
    _arr = arrNew;
}

#endif