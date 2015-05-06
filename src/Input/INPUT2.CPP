//------------------------------------
//  input2.cpp
//  Member function scope
//  (c) Bartosz Milewski, 1994
//------------------------------------

#include <iostream>
using std::cout;
using std::cin;

class  InputNum
{
public:
	InputNum ()
	{
		cout << "Enter number ";
		cin >> _num;
	}

    int GetValue () const {  return _num; }

	void AddInput ()
	{
		InputNum aNum;
		_num = _num + aNum.GetValue();
	}
		
private:
	int _num;
};

void main()
{
	InputNum num;
	cout << "The value is " << num.GetValue() << "\n";
	num.AddInput();
	cout << "Now the value is " << num.GetValue() << "\n";
}
