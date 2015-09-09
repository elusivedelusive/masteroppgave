/*
bot.cpp 
JNI implementation. 
Please see the java file and the readme for more information.
*/

#include "dll/stdafx.h"
#include "dll/enums.h"      // Contains all important enums and constants
#include "bot/bot.h"


#include <sstream>

// allow static jni callback functions to access bot
Bot *myBot;

Bot::Bot()
{	
	m_jni_loaded = false;

	// If you want to change the name or location of your bot or java files, apply these changes here.
	// These are default values which can be overwritten by commandline options passed to DEFCON.
	m_javaClassPath = "AI/javabot/source/java";
	m_javaClassName = "javabot/JBot"; // Format: package/package/class
	m_javaVersion = JNI_VERSION_1_6;
	myBot = this;
}

// Initialise
// Called when the bot is initialized (every time it is selected from the "Select Bot"
// dropdown in the lobby.
bool Bot::Initialise(Funct *_functions, std::vector<std::vector<std::string>> _commandLineOptions)
{
	// The f object is an object of the Funct class, containing all the functions exposed by DEFCON.
	m_game = _functions;

	// select commandline options that specify location of java bot
	for (unsigned int i = 0; i < _commandLineOptions.size(); i++)
	{
		if (_commandLineOptions[i][0] == "javaclasspath")
		{
			m_javaClassPath = _commandLineOptions[i][1];
		}
		else if (_commandLineOptions[i][0] == "javaclassname")
		{
			m_javaClassName = _commandLineOptions[i][1];
		}
		else if (_commandLineOptions[i][0] == "javaversion")
		{
			if (_commandLineOptions[i][1] == "1.6")
				m_javaVersion = JNI_VERSION_1_6;
			else if (_commandLineOptions[i][1] == "1.4")
				m_javaVersion = JNI_VERSION_1_4;
			else if (_commandLineOptions[i][1] == "1.2")
				m_javaVersion = JNI_VERSION_1_2;
			else if (_commandLineOptions[i][1] == "1.1")
				m_javaVersion = JNI_VERSION_1_1;
		}
	}

	if (!m_jni_loaded)
	{
		if (!InitJavaDriver())
			return false;
		else
		{
			// call java

			jobjectArray row = (jobjectArray)m_javaEnv->NewObjectArray(2,  
				m_javaEnv->FindClass("java/lang/String"),  
				m_javaEnv->NewStringUTF(""));
			jobjectArray ret = (jobjectArray)m_javaEnv->NewObjectArray(
				_commandLineOptions.size(), m_javaEnv->GetObjectClass(row), 0);

			for(unsigned int i = 0; i < _commandLineOptions.size(); i++) {
				row = (jobjectArray)m_javaEnv->NewObjectArray(2,  
					m_javaEnv->FindClass("java/lang/String"),  
					m_javaEnv->NewStringUTF(""));
				m_javaEnv->SetObjectArrayElement(row, 0, m_javaEnv->NewStringUTF(_commandLineOptions[i][0].c_str()));
				m_javaEnv->SetObjectArrayElement(row, 1, m_javaEnv->NewStringUTF(_commandLineOptions[i][1].c_str()));
				m_javaEnv->SetObjectArrayElement(ret, i, row);
			}


			jmethodID mid = m_javaEnv->GetStaticMethodID(m_javaClass, "initialise", "([[Ljava/lang/String;)Z");
			jboolean b = m_javaEnv->CallBooleanMethod(m_javaClass, mid, ret);
			return b == JNI_TRUE;
		}
	}
	return true;
}

// Callback functions

jint JNICALL jGetDefcon(JNIEnv *, jobject)
{
	return myBot->m_game->GetDefcon();
}

jfloat JNICALL jGetGameTime(JNIEnv *, jobject)
{
	return myBot->m_game->GetGameTime();
}

jint JNICALL jGetGameSpeed(JNIEnv *, jobject)
{
	return myBot->m_game->GetGameSpeed();
}

