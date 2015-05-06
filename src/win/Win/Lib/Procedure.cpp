// (c) Bartosz Milewski 2000
#include "Procedure.h"
#include "Controller.h"
#include "Win.h"
#include "Mouse.h"

LRESULT CALLBACK Win::Procedure (HWND hwnd, 
                                 UINT message, 
                                 WPARAM wParam, 
                                 LPARAM lParam)
{
    Controller * pCtrl = Win::GetLong<Controller *> (hwnd);
    switch (message)
    {
    case WM_NCCREATE:
        {
            CreateData const * create = 
                reinterpret_cast<CreateData const *> (lParam);
            pCtrl = static_cast<Controller *> (create->GetCreationData ());
            pCtrl->SetWindowHandle (hwnd);
            Win::SetLong<Controller *> (hwnd, pCtrl);
        }
        break;
	case WM_CREATE:
		break;
    case WM_DESTROY:
        // We're no longer on screen
        pCtrl->OnDestroy ();
        return 0;
	case WM_PAINT:
		if (pCtrl->OnPaint ())
			return 0;
        break;
	case WM_MOUSEMOVE:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnMouseMove (p.x, p.y, kState))
				return 0;
		}
        break;
	case WM_LBUTTONDOWN:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonDown (p.x, p.y, kState))
				return 0;
		}
        break;
	case WM_LBUTTONUP:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonUp (p.x, p.y, kState))
				return 0;
		}
        break;
	case WM_CAPTURECHANGED:
		if (pCtrl->OnCaptureChanged (reinterpret_cast<HWND> (lParam)))
			return 0;
        break;
    }
    return ::DefWindowProc (hwnd, message, wParam, lParam);
}

