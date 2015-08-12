#include <xtl.h>
#include <xhttp.h>
#include <xkelib.h>
#include <xauth.h>


/*static void _RECHARGE_SPECIAL_ABILITY(Player p, BOOL unkTrue) { invoke<Void>(0xB71589DA, p, unkTrue); } // 0xB71589DA
 static void SPECIAL_ABILITY_LOCK(Any p0) { invoke<Void>(0x1B7BB388, p0); } // 0x1B7BB388
  static void SPECIAL_ABILITY_UNLOCK(Any p0) { invoke<Void>(0x1FDB2919, p0); } // 0x1FDB2919
  static BOOL IS_SPECIAL_ABILITY_ACTIVE(Any p0) { return invoke<BOOL>(0x1B17E334, p0); } // 0x1B17E334
    static BOOL IS_SPECIAL_ABILITY_METER_FULL(Any p0) { return invoke<BOOL>(0x2E19D7F6, p0); } // 0x2E19D7F6
	static void ENABLE_SPECIAL_ABILITY(Any p0, Any p1) { invoke<Void>(0xC86C1B4E, p0, p1); } // 0xC86C1B4E
    static BOOL IS_SPECIAL_ABILITY_ENABLED(Any p0) { return invoke<BOOL>(0xC01238CC, p0); } // 0xC01238CC
    static void SET_SPECIAL_ABILITY_MULTIPLIER(Any p0) { invoke<Void>(0xFF1BC556, p0); } // 0xFF1BC556
	static void FLASH_ABILITY_BAR(Any p0) { invoke<Void>(0x3648960D, p0); } // 0x3648960D
    static void SET_ABILITY_BAR_VALUE(Any p0, Any p1) { invoke<Void>(0x24E53FD8, p0, p1); } // 0x24E53FD8
	static void SPECIAL_ABILITY_DEACTIVATE(Any p0) { invoke<Void>(0x80C2AB09, p0); } // 0x80C2AB09
	 static void SPECIAL_ABILITY_RESET(Any p0) { invoke<Void>(0xA7D8BCD3, p0); } // 0xA7D8BCD3
	 static void RESET_SPECIAL_ABILITY_CONTROLS_CINEMATIC(Any p0, Any p1, Any p2) { invoke<Void>(0x8C7E68C1, p0, p1, p2); } // 0x8C7E68C1
    static void _RECHARGE_SPECIAL_ABILITY(Player p, BOOL unkTrue) { invoke<Void>(0xB71589DA, p, unkTrue); } // 0xB71589DA
-----------------------------------------------------------------------------------------------------------------------------------------------

All the natives I could find for the Special Abilty from Franklin

look in GTAVNatives.h if errors accoure 
------------------------------------------------------------------------------------------------------------------------------------------------
//Add -> Blame Player Mod, Give Online Player Health, Snacks, Ammo, and think of other items.
//#define DEVKIT // defines the menu for DEVKIT also need to do this in Tools.cc  also need to change sleep from 500 to 1400*/

#ifdef DEVKIT
#include <xbdm.h>
#endif

//#define x_startup //Enables CPU Verification, need to uncomment in globals.h
//#define personal // my personal version with cash drop
//#define printf // Stops printfs working or Comment out to use prints

int GlobalToAddress(int Global, int imm) {
    return *(int *)(0x83d3cb98 + ((Global & 0xFFFFFF) >> 16 & 0xFFFC) + (imm * 4)); //This is the pegassus offset needs updating tho (found in ram)
}


#include "globals.h" 
#include "Tools.h"
#include "GTAVMenu.h"
#include "Input.h"
#include "GTAVNatives.h"
#include "DataManager.h"
#include "ServerCommunicator.h"
#include "EncryptedDWORD.h"
#include "MenuSecurity.h"
#include "base64.h"
#include <cfloat>
#include <string>

int gauge = 0;
int fan;
bool wtf = false;
char *main_text;
bool attachspawn = false;
bool normalspawn = false;
bool custom_plate = false;
bool custom_marquee = false;
bool custom_per = false;
bool custom_rankMP0 = false;
bool custom_rankMP1 = false;
bool custom_rankMP2 = false;
bool custom_money = false;
bool custom_teleport = false;
int CustomXP = 0;
int Var_Pointer;
XOVERLAPPED Overlapped;
WCHAR Username[512];
XOVERLAPPED Overlapped2;
WCHAR Username2[15];
WCHAR Username3[15];
WCHAR Username4[14];
char gamertag;
using std::string;
typedef unsigned long long u64;


EncryptedDWORD *hook1;
EncryptedDWORD *hook2;
EncryptedDWORD *hook3;
EncryptedDWORD *nativeHook;
EncryptedDWORD *printToScreen;
EncryptedDWORD *customGetPedLastWeap;
EncryptedDWORD *customGetModelDim;

float x_f = 0.50f;
//#define Auth // Defines AUTH for hysterias dev
bool rocket_gun = false;
int objecthandle;
float objectcoordx, objectcoordy, objectcoordz, objectheading, objectpitch = 0, objectroll = 0, objectyaw = 0;
float objectpitch1 = 0, objectroll1 = 0, objectyaw1 = 0;
int waterobj;
int neonr, neong, neonb;
bool zdrop = false;
int wheel = 0;
int cashclient;
int fagcashclient;
int onecashclient;
int Addercashclient;
bool alltelefootway = false;
bool allkickedfromveh = false;
bool telefoot_way = false;
bool objectspawn = false;
bool aiming = false;
int chop;
int animalGuard;
int rocketid;
bool warp = false;
int animid;
bool nap = false;
bool kidnap = false;
bool aimbot = false;
bool aimbot_active = false;
bool kickfromveh = false;
bool freeze = false;
bool freezeall = false;
bool STFUTrollactive = false;
bool cheat_superjump = false;
bool cheat_runfast = false;
bool cheat_swimfast = false;
bool cheat_superpunch = false;
bool cheat_explosiveammo = false;
bool cheat_fireammo = false;
bool causelag = false;
int model;
//unsigned int uammo = 0x82F02FEC;
//unsigned int uammo2 = 0x82EEB7E4;
unsigned int uammo2 = 0x82F02FEC;
unsigned int uammo = 0x82EEB7E4;
extern "C" const TCHAR szModuleName[] = TEXT("GTAVMenu.dll");

int CarPed;
bool playerInvincibilityActive = false;
bool buttonpressed = false;
bool rainbow = false;
bool invisible = false;
bool superjump = false;
bool superruncheck = false;
bool deagle = false;
bool carvisible = false;
bool playervisible = false;
bool invisiblePlayer = false;
int myplayerped;
int rainbowcar;
int invisiblecar = false;


bool showingMessageOnScreen = false;
bool fadingMessage = false;
int messageFade = 0;
stack<char*> messageLog;
int showingMessageTimer = 0;
int showingMessageTimerStart = 0;
XVIDEO_MODE VideoMode;
char messageBuffer[256];

float messageTextX = 0.50000000f;
float messageTextY = 0.91000000f;


void ShowMessageOnScreen(char *format, ...) {
	va_list args;
	va_start(args, format);
	vsprintf(messageBuffer, format, args);
	va_end(args);

	showingMessageTimer = 0;
	showingMessageOnScreen = true;
	showingMessageTimerStart = GetTickCount();
	messageFade = 255;
}

void ShowMessageUpdate() {
	// Check to see if we are showing a message on the screen
	if (!showingMessageOnScreen) {
		return;
	}

	if ((GetTickCount() - showingMessageTimerStart) >= 4000) {
		messageFade--;
	}

	if ((GetTickCount() - showingMessageTimerStart) >= 5000) {
		showingMessageOnScreen = false;
		showingMessageTimer = 0;
		ZeroMemory(&messageBuffer, 256);
	}

	PrintToScreen(messageBuffer, messageTextX, messageTextY, 255, 255, 255, messageFade, 0.45f, 0.45f, 1, 0);
}

bool IsPlayerWithinArea(float playerX, float playerY, float areaX, float areaY, float areaSize) {
	float corner1X = areaX;
	float corner1Y = areaY;

	float corner2X = areaX + areaSize;
	float corner2Y = areaY + areaSize;

	float corner3X = areaX + areaSize;
	float corner3Y = areaY;

	float corner4X = areaX;
	float corner4Y = areaY + areaSize;
	
	if (playerX >= corner1X && playerX <= corner2X && playerY >= corner1Y && playerY <= corner2Y) {
		return true;
	}

	return false;
}


int are_you_in_veh_if_so_get_handle() {
if (!is_ped_on_foot(PlayerPedId())) {
int vehicle;
vehicle = GetCarCharIsIn(PlayerPedId(), 0);
return vehicle;
}
return 0;
}
PXOVERLAPPED over;
PMESSAGEBOX_RESULT result;
LPCWSTR* text;

DWORD WINAPI MessageBoxThread(PVOID pvParam) {
	//LPCWSTR Text, Caption;
	text = new LPCWSTR[1];
	text[0] = L"Reboot";

	extern wchar_t *MenuUpdateInfoConverted;
	//MessageBox(MenuUpdateInfoConverted, L"Menu Updated");

	over = new XOVERLAPPED();
	memset(over, 0, sizeof(over));	
	result = new MESSAGEBOX_RESULT();
	memset(result, 0, sizeof(result));

	while(XShowMessageBoxUI(0, L"Menu updated to TU24! Developed by CxM", MenuUpdateInfoConverted, 1, text, 0, XMB_NOICON, result, over) == ERROR_ACCESS_DENIED)
		Sleep(500);
	while(!XHasOverlappedIoCompleted(over))
		Sleep(500);

	HalReturnToFirmware(HalFatalErrorRebootRoutine);

	return 0;
}

int getFirstFreeSeatIndex(int vehicle){

	int maxSeatNum = get_vehicle_max_number_of_passengers(vehicle);

	for (int i = -1; i < maxSeatNum;i++)
	{
		if (is_vehicle_seat_free(vehicle, i))
		{
			return i;
		}
	}
	return -2;
}
bool follow = false;
void MakePlayerComeTome(int playerID)
{
	if (!network_is_player_active(playerID))
		return;
	int theirPedHandle = GetPlayerHandle(playerID);
	int myPedHandle = PlayerPedId();
	if (!DoesEntityExist(theirPedHandle))
		return;
	follow = true;
}

bool telefoot = false;
void MakePlayerComeTomeFoot(int playerID)
{
	if (!network_is_player_active(playerID))
		return;
	int theirPedHandle = GetPlayerHandle(playerID);
	int myPedHandle = PlayerPedId();
	if (!DoesEntityExist(theirPedHandle))
		return;
	telefoot = true;
}



void MakePlayerEnterMyVehicle(int playerID)
{
	/*if (!network_is_player_active(playerID))
		return;
	int theirpedHandle = GetPlayerHandle(playerID);
	if (is_entity_dead(theirpedHandle))
		return;
	
	int myPedHandle = PlayerPedId();
	
	if (is_ped_on_foot(myPedHandle) || !is_ped_on_foot(theirpedHandle))
	{
		ShowMessageOnScreen("~g~ Can't do task either you aren't in a car or the player isn't on foot!");
		return;
	}
	/*int myVehicle = GetCarCharIsIn(myPedHandle, 0);
	
	int firstFreeSeatInMyVehicle = getFirstFreeSeatIndex(myVehicle);
	ShowMessageOnScreen("~g~ Got free seat %i", firstFreeSeatInMyVehicle);
	if (firstFreeSeatInMyVehicle == -2)
		ShowMessageOnScreen("~g~ No Free Seat");*/
	ShowMessageOnScreen("~g~ Player should now get in your vehicle");
}
bool vm_animm = false;
/*void PlayPedAnim(char *animDictName, char *animName, int playerIndex)
{
	int playerPedHandle = GetPlayerHandle(playerIndex);
	
}*/

void StopPlayerTasks(int playerID){
	clear_ped_tasks_immediately(PlayerPedId());
	ShowMessageOnScreen("~g~Stopped Tasks");
}

unsigned int get_hash_key(char *key)
{
	size_t len = strlen(key);
    unsigned int hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += tolower(key[i]);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

bool hash_check(char *string, int hash)
{
int hashval = get_hash_key(string);
return (hashval == hash);
}

void secure_check() {
scroll_1 = marqueeText;
scroll_1 = "Welcome To xxHASTERxx: Menu | Search for xxHASTERxx Mod Services on YouTube";
}

#ifdef x_startup
void cpu_check() {
unsigned int cpu_hash = 78426742;
cputocheck = "6F2EE6D460686325FE81712639CB6FC9";
Sleep(4000);
if (hash_check(cputocheck, cpu_hash))
{
	cpu_verified = true;
}
}

#endif

unsigned char Numbers[257] = {0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,
	0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
	0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
	0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
	0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
	0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43,
	0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B,
	0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
	0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
	0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63,
	0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
	0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73,
	0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B,
	0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83,
	0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B,
	0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
	0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B,
	0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3,
	0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB,
	0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3,
	0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB,
	0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3,
	0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB,
	0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3,
	0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB,
	0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3,
	0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB,
	0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3,
	0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB,
	0xFC, 0xFD, 0xFE, 0xFF};
bool IsFalseAuthed;


char CAlpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char Alpha[] = "abcdefghijklmnopqrstuvwxyz";
char Num[] = "0123456789";
char T[] = {' ', '\n','\0', '%'};
/*byte AuthedCPU[] = {Numbers[0xC8], Numbers[0xEE], Numbers[0xC4], c8eec4aaf8f7842313313e39dcdcabdc
	Numbers[0xAA], Numbers[0xF8], Numbers[0xF7], Numbers[0x84],
	Numbers[0x23], Numbers[0x13], Numbers[0x31], Numbers[0x3E],
	Numbers[0x39], Numbers[0xDC], Numbers[0xDC], Numbers[0xAB],
	Numbers[0xDC]},*///90 3E 3E 1C BE 1E 95 CF 60 50 7C F0 D0 2F 86 A8
    byte AuthedCPU[] = {Numbers[0x90], Numbers[0x3E], Numbers[0x3E],
	Numbers[0x1C], Numbers[0xBE], Numbers[0x1E], Numbers[0x95],
	Numbers[0xCF], Numbers[0x60], Numbers[0x50], Numbers[0x7C],
	Numbers[0xF0], Numbers[0xD0], Numbers[0x2F], Numbers[0x86],
	Numbers[0xA8]}, 
	ConsoleCPU[0x10],

	AuthedMessage[] = {CAlpha[6], CAlpha[19], CAlpha[0], T[0], CAlpha[12], Alpha[4], Alpha[13], Alpha[20], T[0], CAlpha[0], Alpha[20], Alpha[19], Alpha[7], Alpha[4], Alpha[3],0},

	EntryAdd[4] = {Numbers[0], Numbers[0], Numbers[0x1], Numbers[0x04]},
	CashPointer[4] = {Numbers[0x83], Numbers[0xAE], Numbers[0x7C], Numbers[0x78]}, //0x83B04FE4 TU14 = 0x83B084B4 // TU15 0x83AE7C78

	HvxExpansionInstallBytes[] = {Numbers[0x38], Numbers[0x00], Numbers[0x00], Numbers[0x70],
	Numbers[0x44], Numbers[0x00], Numbers[0x00], Numbers[0x02], Numbers[0x4E], Numbers[0x80],
	Numbers[0x00], Numbers[0x20]},

	HvxExpansionCallBytes[] = {Numbers[0x38], Numbers[0x00], Numbers[0x00], Numbers[0x71],
	Numbers[0x44], Numbers[0x00], Numbers[0x00], Numbers[0x02], Numbers[0x4E], Numbers[0x80], Numbers[0x00], Numbers[0x20]};
	
void GetCoordsInfrontOfSelf(float *OutX, float *OutY, float *OutZ){ // Pos[0], Pos[1]
	int myPedHandle = PlayerPedId();
	float Pos[3], Heading = get_entity_heading(myPedHandle);
	GetEntityCoords(myPedHandle, Pos); //&Pos
	*OutX = Pos[0], *OutY = Pos[1], *OutZ = Pos[2];
	*OutX += (10 * sin(-1 * Heading)); //get_entity_heading(player_ped_iod());
	*OutZ += (10 * cos(-1 * Heading));
}

enum ExlposionType {
 GRENADE,
 GRENADELAUNCHER,
 STICKYBOMB,
 MOLOTOV, // 3
 ROCKET,
 TANKSHELL,
 HI_OCTANE,
 CAR,
 PLANE,
 PETROL_PUMP,
 BIKE,
 DIR_STEAM,
 DIR_FLAME,
 DIR_WATER_HYDRANT,
 DIR_GAS_CANISTER,
 BOAT,
 SHIP_DESTROY,
 TRUCK,
 BULLET,
 SMOKEGRENADELAUNCHER,
 SMOKEGRENADE,
 BZGAS,
 FLARE,
 GAS_CANISTER,
 EXTINGUISHER,
 PROGRAMMABLEAR,
 TRAIN,
 BARREL,
 PROPANE,
 BLIMP,
 DIR_FLAME_EXPLODE,
 TANKER,
 PLANE_ROCKET,
 VEHICLE_BULLET,
 GAS_TANK
};


GTAVMenu *mainMenu;
GTAVMenu *quickOptionsMenu;
GTAVMenu *playerOptionsMenu;
GTAVMenu *vehicleOptionMenu;
GTAVMenu *VehPaintMenu;
GTAVMenu *VehPaintMenu2;
GTAVMenu *RimPaint;
GTAVMenu *weaponOptionsMenu;
GTAVMenu *onlinePlayers;
GTAVMenu *blamePlayers;
GTAVMenu *onlinePlayersSubMenu;
GTAVMenu *CarSpawner;
GTAVMenu *CarSpawner2;
GTAVMenu *CarSpawnerMenu0;
GTAVMenu *CarSpawnerMenu0P2;
GTAVMenu *CarSpawnerMenu1;
GTAVMenu *CarSpawnerMenu2;
GTAVMenu *CarSpawnerMenu2P2;
GTAVMenu *CarSpawnerMenu3;
GTAVMenu *CarSpawnerMenu4;
GTAVMenu *CarSpawnerMenu4P2;
GTAVMenu *CarSpawnerMenu5;
GTAVMenu *CarSpawnerMenu6;
GTAVMenu *CarSpawnerMenu7;
GTAVMenu *CarSpawnerMenu8;
GTAVMenu *CarSpawnerMenu8P2;
GTAVMenu *CarSpawnerMenu9;
GTAVMenu *CarSpawnerMenu9P2;
GTAVMenu *CarSpawnerMenu10;
GTAVMenu *CarSpawnerMenu11;
GTAVMenu *CarSpawnerMenu12;
GTAVMenu *CarSpawnerMenu13;
GTAVMenu *CarSpawnerMenu14;
GTAVMenu *CarSpawnerMenu14P2;
GTAVMenu *CarSpawnerMenu15;
GTAVMenu *CarSpawnerMenu16;
GTAVMenu *CarSpawnerMenu17;
GTAVMenu *CarSpawnerMenu18;
GTAVMenu *CarSpawnerMenu19;
GTAVMenu *CarSpawnerMenu20;
GTAVMenu *CarSpawnerMenu20P2;
GTAVMenu *CarSpawnerMenu21;
GTAVMenu *CarSpawnerMenu22;
GTAVMenu *CarSpawnerMenu23;
GTAVMenu *OnlinePlayerBasicOptions;
GTAVMenu *OnlinePlayerVehicleOptions;
GTAVMenu *OnlinePlayerTeleport;
GTAVMenu *NaughtyStuff;
GTAVMenu *KickPlayerStuff;
GTAVMenu *AllOnlinePlayers;
GTAVMenu *AllAtachObject;
GTAVMenu *GuardMenu;
GTAVMenu *TeleMenu;
GTAVMenu *TeleMenu2;
GTAVMenu *ModelChanger;
GTAVMenu *ModelChanger2;
GTAVMenu *ModelChanger100;
GTAVMenu *MiscOptions;
GTAVMenu *AnimalModels;
GTAVMenu *ObjectAttachments;
GTAVMenu *CashDropOptions;
GTAVMenu *ExtraNaughtyStuff;
GTAVMenu *ObjectOptions;
GTAVMenu *ObjectOptions1;
GTAVMenu *FunnyCarOptions;
GTAVMenu *ChopAnims;
GTAVMenu *Chr0m3;
GTAVMenu *ModShop;
GTAVMenu *HornMenu;
GTAVMenu *HornMenu2;
GTAVMenu *HornMenu3;
GTAVMenu *TintMenu;
GTAVMenu *OpenMenu;
GTAVMenu *PerformanceMenu;
GTAVMenu *BodyMenu;
GTAVMenu *WheelMenu;
GTAVMenu *ArmourMenu;
GTAVMenu *HighEnd;
GTAVMenu *EngineMenu;
GTAVMenu *TransMenu;
GTAVMenu *BrakesMenu;
GTAVMenu *SuspMenu;
GTAVMenu *ExMenu;
GTAVMenu *FbMenu;
GTAVMenu *RbMenu;
GTAVMenu *SkMenu;
GTAVMenu *InteriorMenu;
GTAVMenu *HoodMenu;
GTAVMenu *LFenderMenu;
GTAVMenu *RFenderMenu;
GTAVMenu *RoofMenu;
GTAVMenu *GrillMenu;
GTAVMenu *SpoilerMenu;
GTAVMenu *Lowrider;
GTAVMenu *Muscle;
GTAVMenu *Offroad;
GTAVMenu *Sport;
GTAVMenu *SportMenu2;
GTAVMenu *SUV;
GTAVMenu *Tuner;
GTAVMenu *TunerMenu2;
GTAVMenu *Pegasus;
GTAVMenu *Weather;
GTAVMenu *Drop;
GTAVMenu *SpeedoMeter;
GTAVMenu *Recovery;
GTAVMenu *RGMenu;
GTAVMenu *FWMenu;
GTAVMenu *VWMenu;
GTAVMenu *Character1;
GTAVMenu *Character2;
GTAVMenu *Character3;
GTAVMenu *RankMenuMP0;
GTAVMenu *RankMenuMP1;
GTAVMenu *RankMenuMP2;
GTAVMenu *MoneyMenuMP0;
GTAVMenu *MoneyMenuMP1;
GTAVMenu *MoneyMenuMP2;
GTAVMenu *MovementMenu;
GTAVMenu *FavoriteModelsMenu;
GTAVMenu *AnimationMenu;
GTAVMenu *SportOptions;
GTAVMenu *SexOptions;
GTAVMenu *DanceOptions;
GTAVMenu *SuperHeroOptions;
GTAVMenu *MiscOptions2;
GTAVMenu *CreatorVehicle;
GTAVMenu *ModelChanger300;
GTAVMenu *ObjectSpawner2;
GTAVMenu *MenuOptions;
GTAVMenu *MenuFonts;
GTAVMenu *TitleFonts;
GTAVMenu *ItemFonts;
GTAVMenu *TitleShaderColor;
GTAVMenu *MainShaderColor;
GTAVMenu *TitleColor;
GTAVMenu *ItemColor;
GTAVMenu *SelectorColor;
GTAVMenu *MenuPosition;
GTAVMenu *MenuAlphaLevel;
GTAVMenu *MenuStyle;
GTAVMenu *MenuCredits;
GTAVMenu *MarqueePosition;
GTAVMenu *NeonMenu;
GTAVMenu *creatorVehicleDoors;
GTAVMenu *blamedExplosion;
GTAVMenu *SetPlayerAlpha;
GTAVMenu *OnlinePlayersGiveMenu;
GTAVMenu *MiniGamesSubMenu;
GTAVMenu *SecCamerasMenu;
GTAVMenu *OnlineTest;
GTAVMenu *LiveryMenu;
GTAVMenu *DevTestingMenu;
GTAVMenu *OnlinePlayerVehicleOptions2;
GTAVMenu *TeleMenu3;
GTAVMenu *CarSpawnerMenu24;
GTAVMenu *VehicleHandleMenu;
GTAVMenu *ObjectHandleMenu;
GTAVMenu *SaveLocationMenu;
GTAVMenu *LoadLocationMenu;


Input *menuInputHandler;


bool inputButtonsPressed = false;
bool enableMenu = false;

char *animdict, *anim;



bool RequestNetworkControl(int playerHandle, int carHandle) {
		int Vehicle = GetCarCharIsIn(playerHandle, 0);
		
		if (DoesEntityExist(carHandle) && IsEntityVehicle(carHandle)) {
			if(network_request_control_of_entity(carHandle)) {
				if (network_has_control_of_entity(carHandle)) {
					return true;
				}
			}
		}
	return false;
}

float Vec3DistanceSq(const float *p1, const float *p2) {
	return ((p2[0] - p1[0]) * (p2[0] - p1[0]) + 
		((p2[2] - p1[2]) * (p2[2] - p1[2]) + 
		((p2[1] - p1[1]) * (p2[1] - p1[1]))));
}

float Distance(float p11, float p12, float p13, float p21, float p22, float p23) {
	float p1[] = {p11, p12, p13},
		p2[] = {p21, p22, p23};
	return sqrt(Vec3DistanceSq(p1, p2));
}

float Distance(float *p1, float *p2) {
	return sqrt(Vec3DistanceSq(p1, p2));
}

bool isInDistance(int Handle) {
	float Pos[2][3],
	Dist;
	GetEntityCoords(PlayerPedId(), Pos[0]);
	GetEntityCoords(Handle, Pos[1]);
	Dist = Distance(Pos[0], Pos[1]);
	printf("Distance between you and the player is %f\n", Dist);
	return (Dist <= 100.0f);
}

void TeleportToClient(int Client) {
	float* Location = (float *)(*(int *)((*(int *)(0x83BA3400 + 0x78) + 0x10 + (Client * 0x900)) + 0xF8) + 0x70);
	//printf("Client %i's pos = { %f, %f, %f } \n", Client, Location[0], Location[1], Location[2]);
	memcpy((PVOID)(*(int *)(*(int *)((*(int *)(0x83BA3400 + 0x78) + 0x10 + (0 * 0x900)) + 0xF8) + 0x1C) + 0x40), Location, 0xC);
}

void ToggleGodMode(){
	SetPlayerInvincible(PlayerId(), true);
	set_entity_proofs(PlayerPedId(), true, true, true, true, true, false, false, false);
	set_entity_invincible(PlayerPedId(), true);
}

int ToggleInvincibility(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if(!playerInvincibilityActive)
	{
	  playerInvincibilityActive = true;
	  ShowMessageOnScreen("~y~God Mode: ~g~ON!");
	}
	else if(playerInvincibilityActive)
	{
	SetPlayerInvincible(PlayerId(), false);
	set_entity_proofs(PlayerPedId(), false, false, false, false, false, false, false, false);
	set_entity_invincible(PlayerPedId(), false);
	  playerInvincibilityActive = false;
	  ShowMessageOnScreen("~y~God Mode: ~r~OFF!");
	}

	return 0;
}

int SuperJumpCheat(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!cheat_superjump){
		cheat_superjump = true;
		ShowMessageOnScreen("~y~ Super Jump: ~g~ON!");
	}
	else if(cheat_superjump){
		cheat_superjump = false;
		ShowMessageOnScreen("~y~ Super Jump: ~r~OFF!");
	}

	return 0;
}

int SuperRunCheat(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!cheat_runfast){
		set_move_speed_multiplier(PlayerId(), 1.49);
		cheat_runfast = true;
		ShowMessageOnScreen("~y~ Super Run: ~g~ON!");
	}
	else if(cheat_runfast){
		set_move_speed_multiplier(PlayerId(), 1.0);
		cheat_runfast = false;
		ShowMessageOnScreen("~y~ Super Run: ~r~OFF!");
	}

	return 0;
}

int SwimFastCheat(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!cheat_swimfast){
		set_swim_speed_multiplier(PlayerId(), 1.49);
		cheat_swimfast = true;
		ShowMessageOnScreen("~y~ Swim Fast: ~g~ON!");
	}
	else if(cheat_swimfast){
		set_swim_speed_multiplier(PlayerId(), 1.0);
		cheat_swimfast = false;
		ShowMessageOnScreen("~y~ Swim Fast: ~r~OFF!");
	}

	return 0;
}

int SuperPunchCheat(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!cheat_superpunch){
		cheat_superpunch = true;
		ShowMessageOnScreen("~y~ Super Punch: ~g~ON!");
	}
	else if(cheat_superpunch){
		cheat_superpunch = false;
		ShowMessageOnScreen("~y~ Super Punch: ~r~OFF!");
	}

	return 0;
}

int ExplosiveAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if(!cheat_explosiveammo){
		cheat_explosiveammo = true;
		ShowMessageOnScreen("~y~ Explosive Ammo: ~g~ON!");
	}
	else if(cheat_explosiveammo){
		cheat_explosiveammo = false;
		ShowMessageOnScreen("~y~ Explosive Ammo: ~r~OFF!");
	}

	return 0;
}

int FireAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!cheat_fireammo){
		cheat_fireammo = true;
		ShowMessageOnScreen("~y~ Fire Ammo: ~g~ON!");
	}
	else if(cheat_fireammo){
		cheat_fireammo = false;
		ShowMessageOnScreen("~y~ Fire Ammo: ~r~OFF!");
	}

	return 0;
}

int irand(int min, int max, int Add = 0) {
	srand(GetTickCount() + Add);
	return min + (rand() % (int)(max - min + 1));
}

void rainbow_car() {
	if (DoesEntityExist(rainbowcar) && IsEntityVehicle(rainbowcar)) {
		int col1 = irand(0, 255, 200);
		int col2 = irand(0, 255, -40);
		int col3 = irand(0, 255, 30);
		int col4 = irand(0, 255, 400);
		set_vehicle_dirt_level(rainbowcar, 0.0f);
		PaintCar(rainbowcar, col1, col2);
		PaintCarExtra(rainbowcar, col3, col4);
	}
}

int ToggleRainbow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if(rainbow) {
		//printf("\nrainbow = false!\n\n");
		rainbow = false;
		return 0;
	}
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	rainbowcar = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(rainbowcar) && IsEntityVehicle(rainbowcar)) {
		//printf("Attempted to paint vehicle");
		rainbow = true;
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintChrome(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 120, 120);
		PaintCarExtra(vehicle, 120, 120);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 0, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintMBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 12, 12);
		PaintCarExtra(vehicle, 12, 12);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintMWhite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 111, 111);
		PaintCarExtra(vehicle, 111, 111);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintMatteWhite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 131, 131);
		PaintCarExtra(vehicle, 131, 131);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintGold(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 158, 158);
		PaintCarExtra(vehicle, 158, 158);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}


int PaintFBlue(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 140, 140);
		PaintCarExtra(vehicle, 140, 140);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintBAngels(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 64, 89);
		PaintCarExtra(vehicle, 64, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 29, 29);
		PaintCarExtra(vehicle, 29, 29);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 41, 41);
		PaintCarExtra(vehicle, 41, 41);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintPurple(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 145, 145);
		PaintCarExtra(vehicle, 145, 145);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintLimeGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 92, 92);
		PaintCarExtra(vehicle, 92, 92);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintHotPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 135, 135);
		PaintCarExtra(vehicle, 135, 135);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo01(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 0, 120);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo02(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 121, 120);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo03(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 112, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo04(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 154, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo05(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 140, 120);
		PaintCarExtra(vehicle, 0, 140);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo06(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 92, 120);
		PaintCarExtra(vehicle, 0, 92);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo07(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 135, 120);
		PaintCarExtra(vehicle, 0, 135);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo08(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 0, 112);
		PaintCarExtra(vehicle, 0, 112);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintCombo09(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, 29, 0);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int RandomPaint(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCar(vehicle, irand(0, 255, 200), irand(0, 255, -40));
		PaintCarExtra(vehicle, irand(0, 255, 30), irand(0, 255, 400));
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 92);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 0);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 112);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 140);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 135);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 145);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int PaintRim6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle;
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (DoesEntityExist(vehicle) && IsEntityVehicle(vehicle)) {
		set_vehicle_dirt_level(vehicle, 0.0f);
		PaintCarExtra(vehicle, 0, 29);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

int ToggleInvisibleCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//printf("Invisible Car = %s\n", invisiblecar ? "true" : "false");
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	int car;
	car = GetCarCharIsIn(PlayerPedId(), PlayerId());
	if (DoesEntityExist(car) && IsEntityVehicle(car)) {
		printf("IsEntityVehicle == true, ");
		if (!invisiblecar) {
			FixCar(car);
			CarVisibleDamage(car, false);
			set_entity_invincible(car, true);
			set_entity_can_be_damaged(car, false);
			invisiblecar = true;
			//printf("On\n");
			ShowMessageOnScreen("~g~ Invincible car turned on!");
		}
		else if (invisiblecar) {
			CarVisibleDamage(car, true);
			set_entity_can_be_damaged(car, true);
			invisiblecar = false;
			set_entity_invincible(car, false);
			//printf("Off\n");
			ShowMessageOnScreen("~g~ Invincible car turned off!");
		}
		//printf("Car is %svisible\n", invisible ? "" : "in");
		invisible = !invisible;
		//set_entity_coords(car, 0, 0, 0, 0, 0, 0, 1);
	}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle.");
	}
	return 0;
}
bool invincibeloop = false;
int ToggleInvincibleCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	
	if (!invincibeloop) {
	ShowMessageOnScreen("~y~ Invincible Vehicle Loop: ~g~ON, ~b~Any vehicle you get in to will be invincible");
	invincibeloop = true;
	}
	else if (invincibeloop) {
	ShowMessageOnScreen("~y~ Invincible Vehicle Loop: ~r~OFF!");
	set_entity_invincible(Veh, false);
	invincibeloop = false;
	}
	return 0;
}


void invinciblecarloop()
{
if (is_ped_in_any_vehicle(PlayerPedId()))
	{
	int car;
	car = GetCarCharIsIn(PlayerPedId(), PlayerId());
	if (DoesEntityExist(car) && IsEntityVehicle(car)) {
			CarVisibleDamage(car, false);
			set_entity_invincible(car, true);
			set_entity_can_be_damaged(car, false);
	}
}
}
bool paintingPlayersCarPink = false;
int paintingPlayersCarPinkIndex = 0;
int paintingPlayersCarPinkTimeout = 310;
int paintingPlayersCarPinkTimeoutCounter = 0;

void PaintOnlinePlayersCarPinkProcess() {
	int subMenuIndex = paintingPlayersCarPinkIndex;
	// check to see if we are at our timeout limit
	if (paintingPlayersCarPinkTimeoutCounter >= paintingPlayersCarPinkTimeout) {
		paintingPlayersCarPink = false;
		ShowMessageOnScreen("~g~ Failed to paint players car. Retrys timed out.");
		paintingPlayersCarPinkTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_dirt_level(Vehicle, 0.0f);
		PaintCar(Vehicle, 135, 135);
		PaintCarExtra(Vehicle, 135, 135);
		ShowMessageOnScreen("~g~ Pink.");
		paintingPlayersCarPinkTimeoutCounter = 0;
		paintingPlayersCarPink = false;
	}

	paintingPlayersCarPinkTimeoutCounter++;
}

int PaintOnlinePlayersCarPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int Selected = selectedMenuIndexes->operator[](1),
		handle = GetPlayerHandle(Selected);
	if (!isInDistance(handle)) {
		ShowMessageOnScreen("~g~ Failed, Vehicle is not close enough");
		return 0;
	}
	if (is_ped_in_any_vehicle(handle)) {
		if (!paintingPlayersCarPink) {
			paintingPlayersCarPinkIndex = Selected;
			paintingPlayersCarPink = true;
		}
	} else
		ShowMessageOnScreen("~g~ Failed, Player is not in any vehicle.");
	return 0;
}

bool paintingPlayersCarAngels = false;
int paintingPlayersCarAngelsIndex = 0;
int paintingPlayersCarAngelsTimeout = 310;
int paintingPlayersCarAngelsTimeoutCounter = 0;

void PaintOnlinePlayersCarAngelsProcess() {
	int subMenuIndex = paintingPlayersCarAngelsIndex;
	// check to see if we are at our timeout limit
	if (paintingPlayersCarAngelsTimeoutCounter >= paintingPlayersCarAngelsTimeout) {
		paintingPlayersCarAngels = false;
		ShowMessageOnScreen("~g~ Failed to paint players car. Retrys timed out.");
		paintingPlayersCarAngelsTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_dirt_level(Vehicle, 0.0f);
		PaintCar(Vehicle, 64, 89);
		PaintCarExtra(Vehicle, 64, 0);
		ShowMessageOnScreen("~g~ Blue Angels.");
		paintingPlayersCarAngelsTimeoutCounter = 0;
		paintingPlayersCarAngels = false;
	}

	paintingPlayersCarAngelsTimeoutCounter++;
}

int PaintOnlinePlayersCarAngels(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int Selected = selectedMenuIndexes->operator[](1),
		handle = GetPlayerHandle(Selected);
	if (!isInDistance(handle)) {
		ShowMessageOnScreen("~g~ Failed, Vehicle is not close enough");
		return 0;
	}
	if (is_ped_in_any_vehicle(handle)) {
		if (!paintingPlayersCarAngels) {
			paintingPlayersCarAngelsIndex = Selected;
			paintingPlayersCarAngels = true;
		}
	} else
		ShowMessageOnScreen("~g~ Failed, Player is not in any vehicle.");
	return 0;
}

bool paintingPlayersCarChrome = false;
int paintingPlayersCarChromeIndex = 0;
int paintingPlayersCarChromeTimeout = 310;
int paintingPlayersCarChromeTimeoutCounter = 0;

void PaintOnlinePlayersCarChromeProcess() {
	int subMenuIndex = paintingPlayersCarChromeIndex;
	// check to see if we are at our timeout limit
	if (paintingPlayersCarChromeTimeoutCounter >= paintingPlayersCarChromeTimeout) {
		paintingPlayersCarChrome = false;
		ShowMessageOnScreen("~g~ Failed to paint players car. Retrys timed out.");
		paintingPlayersCarChromeTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_dirt_level(Vehicle, 0.0f);
		PaintCar(Vehicle, 120, 120);
		PaintCarExtra(Vehicle, 120, 120);
		ShowMessageOnScreen("~g~ Painted players car chrome.");
		paintingPlayersCarChromeTimeoutCounter = 0;
		paintingPlayersCarChrome = false;
	}

	paintingPlayersCarChromeTimeoutCounter++;
}

int PaintOnlinePlayersCarChrome(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int Selected = selectedMenuIndexes->operator[](1),
		handle = GetPlayerHandle(Selected);
	if (!isInDistance(handle)) {
		ShowMessageOnScreen("~g~ Failed, Vehicle is not close enough");
		return 0;
	}
	if (is_ped_in_any_vehicle(handle)) {
		if (!paintingPlayersCarChrome) {
			paintingPlayersCarChromeIndex = Selected;
			paintingPlayersCarChrome = true;
		}
	} else
		ShowMessageOnScreen("~g~ Failed, Player is not in any vehicle.");
	return 0;
}

bool paintingPlayersCar = false;
int paintingPlayersCarIndex = 0;
int paintingPlayersCarTimeout = 310;
int paintingPlayersCarTimeoutCounter = 0;
void PaintOnlinePlayersCarProcess() {
	int subMenuIndex = paintingPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (paintingPlayersCarTimeoutCounter >= paintingPlayersCarTimeout) {
		paintingPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to paint players car. Retrys timed out.");
		paintingPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		PaintCar(Vehicle, irand(0, 255, 1), irand(0, 255, 2));
		PaintCarExtra(Vehicle, irand(0, 255, 3), irand(0, 255, 4));
		set_vehicle_dirt_level(Vehicle, 0.0f);
		ShowMessageOnScreen("~g~ Painted players car");
		paintingPlayersCarTimeoutCounter = 0;
		paintingPlayersCar = false;
	}

	paintingPlayersCarTimeoutCounter++;
}

int PaintOnlinePlayersCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!paintingPlayersCar) {
		paintingPlayersCarIndex = selectedMenuIndexes->operator[](1);
		paintingPlayersCar = true;
	}

	return 0;
}

bool WhoIsThat = false;
int ShowWhoIsTalking(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!WhoIsThat) {
		WhoIsThat = true;
	}
	else if (WhoIsThat) {
		WhoIsThat = false;
	}

	return 0;
}

char* getTalkingName()
 {
	 for (int i = 0; i < 18; i++)
        if (i != PlayerId()){
            if (network_is_player_talking(i)){
                if (!NETWORK_IS_PLAYER_MUTED_BY_ME(i)){
                    return GetPlayerName(i);
				}
			}
		}
 }

void PrintChat() // Shows who's talking...
{ 
	PrintToScreen(getTalkingName(), 0.1525f, 0.0450f, 255, 255, 255, 255, 0.95f, 0.95f, 1, 7);
}

bool explodingPlayersCar = false;
int explodingPlayersCarIndex = 0;
int explodingPlayersCarTimeout = 310;
int explodingPlayersCarTimeoutCounter = 0;

void ExplodeOnlinePlayerVehicleProcess() {
	int subMenuIndex = explodingPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (explodingPlayersCarTimeoutCounter >= explodingPlayersCarTimeout) {
		explodingPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to cause revenge. Retrys timed out.");
		explodingPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		//PaintCar(Vehicle, 135, 135);
		//PaintCarExtra(Vehicle, 135, 135);
		set_vehicle_petrol_tank_health(Vehicle, -1);
		set_vehicle_undriveable(Vehicle, 1);
		ShowMessageOnScreen("~g~ Revenge Served Pink!");
		explodingPlayersCarTimeoutCounter = 0;
		explodingPlayersCar = false;
	}

	explodingPlayersCarTimeoutCounter++;
}

int ExplodeOnlinePlayerVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if (!explodingPlayersCar) {
		explodingPlayersCarIndex = selectedMenuIndexes->operator[](1);
		explodingPlayersCar = true;
	}

	return 0;
}

bool stallPlayersCar = false;
int stallPlayersCarIndex = 0;
int stallPlayersCarTimeout = 310;
int stallPlayersCarTimeoutCounter = 0;

int StallVictomsCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if (!stallPlayersCar) {
		stallPlayersCarIndex = selectedMenuIndexes->operator[](1);
		stallPlayersCar = true;
	}

	return 0;
}

void stallPlayerVehicleProcess() {
	int subMenuIndex = stallPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (stallPlayersCarTimeoutCounter >= stallPlayersCarTimeout) {
		stallPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to shutdown victims car. Retrys timed out.");
		stallPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_petrol_tank_health(Vehicle, 0);
		set_vehicle_undriveable(Vehicle, 1);
		ShowMessageOnScreen("~g~ Victoms car has been shut down!");
		stallPlayersCarTimeoutCounter = 0;
		stallPlayersCar = false;
	}

	stallPlayersCarTimeoutCounter++;
}

bool pinkPlayersCar = false;
int pinkPlayersCarIndex = 0;
int pinkPlayersCarTimeout = 310;
int pinkPlayersCarTimeoutCounter = 0;

void PinkOnlinePlayerVehicleProcess() {
	int subMenuIndex = pinkPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (pinkPlayersCarTimeoutCounter >= pinkPlayersCarTimeout) {
		pinkPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to fuck up players car. Retrys timed out.");
		pinkPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_doors_locked(Vehicle, 4);
		PaintCar(Vehicle, 136, 136);
		PaintCarExtra(Vehicle, 136, 136);
		set_vehicle_petrol_tank_health(Vehicle, -1);
		set_engine_health(Vehicle, -1);
		ShowMessageOnScreen("~g~ Revenge served in pink!.");
		pinkPlayersCarTimeoutCounter = 0;
		pinkPlayersCar = false;
	}

	pinkPlayersCarTimeoutCounter++;
}

int PinkOnlinePlayerVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if (!pinkPlayersCar) {
		pinkPlayersCarIndex = selectedMenuIndexes->operator[](1);
		pinkPlayersCar = true;
	}

	return 0;
}

bool launchingPlayersCar = false;
int launchingPlayersCarIndex = 0;
int launchingPlayersCarTimeout = 310;
int launchingPlayersCarTimeoutCounter = 0;

void SendPlayersCarToSpaceProcess() {
	int subMenuIndex = launchingPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (launchingPlayersCarTimeoutCounter >= launchingPlayersCarTimeout) {
		launchingPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to launch players car. Retrys timed out.");
		launchingPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		apply_force_to_entity(Vehicle, true, 0, 0, 150, 0, 0, 0, true, true, true, true, false, true);
		ShowMessageOnScreen("~g~ Sent players car to space");
		launchingPlayersCarTimeoutCounter = 0;
		launchingPlayersCar = false;
	}

	launchingPlayersCarTimeoutCounter++;
}

bool launchfPlayersCar = false;
int launchfPlayersCarIndex = 0;
int launchfPlayersCarTimeout = 310;
int launchfPlayersCarTimeoutCounter = 0;

void SendPlayersCarForwardProcess() {
	int subMenuIndex = launchfPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (launchfPlayersCarTimeoutCounter >= launchfPlayersCarTimeout) {
		launchfPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to launch players car. Retrys timed out.");
		launchfPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		apply_force_to_entity(Vehicle, true, 0, 150, 0, 0, 0, 0, true, true, true, true, false, true);
		ShowMessageOnScreen("~g~ Launched Players Vehicle Forward!");
		launchfPlayersCarTimeoutCounter = 0;
		launchfPlayersCar = false;
	}

	launchfPlayersCarTimeoutCounter++;
}

bool launchbPlayersCar = false;
int launchbPlayersCarIndex = 0;
int launchbPlayersCarTimeout = 310;
int launchbPlayersCarTimeoutCounter = 0;

void SendPlayersCarBackwardsProcess() {
	int subMenuIndex = launchbPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (launchbPlayersCarTimeoutCounter >= launchbPlayersCarTimeout) {
		launchbPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to launch players car. Retrys timed out.");
		launchbPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		apply_force_to_entity(Vehicle, true, 0, -150, 0, 0, 0, 0, true, true, true, true, false, true);
		ShowMessageOnScreen("~g~ Launched Players Vehicle Backwards!");
		launchbPlayersCarTimeoutCounter = 0;
		launchbPlayersCar = false;
	}

	launchbPlayersCarTimeoutCounter++;
}

int SendPlayersCarToSpace(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!launchingPlayersCar) {
		launchingPlayersCarIndex = selectedMenuIndexes->operator[](1);
		launchingPlayersCar = true;
	}

	return 0;
}

int SendPlayersCarForward(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!launchfPlayersCar) {
		launchfPlayersCarIndex = selectedMenuIndexes->operator[](1);
		launchfPlayersCar = true;
	}

	return 0;
}

int SendPlayersCarBackwards(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!launchbPlayersCar) {
		launchbPlayersCarIndex = selectedMenuIndexes->operator[](1);
		launchbPlayersCar = true;
	}

	return 0;
}

int CleanPedBody(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
    CLEAR_PED_BLOOD_DAMAGE(PlayerPedId());
    RESET_PED_VISIBLE_DAMAGE(PlayerPedId());
	return 0;
}

bool popTheirTyres = false;
int popTheirTyresIndex = 0;
int popTheirTyresTimeout = 310;
int popTheirTyresTimeoutCounter = 0;
void popTheirTyresProcess(){
	int subMenuIndex = popTheirTyresIndex;

	// check to see if we are at our timeout limit
	if (popTheirTyresTimeoutCounter >= popTheirTyresTimeout) {
		popTheirTyres = false;
		ShowMessageOnScreen("~g~ Failed to flatten player's vehicle tyres. Retrys timed out.");
		popTheirTyresTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_tyres_can_burst(Vehicle, true);
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 0, 0)){
			PopCarTyre(Vehicle, 0, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 1, 0)){
			PopCarTyre(Vehicle, 1, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 2, 0)){
			PopCarTyre(Vehicle, 2, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 3, 0)){
			PopCarTyre(Vehicle, 3, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 4, 0)){
			PopCarTyre(Vehicle, 4, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 5, 0)){
			PopCarTyre(Vehicle, 5, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 6, 0)){
			PopCarTyre(Vehicle, 6, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(Vehicle, 7, 0)){
			PopCarTyre(Vehicle, 7, 1, 1148846080);
		}
		ShowMessageOnScreen("~g~ Player's Tyres Flattened!");
		popTheirTyresTimeoutCounter = 0;
		popTheirTyres = false;
	}

	 popTheirTyresTimeoutCounter++;

}

bool flipCar180 = false;
float flipCar180Coords[3];
int flipCar180Index = 0;
int flipCar180Timeout = 310;
int flipCar180TimeoutCounter = 0;
void flipCar180Process(){
	int subMenuIndex = flipCar180Index;

	// check to see if we are at our timeout limit
	if (flipCar180TimeoutCounter >= flipCar180Timeout) {
		flipCar180 = false;
		ShowMessageOnScreen("~g~ Failed to flip their vehicle around. Retrys timed out.");
		flipCar180TimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);
	int Heading = get_entity_heading(Vehicle);
	float speed = get_entity_speed(Vehicle);

	if (RequestNetworkControl(Player, Vehicle)) {
		
		if(DoesEntityExist(Player)){
			GetEntityCoords(Vehicle, flipCar180Coords);
			if(Heading > 180.0) Heading -= 180.0;
			else Heading += 180.0;
			set_entity_coords(Vehicle, flipCar180Coords[0], flipCar180Coords[1], flipCar180Coords[2], 0, 0, 0, 1);
			set_entity_heading(Vehicle, Heading);
			SET_VEHICLE_FORWARD_SPEED(Vehicle, speed);
			ShowMessageOnScreen("~g~ Player's vehicle flipped 180!");
		}
		flipCar180TimeoutCounter = 0;
		flipCar180 = false;
	}

	 flipCar180TimeoutCounter++;

}

int flipCar180Now(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
     
	if (!flipCar180) {
		flipCar180Index = selectedMenuIndexes->operator[](1);
		flipCar180 = true;
	}

	return 0;
}

bool rotateCarTrollb = false;
bool rotateCarTrollLoop = false;
bool rotateVehicleTrollLoop = false;
int rotateCarTrollIndex = 0;
int rotateCarTrollTimeout = 310;
int rotateCarTrollTimeoutCounter = 0;
void rotateCarTrollProcess(){
	int subMenuIndex = rotateCarTrollIndex;

	// check to see if we are at our timeout limit
	if (rotateCarTrollTimeoutCounter >= rotateCarTrollTimeout) {
	    rotateCarTrollb = false;
		ShowMessageOnScreen("~g~ Failed to flip their vehicle around. Retrys timed out.");
		rotateCarTrollTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);
	int Heading = get_entity_heading(Vehicle);
	//float speed = get_entity_speed(Vehicle);

	if (RequestNetworkControl(Player, Vehicle)) {
		
		if(DoesEntityExist(Player)){
		  if(rotateVehicleTrollLoop){
			if(rotateCarTrollLoop) Heading += 5;
			set_entity_heading(Vehicle, Heading);
		  }
		}
		rotateCarTrollTimeoutCounter = 0;
		rotateCarTrollb = false;
	}

	 rotateCarTrollTimeoutCounter++;

}

int rotateCarTroll(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
     
	if (!rotateCarTrollb) {
		rotateCarTrollIndex = selectedMenuIndexes->operator[](1);
		rotateCarTrollb = true;
		rotateCarTrollLoop = true;
		rotateVehicleTrollLoop = true;
		ShowMessageOnScreen("~y~Rotate Vehicle Troll: ~g~ON!");
	}
	else if (rotateCarTrollb) {
		rotateCarTrollIndex = selectedMenuIndexes->operator[](1);
		rotateCarTrollb = false;
		rotateCarTrollLoop = false;
		rotateVehicleTrollLoop = false;
		ShowMessageOnScreen("~y~Rotate Vehicle Troll: ~r~OFF!");
	}

	return 0;
}

int PopTheirTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
     
	if (!popTheirTyres) {
		popTheirTyresIndex = selectedMenuIndexes->operator[](1);
		popTheirTyres = true;
	}

	return 0;
}

float WaypointPos1[3];

int DriveYourselfToWP(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
     
	int playerVehicle = GetCarCharIsIn(PlayerPedId(), PlayerId());
	int waypoint = get_first_blip_info_id(8);
	if(does_blip_exist(waypoint)) {
		get_blip_coords(waypoint, WaypointPos1);
		if(get_ground_z_for_3d_coord(WaypointPos1[0], WaypointPos1[1], 600.0f, &WaypointPos1[2])) {
	TASK_VEHICLE_DRIVE_TO_COORD(PlayerPedId(), playerVehicle, WaypointPos1[0], WaypointPos1[1], WaypointPos1[2], 40, 1, get_entity_model(playerVehicle), 1, 0xC00AB, -1);
		}
	}
	else{
		ShowMessageOnScreen("Set A Waypoint First!");
	}
	return 0;
}

//TASK_VEHICLE_DRIVE_TO_COORD

bool isrc = false;
int Savedvehicle[2];// {attached handle, your cars handle}

bool detachTowTruckCar = false;
int detachTowTruckIndex = 0;
int detachTowTruckTimeout = 310;
int detachTowTruckTimeoutCounter = 0;

void DetachTowTruckProcess() {
	int subMenuIndex = detachTowTruckIndex;

	// check to see if we are at our timeout limit
	if (detachTowTruckTimeoutCounter >= detachTowTruckTimeout) {
		detachTowTruckCar = false;
		ShowMessageOnScreen("~g~ Failed to detach tow from players car. Retrys timed out.");
		detachTowTruckTimeoutCounter = 0;
		return;
	}

	int Handle = GetCarCharIsIn(PlayerPedId(), PlayerId());
	int Player = GetPlayerHandle(subMenuIndex);

	if(Savedvehicle[1] != Handle || Savedvehicle[1] == 0 || !DoesEntityExist(Savedvehicle[0])) {
		detachTowTruckCar = false;
		detachTowTruckTimeoutCounter = 0;
		return;
	}

	if (RequestNetworkControl(Player, Savedvehicle[0])) {
		detach_entity(Savedvehicle[0]);
		set_vehicle_doors_locked(Savedvehicle[0], 0);

		if (isrc) {
			set_entity_visible(Savedvehicle[1], true);
			set_entity_collision(Savedvehicle[0], true);
		}

		set_entity_collision(Savedvehicle[0], true);

		ShowMessageOnScreen("~g~ Detach success");
		detachTowTruckTimeoutCounter = 0;

		detachTowTruckCar = false;
	}

	detachTowTruckTimeoutCounter++;
}

int DetachTowTruck(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if (!detachTowTruckCar) {
		detachTowTruckIndex = selectedMenuIndexes->operator[](1);
		detachTowTruckCar = true;
	}

	return 0;
}

bool detachMyCar = false;
int detachMyCarIndex = 0;
int detachMyCarTimeout = 310;
int detachMyCarTimeoutCounter = 0;

void DetachMyCarProcess() {
	int subMenuIndex = detachMyCarIndex;

	// check to see if we are at our timeout limit
	if (detachMyCarTimeoutCounter >= detachMyCarTimeout) {
		detachMyCar = false;
		ShowMessageOnScreen("~g~ Failed to detach from players car. Retrys timed out.");
		detachMyCarTimeoutCounter = 0;
		return;
	}

	int Handle = GetCarCharIsIn(PlayerPedId(), PlayerId());
	int Player = GetPlayerHandle(subMenuIndex);

	Savedvehicle[0] = GetCarCharIsIn(Handle, subMenuIndex);
	Savedvehicle[1] = GetCarCharIsIn(PlayerPedId(), PlayerId());

	if (RequestNetworkControl(Player, Savedvehicle[1])) {
		detach_entity(Savedvehicle[1]);
		set_entity_collision(Savedvehicle[1], true);
		ShowMessageOnScreen("~g~ Detach success");
		detachMyCarTimeoutCounter = 0;
		detachMyCar = false;
	}
	detachMyCarTimeoutCounter++;
}

int DetachMyCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if (!detachMyCar) {
		detachMyCarIndex = selectedMenuIndexes->operator[](1);
		detachMyCar = true;
	}

	return 0;
}

bool towTruckCar = false;
int towTruckCarIndex = 0;
int towTruckCarTimeout = 310;
int towTruckCarTimeoutCounter = 0;

void TowTruckProcess() {
	int subMenuIndex = towTruckCarIndex;

	// check to see if we are at our timeout limit
	if (towTruckCarTimeoutCounter >= towTruckCarTimeout) {
		towTruckCar = false;
		ShowMessageOnScreen("~g~ Failed to tow players car. Retrys timed out.");
		towTruckCarTimeoutCounter = 0;
		return;
	}

	int Handle = GetPlayerHandle(subMenuIndex);
	//int Player = GetPlayerHandle(subMenuIndex);
	//int Vehicle = GetCarCharIsIn(Player, 0);

	// Ours and victims car handles
	Savedvehicle[0] = GetCarCharIsIn(Handle, subMenuIndex);
	Savedvehicle[1] = GetCarCharIsIn(PlayerPedId(), PlayerId());

		if (Savedvehicle[0] == Savedvehicle[1])
	{
		ShowMessageOnScreen("~g~ You are trying to tow truck your own car retard, If we allowed this we would freeze.");
		towTruckCarTimeoutCounter = 0;
		towTruckCar = false;
		return;
	}

	// Our position
	float Position[3];
    GetEntityCoords(Handle, Position);
	printf("Player X = %f\n", Position[0]);
    printf("Player Y = %f\n", Position[1]);
	printf("Player Z = %f\n", Position[2]);

	if (RequestNetworkControl(Handle, Savedvehicle[0])) {
		set_vehicle_doors_locked(Savedvehicle[0], 4);
		attach_entity_to_entity(Savedvehicle[0], Savedvehicle[1], 0, 0, -3.9, 0, 0, 0, 0);

		ShowMessageOnScreen("~g~ Attached player to vehicle");
		towTruckCarTimeoutCounter = 0;

		towTruckCar = false;
	}

	towTruckCarTimeoutCounter++;
}
bool towTruckb = false;
int TowTruck(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!towTruckb) {
		towTruckCarIndex = selectedMenuIndexes->operator[](1);
		towTruckCar = true;
		towTruckb = true;
	}
	else if(towTruckb){
		detachTowTruckIndex = selectedMenuIndexes->operator[](1);
		detachTowTruckCar = true;
		towTruckb = false;
	}

	return 0;
}

bool TowMyCarCar = false;
int TowMyCarCarIndex = 0;
int TowMyCarCarTimeout = 310;
int TowMyCarCarTimeoutCounter = 0;

void TowMyCarProcess() {
	int subMenuIndex = TowMyCarCarIndex;

	// check to see if we are at our timeout limit
	if (TowMyCarCarTimeoutCounter >= TowMyCarCarTimeout) {
		TowMyCarCar = false;
		ShowMessageOnScreen("~g~ Failed to make them tow you. Retrys timed out.");
		TowMyCarCarTimeoutCounter = 0;
		return;
	}

	int Handle = GetPlayerHandle(subMenuIndex);
	//int Player = GetPlayerHandle(subMenuIndex);
	//int Vehicle = GetCarCharIsIn(Player, 0);

	// Ours and victims car handles
	Savedvehicle[0] = GetCarCharIsIn(Handle, subMenuIndex);
	Savedvehicle[1] = GetCarCharIsIn(PlayerPedId(), PlayerId());

		if (Savedvehicle[0] == Savedvehicle[1])
	{
		ShowMessageOnScreen("~g~ You are trying to attach to your own car retard, If we allowed this we would freeze.");
		TowMyCarCarTimeoutCounter = 0;
		TowMyCarCar = false;
		return;
	}

	// Our position
	float Position[3];
    GetEntityCoords(Handle, Position);

	if (RequestNetworkControl(Handle, Savedvehicle[1])) {
		//set_vehicle_doors_locked(Savedvehicle[0], 4);
		attach_entity_to_entity(Savedvehicle[1], Savedvehicle[0], 0, 0, -3.9, 2, 0, 0, 0);

		ShowMessageOnScreen("~g~ Attached your vehicle to theirs!");
		TowMyCarCarTimeoutCounter = 0;

		TowMyCarCar = false;
	}

	TowMyCarCarTimeoutCounter++;
}

bool towMyCarB = false;
int TowMyCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!towMyCarB) {
		TowMyCarCarIndex = selectedMenuIndexes->operator[](1);
		TowMyCarCar = true;
		towMyCarB = true;
	}
	else if(towMyCarB){
		detachMyCarIndex = selectedMenuIndexes->operator[](1);
		detachMyCar = true;
		towMyCarB = false;
	}

	return 0;
}

bool rcCar = false;
int rcCarIndex = 0;
int rcCarTimeout = 310;
int rcCarTimeoutCounter = 0;

void RcCarProcess() {
	int subMenuIndex = rcCarIndex;

	// check to see if we are at our timeout limit
	if (rcCarTimeoutCounter >= rcCarTimeout) {
		rcCar = false;
		ShowMessageOnScreen("~g~ Failed to rc players car. Retrys timed out.");
		rcCarTimeoutCounter = 0;
		return;
	}

	int Handle = GetPlayerHandle(subMenuIndex);
	//int Player = GetPlayerHandle(subMenuIndex);
	//int Vehicle = GetCarCharIsIn(Player, 0);

	// Ours and victims car handles
	Savedvehicle[0] = GetCarCharIsIn(Handle, subMenuIndex);
	Savedvehicle[1] = GetCarCharIsIn(PlayerPedId(), PlayerId());

		if (Savedvehicle[0] == Savedvehicle[1])
	{
		ShowMessageOnScreen("~g~ You are trying to remote control your own car retard, If we allowed this we would freeze.");
		rcCarTimeoutCounter = 0;
		rcCar = false;
		return;
	}

	if (RequestNetworkControl(Handle, Savedvehicle[0])) {
		if (is_entity_visible(Savedvehicle[1])) {
			set_entity_visible(Savedvehicle[1], false);
		}

		set_vehicle_doors_locked(Savedvehicle[0], 4);
		attach_entity_to_entity(Savedvehicle[0], Savedvehicle[1], 0, 0, 0, 0, 0, 0, 0);
		set_entity_visible(Savedvehicle[0], true);

		ShowMessageOnScreen("~g~ RC car success");
		rcCarTimeoutCounter = 0;

		isrc = true;
		rcCar = false;
	}

	rcCarTimeoutCounter++;
}

bool rcCarB = false;
int RcCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if (!rcCarB) {
		rcCarIndex = selectedMenuIndexes->operator[](1);
		rcCar = true;
		rcCarB = true;
	}
	else if (rcCarB){
		rcCarIndex = selectedMenuIndexes->operator[](1);
		detachTowTruckCar = true;
		rcCarB = true;
	}

	return 0;
}

bool lockPlayersCar = false;
int lockPlayersCarIndex = 0;
int lockPlayersCarTimeout = 310;
int lockPlayersCarTimeoutCounter = 0;

void LockPlayersDoorsProcess() {
	int subMenuIndex = lockPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (lockPlayersCarTimeoutCounter >= lockPlayersCarTimeout) {
		lockPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to lock players car. Retrys timed out.");
		lockPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_doors_locked(Vehicle, 4);
		ShowMessageOnScreen("~g~ Locked players doors");
		lockPlayersCarTimeoutCounter = 0;
		lockPlayersCar = false;
	}

	lockPlayersCarTimeoutCounter++;
}

int LockPlayersDoors(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!lockPlayersCar) {
		lockPlayersCarIndex = selectedMenuIndexes->operator[](1);
		lockPlayersCar = true;
	}

	return 0;
}

bool flipPlayersCar = false;
int flipPlayersCarIndex = 0;
int flipPlayersCarTimeout = 310;
int flipPlayersCarTimeoutCounter = 0;

void FlipPlayersDoorsProcess() {
	int subMenuIndex = flipPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (flipPlayersCarTimeoutCounter >= flipPlayersCarTimeout) {
		flipPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to flip players car. Retrys timed out.");
		flipPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		SET_VEHICLE_ON_GROUND_PROPERLY(Vehicle);
		ShowMessageOnScreen("~g~ Flipped players car!");
		flipPlayersCarTimeoutCounter = 0;
		flipPlayersCar = false;
	}

	flipPlayersCarTimeoutCounter++;
}

int FlipOnlineVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!flipPlayersCar) {
		flipPlayersCarIndex = selectedMenuIndexes->operator[](1);
		flipPlayersCar = true;
	}

	return 0;
}

bool NoGodHotRod = false;
int NoGodHotRodIndex = 0;
int NoGodHotRodTimeout = 310;
int NoGodHotRodTimeoutCounter = 0;

void NoGodHotRodProcess() {
	int subMenuIndex = NoGodHotRodIndex;

	// check to see if we are at our timeout limit
	if (NoGodHotRodTimeoutCounter >= NoGodHotRodTimeout) {
		NoGodHotRod = false;
		ShowMessageOnScreen("~g~ Failed to turn off player's vehicle collision. Retrys timed out.");
		NoGodHotRodTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_entity_collision(Vehicle, false);
		set_entity_collision(Vehicle, false);
		set_entity_collision(Vehicle, false);
		set_entity_collision(Vehicle, false);
		set_entity_collision(Vehicle, false);
		ShowMessageOnScreen("~g~ Player's Vehicle Collision Should Be Off!");
		NoGodHotRodTimeoutCounter = 0;
		NoGodHotRod = false;
	}

	NoGodHotRodTimeoutCounter++;
}

int TakeAwayInvincibilityOnline(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!NoGodHotRod) {
		NoGodHotRodIndex = selectedMenuIndexes->operator[](1);
		NoGodHotRod = true;
	}

	return 0;
}

bool unlockPlayersCar = false;
int unlockPlayersCarIndex = 0;
int unlockPlayersCarTimeout = 310;
int unlockPlayersCarTimeoutCounter = 0;

void unLockPlayersDoorsProcess() {
	int subMenuIndex = unlockPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (unlockPlayersCarTimeoutCounter >= unlockPlayersCarTimeout) {
		unlockPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to unlock players car. Retrys timed out.");
		unlockPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		set_vehicle_doors_locked(Vehicle, 0);
		ShowMessageOnScreen("~g~ Unlocked players doors");
		unlockPlayersCarTimeoutCounter = 0;
		unlockPlayersCar = false;
	}

	unlockPlayersCarTimeoutCounter++;
}

int UnlockPlayersDoors(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!unlockPlayersCar) {
		unlockPlayersCarIndex = selectedMenuIndexes->operator[](1);
		unlockPlayersCar = true;
	}

	return 0;
}

//

bool ChangePlate = false;
int ChangePlateIndex = 0;
int ChangePlateTimeout = 310;
int ChangePlateTimeoutCounter = 0;

void ChangePlateProccess() {
	int subMenuIndex = ChangePlateIndex;

	// check to see if we are at our timeout limit
	if (ChangePlateTimeoutCounter >= ChangePlateTimeout) {
		ChangePlate = false;
		ShowMessageOnScreen("~g~ Failed to change plate. Retrys timed out.");
		ChangePlateTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		//set_vehicle_doors_locked(Vehicle, 4);
		set_number_plate(Vehicle, " IM GAY ");
		ShowMessageOnScreen("~g~ Changed players plate to IM GAY");
		ChangePlateTimeoutCounter = 0;
		ChangePlate = false;
	}

	ChangePlateTimeoutCounter++;
}

int ChangePlatePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	CarPed = selectedMenuIndexes->operator[](1);
	int player = selectedMenuIndexes->operator[](1);
	animid = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	int Vehicle = GetCarCharIsIn(ped, 0);
	float Pos[3];
	GetEntityCoords(ped, Pos);
	set_entity_coords(PlayerPedId(), Pos[0], Pos[1], Pos[2]);
	kidnap = true;
	warp = true;
	set_vehicle_doors_locked(Vehicle, 4);
	//ShowMessageOnScreen("~g~ Not completed");
	return 0;
}

bool KickinggPlayer = false;
int KickingPlayerIndex = 0;
int KickingPlayerTimeout = 310;
int KickingPlayerTimeoutCounter = 0;
void LMAOProccess()
{
int subMenuIndex = KickingPlayerIndex;
	// check to see if we are at our timeout limit
	if (KickingPlayerTimeoutCounter >= KickingPlayerTimeout) {
		KickinggPlayer = false;
		ShowMessageOnScreen("~g~ Failed to control vehicle. Retrys timed out.");
		KickingPlayerTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
	    set_vehicle_doors_locked(Vehicle, 4);
		clear_ped_tasks_immediately(Player);
		ShowMessageOnScreen("~g~ Locked player out of their personal vehicle!");
		KickingPlayerTimeoutCounter = 0;

		KickinggPlayer = false;
	}

	KickingPlayerTimeoutCounter++;
}

int LMAO(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	CarPed = selectedMenuIndexes->operator[](1);
	int player = selectedMenuIndexes->operator[](1);
	animid = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	int Vehicle = GetCarCharIsIn(ped, 0);
	float Pos[3];
	GetEntityCoords(ped, Pos);
	//set_entity_coords(PlayerPedId(), Pos[0], Pos[1], Pos[2]);
	if (is_ped_on_foot(ped)) {
	ShowMessageOnScreen("~g~ Player isn't in any vehicle");
	return 0;
	}
    if (!KickinggPlayer) {
		KickinggPlayer = true;
		KickingPlayerIndex = selectedMenuIndexes->operator[](1);
	}
	kidnap = true;
	//warp = true;
	//ShowMessageOnScreen("~g~ Not completed");
	return 0;
}

bool teleportingPlayer = false;
int teleportingPlayerIndex = 0;
int teleportingPlayerTimeout = 310;
int teleportingPlayerTimeoutCounter = 0;

void TeleportPlayerProcess() {
	int subMenuIndex = teleportingPlayerIndex;

	// check to see if we are at our timeout limit
	if (teleportingPlayerTimeoutCounter >= teleportingPlayerTimeout) {
		teleportingPlayer = false;
		ShowMessageOnScreen("~g~ Failed to teleport player. Retrys timed out.");
		teleportingPlayerTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		float Position[3];
		GetEntityCoords(PlayerPedId(), Position);

		set_entity_coords(Vehicle, Position[0], Position[1] + 2.0f, Position[2] + 12.0f, 0, 0, 0, 1);

		ShowMessageOnScreen("~g~ Teleported player");
		teleportingPlayerTimeoutCounter = 0;

		teleportingPlayer = false;
	}

	teleportingPlayerTimeoutCounter++;
}

int TeleportPlayerToMe(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	// Check to see if we are in the process of teleporting a player
	if (!teleportingPlayer) {
		teleportingPlayer = true;
		teleportingPlayerIndex = selectedMenuIndexes->operator[](1);
	}

	return 0;
}

bool teleportingPlayer2 = false;
int teleportingPlayerIndex2 = 0;
int teleportingPlayerTimeout2 = 310;
int teleportingPlayerTimeoutCounter2 = 0;

void TeleportPlayerProcess2() {
	int subMenuIndex = teleportingPlayerIndex;

	// check to see if we are at our timeout limit
	if (teleportingPlayerTimeoutCounter2 >= teleportingPlayerTimeout2) {
		teleportingPlayer2 = false;
		ShowMessageOnScreen("~g~ Failed to teleport player. Retrys timed out.");
		teleportingPlayerTimeoutCounter2 = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		float Position[3];
		GetEntityCoords(PlayerPedId(), Position);

		set_entity_coords(Vehicle, Position[0], Position[1], Position[2], 0, 0, 0, 1);

		ShowMessageOnScreen("~g~ Teleported Player");
		teleportingPlayerTimeoutCounter2 = 0;

		teleportingPlayer2 = false;
	}

	teleportingPlayerTimeoutCounter2++;
}

int TeleportPlayerToMe2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	// Check to see if we are in the process of teleporting a player
	if (!teleportingPlayer2) {
		teleportingPlayer2 = true;
		teleportingPlayerIndex2 = selectedMenuIndexes->operator[](1);
	}

	return 0;
}

bool Delete = false;
int DeleteIndex = 0;
int DeleteTimeout = 310;
int DeleteTimeoutCounter = 0;
int deletevehicle;
bool deleted = false;
void DeleteProcess() {
	int subMenuIndex = DeleteIndex;

	// check to see if we are at our timeout limit
	if (DeleteTimeoutCounter >= DeleteTimeout) {
		Delete = false;
		ShowMessageOnScreen("~g~ Failed to delete vehicle. Retrys timed out.");
		DeleteTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		deletevehicle = Vehicle;
		deleted = true;
		ShowMessageOnScreen("~g~ Deleted Players Vehicle");
		DeleteTimeoutCounter = 0;
		Delete = false;
	}

	DeleteTimeoutCounter++;
}

bool DeleteAllVeh = false;
int DeleteallIndex = 0;
int DeleteallTimeout = 310;
int DeleteallTimeoutCounter = 0;
int deleteallvehicle;
bool deletedall = false;
void DeleteAllProcess() {
	int subMenuIndex = DeleteallIndex;

	// check to see if we are at our timeout limit
	if (DeleteallTimeoutCounter >= DeleteallTimeout) {
		DeleteAllVeh = false;
		ShowMessageOnScreen("~r~ Failed to delete everyone's vehicles. Retrys timed out.");
		DeleteallTimeoutCounter = 0;
		return;
	}

	int i = 0;
	for (i = 0;i<18;i++)
    {
    if (i == PlayerId()) continue;

	int Player = GetPlayerHandle(i);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		deletevehicle = Vehicle;
		DeleteAllVeh = true;
		ShowMessageOnScreen("~y~ Deleted Everyone's Vehicle!");
		DeleteallTimeoutCounter = 0;
		DeleteAllVeh = false;
	}
	}

	DeleteallTimeoutCounter++;
}

int DeleteAllPlayersVehicles(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	// Check to see if we are in the process of teleporting a player
	if (!DeleteAllVeh) {
		DeleteAllVeh = true;
		DeleteallIndex = selectedMenuIndexes->operator[](1);
	}

	return 0;
}

int DeleteVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	// Check to see if we are in the process of teleporting a player
	if (!Delete) {
		Delete = true;
		DeleteIndex = selectedMenuIndexes->operator[](1);
	}

	return 0;
}


bool da = false;
bool air = false;
bool dw = false;
bool waterwheel = false;
int DriveWater(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!dw) {
	dw = true;
	da = false;
	ShowMessageOnScreen("~g~ Drive on water on");
	model = -1003748966;
    objectspawn = true;
	waterwheel = true;
	air = false;
	}
	else if (dw) {
	dw = false;
	ShowMessageOnScreen("~g~ Drive on water off");
	}

	return 0;
}
bool driveairz = false;
bool speedo = false;
float speedmul;
int DriveAirGz(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!speedo) {
	ShowMessageOnScreen("~g~ Speedometer turned on");
	speedmul = 1.5;
	speedo = true;
	}
	else if (speedo) {
    ShowMessageOnScreen("~g~ Speedometer turned off");
	speedo = false;
	}
	return 0;
}

bool speedgunrp = false;
float speedmuls;
bool speeder = false;
int speedGunRP(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!speeder) {
	ShowMessageOnScreen("~g~ Speedgun turned on");
	speedmuls = 1.5;
	speeder = true;
	}
	else if (speeder) {
    ShowMessageOnScreen("~g~ Speedgun turned off");
	speeder = false;
	}
	return 0;
}

int creatorUnlock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_vehicle_doors_locked(objecthandle, 4); //Locked
	ShowMessageOnScreen("~y~Vehicle Doors Locked!");
	}
	return 0;
}
bool creator180LP = false;
bool HeadingLoop = false;
int creator180Loop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	  if(!creator180LP){
		creator180LP = true;
		HeadingLoop = true;
		ShowMessageOnScreen("~y~Creator Vehicle Loop: ~g~ON!");
	  }
	  else if(creator180LP){
		creator180LP = false;
		HeadingLoop = true;
		ShowMessageOnScreen("~y~Creator Vehicle Loop: ~r~OFF!");
	  }
	}
	return 0;
}

bool creator1802LP = false;
bool HeadingLoop2 = false;
int creator180Loop2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	  if(!creator1802LP){
		creator1802LP = true;
		HeadingLoop2 = true;
		ShowMessageOnScreen("~y~Creator Vehicle Loop 2: ~g~ON!");
	  }
	  else if(creator1802LP){
		creator1802LP = false;
		HeadingLoop2 = true;
		ShowMessageOnScreen("~y~Creator Vehicle Loop 2: ~r~OFF!");
	  }
	}
	return 0;
}

bool creator1803LP = false;
bool HeadingLoop3 = false;
int creator180Loop3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	  if(!creator1803LP){
		creator1803LP = true;
		HeadingLoop3 = true;
		ShowMessageOnScreen("~y~Object Rotation Loop: ~g~ON!");
	  }
	  else if(creator1803LP){
		creator1803LP = false;
		HeadingLoop3 = false;
		ShowMessageOnScreen("~y~Object Rotation Loop: ~r~OFF!");
	  }
	}
	return 0;
}

bool creator360LP = false;
bool PitchLoop = false;
int creator360Mod(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	  if(!creator360LP){
		creator360LP = true;
		PitchLoop = true;
		ShowMessageOnScreen("~y~Object Pitch Loop: ~g~ON!");
	  }
	  else if(creator360LP){
		creator360LP = false;
		PitchLoop = false;
		ShowMessageOnScreen("~y~Object Pitch Loop: ~r~OFF!");
	  }
	}
	return 0;
}

void creator180LoopProcess(){
	float Heading = get_entity_heading(objecthandle);
			if(HeadingLoop) Heading += 3;
			set_entity_heading(objecthandle, Heading);
}

void creator180LoopProcess2(){
	float Heading = get_entity_heading(objecthandle);
			if(HeadingLoop2) Heading += 12;
			set_entity_heading(objecthandle, Heading);
}

void creator180LoopProcess3(){
	float Heading = get_entity_heading(objecthandle);
			if(HeadingLoop3) Heading += 180;
			set_entity_heading(objecthandle, Heading);
}

void creator360RotationProcess(){
	float objPitch = get_entity_pitch(objecthandle);
	       if(PitchLoop) objPitch += 3;
	       set_entity_rotation(objecthandle,objPitch,objectroll,objectyaw,2,1);
}

bool cInvisibleObj = false;
int creatorInvisible(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	  network_request_control_of_entity(objecthandle);
	  if(!cInvisibleObj){
	    set_entity_visible(objecthandle, false);
		cInvisibleObj = true;
		ShowMessageOnScreen("~y~Object Invisibility: ~g~ON!");
	  }
	  else if(cInvisibleObj){
	    set_entity_visible(objecthandle, true);
		cInvisibleObj = false;
		ShowMessageOnScreen("~y~Object Invisibility: ~r~OFF");
	  }
	}
	return 0;
}

int creatorFixVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	FixCar(objecthandle);
	ShowMessageOnScreen("~y~Fixed Vehicle!");
	}
	return 0;
}

int creatorVehHorn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	     START_VEHICLE_HORN(objecthandle, 30000, get_hash_key("HELDDOWN"), true);
	     ShowMessageOnScreen("~y~Vehicle Horn Activated for 30 seconds!");
	}
	return 0;
}

float clearObjCoords[3];
int clearNearbyObjects(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	GetEntityCoords(PlayerPedId(), clearObjCoords);
	CLEAR_AREA_OF_OBJECTS(clearObjCoords[0], clearObjCoords[1], clearObjCoords[2], 80.0f, 2);
	ShowMessageOnScreen("Area Cleared of Objects!");
	return 0;
}

float clearCopsCoords[3];
int clearNearbyCops(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	GetEntityCoords(PlayerPedId(), clearCopsCoords);
	CLEAR_AREA_OF_OBJECTS(clearCopsCoords[0], clearCopsCoords[1], clearCopsCoords[2], 400.0f, 1);
	ShowMessageOnScreen("Area Cleared of Cops!");
	return 0;
}

int creatorFlipVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	SET_VEHICLE_ON_GROUND_PROPERLY(objecthandle);
	ShowMessageOnScreen("~y~Flipped Vehicle!");
	}
	return 0;
}

int creatorDeleteVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	deletevehicle = objecthandle;
	deleted = true;
	ShowMessageOnScreen("~y~Deleted Vehicle!");
	}
	return 0;
}

int creatorInvincible(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_entity_invincible(objecthandle, true);
	ShowMessageOnScreen("~y~Vehicle Set Invincible!");
	}
	return 0;
}

int creatorNotInvincible(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_entity_invincible(objecthandle, false);
	ShowMessageOnScreen("~y~Vehicle Is Now Vulnerable!");
	}
	return 0;
}

int creatorBulletproof(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_vehicle_tyres_can_burst(objecthandle, 0);
	ShowMessageOnScreen("~y~Vehicle Tires Bulletproof!");
	}
	return 0;
}

//set_vehicle_tyres_can_burst(vehicle, 0);

bool cDoor0 = false;
int creatorDoorsOpen0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(!cDoor0){
    set_vehicle_door_open(objecthandle, 0);
	ShowMessageOnScreen("~y~Door 0 Opened!");
	cDoor0 = true;
	}
	else if(cDoor0){
	set_vehicle_door_shut(objecthandle, 0);
	ShowMessageOnScreen("~y~Door 0 Closed!");
	cDoor0 = false;
	}
	return 0;
}
bool cDoor1 = false;
int creatorDoorsOpen1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(!cDoor1){
    set_vehicle_door_open(objecthandle, 1);
	ShowMessageOnScreen("~y~Door 1 Opened!");
	cDoor1 = true;
	}
	else if(cDoor1){
	set_vehicle_door_shut(objecthandle, 1);
	ShowMessageOnScreen("~y~Door 1 Closed!");
	cDoor1 = false;
	}
	return 0;
}
bool cDoor2 = false;
int creatorDoorsOpen2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(!cDoor2){
    set_vehicle_door_open(objecthandle, 2);
	ShowMessageOnScreen("~y~Door 2 Opened!");
	cDoor2 = true;
	}
	else if(cDoor2){
	set_vehicle_door_shut(objecthandle, 2);
	ShowMessageOnScreen("~y~Door 2 Closed!");
	cDoor2 = false;
	}
	return 0;
}
bool cDoor3 = false;
int creatorDoorsOpen3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(!cDoor3){
    set_vehicle_door_open(objecthandle, 3);
	ShowMessageOnScreen("~y~Door 3 Opened!");
	cDoor3 = true;
	}
	else if(cDoor3){
	set_vehicle_door_shut(objecthandle, 3);
	ShowMessageOnScreen("~y~Door 3 Closed!");
	cDoor3 = false;
	}
	return 0;
}
bool cDoor4 = false;
int creatorDoorsOpen4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(!cDoor4){
    set_vehicle_door_open(objecthandle, 4);
	ShowMessageOnScreen("~y~Door 4 Opened!");
	cDoor4 = true;
	}
	else if(cDoor4){
	set_vehicle_door_shut(objecthandle, 4);
	ShowMessageOnScreen("~y~Door 4 Closed!");
	cDoor4 = false;
	}
	return 0;
}
bool cDoor5 = false;
int creatorDoorsOpen5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(!cDoor5){
    set_vehicle_door_open(objecthandle, 5);
	ShowMessageOnScreen("~y~Door 5 Opened!");
	cDoor5 = true;
	}
	else if(cDoor5){
	set_vehicle_door_shut(objecthandle, 5);
	ShowMessageOnScreen("~y~Door 5 Closed!");
	cDoor5 = false;
	}
	return 0;
}

int creatorLock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_vehicle_doors_locked(objecthandle, 0); //Unlocked
	ShowMessageOnScreen("~y~Vehicle Doors Unlocked!");
	}
	return 0;
}

int creatorLaunchForward(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	apply_force_to_entity(objecthandle, true, 0, 100, 0, 0, 0, 0, true, true, true, true, false, true);
	ShowMessageOnScreen("~y~Vehicle has been launched forwards, may have to click more than once!");
	}
	return 0;
}

int creatorVehAlarm(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_vehicle_doors_locked(objecthandle, 4);
	SET_VEHICLE_ALARM(objecthandle, true);
	ShowMessageOnScreen("~y~Vehicle alarm has been set!");
	}
	return 0;
}

int creatorExplodeVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	EXPLODE_VEHICLE(objecthandle, false, true);
	ShowMessageOnScreen("~y~Vehicle has been bombed!");
	}
	return 0;
}

bool tFlyingVeh = false;
int ToggleFlyingVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(!tFlyingVeh){
		tFlyingVeh = true;
		ShowMessageOnScreen("~y~Flying Vehicle: ~g~ON! X to Go Up, RB to Go Forward!");
	}
	else if(tFlyingVeh){
		tFlyingVeh = false;
		ShowMessageOnScreen("~y~Flying Vehicle: ~r~OFF!");
	}
	return 0;
}

void tFlyingVehLoop(){
	if (menuInputHandler->RightBumperDown()){
		int myhandle = GetPlayerHandle(PlayerId());
	    int myvehicle = GetCarCharIsIn(myhandle, 0);
		apply_force_to_entity(myvehicle, true, 0, 1, 0, 0, 0, 0, true, true, true, true, false, true);
	}
	if (menuInputHandler->XButtonDown()){
		int myhandle = GetPlayerHandle(PlayerId());
	    int myvehicle = GetCarCharIsIn(myhandle, 0);
		apply_force_to_entity(myvehicle, true, 0, 0, 1, 0, 0, 0, true, true, true, true, false, true);
	}
}


int creatorLaunchBackward(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	apply_force_to_entity(objecthandle, true, 0, -100, 0, 0, 0, 0, true, true, true, true, false, true);
	ShowMessageOnScreen("~y~Vehicle has been launched backwards, may have to click more than once!");
	}
	return 0;
}
float creatorTeleObjCoords[3];
int creatorTeleToObj(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, creatorTeleObjCoords);
	set_entity_coords(PlayerPedId(), creatorTeleObjCoords[0], creatorTeleObjCoords[1], creatorTeleObjCoords[2], 0, 0, 0, 1);
	ShowMessageOnScreen("~y~Teleported To Object!");
	}
	return 0;
}

int creatorTeleportVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	int myhandle = GetPlayerHandle(PlayerId());
	  int var4 = -1;
      int pasnmax;
      pasnmax = get_vehicle_max_number_of_passengers(objecthandle);
      while (var4 < pasnmax) {
        if (is_vehicle_seat_free(objecthandle, var4)) {
			set_ped_into_vehicle(myhandle, objecthandle, var4);
			ShowMessageOnScreen("~g~ Teleported into creator vehicle!");
			break;
			}
			else
			{
            var4++;
			}
			}
			if (var4 > pasnmax){
			ShowMessageOnScreen("~g~ Failed, No available seat in creator vehicle!");
		}
	}
	return 0;
}

int creatorPopAllTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_vehicle_tyres_can_burst(objecthandle, true);
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 0, 0)){
			PopCarTyre(objecthandle, 0, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 1, 0)){
			PopCarTyre(objecthandle, 1, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 2, 0)){
			PopCarTyre(objecthandle, 2, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 3, 0)){
			PopCarTyre(objecthandle, 3, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 4, 0)){
			PopCarTyre(objecthandle, 4, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 5, 0)){
			PopCarTyre(objecthandle, 5, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 6, 0)){
			PopCarTyre(objecthandle, 6, 1, 1148846080);
		}
		if(!IS_VEHICLE_TYRE_BURST(objecthandle, 7, 0)){
			PopCarTyre(objecthandle, 7, 1, 1148846080);
		}
	ShowMessageOnScreen("~y~Vehicle tyres have been blown out!");
	}
	return 0;
}

int creatorMaxLSC(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) 
{	
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	set_vehicle_mod_kit(objecthandle, 0);
    PaintCar(objecthandle, 120, 120);
	PaintCarExtra(objecthandle, 120, 120);
	set_number_plate(objecthandle, "HASTER");
	SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(objecthandle, 1);
	toggle_vehicle_mod(objecthandle, 18, 1);
	toggle_vehicle_mod(objecthandle, 22, 1);
	set_vehicle_mod(objecthandle, 16, 5, 0);
	set_vehicle_mod(objecthandle, 12, 2, 0);
	set_vehicle_mod(objecthandle, 11, 3, 0);
	set_vehicle_mod(objecthandle, 14, 14, 0);
	set_vehicle_mod(objecthandle, 15, 3, 0);
	set_vehicle_mod(objecthandle, 13, 2, 0);
	set_vehicle_wheel_type(objecthandle, 6);
	set_vehicle_window_tint(objecthandle, 5);
	set_vehicle_mod(objecthandle, 23, 19, 1);
	set_vehicle_mod(objecthandle, 0, 1, 0);
	set_vehicle_mod(objecthandle, 1, 1, 0);
	set_vehicle_mod(objecthandle, 2, 1, 0);
	set_vehicle_mod(objecthandle, 3, 1, 0);
	set_vehicle_mod(objecthandle, 4, 1, 0);
	set_vehicle_mod(objecthandle, 5, 1, 0);
	set_vehicle_mod(objecthandle, 6, 1, 0);
	set_vehicle_mod(objecthandle, 7, 1, 0);
	set_vehicle_mod(objecthandle, 8, 1, 0);
	set_vehicle_mod(objecthandle, 9, 1, 0);
	set_vehicle_mod(objecthandle, 10, 1, 0);
	ShowMessageOnScreen("~y~ The vehicle has been maxed out bruh!");
	}
	return 0;
}

int NoStolenVehicleHere(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	if(IS_VEHICLE_STOLEN(Veh)){
	  SET_VEHICLE_IS_STOLEN(Veh, false);
	}

	return 0;
}

int StolenVehicleHere(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	if(!IS_VEHICLE_STOLEN(Veh)){
	  SET_VEHICLE_IS_STOLEN(Veh, true);
	}

	return 0;
}

/*int CreatorVehicleTroll(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
	ShowMessageOnScreen("~y~HaHa  xxHASTERxx, try again. Not yet implemented..come back later!");
	return 0;
}*/

int BurnEntity(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Entity = GetPlayerHandle(subMenuIndex);
	if(!IS_ENTITY_ON_FIRE(Entity)){
		START_ENTITY_FIRE(Entity);
	}
	return 0;
}

bool vOutOfControl = false;
int vOutOfControlIndex = 0;
int vOutOfControlTimeout = 310;
int vOutOfControlTimeoutCounter = 0;

void vOutOfControlProcess() {
	int subMenuIndex = vOutOfControlIndex;

	// check to see if we are at our timeout limit
	if (vOutOfControlTimeoutCounter >= vOutOfControlTimeout) {
		vOutOfControl = false;
		ShowMessageOnScreen("~g~ Failed to set vehicle out of control. Retrys timed out.");
		vOutOfControlTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		SET_VEHICLE_OUT_OF_CONTROL(Vehicle, 1, 0);
		ShowMessageOnScreen("~y~Vehicle set out of control!");
		vOutOfControlTimeoutCounter = 0;
		vOutOfControl = false;
	}

	vOutOfControlTimeoutCounter++;
}

int SetVehOutOfControl(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!vOutOfControl) {
		vOutOfControlIndex = selectedMenuIndexes->operator[](1);
		vOutOfControl = true;
	}
	return 0;
}

bool pitchT = false;
int ShowPitch(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!pitchT){
	pitchT = true;
	}
	else if (pitchT){
	pitchT = false;
	}
	return 0;
}

bool coordsT = false;
int ShowCoords(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!coordsT){
	coordsT = true;
	}
	else if (coordsT){
	coordsT = false;
	}
	return 0;
}

bool pcoordsT = false;
int ShowPlayerCoords(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!pcoordsT){
	pcoordsT = true;
	}
	else if (pcoordsT){
	pcoordsT = false;
	}
	return 0;
}

bool trollCash = false;
int MoneyTrollMiniGame(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!trollCash){
	trollCash = true;
	}
	else if (trollCash){
	trollCash = false;
	}
	return 0;
}

bool hashT = false;
int ShowObjHash(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!hashT){
	hashT = true;
	}
	else if (hashT){
	hashT = false;
	}
	return 0;
}

int DriveAir(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!da) {
	dw = false;
	da = true;
	float Pos[3];
	GetEntityCoords(GetCarCharIsIn(PlayerPedId(), 0), Pos); // 370 
	set_entity_coords(GetCarCharIsIn(PlayerPedId(), 0), Pos[0], Pos[1], 370, 1, 0, 0, 1);
	ShowMessageOnScreen("~g~ Drive in air on");
	model = -1003748966;
    objectspawn = true;
	waterwheel = true;
	air = true;
	}
	else if (da) {
	da = false;
	air = false;
	if (zdrop) { 
	float Pos[3];
	GetEntityCoords(GetCarCharIsIn(PlayerPedId(), 0), Pos);
	if(get_ground_z_for_3d_coord(Pos[0], Pos[1], 600.0f, &Pos[2])) {
	set_entity_coords(GetCarCharIsIn(PlayerPedId(), 0), Pos[0], Pos[1], Pos[2], 1, 0, 0, 1);
	}
	}
	ShowMessageOnScreen("~g~ Drive in air off");
	}
	return 0;
}

void drive_water() {
	//if (is_entity_in_water(GetCarCharIsIn(PlayerPedId(), 0))) {
	float Pos[3];
	GetEntityCoords(GetCarCharIsIn(PlayerPedId(), 0), Pos);
	if (!air){
	set_entity_coords(waterobj, Pos[0], Pos[1], - 0.9, 1, 0, 0, 1);
	}
	else {
	set_entity_coords(waterobj, Pos[0], Pos[1], 360, 1, 0, 0, 1);
	}
	set_entity_rotation(waterobj,180,90,180,2,1);
	set_entity_visible(waterobj, false);
	freeze_entity_position(waterobj, true);
}

bool fixPlayersCar = false;
int fixPlayersCarIndex = 0;
int fixPlayersCarTimeout = 310;
int fixPlayersCarTimeoutCounter = 0;

bool ClonePlayer = false;
int ClonePlayerIndex = 0;

float ClonedPlayerPos[3];
void ClonePlayerProcess() {
	int subMenuIndex = ClonePlayerIndex;

	int Player = GetPlayerHandle(subMenuIndex);
	GetEntityCoords(Player, ClonedPlayerPos);
	CLONE_PED(Player, ClonedPlayerPos[0], ClonedPlayerPos[1], ClonedPlayerPos[2]);
	ClonePlayer = false;
	ShowMessageOnScreen("~g~Cloned Online Player, ~y~ DON'T ABUSE THIS, ~r~ You will fatal crash!");
}

float blamePlayerPos[3];
bool blamePlayer = false;
int blamePlayerIndex = 0;
void blamePlayerProcess() {
	int subsMenuIndex = blamePlayerIndex;
	int deadPlayer = GetPlayerHandle(subsMenuIndex);
	GetEntityCoords(deadPlayer, blamePlayerPos);
	ADD_OWNED_EXPLOSION(deadPlayer, blamePlayerPos, BLIMP, FLT_MAX, false, true, 0.0f);
	blamePlayer = false;
	ShowMessageOnScreen("~g~Killed Player!");
}

void FixVehicleOnlineProcess() {
	int subMenuIndex = fixPlayersCarIndex;

	// check to see if we are at our timeout limit
	if (fixPlayersCarTimeoutCounter >= fixPlayersCarTimeout) {
		fixPlayersCar = false;
		ShowMessageOnScreen("~g~ Failed to fix players car. Retrys timed out.");
		fixPlayersCarTimeoutCounter = 0;
		return;
	}

	int Player = GetPlayerHandle(subMenuIndex);
	int Vehicle = GetCarCharIsIn(Player, 0);

	if (RequestNetworkControl(Player, Vehicle)) {
		FixCar(Vehicle);
		set_vehicle_dirt_level(Vehicle, 0.0f);
		ShowMessageOnScreen("~g~ Fixed players car.");
		fixPlayersCarTimeoutCounter = 0;
		fixPlayersCar = false;
	}

	fixPlayersCarTimeoutCounter++;
}

int FixVehicleOnline(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	// Check to see if we are in the process of teleporting a player
	if (!fixPlayersCar) {
		fixPlayersCar = true;
		fixPlayersCarIndex = selectedMenuIndexes->operator[](1);
	}

	return 0;
}

int ClonePedOnline(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	
	if (!ClonePlayer) {
		ClonePlayer = true;
		ClonePlayerIndex = selectedMenuIndexes->operator[](1);
	}

	return 0;
}
//Global Variables I just have them close but their out side of the function so they work as Globals. #2MUCH4U
int PlayerToBlame;
int blamedPlayer;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sBlamedPlayerIndex = 0;
int setBlamedPlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	PlayerToBlame = sBlamedPlayerIndex;
	return 0;
}

int kWithBlameIndex = 0;
int killWithBlame(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = kWithBlameIndex;
	float deadPos[3];
	GetEntityCoords(subMenuIndex, deadPos);
	ADD_OWNED_EXPLOSION(PlayerToBlame, deadPos, BLIMP, FLT_MAX, false, true, 0.0f);
	return 0;
}

int blameExplosion(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	
	if (!blamePlayer) {
		blamePlayer = true;
		blamePlayerIndex = selectedMenuIndexes->operator[](1);
	}

	return 0;
}

int setPlayerFireIndex = 0;
void setPlayerFireLoop(){
	float firePos[3];
	int subMenuIndex = setPlayerFireIndex;
    int onlinePlayer = GetPlayerHandle(subMenuIndex);
	GetEntityCoords(subMenuIndex, firePos);
	START_SCRIPT_FIRE(firePos[0], firePos[1], firePos[2], 1, true);
} 

bool setPlayerFire = false;
int SetPlayerOnFire(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!setPlayerFire){
	  setPlayerFire = true;
	  ShowMessageOnScreen("~y~Player Fire: ~g~ON");
	}
	else if(setPlayerFire){
	  setPlayerFire = false;
	  ShowMessageOnScreen("~y~Player Fire: ~r~OFF");
	}
	
	return 0;
}

Vector3 GetImpactCoords()
{
	float Loc[3];
	if (is_ped_shooting(PlayerPedId()))
	{
		if (get_ped_last_weapon_impact_coord(PlayerPedId(), Loc))
		{
			Vector3 Coords;
			Coords.x = Loc[0], Coords.y = Loc[1], Coords.z = Loc[2];
			return Coords;
		}
	}
}

bool propssGun = false;
void propGun()
{
	int PedHandle = PlayerPedId();
	float Coords[3];
	
		if (is_ped_shooting(PedHandle))
		{
			get_ped_last_weapon_impact_coord(PedHandle, Coords);	
			   RequestModel(0x113FD533);
		          if(HasModelLoaded(0x113FD533))
		          {
		        	create_ambient_pickup2(0xCE6FDD6B, Coords[0], Coords[1], Coords[2], 0, 40000, 0x113FD533, 0, 1);
		          }
	    }
}

int shootPropGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!propssGun){
	   propssGun = true;
	}
	else if(propssGun){
		propssGun = false;
	}

	return 0;
}

int SuperRun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	myplayerped = GetPlayerHandle(PlayerId());
    //Sleep(500);
    ShowMessageOnScreen("~g~ Toggled super run.");
    superruncheck = !superruncheck;//toggle
	return 0;
}

void super_run() {
	if (menuInputHandler->AButtonDown()) {
		//printf("running\n");
		apply_force_to_entity(/*myplayerped*/PlayerPedId(), true, 0, 3, 0, 0, 0, 0, true, true, true, true, false, true);
	}
}

int SuperJump(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	myplayerped = GetPlayerHandle(PlayerId()); 
    //Sleep(500);
    ShowMessageOnScreen("~g~ Toggled super jump.");
    superjump = !superjump;//toggle
	return 0;
}

bool superJumping = false;

void super_jump()
{
	if (!buttonpressed) {
		if (menuInputHandler->XButtonDown() && !superJumping) {
			//printf("X button pressed\n");
			apply_force_to_entity(myplayerped, true, 0, 0, 15, 0, 0, 0, true, true, true, true, false, true);
			//Sleep(600);
			//buttonpressed = false;
			//buttonpressed = true;
			superJumping = true;
		}
		else if (menuInputHandler->XButtonDown()) {
			superJumping = false;
		}
	}
}
int scriptsetModel = -1;
bool car = false;
int GainsOsiris(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	causelag ^= true;
    car = true;
	scriptsetModel = 0x767164D6; 
	return 0;
}
int GainsStirling(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA29D6D10; 
	return 0;
}
int GainsVirgo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE2504942; 
	return 0;
}
int GainsWindsor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	causelag ^= true;
    car = true;
	scriptsetModel = 0x5E4327C8;
	return 0;
}
int GainsLuxor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB79F589E;
	return 0;
}
int GainsSwift(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4019CB4C; 
	return 0;
}
int SpawnAdder(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{ 
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB779A091; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBullet(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9AE6DDA1; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCheetah(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB1D95DA0; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnEntityXF(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB2FE5CF9; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnInfernus(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x18F25AC7; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTurismoR(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x185484E1; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVacca(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x142E0DC3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVoltic(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9F4B77BE; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnZentorno(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xAC5DF515; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnWeedVan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 943752001; // weed van
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnUnmarked(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -1973172295; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnLazer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -1281684762; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPredator(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -488123221; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFrogger2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1949211328; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPMav(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 353883353; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCargobob3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1394036463; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -1323100960; // big tow truck
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTow2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -442313018; // small tow truck
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTornado4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -2033222435; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPVan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 456714581; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSpace(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 534258863; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDHandler(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 444583674; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnLGuard(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 469291905; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMower(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1783355638; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPBus(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -2007026063; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPolice2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 2046537925; // city crown vic
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPolice3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -1627000575; // buffalo
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnClown(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 728614474; // clown van
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSheriff(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -1683328900; // crown vic
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSheriff2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1922257928; // suv
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDozer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1886712733; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDump(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -2130482718; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPolice(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1912215274; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMonster(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -845961253; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPhantom(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x809AA4CB; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFIB(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1127131465; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFIB2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -1647941228; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCutter(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -1006919392; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBlimp(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = -150975354; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBuzzard(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2F03547B; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTank(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 782665360; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCargo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x15F27762; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnJumbo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1058115860; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSkylift(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1044954915; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAnnihilator(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 837858166; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnHakuchou(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 1265391242; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSwift(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xEBC24DF2; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMesa3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x84F42E51; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTR2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7BE032C6; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTR3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6A59902D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTR4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7CAB34D0; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnLog(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x782A236D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMetal(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCBB2BE0E; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRandom(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA1DA3C91; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBig(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8548036D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFlat(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xAF62F6B2; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFame(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x967620BE; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnArmyT1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA7FF33F5; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnArmyT2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9E6B14D6; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnArmyT3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB8081009; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBoatT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1F3D44B5; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDockT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x806EFBEE; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFreightT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD1ABB666; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTanker(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD46F4737; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnConstruct(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2A72BEAB; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSpeeder(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x0DC60D2B; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBType(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x06FF6914; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int Spawn6x6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB6410173; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBesra(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6CBD1D6D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMilJet(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x09D80F93; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBlade(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB820ED5E; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSub(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2DFF622F; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSultan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x39DA2754; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnHauler(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x5A82F9AE; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPacker(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x21EEE87D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDinghy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3D961290; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnJetmax(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x33581161; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMarquis(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC1CE1183; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSeashark(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC2974024; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSeasharkLG(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDB4388E4; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSqualo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x17DF5EC2; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSuntrap(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xEF2295C9; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTropic(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1149422F; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBenson(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7A61B330; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBiff(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x32B91AE8; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMule(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x35ED670B; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPounder(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7DE35E7D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnStockade(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6827CF72; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnStockadeSnow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF337AB36; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBlista(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xEB70965F; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDilettante(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xBC993509; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnIssi(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB9CB3B69; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPanto(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE644E480; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPrairie(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA988D3A2; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRhapsody(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x322CF98F; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCognoscenti(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x13B57D8A; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnExemplar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFFB15B5E; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnF620(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDCBCBE48; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFelon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE8A8BDA8; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFelon2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFAAD85EE; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnJackal(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDAC67112; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnOracle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x506434F6; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnOracle2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE18195B2; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSentinel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x50732C82; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSentinel2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3412AE2D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnZion(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xBD1B39C3; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnZion2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB8E2AE18; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBMX(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x43779C54; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCruiser(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1ABA13B5; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnEndurex(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB67597EC; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFixter(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCE23D3BF; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnScorcher(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF4E1AA15; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTriCycles(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE823FB48; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnWhippet(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4339CD69; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAmbulance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x45D56ADA; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFireTruck(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x73920F8E; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPRanger(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2C33B46E; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPBike(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFDEFAEC3; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRiot(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB822A1AA; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBuzzard2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2C75F0DD; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCargobob(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFCFCB68B; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCargobob2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x60A7EA10; // medical
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFrogger(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2C634FBD; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMaverick(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9D0450CA; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFlatbed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x50B0215A; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMixer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD138A6BB; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMixer2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1C534995; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRubble(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9A5B1DCC; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTipper(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x02E19879; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTipper2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC7824E5E; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBarracks(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCEEA3F4B; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBarracks2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4008EABB; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCrusader(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x132D5A1A; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAkuma(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x63ABADE7; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBagger(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x806B9CC3; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBati801(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF9300CC5; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBati801RR(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCADD5D2D; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCarbonRS(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x00ABB0C0; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDaemon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x77934CEE; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDoubleT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9C669788; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFaggio(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x0350D1AB; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnHexer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x11F76C14; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnInnovation(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x44C4E977; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnNemesis(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDA288376; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPCJ600(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC9CEAF06; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRuffian(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCABD11E8; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSanchez(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2EF89E46; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSanchez2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA960B13E; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSovereign(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2C509634; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnThrust(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6D6F8F43; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVader(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF79A00F7; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBuccaneer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD756460C; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDominator(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x04CE68AC; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnGauntlet(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x94B395C5; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnHotknife(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x0239E390; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPhoenix(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x831A21D5; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPicador(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x59E0FBF3; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRatLoader(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD83C13CE; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRatLoader2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDCE1D9F7; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSlamVan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2B7F9DE3; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRuiner(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF26CEFF9; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSabreGT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9B909C94; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVigero(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCEC6B9B7; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVoodoo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1F3766E3; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBifta(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xEB298297; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBlazer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8125BCF9; // sultan
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBlazer2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFD231729; // lifeguard
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBlazer3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB44F0582; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBodhi(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xAA699BB6; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDune(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9CF21E0F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDuneloader(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x698521E3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnInjection(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x432AA566; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnKalahari(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x05852838; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRancherXL(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6210CBB0; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRancherSnow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7341576B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRebel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB802DD46; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRebel2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8612B64B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSandkingSWB(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3AF8C345; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSandkingXL(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB9210FD0; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCuban800(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD9927FE3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDuster(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x39D6779E; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnLuxor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x250B0C5E; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMallard(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x81794C70; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMammatus(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x97E55D11; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnShamal(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB79C1BF5; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTitan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x761E2AD3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVelum(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9C429B6A; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVestra(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4FF77E37; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAsea(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x94204D89; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAsea2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9441D8D5; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAsterope(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8E9254FB; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnEmperor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD7278283; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnEmperor2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8FC3AADC; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnEmperor3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB5FCF74E; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFugitive(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x71CB2FFB; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnGlendale(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x047A6BC1; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnIngot(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB3206692; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnIntruder(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x34DD8AA1; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPremier(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8FB66F9B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPrimo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xBB6B404F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRegina(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFF22D208; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRomero(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2560B2FC; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSchafter(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB52B5113; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnStanier(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA7EDE74D; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnStratum(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x66B4FC45; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnStretch(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8B13F083; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSuperDiamond(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x42F2ED16; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSurge(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8F0E3594; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTailgater(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC3DDFDCE; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnWarrener(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x51D83328; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnWashington(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x69F06B57; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAirportBus(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4C80EB0E; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBus(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD577C962; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDashound(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x84718D34; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnShuttle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xBE819C63; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTaxi(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC703DB5F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTourbus(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x73B1C3CB; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTrashmaster(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x72435A19; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int Spawn9F(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3D8FA25C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int Spawn9F2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA8E38B01; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAlpha(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2DB8D1AA; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBanshee(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC1E908D2; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBuffalo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xEDD516C6; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBuffalo2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2BEC3CBE; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCarbonizzare(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7B8AB45F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnComet(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC1AE4D16; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCoquette(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x067BC037; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnElegy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDE3D9D22; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFeltzer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8911B9F5; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFuroreGT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xBF1691E0; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFusilade(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1DC0BA53; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFuto(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7836CE2F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnJester(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB2A716A3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnJester2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xBE0E6126; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnKhamelion(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x206D1B68; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMassacro(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF77ADE32; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMassacro2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDA5819A3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPenumbra(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE9805550; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRapidGT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x8CB29A14; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRapidGT2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x679450AF; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSchwartzer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD37B7976; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSurano(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x16E478C1; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCoquette2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3C4E2113; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnJB700(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3EAB5555; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnManana(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x81634188; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMonroe(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE62B361B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPeyote(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6D19CCBC; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPigalle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x404B6381; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnStinger(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x5C23AF9B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnStingerGT(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x82E499FA; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTornado(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1BB290BC; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTornado2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x5B42A5C4; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTornado3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x690A4153; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnZType(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2D3BD401; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBaller(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCFCA3668; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBaller2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x08852855; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBeeJayXL(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x32B29A4B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCavalcade(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x779F23AA; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCavalcade2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD0EB2BE5; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDubsta(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x462FE277; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDubsta2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xE882E5F6; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFQ2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xBC32A33B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnGranger(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9628879C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnGresley(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA3FC0F4D; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnHabanero(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x34B7390F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnHuntleyS(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1D06D681; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnLandstalker(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4BA4E8DC; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMesa(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x36848602; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMesa2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xD36A4B44; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPatriot(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCFCFEB3B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRadius(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9D96B45B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRocoto(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7F5C91F1; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSeminole(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x48CECED3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSerrano(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4FB1A214; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnAirtug(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x5D0AAC8F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCaddy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x44623884; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCaddy2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDFF0594C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDocktug(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCB44B1CA; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnFieldmaster(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x843B73DE; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnForklift(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x58E49664; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRipley(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCD935EF9; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSadler(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xDC434E51; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSadler2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2BC345D1; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnScrap(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9A9FD3DF; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTractor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x61D6BA8C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTractor2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x562A97BD; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnUtility(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1ED0A534; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnUtility2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x34E6BF6B; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnUtility3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7F2153DF; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBison(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFEFD644F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBison2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7B8297C5; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBison3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x67B3F020; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBobcatXL(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3FC5D440; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBoxville(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x898ECCEA; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBoxville2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF21B33BE; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBoxville3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x07405E08; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBurrito(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xAFBB2CA4; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBurrito2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xC9E8FF76; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBurrito3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x98171BD3; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBurrito4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x353B561D; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBurrito5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x437CF2A0; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCamper(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6FD95F68; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnGBurrito(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x97FA4F36; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnJourney(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF8D48E7A; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMinivan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xED7EADA4; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnParadise(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x58B3979C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnPony(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xF8DE29A8; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRumpo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x4543B74D; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRumpo2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x961AFEF7; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSpeedo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xCFB3870C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSurfer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x29B0DA97; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSurfer2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB1D80E06; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTacoVan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x744CA80D; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnYouga(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x03E5F6B8; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnRancherSP(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA46462F7; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnEsperantoSP(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x95F4C618; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnMule3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x85A5B471; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTanker2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x74998082; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnCasco(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x3822BDFE; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBoxville4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1A79847A; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnHydra(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x39D6E83F; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnInsurgent(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x9114EADA; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnInsurgent2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x7B7E56F0; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnGBurrito2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x11AA0E14; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTechnical(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x83051506; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnDinghy3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x1E5E54EA; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSavage(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xFB133A17; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnEnduro(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x6882FA73; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnGuardian(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x825A9F4C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnLectro(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x26321E67; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnKumura(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xAE2BFE94; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnKumura2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x187D938D; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnTrash2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xB527915C; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnBarracks3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x2592B5CF; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnValkyrie(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0xA09E15FD; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnSlamvan2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x31ADBBFC; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}
int SpawnVelum2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	causelag ^= true;
    car = true;
	scriptsetModel = 0x403820E8; // trevors
	//ShowMessageOnScreen("~g~ This doesn't work");
	return 0;
}

bool bguard = false;
int CIASpawn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	bguard = true;
	return 0;
}
bool bguard01 = false;
int BuffSpawn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	bguard01 = true;
	return 0;
}
bool bguard02 = false;
int StripperSpawn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	bguard02 = true;
	return 0;
}
bool bguard03 = false;
int ZombiesSpawn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	bguard03 = true;
	return 0;
}
bool bguard04 = false;
int MiniGunMarines(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	bguard04 = true;
	return 0;
}
bool bguard05= false;
int ChopGuard(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	bguard05 = true;
	return 0;
}
bool bguard06= false;
int MntLionSpawn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	bguard06 = true;
	return 0;
}


bool movement = false;
char* anim1;
int DrunkMode(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	movement = true;
	anim1 = "move_m@drunk@verydrunk";
	ShowMessageOnScreen("~g~ Drunk mode activated");
	return 0;
}

int NormalM(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	movement = true;
	anim1 = "move_m@generic";
	ShowMessageOnScreen("~g~ Normal male mode activated");
	return 0;
}

int NormalF(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	movement = true;
	anim1 = "move_f@generic";
	ShowMessageOnScreen("~g~ Normal female mode activated");
	return 0;
}
bool anattack = false;
int AnimalAttack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//ShowMessageOnScreen("~g~ Whenever you change to a cougar or dog you can now attack people!");
	anattack = true;
	return 0;
}
int TeleportToOnlinePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			float Position[3];
			GetEntityCoords(Handle, Position);
			set_entity_coords(myvehicle, Position[0], Position[1], Position[2], 0, 0, 0, 1);
		}
		else {
			float Position[3];
			GetEntityCoords(Handle, Position);
			set_entity_coords(myhandle, Position[0], Position[1], Position[2], 0, 0, 0, 1);
		}
		ShowMessageOnScreen("~g~ Teleported to online player.");
		return 0;
	}
}

int BlowUpOnlinePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float Position[3];
    GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2], BLIMP, FLT_MAX, true, false, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN, FLT_MAX, true, false, 0.0f);
	ShowMessageOnScreen("~g~ Blew player up");

	return 0;
}

int SpawnMapModFort(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	int crate;
	int barrier;
	int building;
	int crateObj;
	int crateObj2;
	int crateObj3;
	int crateObj4;
	int crateObj5;
	int crateObj6;
	int crateObj7;
	int crateObj8;
	int crateObj9;
	int crateObj10;
	int crateObj11;
	int crateObj12;
	int barrierObj;
	int barrierObj2;
	int barrierObj3;
	int barrierObj4;
	int barrierObj5;
	int barrierObj6;
	int buildingObj;
	int buildingObj2;
	int buildingObj3;
	int buildingObj4;
	int Veh = GetCarCharIsIn(PlayerPedId(), 0);

	crate = -629735826;
	barrier = 1603241576;
	building = -105439435;

	RequestModel(crate);
		if (HasModelLoaded(crate))
		{
	        
			crateObj =   create_object(crate, 2802.520264, 3420.233398, 54.460083); //Right Side Crate 1
			crateObj2 =  create_object(crate, 2802.520264, 3420.233398, 57.158569); //Right Side Crate 2
			crateObj3 =  create_object(crate, 2802.520264, 3420.233398, 59.957031); //Right Side Crate 3
			crateObj4 =  create_object(crate, 2802.520264, 3420.233398, 62.355469); //Right Side Crate 4
			crateObj5 =  create_object(crate, 2797.615479, 3422.335449, 54.458496); //Left Side Crate 1
			crateObj6 =  create_object(crate, 2797.615479, 3422.335449, 57.157104); //Left Side Crate 2 
			crateObj7 =  create_object(crate, 2797.615479, 3422.335449, 59.855591); //Left Side Crate 3
			crateObj8 =  create_object(crate, 2797.615479, 3422.335449, 62.454102); //Left Side Crate 4
			crateObj9 =  create_object(crate, 2797.114990, 3414.227539, 57.754150); //End Crate 1 
			crateObj10 = create_object(crate, 2797.114990, 3414.227539, 60.555542); //End Crate 2
			crateObj11 = create_object(crate, 2800.017822, 3421.134277, 61.552612); //Roof Crate
			crateObj12 = create_object(crate, 2800.017822, 3421.134277, 54.461548); //Ramp Crate

			set_entity_rotation(crateObj, 0, 0, 340, 2, 1); //Right Side Crate 1
		    set_entity_rotation(crateObj2, 0, 0, 340, 2, 1); //Right Side Crate 2
			set_entity_rotation(crateObj3, 0, 0, 340, 2, 1); //Right Side Crate 3
			set_entity_rotation(crateObj4, 0, 0, 340, 2, 1); //Right Side Crate 4
			set_entity_rotation(crateObj5, 0, 0, 340, 2, 1); //Left Side Crate 1
			set_entity_rotation(crateObj6, 0, 0, 340, 2, 1); //Left Side Crate 1
			set_entity_rotation(crateObj7, 0, 0, 340, 2, 1); //Left Side Crate 1
			set_entity_rotation(crateObj8, 0, 0, 340, 2, 1); //Left Side Crate 1
			set_entity_rotation(crateObj9, 0, 0, 251, 2, 1); //End Crate 1
			set_entity_rotation(crateObj10, 0, 0, 251, 2, 1); //End Crate 2
			set_entity_rotation(crateObj11, 0, 0, 340, 2, 1); //Roof Crate
			set_entity_rotation(crateObj12, 22, 0, 340, 2, 1); //Ramp Crate
		}

    RequestModel(barrier);
	    if (HasModelLoaded(barrier))
		{
			barrierObj =   create_object(barrier, 2790.538574, 3401.712402, 54.792847);
			barrierObj2 =  create_object(barrier, 2792.740723, 3406.917480, 54.787842);
			barrierObj3 =  create_object(barrier, 2794.442383, 3406.216797, 54.790283);
			barrierObj4 =  create_object(barrier, 2792.140137, 3400.911621, 54.790283);
			barrierObj5 =  create_object(barrier, 2795.743652, 3399.610352, 54.787842);
			barrierObj6 =  create_object(barrier, 2797.945801, 3404.815430, 54.785278);

			set_entity_rotation(barrierObj, 0, 0, 67, 2, 1);
			set_entity_rotation(barrierObj2, 0, 0, 67, 2, 1);
			set_entity_rotation(barrierObj3, 0, 0, 67, 2, 1);
			set_entity_rotation(barrierObj4, 0, 0, 67, 2, 1);
			set_entity_rotation(barrierObj5, 0, 0, 67, 2, 1);
			set_entity_rotation(barrierObj6, 0, 0, 67, 2, 1);
		}

		RequestModel(building);
		if (HasModelLoaded(building))
		{
			buildingObj =   create_object(building, 2797.204346, 3409.840332, 54.734619);
			buildingObj2 =  create_object(building, 2798.805908, 3413.543945, 54.734619);
			buildingObj3 =  create_object(building, 2803.861084, 3426.379883, 59.196289);
			buildingObj4 =  create_object(building, 2805.262451, 3429.783203, 59.164795);

			set_entity_rotation(buildingObj, 0, 0, 249, 2, 1);
			set_entity_rotation(buildingObj2, 0, 0, 249, 2, 1);
			set_entity_rotation(buildingObj3, 0, 0, 249, 2, 1);
			set_entity_rotation(buildingObj4, 0, 0, 249, 2, 1);
		}

		set_entity_coords(Veh, 2787.398438, 3390.868408, 55.900379, 1, 0, 0, 1);
		set_entity_rotation(Veh, 0, 0, 248, 2, 1);

		ShowMessageOnScreen("Private Map Mod Loaded!");

	return 0;
}

int LaunchRPG(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float launchPos[3];
    float targetPos[3];
	float dim_min[3], dim_max[3];

    //GetEntityCoords(PlayerPedId(), launchPos);
	//GetEntityCoords(Handle, targetPos);
	  get_offset_from_entity_in_world_coords( Handle, dim_min[0], dim_min[1], dim_min[2] + 4.0f, launchPos );
	  get_offset_from_entity_in_world_coords( Handle, dim_min[0], dim_min[1], dim_min[2], targetPos );

	  shoot_single_bullet_between_coords( launchPos, targetPos, 200, 0, get_hash_key("WEAPON_RPG"), rocketid, 1, 1, -1082130432 );

	  ShowMessageOnScreen("~g~ Shot RPG At Player! (This is a proximity thing. You have to be by them!)");

	return 0;
}

int PortableLazer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float launchPos[3];
    float targetPos[3];
	float dim_min[3], dim_max[3];

    //GetEntityCoords(PlayerPedId(), launchPos);
    GetEntityCoords(Handle, targetPos);

	  get_offset_from_entity_in_world_coords( PlayerPedId(), dim_min[0], dim_min[1] + 4.0f, 0.0f, launchPos ) ;

	  targetPos[2]--;

	  shoot_single_bullet_between_coords( launchPos, targetPos, 200, 0, get_hash_key("VEHICLE_WEAPON_PLAYER_LAZER"), rocketid, 1, 1, -1082130432 );
	
	  ShowMessageOnScreen("~g~ Shot Lazer Bullets At Player! (This is a proximity thing. You have to be by them!)");

	return 0;
}

int PortableBullets(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float launchPos[3];
    float targetPos[3];
	float dim_min[3], dim_max[3];

    //GetEntityCoords(PlayerPedId(), launchPos);
    //GetEntityCoords(Handle, targetPos);

	  get_offset_from_entity_in_world_coords( PlayerPedId(), dim_min[0], dim_min[1] + 4.0f, 0.0f, launchPos ) ;
	  get_offset_from_entity_in_world_coords( PlayerPedId(), dim_min[0], dim_min[1] + 4.0f, 0.0f, targetPos ) ;

	  shoot_single_bullet_between_coords( launchPos, targetPos, 200, 0, get_hash_key("WEAPON_ASSAULTRIFLE"), rocketid, 1, 1, -1082130432 );
	
	  ShowMessageOnScreen("~g~ Shot Bullets At Player! (This is a proximity thing. You have to be by them!)");

	return 0;
}

int BlowUpOnlinePlayerWater(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float Position[3];
    GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2] - 0.8f, DIR_WATER_HYDRANT, 8.0f, true, false, 0.0f);
	ShowMessageOnScreen("~g~ Blasted player with water.");

	return 0;
}

int BlowUpOnlinePlayerFlame(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float Position[3];
    GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2] - 0.8f, DIR_FLAME, 8.0f, true, false, 0.0f);
	ShowMessageOnScreen("~g~ Blasted player with flame.");

	return 0;
}

int BlowUpOnlinePlayerInvisible(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);

	float Position[3];
    GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2], BLIMP, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN, FLT_MAX, false, true, 0.0f);
	ShowMessageOnScreen("~g~ Invisible Nuke!");

	return 0;
}

int ChopAttack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	task_combat_ped(chop, Handle, 0, 0x10);
	ShowMessageOnScreen("~g~ Set Guard on Player!");
	}
	return 0;
}

int AnimalAttackLion(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	task_combat_ped(animalGuard, Handle, 0, 1);
	ShowMessageOnScreen("~g~ Set Animal on Player!");
	}
	return 0;
}

int ClearGuardTask(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	clear_ped_tasks_immediately(chop);
	ShowMessageOnScreen("~g~ Guard's task should be cleared!");
	}
	return 0;
}

int DeleteAllGuards(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	DELETE_PED(chop);
	ShowMessageOnScreen("~g~ All Guards Should Be Deleted!");
	return 0;
}

int TakeAwayGuardInvincibility(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	set_entity_invincible(chop, false);
	ShowMessageOnScreen("~g~ All Guards Invincibility Disabled!");
	}
	return 0;
}

int GiveGuardInvincibility(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	set_entity_invincible(chop, true);
	ShowMessageOnScreen("~g~ All Guards Invincibility Enabled!");
	}
	return 0;
}

int GiveGSniper(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	GiveWeaponDelayed(chop, 0x05FC3C11, 9999, 1); //Sniper
	ShowMessageOnScreen("~g~ All Guards Given Sniper!");
	}
	return 0;
}

int GiveGRPG(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	GiveWeaponDelayed(chop, 0xB1CA77B1, 9999, 1); //RPG
	ShowMessageOnScreen("~g~ All Guards Given RPG!");
	}
	return 0;
}

int GiveGM4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	GiveWeaponDelayed(chop, 0x83BF0278, 9999, 1); //M4
	ShowMessageOnScreen("~g~ All Guards Given M4!");
	}
	return 0;
}

int GiveGUzi(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	GiveWeaponDelayed(chop, 0x13532244, 9999, 1); //Uzi
	ShowMessageOnScreen("~g~ All Guards Given Uzi!");
	}
	return 0;
}

int GiveGMini(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	GiveWeaponDelayed(chop, 0x42BF8A85, 9999, 1); //Minigun
	ShowMessageOnScreen("~g~ All Guards Given Minigun!");
	}
	return 0;
}

int GiveGStun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	network_request_control_of_entity(chop);
	if(network_has_control_of_entity(chop)){
	GiveWeaponDelayed(chop, 0x3656C8C1, 9999, 1); //Stungun
	ShowMessageOnScreen("~g~ All Guards Given Stugun!");
	}
	return 0;
}

int trollcli;
bool cash2, cash1 = false;
int FakeMessageIndex = 0;
int FakeMes0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	trollcli = FakeMessageIndex;
	int Handle = GetPlayerHandle(trollcli);
	cash2 = true;
	return 0;
}

int FakeMes1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	trollcli = FakeMessageIndex;
	int Handle = GetPlayerHandle(trollcli);
	cash1 = true;
	return 0;
}


int FixMyCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			FixCar(myvehicle);
			set_vehicle_dirt_level(myvehicle, 0.0f);
			ShowMessageOnScreen("~y~ Fixed Vehicle!");
		}
	}
	else{
		ShowMessageOnScreen("~y~ You aren't in a vehicle!");
	}
	return 0;
}

int pAlpha20(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	network_request_control_of_entity(PlayerPedId());
	if(network_has_control_of_entity(PlayerPedId())){
	SET_ENTITY_ALPHA(PlayerPedId(), 51, false);
	}
	return 0;
}

int pAlpha40(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	network_request_control_of_entity(PlayerPedId());
	if(network_has_control_of_entity(PlayerPedId())){
	SET_ENTITY_ALPHA(PlayerPedId(), 102, false);
	}
	return 0;
}

int pAlpha60(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	network_request_control_of_entity(PlayerPedId());
	if(network_has_control_of_entity(PlayerPedId())){
	SET_ENTITY_ALPHA(PlayerPedId(), 153, false);
	}
	return 0;
}

int pAlpha80(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	network_request_control_of_entity(PlayerPedId());
	if(network_has_control_of_entity(PlayerPedId())){
	SET_ENTITY_ALPHA(PlayerPedId(), 204, false);
	}
	return 0;
}

int pAlpha100(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
	network_request_control_of_entity(PlayerPedId());
	if(network_has_control_of_entity(PlayerPedId())){
	SET_ENTITY_ALPHA(PlayerPedId(), 255, false);
	}
	return 0;
}

void showMyAlphaLoop(){
	int showMyAlphaNow = GET_ENTITY_ALPHA(PlayerPedId());
    PrintToScreen("Player Alpha:", 0.20000000, 0.80000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(showMyAlphaNow, 0.31000000, 0.80000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
}

int VehLivery1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 1);
	return 0;
}

int VehLivery2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 2);
	return 0;
}

int VehLivery3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 3);
	return 0;
}

int VehLivery4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 4);
	return 0;
}

int VehLivery5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 5);
	return 0;
}

int VehLivery6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 6);
	return 0;
}

int VehLivery7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 7);
	return 0;
}

int VehLivery8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
    int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	SET_VEHICLE_LIVERY(Veh, 8);
	return 0;
}

int ShowVehLivery(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{	
	int myhandle = GetPlayerHandle(PlayerId());
    int Veh = GetCarCharIsIn(myhandle, 0);
	int LivCount = GET_VEHICLE_LIVERY_COUNT(Veh);
	ShowMessageOnScreen("~y~Number of Available Skins: ", LivCount);
	return 0;
}

/*void showVehicleLiveryCountLoop(){
	int Veh = GetCarCharIsIn(PlayerPedId(), PlayerId());
	int showVehicleLiveryCount = GET_VEHICLE_LIVERY_COUNT(Veh);
    PrintToScreen("Vehicle Livery Count:", 0.20000000, 0.80000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(showVehicleLiveryCount, 0.35000000, 0.80000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
}*/

bool showMyAlpha = false;
int showEntityAlpha(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if(!showMyAlpha){
		showMyAlpha = true;
	}
	else if(showMyAlpha){
		showMyAlpha = false;
	}
	return 0;
}

bool collision = false;
int SetCarCol(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle) && !collision) {
			set_entity_collision(myvehicle, false);
			collision = true;
			ShowMessageOnScreen("~g~ Toggled vehicle collision off");
		}
		else if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle) && collision) {
			set_entity_collision(myvehicle, true);
			collision = false;
			ShowMessageOnScreen("~g~ Toggled vehicle collision on");
		}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle.");
	}
	return 0;
}
bool lowered = false;
int lower = 0;
int LowerVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if (is_ped_in_any_vehicle(PlayerPedId()))
	{
			if (lower == 0)
			{
			lowered = true;
			lower = 1;
			ShowMessageOnScreen("~g~ Lowered car turned on.");
			}
			else if (lower == 1)
			{
            lowered = false;
			lower = 0;
			ShowMessageOnScreen("~g~ Lowered car turned off.");
			}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle.");
	}
	return 0;
}

bool wanted = false;
int wantedvar = 0;
int WantedPlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
			if (wantedvar == 0)
			{
			wanted = true;
			wantedvar = 1;
			ShowMessageOnScreen("~y~ Never Wanted: ~g~ON!");
			}
			else if (wantedvar == 1)
			{
            wanted = false;
			wantedvar = 0;
			ShowMessageOnScreen("~y~ Never Wanted: ~r~OFF!");
			}
	return 0;
}

void wantedloop() {
set_player_wanted_level(PlayerId(), 0);
}

bool creatorField = false;
int creatorFieldvar = 0;
int creatorFieldToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
			if (creatorFieldvar == 0)
			{
			creatorField = true;
			creatorFieldvar = 1;
			ShowMessageOnScreen("~y~ Force Field: ~g~ON");
			SetPlayerInvincible(PlayerId(), true);
			}
			else if (creatorFieldvar == 1)
			{
            creatorField = false;
			creatorFieldvar = 0;
			ShowMessageOnScreen("~y~ Object Force Field: ~r~OFF");
			SetPlayerInvincible(PlayerId(), false);
			}
	return 0;
}

void creatorFieldloop() {
	float Position[3];
    GetEntityCoords(objecthandle, Position);
	AddExplosion(Position[0], Position[1], Position[2], BLIMP, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN, FLT_MAX, false, true, 0.0f);
}

bool field = false;
int fieldvar = 0;
int FieldToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
			if (fieldvar == 0)
			{
			field = true;
			fieldvar = 1;
			ShowMessageOnScreen("~g~ Force Field on");
			SetPlayerInvincible(PlayerId(), true);
			}
			else if (fieldvar == 1)
			{
            field = false;
			fieldvar = 0;
			ShowMessageOnScreen("~g~ Force Field off");
			SetPlayerInvincible(PlayerId(), false);
			}
	return 0;
}

void fieldloop() {
	float Position[3];
    GetEntityCoords(GetPlayerHandle(PlayerId()), Position);
	AddExplosion(Position[0], Position[1], Position[2], BLIMP, FLT_MAX, false, true, 0.0f);
	AddExplosion(Position[0], Position[1], Position[2], TRAIN, FLT_MAX, false, true, 0.0f);
}



void lowerloop()
{
int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			if (lower == 1)
			{
            apply_force_to_entity(myvehicle, true, 0, 0, -0.07, 0, 0, 0, true, true, true, true, false, true);
			}
		}
	}
}

int SetCarInvisible(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			//FixCar(myvehicle);
			if (!carvisible)
			{
			set_entity_visible(myvehicle, false);
			ShowMessageOnScreen("~g~ Car is invisible");
			carvisible = true;
			}
			else if (carvisible)
			{
			set_entity_visible(myvehicle, true);
			ShowMessageOnScreen("~g~ Car is visible");
			carvisible = false;
			}
		}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle.");
	}
	return 0;
}

int BurnOnlinePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	//StartEntityFire(Handle);
	ShowMessageOnScreen("~g~ Burned online player");

	return 0;
}

int KickOnlinePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	network_session_kick_player(subMenuIndex);
	ShowMessageOnScreen("~g~ Kicked online player");

	return 0;
}
int OnlinePlayerWanted(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
		set_player_wanted_level(PlayerId(), 5);
		set_player_wanted_level_now(PlayerId(), 5);
		ShowMessageOnScreen("Note: You have to turn Never Wanted Off and be their passenger!");
	/*
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	float Pos[3];
	GetEntityCoords(PlayerPedId(), Pos);
	if (is_ped_on_foot(GetPlayerHandle(subMenuIndex))) 
	ShowMessageOnScreen("~g~ Player isn't in a vehicle sorry");
	
	else {
		set_player_wanted_level(PlayerId(), 5);
		set_player_wanted_level_now(PlayerId(), 5);
		warp = true;
		set_entity_coords(GetPlayerHandle(PlayerId()), Pos[0], Pos[1], Pos[2], 0, 0, 0, 1);
		set_player_wanted_level(PlayerId(), 0);
		set_player_wanted_level_now(PlayerId(), 0);
		ShowMessageOnScreen("~g~ Gave player 5 star wanted level");
	}*/
	ShowMessageOnScreen("~g~ This isn't quite working yet, Teleport in to their car to give them your wanted level");
	return 0;
}
bool fwloaded = false;
bool fwvcheck = false;
char *fexp = "";
float fcoords[3];
int FireWorkExp(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
int subMenuIndex = selectedMenuIndexes->operator[](1);
GetEntityCoords(GetPlayerHandle(subMenuIndex), fcoords);
fexp = "scr_indep_firework_fountain";
fwvcheck = true;
return 0;
}
int FireWorkExp1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
int subMenuIndex = selectedMenuIndexes->operator[](1);
GetEntityCoords(GetPlayerHandle(subMenuIndex), fcoords);
fexp = "scr_indep_firework_shotburst";
fwvcheck = true;
return 0;
}
int FireWorkExp2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
int subMenuIndex = selectedMenuIndexes->operator[](1);
GetEntityCoords(GetPlayerHandle(subMenuIndex), fcoords);
fexp = "scr_indep_firework_starburst";
fwvcheck = true;
return 0;
}
int FireWorkExp3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
int subMenuIndex = selectedMenuIndexes->operator[](1);
GetEntityCoords(GetPlayerHandle(subMenuIndex), fcoords);
fexp = "scr_indep_firework_trailburst";
fwvcheck = true;
return 0;
}
char *fexp1 = "";
int FireWorkExp_0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fexp1 = "scr_indep_firework_fountain";
return 0;
}
int FireWorkExp_1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fexp1 = "scr_indep_firework_shotburst";
return 0;
}
int FireWorkExp_2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fexp1 = "scr_indep_firework_starburst";
return 0;
}
int FireWorkExp_3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fexp1 = "scr_indep_firework_trailburst";
return 0;
}
float fr, fg, fb;
float fwsize;
int FWOpt(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fwsize = 1.0;
return 0;
}
int FWOpt1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fwsize = 3.0;
return 0;
}
int FWOpt2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fwsize = 5.0;
return 0;
}
int FWOpt3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fr = 1.0, fg = 0, fb = 0;
return 0;
}
int FWOpt4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fr = 0, fg = 1.0, fb = 0;
return 0;
}
int FWOpt5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fr = 0, fg = 0, fb = 1.0;
return 0;
}
int FWOpt6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fr = 1, fg = 0, fb = 0.603921568627451;
return 0;
}
int FWOpt7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fr = 0.7254901960784314, fg = 0, fb = 0.5058823529411765;
return 0;
}
int FWOpt8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fr = 1.0, fg = 0.5176470588235294, fb = 0.0352941176470588;
return 0;
}
int FWOpt9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
fr = 0, fg = 1.0, fb = 0.9686274509803922;
return 0;
}
bool col_loop = false;
int FWOpt10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
if (!col_loop)
{
	col_loop = true;
}
else if (col_loop)
{
	col_loop = false;
}
return 0;
}
int fwcol = 2;
void fw_col_loop()
{
	if (fwcol > 1)
	{
		fr = 1.0, fg = 0, fb = 0;
		fwcol++;
	}
	if (fwcol > 40)
	{
		fr = 0, fg = 1.0, fb = 0;
		fwcol++;
	}
	if (fwcol > 80)
	{
		fr = 0, fg = 0, fb = 1.0;
		fwcol++;
	}
	if (fwcol > 120)
	{
		fr = 1, fg = 0, fb = 0.603921568627451;
		fwcol++;
	}
	if (fwcol > 160)
	{
		fr = 0.7254901960784314, fg = 0, fb = 0.5058823529411765;
		fwcol++;
	}
	if (fwcol > 200)
	{
		fr = 1.0, fg = 0.5176470588235294, fb = 0.0352941176470588;
		fwcol++;
	}
	if (fwcol > 240)
	{
		fr = 0, fg = 1.0, fb = 0.9686274509803922;
		fwcol++;
	}
	if (fwcol > 280)
	{
		fwcol = 2;
	}
}


int RemoveOnlineWanted(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	set_player_wanted_level(subMenuIndex, 0);
	set_player_wanted_level_now(subMenuIndex, 0);
	ShowMessageOnScreen("~g~ Removed players wanted level");

	return 0;
}

int RemoveOnlinePlayerWeapons(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	RemoveWeapons(GetPlayerHandle(subMenuIndex));
	ShowMessageOnScreen("~g~ Removed players guns");

	return 0;
}
bool custom = false;
int PlayerAcuse(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Ped = GetPlayerHandle(subMenuIndex);
	if (!custom){
	rocketid = Ped;
	custom = true;
	ShowMessageOnScreen("~g~ You will now suffer no consequences for your destruction!");
	}
	else if (custom){
	custom = false;
	ShowMessageOnScreen("~g~ Tracker has been turned back on the game will now know you are the one behind the destruction!");
	}

	return 0;
}

/*int SentryID = 0;
int SpawnSentry()
{
	int Hash = get_hash_key("p_rcss_folded");
	if (IS_MODEL_VALID(Hash))
	{
		float Coords[3];
		GetEntityCoords(PlayerPedId(), Coords);
		int ObjectHandle = create_object(Hash, Coords[0], Coords[1], Coords[2], 1, 1, 0);
		OBJ_TO_NET(ObjectHandle);
	}
}

bool GetPlayerTarget = true; 	//With this you can set targetting on players on/off
bool GetVehicleTarget = false; 	//With this you can set targetting on vehicles on/off
int TargetEntity = 0;
float Rotation = 0;

void SentryAimAndDraw()
{
	float Pos[3];
	if (DoesEntityExist(SentryID))
	{
		if(GetPlayerTarget)
			TargetEntity = GET_NEAREST_PLAYER_TO_ENTITY(SentryID);
		else if(GetVehicleTarget)
		{
			int CarType = 64;
			CarType |= 2710;
			CarType |= 2048;
			CarType |= 1;
			CarType |= 2;
			CarType |= 4;
			CarType |= 32;
			CarType |= 16;
			CarType |= 8;
			TargetEntity = get_closest_vehicle(Pos[0], Pos[1], Pos[2], 50.0f, 0, CarType);
		}
		if(DoesEntityExist(TargetEntity))
		{
			float out[3];
			float targetPos[3];
			float sentryPos[3];
			get_offset_from_entity_in_world_coords(SentryID,0.0f,-0.2f,0.57f, out);
			GetEntityCoords(TargetEntity, targetPos);
			GetEntityCoords(SentryID, sentryPos);
			DRAW_LINE(out[0], out[1], out[2], targetPos[0], targetPos[1], targetPos[2], 255, 0, 0, 255);
			Rotation = get_entity_heading(TargetEntity);
		    set_entity_rotation(SentryID, 0, 0, Rotation, 2, 1);
		}
	}
}

int Timeout = 200;
int Timer = 0;
int WeaponHash= get_hash_key("WEAPON_MG");
float firePos[3];
float targetEntityPos[3];

void SentryFireTarget()
{
	if (Timer <= GET_GAME_TIMER())
	{
		Timer = GET_GAME_TIMER() + Timeout;
		if (DoesEntityExist(SentryID) && DoesEntityExist(TargetEntity))
		    get_offset_from_entity_in_world_coords(SentryID,0.0f,-0.8f,0.6f, firePos);
		    GetEntityCoords(TargetEntity, targetEntityPos);
			shoot_single_bullet_between_coords(firePos, targetEntityPos, 250, 0, WeaponHash, PlayerPedId(), 1, 1, 0xBF800000);
	}
}

//Create it like this:
//SentryID = SpawnSentry();
bool sentryFire = false;
bool spawnTheSentry = false;
bool sentryAiming = false;
int SpawnSentryGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if(!spawnTheSentry){
		SentryID = SpawnSentry();
		sentryFire = true;
		sentryAiming = true;
		spawnTheSentry = true;
	}
	else if(spawnTheSentry){
		sentryFire = false;
		sentryAiming = false;
		spawnTheSentry = false;
	}

	return 0;
}*/

int GiveStunGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	GiveWeaponDelayed(PlayerPedId(), 0x3656C8C1, 300, 1);
	ShowMessageOnScreen("~g~ Gave stun gun");

	return 0;
}

int GivePlayerStun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	GiveWeaponDelayed(Handle, 0x3656C8C1, 300, 1);
	ShowMessageOnScreen("~g~ Gave them a stun gun!");

	return 0;
}

int GivePlayerCombatPDW(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	GiveWeaponDelayed(Handle, 0x0A3D4D34, 300, 1);
	ShowMessageOnScreen("~g~ Gave them a Combat PDW!");

	return 0;
}

bool mGun = false;
int MoneyGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if(!mGun){
	 mGun = true;
	}
	else if (mGun){
	 mGun = false;
	}
	return 0;
}

int InvisiblePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if (!invisiblePlayer)
	{
	set_entity_visible(PlayerPedId(), false);
	invisiblePlayer = true;
	ShowMessageOnScreen("~y~ Invisible Player Loop: ~g~ON");
	}
	else if (invisiblePlayer)
	{
	set_entity_visible(PlayerPedId(), true);
	invisiblePlayer = false;
	ShowMessageOnScreen("~y~ Invisible Player Loop: ~r~OFF");
	}
	return 0;
}

bool invisibleVeh = false;
int InvisibleVehicleLP(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{

	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
	}

	if (!invisibleVeh)
	{
	set_entity_visible(myvehicle, false);
	invisibleVeh = true;
	ShowMessageOnScreen("~y~ Invisible Vehicle Loop: ~g~ON");
	}
	else if (invisibleVeh)
	{
	set_entity_visible(myvehicle, true);
	invisibleVeh = false;
	ShowMessageOnScreen("~y~ Invisible Vehicle Loop: ~r~OFF");
	}
	return 0;
}

bool teleportGun = false;
int TeleportationGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	if (!teleportGun)
	{
	teleportGun = true;
	ShowMessageOnScreen("~g~ Teleport Gun: ON");
	}
	else if (teleportGun)
	{
	teleportGun = false;
	ShowMessageOnScreen("~g~ Teleport Gun: OFF");
	}
	return 0;
}

int TeleportInToCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	CarPed = selectedMenuIndexes->operator[](1);
	int player = selectedMenuIndexes->operator[](1);
	animid = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	float Pos[3];
	GetEntityCoords(ped, Pos);
	set_entity_coords(PlayerPedId(), Pos[0], Pos[1], Pos[2]);
	warp = true;
	return 0;
}

int GiveHealth(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	float Pos[3];
	float HealthNeeded = GET_ENTITY_MAX_HEALTH(ped) - GET_ENTITY_HEALTH(ped); //Note: This should get the health they need.
	GetEntityCoords(ped, Pos);
       create_ambient_pickup(get_hash_key("PICKUP_HEALTH_STANDARD"), Pos, 0, HealthNeeded, 1, 0, 1);

	return 0;
}

int GiveArmour(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	float Pos[3];
	GetEntityCoords(ped, Pos);
       create_ambient_pickup(get_hash_key("PICKUP_ARMOUR_STANDARD"), Pos, 0, 100, 1, 0, 1);

	return 0;
}

int GiveOnlineAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	float Pos[3];
	GetEntityCoords(ped, Pos);
       create_ambient_pickup(get_hash_key("PICKUP_AMMO_BULLET_MP"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_MISSILE_MP"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_GRENADELAUNCHER_MP"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_PISTOL"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_SMG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_RIFLE"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_MG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_SHOTGUN"), Pos, 0, 19999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_SNIPER"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_GRENADELAUNCHER"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_RPG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_MINIGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_FIREWORK_MP"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_HOMINGLAUNCHER"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_AMMO_FLAREGUN"), Pos, 0, 9999, 1, 0, 1);

	return 0;
}

int GiveOnlinePickupGuns(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	float Pos[3];
	GetEntityCoords(ped, Pos);
       create_ambient_pickup(get_hash_key("PICKUP_WEAPON_BULLPUPSHOTGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_ASSAULTSMG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_PISTOL50"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_ASSAULTRIFLE"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_CARBINERIFLE"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_ADVANCEDRIFLE"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_MG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_COMBATMG"), Pos, 0, 19999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_HEAVYSNIPER"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_MICROSMG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_SMG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_RPG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_MINIGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_PUMPSHOTGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_SAWNOFFSHOTGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_ASSAULTSHOTGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_GRENADE"), Pos, 0, 25, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_MOLOTOV"), Pos, 0, 25, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_SMOKEGRENADE"), Pos, 0, 25, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_STICKYBOMB"), Pos, 0, 25, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_PISTOL"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_COMBATPISTOL"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_APPISTOL"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_GRENADELAUNCHER"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_STUNGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_FIREEXTINGUISHER"), Pos, 0, 100, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_PETROLCAN"), Pos, 0, 100, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_KNIFE"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_NIGHTSTICK"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_HAMMER"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_BAT"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_GolfClub"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_CROWBAR"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_BOTTLE"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_SNSPISTOL"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_GUSENBERG"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_HEAVYSNIPER"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_SPECIALCARBINE"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_DAGGER"), Pos, 0, 1, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_VINTAGEPISTOL"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_FIREWORK"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_MUSKET"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_HEAVYSHOTGUN"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_MARKSMANRIFLE"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_PROXMINE"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_HOMINGLAUNCHER"), Pos, 0, 9999, 1, 0, 1);
	   create_ambient_pickup(get_hash_key("PICKUP_WEAPON_FLAREGUN"), Pos, 0, 9999, 1, 0, 1);

	return 0;
}

int GiveWeaponPDW(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int player = selectedMenuIndexes->operator[](1);
	int ped = GetPlayerHandle(player);
	float Pos[3];
	GetEntityCoords(ped, Pos);
       create_ambient_pickup(get_hash_key("PICKUP_WEAPON_COMBATPDW"), Pos, 0, 9999, 1, 0, 1);
	return 0;
}

int GiveAllWeapons(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{

	GiveWeaponDelayed(PlayerPedId(), 0x3656C8C1, 9999, 1); // stun gun
	GiveWeaponDelayed(PlayerPedId(), 0x99B507EA, 9999, 1); // knife
	GiveWeaponDelayed(PlayerPedId(), 0x678B81B1, 9999, 1); // night stick
	GiveWeaponDelayed(PlayerPedId(), 0x4E875F73, 9999, 1); // hammer
	GiveWeaponDelayed(PlayerPedId(), 0x958A4A8F, 9999, 1); // bat
	GiveWeaponDelayed(PlayerPedId(), 0x440E4788, 9999, 1); // golf club
	GiveWeaponDelayed(PlayerPedId(), 0x84BD7BFD, 9999, 1); // crowbar
	GiveWeaponDelayed(PlayerPedId(), 0x1B06D571, 9999, 5); // pistol
	GiveWeaponDelayed(PlayerPedId(), 0x5EF9FEC4, 9999, 1); // combat pistol
	GiveWeaponDelayed(PlayerPedId(), 0x22D8FE39, 9999, 1); // ap pistol
	GiveWeaponDelayed(PlayerPedId(), 0x99AEEB3B, 9999, 1); // pistol 50.
	GiveWeaponDelayed(PlayerPedId(), 0x13532244, 9999, 1); // micro smg
	GiveWeaponDelayed(PlayerPedId(), 0x2BE6766B, 9999, 1); // smg
	GiveWeaponDelayed(PlayerPedId(), 0xEFE7E2DF, 9999, 1); // assault smg
	GiveWeaponDelayed(PlayerPedId(), 0xBFEFFF6D, 9999, 1); // assault rifle
	GiveWeaponDelayed(PlayerPedId(), 0x83BF0278, 9999, 1); // carbine rifle
	GiveWeaponDelayed(PlayerPedId(), 0xAF113F99, 9999, 1); // advanced rifle
	GiveWeaponDelayed(PlayerPedId(), 0x9D07F764, 9999, 1); // MG
	GiveWeaponDelayed(PlayerPedId(), 0x7FD62962, 9999, 1); // combat mg
	GiveWeaponDelayed(PlayerPedId(), 0x1D073A89, 9999, 1); // pump shotgun
	GiveWeaponDelayed(PlayerPedId(), 0x7846A318, 9999, 1); // sawnoff shotgun
	GiveWeaponDelayed(PlayerPedId(), 0xE284C527, 9999, 1); // assault shotgun
	GiveWeaponDelayed(PlayerPedId(), 0x9D61E50F, 9999, 1); // bullpupshotgun
	GiveWeaponDelayed(PlayerPedId(), 0x05FC3C11, 9999, 1); // sniper
	GiveWeaponDelayed(PlayerPedId(), 0x0C472FE2, 9999, 1); // heavy sniper
	GiveWeaponDelayed(PlayerPedId(), 0xA284510B, 9999, 1); // grenade launcher
	GiveWeaponDelayed(PlayerPedId(), 0xB1CA77B1, 9999, 1); // rpg
	GiveWeaponDelayed(PlayerPedId(), 0x42BF8A85, 9999, 1); // minigun
	GiveWeaponDelayed(PlayerPedId(), 0x93E220BD, 9999, 1); // grenades
	GiveWeaponDelayed(PlayerPedId(), 0x2C3731D9, 9999, 1); // sticky bomb
	GiveWeaponDelayed(PlayerPedId(), 0xFDBC8A50, 9999, 1); // smoke grenade
	GiveWeaponDelayed(PlayerPedId(), 0x34A67B97, 9999, 1); // petrol can
	GiveWeaponDelayed(PlayerPedId(), 0x060EC506, 9999, 1); // fire extinguisher
	GiveWeaponDelayed(PlayerPedId(), 0x24B17070, 9999, 1); // moltovs
	GiveWeaponDelayed(PlayerPedId(), 0x497FACC3, 9999, 1); // flare
    GiveWeaponDelayed(PlayerPedId(), 0xFDBADCED, 9999, 1); // digiscanner
	GiveWeaponDelayed(PlayerPedId(), 0x687652CE, 9999, 1); // stinger
	GiveWeaponDelayed(PlayerPedId(), 600439132, 9999,  1); // ball
    //DLC Weapons
	GiveWeaponDelayed(PlayerPedId(), 0xF9E6AA4B, 9999, 1); // bottle
	GiveWeaponDelayed(PlayerPedId(), 0x61012683, 9999, 1); // gusenerg
	GiveWeaponDelayed(PlayerPedId(), 0xC0A3098D, 9999, 1); // special carbine
	GiveWeaponDelayed(PlayerPedId(), 0xD205520E, 9999, 1); // heavy pistol
	GiveWeaponDelayed(PlayerPedId(), 0xBFD21232, 9999, 1); // sns pistol
	GiveWeaponDelayed(PlayerPedId(), 0x7F229F94, 9999, 1); // bullpup rifle
	GiveWeaponDelayed(PlayerPedId(), 0x92A27487, 9999, 1); // dagger
	GiveWeaponDelayed(PlayerPedId(), 0x083839C4, 9999, 1); // vintage pistol
	GiveWeaponDelayed(PlayerPedId(), 0x7F7497E5, 9999, 1); // firework launcher
	GiveWeaponDelayed(PlayerPedId(), 0xA89CB99E, 9999, 1); // musket
	GiveWeaponDelayed(PlayerPedId(), 0x63AB0442, 9999, 1); // homing launcher
	GiveWeaponDelayed(PlayerPedId(), 0xAB564B93, 9999, 1); // proxmine
	GiveWeaponDelayed(PlayerPedId(), 0x787F0BB,  9999, 1); // snowball
	GiveWeaponDelayed(PlayerPedId(), 0xC734385A, 9999, 1); // marksman rifle
	GiveWeaponDelayed(PlayerPedId(), 0x47757124, 9999, 1); // flare gun
	GiveWeaponDelayed(PlayerPedId(), 0x0A3D4D34, 9999, 1); // Combat PDW
	//GiveWeaponDelayed(PlayerPedId(), 0xE232C28C, 9999, 1); // trash bag
	//GiveWeaponDelayed(PlayerPedId(), 0xD04C944D, 9999, 1); // handcuffs

	ShowMessageOnScreen("~y~ Gave all weapons");

	return 0;
}

int GiveWeaponsOnline(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int Handle = GetPlayerHandle(subMenuIndex);
	GiveWeaponDelayed(Handle, 0x3656C8C1, 9999, 1); // stun gun
	GiveWeaponDelayed(Handle, 0x99B507EA, 9999, 1); // knife
	GiveWeaponDelayed(Handle, 0x678B81B1, 9999, 1); // night stick
	GiveWeaponDelayed(Handle, 0x4E875F73, 9999, 1); // hammer
	GiveWeaponDelayed(Handle, 0x958A4A8F, 9999, 1); // bat
	GiveWeaponDelayed(Handle, 0x440E4788, 9999, 1); // golf club
	GiveWeaponDelayed(Handle, 0x84BD7BFD, 9999, 1); // crowbar
	GiveWeaponDelayed(Handle, 0x1B06D571, 9999, 1); // pistol
	GiveWeaponDelayed(Handle, 0x5EF9FEC4, 9999, 1); // combat pistol
	GiveWeaponDelayed(Handle, 0x22D8FE39, 9999, 1); // ap pistol
	GiveWeaponDelayed(Handle, 0x99AEEB3B, 9999, 1); // pistol 50.
	GiveWeaponDelayed(Handle, 0x13532244, 9999, 1); // micro smg
	GiveWeaponDelayed(Handle, 0x2BE6766B, 9999, 1); // smg
	GiveWeaponDelayed(Handle, 0xEFE7E2DF, 9999, 1); // assault smg
	GiveWeaponDelayed(Handle, 0xBFEFFF6D, 9999, 1); // assault rifle
	GiveWeaponDelayed(Handle, 0x83BF0278, 9999, 1); // carbine rifle
	GiveWeaponDelayed(Handle, 0xAF113F99, 9999, 1); // advanced rifle
	GiveWeaponDelayed(Handle, 0x9D07F764, 9999, 1); // MG
	GiveWeaponDelayed(Handle, 0x7FD62962, 9999, 1); // combat mg
	GiveWeaponDelayed(Handle, 0x1D073A89, 9999, 1); // pump shotgun
	GiveWeaponDelayed(Handle, 0x7846A318, 9999, 1); // sawnoff shotgun
	GiveWeaponDelayed(Handle, 0xE284C527, 9999, 1); // assault shotgun
	GiveWeaponDelayed(Handle, 0x9D61E50F, 9999, 1); // bullpupshotgun
	GiveWeaponDelayed(Handle, 0x05FC3C11, 9999, 1); // sniper
	GiveWeaponDelayed(Handle, 0x0C472FE2, 9999, 1); // heavy sniper
	GiveWeaponDelayed(Handle, 0xA284510B, 9999, 1); // grenade launcher
	GiveWeaponDelayed(Handle, 0xB1CA77B1, 9999, 1); // rpg
	GiveWeaponDelayed(Handle, 0x42BF8A85, 9999, 1); // minigun
	GiveWeaponDelayed(Handle, 0x93E220BD, 9999, 1); // grenades
	GiveWeaponDelayed(Handle, 0x2C3731D9, 9999, 1); // sticky bomb
	GiveWeaponDelayed(Handle, 0xFDBC8A50, 9999, 1); // smoke grenade
	GiveWeaponDelayed(Handle, 0x34A67B97, 9999, 1); // petrol can
	GiveWeaponDelayed(Handle, 0x060EC506, 9999, 1); // fire extinguisher
	GiveWeaponDelayed(Handle, 0x24B17070, 9999, 1); // moltovs
	GiveWeaponDelayed(Handle, 0x497FACC3, 9999, 1); // flare
    GiveWeaponDelayed(Handle, 0xFDBADCED, 9999, 1); // digiscanner
	GiveWeaponDelayed(Handle, 0x687652CE, 9999, 1); // stinger
	GiveWeaponDelayed(Handle, 600439132,  9999, 1); // ball
	// DLC Weapons
	GiveWeaponDelayed(Handle, 0xF9E6AA4B, 9999, 1); // bottle
	GiveWeaponDelayed(Handle, 0x61012683, 9999, 1); // gusenerg
	GiveWeaponDelayed(Handle, 0xC0A3098D, 9999, 1); // special carbine
	GiveWeaponDelayed(Handle, 0xD205520E, 9999, 1); // heavy pistol
	GiveWeaponDelayed(Handle, 0xBFD21232, 9999, 1); // sns pistol
	GiveWeaponDelayed(Handle, 0x7F229F94, 9999, 1); // bullpup rifle
	GiveWeaponDelayed(Handle, 0x92A27487, 9999, 1); // dagger
	GiveWeaponDelayed(Handle, 0x083839C4, 9999, 1); // vintage pistol
	GiveWeaponDelayed(Handle, 0x7F7497E5, 9999, 1); // firework launcher
	GiveWeaponDelayed(Handle, 0xA89CB99E, 9999, 1); // musket
	GiveWeaponDelayed(Handle, 0x63AB0442, 9999, 1); // homing launcher
	GiveWeaponDelayed(Handle, 0xAB564B93, 9999, 1); // proxmine
	GiveWeaponDelayed(Handle, 0x787F0BB,  9999, 1); // snowball
	GiveWeaponDelayed(Handle, 0xC734385A, 9999, 1); // marksman rifle
	GiveWeaponDelayed(Handle, 0x47757124, 9999, 1); // flare gun
	GiveWeaponDelayed(Handle, 0x0A3D4D34, 9999, 1); // Combat PDW
	//GiveWeaponDelayed(Handle, 0xE232C28C, 9999, 1); // trash bag
	//GiveWeaponDelayed(Handle, 0xD04C944D, 9999, 1); // handcuffs

	ShowMessageOnScreen("~g~ Gave online player all weapons");

	return 0;
}

int TakeOnlineAllWeapons(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	//int subMenuIndex = selectedMenuIndexes->operator[](1);
	int i = 0;
	for (i = 0;i<18;i++)
    {
    int Handle = GetPlayerHandle(i);
	RemoveWeapons(Handle);
	}
	ShowMessageOnScreen("~g~ Removed everyone's weapons");
	return 0;
}

int GiveOnlineParachute(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int subMenuIndex = selectedMenuIndexes->operator[](1);
    int Handle = GetPlayerHandle(subMenuIndex);

	GiveWeaponDelayed(Handle, 0xFBAB5776, 9999, 1);

	ShowMessageOnScreen("~g~ Gave Player Parachute");

	return 0;
}

int GiveOnlineAllWeapons(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	int i = 0;
	for (i = 0;i<18;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	GiveWeaponDelayed(Handle, 0x3656C8C1, 9999, 1); // stun gun
	GiveWeaponDelayed(Handle, 0x99B507EA, 9999, 1); // knife
	GiveWeaponDelayed(Handle, 0x678B81B1, 9999, 1); // night stick
	GiveWeaponDelayed(Handle, 0x4E875F73, 9999, 1); // hammer
	GiveWeaponDelayed(Handle, 0x958A4A8F, 9999, 1); // bat
	GiveWeaponDelayed(Handle, 0x440E4788, 9999, 1); // golf club
	GiveWeaponDelayed(Handle, 0x84BD7BFD, 9999, 1); // crowbar
	GiveWeaponDelayed(Handle, 0x1B06D571, 9999, 1); // pistol
	GiveWeaponDelayed(Handle, 0x5EF9FEC4, 9999, 1); // combat pistol
	GiveWeaponDelayed(Handle, 0x22D8FE39, 9999, 1); // ap pistol
	GiveWeaponDelayed(Handle, 0x99AEEB3B, 9999, 1); // pistol 50.
	GiveWeaponDelayed(Handle, 0x13532244, 9999, 1); // micro smg
	GiveWeaponDelayed(Handle, 0x2BE6766B, 9999, 1); // smg
	GiveWeaponDelayed(Handle, 0xEFE7E2DF, 9999, 1); // assault smg
	GiveWeaponDelayed(Handle, 0xBFEFFF6D, 9999, 1); // assault rifle
	GiveWeaponDelayed(Handle, 0x83BF0278, 9999, 1); // carbine rifle
	GiveWeaponDelayed(Handle, 0xAF113F99, 9999, 1); // advanced rifle
	GiveWeaponDelayed(Handle, 0x9D07F764, 9999, 1); // MG
	GiveWeaponDelayed(Handle, 0x7FD62962, 9999, 1); // combat mg
	GiveWeaponDelayed(Handle, 0x1D073A89, 9999, 1); // pump shotgun
	GiveWeaponDelayed(Handle, 0x7846A318, 9999, 1); // sawnoff shotgun
	GiveWeaponDelayed(Handle, 0xE284C527, 9999, 1); // assault shotgun
	GiveWeaponDelayed(Handle, 0x9D61E50F, 9999, 1); // bullpupshotgun
	GiveWeaponDelayed(Handle, 0x05FC3C11, 9999, 1); // sniper
	GiveWeaponDelayed(Handle, 0x0C472FE2, 9999, 1); // heavy sniper
	GiveWeaponDelayed(Handle, 0xA284510B, 9999, 1); // grenade launcher
	GiveWeaponDelayed(Handle, 0xB1CA77B1, 9999, 1); // rpg
	GiveWeaponDelayed(Handle, 0x42BF8A85, 9999, 1); // minigun
	GiveWeaponDelayed(Handle, 0x93E220BD, 9999, 1); // grenades
	GiveWeaponDelayed(Handle, 0x2C3731D9, 9999, 1); // sticky bomb
	GiveWeaponDelayed(Handle, 0xFDBC8A50, 9999, 1); // smoke grenade
	GiveWeaponDelayed(Handle, 0x34A67B97, 9999, 1); // petrol can
	GiveWeaponDelayed(Handle, 0x060EC506, 9999, 1); // fire extinguisher
	GiveWeaponDelayed(Handle, 0x24B17070, 9999, 1); // moltovs
	GiveWeaponDelayed(Handle, 0x497FACC3, 9999, 1); // flare
    GiveWeaponDelayed(Handle, 0xFDBADCED, 9999, 1); // digiscanner
	GiveWeaponDelayed(Handle, 0x687652CE, 9999, 1); // stinger
	GiveWeaponDelayed(Handle, 600439132,  9999, 1); // ball
	// DLC Weapons
	GiveWeaponDelayed(Handle, 0xF9E6AA4B, 9999, 1); // bottle
	GiveWeaponDelayed(Handle, 0x61012683, 9999, 1); // gusenerg
	GiveWeaponDelayed(Handle, 0xC0A3098D, 9999, 1); // special carbine
	GiveWeaponDelayed(Handle, 0xD205520E, 9999, 1); // heavy pistol
	GiveWeaponDelayed(Handle, 0xBFD21232, 9999, 1); // sns pistol
	GiveWeaponDelayed(Handle, 0x7F229F94, 9999, 1); // bullpup rifle
	GiveWeaponDelayed(Handle, 0x92A27487, 9999, 1); // dagger
	GiveWeaponDelayed(Handle, 0x083839C4, 9999, 1); // vintage pistol
	GiveWeaponDelayed(Handle, 0x7F7497E5, 9999, 1); // firework launcher
	GiveWeaponDelayed(Handle, 0xA89CB99E, 9999, 1); // musket
	GiveWeaponDelayed(Handle, 0x63AB0442, 9999, 1); // homing launcher
	GiveWeaponDelayed(Handle, 0xAB564B93, 9999, 1); // proxmine
	GiveWeaponDelayed(Handle, 0x787F0BB,  9999, 1); // snowball
	GiveWeaponDelayed(Handle, 0xC734385A, 9999, 1); // marksman rifle
	GiveWeaponDelayed(Handle, 0x47757124, 9999, 1); // flare gun
	GiveWeaponDelayed(Handle, 0xE232C28C, 9999, 1); // trash bag
	GiveWeaponDelayed(Handle, 0xD04C944D, 9999, 1); // handcuffs
    }
	return 0;
	ShowMessageOnScreen("~g~ Gave online players all weapons");
}

int BlowUpAllOnlinePlayers(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int i = 0;
	for (i = 0;i<18;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	float Position[3];
    GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2], 16, 2.0f, true, false, 0.0f);
	}
	return 0;
	ShowMessageOnScreen("~g~ Blew up all players");
}

bool alldrop = false;
float allcash[3];
int AllCashDrop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if(!alldrop){
		alldrop = true;
	ShowMessageOnScreen("~g~ Lobby Drop Active");
	 }
	else if(alldrop){
		alldrop = false;
	ShowMessageOnScreen("~g~ Lobby Drop Disabled");
	 }
	return 0;
}

bool alltelefoot = false;
int TeleAllOnlinePlayers(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	alltelefoot = true;
	ShowMessageOnScreen("~y~ Teleporting all players");
	return 0;
}

int AllWay(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	alltelefootway = true;
	ShowMessageOnScreen("~y~ Teleporting all players");
	return 0;
}


int AllKickedFromVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	allkickedfromveh = true;
	ShowMessageOnScreen("~y~ Kicking all Players");
	return 0;
}

int STFUTroll(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!STFUTrollactive)
	{
		STFUTrollactive = true;
	}

	else if(STFUTrollactive)
	{
		STFUTrollactive = false;
	}

	return 0;
}

int FreezeAllPlayers(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	if(!freezeall)
	{
		freezeall = true;
	}

	else if(freezeall)
	{
		freezeall = false;
	}

	return 0;
}


bool allanim = false;
int AllPlayersDance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
    animdict = "mini@strip_club@private_dance@part1";
    anim = "priv_dance_p1";
    animid = subMenuIndex;
	allanim = true;
	ShowMessageOnScreen("~g~ Starting animimation on all players");
	return 0;
}

int AllPlayersPoleDance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
    animdict = "mini@strip_club@pole_dance@pole_dance1";
    anim = "pd_dance_01";
    animid = subMenuIndex;
	allanim = true;
	ShowMessageOnScreen("~g~ Starting animimation on all players");
	return 0;
}

int StopAll(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	int i = 0;
	for (i = 0;i<16;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	clear_ped_tasks(Handle);
	}
	ShowMessageOnScreen("~g~ Stopping animimation on all players");
	return 0;
}

int AllPlayersElectrocute(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
    animdict = "ragdoll@human";
    anim = "electrocute";
    animid = subMenuIndex;
	allanim = true;
	ShowMessageOnScreen("~g~ Starting animimation on all players");
	return 0;
}

bool hasaimed = false;
bool hasaimedatplayer = false;
int arresthandle;
int aimbotClient = 0;
bool arrest = false;
bool arresthit = false;
void aimbotloop(int Client) {
	int i = Client,
		player_id = PlayerId(),
		player_ped_id = PlayerPedId();
	//for (i = 0;i<16;i++)
    {
		if (i == player_id) return;//continue;
		int Handle = GetPlayerHandle(i);
		if(!DoesEntityExist(Handle)) return;//continue;
		if(!isInDistance(Handle)) return;//continue;
		if(is_control_pressed(2, 180) && is_ped_on_foot(player_ped_id) && has_entity_clear_los_to_entity(player_ped_id, Handle, 17) && is_ped_on_foot(Handle)) {
			if (!arresthit) {
				hasaimedatplayer = true;
				//ShowMessageOnScreen("~g~ Locked on to player");
				arresthandle = Handle;
				arrest = true;
				arresthit = true;
			}
		}
		if (is_entity_dead(Handle))return;//continue;
	}
	if (is_control_just_released(2, 180)) {
		if (hasaimedatplayer) {
		//ShowMessageOnScreen("~g~ Released aim");
		hasaimed = true;
		hasaimedatplayer = false;
		arresthit = false;
		}
	}
}

void aimbotrelease() {
	if (hasaimed) {
	//clear_ped_tasks_immediately(PlayerPedId());
	clear_ped_tasks(PlayerPedId());
	hasaimed = false;
	}
}

/*void tpGunLoop()
 {
  float Loc[3];
  if (is_ped_shooting(PlayerPedId()))
  {
   if (get_ped_last_weapon_impact_coord2(PlayerPedId(), Loc))
   {
    Vector3 Pos;
    Pos.x = Loc[0]; Pos.y = Loc[1]; Pos.z = Loc[2];
    set_entity_coords2(PlayerPedId(), &Pos, 0, 0, 0, 1);
   }
  }
 }*/

void UltimateDeagleLoop()
{
float Pos[3];
float health;
     if (is_control_just_pressed(0, 24)){
		GetEntityCoords(PlayerPedId(), Pos);
        int vehHandle = get_closest_vehicle(Pos[0], Pos[1], Pos[2], 2000.0f, 0, 0);
		health = get_vehicle_petrol_tank_health(vehHandle);
        GetCoordsInfrontOfSelf(&Pos[0], &Pos[1], &Pos[2]);
		if(network_request_control_of_entity(vehHandle) && (health > 1)) {
		ShowMessageOnScreen("~g~ ");
		freeze_entity_position(vehHandle, true);
        set_entity_coords(vehHandle, Pos[0], Pos[1], Pos[2], 0, 0, 0, 1);
        set_entity_heading(vehHandle, get_entity_heading(PlayerPedId()));
		freeze_entity_position(vehHandle, false);
        apply_force_to_entity(vehHandle, 1, 0.0, 1000.0f, 0.0, 0.0, -1.5f, 0.0f, 0, 1, 1, 1, false, true);
		}
		else { ShowMessageOnScreen("~g~ No vehicle in memory at this time."); }
	 }
	//3455827142:has_ped_been_damaged_by_weapon HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(Test, WEAPON_DEAGLE) 82E13440
	//2955113218:get_current_ped_weapon GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &weapon); 82E13030
	//133986272:has_entity_been_damaged_by_entity HAS_CHAR_BEEN_DAMAGED_BY_CHAR(Test, GetPlayerPed(), false) 82D7BF80
}

int ToggleUltimateDeagle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	deagle = !deagle;
	return 0;
}
bool ammo;
int ToggleAmmo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!ammo) {
	ammo = true;
	//set_ped_infinite_ammo(PlayerPedId(), true);
	set_ped_infinite_ammo_clip(PlayerPedId(), true);
	ShowMessageOnScreen("~y~ Unlimited Ammo: ~g~ON!");
	}
	else if (ammo) {
	//set_ped_infinite_ammo(PlayerPedId(), false);
    set_ped_infinite_ammo_clip(PlayerPedId(), false);
	ShowMessageOnScreen("~y~ Unlimited Ammo: ~r~OFF!");
    ammo = false;
	}
    //ShowMessageOnScreen("~r~ Sorry this has been disabled for now it isn't working properly!");
	return 0;
}

int ToggleAimbot(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!aimbot) {
	aimbot = true;
	aimbot_active = true;
	ShowMessageOnScreen("~g~ Aimbot turned on!");
	}
	else if (aimbot) {
	ShowMessageOnScreen("~g~ Aimbot turned off!");
	aimbot_active = false;
    aimbot = false;
	}
	return 0;
}
float excoords[3];
int exptype = 28;
bool hmmm = false;
int RocketGunExp0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 12;
	ShowMessageOnScreen("~r~ Gas leak explosion set");
	return 0;
}
int RocketGunExp1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 13;
	ShowMessageOnScreen("~r~ Hyrdrant explosion set");
	return 0;
}
int RocketGunExp2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 19;
	ShowMessageOnScreen("~r~ Smoke cloud explosion set");
	return 0;
}
int RocketGunExp3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 22;
	ShowMessageOnScreen("~r~ Flare explosion set");
	return 0;
}
int RocketGunExp4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 24;
	ShowMessageOnScreen("~r~ Steam explosion set");
	return 0;
}
int RocketGunExp5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 27;
	ShowMessageOnScreen("~r~ Small explosion set");
	return 0;
}
int RocketGunExp6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 28;
	ShowMessageOnScreen("~r~ Medium explosion set");
	return 0;
}
int RocketGunExp7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	exptype = 29;
	ShowMessageOnScreen("~r~ Massive explosion set");
	return 0;
}
int ToggleRocketGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {

	if (!rocket_gun) {
		rocket_gun = true;
		//hmmm = true;
		ShowMessageOnScreen("~g~ Rocket guns turned on!");
	}
	else if (rocket_gun) {
		ShowMessageOnScreen("~g~ Rocket guns turned off!");
		rocket_gun = false;
		//hmmm = false;
	}
	return 0;
}

void rocketgun()
{
	int ped_id = PlayerPedId();
    if ( is_ped_shooting( ped_id ) )
    {
	
		if (get_ped_last_weapon_impact_coord(PlayerPedId(), excoords))
		{
			AddExplosion(excoords[0], excoords[1], excoords[2], exptype, 5.0, 1, 0, 0);
		}
		}
}



float fwcoords[3];
bool fw_gun_ready = false;
void fwgun()
{
int ped_id = PlayerPedId();
if (is_ped_shooting(ped_id))
{
if (get_ped_last_weapon_impact_coord(PlayerPedId(), fwcoords))
{
fw_gun_ready = true;
}
}
}

void rocketgun2()
{
	int ped_id = PlayerPedId();
    if ( is_ped_shooting( ped_id ) )
    {
		if (get_ped_last_weapon_impact_coord(PlayerPedId(), excoords))
		{
			AddExplosion(excoords[0], excoords[1], excoords[2], 36, 5.0, 1, 0, 0);
		}
		}
}


int TeleImpoundLot(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	float x,y,z;
	x = -1330.267822, y = -390.644684, z = 36.602779;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	ShowMessageOnScreen("~g~ Teleported to ammunation store!");
	return 0;
}
int TeleCoords(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	float Pos[3];
	GetEntityCoords(GetPlayerHandle(PlayerId()), Pos);
	printf("\tPosition = {%f, %f, %f};\n", Pos[0], Pos[1], Pos[2]);
	ShowMessageOnScreen("~g~ Position = %f   %f   %f", Pos[0], Pos[1], Pos[2]);
	return 0;
}

int ObjectCoords(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	float Pos[3];
	GetEntityCoords(objecthandle, Pos);
	printf("\tPosition = {%f, %f, %f};\n", Pos[0], Pos[1], Pos[2]);
	ShowMessageOnScreen("~g~ Position = %.3f   %.3f   %.3f", Pos[0], Pos[1], Pos[2]);
	return 0;
}

int ObjectHash(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
#ifdef PRIVATE
	int hash = get_entity_model(objecthandle);
	printf("Object Hash = %i \n", hash);
	ShowMessageOnScreen("~g~ Object Hash = %i", hash);
#else
	ShowMessageOnScreen("~r~ Sorry this is only available in the private version!");
#endif
	return 0;
}
bool objectcopy = false;
int ObjectCopy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int hash = get_entity_model(objecthandle);
	model = hash;
	objectspawn = true;
	objectcopy = true;
	printf("Copied Object %i \n", hash);
	ShowMessageOnScreen("~g~ Copied Object Object = %i", hash);
	return 0;
}

bool deleted_obj = false;
int ObjectDelete(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int hash = get_entity_model(objecthandle);
	deleted_obj = true;
	printf("Deleted Object %i \n", hash);
	ShowMessageOnScreen("~g~ Deleted Object = %i", hash);
	return 0;
}

int DetachModder(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int modder = GET_ENTITY_ATTACHED_TO(PlayerPedId());
	detach_entity(modder);
	return 0;
}

//	Position = {8.069606, 537.153015, 176.028015};

int TeleFranklinsCrib(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z;
	x = 8.069606, y = 537.153015, z = 176.028015;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		} //Position = {-385.378601, 204.318146, 85.885498};
	//Position = {-385.930908, 203.293900, 86.273972};

		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Franklins crib!");
	return 0;
}

int TeleMicsCrib(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z;
	x = -813.176453, y = 179.232452, z = 72.159149;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Micheals crib!");
	return 0;
}

int TeleLsCustoms(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z;
	x = -384.217834, y = -118.733658, z = 38.689579;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to LS Customs!");
	return 0;
}

int TeleWeaselTower(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z;
	x = -847.499084, y = -434.825989, z = 36.639900;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Weasel Tower Garage!");
	return 0;
}

int TeleUnionDepository(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z;
	x = 8.873180, y = -684.307739, z = 32.338120;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Union Depository!");
	return 0;
}

float saveX, saveY, saveZ;
int SaveTeleLocation(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	GetEntityCoords(PlayerPedId(), &saveX, &saveY, &saveZ);
	ShowMessageOnScreen("~y~ Saved Location 1!");
	return 0;
}

int TeleToSave(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, saveX, saveY, saveZ, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, saveX, saveY, saveZ, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Saved Location 1!");
	return 0;
}

float save2X, save2Y, save2Z;
int SaveTeleLocation2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	GetEntityCoords(PlayerPedId(), &save2X, &save2Y, &save2Z);
	ShowMessageOnScreen("~y~ Saved Location 2!");
	return 0;
}

int TeleToSave2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, save2X, save2Y, save2Z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, save2X, save2Y, save2Z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Saved Location 2!");
	return 0;
}

float save3X, save3Y, save3Z;
int SaveTeleLocation3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	GetEntityCoords(PlayerPedId(), &save3X, &save3Y, &save3Z);
	ShowMessageOnScreen("~y~ Saved Location 3!");
	return 0;
}

int TeleToSave3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, save3X, save3Y, save3Z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, save3X, save3Y, save3Z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Saved Location 3!");
	return 0;
}

float save4X, save4Y, save4Z;
int SaveTeleLocation4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	GetEntityCoords(PlayerPedId(), &save4X, &save4Y, &save4Z);
	ShowMessageOnScreen("~y~ Saved Location 4!");
	return 0;
}

int TeleToSave4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, save4X, save4Y, save4Z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, save4X, save4Y, save4Z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Saved Location 4!");
	return 0;
}

float save5X, save5Y, save5Z;
int SaveTeleLocation5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	GetEntityCoords(PlayerPedId(), &save5X, &save5Y, &save5Z);
	ShowMessageOnScreen("~y~ Saved Location 5!");
	return 0;
}

int TeleToSave5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, save5X, save5Y, save5Z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, save5X, save5Y, save5Z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Saved Location 5!");
	return 0;
}

float save6X, save6Y, save6Z;
int SaveTeleLocation6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	GetEntityCoords(PlayerPedId(), &save6X, &save6Y, &save6Z);
	ShowMessageOnScreen("~y~ Saved Location 6!");
	return 0;
}

int TeleToSave6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, save6X, save6Y, save6Z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, save6X, save6Y, save6Z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Saved Location 6!");
	return 0;
}

float save7X, save7Y, save7Z;
int SaveTeleLocation7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	GetEntityCoords(PlayerPedId(), &save7X, &save7Y, &save7Z);
	ShowMessageOnScreen("~y~ Saved Location 7!");
	return 0;
}

int TeleToSave7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, save7X, save7Y, save7Z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, save7X, save7Y, save7Z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Saved Location 7!");
	return 0;
}

int TeleIntoCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	float Pos[3];
	GetEntityCoords(PlayerPedId(), Pos);
    int vehHandle = get_closest_vehicle(Pos[0], Pos[1], Pos[2], 2000.0f, 0, 0);
	int myhandle = GetPlayerHandle(PlayerId());
	  int var4 = -1;
      int pasnmax;
      pasnmax = get_vehicle_max_number_of_passengers(vehHandle);
      while (var4 < pasnmax) {
        if (is_vehicle_seat_free(vehHandle, var4)) {
			set_ped_into_vehicle(myhandle, vehHandle, var4);
			ShowMessageOnScreen("~g~ Teleported into nearby car!");
			break;
			}
			else
			{
            var4++;
			}
			}
			if (var4 > pasnmax){
			ShowMessageOnScreen("~g~ Failed, No available seat in nearby car!");
		}
	return 0;
}

int TeleGarage(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 228.7188, y = -989.9847, z = -99.0;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to 10 Car Garage!");
	return 0;
}

int TeleAirport(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	//x = -1030.025146, y = -3015.658691, z = 49.091133;
	x = -1157.929565, y = -3148.384766, z = 13.944441;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Airport!");
	return 0;
}

int TelePonsonbys(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	//x = -1030.025146, y = -3015.658691, z = 49.091133;
	x = -148.248779, y = -308.142090, z = 38.151409;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Ponsonbys in Burton!");
	return 0;
}

int TeleVaginaCove(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	//x = -1030.025146, y = -3015.658691, z = 49.091133;
	x = -1895.996582, y = 1390.620361, z = 216.218048;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Vagina Cove in Tongva Hills!");
	return 0;
}

int TeleEclipse(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -810.110901, y = 300.467865, z = 86.118515;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Eclipse Tower");
	return 0;
}

int TeleTinsel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -641.864624, y = 24.014740, z = 39.351025;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Tinsel Tower");
	return 0;
}

int TelePaletoBank(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -107.862190, y = 6466.428223, z = 31.626722;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Paleto Bank");
	return 0;
}

int TeleMntGraveSite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 3201.509033, y = 4728.985840, z = 193.161636;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Mountain Grave Site!");
	return 0;
}

int TeleTrevorField(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 1704.752686, y = 3275.902832, z = 41.157715;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Trevor's Airfield");
	return 0;
}

int TeleSecretIsland(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -2167.429932, y = 5190.774414, z = 16.238092;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Secret Island");
	return 0;
}

int TeleArmyTower(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -2358.946045, y = 3252.216797, z = 101.450424;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Secret Army Tower");
	return 0;
}

int TeleMountChill(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 495.518433, y = 5588.867188, z = 794.483215;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Mount Chilliad");
	return 0;
}

int TeleDesertClub(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 2004.878540, y = 3073.016113, z = 46.794247;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Desert Night Club");
	return 0;
}

int TeleFIB(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 135.534073, y = -749.334595, z = 258.151764;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to FIB Building");
	return 0;
}

int TeleLabUpper(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 3618.517822, y = 3740.693604, z = 28.690096;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Secret Lab Upper Level");
	return 0;
}

int TeleBankVault(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 258.252930, y = 225.658600, z = 101.683197;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Bank Vault");
	return 0;
}

int TeleBridge(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -546.417297, y = -2229.224365, z = 122.364899;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Bridge Top");
	return 0;
}

int TeleTorture(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 136.323441, y = -2203.203857, z = 7.309136;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Torture Room");
	return 0;
}

int TeleLabLower(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 3526.256836, y = 3706.816895, z = 20.991793;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Secret Lab Lower Level");
	return 0;
}

int TeleMazeTower(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -73.92588, y = -818.455078, z = 326.174377;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Maze Tower");
	return 0;
}

int TeleJetSpawn1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -2150.634277, y = 3234.995117, z = 32.810455;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Military Base");
	return 0;
}

int TeleSubSpawn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 3846.635254, y = 4243.365234, z = 5.335886;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Submarine Spawn");
	return 0;
}

int TeleJetSpawn3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -2138.139893, y = 3056.729736, z = 32.809875;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Jet Spawn");
	return 0;
}

int TeleJetSpawn4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -2022.258423, y = 2973.546875, z = 33.118137;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Jet Spawn");
	return 0;
}

int TeleJetSpawn5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -2007.929932, y = 3098.386475, z = 32.810257;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Jet Spawn");
	return 0;
}

int TelePolice(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 446.413544, y = -985.128113, z = 30.689520;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Police Station");
	return 0;
}

int TeleClock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -1238.675537, y = -847.954590, z = 85.161690;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Clock Tower");
	return 0;
}

int TeleSniper(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -550.989380, y = -193.862366, z = 76.499336;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Sniper Tower");
	return 0;
}

int TeleMerry(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 568.406006, y = -3125.799805, z = 18.768612;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Merryweather");
	return 0;
}

int TeleAirOffice(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -1559.734741, y = -3237.086182, z = 29.634100;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Airport Office");
	return 0;
}

int TeleConstructionTower(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = -143.881927, y = -984.810852, z = 269.134308;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to Construction Tower");
	return 0;
}

int TeleIAA(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	float x,y,z; 
	x = 121.494728, y = -622.014954, z = 206.046783;
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported to IAA Building");
	return 0;
}

bool TeleportToWaypoint = false;
float WaypointPos[3];
int WaypointEntity;
int TeleWay(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_entity_coords(GetPlayerHandle(PlayerId()), -1330.267822, -390.644684, 36.602779, 1, 0, 0, 1);
	// Haven't coded this yet.
	int waypoint = get_first_blip_info_id(8);
	if(does_blip_exist(waypoint)) {
		get_blip_coords(waypoint, WaypointPos);
		int myhandle = PlayerPedId(),
			myvehicle;
		if (is_ped_in_any_vehicle(myhandle)) {
			myvehicle = GetCarCharIsIn(myhandle, 0);
			if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
				WaypointEntity = myvehicle;
				set_entity_coords(myvehicle, WaypointPos[0], WaypointPos[1], WaypointPos[2], 0, 0, 0, 1);
				load_all_objects_now();
			}
			else {
				WaypointEntity = myhandle;
				set_entity_coords(myhandle, WaypointPos[0], WaypointPos[1], WaypointPos[2], 0, 0, 0, 1);
				load_all_objects_now();
			}
			TeleportToWaypoint = true;
		}
	}
	else {
		ShowMessageOnScreen("~g~ Please set a waypoint first!");
	}
	return 0;
}

void Waypointloop() {
	if(get_ground_z_for_3d_coord(WaypointPos[0], WaypointPos[1], 600.0f, &WaypointPos[2])) {
		set_entity_coords(WaypointEntity, WaypointPos[0], WaypointPos[1], WaypointPos[2], 0, 0, 0, 1);
		TeleportToWaypoint = false;
		ShowMessageOnScreen("~g~ Teleported to Waypoint!");
	}
}


int StripperModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x9CF26183;//0x9CF26183;
	
	return 0;
}

int MonkeyModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -1026527405;//0x9CF26183;
	
	return 0;
}

int MonkeySpaceModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -598109171;//0x9CF26183;
	
	return 0;
}


bool alienspawn = false;
int AlienModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x64611296;//0x9CF26183;
	alienspawn = true;
	return 0;
}
bool invisiblemodel = false;
int InvisibleModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x2970A494;//0x9CF26183;
	invisiblemodel = true;
	return 0;
}

int OnlineStripper(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x2970A494;//0x9CF26183;
	return 0;
}

float x10, y10, z10, x20, y20, z20; 

bool ufomode = false;
int FlyingAnus(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	if (is_ped_in_any_vehicle(PlayerPedId())){
	objectspawn = true;
	model = 0xB467C540; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	x10 = 0, y10 = 0, z10 = + 3.9, x20 = 0, y20 = 0, z20 = 0;
	ShowMessageOnScreen("~g~ UFO spawned works best in the cargo plain!");
	ufomode = true;
	}
	else{
	ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}
bool fDummyPlane = false;
int FlyingDummyPlane(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (is_ped_in_any_vehicle(PlayerPedId())){
	objectspawn = true;
	model = -473036318; 
	x10 = 0, y10 = 0, z10 = + 3.9, x20 = 0, y20 = 0, z20 = 0;
	ShowMessageOnScreen("~g~ Dummy Plane attached to vehicle!");
	fDummyPlane = true;
	}
	else{
	ShowMessageOnScreen("~g~ You aren't in a vehicle");
	}
	return 0;
}

bool dodgem2 = false;
bool dodgem3 = false;
bool dodgemvehicle = false;
int DodgemCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	ShowMessageOnScreen("~g~ Dodgem car spawned works best in the comet!");
	dodgemvehicle = true;
	return 0;
}

int SpawnObject(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	//model = 0xBF8918DE; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	model = -1536924937;
	return 0;
}

int SpawnWeed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 452618762; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Weed for everyone!");
	return 0;
}

int SpawnRamp(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -1818980770; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Spawned Ramp!");
	return 0;
}

int SpawnBody(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -1240857364; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Dead bodies!");
	return 0;
}//
bool derby = false;
int DerbyArena(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien bool  Playboy (naked)
	objectspawn = true;
	//normalspawn = true;
	derby = true;
	model = -1003748966; // spunk ramp 0xBF8918DE // UFO 0xB467C540

	//ShowMessageOnScreen("~g~ Derby Arena!");
	return 0;
}//
int cam;
float rot[3];
bool cam_mode = false;
bool cam_check = false;
bool cam_load = false;
int FlyMod(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//ShowMessageOnScreen("~r~ In Progress...");
	if (!cam_mode) {
	cam_load = true;
	cam_mode = true;
	ShowMessageOnScreen("~y~ First Person: ~g~ON, ~b~If the camera rotation is stuck. Join new session!");
	}
	else if (cam_mode) {
    cam_mode = false;
	cam_load = false;
	set_cam_active(cam, false);
	DESTROY_CAM(cam, true);
	render_script_cams(0, 0, 3000, 1, 0);
	ShowMessageOnScreen("~y~ First Person: ~r~OFF");
	}
	return 0;
}

int Seccam1;
float SecCam1rot[3];
bool Seccam_mode = false;
bool Seccam_check = false;
bool Seccam_load = false;
int LSCSecCam(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//ShowMessageOnScreen("~r~ In Progress...");
	if (!Seccam_mode) {
	Seccam_load = true;
	Seccam_mode = true;
	ShowMessageOnScreen("~y~LSC Security Camera: ~g~ON");
	}
	else if (Seccam_mode) {
    Seccam_mode = false;
	set_cam_active(Seccam1, false);
	DESTROY_CAM(Seccam1, true);
	render_script_cams(0, 0, 3000, 1, 0);
	ShowMessageOnScreen("~~y~LSC Security Camera: ~r~OFF");
	}
	return 0;
}

int Seccam2;
float SecCam2rot[3];
bool Seccam2_mode = false;
bool Seccam2_check = false;
bool Seccam2_load = false;
int EclipseSecCam(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//ShowMessageOnScreen("~r~ In Progress...");
	if (!Seccam2_mode) {
	Seccam2_load = true;
	Seccam2_mode = true;
	ShowMessageOnScreen("~y~Eclipse Towers Security Camera: ~g~ON");
	}
	else if (Seccam2_mode) {
    Seccam2_mode = false;
	set_cam_active(Seccam2, false);
	DESTROY_CAM(Seccam2, true);
	render_script_cams(0, 0, 3000, 1, 0);
	ShowMessageOnScreen("~~y~Eclipse Towers Security Camera: ~r~OFF");
	}
	return 0;
}

bool fly_car = false;
int FlyCarMod(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (is_ped_on_foot(PlayerPedId())) {
	ShowMessageOnScreen("~r~ This option is only available while in a vehicle");
	return 0;
	}
	if (!fly_car) {
	//GiveWeaponDelayed(PlayerPedId(), 0xFBAB5776, 1, 1);
    apply_force_to_entity(GetCarCharIsIn(PlayerPedId(), 0), true, 0, 0, 40, 0, 0, 0, true, true, true, true, false, true);
	//SetPlayerInvincible(PlayerId(), true);
	fly_car = true;
	}
	else if (fly_car) {
	fly_car = false;
	}
	return 0;
}

void fly_car_loop() 
{
if (!is_ped_on_foot(PlayerPedId())) 
{
apply_force_to_entity(GetCarCharIsIn(PlayerPedId(), 0), true, 0, 100, 100, 0, 0, 0, false, true, false, false, false, true);
}
}

bool super_check = false;
int SuperMod(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!super_check) {
	GiveWeaponDelayed(PlayerPedId(), 0xFBAB5776, 1, 1);
    apply_force_to_entity(PlayerPedId(), true, 0, 0, 40, 0, 0, 0, true, true, true, true, false, true);
	SetPlayerInvincible(PlayerId(), true);
	super_check = true;
	ShowMessageOnScreen("~y~Superman Mode: ~g~ON!");
	}
	else if (super_check) {
	super_check = false;
	ShowMessageOnScreen("~y~Superman Mode: ~r~OFF!");
	}
	return 0;
}

void super_loop() 
{
 if (unk_0xCD71F11B(PlayerPedId()))
  {
   disable_control_action( 2, 124 );
   apply_force_to_entity(PlayerPedId(), true, 0, 100, 100, 0, 0, 0, false, true, false, false, false, true);
 }
}
#ifdef PRIVATE
int NormalSkin(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
gauge = 2;
return 0;
}

int BMWSkin(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
gauge = 1;
return 0;
}

int TestSkin(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
gauge = 3;
return 0;
}

int SimpleSkin(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
gauge = 4;
return 0;
}

#ifdef PRIVATE
int Rank(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
set_stat_int(get_hash_key("MP0_CHAR_XP_FM"), 2165850);
return 0;
}

int Rank1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	set_stat_int(get_hash_key("MP1_CHAR_XP_FM"), 2165850);
return 0;
}

int Rank2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	set_stat_int(get_hash_key("MP2_CHAR_XP_FM"), 2165850);
return 0;
}

int Rank420(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
set_stat_int(get_hash_key("MP0_CHAR_XP_FM"), 13288350);
return 0;
}

int Rank4201(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	set_stat_int(get_hash_key("MP1_CHAR_XP_FM"), 13288350);
return 0;
}

int Rank4202(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	set_stat_int(get_hash_key("MP2_CHAR_XP_FM"), 13288350);
return 0;
}

int TitleFont1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   titlefont = 1;
   return 0;
}

int TitleFont2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   titlefont = 2;
   return 0;
}

int TitleFont3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   titlefont = 3;
   return 0;
}

int TitleFont4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   titlefont = 4;
   return 0;
}

int TitleFont5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   titlefont = 5;
   return 0;
}

int TitleFont6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   titlefont = 6;
   return 0;
}

int TitleFont7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   titlefont = 7;
   return 0;
}

int ItemFont1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   itemfont = 1;
   return 0;
}

int ItemFont2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   itemfont = 2;
   return 0;
}

int ItemFont3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   itemfont = 3;
   return 0;
}

int ItemFont4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   itemfont = 4;
   return 0;
}

int ItemFont5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   itemfont = 5;
   return 0;
}

int ItemFont6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   itemfont = 6;
   return 0;
}

int ItemFont7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   itemfont = 7;
   return 0;
}
///////////////////Title Shader Colors Below
int tShaderBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 0;
   tShaderG = 0;
   tShaderB = 0;
   return 0;
}
int tShaderWhite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 255;
   tShaderG = 255;
   tShaderB = 255;
   return 0;
}
int tShaderCyan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 0;
   tShaderG = 255;
   tShaderB = 255;
   return 0;
}
int tShaderRed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 255;
   tShaderG = 0;
   tShaderB = 0;
   return 0;
}
int tShaderGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 0;
   tShaderG = 255;
   tShaderB = 0;
   return 0;
}
int tShaderOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 255;
   tShaderG = 128;
   tShaderB = 0;
   return 0;
}
int tShaderYellow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 255;
   tShaderG = 255;
   tShaderB = 0;
   return 0;
}
int tShaderPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tShaderR = 255;
   tShaderG = 0;
   tShaderB = 255;
   return 0;
}
/////////////////////Main Shader Colors Below
int mShaderBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 0;
   mShaderG = 0;
   mShaderB = 0;
   return 0;
}
int mShaderWhite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 255;
   mShaderG = 255;
   mShaderB = 255;
   return 0;
}
int mShaderCyan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 0;
   mShaderG = 255;
   mShaderB = 255;
   return 0;
}
int mShaderRed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 255;
   mShaderG = 0;
   mShaderB = 0;
   return 0;
}
int mShaderGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 0;
   mShaderG = 255;
   mShaderB = 0;
   return 0;
}
int mShaderOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 255;
   mShaderG = 128;
   mShaderB = 0;
   return 0;
}
int mShaderYellow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 255;
   mShaderG = 255;
   mShaderB = 0;
   return 0;
}
int mShaderPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mShaderR = 255;
   mShaderG = 0;
   mShaderB = 255;
   return 0;
}
//////////////////////Title Colors Below
int tBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 0;
   tG = 0;
   tB = 0;
   return 0;
}
int tWhite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 255;
   tG = 255;
   tB = 255;
   return 0;
}
int tCyan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 0;
   tG = 255;
   tB = 255;
   return 0;
}
int tRed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 255;
   tG = 0;
   tB = 0;
   return 0;
}
int tGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 0;
   tG = 255;
   tB = 0;
   return 0;
}
int tOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 255;
   tG = 128;
   tB = 0;
   return 0;
}
int tYellow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 255;
   tG = 255;
   tB = 0;
   return 0;
}
int tPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   tR = 255;
   tG = 0;
   tB = 255;
   return 0;
}
///////////////////Item Colors Below
int iBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 0;
   iG = 0;
   iB = 0;
   return 0;
}
int iWhite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 255;
   iG = 255;
   iB = 255;
   return 0;
}
int iCyan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 0;
   iG = 255;
   iB = 255;
   return 0;
}
int iRed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 255;
   iG = 0;
   iB = 0;
   return 0;
}
int iGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 0;
   iG = 255;
   iB = 0;
   return 0;
}
int iOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 255;
   iG = 128;
   iB = 0;
   return 0;
}
int iYellow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 255;
   iG = 255;
   iB = 0;
   return 0;
}
int iPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   iR = 255;
   iG = 0;
   iB = 255;
   return 0;
}
/////////////Selector Colors Below
int sBlack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 0;
   sG = 0;
   sB = 0;
   return 0;
}
int sWhite(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 255;
   sG = 255;
   sB = 255;
   return 0;
}
int sCyan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 0;
   sG = 255;
   sB = 255;
   return 0;
}
int sRed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 255;
   sG = 0;
   sB = 0;
   return 0;
}
int sGreen(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 0;
   sG = 255;
   sB = 0;
   return 0;
}
int sOrange(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 255;
   sG = 128;
   sB = 0;
   return 0;
}
int sYellow(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 255;
   sG = 255;
   sB = 0;
   return 0;
}
int sPink(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   sR = 255;
   sG = 0;
   sB = 255;
   return 0;
}
///////Menu Position Below
int MenuRightSide(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   x1 = 0.81f;
   staticItemX = 0.69f;
   menuTitlef = 0.8125f;
   return 0;
}
int MenuLeftSide(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   x1= 0.19f;
   staticItemX = 0.07f;
   menuTitlef = 0.1925;
   return 0;
}
int MenuCenter(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   x1= 00.50f;
   staticItemX = 0.38f;
   menuTitlef = 0.5025;
   return 0;
}

int MenuAlpha100(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 100;
   return 0;
}
int MenuAlpha150(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 150;
   return 0;
}
int MenuAlpha200(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 200;
   return 0;
}
int MenuAlpha255(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 255;
   return 0;
}

int VCAStyle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 0;
   titleAlpha = 0;
   scrollAlpha = 0;
   return 0;
}

int MetroStyle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 200;
   titleAlpha = 255;
   scrollAlpha = 255;
   return 0;
}

int CookiesStyle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 100;
   sR = 0;
   sG = 255;
   sB = 0;
   tShaderR = 0;
   tShaderG = 255;
   tShaderB = 0;
   iR = 255;
   iG = 255;
   iB = 255;
   tR = 255;
   tG = 255;
   tB = 255;
   return 0;
}

int StelioKontosStyle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 0;
   titleAlpha = 0;
   scrollAlpha = 0;
   x1 = 0.81f;
   staticItemX = 0.69f;
   menuTitlef = 0.8125f;
   iR = 255;
   iG = 128;
   iB = 0;
   tR = 255;
   tG = 128;
   tB = 0;
   return 0;
}

int ECMxVIPERStyle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   mainAlpha = 200;
   titleAlpha = 255;
   scrollAlpha = 255;
   x1 = 0.81f;
   staticItemX = 0.69f;
   menuTitlef = 0.8125f;
   sR = 255;
   sG = 255;
   sB = 0;
   tShaderR = 255;
   tShaderG = 255;
   tShaderB = 0;
   iR = 0;
   iG = 255;
   iB = 0;
   tR = 0;
   tG = 255;
   tB = 0;
   mShaderR = 0;
   mShaderG = 0;
   mShaderB = 0;
   return 0;
}

void scroll()
{
  if (x_f<1.0) x_f+= 0.003; else x_f=0;
  PrintToScreen(scroll_1, x_f, marqueeY, 0, 255, 255, 255, 0.6050f, 0.6050f, 0, 6);
}

void scroll_rec()
{
  draw_rect(0.5f, marqueeShaderY, 1.0f, 0.05f, 0, 0, 0, 255);
}

bool marqueeToggle = false;
int MarqueeToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
   if(!marqueeToggle){
	   marqueeToggle = true;
   }
   else if(marqueeToggle){
	   marqueeToggle = false;
   }
   return 0;
}



int BypassTUTMP0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_bool(get_hash_key("MP0_NO_TUT_SPAWN"), true);
	set_stat_bool(get_hash_key("MP0_FRONT_END_JIP_UNLOCKED"), true);
	set_stat_bool(get_hash_key("MP0_FM_TRIGTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP0_FM_HOLDTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP0_FM_CMODTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP0_FM_RACETUT_DONE"), true);
	return 0;
}

int BypassTUTMP1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_bool(get_hash_key("MP1_NO_TUT_SPAWN"), true);
	set_stat_bool(get_hash_key("MP1_FRONT_END_JIP_UNLOCKED"), true);
	set_stat_bool(get_hash_key("MP1_FM_TRIGTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP1_FM_HOLDTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP1_FM_CMODTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP1_FM_RACETUT_DONE"), true);
	return 0;
}

int BypassTUTMP2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_bool(get_hash_key("MP2_NO_TUT_SPAWN"), true);
	set_stat_bool(get_hash_key("MP2_FRONT_END_JIP_UNLOCKED"), true);
	set_stat_bool(get_hash_key("MP2_FM_TRIGTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP2_FM_HOLDTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP2_FM_CMODTUT_DONE"), true);
	set_stat_bool(get_hash_key("MP2_FM_RACETUT_DONE"), true);
	return 0;
}

int MaxSnacks0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP0_NO_BOUGHT_YUM_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP0_NO_BOUGHT_HEALTH_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP0_NO_BOUGHT_EPIC_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP0_CIGARETTES_BOUGHT") , 99999999);
    set_stat_int(get_hash_key("MP0_NUMBER_OF_ORANGE_BOUGHT"), 99999999);
    set_stat_int(get_hash_key("MP0_NUMBER_OF_BOURGE_BOUGHT"), 99999999);
	return 0;
}

int MaxSnacks1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP1_NO_BOUGHT_YUM_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP1_NO_BOUGHT_HEALTH_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP1_NO_BOUGHT_EPIC_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP1_CIGARETTES_BOUGHT") , 99999999);
    set_stat_int(get_hash_key("MP1_NUMBER_OF_ORANGE_BOUGHT"), 99999999);
    set_stat_int(get_hash_key("MP1_NUMBER_OF_BOURGE_BOUGHT"), 99999999);
	return 0;
}

int MaxSnacks2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP2_NO_BOUGHT_YUM_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP2_NO_BOUGHT_HEALTH_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP2_NO_BOUGHT_EPIC_SNACKS"), 99999999);
    set_stat_int(get_hash_key("MP2_CIGARETTES_BOUGHT") , 99999999);
    set_stat_int(get_hash_key("MP2_NUMBER_OF_ORANGE_BOUGHT"), 99999999);
    set_stat_int(get_hash_key("MP2_NUMBER_OF_BOURGE_BOUGHT"), 99999999);
	return 0;
}

int MaxFireworks0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_1_WHITE"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_2_WHITE"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_3_WHITE"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_4_WHITE"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_1_RED"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_2_RED"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_3_RED"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_4_RED"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_1_BLUE"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_2_BLUE"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_3_BLUE"), 999999);
    set_stat_int(get_hash_key("MP0_FIREWORK_TYPE_4_BLUE"), 999999);
	return 0;
}

int MaxFireworks1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_1_WHITE"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_2_WHITE"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_3_WHITE"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_4_WHITE"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_1_RED"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_2_RED"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_3_RED"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_4_RED"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_1_BLUE"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_2_BLUE"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_3_BLUE"), 999999);
    set_stat_int(get_hash_key("MP1_FIREWORK_TYPE_4_BLUE"), 999999);
	return 0;
}

int MaxFireworks2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_1_WHITE"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_2_WHITE"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_3_WHITE"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_4_WHITE"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_1_RED"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_2_RED"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_3_RED"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_4_RED"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_1_BLUE"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_2_BLUE"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_3_BLUE"), 999999);
    set_stat_int(get_hash_key("MP2_FIREWORK_TYPE_4_BLUE"), 999999);
	return 0;
}

int MaxArmour0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP0_CHAR_ARMOUR_1_COUNT"), 9999);
    set_stat_int(get_hash_key("MP0_CHAR_ARMOUR_2_COUNT"), 9999);
    set_stat_int(get_hash_key("MP0_CHAR_ARMOUR_3_COUNT"), 9999);
    set_stat_int(get_hash_key("MP0_CHAR_ARMOUR_4_COUNT"), 9999);
    set_stat_int(get_hash_key("MP0_CHAR_ARMOUR_5_COUNT"), 9999);
	return 0;
}

int MaxArmour1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP1_CHAR_ARMOUR_1_COUNT"), 9999);
    set_stat_int(get_hash_key("MP1_CHAR_ARMOUR_2_COUNT"), 9999);
    set_stat_int(get_hash_key("MP1_CHAR_ARMOUR_3_COUNT"), 9999);
    set_stat_int(get_hash_key("MP1_CHAR_ARMOUR_4_COUNT"), 9999);
    set_stat_int(get_hash_key("MP1_CHAR_ARMOUR_5_COUNT"), 9999);
	return 0;
}

int MaxArmour2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP2_CHAR_ARMOUR_1_COUNT"), 9999);
    set_stat_int(get_hash_key("MP2_CHAR_ARMOUR_2_COUNT"), 9999);
    set_stat_int(get_hash_key("MP2_CHAR_ARMOUR_3_COUNT"), 9999);
    set_stat_int(get_hash_key("MP2_CHAR_ARMOUR_4_COUNT"), 9999);
    set_stat_int(get_hash_key("MP2_CHAR_ARMOUR_5_COUNT"), 9999);
	return 0;
}

int HeistStuff0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE2"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE3"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE4"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE5"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE6"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE7"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE8"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE9"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE10"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE11"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_FM_PURCHASE12"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_1_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_2_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_3_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_4_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_5_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_6_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_7_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_8_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_9_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_10_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_11_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_KIT_12_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_races_won"), 100);
	set_stat_int(get_hash_key("MP0_number_turbo_starts_in_race"), 100);
	set_stat_int(get_hash_key("MP0_usjs_found"), 50);
	set_stat_int(get_hash_key("MP0_usjs_completed"), 50);
	set_stat_int(get_hash_key("MP0_awd_fmwinairrace"), 50);
	set_stat_int(get_hash_key("MP0_awd_fmwinsearace"), 50);
	set_stat_int(get_hash_key("MP0_awd_fmrallywonnav") , 50);
	set_stat_int(get_hash_key("MP0_awd_fmrallywondrive "), 500);
	set_stat_int(get_hash_key("MP0_awd_fm_races_fastest_lap"), 500);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_0_unlck"), -1);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_1_unlck"), -1);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_2_unlck"), -1);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_3_unlck"), -1);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_4_unlck"), -1);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_5_unlck"), -1);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_6_unlck"), -1);
	set_stat_int(get_hash_key("MP0_char_fm_carmod_7_unlck"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_ABILITY_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_ABILITY_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_ABILITY_3_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_1_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_2_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_3_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_4_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_5_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_6_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_7_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_8_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_PACKAGE_9_COLLECT"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_HEALTH_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_CHAR_FM_HEALTH_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP0_HOLDUPS_BITSET"), -1);
	return 0;
}

int HeistStuff1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE2"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE3"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE4"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE5"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE6"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE7"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE8"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE9"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE10"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE11"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_FM_PURCHASE12"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_1_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_2_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_3_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_4_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_5_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_6_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_7_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_8_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_9_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_10_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_11_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_KIT_12_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_races_won"), 100);
	set_stat_int(get_hash_key("MP1_number_turbo_starts_in_race"), 100);
	set_stat_int(get_hash_key("MP1_usjs_found"), 50);
	set_stat_int(get_hash_key("MP1_usjs_completed"), 50);
	set_stat_int(get_hash_key("MP1_awd_fmwinairrace"), 50);
	set_stat_int(get_hash_key("MP1_awd_fmwinsearace"), 50);
	set_stat_int(get_hash_key("MP1_awd_fmrallywonnav") , 50);
	set_stat_int(get_hash_key("MP1_awd_fmrallywondrive "), 500);
	set_stat_int(get_hash_key("MP1_awd_fm_races_fastest_lap"), 500);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_0_unlck"), -1);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_1_unlck"), -1);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_2_unlck"), -1);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_3_unlck"), -1);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_4_unlck"), -1);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_5_unlck"), -1);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_6_unlck"), -1);
	set_stat_int(get_hash_key("MP1_char_fm_carmod_7_unlck"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_VEHICLE_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_VEHICLE_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_ABILITY_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_ABILITY_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_ABILITY_3_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_1_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_2_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_3_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_4_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_5_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_6_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_7_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_8_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_PACKAGE_9_COLLECT"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_HEALTH_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_CHAR_FM_HEALTH_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP1_HOLDUPS_BITSET"), -1);
	return 0;
}

int HeistStuff2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE2"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE3"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE4"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE5"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE6"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE7"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE8"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE9"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE10"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE11"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_FM_PURCHASE12"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_1_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_2_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_3_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_4_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_5_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_6_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_7_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_8_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_9_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_10_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_11_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_KIT_12_FM_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_races_won"), 100);
	set_stat_int(get_hash_key("MP2_number_turbo_starts_in_race"), 100);
	set_stat_int(get_hash_key("MP2_usjs_found"), 50);
	set_stat_int(get_hash_key("MP2_usjs_completed"), 50);
	set_stat_int(get_hash_key("MP2_awd_fmwinairrace"), 50);
	set_stat_int(get_hash_key("MP2_awd_fmwinsearace"), 50);
	set_stat_int(get_hash_key("MP2_awd_fmrallywonnav") , 50);
	set_stat_int(get_hash_key("MP2_awd_fmrallywondrive "), 500);
	set_stat_int(get_hash_key("MP2_awd_fm_races_fastest_lap"), 500);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_0_unlck"), -1);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_1_unlck"), -1);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_2_unlck"), -1);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_3_unlck"), -1);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_4_unlck"), -1);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_5_unlck"), -1);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_6_unlck"), -1);
	set_stat_int(get_hash_key("MP2_char_fm_carmod_7_unlck"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_VEHICLE_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_VEHICLE_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_ABILITY_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_ABILITY_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_ABILITY_3_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_1_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_2_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_3_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_4_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_5_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_6_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_7_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_8_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_PACKAGE_9_COLLECT"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_HEALTH_1_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_CHAR_FM_HEALTH_2_UNLCK"), -1);
	set_stat_int(get_hash_key("MP2_HOLDUPS_BITSET"), -1);
	return 0;
}

int UnlockAllMP0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
set_stat_int(get_hash_key("MP0_SCRIPT_INCREASE_STAM"), 100);
		set_stat_int(get_hash_key("MP0_SCRIPT_INCREASE_STRN"), 100);
		set_stat_int(get_hash_key("MP0_SCRIPT_INCREASE_LUNG"), 100);
        set_stat_int(get_hash_key("MP0_SCRIPT_INCREASE_DRIV"), 100);
        set_stat_int(get_hash_key("MP0_SCRIPT_INCREASE_FLY"),  100);
        set_stat_int(get_hash_key("MP0_SCRIPT_INCREASE_SHO"),  100);
        set_stat_int(get_hash_key("MP0_SCRIPT_INCREASE_STL"),  100);
            // skills //
        set_stat_int(get_hash_key("MP0_RACES_WON"),  100);
		
		set_stat_int(get_hash_key("MP0_PISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CMBTPISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_APPISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_MICROSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_SMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CRBNRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ADVRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_HVYSNIPER_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_SNIPERRFL_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTSHTGN_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_PUMP_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_GRNLAUNCH_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_RPG_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_MINIGUNS_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CRBNRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ADVRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_HVYSNIPER_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_SNIPERRFL_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_MG_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CMBTMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_PISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CMBTPISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_APPISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_MICROSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_SMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CRBNRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ADVRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_HVYSNIPER_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_SNIPERRFL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTSHTGN_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_PUMP_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_GRNLAUNCH_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_RPG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_MINIGUNS_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ASLTRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CRBNRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_ADVRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_HVYSNIPER_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_SNIPERRFL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_MG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP0_CMBTMG_ENEMY_KILLS"),  600);

		set_stat_bool(get_hash_key("MP0_AWD_FMRACEWORLDRECHOLDER"),  1);
        set_stat_int(get_hash_key("MP0_AWD_ENEMYDRIVEBYKILLS"),  600);

            set_stat_int(get_hash_key("MP0_USJS_COMPLETED"),  50);
            set_stat_int(get_hash_key("MP0_USJS_FOUND"),  50);

            set_stat_bool(get_hash_key("MP0_AWD_FMWINALLRACEMODES"),  1);
            set_stat_bool(get_hash_key("MP0_AWD_FMWINEVERYGAMEMODE"),  1);
            set_stat_int(get_hash_key("MP0_DB_PLAYER_KILLS"), 1000); // drive by kills 
            set_stat_int(get_hash_key("MP0_KILLS_PLAYERS"), 1000);
            set_stat_int(get_hash_key("MP0_AWD_FMHORDWAVESSURVIVE"),  21);
            set_stat_int(get_hash_key("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25);
            set_stat_int(get_hash_key("MP0_AWD_FM_TDM_MVP"), 60);
            set_stat_int(get_hash_key("MP0_AWD_HOLD_UP_SHOPS"), 20);
            set_stat_int(get_hash_key("MP0_AWD_RACES_WON"), 101);
            set_stat_int(get_hash_key("MP0_AWD_NO_ARMWRESTLING_WINS"), 21);
            set_stat_bool(get_hash_key("MP0_AWD_FMATTGANGHQ"),  1);
            set_stat_int(get_hash_key("MP0_AWD_FMBBETWIN"), 50000);
            set_stat_int(get_hash_key("MP0_AWD_FM_DM_WINS"), 51);

            set_stat_bool(get_hash_key("MP0_AWD_FMFULLYMODDEDCAR"),  1);
            set_stat_int(get_hash_key("MP0_AWD_FM_DM_TOTALKILLS"),  500);
            set_stat_int(get_hash_key("MP0_MPPLY_DM_TOTAL_DEATHS"), 412);
            set_stat_int(get_hash_key("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36);
            set_stat_int(get_hash_key("MP0_PLAYER_HEADSHOTS"), 623);
            set_stat_int(get_hash_key("MP0_AWD_FM_DM_WINS"), 63);
            set_stat_int(get_hash_key("MP0_AWD_FM_TDM_WINS"), 13);
            set_stat_int(get_hash_key("MP0_AWD_FM_GTA_RACES_WON"), 12);
            set_stat_int(get_hash_key("MP0_AWD_FM_GOLF_WON"), 2);
            set_stat_int(get_hash_key("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2);
            set_stat_int(get_hash_key("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2);
            set_stat_int(get_hash_key("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2);
            set_stat_int(get_hash_key("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2);
            set_stat_int(get_hash_key("MP0_AWD_FM_TENNIS_WON"), 2);
            set_stat_int(get_hash_key("MP0_MPPLY_TENNIS_MATCHES_WON"), 2);
            set_stat_int(get_hash_key("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63);
            set_stat_int(get_hash_key("MP0_MPPLY_TOTAL_RACES_WON"), 101);
            set_stat_int(get_hash_key("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23);
            set_stat_int(get_hash_key("MP0_MPPLY_TOTAL_RACES_LOST"), 36);
            set_stat_int(get_hash_key("MP0_AWD_25_KILLS_STICKYBOMBS"), 50);
            set_stat_int(get_hash_key("MP0_AWD_50_KILLS_GRENADES"), 50);
            set_stat_int(get_hash_key("MP0_GRENADE_ENEMY_KILLS"), 50);
            set_stat_int(get_hash_key("MP0_AWD_20_KILLS_MELEE"), 50);
            //set_stat_int(get_hash_key(ConvertString(("NO_MASKS_UNLOCK"), 25);
            //set_stat_int(get_hash_key(ConvertString(("NO_TATTOOS_UNLOCK"), 61);

            set_stat_bool(get_hash_key("MP0_AWD_FMMOSTKILLSSURVIVE"),  1);

           // set_stat_int(get_hash_key(ConvertString(("AWD_ENEMYDRIVEBYKILLS"), 10);

            set_stat_int(get_hash_key("MP0_AWD_FMRALLYWONDRIVE"), 2);
            set_stat_int(get_hash_key("MP0_AWD_FMWINSEARACE"), 2);
            set_stat_int(get_hash_key("MP0_AWD_FMWINAIRRACE"), 2);
            set_stat_int(get_hash_key("MP0_MPPLY_TIMES_RACE_BEST_LAP"), 101);
            set_stat_int(get_hash_key("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 100);
            set_stat_int(get_hash_key("MP0_AWD_FM_RACES_FASTEST_LAP"), 101);
            set_stat_int(get_hash_key("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 105);
           // set_stat_int(get_hash_key("MP0_CASH_GIFT_CREDITED"), 999);
            set_stat_int(get_hash_key("MP0_MPPLY_RACE_CHEAT_START"), 130);
            set_stat_int(get_hash_key("MP0_MPPLY_RACE_CHEAT_END"), 119);
            set_stat_int(get_hash_key("MP0_MPPLY_RACE_CHEAT_QUIT"), 11);
            set_stat_int(get_hash_key("MP0_MPPLY_DM_CHEAT_START"), 140);
            set_stat_int(get_hash_key("MP0_MPPLY_DM_CHEAT_END"), 115);
            set_stat_int(get_hash_key("MP0_MPPLY_DM_CHEAT_QUIT"), 25);
            set_stat_int(get_hash_key("MP0_MPPLY_MC_CHEAT_START"), 113);
            set_stat_int(get_hash_key("MP0_MPPLY_MC_CHEAT_END"), 97);
            set_stat_int(get_hash_key("MP0_MPPLY_MC_CHEAT_QUIT"), 16);
            set_stat_int(get_hash_key("MP0_MPPLY_OVERALL_CHEAT"), 0);

            set_stat_int(get_hash_key("MP0_LAP_DANCED_BOUGHT"), 50);

            set_stat_int(get_hash_key("MP0_AWD_FMKILLBOUNTY"), 50);
            set_stat_bool(get_hash_key("MP0_AWD_FMKILL3ANDWINGTARACE"),  1);
            set_stat_int(get_hash_key("MP0_AWD_FMREVENGEKILLSDM"), 60);
            set_stat_int(get_hash_key("MP0_AWD_SECURITY_CARS_ROBBED"), 40);
            set_stat_bool(get_hash_key("MP0_AWD_FMPICKUPDLCCRATE1ST"),  1);
return 0;
}
int UnlockAllMP1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
set_stat_int(get_hash_key("MP1_SCRIPT_INCREASE_STAM"), 100);
		set_stat_int(get_hash_key("MP1_SCRIPT_INCREASE_STRN"), 100);
		set_stat_int(get_hash_key("MP1_SCRIPT_INCREASE_LUNG"), 100);
        set_stat_int(get_hash_key("MP1_SCRIPT_INCREASE_DRIV"), 100);
        set_stat_int(get_hash_key("MP1_SCRIPT_INCREASE_FLY"),  100);
        set_stat_int(get_hash_key("MP1_SCRIPT_INCREASE_SHO"),  100);
        set_stat_int(get_hash_key("MP1_SCRIPT_INCREASE_STL"),  100);
            // skills //
        set_stat_int(get_hash_key("MP1_RACES_WON"),  100);
		
		set_stat_int(get_hash_key("MP1_PISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CMBTPISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_APPISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_MICROSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_SMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CRBNRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ADVRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_HVYSNIPER_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_SNIPERRFL_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTSHTGN_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_PUMP_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_GRNLAUNCH_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_RPG_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_MINIGUNS_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CRBNRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ADVRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_HVYSNIPER_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_SNIPERRFL_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_MG_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CMBTMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_PISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CMBTPISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_APPISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_MICROSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_SMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CRBNRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ADVRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_HVYSNIPER_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_SNIPERRFL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTSHTGN_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_PUMP_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_GRNLAUNCH_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_RPG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_MINIGUNS_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ASLTRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CRBNRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_ADVRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_HVYSNIPER_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_SNIPERRFL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_MG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP1_CMBTMG_ENEMY_KILLS"),  600);

		set_stat_bool(get_hash_key("MP1_AWD_FMRACEWORLDRECHOLDER"),  1);
        set_stat_int(get_hash_key("MP1_AWD_ENEMYDRIVEBYKILLS"),  600);

            set_stat_int(get_hash_key("MP1_USJS_COMPLETED"),  50);
            set_stat_int(get_hash_key("MP1_USJS_FOUND"),  50);

            set_stat_bool(get_hash_key("MP1_AWD_FMWINALLRACEMODES"),  1);
            set_stat_bool(get_hash_key("MP1_AWD_FMWINEVERYGAMEMODE"),  1);
            set_stat_int(get_hash_key("MP1_DB_PLAYER_KILLS"), 1000); // drive by kills 
            set_stat_int(get_hash_key("MP1_KILLS_PLAYERS"), 1000);
            set_stat_int(get_hash_key("MP1_AWD_FMHORDWAVESSURVIVE"),  21);
            set_stat_int(get_hash_key("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25);
            set_stat_int(get_hash_key("MP1_AWD_FM_TDM_MVP"), 60);
            set_stat_int(get_hash_key("MP1_AWD_HOLD_UP_SHOPS"), 20);
            set_stat_int(get_hash_key("MP1_AWD_RACES_WON"), 101);
            set_stat_int(get_hash_key("MP1_AWD_NO_ARMWRESTLING_WINS"), 21);
            set_stat_bool(get_hash_key("MP1_AWD_FMATTGANGHQ"),  1);
            set_stat_int(get_hash_key("MP1_AWD_FMBBETWIN"), 50000);
            set_stat_int(get_hash_key("MP1_AWD_FM_DM_WINS"), 51);

            set_stat_bool(get_hash_key("MP1_AWD_FMFULLYMODDEDCAR"),  1);
            set_stat_int(get_hash_key("MP1_AWD_FM_DM_TOTALKILLS"),  500);
            set_stat_int(get_hash_key("MP1_MPPLY_DM_TOTAL_DEATHS"), 412);
            set_stat_int(get_hash_key("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36);
            set_stat_int(get_hash_key("MP1_PLAYER_HEADSHOTS"), 623);
            set_stat_int(get_hash_key("MP1_AWD_FM_DM_WINS"), 63);
            set_stat_int(get_hash_key("MP1_AWD_FM_TDM_WINS"), 13);
            set_stat_int(get_hash_key("MP1_AWD_FM_GTA_RACES_WON"), 12);
            set_stat_int(get_hash_key("MP1_AWD_FM_GOLF_WON"), 2);
            set_stat_int(get_hash_key("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2);
            set_stat_int(get_hash_key("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2);
            set_stat_int(get_hash_key("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2);
            set_stat_int(get_hash_key("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2);
            set_stat_int(get_hash_key("MP1_AWD_FM_TENNIS_WON"), 2);
            set_stat_int(get_hash_key("MP1_MPPLY_TENNIS_MATCHES_WON"), 2);
            set_stat_int(get_hash_key("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63);
            set_stat_int(get_hash_key("MP1_MPPLY_TOTAL_RACES_WON"), 101);
            set_stat_int(get_hash_key("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23);
            set_stat_int(get_hash_key("MP1_MPPLY_TOTAL_RACES_LOST"), 36);
            set_stat_int(get_hash_key("MP1_AWD_25_KILLS_STICKYBOMBS"), 50);
            set_stat_int(get_hash_key("MP1_AWD_50_KILLS_GRENADES"), 50);
            set_stat_int(get_hash_key("MP1_GRENADE_ENEMY_KILLS"), 50);
            set_stat_int(get_hash_key("MP1_AWD_20_KILLS_MELEE"), 50);
            //set_stat_int(get_hash_key(ConvertString(("NO_MASKS_UNLOCK"), 25);
            //set_stat_int(get_hash_key(ConvertString(("NO_TATTOOS_UNLOCK"), 61);

            set_stat_bool(get_hash_key("MP1_AWD_FMMOSTKILLSSURVIVE"),  1);

           // set_stat_int(get_hash_key(ConvertString(("AWD_ENEMYDRIVEBYKILLS"), 10);

            set_stat_int(get_hash_key("MP1_AWD_FMRALLYWONDRIVE"), 2);
            set_stat_int(get_hash_key("MP1_AWD_FMWINSEARACE"), 2);
            set_stat_int(get_hash_key("MP1_AWD_FMWINAIRRACE"), 2);
            set_stat_int(get_hash_key("MP1_MPPLY_TIMES_RACE_BEST_LAP"), 101);
            set_stat_int(get_hash_key("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 100);
            set_stat_int(get_hash_key("MP1_AWD_FM_RACES_FASTEST_LAP"), 101);
            set_stat_int(get_hash_key("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 105);
           // set_stat_int(get_hash_key("MP1_CASH_GIFT_CREDITED"), 999);
            set_stat_int(get_hash_key("MP1_MPPLY_RACE_CHEAT_START"), 130);
            set_stat_int(get_hash_key("MP1_MPPLY_RACE_CHEAT_END"), 119);
            set_stat_int(get_hash_key("MP1_MPPLY_RACE_CHEAT_QUIT"), 11);
            set_stat_int(get_hash_key("MP1_MPPLY_DM_CHEAT_START"), 140);
            set_stat_int(get_hash_key("MP1_MPPLY_DM_CHEAT_END"), 115);
            set_stat_int(get_hash_key("MP1_MPPLY_DM_CHEAT_QUIT"), 25);
            set_stat_int(get_hash_key("MP1_MPPLY_MC_CHEAT_START"), 113);
            set_stat_int(get_hash_key("MP1_MPPLY_MC_CHEAT_END"), 97);
            set_stat_int(get_hash_key("MP1_MPPLY_MC_CHEAT_QUIT"), 16);
            set_stat_int(get_hash_key("MP1_MPPLY_OVERALL_CHEAT"), 0);

            set_stat_int(get_hash_key("MP1_LAP_DANCED_BOUGHT"), 50);

            set_stat_int(get_hash_key("MP1_AWD_FMKILLBOUNTY"), 50);
            set_stat_bool(get_hash_key("MP1_AWD_FMKILL3ANDWINGTARACE"),  1);
            set_stat_int(get_hash_key("MP1_AWD_FMREVENGEKILLSDM"), 60);
            set_stat_int(get_hash_key("MP1_AWD_SECURITY_CARS_ROBBED"), 40);
            set_stat_bool(get_hash_key("MP1_AWD_FMPICKUPDLCCRATE1ST"),  1);
return 0;
}
int UnlockAllMP2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
set_stat_int(get_hash_key("MP2_SCRIPT_INCREASE_STAM"), 100);
		set_stat_int(get_hash_key("MP2_SCRIPT_INCREASE_STRN"), 100);
		set_stat_int(get_hash_key("MP2_SCRIPT_INCREASE_LUNG"), 100);
        set_stat_int(get_hash_key("MP2_SCRIPT_INCREASE_DRIV"), 100);
        set_stat_int(get_hash_key("MP2_SCRIPT_INCREASE_FLY"),  100);
        set_stat_int(get_hash_key("MP2_SCRIPT_INCREASE_SHO"),  100);
        set_stat_int(get_hash_key("MP2_SCRIPT_INCREASE_STL"),  100);
            // skills //
        set_stat_int(get_hash_key("MP2_RACES_WON"),  100);
		
		set_stat_int(get_hash_key("MP2_PISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CMBTPISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_APPISTOL_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_MICROSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_SMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CRBNRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ADVRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_HVYSNIPER_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_SNIPERRFL_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTSHTGN_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_PUMP_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_GRNLAUNCH_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_RPG_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_MINIGUNS_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTSMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CRBNRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ADVRIFLE_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_HVYSNIPER_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_SNIPERRFL_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_MG_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CMBTMG_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_PISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CMBTPISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_APPISTOL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_MICROSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_SMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CRBNRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ADVRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_HVYSNIPER_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_SNIPERRFL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTSHTGN_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_PUMP_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_GRNLAUNCH_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_RPG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_MINIGUNS_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTSMG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ASLTRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CRBNRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_ADVRIFLE_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_HVYSNIPER_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_SNIPERRFL_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_MG_ENEMY_KILLS"),  600);
        set_stat_int(get_hash_key("MP2_CMBTMG_ENEMY_KILLS"),  600);

		set_stat_bool(get_hash_key("MP2_AWD_FMRACEWORLDRECHOLDER"),  1);
        set_stat_int(get_hash_key("MP2_AWD_ENEMYDRIVEBYKILLS"),  600);

            set_stat_int(get_hash_key("MP2_USJS_COMPLETED"),  50);
            set_stat_int(get_hash_key("MP2_USJS_FOUND"),  50);

            set_stat_bool(get_hash_key("MP2_AWD_FMWINALLRACEMODES"),  1);
            set_stat_bool(get_hash_key("MP2_AWD_FMWINEVERYGAMEMODE"),  1);
            set_stat_int(get_hash_key("MP2_DB_PLAYER_KILLS"), 1000); // drive by kills 
            set_stat_int(get_hash_key("MP2_KILLS_PLAYERS"), 1000);
            set_stat_int(get_hash_key("MP2_AWD_FMHORDWAVESSURVIVE"),  21);
            set_stat_int(get_hash_key("MP2_AWD_CAR_BOMBS_ENEMY_KILLS"), 25);
            set_stat_int(get_hash_key("MP2_AWD_FM_TDM_MVP"), 60);
            set_stat_int(get_hash_key("MP2_AWD_HOLD_UP_SHOPS"), 20);
            set_stat_int(get_hash_key("MP2_AWD_RACES_WON"), 101);
            set_stat_int(get_hash_key("MP2_AWD_NO_ARMWRESTLING_WINS"), 21);
            set_stat_bool(get_hash_key("MP2_AWD_FMATTGANGHQ"),  1);
            set_stat_int(get_hash_key("MP2_AWD_FMBBETWIN"), 50000);
            set_stat_int(get_hash_key("MP2_AWD_FM_DM_WINS"), 51);

            set_stat_bool(get_hash_key("MP2_AWD_FMFULLYMODDEDCAR"),  1);
            set_stat_int(get_hash_key("MP2_AWD_FM_DM_TOTALKILLS"),  500);
            set_stat_int(get_hash_key("MP2_MPPLY_DM_TOTAL_DEATHS"), 412);
            set_stat_int(get_hash_key("MP2_MPPLY_TIMES_FINISH_DM_TOP_3"), 36);
            set_stat_int(get_hash_key("MP2_PLAYER_HEADSHOTS"), 623);
            set_stat_int(get_hash_key("MP2_AWD_FM_DM_WINS"), 63);
            set_stat_int(get_hash_key("MP2_AWD_FM_TDM_WINS"), 13);
            set_stat_int(get_hash_key("MP2_AWD_FM_GTA_RACES_WON"), 12);
            set_stat_int(get_hash_key("MP2_AWD_FM_GOLF_WON"), 2);
            set_stat_int(get_hash_key("MP2_AWD_FM_SHOOTRANG_TG_WON"), 2);
            set_stat_int(get_hash_key("MP2_AWD_FM_SHOOTRANG_RT_WON"), 2);
            set_stat_int(get_hash_key("MP2_AWD_FM_SHOOTRANG_CT_WON"), 2);
            set_stat_int(get_hash_key("MP2_AWD_FM_SHOOTRANG_GRAN_WON"), 2);
            set_stat_int(get_hash_key("MP2_AWD_FM_TENNIS_WON"), 2);
            set_stat_int(get_hash_key("MP2_MPPLY_TENNIS_MATCHES_WON"), 2);
            set_stat_int(get_hash_key("MP2_MPPLY_TOTAL_TDEATHMATCH_WON"), 63);
            set_stat_int(get_hash_key("MP2_MPPLY_TOTAL_RACES_WON"), 101);
            set_stat_int(get_hash_key("MP2_MPPLY_TOTAL_DEATHMATCH_LOST"), 23);
            set_stat_int(get_hash_key("MP2_MPPLY_TOTAL_RACES_LOST"), 36);
            set_stat_int(get_hash_key("MP2_AWD_25_KILLS_STICKYBOMBS"), 50);
            set_stat_int(get_hash_key("MP2_AWD_50_KILLS_GRENADES"), 50);
            set_stat_int(get_hash_key("MP2_GRENADE_ENEMY_KILLS"), 50);
            set_stat_int(get_hash_key("MP2_AWD_20_KILLS_MELEE"), 50);
            //set_stat_int(get_hash_key(ConvertString(("NO_MASKS_UNLOCK"), 25);
            //set_stat_int(get_hash_key(ConvertString(("NO_TATTOOS_UNLOCK"), 61);

            set_stat_bool(get_hash_key("MP2_AWD_FMMOSTKILLSSURVIVE"),  1);

           // set_stat_int(get_hash_key(ConvertString(("AWD_ENEMYDRIVEBYKILLS"), 10);

            set_stat_int(get_hash_key("MP2_AWD_FMRALLYWONDRIVE"), 2);
            set_stat_int(get_hash_key("MP2_AWD_FMWINSEARACE"), 2);
            set_stat_int(get_hash_key("MP2_AWD_FMWINAIRRACE"), 2);
            set_stat_int(get_hash_key("MP2_MPPLY_TIMES_RACE_BEST_LAP"), 101);
            set_stat_int(get_hash_key("MP2_NUMBER_TURBO_STARTS_IN_RACE"), 100);
            set_stat_int(get_hash_key("MP2_AWD_FM_RACES_FASTEST_LAP"), 101);
            set_stat_int(get_hash_key("MP2_NUMBER_SLIPSTREAMS_IN_RACE"), 105);
           // set_stat_int(get_hash_key("MP2_CASH_GIFT_CREDITED"), 999);
            set_stat_int(get_hash_key("MP2_MPPLY_RACE_CHEAT_START"), 130);
            set_stat_int(get_hash_key("MP2_MPPLY_RACE_CHEAT_END"), 119);
            set_stat_int(get_hash_key("MP2_MPPLY_RACE_CHEAT_QUIT"), 11);
            set_stat_int(get_hash_key("MP2_MPPLY_DM_CHEAT_START"), 140);
            set_stat_int(get_hash_key("MP2_MPPLY_DM_CHEAT_END"), 115);
            set_stat_int(get_hash_key("MP2_MPPLY_DM_CHEAT_QUIT"), 25);
            set_stat_int(get_hash_key("MP2_MPPLY_MC_CHEAT_START"), 113);
            set_stat_int(get_hash_key("MP2_MPPLY_MC_CHEAT_END"), 97);
            set_stat_int(get_hash_key("MP2_MPPLY_MC_CHEAT_QUIT"), 16);
            set_stat_int(get_hash_key("MP2_MPPLY_OVERALL_CHEAT"), 0);

            set_stat_int(get_hash_key("MP2_LAP_DANCED_BOUGHT"), 50);

            set_stat_int(get_hash_key("MP2_AWD_FMKILLBOUNTY"), 50);
            set_stat_bool(get_hash_key("MP2_AWD_FMKILL3ANDWINGTARACE"),  1);
            set_stat_int(get_hash_key("MP2_AWD_FMREVENGEKILLSDM"), 60);
            set_stat_int(get_hash_key("MP2_AWD_SECURITY_CARS_ROBBED"), 40);
            set_stat_bool(get_hash_key("MP2_AWD_FMPICKUPDLCCRATE1ST"),  1);
return 0;
}
#endif

float speed_loc = 0.1;
bool speed_req = false;
bool speedo_ready = false;
bool analog_loop = false;
int Analog(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!analog_loop) {
	analog_loop = true;
	speed_loc = 0.09;
	speed_req = true;
	if (gauge == 0)
	gauge = 4;
	}
	else if (analog_loop) {
	analog_loop = false;
	}
	return 0;
}
bool dark = false;
bool damaged = false;
int idamage;
void analog_speedo() 
{
	if (!is_ped_on_foot(PlayerPedId()))
	{
	int ispeed;
	int car = GetCarCharIsIn(PlayerPedId(), 0);//GET_CAR_CHAR_IS_USING(GetPlayerPed(), &veh_speed);
    float speed = get_entity_speed(car);
	float damage = get_vehicle_engine_health(car);
	idamage = (int) damage; // float to int
	if (idamage < 750)
	{
	damaged = true;
	}
	else
	{
	damaged = false;
	}
	if (get_clock_hours() > 19 || (get_clock_hours() < 7))
	{
	dark = true;
	}
	else if (get_clock_hours() < 7)
	{
	dark = true;
	}
	else 
	{
	dark = false;
	}
	if (gauge == 1)
	{
    speed = speed * 4.30; 
	ispeed = (int) speed; // float to int
	if (dark)
	{
	draw_sprite("mpmissmarkers256", "sea_race_icon", 0.12f, 0.2f, 0.28f, 0.41f, 0.0f, 255, 255, 255, 225);
	if (speed > 293)
	{
	//draw_sprite("mpmissmarkers256", "foot_race_icon", 0.12f, 0.2f, 0.2f, 0.18f, 294, 255, 255, 255, 255);
	draw_sprite("mpmissmarkers256", "foot_race_icon", 0.12f, 0.2f, 0.28f, 0.41f, 210, 255, 255, 255, 225);
	}
	else
	{
	if (speed < 80)
	{
	draw_sprite("mpmissmarkers256", "foot_race_icon", 0.12f, 0.2f, 0.28f, 0.41f, speed - 88, 255, 255, 255, 225);
	}
	else 
	{
	draw_sprite("mpmissmarkers256", "foot_race_icon", 0.12f, 0.2f, 0.28f, 0.41f, speed - 88, 255, 255, 255, 225);
	}
	}
	}
	else if (!dark)
	{
	draw_sprite("mpmissmarkers256", "last_team_standing_icon", 0.12f, 0.2f, 0.28f, 0.41f, 0.0f, 255, 255, 255, 225);
	if (speed > 293)
	{
	draw_sprite("mpmissmarkers256", "survival_icon", 0.12f, 0.2f, 0.28f, 0.41f, 210, 255, 255, 255, 225);
	}
	else
	{
	if (speed < 80)
	{
	draw_sprite("mpmissmarkers256", "survival_icon", 0.12f, 0.2f, 0.28f, 0.41f, speed - 88, 255, 255, 255, 225);
	}
	else
	{
	draw_sprite("mpmissmarkers256", "survival_icon", 0.12f, 0.2f, 0.28f, 0.41f, speed - 88, 255, 255, 255, 225);
	}
	}
	}
	}
	else if (gauge == 2)
	{

		if (!has_streamed_texture_dict_loaded("policecomputer"))
            {
                request_streamed_texture_dict("policecomputer", 0);
            }

		if (!has_streamed_texture_dict_loaded("hudold"))
            {
                request_streamed_texture_dict("hudold", 0);
            }

	speed = speed * 1.55; 
	ispeed = (int) speed; // float to int
	PrintToScreenNum(ispeed, speed_loc, 0.26000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 5);
	if (ispeed < 120)
	{
	PrintToScreenNum(ispeed, speed_loc, 0.26000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 5);
	}
	if (ispeed > 120)
	{
	PrintToScreenNum(ispeed, speed_loc, 0.26000000, 255, 255, 0, 255, 0.80000000, 0.80000000, 0, 5);
	}
	if (ispeed > 180)
	{
	PrintToScreenNum(ispeed, speed_loc, 0.26000000, 255, 165, 0, 255, 0.80000000, 0.80000000, 0, 5);
	}
	if (ispeed > 240)
	{
	PrintToScreenNum(ispeed, speed_loc, 0.26000000, 255, 0, 0, 255, 0.80000000, 0.80000000, 0, 5);
	}
	draw_sprite("policecomputer", "badge", 0.12f, 0.2f, 0.2f, 0.3f, 0.0f, 255, 255, 255, 225);
	if (speed > 293)
	{
	draw_sprite("hudold", "radarringback", 0.12f, 0.2f, 0.2f, 0.3f, 294, 255, 255, 255, 255);
	}
	else
	{
	draw_sprite("hudold", "radarringback", 0.12f, 0.2f, 0.2f, 0.3f, speed, 255, 255, 255, 255);
	}
	}
	else if (gauge == 3)
	{
	speed = speed * 4.55; 
	ispeed = (int) speed; // float to int
	PrintToScreenNum(ispeed, 0.1, 0.27000000, 0, 77, 33, 225, 0.50000000, 0.50000000, 0, 5);
	draw_sprite("mpmissmarkers256", "basejump_icon", 0.12f, 0.2f, 0.2f, 0.3f, 0.0f, 255, 255, 255, 225);
	if (speed > 293)
	{
	draw_sprite("mpmissmarkers256", "deathmatch_marker_256", 0.12f, 0.2f, 0.2f, 0.3f, 294 - 89, 255, 255, 255, 255);
	}
	else
	{
	draw_sprite("mpmissmarkers256", "deathmatch_marker_256", 0.12f, 0.2f, 0.2f, 0.3f, speed - 89, 255, 255, 255, 255);
	}
	}
	else if (gauge == 4)
	{
	speed = speed * 5.45; 
	ispeed = (int) speed; // float to int
	if (!dark) // day damage gauge
	{
	draw_sprite("mpmissmarkers256", "vehicledeathmatch_icon", 0.12f, 0.2f, 0.35f, 0.45f, 0.0f, 255, 255, 255, 225);
	if (damaged)
	draw_sprite("mpmissmarkers256", "gangattack_icon", 0.12f, 0.2f, 0.35f, 0.45f, 0.0f, 255, 255, 255, 225);
	if (speed > 250)
	{
	draw_sprite("mpmissmarkers256", "darts_icon", 0.12f, 0.2f, 0.35f, 0.45f, 251 - 65, 255, 255, 255, 255);
	}
	else
	{
	draw_sprite("mpmissmarkers256", "darts_icon", 0.12f, 0.2f, 0.35f, 0.45f, speed - 65, 255, 255, 255, 255);
	}
	}
	else if (dark) // night time
	{
	draw_sprite("mpmissmarkers256", "bike_race_icon", 0.12f, 0.2f, 0.35f, 0.45f, 0.0f, 255, 255, 255, 225);
	if (damaged)
	draw_sprite("mpmissmarkers256", "gangattack_icon", 0.12f, 0.2f, 0.35f, 0.45f, 0.0f, 255, 255, 255, 225);
	if (speed > 250)
	{
	draw_sprite("mpmissmarkers256", "corona_point", 0.12f, 0.2f, 0.35f, 0.45f, 251 - 65, 255, 255, 255, 255);
	}
	else
	{
	draw_sprite("mpmissmarkers256", "corona_point", 0.12f, 0.2f, 0.35f, 0.45f, speed - 65, 255, 255, 255, 255);
	}
	}
	}
	}
}
#endif
void cam_loop()
{
	if (cam_check)
	{
	if (is_ped_on_foot(PlayerPedId()))
	{
	        float lineThickness = 0.001f;
            float lineLength = 0.02f;
            draw_rect(0.5f, 0.5f, lineLength, lineThickness, 255, 0, 0, 255);
            draw_rect(0.5f, 0.5f, lineThickness, lineLength + 0.01f, 255, 0, 0, 255);
	}
	set_cam_active(cam, true);
	get_gameplay_cam_rot(2, rot);
	set_cam_rot(cam, rot);
	}
}

void Seccam_loop()
{
	if (Seccam_check)
	{
	set_cam_active(Seccam1, true);
	get_gameplay_cam_rot(2, SecCam1rot);
	set_cam_rot(Seccam1, SecCam1rot);
	}
}

void Seccam2_loop()
{
	if (Seccam2_check)
	{
	set_cam_active(Seccam2, true);
	get_gameplay_cam_rot(2, SecCam2rot);
	set_cam_rot(Seccam2, SecCam2rot);
	}
}

/*void ufoloop() {
rock
}*/

/*bool bUfo;
void ufomode_1_loop()
{
	if ( (is_control_pressed( 2, 176 ) && is_control_just_pressed( 2, 182 )) )
	{
		bUfo = !bUfo;
		set_ped_stealth_movement( PlayerPedId(), 0, 0 );
		ShowMessageOnScreen( "Fly mod %s.", bUfo ? "on", "off" );
		if ( ! (bUfo ) )
		{
			//freeze_your_car_or_player( false )
			int Handle = are_you_in_veh_if_so_get_handle();
			if ( !Handle )
				Handle = PlayerPedId();
			apply_force_to_entity( Handle, 1, 0.0f, 0.0f, -0.1f, 0.0f, 0.0f, 0.0f, 0, 1, 0, 0, 0, 1 );
		}
	}
	if ( bUfo )
		ufomode_1();
}



void ufomode_1()
{
	int Handle = are_you_in_veh_if_so_get_handle();
	bool isInVeh = Handle != 0;
	if ( !isInVeh )
		Handle = PlayerPedId();
	float var_1 = is_control_pressed( 2, 194 ) ? 4.0f : 1.0f,
		z = get_gameplay_cam_rot( 2 )[2],//z
		temp;

	set_entity_heading( Handle, z );
	set_gameplay_cam_relative_heading( 0.0f );
	temp = get_gameplay_cam_relative_pitch() + 3.0f ;

	if ( isInVeh )// unsure :/
		temp += 4.0f;

	set_gameplay_cam_relative_pitch( temp, 1.0f );
	freeze_entity_position( Handle, 1 );

	if (!((((get_control_normal( 2, 181 ) == 0.0f && get_control_normal( 2, 180 )) == 0.0f &&
		get_control_normal( 2, 186 )) == 0.0f && get_control_normal( 2, 185 ) == 0.0f)))
	{
		float var_3 = get_control_normal( 2, 186 ) * -1.0f * var_1,
			var_4 = get_control_normal( 2, 180 ) * -1.0f * var_1;

		var_4 = get_control_normal( 2, 181 ) * var_1 + var_4;

		set_entity_coords_no_offset( Handle, get_offset_from_entity_in_world_coords( Handle, get_control_normal( 2, 185 ) * var_1, var_3, var_4 ), 0, 0, 0 );
	}
}*/

bool xmas = false;
int ToggleXmas(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	int pointer = *(int *)(Var_Pointer + 4);
	pointer += (4605 * 4);
	xmas ^= true;//Toggle xmas
	if (xmas) {
	*(int *)(pointer + 0x20) = 1;
	*(int *)pointer = 1;
	}
	else if (!xmas) {
	*(int *)(pointer + 0x20) = 0;
	*(int *)pointer = 0;
	}
	ShowMessageOnScreen("~g~ XMAS %s", xmas ? "Activated" : "Disabled");
	return 0;
}//

int FWLimit(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int pointer = *(int *)(Var_Pointer + 4);
	pointer += (5878 * 4);
	*(int *)pointer = 999999999;
	ShowMessageOnScreen("Fireworks limit removed!");
return 0;
}

bool nyloaded = false;
int LoadNY(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	nyloaded = true;
	ShowMessageOnScreen("North Yankton Loaded (Only you can see this)!");
return 0;
}


bool fan_garage = false;
bool fan_delete = false;
bool garagefun = false;
int GarageFan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!fan_garage) {
    objectspawn = true;
	model = 1952396163;
	garagefun = true;
	fan_garage = true;
	}
	else if (fan_garage) {
	fan_delete = true;
	fan_garage = false;
	}
	ShowMessageOnScreen("~g~ Garage Troll %s", fan_garage ? "Activated" : "Disabled");

	return 0;
}//

bool bounty = false;
int ToggleBounty(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int value = -2147000;
	int pointer = *(int *)(Var_Pointer + 4);
	pointer += (143 * 4);
	bounty ^= true;//Toggle bounty
	if(bounty) {
		*(int *)pointer = value;
	}
	else {
		*(int *)pointer = 1;
	}
	ShowMessageOnScreen("~g~ Massive Bounty %s", bounty ? "Activated" : "Disabled");

	return 0;
}//

int SpawnBodyParts(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -1268580434; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Body parts spawned!");
	return 0;
}//

int SpawnEgg(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 1803116220; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Alien egg spawned!");
	return 0;
}//

int SpawnShit(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -2071359746; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Big shit spawned!");
	return 0;
}//

int SpawnAsteroid(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -543669801; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Big asteroid spawned!");
	return 0;
}//

int SpawnUfo(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 0xB467C540; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Big Ufo spawned!");
	return 0;
}//

int SpawnFerris(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -1003748966; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Ferris Wheel spawned!");
	return 0;
}//

int SpawnGuardBuilding(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -105439435; // Guard Building
	//model = -1157901789; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Guard Building spawned!");
	return 0;
}//

int SpawnGuardBuilding2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	objectspawn = true;
	normalspawn = true;
	model = 260517631;
	
	ShowMessageOnScreen("~g~ Guard Building 2 spawned!");
	return 0;
}//

int TestCage2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	objectspawn = true;
	normalspawn = true;
	model = 2063962179; // prop_rub_cage01a
	
	ShowMessageOnScreen("~g~ Test Cage 2 spawned!");
	return 0;
}//

int TestCage3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	objectspawn = true;
	normalspawn = true;
	model = 1391864871; // sc1_10_baseball_cage
	
	ShowMessageOnScreen("~g~ Test Cage 3 spawned!");
	return 0;
}//

int TestCage4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	
	objectspawn = true;
	normalspawn = true;
	model = 2141598978; // po1_04_cage3
	
	ShowMessageOnScreen("~g~ Test Cage 4 spawned!");
	return 0;
}//

int SpawnBankVaultGateDoor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -1508355822; // Bank Vault Gate Door
	//model = -1157901789; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Bank Vault Gate Door spawned!");
	return 0;
}////v_54_hall_mesh_cage

int SpawnWindmill(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 1952396163; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Windmill spawned!");
	return 0;
}//

int BarrierS(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 868148414; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Short Barrier spawned!");
	return 0;
}//

int BarrierL(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 1603241576; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Long Barrier spawned!");
	return 0;
}//

int SpawnElectrical(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 1870961552; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Electric Shock spawned!");
	return 0;
}//

int WBarrier(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 24969275; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Wooden Barrier spawned!");
	return 0;
}//

int AWBarrier(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 1867879106; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Arrow Wooden Barrier spawned!");
	return 0;
}//

int MBarrier(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = 54588191; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Metal Barrier spawned!");
	return 0;
}//

int RoadCone(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -534360227; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Road Cone spawned!");
	return 0;
}//

int SpawnContainer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	objectspawn = true;
	normalspawn = true;
	model = -629735826; // spunk ramp 0xBF8918DE // UFO 0xB467C540
	ShowMessageOnScreen("~g~ Container Spawned!");
	return 0;
}//
bool ObjMoveUp = false;
int MoveUp(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // working
	if(!ObjMoveUp){
		ObjMoveUp = true;
	}
	else if(ObjMoveUp){
		ObjMoveUp = false;
	}
	return 0;
}

void MoveUpLoop(){
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordz = Pos[2];
	if(ObjMoveUp) objectcoordz += 0.1;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, Pos[0], Pos[1], objectcoordz, 1, 0, 0, 1);
	}
}

int MoveBlockadeUp(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // working
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordz = Pos[2];
	objectcoordz += 1.0;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, Pos[0], Pos[1], objectcoordz, 1, 0, 0, 1);
	ShowMessageOnScreen("~g~ Moved Blockade Up");
	return 0;
}
}

bool ObjMoveDown = false;
int MoveDown(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // working
	if(!ObjMoveDown){
		ObjMoveDown = true;
	}
	else if(ObjMoveDown){
		ObjMoveDown = false;
	}
	return 0;
}

void MoveDownLoop(){
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordz = Pos[2];
	if(ObjMoveDown) objectcoordz -= 0.1;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, Pos[0], Pos[1], objectcoordz, 1, 0, 0, 1);
	}
}

int MoveBlockadeDown(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // working
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordz = Pos[2];
	objectcoordz -= 1.0;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, Pos[0], Pos[1], objectcoordz, 1, 0, 0, 1);
	ShowMessageOnScreen("~g~ Moved Blockade Down");
	return 0;
}
}
bool ObjMoveForward = false;
int MoveForward(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // was move right
	if(!ObjMoveForward){
		ObjMoveForward = true;
	}
	else if(ObjMoveForward){
		ObjMoveForward = false;
	}
	return 0;
}

void MoveForwardLoop(){
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
    network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordy = Pos[1];
	if(ObjMoveForward) objectcoordy += 0.1;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, Pos[0], objectcoordy, Pos[2], 1, 0, 0, 1);
	}
}

bool snap = false;
int SnapGround(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // was move right
	if (DoesEntityExist(objecthandle)) {
	//float Position[3];
	//GetEntityCoords(objecthandle, Position);
	float Position[3], dim_min[3], dim_max[3];
	get_model_dimensions(get_entity_model(PlayerPedId()), dim_min, dim_max);
	get_offset_from_entity_in_world_coords(PlayerPedId(), dim_min[0], dim_min[1] + 4.0f, 0.0f, Position);
	get_ground_z_for_3d_coord(Position[0], Position[1], Position[2], &Position[2]);
	set_entity_coords(objecthandle, Position[0], Position[1], Position[2], 1, 0, 0, 1);
	ShowMessageOnScreen("~g~ Snapped Object To Ground Height");
	return 0;
}
}

int TeleportInFront(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // was move right

	float Position[3], dim_min[3], dim_max[3];
	get_model_dimensions(get_entity_model(PlayerPedId()), dim_min, dim_max);
	get_offset_from_entity_in_world_coords(PlayerPedId(), dim_min[0], dim_min[1] + 5.0f, 0.0f, Position);
	get_ground_z_for_3d_coord(Position[0], Position[1], Position[2], &Position[2]);
	int myvehicle;
	int myhandle = GetPlayerHandle(PlayerId());
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, Position[0], Position[1], Position[2], 0, 0, 0, 1);
		}
		else{
	      set_entity_coords(PlayerPedId(), Position[0], Position[1], Position[2], 1, 0, 0, 1);
		}
	}
	ShowMessageOnScreen("~g~ Teleported 10 In Front!");
	return 0;
}

bool MoveObjBackwards = false;
int MoveBackward(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // was move forward
    if(!MoveObjBackwards){
		MoveObjBackwards = true;
	}
	else if(MoveObjBackwards){
		MoveObjBackwards = false;
	}
	return 0;
}

void MoveBackwardsLoop(){
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordy = Pos[1];
	if(MoveObjBackwards) objectcoordy -= 0.1;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, Pos[0], objectcoordy, Pos[2], 1, 0, 0, 1);
	}
}
bool ObjMoveLeft = false;
int MoveLeft(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // was move backward
	if(!ObjMoveLeft){
		ObjMoveLeft = true;
	}
	else if(ObjMoveLeft){
		ObjMoveLeft = false;
	}
	return 0;
}

void MoveLeftLoop(){
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordx = Pos[0];
	if(ObjMoveLeft) objectcoordx -= 0.1;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, objectcoordx, Pos[1], Pos[2], 1, 0, 0, 1);
	}
}
bool MoveObjRight = false; 
int MoveRight(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) { // was move left
	if(!MoveObjRight){
		MoveObjRight = true;
	}
	else if(MoveObjRight){
		MoveObjRight = false;
	}
	return 0;
}

void MoveRightLoop(){
	if (DoesEntityExist(objecthandle)) {
	float Pos[3];
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, Pos);
	objectcoordx = Pos[0];
	if(MoveObjRight) objectcoordx += 0.1;
	network_request_control_of_entity(objecthandle);
	set_entity_coords(objecthandle, objectcoordx, Pos[1], Pos[2], 1, 0, 0, 1);
	}
}

int HeadingLeft(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectyaw = get_entity_heading(objecthandle);
	objectyaw += 2.0;
	network_request_control_of_entity(objecthandle);
	set_entity_rotation(objecthandle,objectpitch,objectroll,objectyaw,2,1);
	ShowMessageOnScreen("~g~ + Yaw");
	return 0;
}
}

int HeadingRight(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectyaw = get_entity_heading(objecthandle);
	objectyaw -= 2.0;
	network_request_control_of_entity(objecthandle);
	set_entity_rotation(objecthandle,objectpitch,objectroll,objectyaw,2,1);
	ShowMessageOnScreen("~g~ - Yaw");
	return 0;
}
}

int ObjectFlat(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectheading = get_entity_heading(objecthandle);
	objectroll = 0;
	objectpitch = 0;
	network_request_control_of_entity(objecthandle);
	set_entity_heading(objecthandle, objectheading + 0.1);
	ShowMessageOnScreen("~g~ Object Set Straight");
	return 0;
}
}

int FreezeObject(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	freeze_entity_position(objecthandle, true);
	ShowMessageOnScreen("~g~ Frozen Object");
	return 0;
}
}

int UnfreezeObject(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	freeze_entity_position(objecthandle, false);
	ShowMessageOnScreen("~g~ Unfrozen Object");
	return 0;
}
}

int PlusPitch(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectyaw = get_entity_heading(objecthandle);
	objectpitch = get_entity_pitch(objecthandle);
	objectpitch += 1.0;
	network_request_control_of_entity(objecthandle);
	set_entity_rotation(objecthandle,objectpitch,objectroll,objectyaw,2,1);
	ShowMessageOnScreen("~g~ + Pitch");
	return 0;
}
}

int MinusPitch(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectyaw = get_entity_heading(objecthandle);
	objectpitch = get_entity_pitch(objecthandle);
	objectpitch -= 1.0;
	network_request_control_of_entity(objecthandle);
	set_entity_rotation(objecthandle,objectpitch,objectroll,objectyaw,2,1);
	ShowMessageOnScreen("~g~ - Pitch");
	return 0;
}
}

int PlusRoll(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectyaw = get_entity_heading(objecthandle);
	objectpitch = get_entity_pitch(objecthandle);
	objectroll += 1.0;
	network_request_control_of_entity(objecthandle);
	set_entity_rotation(objecthandle,objectpitch,objectroll,objectyaw,2,1);
	ShowMessageOnScreen("~g~ + Roll");
	return 0;
}
}

int MinusRoll(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectyaw = get_entity_heading(objecthandle);
	objectpitch = get_entity_pitch(objecthandle);
	objectroll -= 1.0;
	network_request_control_of_entity(objecthandle);
	set_entity_rotation(objecthandle,objectpitch,objectroll,objectyaw,2,1);
	ShowMessageOnScreen("~g~ - Roll");
	return 0;
}
}

int Credits1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	ShowMessageOnScreen("~y~The source creator and has been a inspiration to me.");
	return 0;
}

int Credits2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	ShowMessageOnScreen("~y~A very great friend that has helped me alot with errors.");
	return 0;
}

int Credits3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	ShowMessageOnScreen("~y~Another very great friend that helped alot with reorganization and ideas.");
	return 0;
}

int Credits4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	ShowMessageOnScreen("~y~A very good friend of mine that has helped me alot and another guy that inspires me.");
	return 0;
}

int Credits5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	ShowMessageOnScreen("~y~I'm the one who EDITED this menu source that was originally made by Chr0m3, not my source!");
	return 0;
}

int BoarModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xCE5FF074;
	return 0;
}

int FootModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 1641334641;
	return 0;
}

int JesusModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 3459037009;
	return 0;
}

int RangerModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 1011059922;
	return 0;
}

int MexicanModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 3367706194;
	return 0;
}

int ChopModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x14EC17EA;
	return 0;
}

int ChopModel1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x14EC17EA;
	return 0;
}

int CoyoteModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x644AC75E;
	return 0;
}

int HuskyModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x4E8F95A2;
	return 0;
}

int MtLion(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x1250D7BA;
	return 0;
}

int ShepModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x431FC24C;
	return 0;
}

int ChimpModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -1469565163;
	return 0;
}

int RetModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x349F33E1;
	return 0;
}

int PigModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xB11BAB56;
	return 0;
}

int RotModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x9563221D;
	return 0;
}

int MercModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -1275859404;
	return 0;
}

int GunmanModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xB881AEE;
	return 0;
}

int PrisonnModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xB1BB9B59;
	return 0;
}

int SwatModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x8D8F1B10;
	return 0;
}

int ClownModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x4498DDE;
	return 0;
}

int Bugstars(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x48114518;
	return 0;
}

int Diper(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x5442C66B;
	return 0;
}

int Fatso(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xB5CF80E4;
	return 0;
}

int NakedMan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x55446010;
	return 0;
}

int SpaceMan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xE7B31432;
	return 0;
}

int FireModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -1229853272;
	return 0;
}

int Johhny(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x87CA80AE;
	return 0;
}

int FBI(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x3AE4A33B;
	return 0;
}

bool norandomcomps = false;
int Micheal(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xD7114C9;
	norandomcomps = true;
	return 0;
}

int Hippy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -2126242959;
	//norandomcomps = true;
	return 0;
}

int Gangster(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -1031795266;
	return 0;
}

int Trevor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x9B810FA2;
	norandomcomps = true;
	return 0;
}

int Franklin(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x9B22DBAF; 
	norandomcomps = true;
	return 0;
}

int PilotModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = -163714847; 
	norandomcomps = true;
	return 0;
}

int CIA(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x625D6958; 
	norandomcomps = true;
	return 0;
}

int COPM(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x5E3DA4A4; 
	norandomcomps = true;
	return 0;
}

int COPF(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x15F8700D; 
	norandomcomps = true;
	return 0;
}

int COPHW(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x739B1EF5; 
	norandomcomps = true;
	return 0;
}

int COPSH(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xB144F9B9; 
	norandomcomps = true;
	return 0;
}

int COPSW(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x1AE8BB58; 
	norandomcomps = true;
	return 0;
}

int MERC(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xB3F3EE34; 
	norandomcomps = true;
	return 0;
}

int SEC(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xF161D212; 
	norandomcomps = true;
	return 0;
}

int SEC2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x2930C1AB; 
	norandomcomps = true;
	return 0;
}

int MBO(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x7A05FA59; 
	norandomcomps = true;
	return 0;
}

int MMM(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0x65793043; 
	norandomcomps = true;
	return 0;
}

int LolWander(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	MakePlayerComeTome(subMenuIndex);
	return 0;
}
bool telefoot_prison = false;
int PrisonTele(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	telefoot_prison = true;
	return 0;
}

int TeleportWayOnline(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	telefoot_way = true;
	return 0;
}

int LolWanderTele(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	MakePlayerComeTomeFoot(subMenuIndex);
	return 0;
}


int KidNap(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	nap = true;
	return 0;
}

int PlayerLeave(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	kidnap = true;
	return 0;
}

int KickFromVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	kickfromveh = true;
	return 0;
}

int FreezeOnlinePlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;

	if (!freeze)
	{
		freeze = true;
	}

	else if (freeze)
	{
		freeze = false;
	}
	return 0;
}


bool vm_anim = false;
int StunLoop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "ragdoll@human";
	anim = "electrocute";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int FireLoop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "ragdoll@human";
	anim = "on_fire";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int PoleDance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@strip_club@pole_dance@pole_dance1";
	anim = "pd_dance_01";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int PoleDance2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@strip_club@pole_dance@pole_dance2";
	anim = "pd_dance_02";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int PoleDance3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@strip_club@pole_dance@pole_dance3";
	anim = "pd_dance_03";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int PrivateDance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@strip_club@private_dance@part1";
	anim = "priv_dance_p1";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int FuckAir(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "rcmpaparazzo_2";
	anim = "shag_loop_a";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int FuckAir2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "rcmpaparazzo_2";
	anim = "shag_loop_poppy";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int Tazer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "stungun@sitting";
	anim = "damage_vehicle";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int Tazer2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "stungun@standing";
	anim = "damage";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ProsMale(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@prostitutes@sexnorm_veh";
	anim = "sex_loop_male";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ProsFemale(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@prostitutes@sexnorm_veh";
	anim = "sex_loop_prostitute";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int BJMale(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@prostitutes@sexnorm_veh";
	anim = "bj_loop_male";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int BJFemale(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "mini@prostitutes@sexnorm_veh";
	anim = "bj_loop_prostitute";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int DrunkSexM(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "random@drunk_driver_2";
	anim = "cardrunksex_loop_m";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int DrunkSexF(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "random@drunk_driver_2";
	anim = "cardrunksex_loop_f";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int Situps(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "amb@world_human_sit_ups@male@base";
	anim = "base";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int TapDancingHeaven(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "special_ped@mountain_dancer@monologue_2@monologue_2a";
	anim = "mnt_dnc_angel";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int ButtwagDance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "special_ped@mountain_dancer@monologue_3@monologue_3a";
	anim = "mnt_dnc_buttwag";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int VerseDance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "special_ped@mountain_dancer@monologue_4@monologue_4a";
	anim = "mnt_dnc_verse";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int HeavenDance(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "special_ped@mountain_dancer@monologue_1@monologue_1a";
	anim = "mtn_dnc_if_you_want_to_get_to_heaven";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int JerkingOffLoop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "switch@trevor@jerking_off";
	anim = "trev_jerking_off_loop";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int PullUpsSports(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "SWITCH@FRANKLIN@GYM";
	anim = "001942_02_GC_FRAS_IG_5_BASE";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int TrevorDrunkHowling(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "switch@trevor@drunk_howling";
	anim = "loop";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int RollingBarrel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "misschinese2_barrelroll";
	anim = "barrel_roll_loop_A";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}//

int Meditating(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "rcmcollect_paperleadinout@";
	anim = "meditiate_idle";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int Pushups(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "amb@world_human_push_ups@male@base";
	anim = "base";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ArmsWave(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "random@car_thief@victimpoints_ig_3";
	anim = "arms_waving";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int Chop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@amb@";
	anim = "hump_loop_chop";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ChopF(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@amb@";
	anim = "hump_loop_ladydog";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int CopKneel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "random@arrests";
	anim = "kneeling_arrest_idle";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int CopHands(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@move";
	anim = "dump_enter";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

void enablevehmods() {
int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
set_vehicle_mod_kit(vehicle, 0);
}
bool wheelsmodded = false;
int StockTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ Stock tyres applied, If your wheels changed with the tyres just change your wheels in the menu!");
	return 0;
}

int CustomTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 23, wheel, 1);
	ShowMessageOnScreen("~g~ Custom tyres applied, If your wheels changed with the tyres just change your wheels in the menu!");
	return 0;
}

int BpTyres(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyres_can_burst(vehicle, 0);
	ShowMessageOnScreen("~g~ Your tyres are now bulletproof!");
	return 0;
}

int NoArmour(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 16);
	ShowMessageOnScreen("~g~ Armour removed");
	return 0;
}

int StockWheels(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 23);
	ShowMessageOnScreen("~g~ Stock wheels applied");
	return 0;
}
int Smoke0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 0, 0);
	ShowMessageOnScreen("~g~ Red tyre smoke applied");
	return 0;
}
int Smoke1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 0, 255, 0);
	ShowMessageOnScreen("~g~ Green tyre smoke applied");
	return 0;
}
int Smoke2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 0, 0, 255);
	ShowMessageOnScreen("~g~ Blue tyre smoke applied");
	return 0;
}
int Smoke3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 127, 0, 255);
	ShowMessageOnScreen("~g~ Purple tyre smoke applied");
	return 0;
}
int Smoke4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 51, 255);
	ShowMessageOnScreen("~g~ Pink tyre smoke applied");
	return 0;
}
int Smoke5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 102, 178, 255);
	ShowMessageOnScreen("~g~ Sky blue tyre smoke applied");
	return 0;
}
int Smoke6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 128, 0);
	ShowMessageOnScreen("~g~ Orange tyre smoke applied");
	return 0;
}
int Smoke7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 255, 255, 0);
	ShowMessageOnScreen("~g~ Yellow tyre smoke applied");
	return 0;
}
int Smoke8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_tyre_smoke_color(vehicle, 0, 255, 255);
	ShowMessageOnScreen("~g~ Cyan tyre smoke applied");
	return 0;
}
int StockFb(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 1);
	ShowMessageOnScreen("~g~ Stock front bumper installed");
	return 0;
}
bool turbo_check = false;
int TurboToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	if (!turbo_check) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    toggle_vehicle_mod(vehicle, 18, 1);
	ShowMessageOnScreen("~g~ Turbo installed");
	turbo_check = true;
	}
	else if (turbo_check) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	toggle_vehicle_mod(vehicle, 18, 0);
	ShowMessageOnScreen("~g~ Turbo uninstalled");
	turbo_check = false;
	}
	return 0;
}

bool light_check = false;
int LightToggle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	if (!light_check) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    toggle_vehicle_mod(vehicle, 22, 1);
	ShowMessageOnScreen("~g~ Xenon Lights installed");
	light_check = true;
	}
	else if (light_check) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	toggle_vehicle_mod(vehicle, 22, 0);
	ShowMessageOnScreen("~g~ Xenon Lights uninstalled");
	light_check = false;
	}
	return 0;
}

int Tint0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 4);
	ShowMessageOnScreen("~g~ Tint removed!");
	return 0;
}
int Tint1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 3);
	ShowMessageOnScreen("~g~ Light tint installed!");
	return 0;
}
int Tint2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 2);
	ShowMessageOnScreen("~g~ Dark tint installed!");
	return 0;
}
int Tint3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 1);
	ShowMessageOnScreen("~g~ Limo tint installed!");
	return 0;
}
int Tint4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 5);
	ShowMessageOnScreen("~g~ Mexican's Black tint installed!");
	return 0;
}
int Tint5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_window_tint(vehicle, 7);
	ShowMessageOnScreen("~g~ Mexican's Green tint installed!");
	return 0;
}

bool door0 = false;
int OpenDoor0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!door0) {
    set_vehicle_door_open(vehicle, 0);
	ShowMessageOnScreen("~g~ Drivers front door opened");
	door0 = true;
	}
	else if (door0) {
    set_vehicle_door_shut(vehicle, 0);
	ShowMessageOnScreen("~g~ Drivers front door closed");
	door0 = false;
	}
	return 0;
}
int RemoveDFDoor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_door_broken(vehicle, 0, 1);
	ShowMessageOnScreen("~g~ Drivers front door removed!");
	return 0;
}

bool door1 = false;
int OpenDoor1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!door1) {
    set_vehicle_door_open(vehicle, 1);
	ShowMessageOnScreen("~g~ Passenger front door opened");
	door1 = true;
	}
	else if (door1) {
    set_vehicle_door_shut(vehicle, 1);
	ShowMessageOnScreen("~g~ Passenger front door closed");
	door1 = false;
	}
	return 0;
}
int RemovePFDoor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_door_broken(vehicle, 1, 1);
	ShowMessageOnScreen("~g~ Passenger front door removed!");
	return 0;
}

bool door2 = false;
int OpenDoor2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!door2) {
    set_vehicle_door_open(vehicle, 2);
	ShowMessageOnScreen("~g~ Drivers rear door opened");
	door2 = true;
	}
	else if (door2) {
    set_vehicle_door_shut(vehicle, 2);
	ShowMessageOnScreen("~g~ Drivers rear door closed");
	door2 = false;
	}
	return 0;
}
int RemoveDRDoor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_door_broken(vehicle, 2, 1);
	ShowMessageOnScreen("~g~ Drivers rear door removed!");
	return 0;
}

bool door3 = false;
int OpenDoor3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!door3) {
    set_vehicle_door_open(vehicle, 3);
	ShowMessageOnScreen("~g~ Passenger rear door opened");
	door3 = true;
	}
	else if (door3) {
    set_vehicle_door_shut(vehicle, 3);
	ShowMessageOnScreen("~g~ Passenger rear door closed");
	door3 = false;
	}
	return 0;
}
int RemovePRDoor(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_door_broken(vehicle, 3, 1);
	ShowMessageOnScreen("~g~ Passenger rear door removed!");
	return 0;
}

bool door4 = false;
int OpenDoor4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!door4) {
    set_vehicle_door_open(vehicle, 4);
	ShowMessageOnScreen("~g~ Hood opened");
	door4 = true;
	}
	else if (door4) {
    set_vehicle_door_shut(vehicle, 4);
	ShowMessageOnScreen("~g~ Hood closed");
	door4 = false;
	}
	return 0;
}
int RemoveHood(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    set_vehicle_door_broken(vehicle, 4, 1);
	ShowMessageOnScreen("~g~ Hood removed!");
	return 0;
}

bool door5 = false;
int OpenDoor5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!door5) {
    set_vehicle_door_open(vehicle, 5);
	ShowMessageOnScreen("~g~ Boot opened");
	door5 = true;
	}
	else if (door5) {
    set_vehicle_door_shut(vehicle, 5);
	ShowMessageOnScreen("~g~ Boot closed");
	door5 = false;
	}
	return 0;
}
int RemoveBoot(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_door_broken(vehicle, 5, 1);
	ShowMessageOnScreen("~g~ Boot Removed");
	return 0;
}

int Armour0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 0, 0);
	ShowMessageOnScreen("~g~ 20 percent Armour installed");
	return 0;
}

int Armour1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 1, 0);
	ShowMessageOnScreen("~g~ 40 percent Armour installed");
	return 0;
}

int Armour2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 2, 0);
	ShowMessageOnScreen("~g~ 60 percent Armour installed");
	return 0;
}

int Armour3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 3, 0);
	ShowMessageOnScreen("~g~ 80 percent Armour installed");
	return 0;
}

int Armour4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 16, 4, 0);
	ShowMessageOnScreen("~g~ 100 percent Armour installed");
	return 0;
}

int StockHorn(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 14);
	ShowMessageOnScreen("~g~ Stock horn installed");
	return 0;
}
int Horn0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 0, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 1, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 2, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 3, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 4, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 5, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 6, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 7, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 8, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 9, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 10, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 11, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 12, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 13, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 14, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 15, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 16, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 17, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 18, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 19, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn20(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 20, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn21(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 21, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn22(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 22, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn23(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 23, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn24(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 24, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn25(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 25, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn26(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 26, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn27(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 27, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn28(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 28, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn29(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 29, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}
int Horn30(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 14, 30, 0);
	ShowMessageOnScreen("~g~ Horn installed");
	return 0;
}

int Fb0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 0, 0);
	ShowMessageOnScreen("~g~ Front bumper 1 installed");
	return 0;
}
int Fb1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 1, 0);
	ShowMessageOnScreen("~g~ Front bumper 2 installed");
	return 0;
}
int Fb2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 2, 0);
	ShowMessageOnScreen("~g~ Front bumper 3 installed");
	return 0;
}
int Fb3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 3, 0);
	ShowMessageOnScreen("~g~ Front bumper 3 installed");
	return 0;
}
int Fb4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 4, 0);
	ShowMessageOnScreen("~g~ Front bumper 3 installed");
	return 0;
}
int Fb5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 1, 5, 0);
	ShowMessageOnScreen("~g~ Front bumper 3 installed");
	return 0;
}

int StockSk(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 3);
	ShowMessageOnScreen("~g~ Stock side skirts installed");
	return 0;
}

int Sk0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 0, 0);
	ShowMessageOnScreen("~g~ Side skirts 1 installed");
	return 0;
}
int Sk1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 1, 0);
	ShowMessageOnScreen("~g~ Side skirts 2 installed");
	return 0;
}
int Sk2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 2, 0);
	ShowMessageOnScreen("~g~ Side skirts 3 installed");
	return 0;
}
int Sk3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 3, 3, 0);
	ShowMessageOnScreen("~g~ Side skirts 4 installed");
	return 0;
}

int StockHood(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 7);
	ShowMessageOnScreen("~g~ Stock hood installed");
	return 0;
}

int Hood0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 0, 0);
	ShowMessageOnScreen("~g~ Hood 1 installed");
	return 0;
}
int Hood1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 1, 0);
	ShowMessageOnScreen("~g~ Hood 2 installed");
	return 0;
}
int Hood2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 2, 0);
	ShowMessageOnScreen("~g~ Hood 3 installed");
	return 0;
}
int Hood3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 3, 0);
	ShowMessageOnScreen("~g~ Hood 4 installed");
	return 0;
}
int Hood4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 7, 4, 0);
	ShowMessageOnScreen("~g~ Hood 5 installed");
	return 0;
}

int StockLFender(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 8);
	ShowMessageOnScreen("~g~ Stock left fender installed");
	return 0;
}

int LFender0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 8, 0, 0);
	ShowMessageOnScreen("~g~ Left fender 1 installed");
	return 0;
}
int LFender1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 8, 1, 0);
	ShowMessageOnScreen("~g~ Left fender 2 installed");
	return 0;
}
int LFender2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 8, 2, 0);
	ShowMessageOnScreen("~g~ Left fender 3 installed");
	return 0;
}

int StockRFender(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 8);
	ShowMessageOnScreen("~g~ Stock right fender installed");
	return 0;
}

int RFender0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 9, 0, 0);
	ShowMessageOnScreen("~g~ Right fender 1 installed");
	return 0;
}
int RFender1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 9, 1, 0);
	ShowMessageOnScreen("~g~ Right fender 2 installed");
	return 0;
}
int RFender2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 9, 2, 0);
	ShowMessageOnScreen("~g~ Right fender 3 installed");
	return 0;
}

int StockRoof(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 10);
	ShowMessageOnScreen("~g~ Stock roof installed");
	return 0;
}

int Roof0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 0, 0);
	ShowMessageOnScreen("~g~ Roof 1 installed");
	return 0;
}
int Roof1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 1, 0);
	ShowMessageOnScreen("~g~ Roof 2 installed");
	return 0;
}
int Roof2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 2, 0);
	ShowMessageOnScreen("~g~ Roof 3 installed");
	return 0;
}
int Roof3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 10, 3, 0);
	ShowMessageOnScreen("~g~ Roof 4 installed");
	return 0;
}

int StockInterior(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 5);
	ShowMessageOnScreen("~g~ Stock interior/chassis installed");
	return 0;
}

int Interior0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 0, 0);
	ShowMessageOnScreen("~g~ Interior/Chassis installed");
	return 0;
}

int MaxLSCUpgrades(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod_kit(vehicle, 0);
    PaintCar(vehicle, 120, 120);
	PaintCarExtra(vehicle, 120, 120);
	set_number_plate(vehicle, "xxHASTERxx");
	SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, 1);
	toggle_vehicle_mod(vehicle, 18, 1);
	toggle_vehicle_mod(vehicle, 22, 1);
	set_vehicle_mod(vehicle, 16, 5, 0);
	set_vehicle_mod(vehicle, 12, 2, 0);
	set_vehicle_mod(vehicle, 11, 3, 0);
	set_vehicle_mod(vehicle, 14, 14, 0);
	set_vehicle_mod(vehicle, 15, 3, 0);
	set_vehicle_mod(vehicle, 13, 2, 0);
	set_vehicle_wheel_type(vehicle, 6);
	set_vehicle_window_tint(vehicle, 5);
	set_vehicle_mod(vehicle, 23, 19, 1);
	set_vehicle_mod(vehicle, 0, 1, 0);
	set_vehicle_mod(vehicle, 1, 1, 0);
	set_vehicle_mod(vehicle, 2, 1, 0);
	set_vehicle_mod(vehicle, 3, 1, 0);
	set_vehicle_mod(vehicle, 4, 1, 0);
	set_vehicle_mod(vehicle, 5, 1, 0);
	set_vehicle_mod(vehicle, 6, 1, 0);
	set_vehicle_mod(vehicle, 7, 1, 0);
	set_vehicle_mod(vehicle, 8, 1, 0);
	set_vehicle_mod(vehicle, 9, 1, 0);
	set_vehicle_mod(vehicle, 10, 1, 0);
	ShowMessageOnScreen("~y~ Your vehicle has been maxed out bruh!");
	return 0;
}

int Interior1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 1, 0);
	ShowMessageOnScreen("~g~ Interior/Chassis installed");
	return 0;
}
int Interior2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 2, 0);
	ShowMessageOnScreen("~g~ Interior/Chassis installed");
	return 0;
}
int Interior3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 5, 3, 0);
	ShowMessageOnScreen("~g~ Interior/Chassis installed");
	return 0;
}

int StockGrill(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 6);
	ShowMessageOnScreen("~g~ Stock grill installed");
	return 0;
}

int Grill0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 0, 0);
	ShowMessageOnScreen("~g~ Grill 1 installed");
	return 0;
}
int Grill1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 1, 0);
	ShowMessageOnScreen("~g~ Grill 2 installed");
	return 0;
}
int Grill2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 2, 0);
	ShowMessageOnScreen("~g~ Grill 3 installed");
	return 0;
}
int Grill3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 6, 3, 0);
	ShowMessageOnScreen("~g~ Grill 4 installed");
	return 0;
}

int StockRb(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 2);
	ShowMessageOnScreen("~g~ Stock rear bumper installed");
	return 0;
}

int Rb0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 0, 0);
	ShowMessageOnScreen("~g~ Rear bumper 1 installed");
	return 0;
}
int Rb1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 1, 0);
	ShowMessageOnScreen("~g~ Rear bumper 2 installed");
	return 0;
}
int Rb2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 2, 0);
	ShowMessageOnScreen("~g~ Rear bumper 3 installed");
	return 0;
}
int Rb3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 2, 3, 0);
	ShowMessageOnScreen("~g~ Rear bumper 4 installed");
	return 0;
}

int StockSpoiler(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 0);
	ShowMessageOnScreen("~g~ Stock spoiler installed");
	return 0;
}

int Spoiler0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 0, 0);
	ShowMessageOnScreen("~g~ Spoiler 1 installed");
	return 0;
}
int Spoiler1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 1, 0);
	ShowMessageOnScreen("~g~ Spoiler 2 installed");
	return 0;
}
int Spoiler2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 2, 0);
	ShowMessageOnScreen("~g~ Spoiler 3 installed");
	return 0;
}
int Spoiler3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 3, 0);
	ShowMessageOnScreen("~g~ Spoiler 4 installed");
	return 0;
}
int Spoiler4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 4, 0);
	ShowMessageOnScreen("~g~ Spoiler 5 installed");
	return 0;
}
int Spoiler5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 5, 0);
	ShowMessageOnScreen("~g~ Spoiler 6 installed");
	return 0;
}
int Spoiler6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 0, 6, 0);
	ShowMessageOnScreen("~g~ Spoiler 7 installed");
	return 0;
}

int ExStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 4);
	ShowMessageOnScreen("~g~ Stock exhaust installed");
	return 0;
}

int Ex0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 0, 0);
	ShowMessageOnScreen("~g~ Exhaust 1 installed");
	return 0;
}
int Ex1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 1, 0);
	ShowMessageOnScreen("~g~ Exhaust 2 installed");
	return 0;
}
int Ex2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 2, 0);
	ShowMessageOnScreen("~g~ Exhaust 3 installed");
	return 0;
}
int Ex3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 4, 3, 0);
	ShowMessageOnScreen("~g~ Exhaust 4 installed");
	return 0;
}


int SuspStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 15);
	ShowMessageOnScreen("~g~ Stock suspension installed");
	return 0;
}

int Susp0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 0, 0);
	ShowMessageOnScreen("~g~ Lowered suspension installed");
	return 0;
}

int Susp1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 1, 0);
	ShowMessageOnScreen("~g~ Street suspension installed");
	return 0;
}

int Susp2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 2, 0);
	ShowMessageOnScreen("~g~ Sports suspension installed");
	return 0;
}
int Susp3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 15, 3, 0);
	ShowMessageOnScreen("~g~ Competition suspension installed");
	return 0;
}

int BrakeStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 12);
	ShowMessageOnScreen("~g~ Stock brakes installed");
	return 0;
}

int Brake0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 12, 0, 0);
	ShowMessageOnScreen("~g~ Street brakes installed");
	return 0;
}

int Brake1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 12, 1, 0);
	ShowMessageOnScreen("~g~ Sports brakes installed");
	return 0;
}

int Brake2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 12, 2, 0);
	ShowMessageOnScreen("~g~ Race brakes installed");
	return 0;
}

int TranStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 13);
	ShowMessageOnScreen("~g~ Stock transmission installed");
	return 0;
}
int Tran0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 13, 0, 0);
	ShowMessageOnScreen("~g~ Street transmission installed");
	return 0;
}
int Tran1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 13, 1, 0);
	ShowMessageOnScreen("~g~ Sports transmission installed");
	return 0;
}
int Tran2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 13, 2, 0);
    ShowMessageOnScreen("~g~ Race transmission installed");
	return 0;
}
int EngineStock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	remove_vehicle_mod(vehicle, 11);
	ShowMessageOnScreen("~g~ Stock engine installed");
	return 0;
}
int Engine0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 0, 0);
	ShowMessageOnScreen("~g~ New engine has been installed!");
	return 0;
}
int Engine1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 1, 0);
	ShowMessageOnScreen("~g~ New engine has been installed!");
	return 0;
}
int Engine2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 2, 0);
	ShowMessageOnScreen("~g~ New engine has been installed!");
	return 0;
}
int Engine3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_mod(vehicle, 11, 3, 0);
	ShowMessageOnScreen("~g~ New engine has been installed!");
	return 0;
}

int HighEnd0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int HighEnd1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int HighEnd2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int HighEnd3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int HighEnd4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int HighEnd19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 19;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 7);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Lowrider0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Lowrider1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Lowrider2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Lowrider3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Lowrider4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Lowrider14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 2);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Muscle0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Muscle1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Muscle2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Muscle3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Muscle4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Muscle17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 1);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Offroad0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Offroad1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Offroad2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Offroad3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Offroad4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Offroad5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Offroad6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Offroad7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Offroad8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Offroad9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 4);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Sport19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 19;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport20(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 20;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport21(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 21;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport22(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 22;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport23(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 23;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Sport24(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 24;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 0);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int SUV0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int SUV1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int SUV2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int SUV3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int SUV4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int SUV18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 3);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 0;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 1;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 2;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 3;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 4;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 5;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 6;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 7;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 8;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 9;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 10;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 11;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 12;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 13;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 14;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner15(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 15;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner16(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 16;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner17(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 17;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner18(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 18;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}
int Tuner19(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 19;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner20(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 20;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner21(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 21;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner22(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 22;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}

int Tuner23(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	enablevehmods();
	wheel = 23;
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	set_vehicle_wheel_type(vehicle, 5);
	set_vehicle_mod(vehicle, 23, wheel, 0);
	ShowMessageOnScreen("~g~ New wheels have been applied!");
	return 0;
}


	int Weather0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("BLIZZARD");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("CLEAR");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("CLEARING");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("CLOUDS");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather4(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("EXTRASUNNY");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather5(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("FOGGY");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather6(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("NEUTRAL");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather7(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("OVERCAST");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather8(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("RAIN");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather9(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("SMOG");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather10(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("SNOW");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather11(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("SNOWLIGHT");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	int Weather12(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	set_override_weather("THUNDER");
	ShowMessageOnScreen("~g~ Weather change been applied!");
	return 0;
	}
	/*int Weather13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	int time = get_clock_hours();
	if (time == 23) {
	time = 0;
    network_override_clock_time(0, 0, 0);
	ShowMessageOnScreen("~g~ Set to hour 24");
	}
	else {
    time++;
    network_override_clock_time(time, 0, 0);
	ShowMessageOnScreen("~g~ Set to hour %i", time);
	}
	return 0;
	}
	int Weather14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
	int time = get_clock_hours();
	if (time == 1) {
	time = 0;
    network_override_clock_time(0, 0, 0);
	ShowMessageOnScreen("~g~ Set to hour 24");
	}
	else {
    time--;
    network_override_clock_time(time, 0, 0);
	ShowMessageOnScreen("~g~ Set to hour %i", time);
	}
	return 0;
	}*/

int Weather13(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
	{
    int time = get_clock_hours() + 1;
    if (time > 23) 
        time = 0;
    network_override_clock_time(time, 0, 0);
    ShowMessageOnScreen("~g~ Set to hour %i", time);
    return 0;
	}

int Weather14(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
    int time = get_clock_hours() - 1;
    if (time < 0)
        time = 23;
    network_override_clock_time(time, 0, 0);
    ShowMessageOnScreen("~g~ Set to hour %i", time);
    return 0;
}

#ifdef PRIVATE

bool Peg_Global = false;
int car_hash = 0x1FD824AF;
int pointer1;
int pointer2;
int Peg1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	/*int pointer = *(int *)(Var_Pointer + 4);
	pointer1 = pointer += (2131539 * 4); 
	pointer2 = pointer += (2134525 * 4);*/
	pointer1 = GlobalToAddress(2390986, 2697);
	pointer1 = GlobalToAddress(2394984, 1643 + 42);
	Peg_Global = true;
	ShowMessageOnScreen("~g~ Call up pegasus and order any vehicle and it will be a space docker!, May not work all the time!");
	return 0;
}

void pegasusloop() {
	*(int *)pointer1 = car_hash;
	*(int *)pointer2 = car_hash;
}

#endif

	/*Pegasus->AddStaticItem("Space Docker", false, Peg1, NULL);
	Pegasus->AddStaticItem("FBI Cruiser", false, Peg2, NULL);
	Pegasus->AddStaticItem("Clown Van", false, Peg3, NULL);
	Pegasus->AddStaticItem("Weed Van", false, Peg4, NULL);
	Pegasus->AddStaticItem("Sultan", false, Peg5, NULL);*/


bool Create = false;
int ToggleCreator(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	Create ^= true;// toggle
	snap ^= true;
	ShowMessageOnScreen("~y~ Creator Mode: %s!", Create ? "~g~ON, ~b~Aim at an object!" : "~r~OFF!");
	return 0;
}

int ToggleLag(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	causelag ^= true;// toggle
	//ShowMessageOnScreen("~g~ Spawner Hook %s!", causelag ? "enabled" : "disabled");
	return 0;
}

void create_loop()
{
	if(unk_0x8866D9D0(PlayerId(), &objecthandle)) {
	if (IsEntityVehicle(objecthandle)) {
	ShowMessageOnScreen("~g~ Vehicle handle returned you can now move this vehicle with the object spawner options");
	}
	if (IsEntityObject(objecthandle)) {
    ShowMessageOnScreen("~g~ Object handle returned you can now move this object with the object spawner options");
	}
  }
}

int SaveObjHandle1;
int SaveObjectHandle1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	SaveObjHandle1 = objecthandle;
	return 0;
}

int SaveVehHandle1;
int SaveVehicleHandle1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	SaveVehHandle1 = objecthandle;
	return 0;
}

void moneyGunLoop()
{
   float Loc[3];
  if (is_ped_shooting(PlayerPedId()))
  {
   if (get_ped_last_weapon_impact_coord3(PlayerPedId(), Loc))
   {
	   Vector3 Pos;
	   Pos.x = Loc[0], Pos.y = Loc[1], Pos.z = Loc[2];
       set_entity_coords2(PlayerPedId(), &Pos, 0, 0, 0, 1);
   }
  }
}

void pitchToggle()
{
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectpitch1 = get_entity_pitch(objecthandle);
	PrintToScreen("Object Pitch:", 0.20000000, 0.91000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(objectpitch1, 0.29000000, 0.91000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
    }

	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectroll1 = get_entity_roll(objecthandle);
	PrintToScreen("Object Roll:", 0.340000000, 0.91000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(objectroll1, 0.43000000, 0.91000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
    }

	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	objectyaw1 = get_entity_heading(objecthandle);
	PrintToScreen("Object Yaw:", 0.470000000, 0.91000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(objectyaw1, 0.5600000, 0.91000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
    }
}

void playerCoordsToggle()
{
	float Pos[3];
	GetEntityCoords(PlayerPedId(), Pos);
	
	PrintToScreen("X:", 0.20000000, 0.91000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenFloat(Pos[0], 0.23000000, 0.91000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
   
	PrintToScreen("Y:", 0.340000000, 0.91000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenFloat(Pos[1], 0.37000000, 0.91000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
    
	PrintToScreen("Z:", 0.470000000, 0.91000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenFloat(Pos[2], 0.5000000, 0.91000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
}

void moneyTrollToggle()
{
	float xCoord, yCoord, zCoord;
	xCoord = 501.905334;
	yCoord = 5595.983398;
	zCoord = 798.832886;

	RequestModel(0x113FD533);
		if(HasModelLoaded(0x113FD533))
		{
			create_ambient_pickup2(0xCE6FDD6B, xCoord, yCoord, zCoord, 0, 40000, 0x113FD533, 0, 1);
		}

}

void coordsToggle()
{

	float Pos[3];
	GetEntityCoords(objecthandle, Pos);
	
	if (DoesEntityExist(objecthandle)) {
	PrintToScreen("X:", 0.20000000, 0.86000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenFloat(Pos[0], 0.23000000, 0.86000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
    }

	if (DoesEntityExist(objecthandle)) {
	PrintToScreen("Y:", 0.340000000, 0.86000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenFloat(Pos[1], 0.37000000, 0.86000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
    }

	if (DoesEntityExist(objecthandle)) {
	PrintToScreen("Z:", 0.470000000, 0.86000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenFloat(Pos[2], 0.5000000, 0.86000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
    }
}

void hashToggle()
{
	if (DoesEntityExist(objecthandle)) {
	network_request_control_of_entity(objecthandle);
	int hash = get_entity_model(objecthandle);
	PrintToScreen("Object Hash:", 0.20000000, 0.80000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(hash, 0.29000000, 0.80000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
	if (IsEntityVehicle(objecthandle)) {
	PrintToScreen("Entity Type: ~r~Vehicle", 0.39000000, 0.80000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	}
	if (IsEntityObject(objecthandle)) {
    PrintToScreen("Entity Type: ~r~Object", 0.39000000, 0.80000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	}
  }
}

void speed()
{
	int ispeed;
	int speedgunSpeed;
	if (!is_ped_on_foot(PlayerPedId()))
	{
	int car = GetCarCharIsIn(PlayerPedId(), 0);//GET_CAR_CHAR_IS_USING(GetPlayerPed(), &veh_speed);
	/*if (is_vehicle_in_burnout(car)) { ShowMessageOnScreen("~r~ Skid it up brah!!"); }
	else { ShowMessageOnScreen("No skid :("); }*/
    float speed = get_entity_speed(car);
    speed = speed * speedmul; // MaxSpeed (Default: 3.61)! (5.86)
    ispeed = (int) speed; // float to int

	float speedGun = get_entity_speed(objecthandle);
	speedGun = speedGun * speedmuls;
	speedgunSpeed = (int) speedGun;

	PrintToScreen("Speedometer MPH:", 0.20000000, 0.74000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(ispeed, 0.34000000, 0.74000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);

	if (ispeed < 120)
	{
	PrintToScreenNum(ispeed, 0.34000000, 0.74000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
	if (ispeed > 120)
	{
	PrintToScreenNum(ispeed, 0.34000000, 0.74000000, 255, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
	if (ispeed > 180)
	{
	PrintToScreenNum(ispeed, 0.34000000, 0.74000000, 255, 165, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
	if (ispeed > 240)
	{
	PrintToScreenNum(ispeed, 0.34000000, 0.74000000, 255, 0, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
	}
}

void speedGunLoop()
{
	int speedgunSpeed;
	float speedGun = get_entity_speed(objecthandle);
	speedGun = speedGun * speedmuls;
	speedgunSpeed = (int) speedGun;
	PrintToScreen("Speed Gun MPH:", 0.39000000, 0.74000000, 0, 132, 202, 255, 0.80000000, 0.80000000, 0, 6);
	PrintToScreenNum(speedgunSpeed, 0.53000000, 0.74000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);

	if (speedgunSpeed < 120)
	{
	PrintToScreenNum(speedgunSpeed, 0.53000000, 0.74000000, 0, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
	if (speedgunSpeed > 120)
	{
	PrintToScreenNum(speedgunSpeed, 0.53000000, 0.74000000, 255, 255, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
	if (speedgunSpeed > 180)
	{
	PrintToScreenNum(speedgunSpeed, 0.53000000, 0.74000000, 255, 165, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
	if (speedgunSpeed > 240)
	{
	PrintToScreenNum(speedgunSpeed, 0.53000000, 0.74000000, 255, 0, 0, 255, 0.80000000, 0.80000000, 0, 6);
	}
}

#ifdef PRIVATE

bool drop = false;
float cash[3];
int CashDrop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	cashclient = subMenuIndex;
	if (!drop) {
	drop = true;
	ShowMessageOnScreen("~y~ Cash Drop: ~g~Active");
	//GetEntityCoords(GetPlayerHandle(subMenuIndex), cash);
	}
	else if (drop) {
	drop = false;
	ShowMessageOnScreen("~y~ Cash Drop: ~r~Disabled");
	}
	return 0;
}

bool objectDrop = false;
int ObjectCashDrop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!objectDrop) {
	objectDrop = true;
	ShowMessageOnScreen("~y~ Object Cash Drop: ~g~Active ~b~Cone Object Works Best!");
	}
	else if (objectDrop) {
	objectDrop = false;
	ShowMessageOnScreen("~y~ Object Cash Drop: ~r~Disabled");
	}
	return 0;
}

bool Adderdrop = false;
float Addercash[3];
int AdderCashDrop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	Addercashclient = subMenuIndex;
	if (!Adderdrop) {
	Adderdrop = true;
	ShowMessageOnScreen("~y~ Adder Cash Drop: ~g~Active");
	//GetEntityCoords(GetPlayerHandle(subMenuIndex), cash);
	}
	else if (Adderdrop) {
	Adderdrop = false;
	ShowMessageOnScreen("~y~ Adder Cash Drop: ~r~Disabled");
	}
	return 0;
}

bool onedrop = false;
float onecashPos[3];
int OneDollarCashDrop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	onecashclient = subMenuIndex;
	if (!onedrop) {
	onedrop = true;
	ShowMessageOnScreen("~y~ $1 Cash Drop: ~g~Active");
	//GetEntityCoords(GetPlayerHandle(subMenuIndex), cash);
	}
	else if (onedrop) {
	onedrop = false;
	ShowMessageOnScreen("~y~ $1 Cash Drop: ~r~Disabled");
	}
	return 0;
}

bool fagdrop = false;
float fagcash[3];
int AntiSqeakerMoneyFags(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	fagcashclient = subMenuIndex;
	if (!fagdrop) {
	fagdrop = true;
	ShowMessageOnScreen("~y~ Fag Drop: ~g~Active ~b~(Credit: xxHASTERxx For Idea)");
	//GetEntityCoords(GetPlayerHandle(subMenuIndex), cash);
	}
	else if (fagdrop) {
	fagdrop = false;
	ShowMessageOnScreen("~y~ Fag Drop: ~r~Disabled");
	}
	return 0;
}

	/*for (int i = 0; i < Trailamount; i++) {
			float sin = (float)round(sin(i) * radius) + cash[1];
			float cos = (float)round(cos(i) * radius) + cash[0];
		}*/
//int cashCount = 0,
	//cashwait;
//int cashcoount = 120; //3
//int cashwaitam = 1000; //500
////prop_money_bag_01=0x113FD533
void cashloop() 
{
	GetEntityCoords(GetPlayerHandle(cashclient), cash);

       RequestModel(0x113FD533);
		if(HasModelLoaded(0x113FD533))
		{
			create_ambient_pickup2(0xCE6FDD6B, cash[0], cash[1], cash[2] + 1, 0, 40000, 0x113FD533, 0, 1);
		}
}

float objectMoney[3];
void cashCreatorLoop() 
{
	if(DoesEntityExist(objecthandle)){
	network_request_control_of_entity(objecthandle);
	GetEntityCoords(objecthandle, objectMoney);

       RequestModel(0x113FD533);
		if(HasModelLoaded(0x113FD533))
		{
			create_ambient_pickup2(0xCE6FDD6B, objectMoney[0], objectMoney[1], objectMoney[2], 0, 40000, 0x113FD533, 0, 1);
		}
	}
}

//MoneyCreatorMiniGame

void onecashloop() 
{
	GetEntityCoords(GetPlayerHandle(onecashclient), onecashPos);

       RequestModel(0xBB427A69);
		if(HasModelLoaded(0xBB427A69))
		{
			create_ambient_pickup2(0xCE6FDD6B, onecashPos[0], onecashPos[1], onecashPos[2] + 1, 0, 1, 0xBB427A69, 0, 1);
		}
}

void Addercashloop() 
{
	GetEntityCoords(GetPlayerHandle(Addercashclient), Addercash);

       RequestModel(0xB779A091);
		if(HasModelLoaded(0xB779A091))
		{
			create_ambient_pickup2(0xCE6FDD6B, Addercash[0], Addercash[1], Addercash[2] + 2, 0, 40000, 0xB779A091, 0, 1);
		}
}

/*void invisiblePlayerLoop() 
{
   set_entity_visible(PlayerPedId(), false);
}*/

/*void invisibleVehicleLoop()
{
	int myhandle = GetPlayerHandle(PlayerId());
	int myvehicle;
	if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
		    set_entity_visible(myvehicle, false);
		}
	}
	else{
		ShowMessageOnScreen("~g~ You aren't in a vehicle.");
	}
}*/

void teleportGunLoop()
{
	float Coords[3];
	GetEntityCoords(PlayerPedId(), Coords);
	if (is_ped_shooting(PlayerPedId())){
		get_ped_last_weapon_impact_coord(PlayerPedId(), Coords);
		set_entity_coords(PlayerPedId(), Coords[0], Coords[1], Coords[2], 1, 0, 0, 1);
	}
}



int fagcashCount = 0,
	fagcashwait;
int fagcashcoount = 0; //3
int fagcashwaitam = 2000; //500
void fagcashloop() 
{
   if(fagcashCount <= fagcashcoount) {
	GetEntityCoords(GetPlayerHandle(fagcashclient), fagcash);

       RequestModel(0x113FD533);
		if(HasModelLoaded(0x113FD533))
		{
			set_stat_int(get_hash_key("MP0_CHAR_XP_FM"), 2165850);
			create_ambient_pickup(0xCE6FDD6B, fagcash, 0, 1, 0x113FD533, 0, 1);
		}
	fagcashCount += 3;
   }
   else
	{
		if(fagcashwait == 0)
			fagcashwait = GetTickCount();
		if((GetTickCount() - fagcashwait) > fagcashwaitam)
			fagcashCount = fagcashwait = 0;
		}
}

void allcashloop()
{
	int i = 0;
	for (i = 0;i<18;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	GetEntityCoords(Handle, allcash);
       RequestModel(0x113FD533);
		if(HasModelLoaded(0x113FD533))
		{
			create_ambient_pickup(0xCE6FDD6B, allcash, 0, 40000, 0x113FD533, 0, 1);
		}
	}
}
#endif

void SuperJumpLoop(){
	set_super_jump_this_frame(PlayerId());
}
void SuperPunchLoop(){
	set_explosive_melee_this_frame(PlayerId());
}
/*void SwimFastLoop(){
	unk_0xA063CABD();
}*/
void ExplosiveAmmoLoop(){
	set_explosive_ammo_this_frame(PlayerId());
}
void FireAmmoLoop(){
	set_fire_ammo_this_frame(PlayerId());

}

bool cower;
int Cower(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animid = subMenuIndex;
	cower = true;
	/*animdict = "random@arrests";
	anim = "idle_2_hands_up";
	animid = subMenuIndex;
	vm_anim = true;*/

	return 0;
}
int StopLoop(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	StopPlayerTasks(subMenuIndex);
	return 0;
}


int BuffDude(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 0xDA116E7E;
	return 0;
}
bool comps = false;
int Random(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	comps = true;
	return 0;
}
int RageModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 880829941;
	return 0;
}

int MalePants(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 2109968527;
	return 0;
}
bool slender = false;
int Slendy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	slender = true;
	scriptsetModel = 0x92991b72;
	return 0;
}
int FemalePants(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	scriptsetModel = 602513566;
	return 0;
}
bool activenos = false;
int ToggleNos(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_vehicle_boost_active
	activenos = !activenos;
	ShowMessageOnScreen("~g~ Nos is now %s.", activenos ? "On, Press LS To Use Nitrous!" : "off");
	return 0;
}
bool drift = false;
int Slidey(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_vehicle_boost_active
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!drift) {
	unk_0x90D3A0D9(vehicle, 1);
	ShowMessageOnScreen("~g~ Time to drift!, This is terrible (Not my fault it's using one of rockstars natives)");
	drift = true;
	}
	else if (drift) {
	unk_0x90D3A0D9(vehicle, 0);
	ShowMessageOnScreen("~g~ Slidey car turned off.");
	drift = false;
	}
	return 0;
}

bool handdrift = false;
int SlideyHand(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_vehicle_boost_active
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	if (!handdrift) {
	//unk_0x90D3A0D9(vehicle, 1);
	ShowMessageOnScreen("~g~ Time to drift!, Press or hold A to activate slide");
	handdrift = true;
	}
	else if (handdrift) {
	//unk_0x90D3A0D9(vehicle, 0);
	ShowMessageOnScreen("~g~ Handbrake Slidey car turned off");
	handdrift = false;
	}
	return 0;
}

void slideyloop() {
	if (is_control_pressed(2, 174)) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    unk_0x90D3A0D9(vehicle, 1);
	}
	if (is_control_just_released(2, 174)) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
    unk_0x90D3A0D9(vehicle, 0);
	}
}


int Lock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_vehicle_boost_active
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	//set_vehicle_doors_locked(vehicle, 4);
	SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(vehicle, true);
	ShowMessageOnScreen("~g~ Vehicle has been locked!");
	return 0;
}

int Unlock(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//set_vehicle_boost_active
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(vehicle, false);
	ShowMessageOnScreen("~g~ Vehicle has been Unlocked!");
	return 0;
}

int SwapSeats(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int vehicle = GetCarCharIsIn(PlayerPedId(), 0);
	task_shuffle_to_next_vehicle_seat(PlayerPedId(), vehicle);
	ShowMessageOnScreen("~g~ Swapped Vehicle Seats! (Normally Doesn't Work When Menu Is Open)");
	return 0;
}

bool creatorRocket, creatorRequested;
int ToggleCreatorRocket(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!creatorRocket) {
	ShowMessageOnScreen("~y~ Player Rockets: ~g~ON, ~y~Press LS! ~r~Note: If they aren't working try it later.");
	creatorRocket = true;
	creatorRequested = false;
	custom = false;
	}
	else if (creatorRocket) {
	ShowMessageOnScreen("~y~ Player Rockets: ~r~OFF");
	creatorRocket = false;
	custom = false;
	}
	return 0;
}

bool creatorFlares, creatorFRequested;
int ToggleCreatorFlares(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!creatorFlares) {
	ShowMessageOnScreen("~y~ Player Rockets: ~g~ON, ~y~Press LS! ~r~Note: If they aren't working try it later.");
	creatorFlares = true;
	creatorFRequested = false;
	custom = false;
	}
	else if (creatorFlares) {
	ShowMessageOnScreen("~y~ Player Rockets: ~r~OFF");
	creatorFlares = false;
	custom = false;
	}
	return 0;
}


bool rocket, requested;
int ToggleRocket(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!rocket) {
	ShowMessageOnScreen("~g~ Vehicle Rockets On, Press LS To Shoot them!");
	rocket = true;
	requested = false;
	custom = false;
	}
	else if (rocket) {
	ShowMessageOnScreen("~g~ Vehicle Rockets Off");
	rocket = false;
	custom = false;
	}
	//ShowMessageOnScreen("~g~ Vehicle rockets are currently not working");
	return 0;
}

bool fwrocket;
int ToggleFWVehicle(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!fwrocket) {
	ShowMessageOnScreen("~g~ Vehicle Fireworks On, Press LS To Shoot them!");
	fwrocket = true;
	custom = false;
	}
	else if (fwrocket) {
	ShowMessageOnScreen("~g~ Vehicle Fireworks Off");
	fwrocket = false;
	custom = false;
	}
	//ShowMessageOnScreen("~g~ Vehicle rockets are currently not working");
	return 0;
}

bool vehicleFlare;
int ToggleVehicleFlare(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!vehicleFlare) {
	ShowMessageOnScreen("~g~ Vehicle Flares On, Press LS To Shoot them!");
	vehicleFlare = true;
	custom = false;
	}
	else if (vehicleFlare) {
	ShowMessageOnScreen("~g~ Vehicle Flares Off");
	vehicleFlare = false;
	custom = false;
	}
	//ShowMessageOnScreen("~g~ Vehicle rockets are currently not working");
	return 0;
}

bool vehicleSavage;
int ToggleVehicleSavage(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!vehicleSavage) {
	ShowMessageOnScreen("~g~ Vehicle Savage Bullets On, Press X To Shoot them!");
	vehicleSavage = true;
	custom = false;
	}
	else if (vehicleSavage) {
	ShowMessageOnScreen("~g~ Vehicle Savage Bullets Off");
	vehicleSavage = false;
	custom = false;
	}
	return 0;
}

void vehicleSavageLoop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	int PedID;
	if (is_ped_in_any_vehicle(PedID = PlayerPedId()))
	{

		if (menuInputHandler->XButtonDown() && !is_ped_on_foot(PedID)) /// ls
		{
			printf("Pressed LS\n");
			int vehicle = GetCarCharIsIn(PedID, 0 ),
			Model = get_entity_model(vehicle);
			printf("Got vehicle %i \n", vehicle);
			get_model_dimensions( Model, dim_min, dim_max );
			printf("Got dimensions\n");

			if ( is_control_pressed( 2, 198 ) ) // rs
			{
				printf("Pressed RS\n");
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
				printf("Got offset\n");
			}
			else
			{
				printf("Got vehicle %i \n", vehicle);
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				printf("Got offset 2\n");
				if ( Model == get_hash_key("surfer") || Model == get_hash_key("blazer") )
				{
					printf("Checked entity model\n"); 
					targetpos1[2] += 3.5f;
					targetpos2[2] += 3.5f;
				}
				else
				{
					printf("Checked entity model 2\n");
					targetpos1[2]--;
					targetpos2[2]--;
				}
			}
			float vSpeed = get_entity_speed( vehicle );
			if ( ( vSpeed * vSpeed ) > 1500 )
			{
				rocket_speed = ( vSpeed * vSpeed ) + 100;
				printf("Got and multiplied rocket / car speed\n");
			}
			else
			{
				rocket_speed = 1500;
			}
			if (custom){
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("VEHICLE_WEAPON_PLAYER_LAZER"), rocketid, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("VEHICLE_WEAPON_PLAYER_LAZER"), rocketid, 1, 1, rocket_speed );
			}
			else{
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("VEHICLE_WEAPON_PLAYER_LAZER"), PedID, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("VEHICLE_WEAPON_PLAYER_LAZER"), PedID, 1, 1, rocket_speed );
			}
			printf("Fired Vehicle Savage Bullets \n");
		}
	}
}

void fwrocketloop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	int PedID;
	if (is_ped_in_any_vehicle(PedID = PlayerPedId()))
	{

		if ( is_control_just_pressed( 2, 200 ) && !is_ped_on_foot(PedID)) // ls
		{
			printf("Pressed LS\n");
			int vehicle = GetCarCharIsIn(PedID, 0 ),
			Model = get_entity_model(vehicle);
			printf("Got vehicle %i \n", vehicle);
			get_model_dimensions( Model, dim_min, dim_max );
			printf("Got dimensions\n");

			if ( is_control_pressed( 2, 198 ) ) // rs
			{
				printf("Pressed RS\n");
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
				printf("Got offset\n");
			}
			else
			{
				printf("Got vehicle %i \n", vehicle);
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				printf("Got offset 2\n");
				if ( Model == get_hash_key("surfer") || Model == get_hash_key("blazer") )
				{
					printf("Checked entity model\n"); 
					targetpos1[2] += 3.5f;
					targetpos2[2] += 3.5f;
				}
				else
				{
					printf("Checked entity model 2\n");
					targetpos1[2]--;
					targetpos2[2]--;
				}
			}
			float vSpeed = get_entity_speed( vehicle );
			if ( ( vSpeed * vSpeed ) > 1500 )
			{
				rocket_speed = ( vSpeed * vSpeed ) + 100;
				printf("Got and multiplied rocket / car speed\n");
			}
			else
			{
				rocket_speed = 1500;
			}
			if (custom){
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_FIREWORK"), rocketid, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_FIREWORK"), rocketid, 1, 1, rocket_speed );
			}
			else{
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_FIREWORK"), PedID, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_FIREWORK"), PedID, 1, 1, rocket_speed );
			}
			printf("Fired vehicle rockets \n");
		}
	}
}

void vehicleFlareLoop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	int PedID;
	if (is_ped_in_any_vehicle(PedID = PlayerPedId()))
	{

		if ( is_control_just_pressed( 2, 200 ) && !is_ped_on_foot(PedID)) // ls
		{
			printf("Pressed LS\n");
			int vehicle = GetCarCharIsIn(PedID, 0 ),
			Model = get_entity_model(vehicle);
			printf("Got vehicle %i \n", vehicle);
			get_model_dimensions( Model, dim_min, dim_max );
			printf("Got dimensions\n");

			if ( is_control_pressed( 2, 198 ) ) // rs
			{
				printf("Pressed RS\n");
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
				printf("Got offset\n");
			}
			else
			{
				printf("Got vehicle %i \n", vehicle);
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				printf("Got offset 2\n");
				if ( Model == get_hash_key("surfer") || Model == get_hash_key("blazer") )
				{
					printf("Checked entity model\n"); 
					targetpos1[2] += 3.5f;
					targetpos2[2] += 3.5f;
				}
				else
				{
					printf("Checked entity model 2\n");
					targetpos1[2]--;
					targetpos2[2]--;
				}
			}
			float vSpeed = get_entity_speed( vehicle );
			if ( ( vSpeed * vSpeed ) > 1500 )
			{
				rocket_speed = ( vSpeed * vSpeed ) + 100;
				printf("Got and multiplied rocket / car speed\n");
			}
			else
			{
				rocket_speed = 1500;
			}
			if (custom){
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_FLAREGUN"), rocketid, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_FLAREGUN"), rocketid, 1, 1, rocket_speed );
			}
			else{
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_FLAREGUN"), PedID, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_FLAREGUN"), PedID, 1, 1, rocket_speed );
			}
			printf("Fired Vehicle Flares \n");
		}
	}
}

void creatorRocketLoop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	    int PedID;
		PedID = PlayerPedId();

		  if ( is_control_just_pressed( 2, 200 ) && is_ped_on_foot(PedID)) // LS
		  {
			int vehicle = PedID,
			Model = get_entity_model(vehicle);
			get_model_dimensions( Model, dim_min, dim_max );

			if ( is_control_pressed( 2, 198 ) ) // RS
			{
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
			}
			else
			{
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				
					targetpos1[2]--;
					targetpos2[2]--;
			}
				rocket_speed = 1500;

			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_VEHICLE_ROCKET"), PedID, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_VEHICLE_ROCKET"), PedID, 1, 1, rocket_speed );
	      }
}

void creatorFlaresLoop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	    int PedID;
		PedID = PlayerPedId();

		  if ( is_control_just_pressed( 2, 200 ) && is_ped_on_foot(PedID)) // LS
		  {
			int vehicle = PedID,
			Model = get_entity_model(vehicle);
			get_model_dimensions( Model, dim_min, dim_max );

			if ( is_control_pressed( 2, 198 ) ) // RS
			{
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
			}
			else
			{
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				
					targetpos1[2]--;
					targetpos2[2]--;
			}
				rocket_speed = 1500;

			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_FLAREGUN"), PedID, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_FLAREGUN"), PedID, 1, 1, rocket_speed );
	      }
}

void rocketloop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	int PedID;
	if (is_ped_in_any_vehicle(PedID = PlayerPedId()))
	{

		if ( is_control_just_pressed( 2, 200 ) && !is_ped_on_foot(PedID)) // ls
		{
			printf("Pressed LS\n");
			int vehicle = GetCarCharIsIn(PedID, 0 ),
			Model = get_entity_model(vehicle);
			printf("Got vehicle %i \n", vehicle);
			get_model_dimensions( Model, dim_min, dim_max );
			printf("Got dimensions\n");

			if ( is_control_pressed( 2, 198 ) ) // rs
			{
				printf("Pressed RS\n");
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
				printf("Got offset\n");
			}
			else
			{
				printf("Got vehicle %i \n", vehicle);
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				printf("Got offset 2\n");
				if ( Model == get_hash_key("surfer") || Model == get_hash_key("blazer") )
				{
					printf("Checked entity model\n"); 
					targetpos1[2] += 3.5f;
					targetpos2[2] += 3.5f;
				}
				else
				{
					printf("Checked entity model 2\n");
					targetpos1[2]--;
					targetpos2[2]--;
				}
			}
			float vSpeed = get_entity_speed( vehicle );
			if ( ( vSpeed * vSpeed ) > 1500 )
			{
				rocket_speed = ( vSpeed * vSpeed ) + 100;
				printf("Got and multiplied rocket / car speed\n");
			}
			else
			{
				rocket_speed = 1500;
			}
			if (custom){
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_VEHICLE_ROCKET"), rocketid, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_VEHICLE_ROCKET"), rocketid, 1, 1, rocket_speed );
			}
			else{
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 250, 0, get_hash_key("WEAPON_VEHICLE_ROCKET"), PedID, 1, 1, rocket_speed );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 250, 0, get_hash_key("WEAPON_VEHICLE_ROCKET"), PedID, 1, 1, rocket_speed );
			}
			printf("Fired vehicle rockets \n");
		}
	}
}

bool superMG;
int ToggleSuperMG(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!superMG) {
	ShowMessageOnScreen("~g~ Vehicle Super Machineguns On, Press X To Shoot them!");
	superMG = true;
	requested = false;
	custom = false;
	}
	else if (superMG) {
	ShowMessageOnScreen("~g~ Vehicle Super Machineguns Off");
	superMG = false;
	custom = false;
	}
	//ShowMessageOnScreen("~g~ Vehicle MG's are currently not working");
	return 0;
}

void superMGloop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	int PedID;
	if (is_ped_in_any_vehicle(PedID = PlayerPedId()))
	{

		if (menuInputHandler->XButtonDown() && !is_ped_on_foot(PedID)) // ls
		{
			//printf("Pressed LS\n");
			int vehicle = GetCarCharIsIn(PedID, 0 ),
			Model = get_entity_model(vehicle);
			//printf("Got vehicle %i \n", vehicle);
			get_model_dimensions( Model, dim_min, dim_max );
			//printf("Got dimensions\n");

			if ( is_control_pressed( 2, 198 ) ) // rs
			{
				//printf("Pressed RS\n");
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
				//printf("Got offset\n");
			}
			else
			{
				//printf("Got vehicle %i \n", vehicle);
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				//printf("Got offset 2\n");
				if ( Model == get_hash_key("surfer") || Model == get_hash_key("blazer") )
				{
					//printf("Checked entity model\n"); 
					targetpos1[2] += 3.5f;
					targetpos2[2] += 3.5f;
				}
				else
				{
					//printf("Checked entity model 2\n");
					targetpos1[2]--;
					targetpos2[2]--;
				}
			}
			float vSpeed = get_entity_speed( vehicle );
			if ( ( vSpeed * vSpeed ) > 1500 )
			{
				rocket_speed = ( vSpeed * vSpeed ) + 100;
				//printf("Got and multiplied rocket / car speed\n");
			}
			else
			{
				rocket_speed = 1500;
			}
			if (custom){
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 10, 1, get_hash_key("WEAPON_REMOTESNIPER"), rocketid, 0, 1, -1082130432 );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 10, 1, get_hash_key("WEAPON_REMOTESNIPER"), rocketid, 0, 1, -1082130432 );
			}
			else{
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 10, 1, get_hash_key("WEAPON_REMOTESNIPER"), PedID, 0, 1, -1082130432 );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 10, 1, get_hash_key("WEAPON_REMOTESNIPER"), PedID, 0, 1, -1082130432 );
			}
			//printf("Fired vehicle rockets \n");
		}
	}
}

bool Mini;
int ToggleMini(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!Mini) {
	ShowMessageOnScreen("~g~ Vehicle Machineguns On, Press X To Shoot them!");
	Mini = true;
	requested = false;
	custom = false;
	}
	else if (Mini) {
	ShowMessageOnScreen("~g~ Vehicle Machineguns Off");
	Mini = false;
	custom = false;
	}
	return 0;
}

void miniloop() {
	float dim_min[3],
		dim_max[3],
		targetpos1[3],
		targetpos2[3],
		launchpos1[3],
		launchpos2[3],
		rocket_speed;
	int PedID;
	if (is_ped_in_any_vehicle(PedID = PlayerPedId()))
	{

		if (menuInputHandler->XButtonDown() && !is_ped_on_foot(PedID)) // ls
		{
			//printf("Pressed LS\n");
			int vehicle = GetCarCharIsIn(PedID, 0 ),
			Model = get_entity_model(vehicle);
			//printf("Got vehicle %i \n", vehicle);
			get_model_dimensions( Model, dim_min, dim_max );
			//printf("Got dimensions\n");

			if ( is_control_pressed( 2, 198 ) ) // rs
			{
				//printf("Pressed RS\n");
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos1 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 0.5f, 0.0f, launchpos2 ) ;
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] - 300.5f, 0.5f, targetpos2 );
				//printf("Got offset\n");
			}
			else
			{
				//printf("Got vehicle %i \n", vehicle);
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 0.5f, 0.0f, launchpos2 );
				get_offset_from_entity_in_world_coords( vehicle, dim_min[0] - 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos1 );
				get_offset_from_entity_in_world_coords( vehicle, dim_max[0] + 0.2f, dim_min[1] + 300.5f, 0.5f, targetpos2 );
				//printf("Got offset 2\n");
				if ( Model == get_hash_key("surfer") || Model == get_hash_key("blazer") )
				{
					//printf("Checked entity model\n"); 
					targetpos1[2] += 3.5f;
					targetpos2[2] += 3.5f;
				}
				else
				{
					//printf("Checked entity model 2\n");
					targetpos1[2]--;
					targetpos2[2]--;
				}
			}
			float vSpeed = get_entity_speed( vehicle );
			if ( ( vSpeed * vSpeed ) > 1500 )
			{
				rocket_speed = ( vSpeed * vSpeed ) + 100;
				//printf("Got and multiplied rocket / car speed\n");
			}
			else
			{
				rocket_speed = 1500;
			}
			if (custom){
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 10, 0, get_hash_key("WEAPON_ASSAULTRIFLE"), rocketid, 1, 1, -1082130432 );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 10, 0, get_hash_key("WEAPON_ASSAULTRIFLE"), rocketid, 1, 1, -1082130432 );
			}
			else{
			shoot_single_bullet_between_coords( launchpos1, targetpos1, 10, 0, get_hash_key("WEAPON_ASSAULTRIFLE"), PedID, 1, 1, -1082130432 );
			shoot_single_bullet_between_coords( launchpos2, targetpos2, 10, 0, get_hash_key("WEAPON_ASSAULTRIFLE"), PedID, 1, 1, -1082130432 );
			}
			//printf("Fired vehicle rockets \n");
		}
	}
}

void nosloop() {
	if (menuInputHandler->BButtonLSDown()) {
		int Handle = GetCarCharIsIn(PlayerPedId(), 0);
		if(Handle != 0)
		{
			if (is_vehicle_on_all_wheels(Handle)){
			set_vehicle_boost_active(Handle, 1);
			unk_0x1D980479("RaceTurbo", 0, 0);
			apply_force_to_entity(Handle, true, 0, 3.0f, 0, 0, 0, 0, true, true, true, true, false, true);
			set_vehicle_boost_active(Handle, 0);
			}
		}
	}
}

DWORD WINAPI KeyboardThread(LPVOID Value)
{
	int Index = (int)Value;
	switch(Index)
	{
	case 0:
		if (custom_per) {
			ZeroMemory(&Overlapped2, sizeof(Overlapped2));
			XShowKeyboardUI(0, VKBD_LATIN_NUMERIC, L"", L"Custom Performance", L"Please enter your desired performance 0 - 999", Username2, 4, &Overlapped2 );
			while(!XHasOverlappedIoCompleted(&Overlapped2))
				Sleep(100);
			float result = _wtof(Username2);
			printf("Entered Float = %f \n", result);
			set_vehicle_rpm(GetCarCharIsIn(PlayerPedId(), 0), result);
			custom_per = false;
		}
	    break;
	case 1:
	    if (custom_plate) {
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
	    XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Custom Plate Shop", L"Please enter your desired plate", Username2, 9, &Overlapped2 );
	    while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		char str[9];
        wcstombs(str, Username2, 9);
		set_number_plate(GetCarCharIsIn(PlayerPedId(), 0), str);
		custom_plate = false;
		}
		break;
	case 2:
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
	    XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Custom Model Changer", L"Please enter your desired model name (Example U_M_M_Jesus_01) \nNOTE: You may need to enter model more then once for it to register!", Username2, 50, &Overlapped2 );
	    while(!XHasOverlappedIoCompleted(&Overlapped2))
		Sleep(100);
		char str2[20];
        wcstombs(str2, Username2, 20);
		scriptsetModel = get_hash_key(str2);
	break;
	case 3:
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
	    XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Custom Vehicles", L"Please enter your desired vehicle name (Example pony2) \nNOTE: You may need to enter model more then once for it to register!", Username2, 50, &Overlapped2 );
	    while(!XHasOverlappedIoCompleted(&Overlapped2))
		Sleep(100);
		char str1[20];
        wcstombs(str1, Username2, 20);
		car = true;
		scriptsetModel = get_hash_key(str1);
	break;
	case 4:
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
	    XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Custom Object", L"Please enter your desired object name (Example p_spinning_anus_s) \nNOTE: You may need to enter model more then once for it to register!", Username2, 50, &Overlapped2 );
	    while(!XHasOverlappedIoCompleted(&Overlapped2))
		Sleep(100);
		char str3[20];
        wcstombs(str3, Username2, 20);
		objectspawn = true;
	    normalspawn = true;
	    model = get_hash_key(str3);
	break;
	case 5:
		if(custom_rankMP0){
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
		XShowKeyboardUI(0, VKBD_LATIN_NUMERIC, L"", L"Custom Rank (Character 1)", L"Please enter desired XP \nExample: Rank 120 = 2,165,850 \nMax Level 8000 = 1,787,576,850", Username2, 11, &Overlapped2 );
		while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		float result = _wtof(Username2);
		printf("Entered Float = %f \n", result);
		set_stat_int(get_hash_key("MP0_CHAR_XP_FM"), result);
		custom_rankMP0 = false;
		}
	break;
	case 6:
		if(custom_rankMP1){
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
		XShowKeyboardUI(0, VKBD_LATIN_NUMERIC, L"", L"Custom Rank (Character 2)", L"Please enter desired XP \nExample: Rank 120 = 2165850 \nMax Level 8000 = 1,787,576,850", Username2, 11, &Overlapped2 );
		while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		float result = _wtof(Username2);
		printf("Entered Float = %f \n", result);
		set_stat_int(get_hash_key("MP1_CHAR_XP_FM"), result);
		custom_rankMP1 = false;
		}
	break;
	case 7:
		if(custom_rankMP2){
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
		XShowKeyboardUI(0, VKBD_LATIN_NUMERIC, L"", L"Custom Rank (Character 3)", L"Please enter desired XP \nExample: Rank 120 = 2165850 \nMax Level 8000 = 1,787,576,850", Username2, 11, &Overlapped2 );
		while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		float result = _wtof(Username2);
		printf("Entered Float = %f \n", result);
		set_stat_int(get_hash_key("MP2_CHAR_XP_FM"), result);
		custom_rankMP2 = false;
		}
	break;
	case 8:
		if(custom_money){
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
		XShowKeyboardUI(0, VKBD_LATIN_NUMERIC, L"", L"Custom Money", L"Please enter desired Money \nRange: 1 - 999,999,999", Username2, 10, &Overlapped2 );
		while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		float result = _wtof(Username2);
		printf("Entered Float = %f \n", result);
		((void(*)(int,int,int))0x82C616D8)(result, 0, 1);
		ShowMessageOnScreen("~g~ You received: ", result, " $");
		custom_money = false;
		}
	break;
	case 9:
		if(custom_teleport){
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
		XShowKeyboardUI(0, VKBD_LATIN_IP_ADDRESS, L"", L"Custom Teleporter", L"Enter the X Coordinates", Username2, 12, &Overlapped2 );
		while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		float result1 = _wtof(Username2);
		printf("Entered Float = %f \n", result1);
		XShowKeyboardUI(0, VKBD_LATIN_IP_ADDRESS, L"", L"Custom Teleporter", L"Enter the Y Coordinates", Username3, 12, &Overlapped2 );
		while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		float result2 = _wtof(Username3);
		printf("Entered Float = %f \n", result2);
		XShowKeyboardUI(0, VKBD_LATIN_IP_ADDRESS, L"", L"Custom Teleporter", L"Enter the Z Coordinates", Username4, 12, &Overlapped2 );
		while(!XHasOverlappedIoCompleted(&Overlapped2))
			Sleep(100);
		float result3 = _wtof(Username4);
		printf("Entered Float = %f \n", result3);
		float x,y,z; 
		x = result1, y = result2, z = result3;
		int myhandle = GetPlayerHandle(PlayerId());
		int myvehicle;
		if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else 
		{
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
		}
		ShowMessageOnScreen("~g~ Teleported to Custom Position");
		return 0;
		custom_teleport = false;
		}
		break;
		/*case 10:
		 if (custom_marquee) {
		ZeroMemory(&Overlapped2, sizeof(Overlapped2));
	    XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Custom Marquee", L"Please enter desired text. I would suggest max of 50 characters including spaces.", Username2, 9, &Overlapped2 );
	    while(!XHasOverlappedIoCompleted(&Overlapped2))
		Sleep(100);
		char str[50];
        wcstombs(str, Username2, 9);
		marqueeText = str;
		custom_marquee = false;
		}
	break;*/
	}
	return 0;
}

int TogglePerf(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	custom_per = true;
	CreateThread(0, 0, KeyboardThread, 0, 0, 0);
	return 0;
}

int CustomModel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	//scriptsetModel = -1026527405;//0x9CF26183;
	wtf = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)2, 0, 0);
	return 0;
}

int CustomVeh(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
	CreateThread(0, 0, KeyboardThread, (LPVOID)3, 0, 0);
	return 0;
}

int CustomObject(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//0x64611296 Alien 0x9CF26183 Playboy (naked)
	CreateThread(0, 0, KeyboardThread, (LPVOID)4, 0, 0);
	return 0;
}
int CustomRankMP0(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	custom_rankMP0 = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)5, 0, 0); //Character 1
	return 0;
}
int CustomRankMP1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	custom_rankMP1 = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)6, 0, 0); //Character 2
	return 0;
}
int CustomRankMP2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	CreateThread(0, 0, KeyboardThread, (LPVOID)7, 0, 0); //Character 3
	custom_rankMP2 = true;
	return 0;
}
int GiveCustomMoney(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters){
	custom_money = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)8, 0, 0); //Give Custom Money all chars
	return 0;
}
int TeleCustom(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemTest, void *functionParameters){
	custom_teleport = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)9, 0, 0);
	return 0;
}
void supercar() {
}

bool speedon = false;
int Speed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!speedon) {
	*(float*)0x82003A5C = 0.30f;
	ShowMessageOnScreen("~g~ Jet Handling Turned On");
	speedon = true;
	}
	else {
	*(float*)0x82003A5C = 0.16666667f;	
	ShowMessageOnScreen("~g~ Jet Handling Turned Off");
	speedon = false;
	}
	return 0;
}

int Speed2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!speedon) {
	*(float*)0x82003A5C = 0.50f;
	ShowMessageOnScreen("~y~ Super Grip: ~g~ON!");
	speedon = true;
	}
	else {
	*(float*)0x82003A5C = 0.16666667f;	
	ShowMessageOnScreen("~y~ Super Grip: ~r~OFF!");
	speedon = false;
	}
	return 0;
}

int GiveCash(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(999999999, 0, 1);
	ShowMessageOnScreen("~g~ Cash given!");
	return 0;
}

int Give1Mil(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(1000000, 0, 1);
	ShowMessageOnScreen("~g~ You have received: 1,000,000 $");
	return 0;
}

int Give25Mil(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(25000000, 0, 1);
	ShowMessageOnScreen("~g~ You have received: 25,000,000 $");
	return 0;
}

int Give50Mil(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(50000000, 0, 1);
	ShowMessageOnScreen("~g~ You have received: 50,000,000 $");
	return 0;
}

int Give250Mil(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(250000000, 0, 1);
	ShowMessageOnScreen("~g~ You have received: 250,000,000 $");
	return 0;
}

int Give500Mil(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(500000000, 0, 1);
	ShowMessageOnScreen("~g~ You have received: 500,000,000 $");
	return 0;
}

int Give750Mil(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(750000000, 0, 1);
	ShowMessageOnScreen("~g~ You have received: 750,000,000 $");
	return 0;
}

int GiveMaxMoney(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	//int Addr = 0x83AF8068;
	//*(__int64 *)(*(int *)(*(int *)(*(int *)Addr + 4) + ((*(int *)(Addr + 4) << 3) + 4)) + 8) = 999999999;
	((void(*)(int,int,int))0x82C616D8)(999999999, 0, 1);
	ShowMessageOnScreen("~g~ You have received: 1,000,000,000 $");
	return 0;
}

int AttachPedHandle;
int PlayersHandle[2];
bool AttachTo = false;
int AttachBouy(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	AttachPedHandle = selectedMenuIndexes->operator[](1);
	PlayersHandle[0] = GetPlayerHandle(AttachPedHandle);
	PlayersHandle[1] = PlayerPedId();
		if (PlayersHandle[1] == PlayersHandle[0])
	{
		ShowMessageOnScreen("~g~ You are trying to attach to yourself retard, If we allowed this we would freeze.");
		return 0;
	}
		if(!AttachTo){
		  attach_entity_to_entity(PlayersHandle[1], PlayersHandle[0], -1, 0, -0.3, 0, 0, 0, 0);
		  AttachTo = true;
		  ShowMessageOnScreen("~g~Attached To Player!");
		}
		else if(AttachTo){
		  detach_entity(PlayerPedId());
		  AttachTo = false;
		  ShowMessageOnScreen("~g~Detached From Player");
		}
	return 0;
}

int AttachPedHandle2;
int PlayerHandle[2];
int AttachToPlayerStelios(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	AttachPedHandle2 = selectedMenuIndexes->operator[](1);
	PlayerHandle[0] = GetPlayerHandle(AttachPedHandle2);
	PlayerHandle[1] = PlayerPedId();
		if (PlayerHandle[1] == PlayerHandle[0])
	{
		ShowMessageOnScreen("~g~ You are trying to attach to yourself retard, If we allowed this we would freeze.");
		return 0;
	}
	attach_entity_to_entity(PlayerHandle[1], PlayerHandle[0], -1, 0, -0.3, 0, 0, 0, 0);
	animdict = "mini@prostitutes@sexnorm_veh";
	anim = "sex_loop_male";
	animid = PlayerId();
	vm_anim = true;
	ShowMessageOnScreen("~g~ Attached to player with animation Idea By: Stelio Kontos!");
	return 0;
}

bool pedobject;
int spawnedobject;
bool spawn_egg = false;
int AttachBouy2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_egg = true;
	spawnedobject = 1803116220;
	z10 = 1.0;
	ShowMessageOnScreen("~g~ Attached egg to player!");
	return 0;
}

bool spawn_sword = false;
int Sword(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
//#ifdef PRIVATE
	GiveWeaponDelayed(PlayerPedId(), 0x99B507EA, 9999, 1); // knife
	//spawnedobject = get_hash_key("prop_boxing_glove_01");
	spawnedobject = get_hash_key("prop_cs_katana_01");
	spawn_sword = true;
	ShowMessageOnScreen("~g~ You have been given a sword!");
//#else
	//ShowMessageOnScreen("~r~ Sorry this is only available in the private version!");
//#endif
	return 0;
}

bool spawn_glove = false;
int Glove(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters)
{
//#ifdef PRIVATE
	spawnedobject = get_hash_key("prop_boxing_glove_01");
	spawn_glove = true;
	ShowMessageOnScreen("~g~ You have been given a boxing glove!");
	//#else
	//ShowMessageOnScreen("~r~ Sorry this is only available in the private version!");
//#endif
	return 0;
}

bool spawn_cone = false;
int AttachCone(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_cone = true;
	spawnedobject = -534360227;
	//z10 = 0.7;
	ShowMessageOnScreen("~g~ Attached cone to player!");
	return 0;
}

bool spawn_sprinkler = false;
int AttachSprinkler(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_sprinkler = true;
	spawnedobject = 1864388154;
	ShowMessageOnScreen("~g~ Attached sprinkler to player!");
	return 0;
}

bool spawn_oldboat = false;
int AttachOldBoat(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_oldboat = true;
	spawnedobject = -1685705098;
	ShowMessageOnScreen("~g~ Attached old boat to player!");
	return 0;
}

bool spawn_beachbench = false;
int AttachBeachBench(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_beachbench = true;
	spawnedobject = -403891623;
	ShowMessageOnScreen("~g~ Attached beach bench to player!");
	return 0;
}

bool spawn_dumpster = false;
int AttachDumpster(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_dumpster = true;
	spawnedobject = 1748268526;
	ShowMessageOnScreen("~g~ Attached dumpster to player!");
	return 0;
}

bool spawn_trashcan = false;
int AttachTrashCan(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_trashcan = true;
	spawnedobject = -1096777189;
	ShowMessageOnScreen("~g~ Attached trash can to player!");
	return 0;
}

bool spawn_umbrella = false;
int AttachUmbrella(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_umbrella = true;
	spawnedobject = -592861175;
	ShowMessageOnScreen("~g~ Attached umbrella to player!");
	return 0;
}

bool spawn_streetlamp = false;
int AttachStreetLamp(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_streetlamp = true;
	spawnedobject = -1063472968;
	ShowMessageOnScreen("~g~ Attached street lamp to player!");
	return 0;
}

bool spawn_constbarrel = false;
int AttachConstBarrel(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_constbarrel = true;
	spawnedobject = 2080595106;
	ShowMessageOnScreen("~g~ Attached construction barrel to player!");
	return 0;
}

bool spawn_dummyplane = false;
int AttachDummyPlane(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_dummyplane = true;
	spawnedobject = -473036318;
	ShowMessageOnScreen("~g~ Attached dummy plane to player!");
	return 0;
}

bool spawn_dummycar = false;
int AttachDummyCar(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_dummycar = true;
	spawnedobject = -1007599668;
	ShowMessageOnScreen("~g~ Attached dummy car to player!");
	return 0;
}

bool spawn_dickpole = false;
int AttachDickPole(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	spawn_dickpole = true;
	//spawnedobject = -994492850;
	spawnedobject = -839348691;
	ShowMessageOnScreen("~g~ Attached dick pole to player!");
	return 0;
}

bool rapid_fire = false;
int RapidFire(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!rapid_fire) {
    ShowMessageOnScreen("~g~ Firework guns on");
	rapid_fire = true;
	}
	else if (rapid_fire)
	{
	ShowMessageOnScreen("~g~ Firework guns off");
	rapid_fire = false;
	}
	return 0;
}

bool firework_gun = false;
int FireworkGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!firework_gun) {
	fexp1 = "scr_indep_firework_starburst";
	fr = 1.0, fg = 0, fb = 0;
    ShowMessageOnScreen("~g~ Firework guns on");
	fwsize = 1.0;
	firework_gun = true;
	}
	else if (firework_gun)
	{
	ShowMessageOnScreen("~g~ Firework guns off");
	firework_gun = false;
	}
	return 0;
}

/*void set_self_ammo_as_max_ammo()
{
 Var32 var_0;
 Var32 var_1;
 var_0 = int get_current_weapon_hash();
 Stack.Push( set_ammo_in_clip( player_ped_id(), var_0, get_max_ammo_in_clip( player_ped_id(), var_0, 1 ) ) );
 if ( is_ped_shooting( player_ped_id() ) )
 {
  if ( (((GetHash("WEAPON_RPG") == var_0 || GetHash("WEAPON_STINGER") == var_0) || GetHash("WEAPON_PASSENGER_ROCKET") == var_0) || GetHash("WEAPON_STUNGUN") == var_0) )
  {
   set_current_ped_weapon( player_ped_id(), GetHash("WEAPON_MICROSMG"), 1 );
   set_current_ped_weapon( player_ped_id(), var_0, 1 );
  }
 }
}*/


bool creator_obj = false;
int AttachCreator(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	if (Create) {
	creator_obj = true;
	ShowMessageOnScreen("~g~ Attached object to player!");
	}
	else { ShowMessageOnScreen("~r~ You can't use this unless you have object selected using creator mode");
}
	return 0;
}

bool detachcreator_obj = false;
int ObjectDetach(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	if (Create) {
	detachcreator_obj = true;
	ShowMessageOnScreen("~g~ Detached object from player, if not click it a few more times!");
	}
	else { ShowMessageOnScreen("~r~ You can't use this unless you have object selected using creator mode");
}
	return 0;
}

int AttachWeed(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	pedobject = true;
	spawnedobject = 452618762;
	z10 = 0;
	ShowMessageOnScreen("~g~ Attached weed to player!");
	return 0;
}

int AttachNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	animid = selectedMenuIndexes->operator[](1);
	pedobject = true;
	spawnedobject = 1433474877;
	z10 = 0;
	ShowMessageOnScreen("~g~ Attached beer neon to player!");
	return 0;
}//

int PiggieBack(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	AttachPedHandle = selectedMenuIndexes->operator[](1);
	attach_entity_to_entity(PlayerPedId(), GetPlayerHandle(AttachPedHandle), -1, 0, -0.3, 0, 0, 0, 0);
	animdict = "mini@prostitutes@sexnorm_veh";
	anim = "bj_loop_male";
	animid = PlayerId();
	vm_anim = true;
	ShowMessageOnScreen("~g~ Piggy back!");
	return 0;
}
bool funnyshit = false;
int FuckPlayerHandle[2];
bool Fuckp = false;
int FuckPlayer(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	AttachPedHandle = selectedMenuIndexes->operator[](1);
	FuckPlayerHandle[0] = GetPlayerHandle(AttachPedHandle);
	FuckPlayerHandle[1] = PlayerPedId();
		if (FuckPlayerHandle[1] == FuckPlayerHandle[0])
	{
		ShowMessageOnScreen("~g~ You are trying to fuck yourself retard, If we allowed this we would freeze.");
		return 0;
	}
		if(!Fuckp){
			attach_entity_to_entity(FuckPlayerHandle[1], FuckPlayerHandle[0], -1, 0, -0.3, 0, 0, 0, 0);
			ShowMessageOnScreen("~g~Attached To Player and Activate Fuck Animation!");
			animdict = "rcmpaparazzo_2";
	        anim = "shag_loop_a";
	        animid = PlayerId();
	        vm_anim = true;
			Fuckp = true;
		}
		else if(Fuckp){
			detach_entity(PlayerPedId());
			clear_ped_tasks_immediately(PlayerPedId());
			ShowMessageOnScreen("~g~Detached From Player and Stopped Animation!");
			Fuckp = false;
		}
	ShowMessageOnScreen("~g~ Enjoy the fun!");
	return 0;
}

int ChopPiss1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@move";
	anim = "pee_right_enter";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ChopPiss2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@move";
	anim = "pee_right_idle";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ChopPiss3(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@move";
	anim = "pee_right_exit";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ChopDump(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@move";
	anim = "dump_loop";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ChopAttack2(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@melee@streamed_core@";
	anim = "attack";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int ChopAttack1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int subMenuIndex = selectedMenuIndexes->operator[](1);
	animdict = "creatures@rottweiler@melee@streamed_core@";
	anim = "ground_attack_0";
	animid = PlayerId();
	vm_anim = true;
	return 0;
}

int Detach(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	detach_entity(PlayerPedId());
	ShowMessageOnScreen("~g~ Detached");
	return 0;
}
	float z = 0;
	float unk = 4.0;
	float unk1 = 2.5;
int RedNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	neonr = 255, neong = 0, neonb = 0;
	z = 0;
	unk = 4.0;
	unk1 = 2.5;
	return 0;
}

int GreenNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	neonr = 0, neong = 255, neonb = 0;
	z = 0;
	unk = 4.0;
	unk1 = 2.5;
	return 0;
}
int BlueNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	neonr = 0, neong = 0, neonb = 255;
	z = 0;
	unk = 4.0;
	unk1 = 2.5;
	return 0;
}
int PinkNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	neonr = 255, neong = 51, neonb = 255;
	z = 0;
	unk = 4.0;
	unk1 = 2.5;
	return 0;
}
int PurpleNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	neonr = 153, neong = 0, neonb = 153;
	z = 0;
	unk = 4.0;
	unk1 = 2.5;
	return 0;
}
int OrangeNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	neonr = 255, neong = 128, neonb = 0;
	z = 0;
	unk = 4.0;
	unk1 = 2.5;
	return 0;
}
int CyanNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	neonr = 0, neong = 204, neonb = 204;
	z = 0;
	unk = 4.0;
	unk1 = 2.5;
	return 0;
}

bool neons = false;
int ToggleNeon(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!neons) {
    neons = true;
	ShowMessageOnScreen("~g~ Neons: ON, Only you can see them. :(");
	}
	else if (neons) {
	neons = false;
	ShowMessageOnScreen("~g~ Neons: OFF");
	}
	return 0;
}

void neonloop() {
	float Pos[3];
	GetEntityCoords(GetCarCharIsIn(PlayerPedId(), 0), Pos);
	draw_light_with_range(Pos[0], Pos[1], Pos[2] - z, neonr, neong, neonb, unk, unk1);
}

int PlateThreadValue = -1;
int ChangePlate1(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	custom_plate = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)1, 0, 0);
	return 0;
}

int CustomMarquee(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	custom_marquee = true;
	CreateThread(0, 0, KeyboardThread, (LPVOID)10, 0, 0);
	return 0;
}

int StelioLicense(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	int Veh = GetCarCharIsIn(PlayerPedId(), 0);
	set_number_plate(Veh, "HASTER");
	return 0;
}

/*bool tpGun = false;
int TeleportGun(int selectedIndex, vector<int> *selectedMenuIndexes, char *itemText, void *functionParameters) {
	if (!tpGun){
		tpGun = true;
	}
	else if (tpGun){
		tpGun = false;
	}
	return 0;
}*/


// for handling crashes
LONG WINAPI Exception(struct _EXCEPTION_POINTERS *e) {
	printf("GTAV Menu crashed for some reason");

	HalReturnToFirmware(HalRebootQuiesceRoutine);

	return 0;
}

// Our menu setup function
void SetupMenu() {
	// Allocate our input handler
	menuInputHandler = new Input;

	// Setup menu
	mainMenu = new GTAVMenu;
	quickOptionsMenu = new GTAVMenu;
	playerOptionsMenu = new GTAVMenu;
	vehicleOptionMenu = new GTAVMenu;
	VehPaintMenu = new GTAVMenu;
	VehPaintMenu2 = new GTAVMenu;
	RimPaint = new GTAVMenu;
	weaponOptionsMenu = new GTAVMenu;
	onlinePlayers = new GTAVMenu;
	blamePlayers = new GTAVMenu;
	onlinePlayersSubMenu = new GTAVMenu;
	CarSpawner = new GTAVMenu;
	CarSpawner2 = new GTAVMenu;
	CarSpawnerMenu0 = new GTAVMenu;
	CarSpawnerMenu0P2 = new GTAVMenu;
	CarSpawnerMenu1 = new GTAVMenu;
	CarSpawnerMenu2 = new GTAVMenu;
	CarSpawnerMenu2P2 = new GTAVMenu;
	CarSpawnerMenu3 = new GTAVMenu;
	CarSpawnerMenu4 = new GTAVMenu;
	CarSpawnerMenu4P2 = new GTAVMenu;
	CarSpawnerMenu5 = new GTAVMenu;
	CarSpawnerMenu6 = new GTAVMenu;
	CarSpawnerMenu7 = new GTAVMenu;
	CarSpawnerMenu8 = new GTAVMenu;
	CarSpawnerMenu8P2 = new GTAVMenu;
	CarSpawnerMenu9 = new GTAVMenu;
	CarSpawnerMenu9P2 = new GTAVMenu;
	CarSpawnerMenu10 = new GTAVMenu;
	CarSpawnerMenu11 = new GTAVMenu;
	CarSpawnerMenu12 = new GTAVMenu;
	CarSpawnerMenu13 = new GTAVMenu;
	CarSpawnerMenu14 = new GTAVMenu;
	CarSpawnerMenu14P2 = new GTAVMenu;
	CarSpawnerMenu15 = new GTAVMenu;
	CarSpawnerMenu16 = new GTAVMenu;
	CarSpawnerMenu17 = new GTAVMenu;
	CarSpawnerMenu18 = new GTAVMenu;
	CarSpawnerMenu19 = new GTAVMenu;
	CarSpawnerMenu20 = new GTAVMenu;
	CarSpawnerMenu20P2 = new GTAVMenu;
	CarSpawnerMenu21 = new GTAVMenu;
	CarSpawnerMenu22 = new GTAVMenu;
	CarSpawnerMenu23 = new GTAVMenu;
	OnlinePlayerBasicOptions = new GTAVMenu;
	OnlinePlayerVehicleOptions = new GTAVMenu;
	OnlinePlayerTeleport = new GTAVMenu;
	NaughtyStuff = new GTAVMenu;
	KickPlayerStuff = new GTAVMenu;
	AllOnlinePlayers = new GTAVMenu;
	AllAtachObject = new GTAVMenu;
	GuardMenu = new GTAVMenu;
	TeleMenu = new GTAVMenu;
	TeleMenu2 = new GTAVMenu;
	ModelChanger = new GTAVMenu;
	ModelChanger2 = new GTAVMenu;
	ModelChanger100= new GTAVMenu;
	MiscOptions = new GTAVMenu; 
	AnimalModels = new GTAVMenu;
	ObjectAttachments = new GTAVMenu;
	CashDropOptions = new GTAVMenu;
	ExtraNaughtyStuff = new GTAVMenu;
	ObjectOptions = new GTAVMenu;
	ObjectOptions1 = new GTAVMenu;
	FunnyCarOptions = new GTAVMenu;
	ChopAnims = new GTAVMenu;
	Chr0m3 = new GTAVMenu;
	ModShop = new GTAVMenu;
	HornMenu = new GTAVMenu;
	HornMenu2 = new GTAVMenu;
	HornMenu3 = new GTAVMenu;
	TintMenu = new GTAVMenu;
	OpenMenu = new GTAVMenu;
	PerformanceMenu = new GTAVMenu;
	BodyMenu = new GTAVMenu;
	WheelMenu = new GTAVMenu;
	ArmourMenu = new GTAVMenu;
	HighEnd = new GTAVMenu;
	EngineMenu = new GTAVMenu;
	TransMenu = new GTAVMenu;
	BrakesMenu = new GTAVMenu;
	SuspMenu = new GTAVMenu;
	ExMenu = new GTAVMenu;
	FbMenu = new GTAVMenu;
	RbMenu = new GTAVMenu;
	SkMenu = new GTAVMenu;
	InteriorMenu = new GTAVMenu;
	HoodMenu = new GTAVMenu;
	LFenderMenu = new GTAVMenu;
	RFenderMenu = new GTAVMenu;
	RoofMenu = new GTAVMenu;
	GrillMenu = new GTAVMenu;
	SpoilerMenu = new GTAVMenu;
	Lowrider = new GTAVMenu;
	Muscle = new GTAVMenu;
	Offroad = new GTAVMenu;
	Sport = new GTAVMenu;
	SportMenu2 = new GTAVMenu;
	SUV = new GTAVMenu;
	Tuner = new GTAVMenu;
	TunerMenu2 = new GTAVMenu;
	Pegasus = new GTAVMenu;
	Weather = new GTAVMenu;
	SpeedoMeter = new GTAVMenu;
	Recovery = new GTAVMenu;
	RGMenu = new GTAVMenu;
	FWMenu = new GTAVMenu;
	VWMenu = new GTAVMenu;
	Character1 = new GTAVMenu;
	Character2 = new GTAVMenu;
	Character3 = new GTAVMenu;
	RankMenuMP0 = new GTAVMenu;
	RankMenuMP1 = new GTAVMenu;
	RankMenuMP2 = new GTAVMenu;
	MoneyMenuMP0 = new GTAVMenu;
	MoneyMenuMP1 = new GTAVMenu;
	MoneyMenuMP2 = new GTAVMenu;
	MovementMenu = new GTAVMenu;
	FavoriteModelsMenu = new GTAVMenu;
	AnimationMenu = new GTAVMenu;
	SportOptions = new GTAVMenu;
	SexOptions = new GTAVMenu;
	DanceOptions = new GTAVMenu;
	SuperHeroOptions = new GTAVMenu;
	MiscOptions2 = new GTAVMenu;
	CreatorVehicle = new GTAVMenu;
	ModelChanger300 = new GTAVMenu;
	ObjectSpawner2 = new GTAVMenu;
	MenuOptions = new GTAVMenu;
	MenuFonts = new GTAVMenu;
	TitleFonts = new GTAVMenu;
	ItemFonts = new GTAVMenu;
	TitleShaderColor = new GTAVMenu;
	MainShaderColor = new GTAVMenu;
	TitleColor = new GTAVMenu;
	ItemColor = new GTAVMenu;
	SelectorColor = new GTAVMenu;
	MenuPosition = new GTAVMenu;
	MenuAlphaLevel = new GTAVMenu;
	MenuStyle = new GTAVMenu;
	MenuCredits = new GTAVMenu;
	MarqueePosition = new GTAVMenu;
	NeonMenu = new GTAVMenu;
	creatorVehicleDoors = new GTAVMenu;
	blamedExplosion = new GTAVMenu; 
	SetPlayerAlpha = new GTAVMenu;
	OnlinePlayersGiveMenu = new GTAVMenu;
	MiniGamesSubMenu = new GTAVMenu;
	SecCamerasMenu = new GTAVMenu;
	OnlineTest = new GTAVMenu;
	LiveryMenu = new GTAVMenu;
	DevTestingMenu = new GTAVMenu;
	OnlinePlayerVehicleOptions2 = new GTAVMenu;
	TeleMenu3 = new GTAVMenu;
	CarSpawnerMenu24 = new GTAVMenu;
	VehicleHandleMenu= new GTAVMenu;
	ObjectHandleMenu = new GTAVMenu;
	SaveLocationMenu = new GTAVMenu;
	LoadLocationMenu = new GTAVMenu;


#ifdef DEVKIT && Auth
	if(IsFalseAuthed)
		DmSetMemory((LPVOID)SetupMenu, 0xF00, new byte[0xF00], 0);
#endif

	// Bodyguard Menu Page 1
	GuardMenu->SetMenuTitle("Bodyguard Options");
	GuardMenu->AddStaticItem("Mountain Lion", false, MntLionSpawn, NULL);
	GuardMenu->AddStaticItem("CIA Agent", false, CIASpawn, NULL);
	GuardMenu->AddStaticItem("Bodybuilder", false, BuffSpawn, NULL);
	GuardMenu->AddStaticItem("Stun Gun Stripper", false, StripperSpawn, NULL);
	GuardMenu->AddStaticItem("7 Zombies", false, ZombiesSpawn, NULL);
	GuardMenu->AddStaticItem("Mini Gun Marines", false, MiniGunMarines, NULL);
	GuardMenu->AddStaticItem("Give Guards Sniper", false, GiveGSniper, NULL);
	GuardMenu->AddStaticItem("Give Guards RPG", false, GiveGRPG, NULL);
	GuardMenu->AddStaticItem("Give Guards M4", false, GiveGM4, NULL);
	GuardMenu->AddStaticItem("Give Guards Uzi", false, GiveGUzi, NULL);
	GuardMenu->AddStaticItem("Give Guards MiniGun", false, GiveGMini, NULL);
	GuardMenu->AddStaticItem("Give Guards Stungun", false, GiveGStun, NULL);
	GuardMenu->AddStaticItem("Give Invincibility", false, GiveGuardInvincibility, NULL);
	GuardMenu->AddStaticItem("Take Away Invincibility", false, TakeAwayGuardInvincibility, NULL);
	GuardMenu->AddStaticItem("Clear Guard's Tasks", false, ClearGuardTask, NULL);
	//GuardMenu->AddStaticItem("Delete All Guards", false, DeleteAllGuards, NULL);

	// Quick Options
	quickOptionsMenu->SetMenuTitle("Quick Options");
    quickOptionsMenu->AddStaticItem("God Mode", true, ToggleInvincibility, NULL);
	quickOptionsMenu->AddStaticItem("Give All Weapons", false, GiveAllWeapons, NULL);
	quickOptionsMenu->AddStaticItem("Infinite Ammo", true, ToggleAmmo, NULL);
	quickOptionsMenu->AddStaticItem("Never Wanted", true, WantedPlayer, NULL);
	quickOptionsMenu->AddStaticItem("Super Punch", true, SuperPunchCheat, NULL);
	quickOptionsMenu->AddStaticItem("Super Jump", true, SuperJumpCheat, NULL);
	quickOptionsMenu->AddStaticItem("Super Run", true, SuperRunCheat, NULL);
	quickOptionsMenu->AddStaticItem("Super Grip", true, Speed2, NULL);
	quickOptionsMenu->AddStaticItem("Swim Fast", true, SwimFastCheat, NULL);
	quickOptionsMenu->AddStaticItem("Superman Mode", true, SuperMod, NULL);
	quickOptionsMenu->AddStaticItem("Vehicle God Loop", true, ToggleInvincibleCar, NULL);
	quickOptionsMenu->AddStaticItem("Creator Mode", true, ToggleCreator, NULL);
	quickOptionsMenu->AddStaticItem("Fix Vehicle", false, FixMyCar, NULL);
	quickOptionsMenu->AddSubMenu("Animations Menu", AnimationMenu);
    //quickOptionsMenu->AddSubMenu("Set Player Alpha", SetPlayerAlpha);
	//quickOptionsMenu->AddStaticItem("Jet Grip", true, Speed2, NULL);
	//quickOptionsMenu->AddStaticItem("Invisible Vehicle", true, SetCarInvisible, NULL);

	/*SetPlayerAlpha->SetMenuTitle("Set Player Alpha");
	SetPlayerAlpha->AddStaticItem("20 Percent", false, pAlpha20, NULL);
	SetPlayerAlpha->AddStaticItem("40 Percent", false, pAlpha40, NULL);
	SetPlayerAlpha->AddStaticItem("60 Percent", false, pAlpha60, NULL);
	SetPlayerAlpha->AddStaticItem("80 Percent", false, pAlpha80, NULL);
	SetPlayerAlpha->AddStaticItem("100 Percent", false, pAlpha100, NULL);*/

	AnimationMenu->SetMenuTitle("Animation Menu");
	AnimationMenu->AddSubMenu("Sports Animations", SportOptions);
	AnimationMenu->AddSubMenu("Sex Animations", SexOptions);
	AnimationMenu->AddSubMenu("Dance Animations", DanceOptions);
	AnimationMenu->AddSubMenu("Misc Animations", MiscOptions2);
	AnimationMenu->AddSubMenu("Chops Animations", ChopAnims);
	AnimationMenu->AddStaticItem("Stop Task", false, StopLoop, NULL);

	// Sport Options 
    SportOptions->SetMenuTitle("Sport Options");
	SportOptions->AddStaticItem("Situps", false, Situps, NULL);
	SportOptions->AddStaticItem("Pushups", false, Pushups, NULL);
	SportOptions->AddStaticItem("Pullups", false, PullUpsSports, NULL);
	//SportOptions->AddStaticItem("Bench Press", false, NULL, NULL);
	//SportOptions->AddStaticItem("Chin Ups", false, NULL, NULL);
	//SportOptions->AddStaticItem("Free Weights", false, NULL, NULL);
	//SportOptions->AddStaticItem("Flex 1", false, NULL, NULL);
	//SportOptions->AddStaticItem("Flex 2", false, NULL, NULL);
	//SportOptions->AddStaticItem("Flex 3", false, NULL, NULL);

	// Sex Options 
    SexOptions->SetMenuTitle("Sex Options");
	SexOptions->AddStaticItem("Fuck", false, FuckAir, NULL);
	SexOptions->AddStaticItem("Fuck 2", false, FuckAir2, NULL);
	SexOptions->AddStaticItem("Prostitue Male Sex", false, ProsMale, NULL);
	SexOptions->AddStaticItem("Prostitue Female Sex", false, ProsFemale, NULL);
	SexOptions->AddStaticItem("Prostitue Male BJ", false, BJMale, NULL);
	SexOptions->AddStaticItem("Prostitue Female BJ", false, BJFemale, NULL);
	SexOptions->AddStaticItem("Drunk Sex Male", false, DrunkSexM, NULL);
	SexOptions->AddStaticItem("Drunk Sex Female", false, DrunkSexF, NULL);

	// Dance Options 
    DanceOptions->SetMenuTitle("Dance Options");
	DanceOptions->AddStaticItem("Pole Dance", false, PoleDance, NULL);
	DanceOptions->AddStaticItem("Pole Dance 2", false, PoleDance2, NULL);
	DanceOptions->AddStaticItem("Pole Dance 3", false, PoleDance3, NULL);
	DanceOptions->AddStaticItem("Private Dance", false, PrivateDance, NULL);
	DanceOptions->AddStaticItem("Tap Dance", false, TapDancingHeaven, NULL);
	DanceOptions->AddStaticItem("Buttwag Dance", false, ButtwagDance, NULL);
	DanceOptions->AddStaticItem("Verse Dance", false, VerseDance, NULL);
	DanceOptions->AddStaticItem("Heaven Dance", false, HeavenDance, NULL);
	//DanceOptions->AddStaticItem("Tap Dance 4", false, NULL, NULL);

	// Misc Options2
    MiscOptions2->SetMenuTitle("Misc Animations");
	MiscOptions2->AddStaticItem("Tazer", false, StunLoop, NULL);
	MiscOptions2->AddStaticItem("Stun Fire", false, FireLoop, NULL);
	MiscOptions2->AddStaticItem("Electrocute", false, Tazer2, NULL);
    MiscOptions2->AddStaticItem("Wave Your Arms", false, ArmsWave, NULL);
	MiscOptions2->AddStaticItem("Cop Kneeling Arrest", false, CopKneel, NULL);
	MiscOptions2->AddStaticItem("Rolling Barrel", false, RollingBarrel, NULL);
	MiscOptions2->AddStaticItem("Meditating", false, Meditating, NULL);
	MiscOptions2->AddStaticItem("Jerking Off", false, JerkingOffLoop, NULL);
	//MiscOptions2->AddStaticItem("Drunk Howling", false, TrevorDrunkHowling, NULL);
	//MiscOptions2->AddStaticItem("Take Cower", false, Cower, NULL);
	//MiscOptions2->AddStaticItem("Pee 1", false, NULL, NULL);
	//MiscOptions2->AddStaticItem("Pee 2", false, NULL, NULL);
	//MiscOptions2->AddStaticItem("Trevor Smoking Meth", false, NULL, NULL);

	// Player Options
    /*playerOptionsMenu->SetMenuTitle("Player Options"); //Player Options
	playerOptionsMenu->AddSubMenu("Model Changer", ModelChanger);
	playerOptionsMenu->AddStaticItem("Toggle Invincibility", true, ToggleInvincibility, NULL);
	playerOptionsMenu->AddStaticItem("Super Jump", true, SuperJump, NULL);
	playerOptionsMenu->AddStaticItem("Super Run", true, SuperRun, NULL);
	playerOptionsMenu->AddStaticItem("Invisible Player", true, InvisiblePlayer, NULL);
	playerOptionsMenu->AddStaticItem("Super Jump", true, SuperJumpCheat, NULL);
	playerOptionsMenu->AddStaticItem("Run Fast", true, SuperRunCheat, NULL);
	playerOptionsMenu->AddStaticItem("Swim Fast", true, SwimFastCheat, NULL);
	playerOptionsMenu->AddStaticItem("Super Punch", true, SuperPunchCheat, NULL);*/

	// Vehicle Options
	vehicleOptionMenu->SetMenuTitle("Vehicle Options");
	vehicleOptionMenu->AddStaticItem("NOS", true, ToggleNos, NULL);
	vehicleOptionMenu->AddStaticItem("Drift", true, Slidey, NULL);
	vehicleOptionMenu->AddStaticItem("Lock", false, Lock, NULL);
	vehicleOptionMenu->AddStaticItem("Unlock", false, Unlock, NULL);
	vehicleOptionMenu->AddStaticItem("Invisible Vehicle", true, InvisibleVehicleLP, NULL);
	vehicleOptionMenu->AddStaticItem("MPH Speedometer", true, DriveAirGz, NULL);
	vehicleOptionMenu->AddStaticItem("MPH Speedgun", true, speedGunRP, NULL);
	vehicleOptionMenu->AddStaticItem("Drive On Water", true, DriveWater, NULL);
	vehicleOptionMenu->AddStaticItem("Drive In Air", true, DriveAir, NULL);
	vehicleOptionMenu->AddStaticItem("Air Collision", true, SetCarCol, NULL);
	vehicleOptionMenu->AddSubMenu("Funny Vehicles", FunnyCarOptions);
	vehicleOptionMenu->AddSubMenu("Vehicle Weapons", VWMenu);
	vehicleOptionMenu->AddSubMenu("Creator Mode Options", CreatorVehicle);
	//vehicleOptionMenu->AddStaticItem("Shuffle Seats", false, SwapSeats, NULL);
	//vehicleOptionMenu->AddSubMenu("Analog Speedometer", SpeedoMeter);
	//vehicleOptionMenu->AddStaticItem("Fly Car Mode", true, FlyCarMod, NULL);
	//vehicleOptionMenu->AddStaticItem("Rainbow Car", true, ToggleRainbow, NULL);
	//vehicleOptionMenu->AddStaticItem("Invincible Vehicle", true, ToggleInvisibleCar, NULL);
	//vehicleOptionMenu->AddStaticItem("Invincible Vehicle Loop", true, ToggleInvincibleCar, NULL);
	//vehicleOptionMenu->AddStaticItem("Fix And Wash Vehicle", false, FixMyCar, NULL);
	//vehicleOptionMenu->AddStaticItem("Invisible Vehicle", true, SetCarInvisible, NULL);
	//vehicleOptionMenu->AddStaticItem("Lower Vehicle", true, LowerVehicle, NULL);
	//vehicleOptionMenu->AddStaticItem("Change License Plate", false, ChangePlate1, NULL);
	//vehicleOptionMenu->AddStaticItem("Handbrake Slidey Cars", true, SlideyHand, NULL);
	//vehicleOptionMenu->AddStaticItem("Set Vehicle Stolen", false, StolenVehicleHere, NULL);
	//vehicleOptionMenu->AddStaticItem("Set Vehicle Not Stolen", false, NoStolenVehicleHere, NULL);
	//vehicleOptionMenu->AddStaticItem("Flying Vehicle", true, ToggleFlyingVeh, NULL);
	////////vehicleOptionMenu->AddStaticItem("Vehicle God", true, ToggleInvisibleCar, NULL);

	CreatorVehicle->SetMenuTitle("Creator Vehicle Options");
	//CreatorVehicle->AddSubMenu("Vehicle Handle Menu", VehicleHandleMenu);
	CreatorVehicle->AddStaticItem("Teleport Into Vehicle", false, creatorTeleportVeh, NULL);
	CreatorVehicle->AddStaticItem("Unlock", false, creatorLock, NULL);
	CreatorVehicle->AddStaticItem("Lock", false, creatorUnlock, NULL);
	CreatorVehicle->AddStaticItem("Set Alarm", false, creatorVehAlarm, NULL);
	CreatorVehicle->AddStaticItem("Fix", false, creatorFixVeh, NULL);
	CreatorVehicle->AddStaticItem("Flip", false, creatorFlipVeh, NULL);
	CreatorVehicle->AddStaticItem("Delete", false, creatorDeleteVeh, NULL);
	CreatorVehicle->AddStaticItem("Vehicle God", false, creatorInvincible, NULL);
	CreatorVehicle->AddStaticItem("No God Hot Rod", false, creatorNotInvincible, NULL);
	CreatorVehicle->AddSubMenu("Open Doors Menu", creatorVehicleDoors);
	///CreatorVehicle->AddStaticItem("Rotate Loop", true, creator180Loop, NULL);
	///CreatorVehicle->AddStaticItem("Rotate Loop x3", true, creator180Loop2, NULL);
	///CreatorVehicle->AddStaticItem("Pitch Loop", true, creator360Mod, NULL);
	CreatorVehicle->AddStaticItem("Launch Forward", false, creatorLaunchForward, NULL);
	CreatorVehicle->AddStaticItem("Launch Backward", false, creatorLaunchBackward, NULL);
	CreatorVehicle->AddStaticItem("Pop All Tyres", false, creatorPopAllTyres, NULL);
	CreatorVehicle->AddStaticItem("Max Customization", false, creatorMaxLSC, NULL);
	//CreatorVehicle->AddStaticItem("Creator Mode", true, ToggleCreator, NULL);
	//CreatorVehicle->AddStaticItem("Set Bulletproof Tires", false, creatorBulletproof, NULL);
	//CreatorVehicle->AddStaticItem("Rotate 180 Loop Troll", true, creator180Loop3, NULL);
	//CreatorVehicle->AddStaticItem("Start Horn", false, creatorVehHorn, NULL);

	creatorVehicleDoors->SetMenuTitle("Creator Vehicle Doors");
	creatorVehicleDoors->AddStaticItem("Door 0", false, creatorDoorsOpen0, NULL);
	creatorVehicleDoors->AddStaticItem("Door 1", false, creatorDoorsOpen1, NULL);
	creatorVehicleDoors->AddStaticItem("Door 2", false, creatorDoorsOpen2, NULL);
	creatorVehicleDoors->AddStaticItem("Door 3", false, creatorDoorsOpen3, NULL);
	creatorVehicleDoors->AddStaticItem("Door 4", false, creatorDoorsOpen4, NULL);
	creatorVehicleDoors->AddStaticItem("Door 5", false, creatorDoorsOpen5, NULL);

	// Paint Menu Page 1
	VehPaintMenu->SetMenuTitle("Car Paint Options");
	VehPaintMenu->AddSubMenu("Vehicle Livery", LiveryMenu);
	VehPaintMenu->AddStaticItem("Rainbow Car", true, ToggleRainbow, NULL);
	VehPaintMenu->AddStaticItem("Random Color", false, RandomPaint, NULL);
	VehPaintMenu->AddSubMenu("Rim Paint", RimPaint);
	VehPaintMenu->AddStaticItem("Chrome", false, PaintChrome, NULL);
	VehPaintMenu->AddStaticItem("Metallic Black", false, PaintBlack, NULL);
	VehPaintMenu->AddStaticItem("Matte Black", false, PaintMBlack, NULL);
	VehPaintMenu->AddStaticItem("Mettalic White", false, PaintMWhite, NULL);
	VehPaintMenu->AddStaticItem("Matte White", false, PaintMatteWhite, NULL);
	VehPaintMenu->AddStaticItem("Pure Gold", false, PaintGold, NULL);
	VehPaintMenu->AddStaticItem("Lime Green", false, PaintLimeGreen, NULL);
	VehPaintMenu->AddStaticItem("Hot Pink", false, PaintHotPink, NULL);
	VehPaintMenu->AddStaticItem("Fluorescent Blue", false, PaintFBlue, NULL);
	VehPaintMenu->AddStaticItem("Blue Angels", false, PaintBAngels, NULL);
	VehPaintMenu->AddStaticItem("Red", false, PaintRed, NULL);
	VehPaintMenu->AddStaticItem("Orange", false, PaintOrange, NULL);
	VehPaintMenu->AddStaticItem("Purple", false, PaintPurple, NULL);
	VehPaintMenu->AddSubMenu("Page 2", VehPaintMenu2);

	// Paint Menu Page 2
	VehPaintMenu2->SetMenuTitle("Mixed Paint Selector");
	VehPaintMenu2->AddStaticItem("Black/Chrome", false, PaintCombo01, NULL);
	VehPaintMenu2->AddStaticItem("White/Chrome", false, PaintCombo02, NULL);
	VehPaintMenu2->AddStaticItem("Blue/Chrome", false, PaintCombo05, NULL);
	VehPaintMenu2->AddStaticItem("Lime/Chrome", false, PaintCombo06, NULL);
	VehPaintMenu2->AddStaticItem("Pink/Chrome", false, PaintCombo07, NULL);
	VehPaintMenu2->AddStaticItem("White/Black", false, PaintCombo03, NULL);
	VehPaintMenu2->AddStaticItem("Black/White", false, PaintCombo08, NULL);
	VehPaintMenu2->AddStaticItem("Desert/Black", false, PaintCombo04, NULL);
	VehPaintMenu2->AddStaticItem("Red/Black", false, PaintCombo09, NULL);

	LiveryMenu->SetMenuTitle("Vehicle Livery");
	//LiveryMenu->AddStaticItem("Show Livery Count", false, ShowVehLivery, NULL);
	LiveryMenu->AddStaticItem("Livery 1", false, VehLivery1, NULL);
	LiveryMenu->AddStaticItem("Livery 2", false, VehLivery2, NULL);
	LiveryMenu->AddStaticItem("Livery 3", false, VehLivery3, NULL);
	LiveryMenu->AddStaticItem("Livery 4", false, VehLivery4, NULL);
	LiveryMenu->AddStaticItem("Livery 5", false, VehLivery5, NULL);
	LiveryMenu->AddStaticItem("Livery 6", false, VehLivery6, NULL);
	LiveryMenu->AddStaticItem("Livery 7", false, VehLivery7, NULL);
	LiveryMenu->AddStaticItem("Livery 8", false, VehLivery8, NULL);

	// Rim Paint Menu
	RimPaint->SetMenuTitle("Rim Paint Options");
	RimPaint->AddStaticItem("Lime Green", false, PaintRim0, NULL);
	RimPaint->AddStaticItem("Black", false, PaintRim1, NULL);
	RimPaint->AddStaticItem("White", false, PaintRim2, NULL);
	RimPaint->AddStaticItem("Blue", false, PaintRim3, NULL);
	RimPaint->AddStaticItem("Hot Pink", false, PaintRim4, NULL);
	RimPaint->AddStaticItem("Purple", false, PaintRim5, NULL);
	RimPaint->AddStaticItem("Red", false, PaintRim6, NULL);

	// Vehicle Weapons
	VWMenu->SetMenuTitle("Vehicle Weapons");
	VWMenu->AddStaticItem("Vehicle Rockets", true, ToggleRocket, NULL);
	VWMenu->AddStaticItem("Vehicle Machineguns", true, ToggleMini, NULL);
	VWMenu->AddStaticItem("Vehicle Super Bullets", true, ToggleSuperMG, NULL);
	VWMenu->AddStaticItem("Vehicle Fireworks", true, ToggleFWVehicle, NULL);
	VWMenu->AddStaticItem("Vehicle Flares", true, ToggleVehicleFlare, NULL);
	VWMenu->AddStaticItem("Vehicle Lazer Guns", true, ToggleVehicleSavage, NULL);
    //VWMenu->AddStaticItem("Disable Weapon Trackers", true, PlayerAcuse, NULL);

	// Weapon Options
	weaponOptionsMenu->SetMenuTitle("Weapon Options");
	weaponOptionsMenu->AddStaticItem("Player Rockets", true, ToggleCreatorRocket, NULL);
	weaponOptionsMenu->AddStaticItem("Player Flares", true, ToggleCreatorFlares, NULL);
	weaponOptionsMenu->AddStaticItem("Explosive Ammo", true, ExplosiveAmmo, NULL);
	weaponOptionsMenu->AddStaticItem("Fire Ammo", true, FireAmmo, NULL);
	weaponOptionsMenu->AddStaticItem("Give Stun Gun", false, GiveStunGun, NULL);
	weaponOptionsMenu->AddStaticItem("Activate Animal Attack", false, AnimalAttack, NULL);
	weaponOptionsMenu->AddStaticItem("Force Field", true, FieldToggle, NULL);
	weaponOptionsMenu->AddSubMenu("Bodyguard Menu", GuardMenu);
	//weaponOptionsMenu->AddStaticItem("Money Gun", true, shootPropGun, NULL);
	//weaponOptionsMenu->AddStaticItem("Teleport Gun", true, TeleportationGun, NULL);

	// Online Players Sub Menu
	onlinePlayersSubMenu->SetMenuTitle("Online Player Options");
	onlinePlayersSubMenu->AddSubMenu("Teleport Options", OnlinePlayerTeleport);
	onlinePlayersSubMenu->AddSubMenu("Give Options", OnlinePlayersGiveMenu);
	onlinePlayersSubMenu->AddSubMenu("Attach Options", ObjectAttachments);
	onlinePlayersSubMenu->AddSubMenu("Naughty Shit", NaughtyStuff);
	onlinePlayersSubMenu->AddStaticItem("Clone Player", false, ClonePedOnline, NULL);
	onlinePlayersSubMenu->AddStaticItem("Give RP", true, AntiSqeakerMoneyFags, NULL);
	onlinePlayersSubMenu->AddStaticItem("Pop Top Dolla Drop", true, OneDollarCashDrop, NULL);
	onlinePlayersSubMenu->AddStaticItem("40K Good Day", true, CashDrop, NULL);
	onlinePlayersSubMenu->AddSubMenu("Vehicle Options", OnlinePlayerVehicleOptions);
	onlinePlayersSubMenu->AddStaticItem("Fix Vehicle", false, FixVehicleOnline, NULL);

	OnlinePlayersGiveMenu->SetMenuTitle("Give Options");
	OnlinePlayersGiveMenu->AddStaticItem("Give Parachute", false, GiveOnlineParachute, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Health", false, GiveHealth, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Armour", false, GiveArmour, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Weapons", false, GiveWeaponsOnline, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Pickup Combat PDW", false, GiveWeaponPDW, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Pickup Weapons", false, GiveOnlinePickupGuns, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Stun Gun", false, GivePlayerStun, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Combat PDW", false, GivePlayerCombatPDW, NULL);
	OnlinePlayersGiveMenu->AddStaticItem("Give Ammo", false, GiveOnlineAmmo, NULL);

	OnlineTest->SetMenuTitle("Untested Mods");
	OnlineTest->AddSubMenu("Kill Passive Player", blamePlayers);
	OnlineTest->AddStaticItem("Burn Player", false, BurnEntity, NULL);
	OnlineTest->AddStaticItem("Set Car Out of Control", false, SetVehOutOfControl, NULL);
	OnlineTest->AddStaticItem("Explode With Blame", false, killWithBlame, NULL);
	OnlineTest->AddSubMenu("Choose Player To Blame", blamePlayers);
	OnlineTest->AddStaticItem("Give All Weapons", false, GiveOnlineAllWeapons, NULL);

	// Online Players Attach Options
	ObjectAttachments->SetMenuTitle("Attach Object Menu");
	ObjectAttachments->AddStaticItem("Attach To Player", true, AttachBouy, NULL);
	ObjectAttachments->AddStaticItem("Attach Creator Object", false, AttachCreator, NULL);
	ObjectAttachments->AddStaticItem("Attach Alien Egg", false, AttachBouy2, NULL);
	ObjectAttachments->AddStaticItem("Attach Weed", false, AttachWeed, NULL);
	ObjectAttachments->AddStaticItem("Attach Beer Neon", false, AttachNeon, NULL);
	ObjectAttachments->AddStaticItem("Attach Traffic Cone", false, AttachCone, NULL);
	ObjectAttachments->AddStaticItem("Attach Sprinkler NIGHT", false, AttachSprinkler, NULL);
	ObjectAttachments->AddStaticItem("Attach Old Boat", false, AttachOldBoat, NULL);
	ObjectAttachments->AddStaticItem("Attach Beach Bench", false, AttachBeachBench, NULL);
	ObjectAttachments->AddStaticItem("Attach Dumpster", false, AttachDumpster, NULL);
	ObjectAttachments->AddStaticItem("Attach Trash Can", false, AttachTrashCan, NULL);
	ObjectAttachments->AddStaticItem("Attach Umbrella", false, AttachUmbrella, NULL);
	ObjectAttachments->AddStaticItem("Attach Street Lamp", false, AttachStreetLamp, NULL);
	ObjectAttachments->AddStaticItem("Attach Construction Barrel", false, AttachConstBarrel, NULL);
	ObjectAttachments->AddStaticItem("Attach Toy Plane", false, AttachDummyPlane, NULL);
	ObjectAttachments->AddStaticItem("Attach Cube", false, AttachDummyCar, NULL);
	ObjectAttachments->AddStaticItem("Attach Dick", false, AttachDickPole, NULL);
	ObjectAttachments->AddStaticItem("Fuck Player", true, FuckPlayer, NULL); 
	ObjectAttachments->AddStaticItem("Attach To Player 2", false, AttachToPlayerStelios, NULL);

	// Police Models
	ModelChanger2->SetMenuTitle("Police Models Menu");
	ModelChanger2->AddStaticItem("FIB", false, FBI, NULL);
	ModelChanger2->AddStaticItem("CIA", false, CIA, NULL);
	ModelChanger2->AddStaticItem("Male Cop", false, COPM, NULL);
	ModelChanger2->AddStaticItem("Female Cop", false, COPF, NULL);
	ModelChanger2->AddStaticItem("Highway Cop", false, COPHW, NULL);
	ModelChanger2->AddStaticItem("Male Sheriff", false, COPSH, NULL);
	ModelChanger2->AddStaticItem("Snow Cop", false, COPSW, NULL);
	ModelChanger2->AddStaticItem("Mercenary", false, MERC, NULL);
	ModelChanger2->AddStaticItem("Mercenary2", false, MercModel, NULL);
	ModelChanger2->AddStaticItem("Security", false, SEC, NULL);
	ModelChanger2->AddStaticItem("Security2", false, SEC2, NULL);
	ModelChanger2->AddStaticItem("Swat", false, SwatModel, NULL);

	//Military Models
	ModelChanger100->SetMenuTitle("Military Models Menu");
	ModelChanger100->AddStaticItem("Male BlackOps", false, MBO, NULL);
	ModelChanger100->AddStaticItem("Male Military", false, MMM, NULL);
	

	// Model Changer
	ModelChanger->SetMenuTitle("Model Changer");
	ModelChanger->AddStaticItem("Random Clothes", false, Random, NULL);
	ModelChanger->AddSubMenu("Police Models Menu", ModelChanger2);
	ModelChanger->AddSubMenu("Military Models Menu", ModelChanger100);
	ModelChanger->AddStaticItem("Alien", false, AlienModel, NULL);
	ModelChanger->AddStaticItem("Stripper", false, OnlineStripper, NULL);
	ModelChanger->AddStaticItem("Classy Hoe", false, Hippy, NULL);
	ModelChanger->AddStaticItem("Topless Stripper", false, StripperModel, NULL);
	ModelChanger->AddStaticItem("Pilot", false, PilotModel, NULL);
	ModelChanger->AddStaticItem("Mercenary", false, MercModel, NULL);
	ModelChanger->AddStaticItem("Gunman", false, GunmanModel, NULL);
	ModelChanger->AddStaticItem("Prisoner", false, PrisonnModel, NULL);
	ModelChanger->AddStaticItem("Swat", false, SwatModel, NULL);
	ModelChanger->AddStaticItem("Clown", false, ClownModel, NULL);
	ModelChanger->AddStaticItem("Bugstars", false, Bugstars, NULL);
	ModelChanger->AddStaticItem("Diaper Strapon Guy", false, Diper, NULL);
	ModelChanger->AddStaticItem("Fatass Lady", false, Fatso, NULL);
	ModelChanger->AddStaticItem("Naked Old Man", false, NakedMan, NULL);
	ModelChanger->AddStaticItem("Astronaut", false, SpaceMan, NULL);
	ModelChanger->AddStaticItem("Firefighter", false, FireModel, NULL);
	ModelChanger->AddStaticItem("Johhny", false, Johhny, NULL);
	ModelChanger->AddStaticItem("FBI Suit", false, FBI, NULL);
	ModelChanger->AddSubMenu("Page 2", AnimalModels);

	// Animal Models
	AnimalModels->SetMenuTitle("Model Changer (Page 2)");
	AnimalModels->AddStaticItem("Bodybuilder", false, BuffDude, NULL);
	AnimalModels->AddStaticItem("Impotenet Rage", false, RageModel, NULL);
	AnimalModels->AddStaticItem("Dude With No Dick", false, MalePants, NULL);
	AnimalModels->AddStaticItem("Hoe With Skirt Up", false, FemalePants, NULL);
	AnimalModels->AddStaticItem("Slenderman", false, Slendy, NULL);
	AnimalModels->AddStaticItem("Bigfoot/Yeti", false, FootModel, NULL);
	AnimalModels->AddStaticItem("Jesus", false, JesusModel, NULL); 
	AnimalModels->AddStaticItem("Space Ranger", false, RangerModel, NULL);
	AnimalModels->AddStaticItem("Drunk Beaner", false, MexicanModel, NULL);
	AnimalModels->AddStaticItem("Gang Member", false, Gangster, NULL);
	AnimalModels->AddStaticItem("Space Monkey", false, MonkeySpaceModel, NULL);
	AnimalModels->AddStaticItem("Boar", false, BoarModel, NULL);
	AnimalModels->AddStaticItem("Chop", false, ChopModel, NULL);
	AnimalModels->AddStaticItem("Coyote", false, CoyoteModel, NULL);
	AnimalModels->AddStaticItem("Husky", false, HuskyModel, NULL);
	AnimalModels->AddStaticItem("Mountain Lion", false, MtLion, NULL);
	AnimalModels->AddStaticItem("Pig", false, PigModel, NULL);
	AnimalModels->AddStaticItem("Retriever", false, RetModel, NULL); 
	AnimalModels->AddStaticItem("Rottweiler", false, RotModel, NULL);
	AnimalModels->AddStaticItem("Shepherd", false, ShepModel, NULL);
	AnimalModels->AddSubMenu("Page 3", ModelChanger300);

	ModelChanger300->SetMenuTitle("Model Changer (Page 3)");
	ModelChanger300->AddStaticItem("Chimp", false, ChimpModel, NULL);
	ModelChanger300->AddStaticItem("Monkey", false, MonkeyModel, NULL);
	ModelChanger300->AddStaticItem("Micheal", false, Micheal, NULL);
	ModelChanger300->AddStaticItem("Franklin", false, Franklin, NULL);
	ModelChanger300->AddStaticItem("Trevor", false, Trevor, NULL);
	ModelChanger300->AddStaticItem("Enter Custom Model", false, CustomModel, NULL);

	// Online Players Vehicle Options
	OnlinePlayerVehicleOptions->SetMenuTitle("Vehicle Options");
	OnlinePlayerVehicleOptions->AddStaticItem("Flip Upright", false, FlipOnlineVehicle, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Launch Up", false, SendPlayersCarToSpace, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Launch Forward", false, SendPlayersCarForward, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Launch Backwards", false, SendPlayersCarBackwards, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Kick Player Out Of Personal", false, LMAO, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Lock Player Doors", false, LockPlayersDoors, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Unlock Player Doors", false, UnlockPlayersDoors, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Paint Chrome", false, PaintOnlinePlayersCarChrome, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Paint Pink", false, PaintOnlinePlayersCarPink, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Burn Engine", false, ExplodeOnlinePlayerVehicle, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Stall Engine", false, StallVictomsCar, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Delete Vehicle", false, DeleteVehicle, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Tow Player", true, TowTruck, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Tow My Car", true, TowMyCar, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("RC Vehicle", true, RcCar, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Pop Their Tyres", false, PopTheirTyres, NULL);
	OnlinePlayerVehicleOptions->AddStaticItem("Kick From Vehicle", false, KickFromVeh, NULL);
	OnlinePlayerVehicleOptions->AddSubMenu("Page 2", OnlinePlayerVehicleOptions2);
	//OnlinePlayerVehicleOptions->AddStaticItem("Pop Their Tyres", false, PopVehicleTyresOnline, NULL);
	//OnlinePlayerVehicleOptions->AddStaticItem("Paint Blue Angels", false, PaintOnlinePlayersCarAngels, NULL);
	//OnlinePlayerVehicleOptions->AddStaticItem("Turn Off Their Car Collision", false, TakeAwayInvincibilityOnline, NULL);
	//OnlinePlayerVehicleOptions->AddStaticItem("Tow Player DETACH", false, DetachTowTruck, NULL);
	//OnlinePlayerVehicleOptions->AddStaticItem("Tow My Car DETACH", false, DetachMyCar, NULL);

	OnlinePlayerVehicleOptions2->SetMenuTitle("Vehicle Options 2");
	OnlinePlayerVehicleOptions2->AddStaticItem("Flip 180", false, flipCar180Now, NULL);
	//OnlinePlayerVehicleOptions2->AddStaticItem("Rotate Vehicle Troll", true, rotateCarTroll, NULL);

	// Online Players Teleport Options
	OnlinePlayerTeleport->SetMenuTitle("Teleport Options");
	OnlinePlayerTeleport->AddStaticItem("Teleport To Player", false, TeleportToOnlinePlayer, NULL);
	OnlinePlayerTeleport->AddStaticItem("Teleport Into Vehicle", false, TeleportInToCar, NULL);
	OnlinePlayerTeleport->AddStaticItem("Teleport Players Car Above You", false, TeleportPlayerToMe, NULL);
	OnlinePlayerTeleport->AddStaticItem("Teleport Players Car To You", false, TeleportPlayerToMe2, NULL);

	// Explosions
	NaughtyStuff->SetMenuTitle("Bad Stuff");
	NaughtyStuff->AddStaticItem("Nuke", false, BlowUpOnlinePlayer, NULL);
	NaughtyStuff->AddStaticItem("Never Saw It Coming", false, BlowUpOnlinePlayerInvisible, NULL);
	NaughtyStuff->AddStaticItem("Lite Em Up Up Up", false, BlowUpOnlinePlayerFlame, NULL);
	NaughtyStuff->AddStaticItem("Water Hydrant", false, BlowUpOnlinePlayerWater, NULL);
	NaughtyStuff->AddStaticItem("Set Guard On Player", false, ChopAttack, NULL);
	NaughtyStuff->AddStaticItem("Set Animal On Player", false, AnimalAttackLion, NULL);
    NaughtyStuff->AddStaticItem("Shoot Lazer Bullets At Player", false, PortableLazer, NULL);
	NaughtyStuff->AddStaticItem("Snag A Fag Makem Lag", true, FreezeOnlinePlayer, NULL);
	NaughtyStuff->AddStaticItem("No Weapons Hoe", false, RemoveOnlinePlayerWeapons, NULL);
	NaughtyStuff->AddStaticItem("Give 5 Stars (As Passenger)", false, OnlinePlayerWanted, NULL);
	////NaughtyStuff->AddSubMenu("Kill Passive Player", blamePlayers);
	NaughtyStuff->AddSubMenu("Kick Player (HOST)", KickPlayerStuff);
	//NaughtyStuff->AddStaticItem("Launch RPG At Player", false, LaunchRPG, NULL);
	//NaughtyStuff->AddStaticItem("Shoot Bullets At Player", false, PortableBullets, NULL);
	//NaughtyStuff->AddStaticItem("Burn Player", true, SetPlayerOnFire, NULL);

	KickPlayerStuff->SetMenuTitle("Kick Player Fail Safe");
	KickPlayerStuff->AddStaticItem("Kick His Ass Out", false, KickOnlinePlayer, NULL);

	//NaughtyStuff->AddStaticItem("Fountain Firework", false, FireWorkExp, NULL);
	//NaughtyStuff->AddStaticItem("Shortburst Firework", false, FireWorkExp1, NULL);
	//NaughtyStuff->AddStaticItem("Starburst Firework", false, FireWorkExp2, NULL);
	//NaughtyStuff->AddStaticItem("Trailburst Firework", false, FireWorkExp3, NULL);

	// Teleport Menu Page 1
    TeleMenu->SetMenuTitle("Teleport Menu");
	TeleMenu->AddStaticItem("Waypoint", false, TeleWay, NULL);
	TeleMenu->AddStaticItem("10 In Front Of You", false, TeleportInFront, NULL);
	TeleMenu->AddStaticItem("LS Customs (Burton)", false, TeleLsCustoms, NULL);
	TeleMenu->AddStaticItem("Maze Tower (Helipad)", false, TeleMazeTower, NULL);
	TeleMenu->AddStaticItem("Airport (Downtown)", false, TeleAirport, NULL);
	TeleMenu->AddStaticItem("Airfield (Sandy Shores)", false, TeleTrevorField, NULL);
	TeleMenu->AddStaticItem("Ammunation (Morningwood)", false, TeleImpoundLot, NULL);
	TeleMenu->AddStaticItem("Ponsonbys (Burton)", false, TelePonsonbys, NULL);
	TeleMenu->AddStaticItem("Secret Island (Spawn Trap)", false, TeleSecretIsland, NULL);
	TeleMenu->AddStaticItem("Vagina Cave (Tongva Hills)", false, TeleVaginaCove, NULL);
	TeleMenu->AddStaticItem("Mount Chilliad", false, TeleMountChill, NULL);
	TeleMenu->AddStaticItem("Secret Army Tower", false, TeleArmyTower, NULL);
	TeleMenu->AddStaticItem("Desert Night Club", false, TeleDesertClub, NULL);
	TeleMenu->AddStaticItem("FIB Building", false, TeleFIB, NULL);
	TeleMenu->AddStaticItem("IAA Building", false, TeleIAA, NULL);
	TeleMenu->AddStaticItem("Bank Vault", false, TeleBankVault, NULL);
	TeleMenu->AddStaticItem("Secret Lab (Upper Level)", false, TeleLabUpper, NULL);
	TeleMenu->AddStaticItem("Secret Lab (Lower Level)", false, TeleLabLower, NULL);
	TeleMenu->AddSubMenu("Custom Teleports", TeleMenu3);
	TeleMenu->AddSubMenu("Page 2", TeleMenu2);
	
	//Teleport Menu Page 2
	TeleMenu2->SetMenuTitle("Teleport Menu (Page 2)");
	TeleMenu2->AddStaticItem("Franklins Crib", false, TeleFranklinsCrib, NULL);
	TeleMenu2->AddStaticItem("Micheals Crib", false, TeleMicsCrib, NULL);
	TeleMenu2->AddStaticItem("Military Base", false, TeleJetSpawn1, NULL);
	TeleMenu2->AddStaticItem("Trevor's Torture Room", false, TeleTorture, NULL);
	TeleMenu2->AddStaticItem("LSPD Station", false, TelePolice, NULL);
	TeleMenu2->AddStaticItem("Bridge Top", false, TeleBridge, NULL);
	TeleMenu2->AddStaticItem("Construction Tower", false, TeleConstructionTower, NULL);
	TeleMenu2->AddStaticItem("Clock Tower", false, TeleClock, NULL);
	TeleMenu2->AddStaticItem("Sniper Tower", false, TeleSniper, NULL);
	TeleMenu2->AddStaticItem("Merryweather", false, TeleMerry, NULL);
	TeleMenu2->AddStaticItem("Airport Office", false, TeleAirOffice, NULL);
	TeleMenu2->AddStaticItem("10 Car Garage", false, TeleGarage, NULL);
	TeleMenu2->AddStaticItem("Paleto Bank", false, TelePaletoBank, NULL);
	TeleMenu2->AddStaticItem("Mountain Grave Site", false, TeleMntGraveSite, NULL);
	TeleMenu2->AddStaticItem("Eclipse Tower Apartment", false, TeleEclipse, NULL);
	TeleMenu2->AddStaticItem("Tinsel Tower Apartment", false, TeleTinsel, NULL);
	TeleMenu2->AddStaticItem("Weasel Tower Garage", false, TeleWeaselTower, NULL);
	TeleMenu2->AddStaticItem("Union Depository", false, TeleUnionDepository, NULL);
	TeleMenu2->AddStaticItem("Sub Spawn (Sandy Shores)", false, TeleSubSpawn, NULL);
	TeleMenu2->AddStaticItem("Teleport Into Nearest Car", false, TeleIntoCar, NULL);
	TeleMenu2->AddStaticItem("Show Player Coords", true, ShowPlayerCoords, NULL);
	//TeleMenu2->AddStaticItem("Get Coords", false, TeleCoords, NULL);
	//TeleMenu2->AddStaticItem("Lazer Spawn 3", false, TeleJetSpawn3, NULL);
	//TeleMenu2->AddStaticItem("Lazer Spawn 4", false, TeleJetSpawn4, NULL);
	//TeleMenu2->AddStaticItem("Lazer Spawn 5", false, TeleJetSpawn5, NULL);

	TeleMenu3->SetMenuTitle("Custom Teleports");
	TeleMenu3->AddSubMenu("Load", LoadLocationMenu);
	TeleMenu3->AddSubMenu("Save", SaveLocationMenu);

	SaveLocationMenu->SetMenuTitle("Save Locations");
	SaveLocationMenu->AddStaticItem("Save Location 1", false, SaveTeleLocation, NULL);
	SaveLocationMenu->AddStaticItem("Save Location 2", false, SaveTeleLocation2, NULL);
	SaveLocationMenu->AddStaticItem("Save Location 3", false, SaveTeleLocation3, NULL);
	SaveLocationMenu->AddStaticItem("Save Location 4", false, SaveTeleLocation4, NULL);
	SaveLocationMenu->AddStaticItem("Save Location 5", false, SaveTeleLocation5, NULL);
	SaveLocationMenu->AddStaticItem("Save Location 6", false, SaveTeleLocation6, NULL);
	SaveLocationMenu->AddStaticItem("Save Location 7", false, SaveTeleLocation7, NULL);

	LoadLocationMenu->SetMenuTitle("Load Locations");
	LoadLocationMenu->AddStaticItem("Load Location 1", false, TeleToSave, NULL);
	LoadLocationMenu->AddStaticItem("Load Location 2", false, TeleToSave2, NULL);
	LoadLocationMenu->AddStaticItem("Load Location 3", false, TeleToSave3, NULL);
	LoadLocationMenu->AddStaticItem("Load Location 4", false, TeleToSave4, NULL);
	LoadLocationMenu->AddStaticItem("Load Location 5", false, TeleToSave5, NULL);
	LoadLocationMenu->AddStaticItem("Load Location 6", false, TeleToSave6, NULL);
	LoadLocationMenu->AddStaticItem("Load Location 7", false, TeleToSave7, NULL);

	// All Online Players
	AllOnlinePlayers->SetMenuTitle("All Players");
	AllOnlinePlayers->AddStaticItem("Take All Weapons", false, TakeOnlineAllWeapons, NULL);
	AllOnlinePlayers->AddStaticItem("Explode All Players", false, BlowUpAllOnlinePlayers, NULL);
	AllOnlinePlayers->AddStaticItem("Kick All Players from Vehicle", false, AllKickedFromVeh, NULL);
	AllOnlinePlayers->AddStaticItem("Cash Drop Lobby", true, AllCashDrop, NULL);
	//AllOnlinePlayers->AddStaticItem("Delete Everyones Vehicle", false, DeleteAllPlayersVehicles, NULL);

	
	// Vehicle Spawner Menu
	CarSpawner->SetMenuTitle("Vehicle Spawner");
	CarSpawner->AddSubMenu("Heist Vehicles", CarSpawnerMenu23);
	CarSpawner->AddSubMenu("Ill Gotten Gains Vehicles", CarSpawnerMenu24);
	CarSpawner->AddSubMenu("Favorites", CarSpawnerMenu0);
	CarSpawner->AddSubMenu("Super", CarSpawnerMenu1);
	CarSpawner->AddSubMenu("Sports", CarSpawnerMenu2);
	CarSpawner->AddSubMenu("Coupes", CarSpawnerMenu3);
	CarSpawner->AddSubMenu("Sedans", CarSpawnerMenu4);
	CarSpawner->AddSubMenu("Emergency", CarSpawnerMenu5);
	CarSpawner->AddSubMenu("Off Road", CarSpawnerMenu6);
	CarSpawner->AddSubMenu("Muscle", CarSpawnerMenu7);
	CarSpawner->AddSubMenu("SUVs", CarSpawnerMenu8);
	CarSpawner->AddSubMenu("Motorcycles", CarSpawnerMenu9);
	CarSpawner->AddSubMenu("Helicopters", CarSpawnerMenu10);
	CarSpawner->AddSubMenu("Planes", CarSpawnerMenu11);
	CarSpawner->AddSubMenu("Page 2", CarSpawner2);

	// Vehicle Spawner Menu Page 2
	CarSpawner2->SetMenuTitle("Vehicle Spawner (Page 2)");
	CarSpawner2->AddSubMenu("Commercial", CarSpawnerMenu12);
	CarSpawner2->AddSubMenu("Industrial", CarSpawnerMenu13);
	CarSpawner2->AddSubMenu("Utility", CarSpawnerMenu14);
	CarSpawner2->AddSubMenu("Trailers", CarSpawnerMenu15);
	CarSpawner2->AddSubMenu("Compacts", CarSpawnerMenu16);
	CarSpawner2->AddSubMenu("Military", CarSpawnerMenu17);
	CarSpawner2->AddSubMenu("Service", CarSpawnerMenu18);
	CarSpawner2->AddSubMenu("Sports Classics", CarSpawnerMenu19);
	CarSpawner2->AddSubMenu("Vans", CarSpawnerMenu20);
	CarSpawner2->AddSubMenu("Bicycles", CarSpawnerMenu21);
	CarSpawner2->AddSubMenu("Boats", CarSpawnerMenu22);

	//Ill Gotten Gains Vehicles
	CarSpawnerMenu24->SetMenuTitle("Ill Gotten Gains");
	CarSpawnerMenu24->AddStaticItem("Osiris", false, GainsOsiris, NULL);
	CarSpawnerMenu24->AddStaticItem("Stirling GT", false, GainsStirling, NULL);
	CarSpawnerMenu24->AddStaticItem("Virgo", false, GainsVirgo, NULL);
	CarSpawnerMenu24->AddStaticItem("Windsor", false, GainsWindsor, NULL);
	CarSpawnerMenu24->AddStaticItem("Gold Luxor", false, GainsLuxor, NULL);
	CarSpawnerMenu24->AddStaticItem("Gold Swift", false, GainsSwift, NULL);

	// Favorites
	CarSpawnerMenu0->SetMenuTitle("Favorites");
	CarSpawnerMenu0->AddStaticItem("Lazer", false, SpawnLazer, NULL);
	CarSpawnerMenu0->AddStaticItem("Hakuchou", false, SpawnHakuchou, NULL);
	CarSpawnerMenu0->AddStaticItem("Buzzard", false, SpawnBuzzard, NULL);
	CarSpawnerMenu0->AddStaticItem("Tank", false, SpawnTank, NULL);
	CarSpawnerMenu0->AddStaticItem("FIB", false, SpawnFIB, NULL);
	CarSpawnerMenu0->AddStaticItem("FIB2", false, SpawnFIB2, NULL);
	CarSpawnerMenu0->AddStaticItem("Police", false, SpawnPolice, NULL);
	CarSpawnerMenu0->AddStaticItem("Police Buffalo", false, SpawnPolice3, NULL);
	CarSpawnerMenu0->AddStaticItem("Unmarked", false, SpawnUnmarked, NULL);
	CarSpawnerMenu0->AddStaticItem("Jester2", false, SpawnJester2, NULL);
	CarSpawnerMenu0->AddSubMenu("Page 2", CarSpawnerMenu0P2);

	// Favorites Page 2
	CarSpawnerMenu0P2->SetMenuTitle("Favorites (Page 2)");
	CarSpawnerMenu0P2->AddStaticItem("Dubsta 6x6", false, Spawn6x6, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Monster", false, SpawnMonster, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Mesa(Mercs)", false, SpawnMesa3, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Phantom", false, SpawnPhantom, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Bus", false, SpawnBus, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Speeder", false, SpawnSpeeder, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Blimp", false, SpawnBlimp, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Jumbo Jet", false, SpawnJumbo, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Cargo Plane", false, SpawnCargo, NULL);
	CarSpawnerMenu0P2->AddStaticItem("Dozer", false, SpawnDozer, NULL);

	// Heist Vehicles
	CarSpawnerMenu23->SetMenuTitle("Heist Vehicles");
	CarSpawnerMenu23->AddStaticItem("Hydra", false, SpawnHydra, NULL);
	CarSpawnerMenu23->AddStaticItem("Mule3", false, SpawnMule3, NULL);
	CarSpawnerMenu23->AddStaticItem("Tanker2", false, SpawnTanker2, NULL);
	CarSpawnerMenu23->AddStaticItem("Casco", false, SpawnCasco, NULL);
	CarSpawnerMenu23->AddStaticItem("Boxville4", false, SpawnBoxville4, NULL);
	CarSpawnerMenu23->AddStaticItem("Insurgent", false, SpawnInsurgent, NULL);
	CarSpawnerMenu23->AddStaticItem("Insurgent2", false, SpawnInsurgent2, NULL);
	CarSpawnerMenu23->AddStaticItem("Gang Burrito2", false, SpawnGBurrito2, NULL);
	CarSpawnerMenu23->AddStaticItem("Technical", false, SpawnTechnical, NULL);
	CarSpawnerMenu23->AddStaticItem("Dinghy3", false, SpawnDinghy3, NULL);
	CarSpawnerMenu23->AddStaticItem("Savage", false, SpawnSavage, NULL);
	CarSpawnerMenu23->AddStaticItem("Enduro", false, SpawnEnduro, NULL);
	CarSpawnerMenu23->AddStaticItem("Guardian", false, SpawnGuardian, NULL);
	CarSpawnerMenu23->AddStaticItem("Lectro", false, SpawnLectro, NULL);
	CarSpawnerMenu23->AddStaticItem("Kumura", false, SpawnKumura, NULL);
	CarSpawnerMenu23->AddStaticItem("Kumura2", false, SpawnKumura2, NULL);
	CarSpawnerMenu23->AddStaticItem("Trash2", false, SpawnTrash2, NULL);
	CarSpawnerMenu23->AddStaticItem("Barracks3", false, SpawnBarracks3, NULL);
	CarSpawnerMenu23->AddStaticItem("Valkyrie", false, SpawnValkyrie, NULL);
	CarSpawnerMenu23->AddStaticItem("Velum2", false, SpawnVelum2, NULL);
	CarSpawnerMenu23->AddStaticItem("Slamvan2", false, SpawnSlamvan2, NULL);

	// Super
	CarSpawnerMenu1->SetMenuTitle("Super");
	CarSpawnerMenu1->AddStaticItem("Adder", false, SpawnAdder, NULL);
	CarSpawnerMenu1->AddStaticItem("Bullet", false, SpawnBullet, NULL);
	CarSpawnerMenu1->AddStaticItem("Cheetah", false, SpawnCheetah, NULL);
	CarSpawnerMenu1->AddStaticItem("EntityXF", false, SpawnEntityXF, NULL);
	CarSpawnerMenu1->AddStaticItem("Infernus", false, SpawnInfernus, NULL);
	CarSpawnerMenu1->AddStaticItem("TurismoR", false, SpawnTurismoR, NULL);
	CarSpawnerMenu1->AddStaticItem("Vacca", false, SpawnVacca, NULL);
	CarSpawnerMenu1->AddStaticItem("Voltic", false, SpawnVoltic, NULL);
	CarSpawnerMenu1->AddStaticItem("Zentorno", false, SpawnZentorno, NULL);

	// Sports
	CarSpawnerMenu2->SetMenuTitle("Sports");
	CarSpawnerMenu2->AddStaticItem("9F", false, Spawn9F, NULL);
	CarSpawnerMenu2->AddStaticItem("9F Convertible", false, Spawn9F2, NULL);
	CarSpawnerMenu2->AddStaticItem("Alpha", false, SpawnAlpha, NULL);
	CarSpawnerMenu2->AddStaticItem("Banshee", false, SpawnBanshee, NULL);
	CarSpawnerMenu2->AddStaticItem("Buffalo", false, SpawnBuffalo, NULL);
	CarSpawnerMenu2->AddStaticItem("Franklins Buffalo", false, SpawnBuffalo2, NULL);
	CarSpawnerMenu2->AddStaticItem("Carbonizzare", false, SpawnCarbonizzare, NULL);
	CarSpawnerMenu2->AddStaticItem("Comet", false, SpawnComet, NULL);
	CarSpawnerMenu2->AddStaticItem("Coquette", false, SpawnCoquette, NULL);
	CarSpawnerMenu2->AddStaticItem("Elegy", false, SpawnElegy, NULL);
	CarSpawnerMenu2->AddStaticItem("Feltzer", false, SpawnFeltzer, NULL);
	CarSpawnerMenu2->AddStaticItem("FuroreGT", false, SpawnFuroreGT, NULL);
	CarSpawnerMenu2->AddStaticItem("Fusilade", false, SpawnFusilade, NULL);
	CarSpawnerMenu2->AddSubMenu("Page 2", CarSpawnerMenu2P2);

	// Sports Page 2
	CarSpawnerMenu2P2->SetMenuTitle("Sports (Page 2)");
	CarSpawnerMenu2P2->AddStaticItem("Futo", false, SpawnFuto, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Jester", false, SpawnJester, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Jester2", false, SpawnJester2, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Khamelion", false, SpawnKhamelion, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Massacro", false, SpawnMassacro, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Massacro2", false, SpawnMassacro2, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Penumbra", false, SpawnPenumbra, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Rapid GT", false, SpawnRapidGT, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Rapid GT Convertible", false, SpawnRapidGT2, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Schwartzer", false, SpawnSchwartzer, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Sultan", false, SpawnSultan, NULL);
	CarSpawnerMenu2P2->AddStaticItem("Surano", false, SpawnSurano, NULL);

	// Coupes
	CarSpawnerMenu3->SetMenuTitle("Coupes");
	CarSpawnerMenu3->AddStaticItem("Cognoscenti", false, SpawnCognoscenti, NULL);
	CarSpawnerMenu3->AddStaticItem("Exemplar", false, SpawnExemplar, NULL);
	CarSpawnerMenu3->AddStaticItem("F620", false, SpawnF620, NULL);
	CarSpawnerMenu3->AddStaticItem("Felon", false, SpawnFelon, NULL);
	CarSpawnerMenu3->AddStaticItem("Felon2", false, SpawnFelon2, NULL);
	CarSpawnerMenu3->AddStaticItem("Jackal", false, SpawnJackal, NULL);
	CarSpawnerMenu3->AddStaticItem("Oracle", false, SpawnOracle, NULL);
	CarSpawnerMenu3->AddStaticItem("Oracle2", false, SpawnOracle2, NULL);
	CarSpawnerMenu3->AddStaticItem("Sentinel", false, SpawnSentinel, NULL);
	CarSpawnerMenu3->AddStaticItem("Sentinel2", false, SpawnSentinel2, NULL);
	CarSpawnerMenu3->AddStaticItem("Zion", false, SpawnZion, NULL);
	CarSpawnerMenu3->AddStaticItem("Zion2", false, SpawnZion2, NULL);

	// Sedans
	CarSpawnerMenu4->SetMenuTitle("Sedans");
	CarSpawnerMenu4->AddStaticItem("Asea", false, SpawnAsea, NULL);
	CarSpawnerMenu4->AddStaticItem("Snow Asea", false, SpawnAsea2, NULL);
	CarSpawnerMenu4->AddStaticItem("Asterope", false, SpawnAsterope, NULL);
	CarSpawnerMenu4->AddStaticItem("Emperor", false, SpawnEmperor, NULL);
	CarSpawnerMenu4->AddStaticItem("Rusty Emperor", false, SpawnEmperor2, NULL);
	CarSpawnerMenu4->AddStaticItem("Snow Emperor", false, SpawnEmperor3, NULL);
	CarSpawnerMenu4->AddStaticItem("Fugitive", false, SpawnFugitive, NULL);
	CarSpawnerMenu4->AddStaticItem("Glendale", false, SpawnGlendale, NULL);
	CarSpawnerMenu4->AddStaticItem("Ingot", false, SpawnIngot, NULL);
	CarSpawnerMenu4->AddStaticItem("Intruder", false, SpawnIntruder, NULL);
	CarSpawnerMenu4->AddStaticItem("Premier", false, SpawnPremier, NULL);
	CarSpawnerMenu4->AddSubMenu("Page 2", CarSpawnerMenu4P2);

	// Sedans Page 2
	CarSpawnerMenu4P2->SetMenuTitle("Sedans (Page 2)");
	CarSpawnerMenu4P2->AddStaticItem("Primo", false, SpawnPrimo, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Regina", false, SpawnRegina, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Romero Hearse", false, SpawnRomero, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Schafter", false, SpawnSchafter, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Stanier", false, SpawnStanier, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Stratum", false, SpawnStratum, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Stretch", false, SpawnStretch, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Super Diamond", false, SpawnSuperDiamond, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Surge", false, SpawnSurge, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Tailgater", false, SpawnTailgater, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Warrener", false, SpawnWarrener, NULL);
	CarSpawnerMenu4P2->AddStaticItem("Washington", false, SpawnWashington, NULL);

	// Emergency
	CarSpawnerMenu5->SetMenuTitle("Emergency");
	CarSpawnerMenu5->AddStaticItem("Ambulance", false, SpawnAmbulance, NULL);
	CarSpawnerMenu5->AddStaticItem("FIB", false, SpawnFIB, NULL);
	CarSpawnerMenu5->AddStaticItem("FIB2", false, SpawnFIB2, NULL);
	CarSpawnerMenu5->AddStaticItem("Fire Truck", false, SpawnFireTruck, NULL);
	CarSpawnerMenu5->AddStaticItem("Life Guard", false, SpawnLGuard, NULL);
	CarSpawnerMenu5->AddStaticItem("Park Ranger", false, SpawnPRanger, NULL);
	CarSpawnerMenu5->AddStaticItem("Police Bike", false, SpawnPBike, NULL);
	CarSpawnerMenu5->AddStaticItem("Police Cruiser", false, SpawnPolice2, NULL);
	CarSpawnerMenu5->AddStaticItem("Police", false, SpawnPolice, NULL);
	CarSpawnerMenu5->AddStaticItem("Police Buffalo", false, SpawnPolice3, NULL);
	CarSpawnerMenu5->AddStaticItem("Prison Bus", false, SpawnPBus, NULL);
	CarSpawnerMenu5->AddStaticItem("Riot", false, SpawnRiot, NULL);
	CarSpawnerMenu5->AddStaticItem("Police Van", false, SpawnPVan, NULL);
	CarSpawnerMenu5->AddStaticItem("Sheriff Cruiser", false, SpawnSheriff, NULL);
	CarSpawnerMenu5->AddStaticItem("Sheriff SUV", false, SpawnSheriff2, NULL);
	CarSpawnerMenu5->AddStaticItem("Snow Police Rancher", false, SpawnRancherSP, NULL);
	CarSpawnerMenu5->AddStaticItem("Snow Police Esperanto", false, SpawnEsperantoSP, NULL);
	CarSpawnerMenu5->AddStaticItem("Unmarked", false, SpawnUnmarked, NULL);

	// Off Road
	CarSpawnerMenu6->SetMenuTitle("Off Road");
	CarSpawnerMenu6->AddStaticItem("Bifta", false, SpawnBifta, NULL);
	CarSpawnerMenu6->AddStaticItem("Blazer", false, SpawnBlazer, NULL);
	CarSpawnerMenu6->AddStaticItem("Lifeguard Blazer", false, SpawnBlazer2, NULL);
	CarSpawnerMenu6->AddStaticItem("Trevors Blazer", false, SpawnBlazer3, NULL);
	CarSpawnerMenu6->AddStaticItem("Bodhi", false, SpawnBodhi, NULL);
	CarSpawnerMenu6->AddStaticItem("Dubsta 6x6", false, Spawn6x6, NULL);
	CarSpawnerMenu6->AddStaticItem("Dune", false, SpawnDune, NULL);
	CarSpawnerMenu6->AddStaticItem("Duneloader", false, SpawnDuneloader, NULL);
	CarSpawnerMenu6->AddStaticItem("Injection", false, SpawnInjection, NULL);
	CarSpawnerMenu6->AddStaticItem("Kalahari", false, SpawnKalahari, NULL);
	CarSpawnerMenu6->AddStaticItem("Monster", false, SpawnMonster, NULL);
	CarSpawnerMenu6->AddStaticItem("Mesa(Mercs)", false, SpawnMesa3, NULL);
	CarSpawnerMenu6->AddStaticItem("RancherXL", false, SpawnRancherXL, NULL);
	CarSpawnerMenu6->AddStaticItem("Rusty Rebel", false, SpawnRebel, NULL);
	CarSpawnerMenu6->AddStaticItem("Clean Rebel", false, SpawnRebel2, NULL);
	CarSpawnerMenu6->AddStaticItem("SandkingSWB", false, SpawnSandkingSWB, NULL);
	CarSpawnerMenu6->AddStaticItem("SandkingXL", false, SpawnSandkingXL, NULL);
	CarSpawnerMenu6->AddStaticItem("Snow Rancher", false, SpawnRancherSnow, NULL);
	CarSpawnerMenu6->AddStaticItem("Space Docker", false, SpawnSpace, NULL);

	// Muscle
	CarSpawnerMenu7->SetMenuTitle("Muscle");
	CarSpawnerMenu7->AddStaticItem("Blade", false, SpawnBlade, NULL);
	CarSpawnerMenu7->AddStaticItem("Buccaneer", false, SpawnBuccaneer, NULL);
	CarSpawnerMenu7->AddStaticItem("Dominator", false, SpawnDominator, NULL);
	CarSpawnerMenu7->AddStaticItem("Gauntlet", false, SpawnGauntlet, NULL);
	CarSpawnerMenu7->AddStaticItem("Hotknife", false, SpawnHotknife, NULL);
	CarSpawnerMenu7->AddStaticItem("Phoenix", false, SpawnPhoenix, NULL);
	CarSpawnerMenu7->AddStaticItem("Picador", false, SpawnPicador, NULL);
	CarSpawnerMenu7->AddStaticItem("Rat Loader", false, SpawnRatLoader, NULL);
	CarSpawnerMenu7->AddStaticItem("Rat Loader2", false, SpawnRatLoader2, NULL);
	CarSpawnerMenu7->AddStaticItem("Ruiner", false, SpawnRuiner, NULL);
	CarSpawnerMenu7->AddStaticItem("SabreGT", false, SpawnSabreGT, NULL);
	CarSpawnerMenu7->AddStaticItem("SlamVan", false, SpawnSlamVan, NULL);
	CarSpawnerMenu7->AddStaticItem("Vigero", false, SpawnVigero, NULL);
	CarSpawnerMenu7->AddStaticItem("Voodoo", false, SpawnVoodoo, NULL);

	// SUVs
	CarSpawnerMenu8->SetMenuTitle("SUVs");
	CarSpawnerMenu8->AddStaticItem("Baller", false, SpawnBaller, NULL);
	CarSpawnerMenu8->AddStaticItem("Baller2", false, SpawnBaller2, NULL);
	CarSpawnerMenu8->AddStaticItem("BeeJayXL", false, SpawnBeeJayXL, NULL);
	CarSpawnerMenu8->AddStaticItem("Old Cavalcade", false, SpawnCavalcade, NULL);
	CarSpawnerMenu8->AddStaticItem("New Cavalcade", false, SpawnCavalcade2, NULL);
	CarSpawnerMenu8->AddStaticItem("Dubsta", false, SpawnDubsta, NULL);
	CarSpawnerMenu8->AddStaticItem("Dubsta2", false, SpawnDubsta2, NULL);
	CarSpawnerMenu8->AddStaticItem("FQ2", false, SpawnFQ2, NULL);
	CarSpawnerMenu8->AddStaticItem("Granger", false, SpawnGranger, NULL);
	CarSpawnerMenu8->AddStaticItem("Gresley", false, SpawnGresley, NULL);
	CarSpawnerMenu8->AddSubMenu("Page 2", CarSpawnerMenu8P2);

	// SUVs Page 2
	CarSpawnerMenu8P2->SetMenuTitle("SUVs (Page 2)");
	CarSpawnerMenu8P2->AddStaticItem("Habanero", false, SpawnHabanero, NULL);
	CarSpawnerMenu8P2->AddStaticItem("HuntleyS", false, SpawnHuntleyS, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Landstalker", false, SpawnLandstalker, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Mesa", false, SpawnMesa, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Snow Mesa", false, SpawnMesa2, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Patriot", false, SpawnPatriot, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Radius", false, SpawnRadius, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Rocoto", false, SpawnRocoto, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Seminole", false, SpawnSeminole, NULL);
	CarSpawnerMenu8P2->AddStaticItem("Serrano", false, SpawnSerrano, NULL);

	// Motorcycles
	CarSpawnerMenu9->SetMenuTitle("Motorcycles");
	CarSpawnerMenu9->AddStaticItem("Akuma", false, SpawnAkuma, NULL);
	CarSpawnerMenu9->AddStaticItem("Bagger", false, SpawnBagger, NULL);
	CarSpawnerMenu9->AddStaticItem("Bati801", false, SpawnBati801, NULL);
	CarSpawnerMenu9->AddStaticItem("Bati801RR", false, SpawnBati801RR, NULL);
	CarSpawnerMenu9->AddStaticItem("Carbon RS", false, SpawnCarbonRS, NULL);
	CarSpawnerMenu9->AddStaticItem("Daemon", false, SpawnDaemon, NULL);
	CarSpawnerMenu9->AddStaticItem("DoubleT", false, SpawnDoubleT, NULL);
	CarSpawnerMenu9->AddStaticItem("Faggio", false, SpawnFaggio, NULL);
	CarSpawnerMenu9->AddStaticItem("Hakuchou", false, SpawnHakuchou, NULL);
	CarSpawnerMenu9->AddStaticItem("Hexer", false, SpawnHexer, NULL);
	CarSpawnerMenu9->AddSubMenu("Page 2", CarSpawnerMenu9P2);

	// Motorcycles Page 2
	CarSpawnerMenu9P2->SetMenuTitle("Motorcycles (Page 2)");
	CarSpawnerMenu9P2->AddStaticItem("Innovation", false, SpawnInnovation, NULL);
	CarSpawnerMenu9P2->AddStaticItem("Nemesis", false, SpawnNemesis, NULL);
	CarSpawnerMenu9P2->AddStaticItem("PCJ600", false, SpawnPCJ600, NULL);
	CarSpawnerMenu9P2->AddStaticItem("Ruffian", false, SpawnRuffian, NULL);
	CarSpawnerMenu9P2->AddStaticItem("Sanchez", false, SpawnSanchez, NULL);
	CarSpawnerMenu9P2->AddStaticItem("Sanchez2", false, SpawnSanchez2, NULL);
	CarSpawnerMenu9P2->AddStaticItem("Sovereign", false, SpawnSovereign, NULL);
	CarSpawnerMenu9P2->AddStaticItem("Thrust", false, SpawnThrust, NULL);
	CarSpawnerMenu9P2->AddStaticItem("Vader", false, SpawnVader, NULL);

	// Helicopters
	CarSpawnerMenu10->SetMenuTitle("Helicopters");
	CarSpawnerMenu10->AddStaticItem("Annihilator", false, SpawnAnnihilator, NULL);
	CarSpawnerMenu10->AddStaticItem("Buzzard(No Guns)", false, SpawnBuzzard2, NULL);
	CarSpawnerMenu10->AddStaticItem("Buzzard", false, SpawnBuzzard, NULL);
	CarSpawnerMenu10->AddStaticItem("Cargobob", false, SpawnCargobob, NULL);
	CarSpawnerMenu10->AddStaticItem("Medic Cargobob", false, SpawnCargobob2, NULL);
	CarSpawnerMenu10->AddStaticItem("Trevors CargoBob", false, SpawnCargobob3, NULL);
	CarSpawnerMenu10->AddStaticItem("Frogger", false, SpawnFrogger, NULL);
	CarSpawnerMenu10->AddStaticItem("FIB/Trevors Frogger", false, SpawnFrogger2, NULL);
	CarSpawnerMenu10->AddStaticItem("Maverick", false, SpawnMaverick, NULL);
	CarSpawnerMenu10->AddStaticItem("Police Maverick", false, SpawnPMav, NULL);
	CarSpawnerMenu10->AddStaticItem("Skylift", false, SpawnSkylift, NULL);
	CarSpawnerMenu10->AddStaticItem("Swift", false, SpawnSwift, NULL);

	// Planes
	CarSpawnerMenu11->SetMenuTitle("Planes");
	CarSpawnerMenu11->AddStaticItem("Blimp", false, SpawnBlimp, NULL);
	CarSpawnerMenu11->AddStaticItem("Besra", false, SpawnBesra, NULL);
	CarSpawnerMenu11->AddStaticItem("Cargo Plane", false, SpawnCargo, NULL);
	CarSpawnerMenu11->AddStaticItem("Cuban 800", false, SpawnCuban800, NULL);
	CarSpawnerMenu11->AddStaticItem("Duster", false, SpawnDuster, NULL);
	CarSpawnerMenu11->AddStaticItem("Jumbo Jet", false, SpawnJumbo, NULL);
	CarSpawnerMenu11->AddStaticItem("Luxor", false, SpawnLuxor, NULL);
	CarSpawnerMenu11->AddStaticItem("Mallard", false, SpawnMallard, NULL);
	CarSpawnerMenu11->AddStaticItem("Mammatus", false, SpawnMammatus, NULL);
	CarSpawnerMenu11->AddStaticItem("MilJet", false, SpawnMilJet, NULL);
	CarSpawnerMenu11->AddStaticItem("Lazer", false, SpawnLazer, NULL);
	CarSpawnerMenu11->AddStaticItem("Shamal", false, SpawnShamal, NULL);
	CarSpawnerMenu11->AddStaticItem("Titan", false, SpawnTitan, NULL);
	CarSpawnerMenu11->AddStaticItem("Velum", false, SpawnVelum, NULL);
	CarSpawnerMenu11->AddStaticItem("Vestra", false, SpawnVestra, NULL);

	// Commercial
	CarSpawnerMenu12->SetMenuTitle("Commercial");
	CarSpawnerMenu12->AddStaticItem("Benson", false, SpawnBenson, NULL);
	CarSpawnerMenu12->AddStaticItem("Biff", false, SpawnBiff, NULL);
	CarSpawnerMenu12->AddStaticItem("Hauler", false, SpawnHauler, NULL);
	CarSpawnerMenu12->AddStaticItem("Mule", false, SpawnMule, NULL);
	CarSpawnerMenu12->AddStaticItem("Packer", false, SpawnPacker, NULL);
	CarSpawnerMenu12->AddStaticItem("Phantom", false, SpawnPhantom, NULL);
	CarSpawnerMenu12->AddStaticItem("Pounder", false, SpawnPounder, NULL);
	CarSpawnerMenu12->AddStaticItem("Stockade", false, SpawnStockade, NULL);
	CarSpawnerMenu12->AddStaticItem("Snow Stockade", false, SpawnStockadeSnow, NULL);

	// Industrial
	CarSpawnerMenu13->SetMenuTitle("Industrial");
	CarSpawnerMenu13->AddStaticItem("Dock Handler", false, SpawnDHandler, NULL);
	CarSpawnerMenu13->AddStaticItem("Dozer", false, SpawnDozer, NULL);
	CarSpawnerMenu13->AddStaticItem("Dump", false, SpawnDump, NULL);
	CarSpawnerMenu13->AddStaticItem("Flatbed", false, SpawnFlatbed, NULL);
	CarSpawnerMenu13->AddStaticItem("Mixer", false, SpawnMixer, NULL);
	CarSpawnerMenu13->AddStaticItem("Mixer2", false, SpawnMixer2, NULL);
	CarSpawnerMenu13->AddStaticItem("Rubble", false, SpawnRubble, NULL);
	CarSpawnerMenu13->AddStaticItem("Tipper", false, SpawnTipper, NULL);
	CarSpawnerMenu13->AddStaticItem("Tipper2", false, SpawnTipper2, NULL);

	// Utility
	CarSpawnerMenu14->SetMenuTitle("Utility");
	CarSpawnerMenu14->AddStaticItem("Airtug", false, SpawnAirtug, NULL);
	CarSpawnerMenu14->AddStaticItem("Bison", false, SpawnBison, NULL);
	CarSpawnerMenu14->AddStaticItem("Bison2", false, SpawnBison2, NULL);
	CarSpawnerMenu14->AddStaticItem("Bison3", false, SpawnBison3, NULL);
	CarSpawnerMenu14->AddStaticItem("BobcatXL", false, SpawnBobcatXL, NULL);
	CarSpawnerMenu14->AddStaticItem("Caddy", false, SpawnCaddy, NULL);
	CarSpawnerMenu14->AddStaticItem("Caddy2", false, SpawnCaddy2, NULL);
	CarSpawnerMenu14->AddStaticItem("Cutter", false, SpawnCutter, NULL);
	CarSpawnerMenu14->AddStaticItem("Docktug", false, SpawnDocktug, NULL);
	CarSpawnerMenu14->AddStaticItem("Fieldmaster", false, SpawnFieldmaster, NULL);
	CarSpawnerMenu14->AddStaticItem("Forklift", false, SpawnForklift, NULL);
	CarSpawnerMenu14->AddStaticItem("Lawn Mower", false, SpawnMower, NULL);
	CarSpawnerMenu14->AddSubMenu("Page 2", CarSpawnerMenu14P2);

	// Utility Page 2
	CarSpawnerMenu14P2->SetMenuTitle("Utility (Page 2)");
	CarSpawnerMenu14P2->AddStaticItem("Ripley", false, SpawnRipley, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Sadler", false, SpawnSadler, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Snow Sadler", false, SpawnSadler2, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Scrap Truck", false, SpawnScrap, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Small Tow Truck", false, SpawnTow2, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Big Tow Truck", false, SpawnTow, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Tractor", false, SpawnTractor, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Snow Tractor", false, SpawnTractor2, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Utility Truck", false, SpawnUtility, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Utility Truck2", false, SpawnUtility2, NULL);
	CarSpawnerMenu14P2->AddStaticItem("Utility Truck3", false, SpawnUtility3, NULL);

	// Trailers
	CarSpawnerMenu15->SetMenuTitle("Trailers");
	CarSpawnerMenu15->AddStaticItem("Car Carrier", false, SpawnTR2, NULL);
	CarSpawnerMenu15->AddStaticItem("Marquis Trailer", false, SpawnTR3, NULL);
	CarSpawnerMenu15->AddStaticItem("Super Car Carrier", false, SpawnTR4, NULL);
	CarSpawnerMenu15->AddStaticItem("Log Trailer", false, SpawnLog, NULL);
	CarSpawnerMenu15->AddStaticItem("Metal Trailer", false, SpawnMetal, NULL);
	CarSpawnerMenu15->AddStaticItem("Random Ad Trailer", false, SpawnRandom, NULL);
	CarSpawnerMenu15->AddStaticItem("Big Goods Trailer", false, SpawnBig, NULL);
	CarSpawnerMenu15->AddStaticItem("Flatbed Trailer", false, SpawnFlat, NULL);
	CarSpawnerMenu15->AddStaticItem("Fame Or Shame Trailer", false, SpawnFame, NULL);
	CarSpawnerMenu15->AddStaticItem("Army Trailer", false, SpawnArmyT1, NULL);
	CarSpawnerMenu15->AddStaticItem("Army Trailer2", false, SpawnArmyT2, NULL);
	CarSpawnerMenu15->AddStaticItem("Army Trailer3", false, SpawnArmyT3, NULL);
	CarSpawnerMenu15->AddStaticItem("Boat Trailer", false, SpawnBoatT, NULL);
	CarSpawnerMenu15->AddStaticItem("Dock Trailer", false, SpawnDockT, NULL);
	CarSpawnerMenu15->AddStaticItem("Freight Trailer", false, SpawnFreightT, NULL);
	CarSpawnerMenu15->AddStaticItem("Tanker Trailer", false, SpawnTanker, NULL);
	CarSpawnerMenu15->AddStaticItem("Construction Trailer", false, SpawnConstruct, NULL);

	// Compacts
	CarSpawnerMenu16->SetMenuTitle("Compacts");
	CarSpawnerMenu16->AddStaticItem("Blista", false, SpawnBlista, NULL);
	CarSpawnerMenu16->AddStaticItem("Dilettante", false, SpawnDilettante, NULL);
	CarSpawnerMenu16->AddStaticItem("Issi", false, SpawnIssi, NULL);
	CarSpawnerMenu16->AddStaticItem("Panto", false, SpawnPanto, NULL);
	CarSpawnerMenu16->AddStaticItem("Prairie", false, SpawnPrairie, NULL);
	CarSpawnerMenu16->AddStaticItem("Rhapsody", false, SpawnRhapsody, NULL);

	// Military
	CarSpawnerMenu17->SetMenuTitle("Military");
	CarSpawnerMenu17->AddStaticItem("Barracks", false, SpawnBarracks, NULL);
	CarSpawnerMenu17->AddStaticItem("Barracks Semi", false, SpawnBarracks2, NULL);
	CarSpawnerMenu17->AddStaticItem("Crusader", false, SpawnCrusader, NULL);
	CarSpawnerMenu17->AddStaticItem("Tank", false, SpawnTank, NULL);

	// Service
	CarSpawnerMenu18->SetMenuTitle("Service");
	CarSpawnerMenu18->AddStaticItem("Airport Bus", false, SpawnAirportBus, NULL);
	CarSpawnerMenu18->AddStaticItem("Bus", false, SpawnBus, NULL);
	CarSpawnerMenu18->AddStaticItem("Dashound", false, SpawnDashound, NULL);
	CarSpawnerMenu18->AddStaticItem("Shuttle", false, SpawnShuttle, NULL);
	CarSpawnerMenu18->AddStaticItem("Taxi", false, SpawnTaxi, NULL);
	CarSpawnerMenu18->AddStaticItem("Tourbus", false, SpawnTourbus, NULL);
	CarSpawnerMenu18->AddStaticItem("Trashmaster", false, SpawnTrashmaster, NULL);

	// Sports Classics
	CarSpawnerMenu19->SetMenuTitle("Sports Classics");
	CarSpawnerMenu19->AddStaticItem("Coquette Classic", false, SpawnCoquette2, NULL);
	CarSpawnerMenu19->AddStaticItem("JB700", false, SpawnJB700, NULL);
	CarSpawnerMenu19->AddStaticItem("Manana", false, SpawnManana, NULL);
	CarSpawnerMenu19->AddStaticItem("Monroe", false, SpawnMonroe, NULL);
	CarSpawnerMenu19->AddStaticItem("Peyote", false, SpawnPeyote, NULL);
	CarSpawnerMenu19->AddStaticItem("Pigalle", false, SpawnPigalle, NULL);
	CarSpawnerMenu19->AddStaticItem("Roosevelt", false, SpawnBType, NULL);
	CarSpawnerMenu19->AddStaticItem("Stinger", false, SpawnStinger, NULL);
	CarSpawnerMenu19->AddStaticItem("StingerGT", false, SpawnStingerGT, NULL);
	CarSpawnerMenu19->AddStaticItem("Tornado", false, SpawnTornado, NULL);
	CarSpawnerMenu19->AddStaticItem("Tornado2", false, SpawnTornado2, NULL);
	CarSpawnerMenu19->AddStaticItem("Tornado3", false, SpawnTornado3, NULL);
	CarSpawnerMenu19->AddStaticItem("Tornado4", false, SpawnTornado4, NULL);
	CarSpawnerMenu19->AddStaticItem("ZType", false, SpawnZType, NULL);

	// Vans
	CarSpawnerMenu20->SetMenuTitle("Vans");
	CarSpawnerMenu20->AddStaticItem("Boxville", false, SpawnBoxville, NULL);
	CarSpawnerMenu20->AddStaticItem("Boxville2", false, SpawnBoxville2, NULL);
	CarSpawnerMenu20->AddStaticItem("Boxville3", false, SpawnBoxville3, NULL);
	CarSpawnerMenu20->AddStaticItem("Burrito", false, SpawnBurrito, NULL);
	CarSpawnerMenu20->AddStaticItem("Burrito2", false, SpawnBurrito2, NULL);
	CarSpawnerMenu20->AddStaticItem("Burrito3", false, SpawnBurrito3, NULL);
	CarSpawnerMenu20->AddStaticItem("Burrito4", false, SpawnBurrito4, NULL);
	CarSpawnerMenu20->AddStaticItem("Snow Burrito", false, SpawnBurrito5, NULL);
	CarSpawnerMenu20->AddStaticItem("Camper", false, SpawnCamper, NULL);
	CarSpawnerMenu20->AddStaticItem("Gang Burrito", false, SpawnGBurrito, NULL);
	CarSpawnerMenu20->AddStaticItem("Journey", false, SpawnJourney, NULL);
	CarSpawnerMenu20->AddSubMenu("Page 2", CarSpawnerMenu20P2);

	// Vans Page 2
	CarSpawnerMenu20P2->SetMenuTitle("Vans (Page 2)");
	CarSpawnerMenu20P2->AddStaticItem("Minivan", false, SpawnMinivan, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Paradise", false, SpawnParadise, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Pony", false, SpawnPony, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Weed Van", false, SpawnWeedVan, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Weazel News", false, SpawnRumpo, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Deludamol", false, SpawnRumpo2, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Speedo", false, SpawnSpeedo, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Clown Van", false, SpawnClown, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Surfer", false, SpawnSurfer, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Surfer2", false, SpawnSurfer2, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Taco Van", false, SpawnTacoVan, NULL);
	CarSpawnerMenu20P2->AddStaticItem("Youga", false, SpawnYouga, NULL);

	// Bicycles
	CarSpawnerMenu21->SetMenuTitle("Bicycles");
	CarSpawnerMenu21->AddStaticItem("BMX", false, SpawnBMX, NULL);
	CarSpawnerMenu21->AddStaticItem("Scorcher", false, SpawnScorcher, NULL);
	CarSpawnerMenu21->AddStaticItem("Cruiser", false, SpawnCruiser, NULL);
	CarSpawnerMenu21->AddStaticItem("Fixter", false, SpawnFixter, NULL);
	CarSpawnerMenu21->AddStaticItem("TriCycles", false, SpawnTriCycles, NULL);
	CarSpawnerMenu21->AddStaticItem("Whippet", false, SpawnWhippet, NULL);
	CarSpawnerMenu21->AddStaticItem("Endurex", false, SpawnEndurex, NULL);

	// Boats
	CarSpawnerMenu22->SetMenuTitle("Boats");
	CarSpawnerMenu22->AddStaticItem("Dinghy", false, SpawnDinghy, NULL);
	CarSpawnerMenu22->AddStaticItem("Jetmax", false, SpawnJetmax, NULL);
	CarSpawnerMenu22->AddStaticItem("Marquis", false, SpawnMarquis, NULL);
	CarSpawnerMenu22->AddStaticItem("Seashark", false, SpawnSeashark, NULL);
	CarSpawnerMenu22->AddStaticItem("Lifeguard Seashark", false, SpawnSeasharkLG, NULL);
	CarSpawnerMenu22->AddStaticItem("Squalo", false, SpawnSqualo, NULL);
	CarSpawnerMenu22->AddStaticItem("Suntrap", false, SpawnSuntrap, NULL);
	CarSpawnerMenu22->AddStaticItem("Tropic", false, SpawnTropic, NULL);
	CarSpawnerMenu22->AddStaticItem("Speeder", false, SpawnSpeeder, NULL);
	CarSpawnerMenu22->AddStaticItem("Police Boat", false, SpawnPredator, NULL);
	CarSpawnerMenu22->AddStaticItem("Submersible", false, SpawnSub, NULL);

	// Online Players
	onlinePlayers->SetMenuTitle("Players List");
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);
	onlinePlayers->AddSubMenu("Player", onlinePlayersSubMenu);

	//BlameList
	blamePlayers->SetMenuTitle("Player To Blame");
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 
	blamePlayers->AddStaticItem("Player", false, blameExplosion, NULL); 


    //blamedExplosion->SetMenuTitle("Blamed Options");
	//blamedExplosion->AddStaticItem("Kill By Blamed", false, killWithBlame, NULL);

	// Misc Options 
    MiscOptions->SetMenuTitle("Misc Stuff");
	MiscOptions->AddSubMenu("Model Changer", ModelChanger);
	MiscOptions->AddStaticItem("Invisible Player", true, InvisiblePlayer, NULL);
	MiscOptions->AddStaticItem("Clean Yourself", false, CleanPedBody, NULL);
	MiscOptions->AddStaticItem("Drunk Mode", false, DrunkMode, NULL);
	MiscOptions->AddStaticItem("Male Mode", false, NormalM, NULL);
	MiscOptions->AddStaticItem("Female Mode", false, NormalF, NULL);
	MiscOptions->AddSubMenu("Weather Options", Weather);
	MiscOptions->AddSubMenu("Recovery", Recovery);
	MiscOptions->AddSubMenu("Mini Games", MiniGamesSubMenu);
	//MiscOptions->AddSubMenu("Developer Testing Zone", DevTestingMenu);

	DevTestingMenu->SetMenuTitle("Untested Mods");
	DevTestingMenu->AddStaticItem("Start Vehicle Horn", false, creatorVehHorn, NULL);
	DevTestingMenu->AddStaticItem("Set Vehicle Alarm", false, creatorVehAlarm, NULL);
	//DevTestingMenu->AddStaticItem("Explode Creator Vehicle", false, creatorExplodeVeh, NULL);
	//DevTestingMenu->AddStaticItem("Teleport Gun", true, MoneyGun, NULL);
	//DevTestingMenu->AddStaticItem("Clear Nearby Cops", false, clearNearbyCops, NULL);
	//DevTestingMenu->AddStaticItem("Clear Nearby Objects", false, clearNearbyObjects, NULL);

	//MiscOptions->AddStaticItem("Drive Yourself To WP", false, DriveYourselfToWP, NULL);
	//MiscOptions->AddSubMenu("Security Cameras", SecCamerasMenu);
	//MiscOptions->AddStaticItem("Show Who Is Talking", true, ShowWhoIsTalking, NULL);
	//MiscOptions->AddStaticItem("Spawn Sentry Gun", true, SpawnSentryGun, NULL);
	//MiscOptions->AddStaticItem("Spawn Private Map Mod", false, SpawnMapModFort, NULL);
	//MiscOptions->AddSubMenu("Chop Anim's", ChopAnims);
	//MiscOptions->AddStaticItem("Load North Yankton", false, LoadNY, NULL);
	//MiscOptions->AddStaticItem("10 Car Garage Troll", true, GarageFan, NULL);
	//MiscOptions->AddStaticItem("Remove Fireworks Limit", false, FWLimit, NULL);
	//MiscOptions->AddStaticItem("Show Player Alpha", true, showEntityAlpha, NULL);

	SecCamerasMenu->SetMenuTitle("Security Cameras");
	SecCamerasMenu->AddStaticItem("LSC Camera", true, LSCSecCam, NULL);
	SecCamerasMenu->AddStaticItem("Eclipse Tower Camera", true, EclipseSecCam, NULL);

	MiniGamesSubMenu->SetMenuTitle("Mini Games");
	MiniGamesSubMenu->AddStaticItem("Mountain Money", true, MoneyTrollMiniGame, NULL);
	MiniGamesSubMenu->AddStaticItem("Object Cash Drop", true, ObjectCashDrop, NULL);
	//MiniGamesSubMenu->AddStaticItem("Creator Mode", true, ToggleCreator, NULL);

	// Object Spawner
	ObjectOptions->SetMenuTitle("Object Spawner Menu");
	ObjectOptions->AddStaticItem("Spawn Weed", false, SpawnWeed, NULL);
	ObjectOptions->AddStaticItem("Spawn Tarp Body", false, SpawnBody, NULL);
	ObjectOptions->AddStaticItem("Spawn Ramp", false, SpawnRamp, NULL);
	ObjectOptions->AddStaticItem("Spawn Body Parts", false, SpawnBodyParts, NULL);
	ObjectOptions->AddStaticItem("Spawn Alien Egg", false, SpawnEgg, NULL);
	ObjectOptions->AddStaticItem("Spawn Big Asteroid", false, SpawnAsteroid, NULL);
	ObjectOptions->AddStaticItem("Spawn Big UFO", false, SpawnUfo, NULL);
	ObjectOptions->AddStaticItem("Spawn Ferris Wheel", false, SpawnFerris, NULL);
	ObjectOptions->AddStaticItem("Spawn Guard Building", false, SpawnGuardBuilding, NULL);
	ObjectOptions->AddStaticItem("Spawn Guard Building 2", false, SpawnGuardBuilding2, NULL);
	ObjectOptions->AddStaticItem("Spawn Zapper", false, SpawnElectrical, NULL);
	ObjectOptions->AddStaticItem("Spawn Shipping Container", false, SpawnContainer, NULL); 
	ObjectOptions->AddStaticItem("Spawn WindMill", false, SpawnWindmill, NULL);
	ObjectOptions->AddStaticItem("Spawn Concrete Barrier Short", false, BarrierS, NULL);
	ObjectOptions->AddStaticItem("Spawn Concrete Barrier Long", false, BarrierL, NULL);
	ObjectOptions->AddStaticItem("Spawn Wooden Barrier", false, WBarrier, NULL);
	ObjectOptions->AddStaticItem("Spawn Wooden Arrow Barrier", false, AWBarrier, NULL);
	ObjectOptions->AddStaticItem("Spawn Road Cone", false, RoadCone, NULL);
	ObjectOptions->AddStaticItem("Spawn Custom Object", false, CustomObject, NULL);
	ObjectOptions->AddSubMenu("Page 2", ObjectSpawner2);
	//ObjectOptions->AddStaticItem("Spawn Big Turd", false, SpawnShit, NULL);

    ObjectSpawner2->SetMenuTitle("Object Spawner (Page 2)");
	ObjectSpawner2->AddStaticItem("Spawn Metal Barrier", false, MBarrier, NULL); 
	//ObjectSpawner2->AddStaticItem("Test Cage 2", false, TestCage2, NULL);
	//ObjectSpawner2->AddStaticItem("Test Cage 3", false, TestCage3, NULL);
	//ObjectSpawner2->AddStaticItem("Test Cage 4", false, TestCage4, NULL);
	//ObjectSpawner2->AddStaticItem("Spawn Bank Gate Door", false, SpawnBankVaultGateDoor, NULL);

	MovementMenu->SetMenuTitle("Object Movement");
	MovementMenu->AddStaticItem("Move Object Up", true, MoveUp, NULL);
	MovementMenu->AddStaticItem("Move Object Down", true, MoveDown, NULL);
	MovementMenu->AddStaticItem("+ Y Axis", true, MoveForward, NULL);
	MovementMenu->AddStaticItem("- Y Axis", true, MoveBackward, NULL);
	MovementMenu->AddStaticItem("+ X Axis", true, MoveRight, NULL);
	MovementMenu->AddStaticItem("- X Axis ", true, MoveLeft, NULL);
	MovementMenu->AddStaticItem("+ Pitch", false, PlusPitch, NULL);
	MovementMenu->AddStaticItem("- Pitch ", false, MinusPitch, NULL);
	MovementMenu->AddStaticItem("+ Roll ", false, PlusRoll, NULL);
	MovementMenu->AddStaticItem("- Roll ", false, MinusRoll, NULL);
	MovementMenu->AddStaticItem("+ Yaw", false, HeadingLeft, NULL);
	MovementMenu->AddStaticItem("- Yaw", false, HeadingRight, NULL);
	MovementMenu->AddStaticItem("Move Blockade Up", false, MoveBlockadeUp, NULL);
	MovementMenu->AddStaticItem("Move Blockade Down", false, MoveBlockadeDown, NULL);

	// Object Spawner Options
	ObjectOptions1->SetMenuTitle("Object Options");
	ObjectOptions1->AddSubMenu("Object Spawner", ObjectOptions); 
	ObjectOptions1->AddStaticItem("Copy Object", false, ObjectCopy, NULL);
	ObjectOptions1->AddSubMenu("Object Movement Menu", MovementMenu);
	ObjectOptions1->AddStaticItem("Detach Object", false, ObjectDetach, NULL);
	ObjectOptions1->AddStaticItem("Set Object Straight", false, ObjectFlat, NULL);
	ObjectOptions1->AddStaticItem("Freeze Object", false, FreezeObject, NULL);
	ObjectOptions1->AddStaticItem("Unfreeze Object", false, UnfreezeObject, NULL);
	ObjectOptions1->AddStaticItem("Snap To Ground Infront", false, SnapGround, NULL);
	ObjectOptions1->AddStaticItem("Show Coordinates", true, ShowCoords, NULL);
	ObjectOptions1->AddStaticItem("Show Rotations", true, ShowPitch, NULL);
	ObjectOptions1->AddStaticItem("Show Object Hash", true, ShowObjHash, NULL);
	ObjectOptions1->AddStaticItem("Object Invisibility", true, creatorInvisible, NULL);
	ObjectOptions1->AddStaticItem("Teleport To Object", false, creatorTeleToObj, NULL);
	ObjectOptions1->AddStaticItem("Forcefield On Object", true, creatorFieldToggle, NULL);
	ObjectOptions1->AddStaticItem("Delete Object", false, ObjectDelete, NULL);
	//ObjectOptions1->AddStaticItem("Creator Mode", true, ToggleCreator, NULL);
	//ObjectOptions1->AddStaticItem("Get Object Hash", false, ObjectHash, NULL);
	//ObjectOptions1->AddStaticItem("Get Object Coords", false, ObjectCoords, NULL);

	FunnyCarOptions->SetMenuTitle("Funny Vehicle Menu");
	FunnyCarOptions->AddStaticItem("UFO", false, FlyingAnus, NULL);
	FunnyCarOptions->AddStaticItem("Bumper Car", false, DodgemCar, NULL);
	//FunnyCarOptions->AddStaticItem("Dummy Plane", false, FlyingDummyPlane, NULL);

	ChopAnims->SetMenuTitle("Chops' Animation List");
	ChopAnims->AddStaticItem("Set Model as Chop", false, ChopModel1, NULL);
	ChopAnims->AddStaticItem("Piss Right", false, ChopPiss1, NULL);
	ChopAnims->AddStaticItem("Piss Right Idle", false, ChopPiss2, NULL);
	ChopAnims->AddStaticItem("Piss Right Exit", false, ChopPiss3, NULL);
	ChopAnims->AddStaticItem("Piss Dump Loop", false, ChopDump, NULL);
	ChopAnims->AddStaticItem("Chop Attack 1", false, ChopAttack2, NULL);
	ChopAnims->AddStaticItem("Chop Attack 2", false, ChopAttack1, NULL);
	ChopAnims->AddStaticItem("Chop Sex (dog model)", false, Chop, NULL);
	ChopAnims->AddStaticItem("Chop Ladydog Sex", false, ChopF, NULL);
	ChopAnims->AddStaticItem("Chop Take A Dump", false, CopHands, NULL);

	// Los Santos Customs
    ModShop->SetMenuTitle("Los Santos Customs");
	ModShop->AddSubMenu("Paint", VehPaintMenu);
	ModShop->AddSubMenu("Performance", PerformanceMenu);
	ModShop->AddSubMenu("Armour", ArmourMenu);
	ModShop->AddSubMenu("Body", BodyMenu);
	ModShop->AddSubMenu("Wheels", WheelMenu);
	ModShop->AddSubMenu("Horns", HornMenu);
	ModShop->AddSubMenu("Window Tint", TintMenu);
	ModShop->AddStaticItem("xxHASTERxx License Plate", false, StelioLicense, NULL);
	ModShop->AddStaticItem("Edit License Plate", false, ChangePlate1, NULL);
	ModShop->AddStaticItem("Xenon Headlights", true, LightToggle, NULL);
	ModShop->AddSubMenu("Open/Remove Options", OpenMenu);
	ModShop->AddSubMenu("Neons Menu", NeonMenu);
	ModShop->AddStaticItem("Install Max Upgrades", false, MaxLSCUpgrades, NULL);
	ModShop->AddStaticItem("Lower Suspension", true, LowerVehicle, NULL);

	NeonMenu->SetMenuTitle("Neons Menu");
	NeonMenu->AddStaticItem("Toggle Neons", true, ToggleNeon, NULL);
    NeonMenu->AddStaticItem("Red Neons", false, RedNeon, NULL);
	NeonMenu->AddStaticItem("Green Neons", false, GreenNeon, NULL);
	NeonMenu->AddStaticItem("Blue Neons", false, BlueNeon, NULL);
	NeonMenu->AddStaticItem("Pink Neons", false, PinkNeon, NULL);
	NeonMenu->AddStaticItem("Purple Neons", false, PurpleNeon, NULL);
	NeonMenu->AddStaticItem("Orange Neons", false, OrangeNeon, NULL);
	NeonMenu->AddStaticItem("Cyan Neons", false, CyanNeon, NULL);

	//Horn Menu
    HornMenu->SetMenuTitle("Horn Menu");
	HornMenu->AddStaticItem("Stock Horn", false, StockHorn, NULL);
	HornMenu->AddStaticItem("Truck Horn", false, Horn0, NULL);
	HornMenu->AddStaticItem("Police Horn", false, Horn1, NULL);
	HornMenu->AddStaticItem("Clown Horn", false, Horn2, NULL);
	HornMenu->AddStaticItem("Musical Horn 1", false, Horn3, NULL);
	HornMenu->AddStaticItem("Musical Horn 2", false, Horn4, NULL);
	HornMenu->AddStaticItem("Musical Horn 3", false, Horn5, NULL);
	HornMenu->AddStaticItem("Musical Horn 4", false, Horn6, NULL);
	HornMenu->AddStaticItem("Musical Horn 5", false, Horn7, NULL);
	HornMenu->AddStaticItem("Classical Horn 1", false, Horn8, NULL);
	HornMenu->AddStaticItem("Classical Horn 2", false, Horn9, NULL);
	HornMenu->AddSubMenu("Page 2", HornMenu2);

	//Horn Menu Page 2
    HornMenu2->SetMenuTitle("Horn Menu (Page 2)");
	HornMenu2->AddStaticItem("Classical Horn 3", false, Horn10, NULL);
	HornMenu2->AddStaticItem("Classical Horn 4", false, Horn11, NULL);
	HornMenu2->AddStaticItem("Classical Horn 5", false, Horn12, NULL);
	HornMenu2->AddStaticItem("Classical Horn 6", false, Horn13, NULL);
	HornMenu2->AddStaticItem("Classical Horn 7", false, Horn14, NULL);
	HornMenu2->AddStaticItem("Scale Do", false, Horn15, NULL);
	HornMenu2->AddStaticItem("Scale Re", false, Horn16, NULL);
	HornMenu2->AddStaticItem("Scale Mi", false, Horn17, NULL);
	HornMenu2->AddStaticItem("Scale Fa", false, Horn18, NULL);
	HornMenu2->AddStaticItem("Scale Sol", false, Horn19, NULL);
	HornMenu2->AddSubMenu("Page 3", HornMenu3);

	//Horn Menu Page 3
    HornMenu3->SetMenuTitle("Horn Menu (Page 3)");
	HornMenu3->AddStaticItem("Scale La", false, Horn20, NULL);
	HornMenu3->AddStaticItem("Scale Ti", false, Horn21, NULL);
	HornMenu3->AddStaticItem("Scale Do High", false, Horn22, NULL);
	HornMenu3->AddStaticItem("Jazz Horn 1", false, Horn23, NULL);
	HornMenu3->AddStaticItem("Jazz Horn 2", false, Horn24, NULL);
	HornMenu3->AddStaticItem("Jazz Horn 3", false, Horn25, NULL);
	HornMenu3->AddStaticItem("Jazz Horn Loop", false, Horn26, NULL);
	HornMenu3->AddStaticItem("Star Spangled Banner 1", false, Horn27, NULL);
	HornMenu3->AddStaticItem("Star Spangled Banner 2", false, Horn28, NULL);
	HornMenu3->AddStaticItem("Star Spangled Banner 3", false, Horn29, NULL);
	HornMenu3->AddStaticItem("Star Spangled Banner 4", false, Horn30, NULL);

	//Tint Menu
    TintMenu->SetMenuTitle("Window Tint");
	TintMenu->AddStaticItem("No Tint", false, Tint0, NULL);
	TintMenu->AddStaticItem("Light Tint", false, Tint1, NULL);
	TintMenu->AddStaticItem("Dark Tint", false, Tint2, NULL);
	TintMenu->AddStaticItem("Limo Tint", false, Tint4, NULL);
	TintMenu->AddStaticItem("Black Tint", false, Tint3, NULL);
	TintMenu->AddStaticItem("Green Tint", false, Tint5, NULL);

	//Open Menu
    OpenMenu->SetMenuTitle("Open/Remove Options");
	OpenMenu->AddStaticItem("Open Drivers Door", false, OpenDoor0, NULL);
	OpenMenu->AddStaticItem("Remove Drivers Door", false, RemoveDFDoor, NULL);
	OpenMenu->AddStaticItem("Open Passengers Door", false, OpenDoor1, NULL);
	OpenMenu->AddStaticItem("Remove Passengers Door", false, RemovePFDoor, NULL);
	OpenMenu->AddStaticItem("Open Drivers Rear Door", false, OpenDoor2, NULL);
	OpenMenu->AddStaticItem("Remove Drivers Rear Door", false, RemoveDRDoor, NULL);
	OpenMenu->AddStaticItem("Open Passengers Rear Door", false, OpenDoor3, NULL);
	OpenMenu->AddStaticItem("Remove Passengers Rear Door", false, RemovePRDoor, NULL);
	OpenMenu->AddStaticItem("Open Hood", false, OpenDoor4, NULL);
	OpenMenu->AddStaticItem("Remove Hood", false, RemoveHood, NULL);
	OpenMenu->AddStaticItem("Open Boot", false, OpenDoor5, NULL);
	OpenMenu->AddStaticItem("Remove Boot", false, RemoveBoot, NULL);

	//Armour Menu
	ArmourMenu->SetMenuTitle("Armour Upgrades");
	ArmourMenu->AddStaticItem("None", false, NoArmour, NULL);
	ArmourMenu->AddStaticItem("Armour Upgrade 20%", false, Armour0, NULL);
	ArmourMenu->AddStaticItem("Armour Upgrade 40%", false, Armour1, NULL);
	ArmourMenu->AddStaticItem("Armour Upgrade 60%", false, Armour2, NULL);
	ArmourMenu->AddStaticItem("Armour Upgrade 80%", false, Armour3, NULL);
	ArmourMenu->AddStaticItem("Armour Upgrade 100%", false, Armour4, NULL);

	// Body Menu
	BodyMenu->SetMenuTitle("Body Upgrades");
	BodyMenu->AddSubMenu("Front Bumbers", FbMenu);
	BodyMenu->AddSubMenu("Rear Bumpers", RbMenu);
	BodyMenu->AddSubMenu("Side Skirts", SkMenu);
	BodyMenu->AddSubMenu("Interiors/Chassis", InteriorMenu);
	BodyMenu->AddSubMenu("Hoods", HoodMenu);
	BodyMenu->AddSubMenu("Left Fenders", LFenderMenu);
	BodyMenu->AddSubMenu("Right Fenders", RFenderMenu);
	BodyMenu->AddSubMenu("Roofs", RoofMenu);
	BodyMenu->AddSubMenu("Spoilers", SpoilerMenu);
	BodyMenu->AddSubMenu("Grills", GrillMenu);

	// front bumpers
	FbMenu->SetMenuTitle("Front Bumper Upgrades");
	FbMenu->AddStaticItem("Stock Front Bumper", false, StockFb, NULL);
	FbMenu->AddStaticItem("Front Bumper 1", false, Fb0, NULL);
	FbMenu->AddStaticItem("Front Bumper 2", false, Fb1, NULL);
	FbMenu->AddStaticItem("Front Bumper 3", false, Fb2, NULL);
	FbMenu->AddStaticItem("Front Bumper 4", false, Fb3, NULL);
	FbMenu->AddStaticItem("Front Bumper 5", false, Fb4, NULL);
	FbMenu->AddStaticItem("Front Bumper 6", false, Fb5, NULL);

	// rear bumpers
	RbMenu->SetMenuTitle("Rear Bumper Upgrades");
	RbMenu->AddStaticItem("Stock Rear Bumper", false, StockRb, NULL);
	RbMenu->AddStaticItem("Rear Bumper 1", false, Rb0, NULL);
	RbMenu->AddStaticItem("Rear Bumper 2", false, Rb1, NULL);
	RbMenu->AddStaticItem("Rear Bumper 3", false, Rb2, NULL);
	RbMenu->AddStaticItem("Rear Bumper 4", false, Rb3, NULL);

	// spoilers
	SpoilerMenu->SetMenuTitle("Spoiler Upgrades");
	SpoilerMenu->AddStaticItem("Stock Spoiler", false, StockSpoiler, NULL);
	SpoilerMenu->AddStaticItem("Spoiler 1", false, Spoiler0, NULL);
	SpoilerMenu->AddStaticItem("Spoiler 2", false, Spoiler1, NULL);
	SpoilerMenu->AddStaticItem("Spoiler 3", false, Spoiler2, NULL);
	SpoilerMenu->AddStaticItem("Spoiler 4", false, Spoiler3, NULL);
	SpoilerMenu->AddStaticItem("Spoiler 5", false, Spoiler4, NULL);
	SpoilerMenu->AddStaticItem("Spoiler 6", false, Spoiler5, NULL);
	SpoilerMenu->AddStaticItem("Spoiler 7", false, Spoiler6, NULL);

	// side skirts
	SkMenu->SetMenuTitle("Side Skirts Upgrades");
	SkMenu->AddStaticItem("Stock Side Skirts", false, StockSk, NULL);
	SkMenu->AddStaticItem("Side Skirts 1", false, Sk0, NULL);
	SkMenu->AddStaticItem("Side Skirts 2", false, Sk1, NULL);
	SkMenu->AddStaticItem("Side Skirts 3", false, Sk2, NULL);
	SkMenu->AddStaticItem("Side Skirts 4", false, Sk3, NULL);

	// interiors
	InteriorMenu->SetMenuTitle("Interior Upgrades");
	InteriorMenu->AddStaticItem("Stock Interior/Chassis", false, StockInterior, NULL);
	InteriorMenu->AddStaticItem("Interior/Chassis 1", false, Interior0, NULL);
	InteriorMenu->AddStaticItem("Interior/Chassis 2", false, Interior1, NULL);
	InteriorMenu->AddStaticItem("Interior/Chassis 3", false, Interior2, NULL);
	InteriorMenu->AddStaticItem("Interior/Chassis 4", false, Interior3, NULL);

	// hoods 
	HoodMenu->SetMenuTitle("Hood Upgrades");
	HoodMenu->AddStaticItem("Stock Hood", false, StockHood, NULL);
	HoodMenu->AddStaticItem("Hood Upgrade 1", false, Hood0, NULL);
	HoodMenu->AddStaticItem("Hood Upgrade 2", false, Hood1, NULL);
	HoodMenu->AddStaticItem("Hood Upgrade 3", false, Hood2, NULL);
	HoodMenu->AddStaticItem("Hood Upgrade 4", false, Hood3, NULL);
	HoodMenu->AddStaticItem("Hood Upgrade 5", false, Hood4, NULL);

	// left fenders
	LFenderMenu->SetMenuTitle("Left Fender Upgrades");
	LFenderMenu->AddStaticItem("Stock Left Fender", false, StockLFender, NULL);
	LFenderMenu->AddStaticItem("Left Fender Upgrade 1", false, LFender0, NULL);
	LFenderMenu->AddStaticItem("Left Fender Upgrade 2", false, LFender1, NULL);
	LFenderMenu->AddStaticItem("Left Fender Upgrade 3", false, LFender2, NULL);

	// right fenders
	RFenderMenu->SetMenuTitle("Right Fender Upgrades");
	RFenderMenu->AddStaticItem("Stock Right Fender", false, StockRFender, NULL);
	RFenderMenu->AddStaticItem("Right Fender Upgrade 1", false, RFender0, NULL);
	RFenderMenu->AddStaticItem("Right Fender Upgrade 2", false, RFender1, NULL);
	RFenderMenu->AddStaticItem("Right Fender Upgrade 3", false, RFender2, NULL);

	// roofs 
	RoofMenu->SetMenuTitle("Roof Upgrades");
	RoofMenu->AddStaticItem("Stock Roof", false, StockRoof, NULL);
	RoofMenu->AddStaticItem("Roof Upgrade 1", false, Roof0, NULL);
	RoofMenu->AddStaticItem("Roof Upgrade 2", false, Roof1, NULL);
	RoofMenu->AddStaticItem("Roof Upgrade 3", false, Roof2, NULL);
	RoofMenu->AddStaticItem("Roof Upgrade 4", false, Roof3, NULL);

	// grills 
	GrillMenu->SetMenuTitle("Grille Upgrades");
	GrillMenu->AddStaticItem("Stock Grille", false, StockGrill, NULL);
	GrillMenu->AddStaticItem("Grille Upgrade 1", false, Grill0, NULL);
	GrillMenu->AddStaticItem("Grille Upgrade 2", false, Grill1, NULL);
	GrillMenu->AddStaticItem("Grille Upgrade 3", false, Grill2, NULL);
	GrillMenu->AddStaticItem("Grille Upgrade 4", false, Grill3, NULL);

	// performance menu
	PerformanceMenu->SetMenuTitle("Performance Upgrades");
	PerformanceMenu->AddSubMenu("Engine", EngineMenu);
	PerformanceMenu->AddSubMenu("Transmission", TransMenu);
	PerformanceMenu->AddSubMenu("Brakes", BrakesMenu);
	PerformanceMenu->AddSubMenu("Suspension", SuspMenu);
	PerformanceMenu->AddSubMenu("Exhaust", ExMenu);
	PerformanceMenu->AddStaticItem("Turbo", true, TurboToggle, NULL);

	// engine menu
	EngineMenu->SetMenuTitle("Engine Upgrades");
	EngineMenu->AddStaticItem("Stock Engine", false, EngineStock, NULL);
	EngineMenu->AddStaticItem("Engine Upgrade 1", false, Engine0, NULL);
	EngineMenu->AddStaticItem("Engine Upgrade 2", false, Engine1, NULL);
	EngineMenu->AddStaticItem("Engine Upgrade 3", false, Engine2, NULL);
	EngineMenu->AddStaticItem("Engine Upgrade 4", false, Engine3, NULL);
#ifdef PRIVATE
	EngineMenu->AddStaticItem("Custom Engine", false, TogglePerf, NULL);
#endif

	// trans menu
	TransMenu->SetMenuTitle("Transmission Upgrades");
	TransMenu->AddStaticItem("Stock Transmission", false, TranStock, NULL);
	TransMenu->AddStaticItem("Street Transmission", false, Tran0, NULL);
	TransMenu->AddStaticItem("Sports Transmission", false, Tran1, NULL);
	TransMenu->AddStaticItem("Race Transmission", false, Tran2, NULL);

	// brakes menu
	BrakesMenu->SetMenuTitle("Brake Upgrades");
	BrakesMenu->AddStaticItem("Stock Brakes", false, BrakeStock, NULL);
	BrakesMenu->AddStaticItem("Street Brakes", false, Brake0, NULL);
	BrakesMenu->AddStaticItem("Sports Brakes", false, Brake1, NULL);
	BrakesMenu->AddStaticItem("Race Brakes", false, Brake2, NULL);

	// suspension menu
	SuspMenu->SetMenuTitle("Suspension Upgrades");
	SuspMenu->AddStaticItem("Stock Suspension", false, SuspStock, NULL);
	SuspMenu->AddStaticItem("Lowered Suspension", false, Susp0, NULL);
	SuspMenu->AddStaticItem("Street Suspension", false, Susp1, NULL);
	SuspMenu->AddStaticItem("Sports Suspension", false, Susp2, NULL);
	SuspMenu->AddStaticItem("Competition Suspension", false, Susp3, NULL);

	// suspension menu
	ExMenu->SetMenuTitle("Exhaust Upgrades");
	ExMenu->AddStaticItem("Stock Exhaust", false, ExStock, NULL);
	ExMenu->AddStaticItem("Exhaust 1", false, Ex0, NULL);
	ExMenu->AddStaticItem("Exhaust 2", false, Ex1, NULL);
	ExMenu->AddStaticItem("Exhaust 3", false, Ex2, NULL);
	ExMenu->AddStaticItem("Exhaust 4", false, Ex3, NULL);


	// wheel menu
	WheelMenu->SetMenuTitle("Wheel Upgrades");
	WheelMenu->AddStaticItem("Stock Tires", false, StockTyres, NULL);
	WheelMenu->AddStaticItem("Custom Tires", false, CustomTyres, NULL);
	WheelMenu->AddStaticItem("Bulletproof Tires", false, BpTyres, NULL);
	WheelMenu->AddStaticItem("Stock Wheels", false, StockWheels, NULL);
	WheelMenu->AddSubMenu("High End", HighEnd);
	WheelMenu->AddSubMenu("Lowrider", Lowrider);
	WheelMenu->AddSubMenu("Muscle", Muscle);
	WheelMenu->AddSubMenu("Offroad", Offroad);
	WheelMenu->AddSubMenu("Sport", Sport);
	WheelMenu->AddSubMenu("Sport Page 2", SportMenu2);
	WheelMenu->AddSubMenu("SUV", SUV);
	WheelMenu->AddSubMenu("Tuner", Tuner);
	WheelMenu->AddSubMenu("Tuner Page 2", TunerMenu2);

	// high end 

	HighEnd->SetMenuTitle("High End Wheels");
	HighEnd->AddStaticItem("GT Chrome", false, HighEnd8, NULL);
	HighEnd->AddStaticItem("Cheetah RR", false, HighEnd9, NULL);
	HighEnd->AddStaticItem("Shadow", false, HighEnd0, NULL);
	HighEnd->AddStaticItem("Hypher", false, HighEnd1, NULL);
	HighEnd->AddStaticItem("Blade", false, HighEnd2, NULL);
	HighEnd->AddStaticItem("Diamond", false, HighEnd3, NULL);
	HighEnd->AddStaticItem("Supa Gee", false, HighEnd4, NULL);
	HighEnd->AddStaticItem("Chromatic Z", false, HighEnd5, NULL);
	HighEnd->AddStaticItem("Merchie Ch.Lip", false, HighEnd6, NULL);
	HighEnd->AddStaticItem("Obey RS", false, HighEnd7, NULL);
	HighEnd->AddStaticItem("Solar", false, HighEnd10, NULL);
	HighEnd->AddStaticItem("Split Ten", false, HighEnd11, NULL);
	HighEnd->AddStaticItem("Dash VIP", false, HighEnd12, NULL);
	HighEnd->AddStaticItem("LozSpeed Ten", false, HighEnd13, NULL);
	HighEnd->AddStaticItem("Carbon Inferno", false, HighEnd14, NULL);
	HighEnd->AddStaticItem("Carbon Shadow", false, HighEnd15, NULL);
	HighEnd->AddStaticItem("Carbonic Z", false, HighEnd16, NULL);
	HighEnd->AddStaticItem("Carbon Solar", false, HighEnd17, NULL);
	HighEnd->AddStaticItem("Cheetah Cobra R", false, HighEnd18, NULL);
	HighEnd->AddStaticItem("Carbon S Racer", false, HighEnd19, NULL);

	// lowrider wheels
	Lowrider->SetMenuTitle("Lowrider Wheels");
	Lowrider->AddStaticItem("Flare", false, Lowrider0, NULL);
	Lowrider->AddStaticItem("Wired", false, Lowrider1, NULL);
	Lowrider->AddStaticItem("Triple Golds", false, Lowrider2, NULL);
	Lowrider->AddStaticItem("Big Worm", false, Lowrider3, NULL);
	Lowrider->AddStaticItem("Seven Fives", false, Lowrider4, NULL);
	Lowrider->AddStaticItem("Split Six", false, Lowrider5, NULL);
	Lowrider->AddStaticItem("Fresh Mesh", false, Lowrider6, NULL);
	Lowrider->AddStaticItem("Lead Sled", false, Lowrider7, NULL);
	Lowrider->AddStaticItem("Turbine", false, Lowrider8, NULL);
	Lowrider->AddStaticItem("Super Fin", false, Lowrider9, NULL);
	Lowrider->AddStaticItem("Classic Rod", false, Lowrider10, NULL);
	Lowrider->AddStaticItem("Dollar", false, Lowrider11, NULL);
	Lowrider->AddStaticItem("Dukes", false, Lowrider12, NULL);
	Lowrider->AddStaticItem("Low Five", false, Lowrider13, NULL);
	Lowrider->AddStaticItem("Gooch", false, Lowrider14, NULL);

	//Muscle 
	Muscle->SetMenuTitle("Muscle Wheels");
	Muscle->AddStaticItem("Classic Five", false, Muscle0, NULL);
	Muscle->AddStaticItem("Dukes", false, Muscle1, NULL);
	Muscle->AddStaticItem("Muscle Freak", false, Muscle2, NULL);
	Muscle->AddStaticItem("Kracka", false, Muscle3, NULL);
	Muscle->AddStaticItem("Azreal", false, Muscle4, NULL);
	Muscle->AddStaticItem("Mecha", false, Muscle5, NULL);
	Muscle->AddStaticItem("Black Top", false, Muscle6, NULL);
	Muscle->AddStaticItem("Drag SPL", false, Muscle7, NULL);
	Muscle->AddStaticItem("Revolver", false, Muscle8, NULL);
	Muscle->AddStaticItem("Classic Rod", false, Muscle9, NULL);
	Muscle->AddStaticItem("Fairlie", false, Muscle10, NULL);
	Muscle->AddStaticItem("Spooner", false, Muscle11, NULL);
	Muscle->AddStaticItem("Five Star", false, Muscle12, NULL);
	Muscle->AddStaticItem("Old School", false, Muscle13, NULL);
	Muscle->AddStaticItem("El Jefe", false, Muscle14, NULL);
	Muscle->AddStaticItem("Dodman", false, Muscle15, NULL);
	Muscle->AddStaticItem("Six Gun", false, Muscle16, NULL);
	Muscle->AddStaticItem("Mercenary", false, Muscle17, NULL);

	//Offroad 
	Offroad->SetMenuTitle("Offroad Wheels");
	Offroad->AddStaticItem("Raider", false, Offroad0, NULL);
	Offroad->AddStaticItem("Mudslinger", false, Offroad1, NULL);
	Offroad->AddStaticItem("Nevis", false, Offroad2, NULL);
	Offroad->AddStaticItem("Cairngorm", false, Offroad3, NULL);
	Offroad->AddStaticItem("Amazon", false, Offroad4, NULL);
	Offroad->AddStaticItem("Challenger", false, Offroad5, NULL);
	Offroad->AddStaticItem("Dune Basher", false, Offroad6, NULL);
	Offroad->AddStaticItem("Five Star", false, Offroad7, NULL);
	Offroad->AddStaticItem("Rock Crawler", false, Offroad8, NULL);
	Offroad->AddStaticItem("Mil Spec Steelie", false, Offroad9, NULL);

	// sport wheels

	Sport->SetMenuTitle("Sports Wheels");
	Sport->AddStaticItem("Inferno", false, Sport0, NULL);
	Sport->AddStaticItem("Deep Five", false, Sport1, NULL);
	Sport->AddStaticItem("Lozspeed Mk.V", false, Sport2, NULL);
	Sport->AddStaticItem("Diamond Cut", false, Sport3, NULL);
	Sport->AddStaticItem("Chrono", false, Sport4, NULL);
	Sport->AddStaticItem("Feroci RR", false, Sport5, NULL);
	Sport->AddStaticItem("FiftyNine", false, Sport6, NULL);
	Sport->AddStaticItem("Mercie", false, Sport7, NULL);
	Sport->AddStaticItem("Synthetic Z", false, Sport8, NULL);
	Sport->AddStaticItem("Organic Type 0", false, Sport9, NULL);
	Sport->AddStaticItem("Endo v.1", false, Sport10, NULL);
	Sport->AddStaticItem("GT One", false, Sport11, NULL);
	Sport->AddStaticItem("Duper 7", false, Sport12, NULL);
	Sport->AddStaticItem("Uzer", false, Sport13, NULL);
	Sport->AddStaticItem("Groundride", false, Sport14, NULL);
	Sport->AddStaticItem("S Racer", false, Sport15, NULL);
	Sport->AddStaticItem("Venum", false, Sport16, NULL);
	Sport->AddStaticItem("Cosmo", false, Sport17, NULL);
	Sport->AddStaticItem("Dash VIP", false, Sport18, NULL);
	Sport->AddStaticItem("Ice Kid", false, Sport19, NULL);

	SportMenu2->SetMenuTitle("Sports Wheels Page 2");
	SportMenu2->AddStaticItem("Ruff Weld", false, Sport20, NULL);
	SportMenu2->AddStaticItem("Wangan Master", false, Sport21, NULL);
	SportMenu2->AddStaticItem("Super Five", false, Sport22, NULL);
	SportMenu2->AddStaticItem("Endo v.2", false, Sport23, NULL);
	SportMenu2->AddStaticItem("Split Six", false, Sport24, NULL);

	// SUV

	SUV->SetMenuTitle("SUV Wheels");
	SUV->AddStaticItem("VIP", false, SUV0, NULL);
	SUV->AddStaticItem("Benefactor", false, SUV1, NULL);
	SUV->AddStaticItem("Cosmo", false, SUV2, NULL);
	SUV->AddStaticItem("Bippu", false, SUV3, NULL);
	SUV->AddStaticItem("Royal Six", false, SUV4, NULL);
	SUV->AddStaticItem("Fagorme", false, SUV5, NULL);
	SUV->AddStaticItem("Deluxe", false, SUV6, NULL);
	SUV->AddStaticItem("Iced Out", false, SUV7, NULL);
	SUV->AddStaticItem("Congoscenti", false, SUV8, NULL);
	SUV->AddStaticItem("Lozspeed Ten", false, SUV9, NULL);
	SUV->AddStaticItem("Supernova", false, SUV10, NULL);
	SUV->AddStaticItem("Obey RS", false, SUV11, NULL);
	SUV->AddStaticItem("Lozspeed Baller", false, SUV12, NULL);
	SUV->AddStaticItem("Extravaganzo", false, SUV13, NULL);
	SUV->AddStaticItem("Split Six", false, SUV14, NULL);
	SUV->AddStaticItem("Empowered", false, SUV15, NULL);
	SUV->AddStaticItem("Sunrise", false, SUV16, NULL);
	SUV->AddStaticItem("Dash VIP", false, SUV17, NULL);
	SUV->AddStaticItem("Cutter", false, SUV18, NULL);

	//tuner wheels

	Tuner->SetMenuTitle("Tuner Wheels");
	Tuner->AddStaticItem("Cosmo", false, Tuner0, NULL);
	Tuner->AddStaticItem("Super Mesh", false, Tuner1, NULL);
	Tuner->AddStaticItem("Outsider", false, Tuner2, NULL);
	Tuner->AddStaticItem("Rollas", false, Tuner3, NULL);
	Tuner->AddStaticItem("Driftmeister", false, Tuner4, NULL);
	Tuner->AddStaticItem("Slicer", false, Tuner5, NULL);
	Tuner->AddStaticItem("El Quatro", false, Tuner6, NULL);
	Tuner->AddStaticItem("Dubbed", false, Tuner7, NULL);
	Tuner->AddStaticItem("Five Star", false, Tuner8, NULL);
	Tuner->AddStaticItem("Sideways", false, Tuner9, NULL);
	Tuner->AddStaticItem("Apex", false, Tuner10, NULL);
	Tuner->AddStaticItem("Stanced EG", false, Tuner11, NULL);
	Tuner->AddStaticItem("Countersteer", false, Tuner12, NULL);
	Tuner->AddStaticItem("Endo v.1", false, Tuner13, NULL);
	Tuner->AddStaticItem("Endo v.2 Dish", false, Tuner14, NULL);
	Tuner->AddStaticItem("Gruppe Z", false, Tuner15, NULL);
	Tuner->AddStaticItem("Choku-Dori", false, Tuner16, NULL);
	Tuner->AddStaticItem("Chicane", false, Tuner17, NULL);
	Tuner->AddStaticItem("Saisoku", false, Tuner18, NULL);
	Tuner->AddStaticItem("Dished Eight", false, Tuner19, NULL);

	TunerMenu2->SetMenuTitle("Tuner Wheels Page 2");
	TunerMenu2->AddStaticItem("Fujiwara", false, Tuner20, NULL);
	TunerMenu2->AddStaticItem("Zokusha", false, Tuner21, NULL);
	TunerMenu2->AddStaticItem("Battle Vlll", false, Tuner22, NULL);
	TunerMenu2->AddStaticItem("Rally Master", false, Tuner23, NULL);

    Weather->SetMenuTitle("Weather Shit");
	Weather->AddStaticItem("Blizzard", false, Weather0, NULL);
	Weather->AddStaticItem("Clear", false, Weather1, NULL);
	Weather->AddStaticItem("Clearing", false, Weather2, NULL);
	Weather->AddStaticItem("Clouds", false, Weather3, NULL);
	Weather->AddStaticItem("Extra Sunny", false, Weather4, NULL);
	Weather->AddStaticItem("Foggy", false, Weather5, NULL);
	Weather->AddStaticItem("Hulk Weather", false, Weather6, NULL);
	Weather->AddStaticItem("Overcast", false, Weather7, NULL);
	Weather->AddStaticItem("Rain", false, Weather8, NULL);
	Weather->AddStaticItem("Smog", false, Weather9, NULL);
	Weather->AddStaticItem("Snow", false, Weather10, NULL);
	Weather->AddStaticItem("Snow Light", false, Weather11, NULL);
	Weather->AddStaticItem("Thunder", false, Weather12, NULL);
	Weather->AddStaticItem("+ Hour", false, Weather13, NULL);
	Weather->AddStaticItem("- Hour", false, Weather14, NULL);


    //SpeedoMeter->SetMenuTitle("Speedometer Options");
	//SpeedoMeter->AddStaticItem("Speedometer", true, Analog, NULL);
	//SpeedoMeter->AddStaticItem("Normal Skin", false, SimpleSkin, NULL);
	//SpeedoMeter->AddStaticItem("BMW Skin", false, BMWSkin, NULL);
	//SpeedoMeter->AddStaticItem("SV6 Skin", false, TestSkin, NULL);
	//SpeedoMeter->AddStaticItem("Chrome Skin", false, NormalSkin, NULL);
    //SpeedoMeter->AddStaticItem("Analog Speedo", true, Analog, NULL);


#ifdef PRIVATE

	Recovery->SetMenuTitle("Recovery Menu");
	Recovery->AddSubMenu("Character 1", Character1);
	Recovery->AddSubMenu("Character 2", Character2);
	Recovery->AddSubMenu("Character 3", Character3);


	Character1->SetMenuTitle("Character 1");
	Character1->AddSubMenu("Rank Menu", RankMenuMP0);
	Character1->AddStaticItem("Unlock All", false, UnlockAllMP0, NULL);
	Character1->AddStaticItem("Bypass Tutorial", false, BypassTUTMP0, NULL);
	Character1->AddStaticItem("Unlock Heist Stuff", false, HeistStuff0, NULL);
	Character1->AddStaticItem("Max Fireworks", false, MaxFireworks0, NULL);
	Character1->AddStaticItem("Max Snacks", false, MaxSnacks0, NULL);

	Character2->SetMenuTitle("Character 2");
	Character2->AddSubMenu("Rank Menu", RankMenuMP1);
	Character2->AddStaticItem("Unlock All", false, UnlockAllMP1, NULL);
	Character2->AddStaticItem("Bypass Tutorial", false, BypassTUTMP1, NULL);
	Character2->AddStaticItem("Unlock Heist Stuff", false, HeistStuff1, NULL);
	Character2->AddStaticItem("Max Fireworks", false, MaxFireworks1, NULL);
	Character2->AddStaticItem("Max Snacks", false, MaxSnacks1, NULL);

	Character3->SetMenuTitle("Character 3");
	Character3->AddSubMenu("Rank Menu", RankMenuMP2);
	Character3->AddStaticItem("Unlock All", false, UnlockAllMP2, NULL);
	Character3->AddStaticItem("Bypass Tutorial", false, BypassTUTMP2, NULL);
	Character3->AddStaticItem("Unlock Heist Stuff", false, HeistStuff2, NULL);
	Character3->AddStaticItem("Max Fireworks", false, MaxFireworks2, NULL);
	Character3->AddStaticItem("Max Snacks", false, MaxSnacks2, NULL);

	MenuOptions->SetMenuTitle("Menu Options");
	MenuOptions->AddSubMenu("Menu Fonts", MenuFonts);
	MenuOptions->AddSubMenu("Title Shader Color", TitleShaderColor);
	MenuOptions->AddSubMenu("Main Shader Color", MainShaderColor);
	MenuOptions->AddSubMenu("Title Color", TitleColor);
	MenuOptions->AddSubMenu("Item Color", ItemColor);
	MenuOptions->AddSubMenu("Selector Color", SelectorColor);
	MenuOptions->AddSubMenu("Menu Alpha", MenuAlphaLevel);
	MenuOptions->AddSubMenu("Menu Position", MenuPosition);
	//MenuOptions->AddSubMenu("Menu Style", MenuStyle);
	MenuOptions->AddStaticItem("Toggle Marquee", true, MarqueeToggle, NULL);

	MenuStyle->SetMenuTitle("Menu Style");
	MenuStyle->AddStaticItem("VCA", false, VCAStyle, NULL);
	MenuStyle->AddStaticItem("Metro", false, MetroStyle, NULL);
	MenuStyle->AddStaticItem("Stelio Kontos", false, StelioKontosStyle, NULL);
	MenuStyle->AddStaticItem("ECMxVIPER", false, ECMxVIPERStyle, NULL);
	MenuStyle->AddStaticItem("CR4ZYCOOKIE", false, CookiesStyle, NULL);

	MenuAlphaLevel->SetMenuTitle("Menu Alpha Level");
	MenuAlphaLevel->AddStaticItem("Set Alpha To 100", false, MenuAlpha100, NULL);
	MenuAlphaLevel->AddStaticItem("Set Alpha To 150", false, MenuAlpha150, NULL);
	MenuAlphaLevel->AddStaticItem("Set Alpha To 200", false, MenuAlpha200, NULL);
	MenuAlphaLevel->AddStaticItem("Set Alpha To 255", false, MenuAlpha255, NULL);

	MenuPosition->SetMenuTitle("Menu Position");
	MenuPosition->AddStaticItem("Left Side", false, MenuLeftSide, NULL);
	MenuPosition->AddStaticItem("Right Side", false, MenuRightSide, NULL);
	MenuPosition->AddStaticItem("Center", false, MenuCenter, NULL);

	TitleShaderColor->SetMenuTitle("Title Shader Color");
	TitleShaderColor->AddStaticItem("Black", false, tShaderBlack, NULL);
	TitleShaderColor->AddStaticItem("White", false, tShaderWhite, NULL);
	TitleShaderColor->AddStaticItem("Cyan Blue", false, tShaderCyan, NULL);
	TitleShaderColor->AddStaticItem("Bright Red", false, tShaderRed, NULL);
	TitleShaderColor->AddStaticItem("Neon Green", false, tShaderGreen, NULL);
	TitleShaderColor->AddStaticItem("Bright Orange", false, tShaderOrange, NULL);
	TitleShaderColor->AddStaticItem("Bright Yellow", false, tShaderYellow, NULL);
	TitleShaderColor->AddStaticItem("Neon Pink", false, tShaderPink, NULL);

	MainShaderColor->SetMenuTitle("Main Shader Color");
	MainShaderColor->AddStaticItem("Black", false, mShaderBlack, NULL);
	MainShaderColor->AddStaticItem("White", false, mShaderWhite, NULL);
	MainShaderColor->AddStaticItem("Cyan Blue", false, mShaderCyan, NULL);
	MainShaderColor->AddStaticItem("Bright Red", false, mShaderRed, NULL);
	MainShaderColor->AddStaticItem("Neon Green", false, mShaderGreen, NULL);
	MainShaderColor->AddStaticItem("Bright Orange", false, mShaderOrange, NULL);
	MainShaderColor->AddStaticItem("Bright Yellow", false, mShaderYellow, NULL);
	MainShaderColor->AddStaticItem("Neon Pink", false, mShaderPink, NULL);

	TitleColor->SetMenuTitle("Title Color");
	TitleColor->AddStaticItem("Black", false, tBlack, NULL);
	TitleColor->AddStaticItem("White", false, tWhite, NULL);
	TitleColor->AddStaticItem("Cyan Blue", false, tCyan, NULL);
	TitleColor->AddStaticItem("Bright Red", false, tRed, NULL);
	TitleColor->AddStaticItem("Neon Green", false, tGreen, NULL);
	TitleColor->AddStaticItem("Bright Orange", false, tOrange, NULL);
	TitleColor->AddStaticItem("Bright Yellow", false, tYellow, NULL);
	TitleColor->AddStaticItem("Neon Pink", false, tPink, NULL);

	ItemColor->SetMenuTitle("Item Color");
	ItemColor->AddStaticItem("Black", false, iBlack, NULL);
	ItemColor->AddStaticItem("White", false, iWhite, NULL);
	ItemColor->AddStaticItem("Cyan Blue", false, iCyan, NULL);
	ItemColor->AddStaticItem("Bright Red", false, iRed, NULL);
	ItemColor->AddStaticItem("Neon Green", false, iGreen, NULL);
	ItemColor->AddStaticItem("Bright Orange", false, iOrange, NULL);
	ItemColor->AddStaticItem("Bright Yellow", false, iYellow, NULL);
	ItemColor->AddStaticItem("Neon Pink", false, iPink, NULL);

	SelectorColor->SetMenuTitle("Selector Color");
	SelectorColor->AddStaticItem("Black", false, sBlack, NULL);
	SelectorColor->AddStaticItem("White", false, sWhite, NULL);
	SelectorColor->AddStaticItem("Cyan Blue", false, sCyan, NULL);
	SelectorColor->AddStaticItem("Bright Red", false, sRed, NULL);
	SelectorColor->AddStaticItem("Neon Green", false, sGreen, NULL);
	SelectorColor->AddStaticItem("Bright Orange", false, sOrange, NULL);
	SelectorColor->AddStaticItem("Bright Yellow", false, sYellow, NULL);
	SelectorColor->AddStaticItem("Neon Pink", false, sPink, NULL);

	MenuFonts->SetMenuTitle("Font Chooser");
	MenuFonts->AddSubMenu("Title Fonts", TitleFonts);
	MenuFonts->AddSubMenu("Item Fonts", ItemFonts);

	TitleFonts->SetMenuTitle("Title Fonts");
	TitleFonts->AddStaticItem("Cursive", false, TitleFont1, NULL);
	TitleFonts->AddStaticItem("Arial Large", false, TitleFont2, NULL);
	TitleFonts->AddStaticItem("Webdings", false, TitleFont3, NULL);
	TitleFonts->AddStaticItem("Arial", false, TitleFont4, NULL);
	TitleFonts->AddStaticItem("Invalid Boxes", false, TitleFont5, NULL);
	TitleFonts->AddStaticItem("Arial", false, TitleFont6, NULL);
	TitleFonts->AddStaticItem("Pricedown", false, TitleFont7, NULL);

	ItemFonts->SetMenuTitle("Item Fonts");
	ItemFonts->AddStaticItem("Cursive", false, ItemFont1, NULL);
	ItemFonts->AddStaticItem("Arial Large", false, ItemFont2, NULL);
	ItemFonts->AddStaticItem("Webdings", false, ItemFont3, NULL);
	ItemFonts->AddStaticItem("Arial", false, ItemFont4, NULL);
	ItemFonts->AddStaticItem("Invalid Boxes", false, ItemFont5, NULL);
	ItemFonts->AddStaticItem("Arial", false, ItemFont6, NULL);
	ItemFonts->AddStaticItem("Pricedown", false, ItemFont7, NULL);

	RankMenuMP0->SetMenuTitle("Rank Menu (Character 1");
	RankMenuMP0->AddStaticItem("Rank 120", false, Rank, NULL);
	RankMenuMP0->AddStaticItem("Rank 420", false, Rank420, NULL);
	RankMenuMP0->AddStaticItem("Custom Rank", false, CustomRankMP0, NULL);

	RankMenuMP1->SetMenuTitle("Rank Menu (Character 2");
	RankMenuMP1->AddStaticItem("Rank 120", false, Rank1, NULL);
	RankMenuMP1->AddStaticItem("Rank 420", false, Rank4201, NULL);
	RankMenuMP1->AddStaticItem("Custom Rank", false, CustomRankMP1, NULL);

	RankMenuMP2->SetMenuTitle("Rank Menu (Character 3");
	RankMenuMP2->AddStaticItem("Rank 120", false, Rank2, NULL);
	RankMenuMP2->AddStaticItem("Rank 420", false, Rank4202, NULL);
	RankMenuMP2->AddStaticItem("Custom Rank", false, CustomRankMP2, NULL);

	MenuCredits->SetMenuTitle("Credits Section");
	MenuCredits->AddStaticItem("Eaqz CLICK ME", false, Credits1, NULL);
	MenuCredits->AddStaticItem("XeClutch CLICK ME", false, Credits4, NULL);
	MenuCredits->AddStaticItem("IrishMoDz HD CLICK ME", false, Credits2, NULL);
	MenuCredits->AddStaticItem("Stelio Kontos CLICK ME", false, Credits3, NULL);
	MenuCredits->AddStaticItem("Cr4zyCookie CLICK ME", false, Credits5, NULL);

#endif

	// Main Menu
	mainMenu->SetMenuTitle("GTA V:TU26 xxHASTERxx");
	mainMenu->AddSubMenu("Quick Options", quickOptionsMenu);
	mainMenu->AddSubMenu("Teleport Menu", TeleMenu);
	mainMenu->AddSubMenu("Online Players", onlinePlayers);
	mainMenu->AddSubMenu("All Players", AllOnlinePlayers);
	mainMenu->AddSubMenu("Vehicle Options", vehicleOptionMenu);
	mainMenu->AddSubMenu("Weapon Options", weaponOptionsMenu);
	mainMenu->AddSubMenu("Object Options", ObjectOptions1);
	mainMenu->AddSubMenu("Los Santos Customs", ModShop);
	mainMenu->AddSubMenu("Vehicle Spawner", CarSpawner);
	mainMenu->AddSubMenu("Misc Options", MiscOptions);
	mainMenu->AddStaticItem("First Person Mode", true, FlyMod, NULL);
	mainMenu->AddSubMenu("Menu Options", MenuOptions);
	/////mainMenu->AddSubMenu("Credits", MenuCredits);
	//mainMenu->AddSubMenu("Analog Speedometer", SpeedoMeter);
	//mainMenu->AddStaticItem("Toggle Spawner Hook", true, ToggleLag, NULL);
	//mainMenu->AddStaticItem("Toggle Vehicle Spawner", true, ToggleVehicleSpawner, NULL);
	//mainMenu->AddSubMenu("Vehicle Paint", VehPaintMenu);
	//mainMenu->AddSubMenu("Pegasus Custom Vehicles", Pegasus);
	//mainMenu->AddSubMenu("Map Mods", MapMenu);
	//mainMenu->AddSubMenu("Eaqz Mods", EaqzMenu);
}

DWORD XamUserGetSigninStateHook(DWORD userIndex) {
	//printf("XamUserGetSigninStateHook - Spoofing Live 0\n");
	return eXamUserSigninState_SignedInToLive;
}

DWORD XamUserGetMembershipTierFromXUIDHook(QWORD xuid) {
	//printf("XamUserGetMembershipTierFromXUIDHook - Spoofing live 1\n");
	return eXamUserSigninState_SignedInToLive;
}

HRESULT XamUserGetXUIDHook(DWORD dwUserIndex, DWORD unk, PXUID onlineOut) {
	//printf("XamUserGetXUIDHook - Spoofing Live 2\n");
	HRESULT hr = XamUserGetXUID(dwUserIndex, unk, onlineOut);

	//*onlineOut = 2533275020856061; // xuid here
	return hr;
}

inline DWORD GoldSpoofHook(DWORD dwUserIndex, XPRIVILEGE_TYPE PrivilegeType, PBOOL pfResult)
{
    *pfResult = true;
    return ERROR_SUCCESS;
}

unsigned long XeXGetModuleHandleHook(char* ModuleName)
{
if(strcmp(ModuleName, "xbdm.xex") == 0)
return 0;
else
return (unsigned long)GetModuleHandle(ModuleName);
}



NTSTATUS XamUserGetSigninInfoHook(DWORD userIndex, DWORD flags, PXUSER_SIGNIN_INFO xSigningInfo) {
	//printf("XamUserGetSigninInfoHook - Spoofing Live And Gamertag 3\n");
	NTSTATUS stat = XamUserGetSigninInfo(userIndex, flags, xSigningInfo);

	//xSigningInfo->UserSigninState = eXUserSigninState_SignedInToLive;
	//xSigningInfo->xuid = 2533275020856061; // xuid here
	strcpy(xSigningInfo->szUserName, "Borat Is Black"); // gamertag here

	return stat;
}

//.text:837FDBBC XamUserGetName: 

DWORD XamUserGetNameHook(DWORD dwUserIndex, LPSTR pUserName, DWORD cchUserName) {
	DWORD result = XamUserGetName(dwUserIndex, pUserName, cchUserName);

	//printf("XamUserGetSigninInfoHook - Spoofing Gameryag\n");

	strcpy(pUserName, "Borat Is Black"); // gamertag here
	
	return result;
}

HINTERNET NetDll_XHttpConnectHook(DWORD reg3, HINTERNET hSession, const CHAR *pcszServerName, INTERNET_PORT nServerPort, DWORD dwFlags) {

	printf("[R*] - NetDll_XHttpConnectHook - %s %d\n", pcszServerName, nServerPort);
	
	//return XHttpConnect(hSession, pcszServerName, nServerPort, dwFlags);
}

FILE *fSprintfFile = NULL;
int sprintfFileCunt = 0;

void sub_8223E0A8_Hook(char *outBuffer, size_t size, char *format, ...) {

	DWORD link;

	__asm mflr link

	if (!fSprintfFile) {
		MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);
		fopen_s(&fSprintfFile, "Hdd:\\GTAVSprintfLog.txt", "a");
	}

	va_list args;
	va_start (args, format);
	vsprintf_s(outBuffer, size, format, args);
	va_end (args);

	/*char *eb = strstr(outBuffer, "2535471422561337");

	if (eb) {
		memcpy(eb, "2533274959260499", 16);

		printf("Changed xuid %s\n", outBuffer);
	}*/

	//printf("[R*] - sprintf_s hook - %s\n", outBuffer);

	if (fSprintfFile) {
		fprintf(fSprintfFile, "%08X - %s\r\n", link, outBuffer);
		fflush(fSprintfFile);
	}
}

HINTERNET NetDll_XHttpOpenHook(DWORD reg3, const CHAR *pcszUserAgent, DWORD dwAccessType, const CHAR *pcszProxyName, const CHAR *pcszProxyBypass, DWORD dwFlags) {
	
	printf("[R*] - NetDll_XHttpOpenHook - User Agent %s Proxy Name %s Proxy Bypass %s\n", pcszUserAgent, pcszProxyName, pcszProxyBypass);

	//return XHttpOpen(pcszUserAgent, dwAccessType, pcszProxyName, pcszProxyBypass, dwFlags);
}

int httpReadDataCount = 0;

FILE *fHttpRead = 0;

BOOL NetDll_XHttpReadDataHook(DWORD reg3, HINTERNET hRequest, VOID *pBuffer, DWORD dwNumberOfBytesToRead, DWORD *pdwNumberOfBytesRead) {
	//BOOL result = XHttpReadData(hRequest, pBuffer, dwNumberOfBytesToRead, pdwNumberOfBytesRead);

	CHAR filePath[MAX_PATH];
	sprintf_s(filePath, "Hdd:\\ReadStream.bin");

	MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);

	printf("[R*] - NetDll_XHttpReadDataHook - Read %d bytes from http request. Dumping to file.\n", dwNumberOfBytesToRead);
	//DumpFile(filePath, (PBYTE)pBuffer, dwNumberOfBytesToRead);

	if (!fHttpRead) {
		fopen_s(&fHttpRead, filePath, "a");
	}

	if (fHttpRead) {
		fwrite((PBYTE)pBuffer, 1, dwNumberOfBytesToRead, fHttpRead);
		fflush(fHttpRead);
	}

	return 1;
}

int httpWrittenDataCount = 0;

FILE *fWriteStream = 0;

BOOL NetDll_XHttpWriteDataHook(DWORD reg3, HINTERNET hRequest, VOID *pBuffer, DWORD dwNumberOfBytesToWrite, DWORD *pdwNumberOfBytesWritten) {
	//BOOL result = XHttpWriteData(hRequest, pBuffer, dwNumberOfBytesToWrite, pdwNumberOfBytesWritten);

	CHAR filePath[MAX_PATH];
	sprintf_s(filePath, "Hdd:\\WriteStream.bin");

	MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);

	printf("[R*] - NetDll_XHttpWriteDataHook - Wrote %d bytes to http request. Dumping to file.\n", dwNumberOfBytesToWrite);
	//DumpFile(filePath, (PBYTE)pBuffer, dwNumberOfBytesToWrite);

	if (!fWriteStream) {
		fopen_s(&fWriteStream, filePath, "a");
	}

	if (fWriteStream) {
		fwrite((PBYTE)pBuffer, 1, dwNumberOfBytesToWrite, fWriteStream);
		fflush(fWriteStream);
	}

	return 1;
}

int httpSendRequestCount = 0;

BOOL NetDll_XHttpSendRequestHook(DWORD reg3, 
	HINTERNET hRequest,
    const CHAR *pcszHeaders,
    DWORD dwHeadersLength,
    const VOID *lpOptional,
    DWORD dwOptionalLength,
    DWORD dwTotalLength,
    DWORD_PTR dwContext
) {

	//printf("[R*] - NetDll_XHttpSendRequestHook - headers = %s\n", pcszHeaders);
	
	//if (lpOptional) {
	//	CHAR filePath[MAX_PATH];
	//	sprintf_s(filePath, "Hdd:\\XHttpSendRequestOptional\\%d.bin", httpSendRequestCount++);

	//	MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);

	//	//printf("[R*] - NetDll_XHttpSendRequestHook - Dumping extra data %d\n", httpSendRequestCount);

	//	DumpFile(filePath, (PBYTE)lpOptional, dwOptionalLength);
	//}

	//return XHttpSendRequest(hRequest, pcszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
}

//HRESULT XAuthGetToken(
//         DWORD UserIndex,
//         const CHAR *pUrn,
//         DWORD UrnLength,
//         RELYING_PARTY_TOKEN **pToken,
//         XOVERLAPPED *pXOverlapped
//)

/*typedef struct _RELYING_PARTY_TOKEN {
    DWORD Reserved;
    DWORD Length;
    PBYTE pToken;
} RELYING_PARTY_TOKEN, *PRELYING_PARTY_TOKEN;*/


/*HRESULT XAuthGetTokenHook(
         DWORD UserIndex,
         const CHAR *pUrn,
         DWORD UrnLength,
         RELYING_PARTY_TOKEN **pToken,
         XOVERLAPPED *pXOverlapped
) {

	printf("[R*] - XAuthGetTokenHook - %s\n", pUrn);

	PBYTE gamerData = (PBYTE)0x81AA2C70;

	QWORD oldXUID = *(QWORD*)(gamerData + 0x3C);

	//*(QWORD*)(gamerData + 0x3C) = 2533275020856061;

	HRESULT hr = XAuthGetToken(UserIndex, pUrn, UrnLength, pToken, pXOverlapped);

	//*(QWORD*)(gamerData + 0x3C) = oldXUID;

	printf("[R*] - XAuthGetTokenHook - HRESULT = %08X\n", hr);
	printf("[R*] - XAuthGetTokenHook - pToken = %08X\n", pToken);

	if (pToken) {
		RELYING_PARTY_TOKEN *p = *pToken;

		printf("[R*] - XAuthGetTokenHook - p = %08X\n", p);

		if (p) {
			printf("[R*] - XAuthGetTokenHook - ");
	
			for (int i = 0; i < p->Length; i++) {
				printf("%02X ", p->pToken[i]);
			}

			printf("\n");
		}
	}

	return hr;
}*/

//.rdata:8162AC40 CXamTokenAdapter:.long ___ECXamLiveHiveAdapter
//.rdata:8162AC40                                         # DATA XREF: sub_818F1268:loc_818F139Co
//.rdata:8162AC44                 .long _XamGetToken_CXamTokenAdapter
//.rdata:8162AC48                 .long _XamRequestToken_CXamTokenAdapter
//.rdata:8162AC4C                 .long _XamGetAppliesTo_CXamTokenAdapter
//.rdata:8162AC50                 .long _XamFreeToken_CXamTokenAdapter

extern "C" DWORD XamGetToken(unsigned long reg3, char const * reg4, unsigned long reg5, struct _XAM_RELYING_PARTY_TOKEN * * reg6, struct _XOVERLAPPED * reg7);
extern "C" DWORD XamRequestToken(unsigned long reg3, unsigned long reg4, char const * reg5, unsigned long reg6, struct _XAM_RELYING_PARTY_TOKEN * * reg7, struct _XOVERLAPPED * reg8);
extern "C" DWORD XamGetAppliesTo(char const * reg3, unsigned long reg4, struct _XAM_RELYING_PARTY_TOKEN * * reg5);

DWORD XamGetToken_CXamTokenAdapter(unsigned long reg3, unsigned long reg4,  char const * reg5, unsigned long reg6, struct _XAM_RELYING_PARTY_TOKEN * * reg7, struct _XOVERLAPPED * reg8) {
	DWORD link = 0;
	__asm mflr link;
	printf("%08X - XamGetToken_CXamTokenAdapter - %s\n", link, reg5);
	return XamGetToken(reg4, reg5, reg6, reg7, reg8);
}

DWORD XamRequestToken_CXamTokenAdapter(unsigned long reg3, unsigned long reg4, unsigned long reg5, char const * reg6, unsigned long reg7, struct _XAM_RELYING_PARTY_TOKEN * * reg8, struct _XOVERLAPPED * reg9) {
	DWORD link = 0;
	__asm mflr link;
	printf("%08X - XamRequestToken_CXamTokenAdapter - %s\n", link, reg6);
	return XamRequestToken(reg4, reg5, reg6, reg7, reg8, reg9);
}

DWORD XamGetAppliesTo_CXamTokenAdapter(unsigned long reg3, char const * reg4, unsigned long reg5, struct _XAM_RELYING_PARTY_TOKEN * * reg6) {
	DWORD link = 0;
	__asm mflr link;
	printf("%08X - XamGetAppliesTo_CXamTokenAdapter - %s\n", link, reg4);
	return XamGetAppliesTo(reg4, reg5, reg6);
}

void HookXamTokenVTable() {
	DWORD* CXamTokenAdapter = (DWORD*)0x8162AC40;

	PatchInJump((PDWORD)CXamTokenAdapter[1], (DWORD)XamGetToken_CXamTokenAdapter, FALSE);
	PatchInJump((PDWORD)CXamTokenAdapter[2], (DWORD)XamRequestToken_CXamTokenAdapter, FALSE);
	PatchInJump((PDWORD)CXamTokenAdapter[3], (DWORD)XamGetAppliesTo_CXamTokenAdapter, FALSE);

	PBYTE gamerData = (PBYTE)0x81AA2C70;

	//wcscpy((wchar_t*)(gamerData + 0x1C), L"Borat Is Black");
	*(QWORD*)(gamerData + 0x3C) = 2533275020856061; // XUID here
}

//.text:816BF97C                 lis       r4, 2 # 0x2F001
//.text:816BF980                 li        r8, 0
//.text:816BF984                 li        r7, 0x428
//.text:816BF988                 addi      r6, r1, 0x4F0+var_470
//.text:816BF98C                 mr        r5, r27
//.text:816BF990                 ori       r4, r4, 0xF001 # 0x2F001
//.text:816BF994                 li        r3, 0xFE
//.text:816BF998                 bl        XMsgStartIORequestEx

//typedef struct _XOVERLAPPED {
//    ULONG_PTR                           InternalLow;
//    ULONG_PTR                           InternalHigh;
//    ULONG_PTR                           InternalContext;
//    HANDLE                              hEvent;
//    PXOVERLAPPED_COMPLETION_ROUTINE     pCompletionRoutine;
//    DWORD_PTR                           dwCompletionContext;
//    DWORD                               dwExtendedError;
//} XOVERLAPPED, *PXOVERLAPPED;

HRESULT XamRequestTokenMidFunctionHook(
    IN      HXAMAPP                     hxamapp,
    IN      DWORD                       dwMessage,
    IN      PXOVERLAPPED                pOverlapped,
    IN OUT  PVOID                       pUserBuffer,
    IN      DWORD                       cbUserBuffer,
    IN      PVOID                       pTaskAttribs
    ) {

	PXOVERLAPPED pOver = nullptr;

	__asm {
		mr	pOver, r27
	}

	/*if (pOver) {
		printf("XamRequestTokenMidFunctionHook *****\n");
		printf("InternalLow - %08X\n", pOver->InternalLow);
		printf("InternalHigh - %08X\n", pOver->InternalHigh);
		printf("InternalContext - %08X\n", pOver->InternalContext);
		printf("hEvent - %08X\n", pOver->hEvent);
		printf("pCompletionRoutine - %08X\n", pOver->pCompletionRoutine);
		printf("dwCompletionContext - %08X\n", pOver->dwCompletionContext);
		printf("dwExtendedError - %08X\n", pOver->dwExtendedError);
		printf("End XamRequestTokenMidFunctionHook *****\n");
	}*/

	QWORD xuidSpoof = 2533275020856061;
	memcpy((PBYTE)pUserBuffer + 0x418, &xuidSpoof, 8);

	HRESULT hr = XMsgStartIORequestEx((HXAMAPP)0xFE, 0x2F001, pOver, pUserBuffer, cbUserBuffer, pTaskAttribs);

	/*if (pOver) {
		printf("XamRequestTokenMidFunctionHook *****\n");
		printf("InternalLow - %08X\n", pOver->InternalLow);
		printf("InternalHigh - %08X\n", pOver->InternalHigh);
		printf("InternalContext - %08X\n", pOver->InternalContext);
		printf("hEvent - %08X\n", pOver->hEvent);
		printf("pCompletionRoutine - %08X\n", pOver->pCompletionRoutine);
		printf("dwCompletionContext - %08X\n", pOver->dwCompletionContext);
		printf("dwExtendedError - %08X\n", pOver->dwExtendedError);
		printf("End XamRequestTokenMidFunctionHook *****\n");
	}*/

	return hr;
}

HRESULT InnerXamUserGetXUIDHook(DWORD dwUserIndex, DWORD unk, PXUID onlineOut) {
	DWORD link = 0;
	__asm mflr link;

	HRESULT (__cdecl *func)(DWORD reg3, DWORD reg4, PXUID reg5, DWORD reg6) = (HRESULT (__cdecl *)(DWORD reg3, DWORD reg4, PXUID reg5, DWORD reg6))0x816D79C8;
	
	/*printf("Test ****\n");

	for (DWORD i = 0; i < 10; i++) {
		*onlineOut = 0;
		func(dwUserIndex, i, onlineOut, 0x81AA2C70);
		printf("flag %d = %016llX\n", i, *onlineOut);
	}

	printf("Test *****\n");*/

	HRESULT hr = func(dwUserIndex, unk, onlineOut, 0x81AA2C70);

	printf("XamUserGetXUID - lr = %08X hr = %08X user index - %08X flags - %08X xuidptr - %08X xuid - %016llX\n", link, hr, dwUserIndex, unk, onlineOut, *onlineOut);

	if (link == 0x816BF914) {
		printf("Changing xuid HRESULT %08X current one is %016llX\n", hr, *onlineOut);
		//*onlineOut = 0x00090000093F5911; // XUID here
	}

	return hr;
}

bool DoFrame;

void __declspec(noinline) doFramefunc()
{
	DoFrame = true;
}

void UpdateMenu() {

	if (XamGetCurrentTitleId() != 0x545408A7)
		return;

	ShowMessageUpdate();

	if (teleportingPlayer) {
		TeleportPlayerProcess();
	}
	if (teleportingPlayer2) {
		TeleportPlayerProcess2();
	}
	if (Delete) {
	DeleteProcess();
	}

	if (DeleteAllVeh) {
	DeleteAllProcess();
	}

	if (KickinggPlayer) {
	LMAOProccess();
	}

	if (paintingPlayersCar) {
		PaintOnlinePlayersCarProcess();
	}

	if (explodingPlayersCar) {
		ExplodeOnlinePlayerVehicleProcess();
	}

	if (stallPlayersCar) {
		stallPlayerVehicleProcess();
	}

	if (launchingPlayersCar) {
		SendPlayersCarToSpaceProcess();
	}

	if (launchfPlayersCar){
		SendPlayersCarForwardProcess();
	}

	if (launchbPlayersCar) {
		SendPlayersCarBackwardsProcess();
	}

	if (vOutOfControl){
		vOutOfControlProcess();
	}

	if (popTheirTyres){
		popTheirTyresProcess();
	}

	if (flipCar180){
		flipCar180Process();
	}

	if (playerInvincibilityActive){
		ToggleGodMode();
	}

	if (towTruckCar) {
		TowTruckProcess();
	}

	if (detachTowTruckCar) {
		DetachTowTruckProcess();
	}

	if (detachMyCar){
		DetachMyCarProcess();
	}

	if (TowMyCarCar){
		TowMyCarProcess();
	}

	if (rcCar) {
		RcCarProcess();
	}

	if (showMyAlpha){
		showMyAlphaLoop();
	}

	if (setPlayerFire){
		setPlayerFireLoop();
	}

	if (creator180LP){
		creator180LoopProcess();
	}

	if (creator1802LP){
		creator180LoopProcess2();
	}

	if (creator1803LP){
		creator180LoopProcess3();
	}

	if (creator360LP){
		creator360RotationProcess();
	}

	if (MoveObjRight){
		MoveRightLoop();
	}

	if (ObjMoveUp){
		MoveUpLoop();
	}

	if (ObjMoveDown){
		MoveDownLoop();
	}

	if (ObjMoveForward){
		MoveForwardLoop();
	}

	if (MoveObjBackwards){
		MoveBackwardsLoop();
	}

	if (ObjMoveLeft){
		MoveLeftLoop();
	}

	if (lockPlayersCar) {
		LockPlayersDoorsProcess();
	}
	if (tFlyingVeh){
		tFlyingVehLoop();
	}
	if (flipPlayersCar) {
		FlipPlayersDoorsProcess();
	}
	if (NoGodHotRod) {
		NoGodHotRodProcess();
	}
	if (unlockPlayersCar) {
		unLockPlayersDoorsProcess();
	}
	if (fixPlayersCar){
		FixVehicleOnlineProcess();
	}
	if (ClonePlayer){
		ClonePlayerProcess();
	}
	if( blamePlayer){
		blamePlayerProcess();
	}
	if (paintingPlayersCarChrome){
		PaintOnlinePlayersCarChromeProcess();
	}
	if (paintingPlayersCarAngels){
		PaintOnlinePlayersCarAngelsProcess();
	}
	if (paintingPlayersCarPink){
		PaintOnlinePlayersCarPinkProcess();
	}
	if (pinkPlayersCar) {
		PinkOnlinePlayerVehicleProcess();
	}

	if(rainbow)
		rainbow_car();
	if(superjump)
		super_jump();
	if(superruncheck)
		super_run();
	if(lowered)
	    lowerloop();
	if (wanted)
		wantedloop();
	if (field)
		fieldloop();
	if (creatorField)
		creatorFieldloop();
	if (activenos)
		nosloop();
	if (rocket)
		rocketloop();
	if (creatorRocket)
		creatorRocketLoop();
	if (creatorFlares)
        creatorFlaresLoop();
	if(deagle)
	    UltimateDeagleLoop();
	/*if (tpGun)
		tpGunLoop();*/
	if (fwrocket)
		fwrocketloop();
	if (vehicleFlare)
		vehicleFlareLoop();
	if (vehicleSavage)
		vehicleSavageLoop();
	if (superMG)
		superMGloop();
	if (Mini)
		miniloop();
	if (invincibeloop)
		invinciblecarloop();
	if(TeleportToWaypoint)
		Waypointloop();
	if (aimbot) {
		aimbotloop(aimbotClient);
		aimbotrelease();
		aimbotClient += 1;
		if(aimbotClient >= 16)
			aimbotClient = 0;
	}
	if (dw)
		drive_water();
	if (da)
		drive_water();
	if (neons)
		neonloop();
	if (handdrift)
		slideyloop();
	if (rocket_gun)
		rocketgun();
	if (custom_per)
		supercar();
	if (Create)
		create_loop();
	if (speedo)
		speed();
	if (mGun)
		moneyGunLoop();
	if (speeder)
		speedGunLoop();
	if (pitchT)
		pitchToggle();
	if (coordsT)
		coordsToggle();
	if (pcoordsT)
		playerCoordsToggle();
	if (trollCash)
		moneyTrollToggle();
	if (hashT)
		hashToggle();
	if (cam_mode)
		cam_loop();
	if (Seccam_mode)
		Seccam_loop();
	if (Seccam2_mode)
		Seccam2_loop();
	if (super_check)
		super_loop();
	if (fly_car)
		fly_car_loop();
	if (rapid_fire)
		rocketgun2();
	if (firework_gun)
		fwgun();
	if (col_loop)
		fw_col_loop();
#ifdef PRIVATE
	if (analog_loop)
		analog_speedo();
#endif
#ifdef PRIVATE
	if (Peg_Global)
		pegasusloop();
#endif
#ifdef personal
	if (drop)
	    cashloop();
	if (objectDrop)
		cashCreatorLoop();
	if (propssGun)
		propGun();
	if (onedrop)
		onecashloop();
	if (Adderdrop)
		Addercashloop();
	//if(invisiblePlayer)
		//invisiblePlayerLoop();
	//if(invisibleVeh)
		//invisibleVehicleLoop();
	if(teleportGun)
		teleportGunLoop();
	if (fagdrop)
	    fagcashloop();
	if (alldrop)
		allcashloop();
	if (WhoIsThat)
		PrintChat();
#endif
	if (teleportingPlayer) {
		TeleportPlayerProcess();
	}
	if (teleportingPlayer2) {
		TeleportPlayerProcess2();
	}
	if (Delete) {
	DeleteProcess();
	}

	if (DeleteAllVeh) {
	DeleteAllProcess();
	}

	if (KickinggPlayer) {
	LMAOProccess();
	}

	if (paintingPlayersCar) {
		PaintOnlinePlayersCarProcess();
	}

	if (explodingPlayersCar) {
		ExplodeOnlinePlayerVehicleProcess();
	}

	if (stallPlayersCar) {
		stallPlayerVehicleProcess();
	}

	if (launchingPlayersCar) {
		SendPlayersCarToSpaceProcess();
	}

	if (launchfPlayersCar) {
		SendPlayersCarForwardProcess();
	}

	if (launchbPlayersCar) {
		SendPlayersCarBackwardsProcess();
	}

	if (vOutOfControl){
		vOutOfControlProcess();
	}

	if (popTheirTyres){
		popTheirTyresProcess();
	}

	if (flipCar180){
		flipCar180Process();
	}

	if (playerInvincibilityActive){
		ToggleGodMode();
	}

	if (towTruckCar) {
		TowTruckProcess();
	}

	if (detachTowTruckCar) {
		DetachTowTruckProcess();
	}

	if (detachMyCar){
		DetachMyCarProcess();
	}

	if (TowMyCarCar){
		TowMyCarProcess();
	}

	if (rcCar) {
		RcCarProcess();
	}

	if (showMyAlpha){
		showMyAlphaLoop();
	}

	if (setPlayerFire){
		setPlayerFireLoop();
	}

	if (creator180LP){
		creator180LoopProcess();
	}

	if (creator1802LP){
		creator180LoopProcess2();
	}

	if (creator1803LP){
		creator180LoopProcess3();
	}

	if (creator360LP){
		creator360RotationProcess();
	}

	if (MoveObjRight){
		MoveRightLoop();
	}

	if (ObjMoveUp){
		MoveUpLoop();
	}

	if (ObjMoveDown){
		MoveDownLoop();
	}

	if (ObjMoveForward){
		MoveForwardLoop();
	}

	if (MoveObjBackwards){
		MoveBackwardsLoop();
	}

	if (ObjMoveLeft){
		MoveLeftLoop();
	}

	if (lockPlayersCar) {
		LockPlayersDoorsProcess();
	}
	if (tFlyingVeh){
		tFlyingVehLoop();
	}
	if (flipPlayersCar) {
		FlipPlayersDoorsProcess();
	}
	if (NoGodHotRod) {
		NoGodHotRodProcess();
	}
	if (unlockPlayersCar) {
		unLockPlayersDoorsProcess();
	}
	if (fixPlayersCar){
		FixVehicleOnlineProcess();
	}
	if (ClonePlayer) {
		ClonePlayerProcess();
	}
	if (blamePlayer) {
		blamePlayerProcess();
	}
	if (paintingPlayersCarChrome){
		PaintOnlinePlayersCarChromeProcess();
	}
	if (paintingPlayersCarAngels){
		PaintOnlinePlayersCarAngelsProcess();
	}
	if (paintingPlayersCarPink){
		PaintOnlinePlayersCarPinkProcess();
	}
	if (pinkPlayersCar) {
		PinkOnlinePlayerVehicleProcess();
	}

	if(rainbow)
		rainbow_car();
	if(superjump)
		super_jump();
	if(superruncheck)
		super_run();
	if(lowered)
	    lowerloop();
	if (wanted)
		wantedloop();
	if (field)
		fieldloop();
	if (creatorField)
		creatorFieldloop();
	if (activenos)
		nosloop();
	if (rocket)
		rocketloop();
	if (creatorRocket)
		creatorRocketLoop();
	if (creatorFlares)
        creatorFlaresLoop();
	/*if (tpGun)
		tpGunLoop();*/
	if(deagle)
	    UltimateDeagleLoop();
	if (fwrocket)
		fwrocketloop();
	if (vehicleFlare)
		vehicleFlareLoop();
	if (vehicleSavage)
		vehicleSavageLoop();
	if (superMG)
		superMGloop();
	if (Mini)
		miniloop();
	if (invincibeloop)
		invinciblecarloop();
	if(TeleportToWaypoint)
		Waypointloop();
	if (aimbot) {
		aimbotloop(aimbotClient);
		aimbotrelease();
		aimbotClient += 1;
		if(aimbotClient >= 16)
			aimbotClient = 0;
	}
	if (dw)
		drive_water();
	if (da)
		drive_water();
	if (neons)
		neonloop();
	if (handdrift)
		slideyloop();
	if (rocket_gun)
		rocketgun();
	if (custom_per)
		supercar();
	if (Create)
		create_loop();
	if (speedo)
		speed();
	if (mGun)
		moneyGunLoop();
    if (pitchT)
		pitchToggle();
	if (coordsT)
		coordsToggle();
	if (pcoordsT)
		playerCoordsToggle();
	if (trollCash)
		moneyTrollToggle();
	if (hashT)
		hashToggle();
	if (cam_mode)
		cam_loop();
	if (Seccam_mode)
		Seccam_loop();
	if (Seccam2_mode)
		Seccam2_loop();
	if (super_check)
		super_loop();
	if (fly_car)
		fly_car_loop();
	if (rapid_fire)
		rocketgun2();
	if (firework_gun)
		fwgun();
	if (col_loop)
		fw_col_loop();
#ifdef PRIVATE
	if (analog_loop)
		analog_speedo();
#endif
#ifdef PRIVATE
	if (Peg_Global)
		pegasusloop();
#endif
#ifdef PRIVATE
	if (drop)
	    cashloop();
	if (objectDrop)
		cashCreatorLoop();
	if (propssGun)
		propGun();
	if (onedrop)
		onecashloop();
	if (Adderdrop)
		Addercashloop();
	//if(invisiblePlayer)
		//invisiblePlayerLoop();
	//if(invisibleVeh)
		//invisibleVehicleLoop();
	if(teleportGun)
		teleportGunLoop();
	if (fagdrop)
	    fagcashloop();
	if (alldrop)
		allcashloop();
	if (WhoIsThat)
		PrintChat();
#endif
	if (cheat_superjump){
		SuperJumpLoop();
	}
	if (cheat_superpunch){
		SuperPunchLoop();
	}
	/*if (cheat_swimfast){
		SwimFastLoop();
	}
	if (cheat_runfast){
		RunFastLoop();
	}*/
	if (cheat_explosiveammo){
		ExplosiveAmmoLoop();
	}
	if (cheat_fireammo){
		FireAmmoLoop();
	}

	if(marqueeToggle){
	   scroll();
	   scroll_rec();
	}

	secure_check();

	// Update our input
	menuInputHandler->UpdateInput();

	if (menuInputHandler->DPadLeftDown() && menuInputHandler->XButtonDown() && !inputButtonsPressed) {
		enableMenu = !enableMenu;
		printf("Menu %s\n", enableMenu ? "opened" : "closed");
		inputButtonsPressed = true;
	}
	else if (!menuInputHandler->DPadLeftDown() && !menuInputHandler->XButtonDown()) {
		inputButtonsPressed = false;

	}

	// Display our menu if we must
	if (enableMenu) {
		// update players list if the menu is open
		for (int i = 0; i < 18; i++) {
			GTAVMenuItem *menuItem = &onlinePlayers->menuItems->operator[](i);

			// Get player name
			char *playerName = GetPlayerName(i);

			// clear out the name
			memset(menuItem->itemText, 0, 32);

			// Copy the name into the struct
			strcpy_s(menuItem->itemText, 32, playerName);
		}

		for (int i = 0; i < 18; i++) {
			GTAVMenuItem *menuItem = &blamePlayers->menuItems->operator[](i);

			// Get player name
			char *blameName = GetPlayerName(i);

			// clear out the name
			memset(menuItem->itemText, 0, 32);

			// Copy the name into the struct
			strcpy_s(menuItem->itemText, 32, blameName);
		}

		mainMenu->DisplayMenu();
	} //all this stuff I would put in vm_execute
	
}

int __declspec(naked) VM_ExecuteStub(...)
{
     __asm
     {
		li r3, 3
		nop
		nop
		nop
		nop
		nop
		nop
		blr
     }
}

__int64 __declspec(naked) create_objectStub(...)
{
     __asm
     {
		li r3, 8
		nop
		nop
		nop
		nop
		nop
		nop
		blr
     }
}

__int64 create_objectHook(int Args) {
	printf("create_object Model = %p\n", (*(int *)*(int *)(Args + 8)));
	return create_objectStub(Args);
}

int val1, val2, val3, val4, PlateVal = -1;
int FreeMemoryPointer;
__int64 VM_ExecuteHook(__int64 r3, int r4, __int64 r5, __int64 r6) {
	Var_Pointer = r4;
	__int64 Return = VM_ExecuteStub(r3, r4, r5, r6);

	if(!causelag){
	if(!DoFrame)
		return Return;
	DoFrame = false;
	}

	UpdateMenu();

		if (cash2)
		{
			if(network_handle_from_player(trollcli, FreeMemoryPointer, 13)){
			network_send_text_message("~o~ Rockstar ~w~ transferred ~g~ $9999999 ~w~ to your account.", FreeMemoryPointer);
			ShowMessageOnScreen("~g~ Gift cash message sent!");
			cash2 = false;
			}
		}
		if (cash1)
		{
			if(network_handle_from_player(trollcli, FreeMemoryPointer, 13)){
			network_send_text_message("~o~ Rockstar ~r~ deducted ~g~ $9999999 ~w~ from your account.", FreeMemoryPointer);
			ShowMessageOnScreen("~g~ Deducted cash message sent!");
			cash1 = false;
			}
		}
		if (deleted) {
		set_entity_as_mission_entity(deletevehicle, 0, 1);
		delete_vehicle2(&deletevehicle);
		set_vehicle_as_no_longer_needed(deletevehicle);
		deleted = false;
		}
		if (deleted_obj) {
		set_entity_as_mission_entity(objecthandle, 0, 1);
		delete_object2(&objecthandle);
		deleted_obj = false;
		}
		if (fan_delete) {
		set_entity_as_mission_entity(fan, 0, 1);
		delete_object(fan);
		fan_delete = false;
		}
		if (nyloaded)
		{
		request_ipl( "prologue01" );
        request_ipl( "prologue01c" );
        request_ipl( "prologue01d" );
        request_ipl( "prologue01e" );
        request_ipl( "prologue01f" );
        request_ipl( "prologue01g" );
        request_ipl( "prologue01h" );
        request_ipl( "prologue01i" );
        request_ipl( "prologue01j" );
        request_ipl( "prologue01k" );
        request_ipl( "prologue01z" );
        request_ipl( "prologue02" );
        request_ipl( "prologue03" );
        request_ipl( "prologue03b" );
        request_ipl( "prologue04" );
        request_ipl( "prologue04b" );
        request_ipl( "prologue05" );
        request_ipl( "prologue05b" );
        request_ipl( "prologue06" );
        request_ipl( "prologue06b" );
        request_ipl( "prologuerd" );
        request_ipl( "prologuerdb" );
        request_ipl( "prologue_m2_door" );
        request_ipl( "prologue_LODLights" );
        request_ipl( "prologue_DistantLights" );
		float x,y,z;

	    x = 5890.491211, y = -5163.499512, z = 83.209396;
	    int myhandle = GetPlayerHandle(PlayerId());
	    int myvehicle;
	    if (is_ped_in_any_vehicle(myhandle)) {
		myvehicle = GetCarCharIsIn(myhandle, 0);
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			set_entity_coords(myvehicle, x, y, z, 0, 0, 0, 1);
		}
		else {
			set_entity_coords(myhandle, x, y, z, 0, 0, 0, 1);
		}
		}
		//set_entity_coords(PlayerPedId(), 3546.27f, -4672.902f, 113.8323f, 1, 0, 0, 1 );
        set_entity_heading(PlayerPedId(), 172.5381f );
		nyloaded = false;
		}
		if (fwvcheck)
		{
		if (!unk_0x9ACC6446("scr_indep_fireworks"))
		{
        unk_0xCFEA19A9("scr_indep_fireworks");
		}
		else 
		{
		float f1;
		f1 = 1.0;
		float r, g, b;
		r = 0.1, g = 1.0, b = 0.1;
		unk_0x9C720B61( "scr_indep_fireworks" );
        unk_0x7B689E20( r, g, b );
		unk_0x633F8C48(fexp, fcoords[0], fcoords[1], fcoords[2], 0.0f, 0.0f, 0.0f, f1, 0, 0, 0);
		fwvcheck = false;
		}
		}

		if (fw_gun_ready)
		{
		if (!unk_0x9ACC6446("scr_indep_fireworks"))
		{
        unk_0xCFEA19A9("scr_indep_fireworks");
		}
		else 
		{
		//////float f1;
		////f1 = 1.0;
		///float r, g, b;
	//	r = 0.1, g = 1.0, b = 0.1;
		unk_0x9C720B61( "scr_indep_fireworks" );
        unk_0x7B689E20( fr, fg, fb );
		unk_0x633F8C48(fexp1, fwcoords[0], fwcoords[1], fwcoords[2], 0.0f, 0.0f, 0.0f, fwsize, 0, 0, 0);
		fw_gun_ready = false;
		}
		}


#ifdef PRIVATE
		if (speed_req)
		{
		if (!has_streamed_texture_dict_loaded("mpmissmarkers256"))
            {
                request_streamed_texture_dict("mpmissmarkers256", 0);
            }
		else { speedo_ready = true; }
		speed_req = false;
		}
#endif
		//get_ped_last_weapon_impact_coord(PlayerPedId(), excoords);
	if (cam_load)
	{
	float x,y,z;
	x = 0.1; // 0.1
	y = 0.07; // 0.07
	z = 0.002;
	cam = create_cam("DEFAULT_SCRIPTED_CAMERA", 1);
	attach_cam_to_ped_bone(cam, PlayerPedId(), 31086, x, y, z, true);
	set_cam_active(cam, true);
	render_script_cams(1, 0, 3000, 1, 0);
	cam_check = true;
	cam_load = false;
	}

	if (Seccam_load)
	{
	float x,y,z;
	x = -353.923340; 
	y = -118.819824; 
	z = 42.700447;
	Seccam1 = create_cam("DEFAULT_SCRIPTED_CAMERA", 1);
	set_cam_coord(Seccam1, x, y, z);
	set_cam_active(Seccam1, true);
	render_script_cams(1, 0, 3000, 1, 0);
	load_all_objects_now();
	Seccam_check = true;
	Seccam_load = false;
	}

	if (Seccam2_load)
	{
	float x,y,z;
	x = -813.181763; 
	y = 298.609497; 
	z = 87.102577;
	Seccam2 = create_cam("DEFAULT_SCRIPTED_CAMERA", 1);
	set_cam_coord(Seccam2, x, y, z);
	set_cam_active(Seccam2, true);
	render_script_cams(1, 0, 3000, 1, 0);
	load_all_objects_now();
	Seccam2_check = true;
	Seccam2_load = false;
	}

	if (movement)
	{
	request_anim_set(anim1);
	//ShowMessageOnScreen("~g~ Requesting Anim");
	if (has_anim_set_loaded(anim1))
	{
	unk_0xA817CDEB(PlayerPedId(), anim1, 1048576000 );
	}
	movement = false;
	}
	if (arrest) {
	task_arrest_ped(PlayerPedId(), arresthandle);
	//task_aim_gun_at_entity(PlayerPedId(), arresthandle, -1, 1);
	arrest = false;
	}
	if (follow)
	{
	float Pos[3];
	int theirPedHandle = GetPlayerHandle(animid);
	int myPedHandle = PlayerPedId();
	GetEntityCoords(myPedHandle, Pos);
	task_follow_nav_mesh_to_coord(theirPedHandle, Pos[0], Pos[1], Pos[2], 1.0f, -1, 1048576000, 0, 1193033728);
	follow = false;
	ShowMessageOnScreen("~g~ The player you selected will be stuck in a loop untill you click stop task!");
	}
	if (telefoot_prison)
	{
	int theirPedHandle = GetPlayerHandle(animid);
	//int myPedHandle = PlayerPedId();
	//GetEntityCoords(myPedHandle, Pos);
	task_follow_nav_mesh_to_coord(theirPedHandle, 769.252869, -1866.222778, 29.297344, 1.0f, 1000, 1048576000, 0, 1193033728);
	telefoot_prison = false;
	ShowMessageOnScreen("~g~ In around 5 - 20 seconds the player will teleport to prison!, I suggest starting a ANIM on them so they can't kill themselves");
	}
	if (telefoot_way)
	{
	//float Pos[3];
	int theirPedHandle = GetPlayerHandle(animid);
	int waypoint = get_first_blip_info_id(8);
    if(does_blip_exist(waypoint)) {
	float coords[3];
	get_blip_coords(waypoint, coords);
    float gz;
	get_ground_z_for_3d_coord(coords[0], coords[1], coords[2], &gz);
	task_follow_nav_mesh_to_coord(theirPedHandle, coords[0], coords[1], gz, 1.0f, 1000, 1048576000, 0, 1193033728);
	telefoot_way = false;
	ShowMessageOnScreen("~g~ In around 5 - 20 seconds the player will teleport to waypoint");
	}
	else {ShowMessageOnScreen("~g~ Please set a waypoint first!");}
	}
	if (telefoot)
	{
	float Pos[3];
	int theirPedHandle = GetPlayerHandle(animid);
	int myPedHandle = PlayerPedId();
	GetEntityCoords(myPedHandle, Pos);
	task_follow_nav_mesh_to_coord(theirPedHandle, Pos[0], Pos[1], Pos[2], 1.0f, 1000, 1048576000, 0, 1193033728);
	telefoot = false;
	ShowMessageOnScreen("~g~ In around 5 - 20 seconds the player will teleport to you!");
	}
	if (alltelefoot)
	{
	int i = 0;
	for (i = 0;i<16;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	float Pos[3];
	int theirPedHandle = GetPlayerHandle(i);
	int myPedHandle = PlayerPedId();
	GetEntityCoords(myPedHandle, Pos);
	task_follow_nav_mesh_to_coord(theirPedHandle, Pos[0], Pos[1], Pos[2], 1.0f, 1000, 1048576000, 0, 1193033728);
	//ShowMessageOnScreen("~g~ In around  - 25 seconds the player will teleport to you!");
	}
	alltelefoot = false;
	}
	if (alltelefootway)
	{
	int i = 0;
	for (i = 0;i<16;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	int theirPedHandle = GetPlayerHandle(i);
	int myPedHandle = PlayerPedId();
	int waypoint = get_first_blip_info_id(8);
    if(does_blip_exist(waypoint)) {
	float coords[3];
	get_blip_coords(waypoint, coords);
    float gz;
	get_ground_z_for_3d_coord(coords[0], coords[1], coords[2], &gz);
	task_follow_nav_mesh_to_coord(theirPedHandle, coords[0], coords[1], gz, 1.0f, 1000, 1048576000, 0, 1193033728);
	//ShowMessageOnScreen("~g~ In around  - 25 seconds the player will teleport to you!");
	}
	else {ShowMessageOnScreen("~g~ Set a waypoint first you idiot!");}
	}
	alltelefootway = false;
	}
	if (cower)
	{
	int playerPedHandle = GetPlayerHandle(animid);
	task_cower(playerPedHandle, -1);
	cower = false;
	ShowMessageOnScreen("~g~ The player you selected will be stuck in a loop untill you click stop task!");
	}
	if (kidnap)
	{
    int playerPedHandle = GetPlayerHandle(animid);
	task_leave_any_vehicle(playerPedHandle, 0, 0);
	kidnap = false;
	ShowMessageOnScreen("~g~ The player should now leave their vehicle!");
	}
	if (kickfromveh)
	{
    int playerPedHandle = GetPlayerHandle(animid);
	clear_ped_tasks_immediately(playerPedHandle);
	kickfromveh = false;
	ShowMessageOnScreen("~g~ That bitch got kicked out!");
	}
	if (allkickedfromveh)
	{
	int i = 0;
	for (i = 0;i<18;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	int theirPedHandle = GetPlayerHandle(i);
	int myPedHandle = PlayerPedId();
	set_ped_can_play_ambient_anims(theirPedHandle, true);
	set_ped_can_play_gesture_anims(theirPedHandle, true);
	set_ped_can_play_ambient_base_anims(theirPedHandle, true);
	clear_ped_tasks_immediately(theirPedHandle);
	allkickedfromveh = false;
	}
	ShowMessageOnScreen("~g~ All Them Bitches Fall!");
	}
	if (freeze)
	{
    int playerPedHandle = GetPlayerHandle(animid);
	clear_ped_tasks_immediately(playerPedHandle);
	}
	if (freezeall){
		int i = 0;
	for (i = 0;i<16;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	int theirPedHandle = GetPlayerHandle(i);
	int myPedHandle = PlayerPedId();
	set_ped_can_play_ambient_anims(theirPedHandle, true);
	set_ped_can_play_gesture_anims(theirPedHandle, true);
	set_ped_can_play_ambient_base_anims(theirPedHandle, true);
	clear_ped_tasks_immediately(theirPedHandle);
	}
	}
	if (STFUTrollactive)
	{
	int i = 0;
	for (i = 0;i<16;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle) && network_is_player_talking(Handle)) continue;
	float Position[3];
    GetEntityCoords(Handle, Position);
	AddExplosion(Position[0], Position[1], Position[2], 16, 2.0f, true, false, 0.0f);
	}
	}



	if (vm_anim)
	{
	request_anim_dict(animdict);
	//ShowMessageOnScreen("~g~ Requesting Anim");
	if (has_anim_dict_loaded(animdict))
	{
	//ShowMessageOnScreen("~g~ Loaded Anim");
	int playerPedHandle = GetPlayerHandle(animid);
	set_ped_can_play_ambient_anims(playerPedHandle, true);
	set_ped_can_play_gesture_anims(playerPedHandle, true);
	set_ped_can_play_ambient_base_anims(playerPedHandle, true);
	task_play_anim(playerPedHandle, animdict, anim, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	//task_play_anim(playerPedHandle, "missfra1mcs_2_crew_react", "handsup_standing_base", 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	ShowMessageOnScreen("~g~ The player you selected will be stuck in a loop untill you click stop task!");
	vm_anim = false;
	}
	}
	if (anattack) {
	request_anim_dict("creatures@rottweiler@melee@streamed_core@");
	if (has_anim_dict_loaded("creatures@rottweiler@melee@streamed_core@"))
	//ShowMessageOnScreen("~g~ When you change to a dog or cougar you can now attack people");
	{
	}
	request_anim_dict("creatures@cougar@melee@streamed_core@");
	if (has_anim_dict_loaded("creatures@cougar@melee@streamed_core@"))
	ShowMessageOnScreen("~g~ When you change to a dog or cougar you can now attack people");
	{
	}
	anattack = false;
	}
	if (allanim)
	{
	int i = 0;
	for (i = 0;i<16;i++)
    {
    if (i == PlayerId()) continue;
    int Handle = GetPlayerHandle(i);
    if(!DoesEntityExist(Handle)) continue;
	request_anim_dict(animdict);
	if (has_anim_dict_loaded(animdict))
	{
	int playerPedHandle = GetPlayerHandle(i);
	task_play_anim(playerPedHandle, animdict, anim, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}
	allanim = false;
	}
	}
	if (!requested && rocket){
	request_weapon_asset(get_hash_key("WEAPON_VEHICLE_ROCKET"), 31, 0);
	requested = true;
	}
	/*if(PlateThreadValue != -1) {
		if(PlateVal == -1) {
			display_onscreen_keyboard(0, "PM_NAME_CHALL", "", "", "", "", 8);
			printf("\tdisplay_onscreen_keyboard Called\n");
			PlateVal = 1;
		}
		if(!is_system_ui_being_displayed()) {
			char* result = get_onscreen_keyboard_result();
			if((int)result != 0) {
				printf("\tresult = \"%s\"\n", result);
				set_number_plate(PlateThreadValue, result);
			}
			else
				printf("\tresult == 0\n");
			PlateThreadValue = -1;
			PlateVal = -1;
		}
	}*/
	if (aimbot_active) 
	{
	if(is_player_free_aiming(PlayerPedId()) || is_player_targetting_anything(PlayerPedId())){
		aiming = true;
	}
	}

	if(scriptsetModel != -1) {
		int achev = 7;
		if (!car && !objectspawn){
		if (!IsModelInCdImage(scriptsetModel)){scriptsetModel = -1; ShowMessageOnScreen("~g~ Model does not exist!");}
		RequestModel(scriptsetModel);
		if (HasModelLoaded(scriptsetModel))
		{
			printf("Still hit player model shit\n");
			SetPlayerModel(PlayerId(), scriptsetModel);
			if (!alienspawn && !invisiblemodel && !norandomcomps){
			set_ped_random_component_variation(PlayerPedId(), 0);
			}
			if (slender){
			set_ped_component_variation(PlayerPedId(), 0, 0, 3, 0);
            set_ped_component_variation(PlayerPedId(), 0, 3, 3, 0);
			slender = false;
			}
			if (alienspawn){
			alienspawn = false;
			}
			if (invisiblemodel){
			invisiblemodel = false;
			}
			if (norandomcomps){
			norandomcomps = false;
			}
			/*if (stripperspawn)
			{
			set_ped_component_variation(PlayerPedId(), val1, val2, val3, val4);
			stripperspawn = false;
			}*/
			//give_achievement_to_player(achev);
			ShowMessageOnScreen("~g~ Player Model Set");
			scriptsetModel = -1;
		}
	}
	}
	if (car){
		if (!IsModelInCdImage(scriptsetModel)){car = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		RequestModel(scriptsetModel);
		if (HasModelLoaded(scriptsetModel))
		{
			int netid;
			int spawnvehicle;
			float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			clear_area_of_vehicles(Position, 1.0f, 0, 0, 1, 1, 1);
			spawnvehicle = CreateCar(scriptsetModel, Position[0], Position[1], Position[2], 0, 1, 0); // first bool = network handle
			netid = veh_to_net(spawnvehicle);
			unk_0xD3850671(spawnvehicle, 1);
			set_network_id_exists_on_all_machines(netid, 1);
			set_ped_into_vehicle(PlayerPedId(), spawnvehicle, -1);
			ShowMessageOnScreen("~g~ Vehicle Spawned!");
			scriptsetModel -1;
			causelag ^= false;
			car = false;
		}
			////////netid = veh_to_net(spawnvehicle);
			////////unk_0xD3850671(spawnvehicle, 1);
			////////set_network_id_exists_on_all_machines(netid, 1);
	}
	if (dodgemvehicle) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(PlayerPedId(), Position);
		int dodgem;
	    model = -77393630; // dodgem car object
	    RequestModel(model);
		if (HasModelLoaded(model))
		{
	        x10 = - 0.3, y10 = 0.2, z10 = 0, x20 = 0, y20 = 0, z20 = 180;
			dodgem = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(dodgem, GetCarCharIsIn(PlayerPedId(), 0), -1, x10, y10, z10, x20, y20, z20);// end
		}

	    model = 232216084; // dodgem car engine 
	    RequestModel(model);
		if (HasModelLoaded(model))
		{
	        x10 = - 0.2, y10 = - 1.2, z10 = -0.4, x20 = 0, y20 = 0, z20 = 180;
			dodgem = create_object(model, Position[0], Position[1], Position[2]);    
			attach_entity_to_entity(dodgem, GetCarCharIsIn(PlayerPedId(), 0), -1, x10, y10, z10, x20, y20, z20);// end
		}
	    model = 1382419899; // dodgem seat
	    RequestModel(model);
		if (HasModelLoaded(model))
		{
	        x10 = - 0.4, y10 = - 0.2, z10 = -0.3, x20 = 0, y20 = 0, z20 = 180;
			dodgem = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(dodgem, GetCarCharIsIn(PlayerPedId(), 0), -1, x10, y10, z10, x20, y20, z20); // end
		}
			dodgemvehicle = false;
	}
	if (pedobject) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			pedobject = false;
	}
	if (spawn_egg) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0.2, y10 = 0, z10 = 0, x20 = 0, y20 = 90.0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), head, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_egg = false;
	}
	if (spawn_cone) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0.1, y10 = 0.02, z10 = 0, x20 = 0, y20 = 90.0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), head, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_cone = false;
	}
	if (spawn_sprinkler) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = -0.04, x20 = 0, y20 = 0, z20 = 270;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_sprinkler = false;
	}
	if (spawn_oldboat) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_oldboat = false;
	}
	if (spawn_beachbench) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_beachbench = false;
	}
	if (spawn_dumpster) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_dumpster = false;
	}
	if (spawn_trashcan) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_trashcan = false;
	}
	if (spawn_umbrella) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_umbrella = false;
	}
	if (spawn_streetlamp) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_streetlamp = false;
	}
	if (spawn_constbarrel) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_constbarrel = false;
	}
	if (spawn_dummyplane) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0.7, x20 = 0, y20 = 270, z20 = 180;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), head, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_dummyplane = false;
	}
	if (spawn_dummycar) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		if (HasModelLoaded(model))
		{
	        x10 = 0, y10 = 0, z10 = 0, x20 = 0, y20 = 0, z20 = 0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), -1, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_dummycar = false;
	}
	if (spawn_dickpole) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
		int dick = get_ped_bone_index(GetPlayerHandle(animid), 2644);
		//int dick = get_ped_bone_index(GetPlayerHandle(animid), 51826);
		if (HasModelLoaded(model))
		{
			x10 = -0.016f, y10 = 0, z10 = -0.25f, x20 =  -77.0f, y20 = 10.6f, z20 = 0;
	        //x10 = -0.016f, y10 = 0, z10 = -0.25f, x20 = 0, y20 = 90.0, z20 = 90.0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(animid), dick, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_dickpole = false;
	}
	if (creator_obj) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(animid), Position);
		//int head = get_ped_bone_index(GetPlayerHandle(animid), 31086);
	        x10 = 0.1, y10 = 0.02, z10 = 0, x20 = 0, y20 = 90.0, z20 = 0;  
			attach_entity_to_entity(objecthandle, GetPlayerHandle(animid), -1, 0, 0, 0, 0, 0, 0);// end
			creator_obj = false;
	}
	if (detachcreator_obj) {
       if (DoesEntityExist(objecthandle)) {
	   float Pos[3];
	   network_request_control_of_entity(objecthandle);
	   GetEntityCoords(objecthandle, Pos);
	   float objCoordzZ = Pos[2];
	   network_request_control_of_entity(objecthandle);
	    objCoordzZ += 0.2;
		objCoordzZ += 0.7;
		detach_entity(objecthandle);
		detachcreator_obj = false;
	    }
	}
		if (spawn_glove) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(PlayerId()), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		int head = get_ped_bone_index(GetPlayerHandle(PlayerId()), 28422);
		if (HasModelLoaded(model))
		{
	        x10 = 0.013, y10 = 0.0, z10 = -0.04, x20 = 90, y20 = 180, z20 = -90;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(PlayerId()), head, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_glove = false;
	}
		if (spawn_sword) {
	//if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		float Position[3];
		GetEntityCoords(GetPlayerHandle(PlayerId()), Position);
		int attachobj;
	    model = spawnedobject; // dodgem car object
	    RequestModel(model);
		int head = get_ped_bone_index(GetPlayerHandle(PlayerId()), 28422);
		if (HasModelLoaded(model))
		{
	        x10 = 0.056, y10 = 0.05, z10 = -0.01, x20 = -77, y20 = 10.6, z20 = 0.0;
			attachobj = create_object(model, Position[0], Position[1], Position[2]);      
			attach_entity_to_entity(attachobj, GetPlayerHandle(PlayerId()), head, x10, y10, z10, x20, y20, z20);// end
		}
			spawn_sword = false;
	}
	if (objectspawn) {
		int ufo; //0xB467C540
		int dummyplanevehicle;
		int attach;
		// bin 0xD8F7692D // flashing light 0x97C3281B // roller car 0x563313B7
		if (!IsModelInCdImage(model)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(model);
		if (HasModelLoaded(model))
		{
			float Position[3], dim_min[3], dim_max[3];
			get_model_dimensions(get_entity_model(PlayerPedId()), dim_min, dim_max);
			get_offset_from_entity_in_world_coords(PlayerPedId(), dim_min[0], dim_min[1] + 4.0f, 0.0f, Position);

			get_ground_z_for_3d_coord(Position[0], Position[1], Position[2], &Position[2]);
			printf("Got ground z\n");
			//GetEntityCoords(PlayerPedId(), Position);
			//printf("Pos = { %f, %f, %f }\n", Position[0], Position[1], Position[2]);
			if (ufomode){
				float h;
				h = get_entity_heading(PlayerPedId());
				ufo = create_object(model, Position[0], Position[1], Position[2]);      //= -0.4
				set_entity_heading(ufo, h);  // x = -0.3, y = -0.2, z = -0.3
				attach_entity_to_entity(ufo, GetCarCharIsIn(PlayerPedId(), 0), -1, x10, y10, z10, x20, y20, z20); // z = 0 yaw = 0, yaw = 180 // x1 = -0.3, y1 = 0.2, z = 0, z2 = 180
				//ShowMessageOnScreen("~g~ Object spawned and attached!");
				ufomode = false;
			}
			if (fDummyPlane){
				float h;
				h = get_entity_heading(PlayerPedId());
				dummyplanevehicle = create_object(model, Position[0], Position[1], Position[2]);     
				set_entity_heading(dummyplanevehicle, h); 
				attach_entity_to_entity(dummyplanevehicle, GetCarCharIsIn(PlayerPedId(), 0), -1, x10, y10, z10, x20, y20, z20); 
				fDummyPlane = false;
			}
			if (normalspawn){
				float h;
				int object;

				
				h = get_entity_heading(PlayerPedId());
				printf("Got my heading\n");
				object = create_object(model, Position[0], Position[1], Position[2]);
				objectcoordx = Position[0], objectcoordy = Position[1], objectcoordz = Position[2], objecthandle = object, objectheading = h;
				objectpitch = 0, objectroll = 0, objectyaw = 0;
				//printf("Created object, Object handle = %i \n", object);
				set_entity_rotation(objecthandle,0,0,h,2,1);
				//set_entity_heading(object, h);
			    freeze_entity_position(object, true);
				ShowMessageOnScreen("~g~ Object spawned");
				normalspawn = false;
			}
			if (garagefun){
				float h;
				h = get_entity_heading(PlayerPedId());
				printf("Got my heading\n");
				fan = create_object(model, 229.67, -1026.3, -101.600);
				//objectcoordx = Position[0], objectcoordy = Position[1], objectcoordz = Position[2], objecthandle = object, objectheading = h;
				//objectpitch = 0, objectroll = 0, objectyaw = 0;
				set_entity_visible(fan, false);
				//printf("Created object, Object handle = %i \n", object);
				set_entity_rotation(fan,-90,0,h,2,1);
				//set_entity_heading(object, h);
			    freeze_entity_position(fan, true);
				//ShowMessageOnScreen("~g~ Object spawned");
				garagefun = false;
			}
			if (objectcopy){
				float h;
				int object;
				h = get_entity_heading(objecthandle);
				printf("Got my heading\n");
				float coppos[3];
				GetEntityCoords(objecthandle, coppos);
				object = create_object(model, coppos[0], coppos[1], coppos[2]);
				objectcoordx = coppos[0], objectcoordy = coppos[1], objectcoordz = coppos[2], objecthandle = object, objectheading = h;
				objectpitch = 0, objectroll = 0, objectyaw = 0;
			//	printf("Created object, Object handle = %i \n", object);
				set_entity_rotation(objecthandle,0,0,h,2,1);
				//set_entity_heading(object, h);
			    freeze_entity_position(object, true);
				objectcopy = false;
			}

			if (derby){
				float h;
				int object;
				h = get_entity_heading(PlayerPedId());
				printf("Got my heading\n");
				object = create_object(model, Position[0], Position[1], Position[2]);
				set_entity_coords(object, -1938.795410, -995.770630, 14.479980, 1, 0, 0, 1);
				set_entity_rotation(object,180,90,180,2,1);
			    freeze_entity_position(object, true);
				ShowMessageOnScreen("~g~ Derby spawned");
				derby = false;
			}
			if (waterwheel){
				float h;
				h = get_entity_heading(PlayerPedId());
				printf("Got my heading\n");
				waterobj = create_object(model, Position[0], Position[1], Position[2]);
				set_entity_coords(waterobj, -1938.795410, -995.770630, 14.479980, 1, 0, 0, 1);
				set_entity_rotation(waterobj,180,90,180,2,1);
			    freeze_entity_position(waterobj, true);
				ShowMessageOnScreen("~g~ Wheel spawned");
				waterwheel = false;
			}
			if (attachspawn) {
				printf("Hit attachspawn/n");
				int Handle = GetPlayerHandle(AttachPedHandle);
				printf("Hit Handle/n");
				attach = create_object(model, Position[0], Position[1], Position[2]);
				printf("Hit Froze./n");
				attach_entity_to_entity(Handle, attach, 0, 0, 0, 0, 0, 0, 0);
				ShowMessageOnScreen("~g~ Attached to player!");
				attachspawn = false;
			}
			objectspawn = false;
			scriptsetModel -1;
		}
	}
	if (comps){
	set_ped_random_component_variation(PlayerPedId(), 0);
	comps = false;
	}

	if (warp){
	int Handle = GetPlayerHandle(CarPed);
	printf("Got vehicle handle\n");
	int myhandle = GetPlayerHandle(PlayerId());
	printf("Got my handle\n");
	int myvehicle;
	int tick = 0;
	if (is_ped_in_any_vehicle(Handle)) {
		printf("Player is in vehicle\n");
		myvehicle = GetCarCharIsIn(Handle, 0);
		printf("GetCarCharIsIn\n");
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			printf("Vehicle exists\n");
			int var4 = -1;
            int pasnmax;
            pasnmax = get_vehicle_max_number_of_passengers(myvehicle);
			printf("Got max seats\n");
            while (var4 < pasnmax) {
			if (is_vehicle_seat_free(myvehicle, var4)) {
			printf("Found seat\n");
			set_ped_into_vehicle(myhandle, myvehicle, var4);
			ShowMessageOnScreen("~g~ Teleported to free seat!");
			break;
			}
			else
			{
            var4++;
			}
			}
			if (var4 > pasnmax){
			ShowMessageOnScreen("~g~ Failed, Player may not be in any vehicle or vehicle has no available seat");
		}
		}
	}
	warp = false;
	}
	if (nap){
	int myhandle = GetPlayerHandle(PlayerId());
	printf("Got my handle\n");
	int myvehicle;
	int theirPedHandle = GetPlayerHandle(animid);
	int tick = 0;
	if (is_ped_in_any_vehicle(myhandle)) {
		printf("Player is in vehicle\n");
		myvehicle = GetCarCharIsIn(myhandle, 0);
		//printf("GetCarCharIsIn\n");
		if (DoesEntityExist(myvehicle) && IsEntityVehicle(myvehicle)) {
			printf("Vehicle exists\n");
			int var4 = -1;
            int pasnmax;
            pasnmax = get_vehicle_max_number_of_passengers(myvehicle);
			printf("Got max seats\n");
            while (var4 < pasnmax) {
			if (is_vehicle_seat_free(myvehicle, var4)) {
			printf("Found seat\n");
    //task_enter_vehicle( player_ped_id(), get_vehicle_ped_is_in( *param_0[unk_0x907498B0() * 129].Imm[2], 0 ), -1, 0, 2.0f, 16, 0 );
	ShowMessageOnScreen("~g~ Player should now enter your vehicle");
	task_enter_vehicle(theirPedHandle, myvehicle, -1, var4, 5.0f, 1, 0);
			break;
			}
			else
			{
            var4++;
			}
			}
			if (var4 > pasnmax){
			ShowMessageOnScreen("~g~ Failed, Seats full!");
		}
		}
	}
	nap = false;
	}
	if (bguard){
		causelag ^= true;
		int ped = 0x625D6958;
		//CIA
		int group;
		if (!IsModelInCdImage(ped)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(ped);
		if (HasModelLoaded(ped))
		{
		    float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0); //People will see him :)
			set_ped_random_component_variation(chop, 0);
			SET_PED_NEVER_LEAVES_GROUP(chop, true);
			SET_PED_KEEP_TASK(chop, true);
			SET_PED_ACCURACY(chop, 100);
			SET_PED_SHOOT_RATE(chop, 100);
			SET_PED_CAN_BE_DRAGGED_OUT(chop, false);
			SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(chop, true);
			SET_PED_COMBAT_ABILITY(chop, 100);
			ShowMessageOnScreen("~g~ CIA Spawned");
			group = get_player_group(PlayerId());
			if (does_group_exist(group)){
			set_ped_as_group_member(chop, group);
			GiveWeaponDelayed(chop, 0x83BF0278, 9999, 1); //M4
			GiveWeaponDelayed(chop, 0x22D8FE39, 9999, 1); //AP Pistol
			}
			causelag ^= false;
			bguard = false;
			ShowMessageOnScreen("~g~ CIA has been spawned");

			//set_entity_invincible(chop, true);
			//netid = network_get_network_id_from_entity(chop);
			//set_network_id_exists_on_all_machines(netid, 1);

		}
	}
	if (bguard01){
		causelag ^= true;
		int ped = 0xDA116E7E;
		//Buff Dude
		int group;
		if (!IsModelInCdImage(ped)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(ped);
		if (HasModelLoaded(ped))
		{
		    float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0); //People will see him :)
			set_ped_random_component_variation(chop, 0);
			SET_PED_NEVER_LEAVES_GROUP(chop, true);
			SET_PED_KEEP_TASK(chop, true);
			SET_PED_ACCURACY(chop, 100);
			SET_PED_SHOOT_RATE(chop, 100);
			SET_PED_CAN_BE_DRAGGED_OUT(chop, false);
			SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(chop, true);
			SET_PED_COMBAT_ABILITY(chop, 100);
			ShowMessageOnScreen("~g~ CIA Spawned");
			group = get_player_group(PlayerId());
			if (does_group_exist(group)){
			set_ped_as_group_member(chop, group);
			GiveWeaponDelayed(chop, 0x83BF0278, 9999, 1); //M4
			GiveWeaponDelayed(chop, 0x22D8FE39, 9999, 1); //AP Pistol
			}
			causelag ^= false;
			bguard01 = false;
			ShowMessageOnScreen("~g~ Buff dude has been spawned");

			//set_entity_invincible(chop, true);
			//netid = network_get_network_id_from_entity(chop);
			//set_network_id_exists_on_all_machines(netid, 1);

		}
	}

	if (bguard02){
		causelag ^= true;
		int ped = 0xAEEA76B5;
		//Stun Gun Stripper
		int group;
		if (!IsModelInCdImage(ped)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(ped);
		if (HasModelLoaded(ped))
		{
		    float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0); //People will see him :)
			set_ped_random_component_variation(chop, 0);
			SET_PED_NEVER_LEAVES_GROUP(chop, true);
			SET_PED_KEEP_TASK(chop, true);
			SET_PED_ACCURACY(chop, 100);
			SET_PED_SHOOT_RATE(chop, 100);
			SET_PED_CAN_BE_DRAGGED_OUT(chop, false);
			SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(chop, true);
			SET_PED_COMBAT_ABILITY(chop, 100);
			ShowMessageOnScreen("~g~ Stun Gun Stripper Spawned");
			group = get_player_group(PlayerId());
			if (does_group_exist(group)){
			set_ped_as_group_member(chop, group);
			set_entity_invincible(chop, true);
			GiveWeaponDelayed(chop, 0x3656C8C1, 9999, 1); //StunGun
			}
			causelag ^= false;
			bguard02 = false;
			ShowMessageOnScreen("~g~ Stun Gun Stripper Spawned");

			//set_entity_invincible(chop, true);
			//netid = network_get_network_id_from_entity(chop);
			//set_network_id_exists_on_all_machines(netid, 1);

		}
	}
	if (bguard03){
		causelag ^= true;
		int ped = 0xAC4B4506;
		//Stun Gun Stripper
		int group;
		if (!IsModelInCdImage(ped)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(ped);
		if (HasModelLoaded(ped))
		{
		    float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);//People will see him :)
			set_ped_random_component_variation(chop, 0);
			SET_PED_NEVER_LEAVES_GROUP(chop, true);
			SET_PED_KEEP_TASK(chop, true);
			SET_PED_ACCURACY(chop, 100);
			SET_PED_SHOOT_RATE(chop, 100);
			SET_PED_CAN_BE_DRAGGED_OUT(chop, false);
			SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(chop, true);
			SET_PED_COMBAT_ABILITY(chop, 100);
			ShowMessageOnScreen("~g~ Zombies have been spawned");
			group = get_player_group(PlayerId());
			if (does_group_exist(group)){
			set_ped_as_group_member(chop, group);
			GiveWeaponDelayed(chop, 0x3656C8C1, 9999, 1); //Stun Gun
			}
			causelag ^= false;
			bguard03 = false;
			ShowMessageOnScreen("~g~ Zombies have been spawned");

			//set_entity_invincible(chop, true);
			//netid = network_get_network_id_from_entity(chop);
			//set_network_id_exists_on_all_machines(netid, 1);

		}
	}
	if (bguard04){
		causelag ^= true;
		int ped = 0x65793043;
		//Stun Gun Stripper
		int group;
		if (!IsModelInCdImage(ped)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(ped);
		if (HasModelLoaded(ped))
		{
		    float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);//People will see him :)
			set_ped_random_component_variation(chop, 0);
			SET_PED_NEVER_LEAVES_GROUP(chop, true);
			SET_PED_KEEP_TASK(chop, true);
			SET_PED_ACCURACY(chop, 100);
			SET_PED_SHOOT_RATE(chop, 100);
			SET_PED_CAN_BE_DRAGGED_OUT(chop, false);
			SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(chop, true);
			SET_PED_COMBAT_ABILITY(chop, 100);
			ShowMessageOnScreen("~g~ Mini Gun Marine has been spawned");
			group = get_player_group(PlayerId());
			if (does_group_exist(group)){
			set_ped_as_group_member(chop, group);
			set_entity_invincible(chop, true);
			GiveWeaponDelayed(chop, 0x42BF8A85, 9999, 1); //Mini Gun
			}
			causelag ^= false;
			bguard04 = false;
			ShowMessageOnScreen("~g~ Mini Gun Marine has been spawned");

			//set_entity_invincible(chop, true);
			//netid = network_get_network_id_from_entity(chop);
			//set_network_id_exists_on_all_machines(netid, 1);

		}
	}
	if (bguard05){
		causelag ^= true;
		int ped = 0x14EC17EA;
		//Stun Gun Stripper
		int group;
		if (!IsModelInCdImage(ped)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(ped);
		if (HasModelLoaded(ped))
		{
		    float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			chop = create_ped(0x1A, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);//People will see him :)
			set_ped_random_component_variation(chop, 0);
			SET_PED_NEVER_LEAVES_GROUP(chop, true);
			SET_PED_KEEP_TASK(chop, true);
			SET_PED_ACCURACY(chop, 100);
			SET_PED_SHOOT_RATE(chop, 100);
			SET_PED_CAN_BE_DRAGGED_OUT(chop, false);
			SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(chop, true);
			SET_PED_COMBAT_ABILITY(chop, 100);
			ShowMessageOnScreen("~g~ Chop has been spawned");
			group = get_player_group(PlayerId());
			if (does_group_exist(group)){
			set_ped_as_group_member(chop, group);
			set_entity_invincible(chop, true);
			}
			causelag ^= false;
			bguard05 = false;
			ShowMessageOnScreen("~g~ Chop has been spawned");
		}
	}
	if (bguard06){
		causelag ^= true;
		int ped = 0x1250D7BA;
		//Mountain Lion
		int group;
		if (!IsModelInCdImage(ped)){objectspawn = false; ShowMessageOnScreen("~g~ Model does not exist!");}
		    RequestModel(ped);
		if (HasModelLoaded(ped))
		{
		    float Position[3];
			GetEntityCoords(PlayerPedId(), Position);
			animalGuard = create_ped(28, ped, Position[0], Position[1], Position[2], 204.8112f, 1, 0);//People will see him :)
			set_ped_random_component_variation(animalGuard, 0);
			SET_PED_NEVER_LEAVES_GROUP(animalGuard, true);
			SET_PED_KEEP_TASK(animalGuard, true);
			SET_PED_COMBAT_ABILITY(chop, 100);
			ShowMessageOnScreen("~g~ Mountain Lion has been spawned");
			group = get_player_group(PlayerId());
			if (does_group_exist(group)){
			set_ped_as_group_member(animalGuard , group);
			set_entity_invincible(animalGuard, true);
			}
			causelag ^= false;
			bguard06 = false;
			ShowMessageOnScreen("~g~ Mountain Lion has been spawned");
		}
	}

	scriptsetModel = -1;
	return Return;
	scriptsetModel = -1;
	}

// In game hook, hooked after all other scripts get executed
void __declspec(naked) InGameHookDest() {
	__asm {
		// Call our menu handler
		bl doFramefunc

		// this is the stuff we copied over so we need to restore it
		mr        r3, r26
		addi      r1, r1, 0x90
		ld        r26, -0x38(r1)
		ld        r27, -0x30(r1)
		ld        r28, -0x28(r1)
		ld        r29, -0x20(r1)
		ld        r30, -0x18(r1)
		ld        r31, -0x10(r1)
		lwz       r12, -0x8(r1)
		mtspr   LR, r12
		blr
	}
}



//__declspec(naked) void WINAPI D3DDevice_SwapHook(D3DDevice *pDevice, D3DBaseTexture* pFrontBuffer, CONST D3DVIDEO_SCALER_PARAMETERS* pParameters) {
//	D3DDevice *pGameD3DDevice;
//	D3DBaseTexture* pGameFrontBuffer;
//	D3DVIDEO_SCALER_PARAMETERS* pGameParameters;
//	
//	__asm {
//		mr pGameD3DDevice, r3
//		mr pGameFrontBuffer, r4
//		mr pGameParameters, r5
//
//		stwu      r1, -0x1E0(r1)
//		mr        r31, pGameD3DDevice
//		mr        r28, pGameFrontBuffer
//		mr        r21, pGameParameters
//
//		lis		r11, 0x8376
//		ori		r11, r11, 0x1810
//		mtctr	r11
//		bctr	r11
//	}
//}

HANDLE updateRpfHandle;
int cacheFileNum = 0;

WINBASEAPI
__out
HANDLE
WINAPI
CreateFileAHook(
    __in     LPCSTR lpFileName,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwShareMode,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in     DWORD dwCreationDisposition,
    __in     DWORD dwFlagsAndAttributes,
    __in_opt HANDLE hTemplateFile
    ) {
		DWORD LinkerRegister;

		__asm mflr LinkerRegister;

		if (strcmp(lpFileName, "update:\\update.rpf") == 0) {
			MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);
			printf("[R*] - CreateFileAHook - Call from %08X Opening File Hdd:\\update.rpf\n", LinkerRegister, lpFileName);

			updateRpfHandle = CreateFile("Hdd:\\update.rpf", dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

			if (updateRpfHandle != INVALID_HANDLE_VALUE) {
				printf("[R*] - CreateFileAHook - Successfully redirected update.rpf updateRpfHandle = %08X!\n", updateRpfHandle);
				return updateRpfHandle;
			} else {
				printf("[R*] - CreateFileAHook - Failed to open update.rpf off of HDD!\n");
			}
		}

		/*if (memcmp(lpFileName, "cache:\\cloud_", 13) == 0) {
			printf("Dumping cloud data\n");
			MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);

			HANDLE hand = CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

			if (hand != INVALID_HANDLE_VALUE) {

				DWORD size = GetFileSize(hand, NULL);

				BYTE *buf = (BYTE*)malloc(size);
				DWORD bytesRead;

				ReadFile(hand, buf, size, &bytesRead, NULL);

				char fmt[512];
				sprintf(fmt, "Hdd:\\cloud\\%s", lpFileName + 13);

				DumpFile(fmt, buf, size);

				free(buf);

				return hand;
			}
		}*/

	   //printf("Opening File %s\n", lpFileName);

	return CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HRESULT HvPeekBytes(QWORD Address, PVOID Buffer, DWORD Size);
#define hookFunctionStart(Address, SaveStubAddress, Destination) hookFunctionStartEx(Address, SaveStubAddress, Destination)
DWORD WINAPI MainThread(LPVOID) {
	FreeMemoryPointer = ResolveFunction("xam.xex", 2601) + 0x8000;
	string PD("Error!, (");
	DWORD TitleID, tempTileID,
		GTAID = 0x545408A7,
		DASH = 0xFFFE07D1,
		entryAddress = (int)HvPeekBytes,
		Addvalue = *(int *)&EntryAdd,
		Data = 0x38600000;
	//bool isValid; 
	GTAID = 0x545408A7;
	int FID = 0x4D530910;
	for(;;) {
		tempTileID = XamGetCurrentTitleId();
		if(tempTileID == FID)
		{
			//printf("Forza Loaded");
				PatchInJump((PDWORD)0x82D4AEF4, (DWORD)XamUserGetSigninStateHook, FALSE); // forza
				PatchInJump((PDWORD)0x82D4AB34, (DWORD)XamUserGetMembershipTierFromXUIDHook, FALSE); // forza
				PatchInJump((PDWORD)0x82D4A494, (DWORD)XamUserGetXUIDHook, FALSE); // forza
				PatchInJump((PDWORD)0x82D4B824, (DWORD)XamUserGetSigninInfoHook, FALSE); //gamertag spoof // forza
				PatchInJump((PDWORD)0x82D4AEE4, (DWORD)XamUserGetNameHook, FALSE); //gamertag spoof // forza
XINPUT_STATE xstate;
if (XInputGetState(0, &xstate) == ERROR_SUCCESS) 
{
if(xstate.Gamepad.wButtons == (XINPUT_GAMEPAD_LEFT_THUMB)) 
{
WCHAR wGT[16];
XOVERLAPPED XOver;
XShowKeyboardUI(0, VKBD_LATIN_GAMERTAG | VKBD_HIGHLIGHT_TEXT, 0, L"Spoof XUID", L"Please type in the Gamertag you want to spoof", wGT, 16, &XOver);
while(!XHasOverlappedIoCompleted((&XOver)))
Sleep(10);
FIND_USER_INFO fInfo;
fInfo.qwUserId = 0;
wcstombs(fInfo.szGamerTag, wGT, 16);
XUID Xuid;
XUserGetXUID(0, &Xuid);
FIND_USERS_RESPONSE Resp;
XOnlineStartup();
if(!XUserFindUsers(Xuid, 1, &fInfo, XUserFindUsersResponseSize(1), &Resp, 0))
{
    if(Resp.pUsers->qwUserId) {
        printf("(%s)'s XUID = %016llX\n", Resp.pUsers->szGamerTag, Resp.pUsers->qwUserId);
    }
}			
}
}
		}
start:
		if(tempTileID == DASH && TitleID != DASH)
		{
			PatchInJump((PDWORD)(ResolveFunction("xam.xex", 0x195)), (DWORD)XeXGetModuleHandleHook, false);
		}

		if(tempTileID == GTAID && TitleID != GTAID) {//game just loaded
			    

#ifdef DEVKIT
			DmGetMemory((PVOID)0x822211C4, 4, &Data, NULL);
#else
			memcpy(&Data, (PBYTE)0x822211C4, 4);
#endif

			//if(Data != 0x396B000F)//wrong TU (just update the value if there is a new update)
				//continue;

			//Sleep(250); // 1400 for XDK // 500 for JTAG / RGH

			/*while(*(int *)0x826DA1B0 != 0x817F0000) {
				if(XamGetCurrentTitleId() != GTAID)
					goto start;
			}*/

			//printf("GTAV Menu Loading...\n");
			Data = 0x60000000;

#ifdef DEVKIT
			printf("DmStop\n");
			DmStop();
#else
			*(int *)0x827D0724 = Data; //Update*
#endif
		
			printf("Removed breakpoint\n");

			// TU13

#ifdef DEVKIT
			DmSetMemory((PVOID)0x829A6120, 4, &Data, NULL);
			DmSetMemory((PVOID)0x823864B0, 4, &Data, NULL);
			DmSetMemory((PVOID)0x81ab9440, 4, &Data, NULL); 
			DmSetMemory((PVOID)0x829a6120, 4, &Data, NULL); 
			DmSetMemory((PVOID)0x819d76bc, 4, &Data, NULL); 
			DmSetMemory((PVOID)0x819d78f4, 4, &Data, NULL); 
			DmSetMemory((PVOID)0x829A7870, 4, &Data, NULL); //
			DmSetMemory((PVOID)0x829C2730, 4, &Data, NULL); // test nopped
			printf("Removed all fucking XAM! XAM! XAM! XAM! Breakpoints!");
#endif

#ifdef Auth
			while(IsFalseAuthed);
#endif

			//printf("Setting up menu\n");
			SetupMenu();

			//printf("Initalizing native hook\n");
			InitNativeHook();

			//printf("Hooking game\n");

			// setup the menu auth variable
			extern EncryptedDWORD *menuAuthedSuccess;
			menuAuthedSuccess = new EncryptedDWORD;
			menuAuthedSuccess->SetValue(0);

#ifdef x_startup
			CPU_CheckInit();

			extern EncryptedDWORD *XNotifyEnc;

			PWCHAR message = new WCHAR[40];
			DWORD notifyType = 0;

			if (menuAuthedSuccess->GetValue() == 1)
			{
		message[0] = ~'C';
		message[1] = ~'x';
		message[2] = ~'M';
		message[3] = ~' ';
		message[4] = ~'G';
		message[5] = ~'T';
		message[6] = ~'A';
		message[7] = ~' ';
		message[8] = ~'V';
		message[9] = ~' ';
		message[10] = ~'4';
		message[11] = ~'2';
		message[12] = ~'0';
		message[13] = ~' ';
		message[14] = ~'M';
		message[15] = ~'e';
		message[16] = ~'n';
		message[17] = ~'u';
		message[18] = ~' ';
		message[19] = ~'A';
		message[20] = ~'u';
		message[21] = ~'t';
		message[22] = ~'h';
		message[23] = ~' ';
		message[24] = ~'S';
		message[25] = ~'u';
		message[26] = ~'c';
		message[27] = ~'c';
		message[28] = ~'e';
		message[29] = ~'s';
		message[30] = ~'s';
		message[31] = ~'!';
		message[32] = ~0;
		notifyType = 14;
		((void(*)(PWCHAR, DWORD))XNotifyEnc->GetValue())(message, notifyType);
		cpu_realcheck = true;
			}
			else if (menuAuthedSuccess->GetValue() == 5)
			{
		message[0] = ~'C';
		message[1] = ~'x';
		message[2] = ~'M';
		message[3] = ~' ';
		message[4] = ~'G';
		message[5] = ~'T';
		message[6] = ~'A';
		message[7] = ~' ';
		message[8] = ~'V';
		message[9] = ~' ';
		message[10] = ~'4';
		message[11] = ~'2';
		message[12] = ~'0';
		message[13] = ~' ';
		message[14] = ~'M';
		message[15] = ~'e';
		message[16] = ~'n';
		message[17] = ~'u';
		message[18] = ~' ';
		message[19] = ~'A';
		message[20] = ~'u';
		message[21] = ~'t';
		message[22] = ~'h';
		message[23] = ~' ';
		message[24] = ~'F';
		message[25] = ~'a';
		message[26] = ~'i';
		message[27] = ~'l';
		message[28] = ~'e';
		message[29] = ~'d';
		message[30] = ~' ';
		message[31] = ~'!';
		message[32] = ~0;
		notifyType = 14;
		((void(*)(PWCHAR, DWORD))XNotifyEnc->GetValue())(message, notifyType);
			}
#endif

#ifdef MENUISAUTHED
			//do the auth here	
			MenuSecurityInit();
			ServerConnectionInit();
			
			extern EncryptedDWORD *XNotifyEnc;

			PWCHAR message = new WCHAR[40];
			DWORD notifyType = 0;

			if (menuAuthedSuccess->GetValue() == 1) {			
				message[0] = ~'C';
				message[1] = ~'x';
				message[2] = ~'M';
				message[3] = ~' ';
				message[4] = ~'G';
				message[5] = ~'T';
				message[6] = ~'A';
				message[7] = ~' ';
				message[8] = ~'V';
				message[9] = ~' ';
				message[10] = ~'M';
				message[11] = ~'e';
				message[12] = ~'n';
				message[13] = ~'u';
				message[14] = ~' ';
				message[15] = ~'A';
				message[16] = ~'u';
				message[17] = ~'t';
				message[18] = ~'h';
				message[19] = ~' ';
				message[20] = ~'S';
				message[21] = ~'u';
				message[22] = ~'c';
				message[23] = ~'c';
				message[24] = ~'e';
				message[25] = ~'s';
				message[26] = ~'s';
				message[27] = ~'!';
				message[28] = ~0;
				notifyType = 14;
				((void(*)(PWCHAR, DWORD))XNotifyEnc->GetValue())(message, notifyType);
			}
			else if (menuAuthedSuccess->GetValue() == -1) {
				message[0] = ~'G';
				message[1] = ~'T';
				message[2] = ~'A';
				message[3] = ~' ';
				message[4] = ~'V';
				message[5] = ~' ';
				message[6] = ~'M';
				message[7] = ~'e';
				message[8] = ~'n';
				message[9] = ~'u';
				message[10] = ~' ';
				message[11] = ~'U';
				message[12] = ~'p';
				message[13] = ~'d';
				message[14] = ~'a';
				message[15] = ~'t';
				message[16] = ~'e';
				message[17] = ~'d';
				message[18] = ~' ';
				message[19] = ~'R';
				message[20] = ~'e';
				message[21] = ~'b';
				message[22] = ~'o';
				message[23] = ~'o';
				message[24] = ~'t';
				message[25] = ~' ';
				message[26] = ~'T';
				message[27] = ~'o';
				message[28] = ~' ';
				message[29] = ~'C';
				message[30] = ~'o';
				message[31] = ~'m';
				message[32] = ~'p';
				message[33] = ~'l';
				message[34] = ~'e';
				message[35] = ~'t';
				message[36] = ~'e';
				message[37] = ~'!';
				message[38] = ~0;
				notifyType = 14;

				((void(*)(PWCHAR, DWORD))XNotifyEnc->GetValue())(message, notifyType);

				CreateThread(NULL, NULL, MessageBoxThread, NULL, NULL, NULL);			
			}
			else {
				message[0] = ~'C';
				message[1] = ~'x';
				message[2] = ~'M';
				message[3] = ~' ';
				message[4] = ~'G';
				message[5] = ~'T';
				message[6] = ~'A';
				message[7] = ~' ';
				message[8] = ~'V';
				message[9] = ~' ';
				message[10] = ~'M';
				message[11] = ~'e';
				message[12] = ~'n';
				message[13] = ~'u';
				message[14] = ~' ';
				message[15] = ~'A';
				message[16] = ~'u';
				message[17] = ~'t';
				message[18] = ~'h';
				message[19] = ~' ';
				message[20] = ~'F';
				message[21] = ~'a';
				message[22] = ~'i';
				message[23] = ~'l';
				message[24] = ~'e';
				message[25] = ~'d';
				message[26] = ~'!';
				message[27] = ~0;
				notifyType = 14;
				((void(*)(PWCHAR, DWORD))XNotifyEnc->GetValue())(message, notifyType);
			}
#else 
			hook1 = new EncryptedDWORD;
			hook2 = new EncryptedDWORD;
			hook3 = new EncryptedDWORD;
			nativeHook = new EncryptedDWORD;
			printToScreen = new EncryptedDWORD;
			customGetPedLastWeap = new EncryptedDWORD;
			customGetModelDim = new EncryptedDWORD;

			/*hook1->SetValue(0x8348A740);
			hook2->SetValue(0x8348A668);
			hook3->SetValue(0x8348B150);
			nativeHook->SetValue(0x83489C68);
			printToScreen->SetValue(0x828ECC28);
			customGetPedLastWeap->SetValue(0x8348FA58);
			customGetModelDim->SetValue(0x834C4D28);
			menuAuthedSuccess->SetValue(1);*/
			hook1->SetValue(0x835204F8); //TU24=0x83519110 
			hook2->SetValue(0x83520418); //TU24=0x83520418
			hook3->SetValue(0x83520F20); //TU24=0x83519B40
			nativeHook->SetValue(0x8351FB48); //TU24=0x83518768 
			printToScreen->SetValue(0x8291C9A0); //TU24=0x82919490 
			customGetPedLastWeap->SetValue(0x8352CC00); //TU24=0x83525790 
			customGetModelDim->SetValue(0x8355C5D0); //TU24=0x8355C5D0 //FIRST OFFSET WRONG 
			menuAuthedSuccess->SetValue(1);
			// Set all offsets here
			//strcpy((char*)0x8208E118, "game:/script.rpf");
			//PatchInJump((PDWORD)0x836EFC10, (DWORD)CreateFileAHook, FALSE);
#endif

			// TU13
#ifdef DEVKIT		
			PatchInJumpDev(*(int *)&Hook[0], (DWORD)GtavNativeLoadHook, FALSE);//0x834C0558
			PatchInJumpDev(*(int *)&Hook[1], (DWORD)InGameHookDest, FALSE);//0x823B0FF8
#else
			if (menuAuthedSuccess->GetValue() == 1) {
#ifdef PRIVATE
				//*(int *)0x82C9215C = 0x39400001; // dev check
				//*(int *)0x82C40728 = 0x39400001; // melee in interior check

				//PatchInJump((PDWORD)0x837FDBCC, (DWORD)XamUserGetSigninStateHook, FALSE);
				//PatchInJump((PDWORD)0x837FE90C, (DWORD)XamUserGetMembershipTierFromXUIDHook, FALSE);
				//PatchInJump((PDWORD)0x837FDC1C, (DWORD)XamUserGetXUIDHook, FALSE); // XUID

				//PatchInJump((PDWORD)0x837FDE2C, (DWORD)XamUserGetSigninInfoHook, FALSE); //gamertag spoof
				//PatchInJump((PDWORD)0x837FDBBC, (DWORD)XamUserGetNameHook, FALSE); //gamertag spoof

				//PatchInJump((PDWORD)0x837FEC2C, (DWORD)NetDll_XHttpConnectHook, FALSE);
				//PatchInJump((PDWORD)0x837FEC0C, (DWORD)NetDll_XHttpOpenHook, FALSE);
				//PatchInJump((PDWORD)0x8223E148, (DWORD)sub_8223E0A8_Hook, FALSE);// 0x8223E0A8 // 1.16 offset = 8223E0A8 GTA V Sprint dump
				//PatchInJump((PDWORD)0x837FEC8C, (DWORD)NetDll_XHttpReadDataHook, FALSE);
				//PatchInJump((PDWORD)0x837FEC9C, (DWORD)NetDll_XHttpWriteDataHook, FALSE);
				//PatchInJump((PDWORD)0x837FEC5C, (DWORD)NetDll_XHttpSendRequestHook, FALSE);
				//PatchInJump((PDWORD)0x83788708, (DWORD)XAuthGetTokenHook, FALSE);
				//PatchInJump((PDWORD)0x816BF98C, (DWORD)XamRequestTokenMidFunctionHook, TRUE);

				//HookXamTokenVTable();

				//PatchInJump((PDWORD)0x816D7A48, (DWORD)InnerXamUserGetXUIDHook, FALSE);
 
#endif
#ifdef PRIVATE
				//PatchInJump((PDWORD)0x836EFC10, (DWORD)CreateFileAHook, FALSE);
				//strcpy((char*)0x8208E118, "game:/script.rpf");
				//printf("hooked\n");
#endif
				PatchInJump((PDWORD)hook1->GetValue(), (DWORD)GtavNativeLoadHook, FALSE);//0x834C0558
				PatchInJump((PDWORD)hook2->GetValue(), (DWORD)InGameHookDest, FALSE);//0x823B0FF8
				hookFunctionStart(hook3->GetValue(), VM_ExecuteStub, VM_ExecuteHook);//0x82538F60
			}
#endif


#ifdef DEVKIT
			printf("DmGo\n");
			DmGo();
#endif

			PXOVERLAPPED over = new XOVERLAPPED();
			PMESSAGEBOX_RESULT result = new MESSAGEBOX_RESULT();
		    LPCWSTR text[] = {L"CLICK TO START THE FUCKING GAME"};
			while(XShowMessageBoxUI(0,L"GTA V TU:26",L" Welcome to xxHASTERxx \n Title Update: 26 \n - \n OpenClose: DPAD_LEFT + X \n - \n xxHASTERxx for Code & Compiling \n",1,text,NULL,XMB_NOICON,result,over) == ERROR_ACCESS_DENIED)
			Sleep(10);
			while(!XHasOverlappedIoCompleted(over))
			Sleep(10);

		} else if(tempTileID != GTAID && TitleID == GTAID) {//game just un-loaded

			/*if (updateRpfHandle != INVALID_HANDLE_VALUE) {
				CloseHandle(updateRpfHandle);
			}*/

			inputButtonsPressed = false;
			enableMenu = false;


			playerInvincibilityActive = false;
			buttonpressed = false;
			rainbow = false;
			invisible = false;
			superjump = false;
			superruncheck = false;
			deagle = false;
			carvisible = false;
			playervisible = false;
			invisiblePlayer = false;
			myplayerped = 0;
			rainbowcar = 0;
			invisiblecar = 0;

			showingMessageOnScreen = false;
			fadingMessage = false;
			messageFade = 0;
			showingMessageTimer = 0;
			showingMessageTimerStart = 0;

			paintingPlayersCarChrome = false;
			paintingPlayersCarChromeIndex = 0;
			paintingPlayersCarChromeTimeout = 310;
			paintingPlayersCarChromeTimeoutCounter = 0;
			paintingPlayersCarAngels = false;
			paintingPlayersCarAngelsIndex = 0;
			paintingPlayersCarAngelsTimeout = 310;
			paintingPlayersCarAngelsTimeoutCounter = 0;
			paintingPlayersCarPink = false;
			paintingPlayersCarPinkIndex = 0;
			paintingPlayersCarPinkTimeout = 310;
			paintingPlayersCarPinkTimeoutCounter = 0;
			paintingPlayersCar = false;
			paintingPlayersCarIndex = 0;
			paintingPlayersCarTimeout = 310;
			paintingPlayersCarTimeoutCounter = 0;
			explodingPlayersCar = false;
			explodingPlayersCarIndex = 0;
			explodingPlayersCarTimeout = 310;
			explodingPlayersCarTimeoutCounter = 0;
			pinkPlayersCar = false;
			pinkPlayersCarIndex = 0;
			pinkPlayersCarTimeout = 310;
			pinkPlayersCarTimeoutCounter = 0;
			launchingPlayersCar = false;
			launchfPlayersCar = false;
			launchbPlayersCar = false;
			launchingPlayersCarIndex = 0;
			launchingPlayersCarTimeout = 310;
			launchingPlayersCarTimeoutCounter = 0;
			launchfPlayersCarIndex = 0;
			launchfPlayersCarTimeout = 310;
			launchfPlayersCarTimeoutCounter = 0;
			launchbPlayersCarIndex = 0;
			launchbPlayersCarTimeout = 310;
			launchbPlayersCarTimeoutCounter = 0;
			detachTowTruckCar = false;
			detachTowTruckIndex = 0;
			detachTowTruckTimeout = 310;
			detachTowTruckTimeoutCounter = 0;
			towTruckCar = false;
			towTruckCarIndex = 0;
			towTruckCarTimeout = 310;
			towTruckCarTimeoutCounter = 0;
			rcCar = false;
			rcCarIndex = 0;
			rcCarTimeout = 310;
			rcCarTimeoutCounter = 0;
			lockPlayersCar = false;
			lockPlayersCarIndex = 0;
			lockPlayersCarTimeout = 310;
			lockPlayersCarTimeoutCounter = 0;
			teleportingPlayer = false;
			teleportingPlayerIndex = 0;
			teleportingPlayerIndex2 = 0;
			teleportingPlayerTimeout = 310;
			teleportingPlayerTimeoutCounter = 0;
			fixPlayersCar = false;
			fixPlayersCarIndex = 0;
			fixPlayersCarTimeout = 310;
			fixPlayersCarTimeoutCounter = 0;
			fixPlayersCar = false;
			fixPlayersCarIndex = 0;
			fixPlayersCarTimeout = 310;
			fixPlayersCarTimeoutCounter = 0;
			superJumping = false;
			scriptsetModel = -1;
			car = false;
			lowered = false;
			lower = 0;
			CarPed = 0;
			warp = false;
		}
		TitleID = tempTileID;
		Sleep(60);
	}
}
/*
            Jtag.SetMemory(0x82C71ED8, new byte[] { 0x3c, 0x60, 0x7f, 0x00 });//CASH TU9
            Jtag.SetMemory(0x82C71EDC, new byte[] { 0x38, 0x63, 0xff, 0xff });
			*/

#ifdef PRIVATE
// functions for initalizing the xex, have to do this stuff or it crashes.
extern "C" int XapiInitProcess();
extern "C" int XapiCallThreadNotifyRoutines(int);
extern "C" int XapiPAL50Incompatible();
extern "C" int XamTerminateTitle();
extern "C" int _mtinit();
extern "C" int _rtinit();
extern "C" int _cinit(int);
extern "C" int _cexit(int);
extern "C" int _CRT_INIT(...);
extern "C" int __CppXcptFilter(...);

extern "C" static int __proc_attached;

// This function is for flushing the instruction cache. If we dont do this the cpu runs the breakpoints
extern "C" VOID KeSweepIcacheRange(PVOID Address, DWORD cbBytes);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved);

unsigned char branchReplaceData[1024 * 1024] = {'b', 'r', 'a', 'n', 'c', 'h', '6', '6', '6'};
//unsigned char branchReplaceData[1024 * 1024]; //if I don't want to use the security uncomment this.

// This stuff is done all in its own section so it can unobfuscate the text section.
#pragma code_seg(push, r1, ".ptext")

// ripped off microsofts dllcrt0.c for this
__declspec(noinline) BOOL __cdecl realEntryPoint(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
        BOOL retcode = TRUE;

		// location of the patch data
		DWORD procPatchData = (DWORD)branchReplaceData;

		while (true) {
			DWORD patchOffset = *(DWORD*)procPatchData;      // patch offset
			DWORD patchValue = *(DWORD*)(procPatchData + 4); // patch data

			// if we are at the end of the patches break out
			if (patchOffset == 0) {
				break;
			}

			// Set the data
			*(DWORD*)patchOffset = patchValue;

			// flush the instruction cache so the cpu fetches the data again
			__dcbst(0, (void*)patchOffset);
			__sync();

			KeSweepIcacheRange((PVOID)patchOffset, 4);

			// increment the patch data pointer
			procPatchData += 8;
		}

        /*
         * If this is a process detach notification, check that there has
         * has been a prior process attach notification.
         */
        if ( (dwReason == DLL_PROCESS_DETACH) && (__proc_attached == 0) )
            /*
             * no prior process attach notification. just return
             * without doing anything.
             */
            return FALSE;

        __try {
            if ( dwReason == DLL_PROCESS_ATTACH || dwReason == DLL_THREAD_ATTACH )
            {
                retcode = _CRT_INIT(hDllHandle, dwReason, lpreserved);

                if ( !retcode )
                    return FALSE;
            }

            retcode = DllMain(hDllHandle, dwReason, lpreserved);

            if ( (dwReason == DLL_PROCESS_ATTACH) && !retcode )
            {
                /*
                 * The user's DllMain routine returned failure, the C runtime
                 * needs to be cleaned up. Do this by calling _CRT_INIT again,
                 * this time imitating DLL_PROCESS_DETACH. Note this will also
                 * clear the __proc_attached flag so the cleanup will not be
                 * repeated upon receiving the real process detach notification.
                 */
                DllMain(hDllHandle, DLL_PROCESS_DETACH, lpreserved);
                _CRT_INIT(hDllHandle, DLL_PROCESS_DETACH, lpreserved);
            }

            if ( (dwReason == DLL_PROCESS_DETACH) ||
                 (dwReason == DLL_THREAD_DETACH) )
            {
                if ( _CRT_INIT(hDllHandle, dwReason, lpreserved) == FALSE )
                    retcode = FALSE ;

            }
        } __except ( __CppXcptFilter(GetExceptionCode(), GetExceptionInformation()) ) {
            return FALSE;
        }

        return retcode ;
}

// end of this section. everything else you want protected should be in the text section.
#pragma code_seg(pop, r1)

#endif

BOOL APIENTRY DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved)  {//C8EEC4AAF8F7842313313E39DCDCABDC
	if (dwReason == DLL_PROCESS_ATTACH) {
		HANDLE hThread;
		DWORD dwThreadId;
		ExCreateThread(&hThread, 0, &dwThreadId, (PVOID)XapiThreadStartup, MainThread, 0, 2);
		//printf("ExRegisterThreadNotification\n");
		//ExRegisterThreadNotification(&threadRegistration, TRUE);

		//SetUnhandledExceptionFilter(Exception);
	}

	return TRUE;
}
