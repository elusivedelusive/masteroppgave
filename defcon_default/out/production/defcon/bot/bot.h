#include "dll/abstract_bot.h"   // Abstract bot object definition
#include <string>
#include <vector>
#include <jni.h>


class Bot : public AbstractBot
{
public:
	Bot();
	virtual bool Update();
    virtual bool Initialise(Funct *_functions, std::vector< std::vector< std::string > > _commandLineOptions);
	virtual void AddEvent(int _eventType, int _causeObjectId, int _targetObjectId, 
		int _unitType, float _longitude, float _latitude);
	bool InitJavaDriver();

	
    // m_game contains all the functions exposed by DEFCON.
    // See import_from_defcon.h for a full list.
	Funct *m_game;
private:
    JNIEnv *m_javaEnv;       /* pointer to native method interface */
	jclass m_javaClass;
	JavaVM *m_jvm;       /* denotes a Java VM */

	bool m_jni_loaded;
	std::string m_javaClassPath;
	std::string m_javaClassName;
	jint m_javaVersion;

};


//Bot m_bot;