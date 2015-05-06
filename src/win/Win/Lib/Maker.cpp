// (c) Bartosz Milewski 2000

#include "Maker.h"
#include <cassert>

using namespace Win;

Maker::Maker (char const * className, HINSTANCE hInst)
  : _style (WS_OVERLAPPEDWINDOW),
    _exStyle (0),
    _className (className),
    _x (CW_USEDEFAULT), // horizontal position of window
    _y (0),             // vertical position of window
    _width (CW_USEDEFAULT), // window width  
    _height (0),        // window height
    _hWndParent (0),    // handle to parent or owner window
    _hMenu (0),         // handle to menu, or child-window identifier
    _data (0),          // pointer to window-creation data
	_hInst (hInst)
{
}

HWND Maker::Create (Controller & controller, char const * title)
{
	HWND hwnd = ::CreateWindowEx (
		_exStyle,
		_className,
		title,
		_style,
		_x,
		_y,
		_width,
		_height,
		_hWndParent,
		_hMenu,
		_hInst,
		&controller);

	if (hwnd == 0)
		throw "Internal error: Window Creation Failed.";
	return hwnd;
}

