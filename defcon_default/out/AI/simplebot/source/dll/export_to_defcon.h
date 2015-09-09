#pragma once

#include "import_from_defcon.h"
#include <vector>
#include <string>

extern "C" bool AI_run();
extern "C" int AI_init(Funct* _functions, std::vector< std::vector< std::string > > _commandLineOptions);
extern "C" bool AI_shutdown();
extern "C" void AI_addevent(int _eventType, int _causeObjectId, int _targetObjectId, 
							int _unitType,  float _longitude, float _latitude);

