#if !defined (UTIL_H)
#define UTIL_H
// (c) Bartosz Milewski 2000

#include <string>
#include <sstream>

template<class T>
inline std::string ToString (T & val)
{
	std::stringstream out;
	out << val;
	return out.str ();
}

#endif
