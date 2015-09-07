#include "dll/import_from_defcon.h"
#include <vector>
#include <string>

class AbstractBot
{
public:
	virtual bool Update() = 0;
    virtual bool Initialise(Funct *f, std::vector< std::vector< std::string > > commandLineOptions) = 0;
	virtual void AddEvent(int _eventType, int _causeObjectId, int _targetObjectId, 
		int _unitType,  float _longitude, float _latitude) = 0;
};