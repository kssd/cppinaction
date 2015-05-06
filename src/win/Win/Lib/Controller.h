#if !defined (CONTROLLER_H)
#define CONTROLLER_H
// (c) Bartosz Milewski 2000
#include "Win.h"
#include "Mouse.h"

namespace Win
{
    class Controller
    {
        friend LRESULT CALLBACK Procedure (HWND hwnd, 
                        UINT message, WPARAM wParam, LPARAM lParam);

        void SetWindowHandle (HWND hwnd) { _h.Init (hwnd); }
    public:
		virtual ~Controller () {}
        virtual bool OnDestroy () throw ()
			{ return false; }
		virtual bool OnPaint () throw ()
			{ return false; }
		virtual bool OnMouseMove (int x, int y, KeyState kState) throw ()
			{ return false; }
		virtual bool OnLButtonDown (int x, int y, KeyState kState) throw ()
			{ return false; }
		virtual bool OnLButtonUp (int x, int y, KeyState kState) throw ()
			{ return false; }
		virtual bool OnCaptureChanged (HWND hwndNewCapture) throw ()
			{ return false; }
    protected:
		Win::Dow  _h;
    };
}
#endif
