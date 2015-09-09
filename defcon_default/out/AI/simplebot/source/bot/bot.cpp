/*
 bot.cpp 
 This is the main file where the AI for the bot should be located
 The three important functions are:
      Initialise  - Called when the bot is initialized in the lobby
      Update      - Called every update cycle of the server
      AddEvent    - Called whenever an event is passed on by DEFCON to the bot.
*/

#include "dll/stdafx.h"
#include "dll/enums.h"      // Contains all important enums and constants
#include "bot/bot.h"

// Initialise
// Called when the bot is initialized (every time it is selected from the "Select Bot"
// dropdown in the lobby.
bool Bot::Initialise(Funct *_functions, std::vector<std::vector<std::string>> _commandLineOptions)
{
    // The f object is an object of the Funct class, containing all the functions exposed by DEFCON.
	m_game = _functions;

    // Send an example chat message. In this case a rename command.
    m_game->SendChatMessage("/name [Bot]TestBot", CHATCHANNEL_PUBLIC);
	return true;
}

// Update
// Called every update cycle of the server, normally every 100ms.
// Most of the AI code should be called from here.
bool Bot::Update()
{
    // put out an example "Hello World" every 30 ticks (server updates).
	if (m_game->GetGameTick() % 30 == 0)
	{
        m_game->SendChatMessage("Hello World!", CHATCHANNEL_PUBLIC);
	}
	return true;
}


// AddEvent
// Called by DEFCON whenever an event happens
void Bot::AddEvent(int _eventType, int _causeId, int _targetId, 
				   int _unitType, float _longitude, float _latitude)
{
}