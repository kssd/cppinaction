//------------------------------------
//  value.cpp
//  Class passed by value
//  (c) Bartosz Milewski, 1994, 1998
//------------------------------------

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
using std::cout;
using std::endl;
using std::stringstream;
using std::ends;

class Value
{
public:
    Value ()
    {
        cout << "  Default constructor\n";
		_numString = new char [1];
		_numString [0] = '\0';
    }

    Value (int i)
    {
        cout << "  Construction/conversion from int " << i << endl;

		stringstream buffer;
		buffer << i << ends; // terminate string
		Init (buffer.str ().c_str ());
		Display ();
    }

    Value (Value const & v)
    {
        cout << "  Copy constructor ( " << v._numString << " )\n";
		Init (v._numString);
		Display ();
    }

    Value & operator= (Value const & v)
    {
        cout << "  Operator = ( " << v._numString << " )\n";
		if (_numString != v._numString)
		{
			delete _numString;
			Init (v._numString);
		}
		Display ();
        return *this;
    }

    friend Value operator+ (Value const & v1, Value const & v2 );
 
private:
	void Init (char const * buf)
	{
		int len = strlen (buf);
		_numString = new char [len + 1];
		strcpy (_numString, buf);
	}

	void Display ()
	{
		cout << "\t" << _numString << endl;
	}

    char * _numString;
};

inline Value operator+ (Value const & v1, Value const & v2 )
{
    cout << "  Operator + (" << v1._numString << ", " << v2._numString << ")\n";
	stringstream buffer;
	buffer << v1._numString << " + " << v2._numString << ends;
	Value result;
	result.Init (buffer.str ().c_str ());
	cout << "  Returning by value\n";
	return result;
}

void main ()
{
    cout << "Value v1 (1);\n";
    Value v1 (1);
    cout << "Value v2 = 2;\n";
    Value v2 = 2;
    cout << "Value v3;\n";
    Value v3;
    cout << "v3 = 3;\n";
    v3 = 3;
    cout << "v3 = v1 + v3;\n";
    v3 = v1 + v3;
    cout << "v3 = v3 + 1;\n";
    v3 = v3 + 1;
}
