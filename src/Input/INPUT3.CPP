//------------------------------------
//  input3.cpp
//  String arguments
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class  InputNum
{
public:
	InputNum (char msg [])
	{
		cout << msg;
		cin >> _num;
	}

    int GetValue () const {  return _num; }

	void AddInput (char msg [])
	{
		InputNum aNum (msg);
		_num = GetValue () + aNum.GetValue ();
	}
		
private:
	int _num;
};

char SumString[] = "The sum is   ";

void main()
{
	InputNum num ("Enter number ");
	num.AddInput ("Another one  ");
	num.AddInput ("One more     ");
	cout << SumString << num.GetValue () << endl;
}
