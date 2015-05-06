#if !defined (PROCEDURE_H)
#define PROCEDURE_H
// (c) Bartosz Milewski 2000
#include <windows.h>

namespace Win
{

    class CreateData: public CREATESTRUCT
    {
    public:
        void * GetCreationData () const { return lpCreateParams; }
        int GetHeight () const { return cy; }
        int GetWidth () const { return cx; }
        int GetX () const { return x; }
        int GetY () const { return y; }
        char const * GetWndName () const { return lpszName; }
    };

	LRESULT CALLBACK Procedure
		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
}

#endif