jint JNICALL jGetGameTick(JNIEnv *, jobject)
{
	return myBot->m_game->GetGameTick();
}

jfloat JNICALL jGetVictoryTimer(JNIEnv *, jobject)
{
	return myBot->m_game->GetVictoryTimer();
}

jboolean JNICALL jIsVictoryTimerActive(JNIEnv *, jobject)
{
	return myBot->m_game->IsVictoryTimerActive();
}

jint JNICALL jGetOptionValue(JNIEnv *env, jobject, jstring options)
{
	int strlength = env->GetStringLength(options);
	char* str = new char[strlength + 1];
	const char* original = env->GetStringUTFChars(options, false);
	strcpy(str, original);
	env->ReleaseStringUTFChars(options, original);
	return myBot->m_game->GetOptionValue(str);
}

jintArray JNICALL jGetCityIds(JNIEnv *env, jobject)
{
	std::vector<int> result = myBot->m_game->GetCityIds();
	/*unsigned int len = result.size();
	jint *buf = new jint[len];
	for (unsigned int i = 0; i < len; i++)
	{
	jint[i] = result[i];
	}*/
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
		env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jint JNICALL jGetCityPopulation(JNIEnv *, jobject, jint _cityId)
{
	return myBot->m_game->GetCityPopulation(_cityId);
}

jint JNICALL jGetRemainingPopulation(JNIEnv *, jobject, jint _cityId)
{
	return myBot->m_game->GetRemainingPopulation(_cityId);
}

jboolean JNICALL jIsValidTerritory(JNIEnv *, jobject, jint _teamId, jfloat _longitude, jfloat _latitude, jboolean seaArea)
{
	return myBot->m_game->IsValidTerritory(_teamId, _longitude, _latitude, seaArea == JNI_TRUE);
}

jboolean JNICALL jIsBorder(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude)
{
	return myBot->m_game->IsBorder(_longitude, _latitude);
}

jint JNICALL jGetTerritoryId(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude)
{
	return myBot->m_game->GetTerritoryId(_longitude, _latitude);
}

jint JNICALL jGetOwnTeamId(JNIEnv *, jobject)
{
	return myBot->m_game->GetOwnTeamId();
}

jintArray JNICALL jGetTeamIds(JNIEnv *env, jobject)
{
	std::vector<int> result = myBot->m_game->GetTeamIds();
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
		env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jintArray JNICALL jGetTeamTerritories(JNIEnv *env, jobject, jint _teamId)
{
	std::vector<int> result = myBot->m_game->GetTeamTerritories(_teamId);
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
		env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jint JNICALL jGetAllianceId(JNIEnv *, jobject, jint _teamId)
{
	return myBot->m_game->GetAllianceId(_teamId);
}

jint JNICALL jGetDesiredGameSpeed(JNIEnv *, jobject, jint _teamId)
{
	return myBot->m_game->GetDesiredGameSpeed(_teamId);
}

jint JNICALL jGetEnemyKills(JNIEnv *, jobject, jint _teamId)
{
	return myBot->m_game->GetEnemyKills(_teamId);
}

jint JNICALL jGetFriendlyDeaths(JNIEnv *, jobject, jint _teamId)
{
	return myBot->m_game->GetFriendlyDeaths(_teamId);
}

jint JNICALL jGetCollateralDamage(JNIEnv *, jobject, jint _teamId)
{
	return myBot->m_game->GetCollateralDamage(_teamId);
}

jstring JNICALL jGetTeamName(JNIEnv *env, jobject, jint _teamId)
{
	return env->NewStringUTF(myBot->m_game->GetTeamName(_teamId));
}

jboolean JNICALL jIsSharingRadar(JNIEnv *, jobject, jint _teamId1, jint _teamId2)
{
	return myBot->m_game->IsSharingRadar(_teamId1, _teamId2);
}

jboolean JNICALL jIsCeaseFire(JNIEnv *, jobject, jint _teamId1, jint _teamId2)
{
	return myBot->m_game->IsCeaseFire(_teamId1, _teamId2);
}

void JNICALL jRequestAlliance(JNIEnv *, jobject, jint _allianceId)
{
	myBot->m_game->RequestAlliance(_allianceId);
}

void JNICALL jRequestCeaseFire(JNIEnv *, jobject, jint _teamId)
{
	myBot->m_game->RequestCeaseFire(_teamId);
}

void JNICALL jRequestShareRadar(JNIEnv *, jobject, jint _teamId)
{
	myBot->m_game->RequestShareRadar(_teamId);
}

void JNICALL jRequestGameSpeed(JNIEnv *, jobject, jint _requestedSpeedIdentifier)
{
	myBot->m_game->RequestGameSpeed(_requestedSpeedIdentifier);
}

jintArray JNICALL jGetAllUnits(JNIEnv *env, jobject)
{
	std::vector<int> result = myBot->m_game->GetAllUnits();
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
		env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jintArray JNICALL jGetOwnUnits(JNIEnv *env, jobject)
{
	std::vector<int> result = myBot->m_game->GetOwnUnits();
	jintArray arr = env->NewIntArray( result.size() );
	env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jintArray JNICALL jGetTeamUnits(JNIEnv *env, jobject, jint _teamId)
{
	std::vector<int> result = myBot->m_game->GetTeamUnits(_teamId);
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
		env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jfloatArray JNICALL j_GetAllUnitData(JNIEnv *env, jobject)
{
	std::vector<Funct::UnitData *> result = myBot->m_game->GetAllUnitData();
	jfloatArray arr = env->NewFloatArray( result.size() * 7 );

	for (unsigned int i = 0; i < result.size(); i++)
	{
		jfloat tmp = (float) result[i]->m_objectId;
		env->SetFloatArrayRegion(arr, i * 7, 1, &tmp);
		tmp = (float) result[i]->m_type;
		env->SetFloatArrayRegion(arr, i * 7 + 1, 1, &tmp); 
		tmp = (float) result[i]->m_teamId;
		env->SetFloatArrayRegion(arr, i * 7 + 2, 1, &tmp); 
		tmp = (float) result[i]->m_currentState;
		env->SetFloatArrayRegion(arr, i * 7 + 3, 1, &tmp); 
		tmp = result[i]->m_visible ? 1.0f : 0.0f;
		env->SetFloatArrayRegion(arr, i * 7 + 4, 1, &tmp); 
		tmp = result[i]->m_longitude;
		env->SetFloatArrayRegion(arr, i * 7 + 5, 1, &tmp); 
		tmp = result[i]->m_latitude;
		env->SetFloatArrayRegion(arr, i * 7 + 6, 1, &tmp); 
	}
	return arr;
}

jint JNICALL jGetType(JNIEnv *, jobject, jint _id)
{
	return myBot->m_game->GetType(_id);
}

jint JNICALL jGetTeamId(JNIEnv *, jobject, jint _id)
{
	return myBot->m_game->GetTeamId(_id);
}

jintArray JNICALL jGetOwnFleets(JNIEnv *env, jobject)
{
	std::vector<int> result = myBot->m_game->GetOwnFleets();
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
	env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jintArray JNICALL jGetFleets(JNIEnv *env, jobject, jint _teamId)
{
	std::vector<int> result = myBot->m_game->GetFleets(_teamId);
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
	env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jintArray JNICALL jGetFleetMembers(JNIEnv *env, jobject, jint _teamId)
{
	std::vector<int> result = myBot->m_game->GetFleetMembers(_teamId);
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
	env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jint JNICALL jGetFleetId(JNIEnv *, jobject, jint _unitId)
{
	return myBot->m_game->GetFleetId(_unitId);
}

jint JNICALL jGetCurrentState(JNIEnv *, jobject, jint _unitId)
{
	return myBot->m_game->GetCurrentState(_unitId);
}

jint JNICALL jGetStateCount(JNIEnv *, jobject, jint _unitId, jint _stateId)
{
	return myBot->m_game->GetStateCount(_unitId, _stateId);
}

jintArray JNICALL jGetActionQueue(JNIEnv *env, jobject, jint _unitId)
{
	std::vector<int> result = myBot->m_game->GetActionQueue(_unitId);
	jintArray arr = env->NewIntArray( result.size() );
	if (result.size() > 0)
	env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

jfloat JNICALL jGetStateTimer(JNIEnv *, jobject, jint _unitId)
{
	return myBot->m_game->GetStateTimer(_unitId);
}

jint JNICALL jGetCurrentTargetId(JNIEnv *, jobject, jint _unitId)
{
	return myBot->m_game->GetCurrentTargetId(_unitId);
}

jfloatArray JNICALL jGetMovementTargetLocation(JNIEnv *env, jobject, jint _unitId)
{
	std::vector<float> result = myBot->m_game->GetMovementTargetLocation(_unitId);
	jfloatArray arr = env->NewFloatArray( result.size() );
	if (result.size() > 0)
	env->SetFloatArrayRegion( arr, 0, result.size(), ( jfloat * ) &result[0] );  
	return arr;
}

jint JNICALL jGetNukeSupply(JNIEnv *, jobject, jint _unitId)
{
	return myBot->m_game->GetNukeSupply(_unitId);
}

jfloatArray JNICALL jGetBomberNukeTarget(JNIEnv *env, jobject, jint _unitId)
{
	std::vector<float> result = myBot->m_game->GetBomberNukeTarget(_unitId);
	jfloatArray arr = env->NewFloatArray( result.size() );
	if (result.size() > 0)
	env->SetFloatArrayRegion( arr, 0, result.size(), ( jfloat * ) &result[0] );  
	return arr;
}

jboolean JNICALL jIsRetaliating(JNIEnv *, jobject, jint _unitId)
{
	return myBot->m_game->IsRetaliating(_unitId);
}

jboolean JNICALL jIsVisible(JNIEnv *, jobject, jint _unitId, jint _byTeamId )
{
	return myBot->m_game->IsVisible(_unitId, _byTeamId);
}

jint JNICALL jSetState(JNIEnv *, jobject, jint _unitId, jint _stateId)
{
	return myBot->m_game->SetState(_unitId, _stateId);
}

void JNICALL jSetMovementTarget(JNIEnv *, jobject, jint _unitId, jfloat _longitude, jfloat _latitude)
{
	return myBot->m_game->SetMovementTarget(_unitId, _longitude, _latitude);
}

void JNICALL jSetActionTarget(JNIEnv *, jobject, jint _unitId, jint _targetUnitId, jfloat _longitude, jfloat _latitude)
{
	return myBot->m_game->SetActionTarget(_unitId, _targetUnitId, _longitude, _latitude);
}

void JNICALL jSetLandingTarget(JNIEnv *, jobject, jint _unitId, jint _targetUnitId)
{
	return myBot->m_game->SetLandingTarget(_unitId, _targetUnitId);
}

jfloat JNICALL jGetLongitude(JNIEnv *, jobject, jint _id)
{
	return myBot->m_game->GetLongitude(_id);
}

jfloat JNICALL jGetLatitude(JNIEnv *, jobject, jint _id)
{
	return myBot->m_game->GetLatitude(_id);
}

jfloatArray JNICALL jGetVelocity(JNIEnv *env, jobject, jint _unitId)
{
	std::vector<float> result = myBot->m_game->GetVelocity(_unitId);
	jfloatArray arr = env->NewFloatArray( result.size() );
	if (result.size() > 0)
	env->SetFloatArrayRegion( arr, 0, result.size(), ( jfloat * ) &result[0] );  
	return arr;
}

jfloat JNICALL jGetRange(JNIEnv *, jobject, jint _unitId)
{
	return myBot->m_game->GetRange(_unitId);
}

jint JNICALL jGetRemainingUnits(JNIEnv *, jobject, jint _typeId)
{
	return myBot->m_game->GetRemainingUnits(_typeId);
}

jboolean JNICALL jIsValidPlacementLocation(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude, jint _typeId )
{
	return myBot->m_game->IsValidPlacementLocation(_longitude, _latitude, _typeId);
}

jfloatArray JNICALL jGetFleetMemberOffset(JNIEnv *env, jobject, jint _memberCount, jint _memberId)
{
	std::vector<float> result = myBot->m_game->GetFleetMemberOffset(_memberCount, _memberId);
	jfloatArray arr = env->NewFloatArray( result.size() );
	if (result.size() > 0)
	env->SetFloatArrayRegion( arr, 0, result.size(), ( jfloat * ) &result[0] );  
	return arr;
}

void JNICALL jPlaceStructure(JNIEnv *, jobject, jint _typeId, jfloat _longitude, jfloat _latitude)
{
	myBot->m_game->PlaceStructure(_typeId, _longitude, _latitude);
}

void JNICALL jPlaceFleet1(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude,
						  jint _typeShip1 )
{
	myBot->m_game->PlaceFleet(_longitude, _latitude, _typeShip1, -1, -1, -1, -1, -1);
}

void JNICALL jPlaceFleet2(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude,
						  jint _typeShip1, jint _typeShip2 )
{
	myBot->m_game->PlaceFleet(_longitude, _latitude, _typeShip1, _typeShip2, -1, -1, -1, -1);
}

void JNICALL jPlaceFleet3(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude,
						  jint _typeShip1, jint _typeShip2, jint _typeShip3 )
{
	myBot->m_game->PlaceFleet(_longitude, _latitude, _typeShip1, _typeShip2, _typeShip3, -1, -1, -1);
}

void JNICALL jPlaceFleet4(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude,
						  jint _typeShip1, jint _typeShip2, jint _typeShip3, jint _typeShip4 )
{
	myBot->m_game->PlaceFleet(_longitude, _latitude, _typeShip1, _typeShip2, _typeShip3, _typeShip4, -1, -1);
}

void JNICALL jPlaceFleet5(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude,
						  jint _typeShip1, jint _typeShip2, jint _typeShip3, jint _typeShip4, jint _typeShip5 )
{
	myBot->m_game->PlaceFleet(_longitude, _latitude, _typeShip1, _typeShip2, _typeShip3, _typeShip4, _typeShip5, -1);
}

void JNICALL jPlaceFleet6(JNIEnv *, jobject, jfloat _longitude, jfloat _latitude,
						  jint _typeShip1, jint _typeShip2, jint _typeShip3, jint _typeShip4, jint _typeShip5, jint _typeShip6 )
{
	myBot->m_game->PlaceFleet(_longitude, _latitude, 
		_typeShip1, _typeShip2, _typeShip3, _typeShip4, _typeShip5, _typeShip6 );
}

jint JNICALL jGetUnitCredits(JNIEnv *, jobject)
{
	return myBot->m_game->GetUnitCredits();
}

jint JNICALL jGetUnitValue(JNIEnv *, jobject, jint _typeId)
{
	return myBot->m_game->GetUnitValue(_typeId);
}

void JNICALL jSendVote(JNIEnv *, jobject, jint _voteId, jint _vote )
{
	myBot->m_game->SendVote(_voteId, _vote);
}

void JNICALL jSendChatMessage(JNIEnv *env, jobject, jstring _chatMessage, jint _receiverId)
{
	std::string tmp = env->GetStringUTFChars(_chatMessage, 0);
	myBot->m_game->SendChatMessage(tmp, _receiverId);
}

jfloat JNICALL jGetDistance(JNIEnv *, jobject, jfloat _longitude1, jfloat _latitude1, jfloat _longitude2, jfloat _latitude2 )
{
	return myBot->m_game->GetDistance( _longitude1,  _latitude1,  _longitude2,  _latitude2 );
}

jfloat JNICALL jGetSailDistance(JNIEnv *, jobject, jfloat _longitude1, jfloat _latitude1, jfloat _longitude2, jfloat _latitude2 )
{
	return myBot->m_game->GetSailDistance( _longitude1,  _latitude1,  _longitude2,  _latitude2 );
}

void JNICALL jDebugLog(JNIEnv *env, jobject o, jstring _entry, jint _objectId, jstring _tags, jint _colorR, jint _colorG, jint _colorB, jint _colorAlpha)
{
	std::string tmp = env->GetStringUTFChars(_entry, 0);
	std::string tmp2 = env->GetStringUTFChars(_tags, 0);
	myBot->m_game->DebugLog(tmp, _objectId, tmp2, 
		(unsigned char) _colorR, (unsigned char) _colorG, (unsigned char) _colorB, (unsigned char) _colorAlpha);
	//env->ReleaseStringUTFChars(_entry, tmp.c_str());
	//env->ReleaseStringUTFChars(_tags, tmp2.c_str());
}

void JNICALL jDebugLog1(JNIEnv *env, jobject o, jstring _entry)
{
	jDebugLog(env, o, _entry, -1, env->NewStringUTF(""), 255, 255, 255, 255);
}

void JNICALL jDebugLog2(JNIEnv *env, jobject o, jstring _entry, jint _objectId)
{
	jDebugLog(env, o, _entry, _objectId, env->NewStringUTF(""), 255, 255, 255, 255);
}

void JNICALL jDebugLog3(JNIEnv *env, jobject o, jstring _entry, jint _objectId, jstring _tags)
{
	jDebugLog(env, o, _entry, _objectId, _tags, 255, 255, 255, 255);
}

void JNICALL jDebugLog4(JNIEnv *env, jobject o, jstring _entry, jint _objectId, jstring _tags, jint _colorR, jint _colorG, jint _colorB)
{
	jDebugLog(env, o, _entry, _objectId, _tags, _colorR, _colorG, _colorB, 255);
}

jboolean JNICALL jDebugIsReplayingGame(JNIEnv *, jobject )
{
	return myBot->m_game->DebugIsReplayingGame();
}

void JNICALL jWhiteboardDraw(JNIEnv *, jobject, jfloat _longitude1, jfloat _latitude1, jfloat _longitude2, jfloat _latitude2 )
{
	return myBot->m_game->WhiteboardDraw( _longitude1,  _latitude1,  _longitude2,  _latitude2 );
}

void JNICALL jWhiteboardClear(JNIEnv *, jobject)
{
	return myBot->m_game->WhiteboardClear( );
}

jintArray JNICALL jGetSuccessfulCommands(JNIEnv *env, jobject)
{
	std::vector<int> result = myBot->m_game->GetSuccessfulCommands();
	jintArray arr = env->NewIntArray( result.size() );
	env->SetIntArrayRegion( arr, 0, result.size(), ( jint * ) &result[0] );  
	return arr;
}

// set up the java virtual machine
bool Bot::InitJavaDriver()
{

	// java initialisation arguments
	JavaVMInitArgs vm_args; 
	JavaVMOption* options = new JavaVMOption[2];
	std::string path = "-Djava.class.path=" + m_javaClassPath;
	char *pathchar = new char[path.length()];
	strcpy(pathchar,path.c_str());
	options[0].optionString = pathchar;
	options[1].optionString = "-verbose:jni";                   /* print JNI-related messages */
	// add more options here if desired.

	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = 2;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;
	/* load and initialize a Java VM, return a JNI interface
	* pointer in m_javaEnv */
	jint res;
	res = JNI_CreateJavaVM(&m_jvm, (void **)&m_javaEnv, &vm_args);
	if (res < 0) {
		fprintf(stderr, "Can't create Java VM\n");
		return false;
	}

	delete options;

	// find class
	m_javaClass = m_javaEnv->FindClass(m_javaClassName.c_str());
	if (m_javaClass == NULL) {
		if (m_javaEnv->ExceptionOccurred()) {
			m_javaEnv->ExceptionDescribe();
		}
		return false;
	}

	// Register callback functions with java
	JNINativeMethod methods[] = {  
		// name, signature, function pointer  
		{ "GetGameTick", "()I", &jGetGameTick },
		{ "GetGameSpeed", "()I", &jGetGameSpeed },
		{ "GetDefcon", "()I", &jGetDefcon },
		{ "SendChatMessage", "(Ljava/lang/String;I)V", &jSendChatMessage },
		{ "GetGameTime", "()F", &jGetGameTime },
		{ "GetVictoryTimer", "()F", &jGetVictoryTimer },
		{ "IsVictoryTimerActive", "()Z", &jIsVictoryTimerActive },
		{ "GetOptionValue", "(Ljava/lang/String;)I", &jGetOptionValue },
		{ "GetCityIds", "()[I", &jGetCityIds },
		{ "GetCityPopulation", "(I)I", &jGetCityPopulation },
		{ "GetRemainingPopulation", "(I)I", &jGetRemainingPopulation },
		{ "IsValidTerritory", "(IFFZ)Z", &jIsValidTerritory },
		{ "IsBorder", "(FF)Z", &jIsBorder },
		{ "GetTerritoryId", "(FF)I", &jGetTerritoryId },
		{ "GetOwnTeamId", "()I", &jGetOwnTeamId },
		{ "GetTeamIds", "()[I", &jGetTeamIds },
		{ "GetTeamTerritories", "(I)[I", &jGetTeamTerritories },
		{ "GetAllianceId", "(I)I", &jGetAllianceId },
		{ "GetDesiredGameSpeed", "(I)I", &jGetDesiredGameSpeed },
		{ "GetEnemyKills", "(I)I", &jGetEnemyKills },
		{ "GetFriendlyDeaths", "(I)I", &jGetFriendlyDeaths },
		{ "GetCollateralDamage", "(I)I", &jGetCollateralDamage },
		{ "GetTeamName", "(I)Ljava/lang/String;", &jGetTeamName },
		{ "IsSharingRadar", "(II)Z", &jIsSharingRadar },
		{ "IsCeaseFire", "(II)Z", &jIsCeaseFire },
		{ "RequestAlliance", "(I)V", &jRequestAlliance },
		{ "RequestCeaseFire", "(I)V", &jRequestCeaseFire },
		{ "RequestShareRadar", "(I)V", &jRequestShareRadar },
		{ "RequestGameSpeed", "(I)V", &jRequestGameSpeed },
		{ "GetAllUnits", "()[I", &jGetAllUnits },
		{ "GetOwnUnits", "()[I", &jGetOwnUnits },
		{ "GetTeamUnits", "(I)[I", &jGetTeamUnits },
		{ "_GetAllUnitData", "()[F", &j_GetAllUnitData },
		{ "GetType", "(I)I", &jGetType },
		{ "GetTeamId", "(I)I", &jGetTeamId },
		{ "GetOwnFleets", "()[I", &jGetOwnFleets },
		{ "GetFleets", "(I)[I", &jGetFleets },
		{ "GetFleetMembers", "(I)[I", &jGetFleetMembers },
		{ "GetFleetId", "(I)I", &jGetFleetId },
		{ "GetCurrentState", "(I)I", &jGetCurrentState },
		{ "GetStateCount", "(II)I", &jGetStateCount },
		{ "GetActionQueue", "(I)[I", &jGetActionQueue },
		{ "GetStateTimer", "(I)F", &jGetStateTimer },
		{ "GetCurrentTargetId", "(I)I", &jGetCurrentTargetId },
		{ "GetMovementTargetLocation", "(I)[F", &jGetMovementTargetLocation },
		{ "GetNukeSupply", "(I)I", &jGetNukeSupply },
		{ "GetBomberNukeTarget", "(I)[F", &jGetBomberNukeTarget },
		{ "IsRetaliating", "(I)Z", &jIsRetaliating },
		{ "IsVisible", "(II)Z", &jIsVisible },
		{ "SetState", "(II)I", &jSetState },
		{ "SetMovementTarget", "(IFF)V", &jSetMovementTarget },
		{ "SetActionTarget", "(IIFF)V", &jSetActionTarget },
		{ "SetLandingTarget", "(II)V", &jSetLandingTarget },
		{ "GetLongitude", "(I)F", &jGetLongitude },
		{ "GetLatitude", "(I)F", &jGetLatitude },
		{ "GetVelocity", "(I)[F", &jGetVelocity },
		{ "GetRange", "(I)F", &jGetRange },
		{ "GetRemainingUnits", "(I)I", &jGetRemainingUnits },
		{ "IsValidPlacementLocation", "(FFI)Z", &jIsValidPlacementLocation },
		{ "GetFleetMemberOffset", "(II)[F", &jGetFleetMemberOffset },
		{ "PlaceStructure", "(IFF)V", &jPlaceStructure },
		{ "PlaceFleet", "(FFI)V", &jPlaceFleet1 },
		{ "PlaceFleet", "(FFII)V", &jPlaceFleet2 },
		{ "PlaceFleet", "(FFIII)V", &jPlaceFleet3 },
		{ "PlaceFleet", "(FFIIII)V", &jPlaceFleet4 },
		{ "PlaceFleet", "(FFIIIII)V", &jPlaceFleet5 },
		{ "PlaceFleet", "(FFIIIIII)V", &jPlaceFleet6 },
		{ "GetUnitCredits", "()I", &jGetUnitCredits },
		{ "GetUnitValue", "(I)I", &jGetUnitValue },
		{ "SendVote", "(II)V", &jSendVote },
		{ "GetDistance", "(FFFF)F", &jGetDistance },
		{ "GetSailDistance", "(FFFF)F", &jGetSailDistance },
		{ "DebugLog", "(Ljava/lang/String;)V", &jDebugLog1 },
		{ "DebugLog", "(Ljava/lang/String;I)V", &jDebugLog2 },
		{ "DebugLog", "(Ljava/lang/String;ILjava/lang/String;)V", &jDebugLog3 },
		{ "DebugLog", "(Ljava/lang/String;ILjava/lang/String;III)V", &jDebugLog4 },
		{ "DebugLog", "(Ljava/lang/String;ILjava/lang/String;IIII)V", &jDebugLog },
		{ "DebugIsReplayingGame", "()Z", &jDebugIsReplayingGame },
		{ "WhiteboardDraw", "(FFFF)V", &jWhiteboardDraw },
		{ "WhiteboardClear", "()V", &jWhiteboardClear },
		{ "GetSuccessfulCommands", "()[I", &jGetSuccessfulCommands }
	}; 
	m_javaEnv->RegisterNatives(m_javaClass, methods, 81);

	m_jni_loaded = true;
	return true;
}


// Update
// Called every update cycle of the server, normally every 100ms.
// Most of the AI code should be called from here.
bool Bot::Update()
{
	// call java
	jmethodID mid = m_javaEnv->GetStaticMethodID(m_javaClass, "update", "()Z");
	jboolean b = m_javaEnv->CallBooleanMethod(m_javaClass, mid);
	return b == JNI_TRUE;
}


// AddEvent
// Called by DEFCON whenever an event happens
void Bot::AddEvent(int _eventType, int _causeId, int _targetId, 
				   int _unitType, float _longitude, float _latitude)
{
	// call java
	jmethodID mid = m_javaEnv->GetStaticMethodID(m_javaClass, "addEvent", "(IIIIFF)V");
	m_javaEnv->CallVoidMethod(m_javaClass, mid, _eventType, _causeId, _targetId, _unitType, _longitude, _latitude);
}