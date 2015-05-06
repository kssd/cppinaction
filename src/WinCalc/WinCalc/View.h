#if !defined (VIEW_H)
#define VIEW_H
// Bartosz Milewski (c) 2000
#include "MenuTable.h"
#include "StatusBar.h"
#include "ListBox.h"
#include "Edit.h"
#include "Win.h"
class Calculator;

class EditController: public Win::SubController
{
public:
	bool OnKeyDown (int vKey, int flags) throw ();
};

class View
{
public:
	View (Win::Dow winTop, Cmd::Vector * cmdVector, Calculator & calc);
	void Init (Win::Dow winTop);
	void Size (int width, int height);
	std::string GetInput ()
	{
		return _edit.GetText ();
	}
	void SetResult (char const * str);
	void UpdateMemory ();
	void ReDisplayMemory ();
	void ClearMemory () { _memoryView.Clear (); }
	void UpdateHistory (std::string const & str, double result);
	void RefreshPopup (HMENU menu, int pos)
	{
		_menu.RefreshPopup (menu, pos);
	}
	void SetStatus (char const * str);
	void SetFocus ()
	{
		_edit.SetFocus ();
	}
private:
	std::string FormatMemoryString (int id);
private:
	int _charWidth, _charHeight;
	int _wValue;		// width in pixels of value field
	int _varNameChars;  // width in chars of name field

	Menu::DropDown	_menu;
	Win::StatusBar	_status;

	Win::ListBox	_historyView;
	Win::ListBox	_memoryView;
	Win::Edit		_edit;
	Win::Edit		_result;

	EditController	_editCtrl;

	Calculator	  & _calc;
};
#endif
