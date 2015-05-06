#if !defined (CONTROL_H)
#define CONTROL_H
// (c) Bartosz Milewski 2000

#include "Controller.h"
#include "Model.h"
#include "View.h"

class TopController: public Win::Controller
{
public:
    bool OnDestroy () throw ();
	bool OnPaint () throw ();
	bool OnMouseMove (int x, int y, Win::KeyState kState) throw ();
	bool OnLButtonDown (int x, int y, Win::KeyState kState) throw ();
	bool OnLButtonUp (int x, int y, Win::KeyState kState) throw ();
	bool OnCaptureChanged (HWND hwndNewCapture) throw ();

private:
	Model	_model;
	View	_view;
};

#endif
