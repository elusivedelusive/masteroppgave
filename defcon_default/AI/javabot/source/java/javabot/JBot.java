/* 
 * DEFCON API Java Bot
 * This is the java extension to the DEFCON AI API.
 * Please see the project homepage for more general information about the api:
 * http://www.doc.ic.ac.uk/~rb1006/projects:api and http://www.introversion.co.uk/defcon/bots/
 * 
 * By default, a JDK compiler compliance level of java version 1.6 is expected by the API. 
 * By giving the command line option javaversion="1.4", java 1.4 compliance can be activated.
 * 
 * The functions called by the api are initialise, update, and addEvent.
 * 
 * Feel free to modify and change the code as you see fit.
 * 
 * Author: Robin Baumgarten (see website above for contact details)
 * February 2009
 * 
 */

package javabot;

import java.util.ArrayList;

public class JBot {
    // the following declarations are functions implemented in the C++ API of DEFCON,
    // they have been exposed by the Java Native Interface. For more information on what
    // each function does, please refer to the function list at the project homepage:
    // http://www.doc.ic.ac.uk/~rb1006/projects:api:documentation
    public static native int GetDefcon();

    public static native float GetGameTime();

    public static native int GetGameTick();

    public static native int GetGameSpeed();

    public static native float GetVictoryTimer();

    public static native boolean IsVictoryTimerActive();

    public static native int GetOptionValue(String name);

    public static native int[] GetCityIds();

    public static native int GetCityPopulation(int cityId);

    public static native int GetRemainingPopulation(int teamId);

    public static native boolean IsValidTerritory(int teamId, float longitude, float latitude, boolean seaArea);

    public static native boolean IsBorder(float longitude, float latitude);

    public static native int GetTerritoryId(float longitude, float latitude);

    public static native int GetOwnTeamId();

    public static native int[] GetTeamIds();

    public static native int[] GetTeamTerritories(int teamId);

    public static native int GetAllianceId(int teamId);

    public static native int GetDesiredGameSpeed(int teamId);

    public static native int GetEnemyKills(int teamId);

    public static native int GetFriendlyDeaths(int teamId);

    public static native int GetCollateralDamage(int teamId);

    public static native String GetTeamName(int teamId);

    public static native boolean IsSharingRadar(int teamId1, int teamId2);

    public static native boolean IsCeaseFire(int teamId1, int teamId2);

    public static native void RequestAlliance(int allianceId);

    public static native void RequestCeaseFire(int teamId);

    public static native void RequestShareRadar(int teamId);

    public static native void RequestGameSpeed(int requestedSpeedIdentifier);

    public static native int[] GetAllUnits();

    public static native int[] GetOwnUnits();

    public static native int[] GetTeamUnits(int teamId);

    private static native float[] _GetAllUnitData();

    public static native int GetType(int id);

    public static native int GetTeamId(int id);

    public static native int[] GetOwnFleets();

    public static native int[] GetFleets(int teamId);

    public static native int[] GetFleetMembers(int _fleetId);

    public static native int GetFleetId(int unitId);

    public static native int GetCurrentState(int unitId);

    public static native int GetStateCount(int unitId, int stateId);

    public static native int[] GetActionQueue(int unitId);

    public static native float GetStateTimer(int unitId);

    public static native int GetCurrentTargetId(int unitId);

    public static native float[] GetMovementTargetLocation(int unitId);

    public static native int GetNukeSupply(int _unitId);

    public static native float[] GetBomberNukeTarget(int _unitId);

    public static native boolean IsRetaliating(int _unitId);

    public static native boolean IsVisible(int _unitId, int _byTeamId);

    public static native int SetState(int unitId, int stateId);

    public static native void SetMovementTarget(int unitId, float longitude, float latitude);

    public static native void SetActionTarget(int _unitId, int _targetUnitId, float _longitude, float _latitude);

    public static native void SetLandingTarget(int _unitId, int _targetUnitId);

    public static native float GetLongitude(int id);

    public static native float GetLatitude(int id);

    public static native float[] GetVelocity(int unitId);

    public static native float GetRange(int unitId);

    public static native int GetRemainingUnits(int typeId);

    public static native boolean IsValidPlacementLocation(float longitude, float latitude, int typeId);

    public static native float[] GetFleetMemberOffset(int memberCount, int memberId);

    public static native void PlaceStructure(int typeId, float longitude, float latitude);

