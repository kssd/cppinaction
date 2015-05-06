#if !defined (COMMANDER_H)
#define COMMANDER_H
// Bartosz Milewski (c) 2000

#include "Command.h"
#include "Win.h"

class Commander;
class Calculator;

namespace Cmd
{
	extern Cmd::Item<Commander> const Table [];
}

typedef Cmd::VectorExec<Commander> CmdVector;

class Commander
{
public:
	Commander (Win::Dow win, Calculator & calc);

    void Program_About ();
	Cmd::Status can_Program_About () const { return Cmd::Enabled; }
    void Program_Exit ();
	Cmd::Status can_Program_Exit () const { return Cmd::Enabled; }
    void Memory_Clear ();
	Cmd::Status can_Memory_Clear () const;
    void Memory_Save ();
	Cmd::Status can_Memory_Save () const { return Cmd::Enabled; }
    void Memory_Load ();
	Cmd::Status can_Memory_Load () const { return Cmd::Enabled; }
private:
	Win::Dow _win;
	Calculator & _calc;
};

#endif
