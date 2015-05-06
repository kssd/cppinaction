#if !defined (WIN_H)
#define WIN_H
// (c) Bartosz Milewski 2000
#include <windows.h>

namespace Win
{
    template <class T>
    inline T GetLong (HWND hwnd, int which = GWL_USERDATA)
    {
        return reinterpret_cast<T> (::GetWindowLong (hwnd, which));
    }

    template <class T>
    inline void SetLong (HWND hwnd, T value, int which = GWL_USERDATA)
    {
        ::SetWindowLong (hwnd, which, reinterpret_cast<long> (value));
    }

	class Dow
	{
	public:
		Dow (HWND h = 0) : _h (h) {}
		void Init (HWND h) { _h = h; }
		operator HWND () const { return _h; }
#if 0 // if compiler supports member templates
		template <class T>
		inline T GetLong (int which = GWL_USERDATA)
		{
			return reinterpret_cast<T> (::GetWindowLong (_h, which));
		}

		template <class T>
		inline void SetLong (T value, int which = GWL_USERDATA)
		{
			::SetWindowLong (_h, which, reinterpret_cast<long> (value));
		}
#endif
		void CaptureMouse ()
		{
			::SetCapture (_h);
		}
		void ReleaseMouse ()
		{
			if (HasCapture ())
				::ReleaseCapture ();
		}
		bool HasCapture () const
		{
			return ::GetCapture () == _h;
		}
		// Window visibility
		void Show (int cmdShow = SW_SHOW) 
		{ 
			::ShowWindow (_h, cmdShow); 
		}
		void Hide () 
		{ 
			::ShowWindow (_h, SW_HIDE); 
		}
		void Update () 
		{ 
			::UpdateWindow (_h); 
		}
		void Display (int cmdShow)
		{
			Show (cmdShow);
			Update ();
		}
	private:
		HWND _h;
	};
}
#endif