    public static native void PlaceFleet(float longitude, float latitude, int typeShip1);

    public static native void PlaceFleet(float longitude, float latitude, int typeShip1, int typeShip2);

    public static native void PlaceFleet(float longitude, float latitude, int typeShip1, int typeShip2, int typeShip3);

    public static native void PlaceFleet(float longitude, float latitude, int typeShip1, int typeShip2, int typeShip3, int typeShip4);

    public static native void PlaceFleet(float longitude, float latitude, int typeShip1, int typeShip2, int typeShip3, int typeShip4, int typeShip5);

    public static native void PlaceFleet(float longitude, float latitude, int typeShip1, int typeShip2, int typeShip3, int typeShip4, int typeShip5, int typeShip6);

    public static native int GetUnitCredits();

    public static native int GetUnitValue(int _typeId);

    public static native void SendVote(int _voteId, int _vote);

    public static native void SendChatMessage(String chatMessage, int receiverId);

    public static native float GetDistance(float longitude1, float latitude1, float longitude2, float latitude2);

    public static native float GetSailDistance(float longitude1, float latitude1, float longitude2, float latitude2);

    public static native void DebugLog(String entry);

    public static native void DebugLog(String entry, int objectId);

    public static native void DebugLog(String entry, int objectId, String tags);

    public static native void DebugLog(String entry, int objectId, String tags, int colorR, int colorG, int colorB);

    public static native void DebugLog(String entry, int objectId, String tags, int colorR, int colorG, int colorB, int colorAlpha);

    public static native boolean DebugIsReplayingGame();

    public static native void WhiteboardDraw(float longitude1, float latitude1, float longitude2, float latitude2);

    public static native void WhiteboardClear();

    public static native int[] GetSuccessfulCommands();

    private static String[][] commandLineOptions;

    class UnitData {
        int m_objectId;
        int m_type;
        int m_teamId;
        int m_currentState;
        boolean m_visible;
        float m_longitude;
        float m_latitude;
    }

    public static final int STATE_AIRBASEFIGHTERLAUNCH = 0;
    public static final int STATE_AIRBASEBOMBERLAUNCH = 1;

    public static final int STATE_BATTLESHIPATTACK = 0;

    public static final int STATE_BOMBERATTACK = 0;
    public static final int STATE_BOMBERNUKE = 1;
    public static final int STATE_BOMBERINQUEUE = 2;

    public static final int STATE_CARRIERFIGHTERLAUNCH = 0;
    public static final int STATE_CARRIERBOMBERLAUNCH = 1;
    public static final int STATE_CARRIERANTISUB = 2;

    public static final int STATE_FIGHTERATTACK = 0;
    public static final int STATE_FIGHTERINQUEUE = 2;    //2 instead of 1 makes handling easier when looking for STATE_s of items in queues

    public static final int STATE_NUKEONTARGET = 0;
    public static final int STATE_NUKEDISARM = 1;

    public static final int STATE_RADARACTIVE = 0;

    public static final int STATE_SILONUKE = 0;
    public static final int STATE_SILOAIRDEFENSE = 1;

    public static final int STATE_SUBPASSIVESONAR = 0;
    public static final int STATE_SUBACTIVESONAR = 1;
    public static final int STATE_SUBNUKE = 2;

    public static final int CHATCHANNEL_PUBLIC = 100;
    public static final int CHATCHANNEL_ALLIANCE = 101;
    public static final int CHATCHANNEL_SPECTATORS = 102;

    // These were enums in C++, but to keep the JNI interface clean have been
    // converted to static ints here. Thus the somewhat inconsistent naming scheme
    // to the above constants. Feel free to use enums instead, with an adequate
    // conversion of the return values from the API functions.
    public static final int TerritoryNorthAmerica = 0;
    public static final int TerritorySouthAmerica = 1;
    public static final int TerritoryEurope = 2;
    public static final int TerritoryRussia = 3;
    public static final int TerritorySouthAsia = 4;
    public static final int TerritoryAfrica = 5;
    public static final int NumTerritories = 6;

