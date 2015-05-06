// (c) Bartosz Milewski 2000
#include "Icon.h"

using namespace Win;

void Icon::Load (HINSTANCE res, int id, int dx, int dy, unsigned flag)
{
    _h = reinterpret_cast<HICON> (
        ::LoadImage (res, 
                     MAKEINTRESOURCE (id), 
                     IMAGE_ICON, 
                     dx, dy, 
                     flag));
    if (_h == 0)
        throw "Icon load image failed";
}

Icon::~Icon ()
{
    ::DestroyIcon (_h);
}

void SmallIcon::Load (HINSTANCE res, int id)
{
    Icon::Load (res, id, 
            ::GetSystemMetrics (SM_CXSMICON),
            ::GetSystemMetrics (SM_CYSMICON));
}

void StdIcon::Load (HINSTANCE res, int id)
{
    Icon::Load (res, id, 
            ::GetSystemMetrics (SM_CXICON),
            ::GetSystemMetrics (SM_CYICON));
}
