// (c) Bartosz Milewski 2000
#include "Class.h"
#include "Maker.h"
#include "Procedure.h"
#include "Control.h"
#include "resource.h"

int WINAPI WinMain
   (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
    char className[] = "Simpleton";
	Win::ClassMaker winClass (className, hInst);
	winClass.SetIcons (IDI_MAIN);
	winClass.SetBkColor (128, 128, 255);
    winClass.Register ();
	Win::Maker win (className, hInst);
	TopController ctrl;
	Win::Dow h = win.Create (ctrl, "Simpleton");
    h.Display (cmdShow);

    // Message loop
    MSG  msg;
	int status;
    while ((status = ::GetMessage (& msg, 0, 0, 0)) != 0)
    {
        if (status == -1)
            return -1;
        ::DispatchMessage (& msg);
    }
    return msg.wParam;
}