    public static final int EventPingSub = 0;
    public static final int EventPingCarrier = 1;
    public static final int EventNukeLaunchSilo = 2;
    public static final int EventNukeLaunchSub = 3;
    public static final int EventHit = 4;
    public static final int EventDestroyed = 5;
    public static final int EventPingDetection = 6;
    public static final int EventCeasedFire = 7;
    public static final int EventUnceasedFire = 8;
    public static final int EventSharedRadar = 9;
    public static final int EventUnsharedRadar = 10;
    public static final int EventNewVote = 11;
    public static final int EventTeamVoted = 12;
    public static final int EventTeamRetractedVote = 13;
    public static final int EventVoteFinishedYes = 14;
    public static final int EventVoteFinishedNo = 15;

    public static final int TypeInvalid = 0;
    public static final int TypeCity = 1;
    public static final int TypeSilo = 2;
    public static final int TypeRadarStation = 3;
    public static final int TypeNuke = 4;
    public static final int TypeExplosion = 5;
    public static final int TypeSub = 6;
    public static final int TypeBattleShip = 7;
    public static final int TypeAirBase = 8;
    public static final int TypeFighter = 9;
    public static final int TypeBomber = 10;
    public static final int TypeCarrier = 11;
    public static final int TypeTornado = 12;
    public static final int TypeSaucer = 13;
    public static final int TypeFleet = 14;
    public static final int TypeGunshot = 15;
    public static final int TypeQueueItem = 16;
    public static final int NumObjectTypes = 17;

    public static final int VoteTypeInvalid = 0;
    public static final int VoteTypeJoinAlliance = 1;
    public static final int VoteTypeKickPlayer = 2;
    public static final int VoteTypeLeaveAlliance = 3;

    public static final int VoteUnknown = 0;
    public static final int VoteYes = 1;
    public static final int VoteNo = 2;
    public static final int VoteAbstain = 3;

    // parse the unit data into a proper object array
    public static UnitData[] GetAllUnitData() {
        float[] data = _GetAllUnitData();
        UnitData[] javaData = new UnitData[data.length];
        int counter = 0;
        for (int i = 0; i < javaData.length; i++) {
            javaData[i].m_objectId = (int) data[counter++];
            javaData[i].m_type = (int) data[counter++];
            javaData[i].m_teamId = (int) data[counter++];
            javaData[i].m_currentState = (int) data[counter++];
            javaData[i].m_visible = Math.round(data[counter++]) != 0;
            javaData[i].m_longitude = data[counter++];
            javaData[i].m_latitude = data[counter++];
        }
        return javaData;
    }
    public static int myTeam;
    public static int cities[];
    public static ArrayList<Integer> myCities;

    public static void findFriendlyCities() {
        myTeam = GetOwnTeamId();
        cities = GetCityIds();
        myCities = new ArrayList<Integer>();
        SendChatMessage("Finding cities", CHATCHANNEL_PUBLIC);
        for (int i = 0; i < cities.length; i++) {
            if (IsValidTerritory(myTeam, GetLongitude(cities[i]), GetLatitude(cities[i]), false)) {
                SendChatMessage(cities[i] + "", CHATCHANNEL_PUBLIC);
                myCities.add(cities[i]);
            }
        }
    }

    public static void placeSilos() {
        SendChatMessage("Placing Silos", CHATCHANNEL_PUBLIC);
        for (int city : myCities){
            if(IsValidPlacementLocation(GetLongitude(city)-1, GetLatitude(city), 2)){
                PlaceStructure(2, GetLongitude(city)-1, GetLatitude(city));
            }
        }
    }

    // update is called every tick of the game
    public static boolean update() {

        //find friendly cities
        if (GetGameTick() == 60) {
            findFriendlyCities();
        }

        if (GetGameTick() == 90) {
            placeSilos();
        }

        if (GetGameTick() % 30 == 0) {
            int[] c = GetAllUnits();
            SendChatMessage("Counting " + c.length + " bitches!", CHATCHANNEL_PUBLIC);
            if (c.length > 5) DebugLog("Unit id 5: " + c[5]);
        }

        return true;
    }

    // this is called when the dll is initialised, usually in the host/join dialog of the game
    public static boolean initialise(String[][] _commandLineOptions) {
        commandLineOptions = _commandLineOptions.clone();
        SendChatMessage("Counting " + _commandLineOptions.length + " cmdline options!", CHATCHANNEL_PUBLIC);

        return true;
    }

    // Whenever an event occurs, this function is called by the dll. This should be used to collect these events only,
    // with the main processing taking place in the update() function.
    public static void addEvent(int _eventType, int _causeObjectId, int _targetObjectId,
                                int _unitType, float _longitude, float _latitude) {

    }

}

