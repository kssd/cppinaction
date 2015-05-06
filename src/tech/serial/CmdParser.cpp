#include "CmdParser.h"
#include "scan.h"
#include "SerStream.h"
#include "calc.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

CommandParser::CommandParser (Scanner & scanner, Calculator & calc)
: _scanner (scanner),
  _calc (calc)
{
    assert (_scanner.IsCommand());
	_scanner.Accept ();
	std::string name = _scanner.GetSymbolName ();
    switch (name [0])
    {
    case 'q':
    case 'Q':
        _command = comQuit;
        break;
    case 's':
    case 'S':
        _command = comSave;
        break;
    case 'l':
    case 'L':
        _command = comLoad;
        break;
    default:
        _command = comError;
        break;
    }
}

Status CommandParser::Execute ()
{
	_scanner.AcceptCommand ();
	std::string nameFile;
    switch (_command)
    {
    case comSave:
        nameFile = _scanner.GetSymbolName ();
        return Save (nameFile);
    case comLoad:
        nameFile = _scanner.GetSymbolName ();
        return Load (nameFile);
    case comQuit:
        cerr << "Good Bye!" << endl;
        return stQuit;
    case comError:
        cerr << "Error" << endl;
        return stError;
    }
    return stOk;
}

const long Version = 1;

Status CommandParser::Load (std::string const & nameFile)
{
    cerr << "Load from: \"" << nameFile << "\"\n";
    Status status = stOk;
    try
    {
        DeSerializer in (nameFile);
        long ver = in.GetLong ();
        if (ver != Version)
            throw "Version number mismatch";
        _calc.DeSerialize (in);
    }
    catch (char* msg)
    {
        cerr << "Error: Load failed: " << msg << endl;
        status = stError;
    }
    catch (...)
    {
        cerr << "Error: Load failed\n";
        // data structures may be corrupt
        throw;
    }
    return status;
}

Status CommandParser::Save (std::string const & nameFile)
{
    cerr << "Save to: \"" << nameFile << "\"\n";
    Status status = stOk;
    try
    {
        Serializer out (nameFile);
        out.PutLong (Version);
        _calc.Serialize (out);
    }
    catch (char* msg)
    {
        cerr << "Error: Save failed: " << msg << endl;
        status = stError;
    }
    catch (...)
    {
        cerr << "Error: Save failed\n";
        status = stError;
    }
    return status;
}
