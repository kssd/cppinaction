#include "Control.h"
// (c) Bartosz Milewski 2000
#include "scan.h"
#include "parse.h"
#include "Params.h"
#include "util.h"
#include "Exception.h"
#include <sstream>

bool TopController::OnDestroy () throw ()
{
    ::PostQuitMessage (0);
    return true;
}

bool TopController::OnCreate (Win::CreateData const * create) throw ()
{
	try
	{
		TheOutput.Init (_h);
		// create a Commander to execute commands
		//_commander.reset (new Commander (_h));
		_commander = std::auto_ptr<Commander> (new Commander (_h, _calc));
		// Create a command vector based on global Cmd::Table and Commander
		//_cmdVector.reset (new CmdVector (Cmd::Table, _commander.get ()));
		_cmdVector = auto_ptr<CmdVector> (new CmdVector (Cmd::Table, _commander.get ()));
		// Create a view which contains a menu
		//_view.reset(new View (_h, _cmdVector.get (), _calc));
		_view = auto_ptr<View>(new View (_h, _cmdVector.get (), _calc));
		// view must be fully constructed before calling these
		_view->Init (_h);
		_view->UpdateMemory ();
		_view->SetStatus ("Ready");
	}
	catch (...)
	{
		TheOutput.Error ("Internal Error:\nFailure to initialize.");
	}
	return true;
}

bool TopController::OnFocus (Win::Dow winPrev) throw ()
{
	_view->SetFocus ();
	return true;
}

bool TopController::OnSize (int width, int height, int flags) throw ()
{
	if (flags != SIZE_MINIMIZED)
	{
		_view->Size (width, height);
		_view->ReDisplayMemory (); // changed column size
	}
	return true;
}

bool TopController::OnCommand (int cmdId, bool isAccel) throw ()
{
	try
	{
		_cmdVector->Execute (cmdId);
		_view->UpdateMemory ();
	}
	catch (Win::ExitException)
	{
		_h.Destroy ();
	}
	catch (Win::Exception const & e)
	{
		TheOutput.Error (e.GetMessage ());
	}
	catch (...)
	{
		TheOutput.Error ("Internal error");
	}
	return true;
}


bool TopController::OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
{
	if (controlId == IDOK)
	{
		try
		{
			std::string expr = _view->GetInput ();
			std::istringstream in (expr);
			Scanner scanner (in);
			Parser  parser (scanner, _calc);
			parser.Parse ();
			double result = parser.Calculate ();
			_view->UpdateHistory (expr, result);
			_view->UpdateMemory ();
			std::ostringstream out;
			out << result;
			std::string strOut = out.str ();
			_view->SetResult (strOut.c_str ());
		}
		catch (Syntax const & err)
		{
			TheOutput.Error (err.GetString ());
			_view->SetResult ("");
		}
		return true;
	}
	return false;
}

bool TopController::OnInitPopup (HMENU menu, int pos) throw ()
{
	try
	{
		_view->RefreshPopup (menu, pos);
	}
	catch (...) 
	{}
	return true;
}

bool TopController::OnMenuSelect (int id, int flags, HMENU menu) throw ()
{
	if (flags == 0xffff)
	{
		// menu dismissed
		_view->SetStatus ("Ready");
		return true;
	}
	if ((flags & MF_SEPARATOR) || (flags & MF_SYSMENU))
	{
		return false;
	}
	if (!(flags & MF_POPUP))
	{
		// menu item selected
		_view->SetStatus (_cmdVector->GetHelp (id));
		return true;
	}
	return false;
}

bool TopController::OnUserMessage ( UINT msg, 
									WPARAM wParam, 
									LPARAM lParam, 
									LRESULT & result) throw ()
{
	if (msg == MSG_MEMCLEAR)
	{
		_view->ClearMemory ();
		return true;
	}
	return false;
}


