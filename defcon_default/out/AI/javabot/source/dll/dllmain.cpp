/*
DEFCON API Example Bot

This is a pretty minimal example bot for the DEFCON API, available online here:
http://www.introversion.co.uk/defcon/bots

dllmain.cpp - This file is the entrypoint for calls to the dll. All four functions 
defined here - AI_run, AI_init, AI_addevent and AI_shutdown - are called 
from the main program (DEFCON). They are exposed through the file dll/bot.def and
declared in export_to_defcon.h.

*/

#include <vector>
#include <string>


#include "dll/stdafx.h"             // contains standard system include files 
#include "import_from_defcon.h"     // defines all functions that are imported from DEFCON
#include "export_to_defcon.h"       // defines the functions exported to DEFCON (defined in this file (dllmain.cpp))
#include "enums.h"                  // contains enums and definitions used by the functions exposed by DEFCON.
#include "../bot/bot.h"             // example bot object that normally contains the AI code


using namespace std;

// This is the example bot object
Bot m_bot;


// AI_run() is called by DEFCON during every game update cycle (every 100ms)
extern "C" bool AI_run()
{

	m_bot.Update();


	return true;
}

extern "C" int AI_init(Funct* _functions, vector<vector<string>> _commandLineOptions)
{
	m_bot.Initialise(_functions, _commandLineOptions);
	return INTERFACE_VERSION;
}

extern "C" bool AI_shutdown()
{
	return true;
}

extern "C" void AI_addevent(int _eventType, int _causeObjectId, int _targetObjectId, 
							int _unitType,  float _longitude, float _latitude)
{
	
	m_bot.AddEvent(_eventType, _causeObjectId, _targetObjectId, 
		_unitType, _longitude, _latitude);
}

