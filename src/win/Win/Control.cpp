// (c) Bartosz Milewski 2000
#include "Control.h"

bool TopController::OnDestroy () throw ()
{
    ::PostQuitMessage (0);
    return true;
}

bool TopController::OnPaint () throw ()
{
	Win::PaintCanvas canvas (_h);
	_view.Paint (canvas, _model.begin (), _model.end ());
	return true;
}

bool TopController::OnMouseMove (int x, int y, Win::KeyState kState) throw ()
{
	Win::UpdateCanvas canvas (_h);
	if (_h.HasCapture ())
	{
		_model.AddPoint (x, y);
		_view.MoveTo (canvas, x, y);
	}
	else
		_view.PrintPos (canvas, x, y);
	return true;
}

bool TopController::OnLButtonDown (int x, int y, Win::KeyState kState) throw ()
{
	_h.CaptureMouse ();
	_model.AddPoint (x, y, true); // starting point
	Win::UpdateCanvas canvas (_h);
	_view.MoveTo (canvas, x, y, false); // don't draw
	return true;
}

bool TopController::OnLButtonUp (int x, int y, Win::KeyState kState) throw ()
{
	// ReleaseMouse will send WM_CAPTURECHANGED
	_h.ReleaseMouse ();
	return true;
}

bool TopController::OnCaptureChanged (HWND hwndNewCapture) throw ()
{
	return true;
}
