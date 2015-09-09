#include "dll/abstract_bot.h"   // Abstract bot object definition
#include <string>
#include <vector>

class Bot : public AbstractBot
{
public:
	virtual bool Update();
    virtual bool Initialise(Funct *_functions, std::vector< std::vector< std::string > > _commandLineOptions);
	virtual void AddEvent(int _eventType, int _causeObjectId, int _targetObjectId, 
		int _unitType, float _longitude, float _latitude);

private:
    // m_game contains all the functions exposed by DEFCON.
    // See import_from_defcon.h for a full list.
	Funct *m_game;
};