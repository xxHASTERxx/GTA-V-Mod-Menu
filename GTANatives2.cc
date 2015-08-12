#include "GTAVNatives.h"

// idk how many arguments can be passed, sureley we wont need 100 arguments....
DWORD VMPassed[100];
DWORD VMReturned[5];
DWORD *VMArgs[3] = {
	VMReturned, // our return value
	0,//num of args
	VMPassed
};

vector<GTAVNative> *gtavNativesList;

void InitNativeHook() {
	gtavNativesList = new vector<GTAVNative>;
}

void GtavNativeLoadHook(unsigned int r3, unsigned int r4) {

	GTAVNative TempNative;
	TempNative.hashValue = r3;
	TempNative.functionOffset = r4;
	gtavNativesList->push_back(TempNative);

	if(r3 < 2) { r3 += 2; }
	((VOID(*)(DWORD, DWORD, DWORD))0x83493540)(0x83D2C188, r3, r4); // TU17
}

DWORD FindNative(DWORD hashValue) {
	for (int i = 0; i < gtavNativesList->size(); i++) {
		if (gtavNativesList->operator[](i).hashValue == hashValue) {
			return gtavNativesList->operator[](i).functionOffset;
		}
	}

	return 0;
}

int CallNative(int nativeAddress, int argumentCount, ...) {
	GTAVNativeCall gtavCall;

	gtavCall.returnValue = new int[1];
	gtavCall.argumentCount = argumentCount;
	gtavCall.argumentData = new int[argumentCount];

	va_list pArgList;
	va_start(pArgList, argumentCount);

	for(int i = 0; i < argumentCount; i++) {
		gtavCall.argumentData[i] = va_arg(pArgList, int);
	}
	
	int returnValue = ((int(*)(void *))nativeAddress)(&gtavCall);

	delete[] gtavCall.argumentData;

	int ret = gtavCall.returnValue[0];

	delete[] gtavCall.returnValue;

	return ret;
}

DWORD SaveVMPassed[100];

void SaveStack()
{
	memcpy(&SaveVMPassed, &VMPassed, 100*4);
}

void ResetStack()
{
	memcpy(&VMPassed, &SaveVMPassed, 100*4);
}

void CarVisibleDamage(int carhandle, bool damage)
{
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = damage;

	int (__cdecl *set_vehicle_can_be_visibly_damaged)(void *) = (int (__cdecl *)(void *))FindNative(0xC5D94017);
	set_vehicle_can_be_visibly_damaged(VMArgs);
	ResetStack();
}

void set_entity_can_be_damaged(int carhandle, bool damage)
{
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = damage;
	((void(*)(void *))FindNative(0x60B6E744))(VMArgs);
	ResetStack();
}

bool is_ped_running(bool running)
{
	SaveStack();
	VMArgs[2][0] = running;
	((void(*)(void *))FindNative(0xE9A5578F))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void set_cinematic_button_active(bool active)
{
	SaveStack();
   	VMArgs[2][0] = active;
	((void(*)(void *))FindNative(0x3FBC5D00))(VMArgs);
	ResetStack();
}


void apply_force_to_entity(int vehicle, unsigned int unknown0, float x, float y, float z, float spinX, float spinY, float spinZ, unsigned int unknown4, unsigned int unknown5_1, unsigned int unknown6_1, unsigned int unknown7_1)
{
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = unknown0;
	VMArgs[2][2] = *(DWORD *)(&x);
	VMArgs[2][3] = *(DWORD *)(&y);
	VMArgs[2][4] = *(DWORD *)(&z);
	VMArgs[2][5] = *(DWORD *)(&spinX);
	VMArgs[2][6] = *(DWORD *)(&spinY);
	VMArgs[2][7] = *(DWORD *)(&spinZ);
	VMArgs[2][8] = unknown4;
	VMArgs[2][9] = unknown5_1;
	VMArgs[2][10] = unknown6_1;
	VMArgs[2][11] = unknown7_1;
	((void(*)(void *))FindNative(0xC1C0855A))(VMArgs);
	ResetStack();
}

void attach_entity_to_entity(int car0, int car1, int unk, float x0, float y0, float z0, float x1, float y1, float z1,
	int unk1, int unk2, int unk3, int unk4, int unk5, int unk6)
{//0x1802, 0x1702, 0x3A, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1
	SaveStack();
	VMArgs[2][0] = car0;
	VMArgs[2][1] = car1;
	VMArgs[2][2] = unk;
	VMArgs[2][3] = *(int *)&x0;
	VMArgs[2][4] = *(int *)&y0;
	VMArgs[2][5] = *(int *)&z0;
	VMArgs[2][6] = *(int *)&x1;
	VMArgs[2][7] = *(int *)&y1;
	VMArgs[2][8] = *(int *)&z1;
	VMArgs[2][9] = unk1;
	VMArgs[2][10] = unk2;
	VMArgs[2][11] = unk3;
	VMArgs[2][12] = unk4;
	VMArgs[2][13] = unk5;
	VMArgs[2][14] = unk5;
	((void(*)(void *))FindNative(0xEC024237))(VMArgs);
	ResetStack();
}

void detach_entity(int entity)
{
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = 0;
	VMArgs[2][2] = 0;
	((void(*)(void *))FindNative(0xC8EFCB41))(VMArgs);
	ResetStack();
}

bool is_entity_attached(int entity)
{
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0xEC1479D5))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void wait(int time)
{
	SaveStack();
	VMArgs[2][0] = time;
	((void(*)(void *))FindNative(0x7715C03B))(VMArgs);
	ResetStack();
}

bool is_entity_visible(int entity)
{
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0x120B4ED5))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void set_vehicle_doors_locked(int entity, int LockStatus)
{
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = LockStatus;
	((void(*)(void *))FindNative(0x4CDD35D0))(VMArgs);
	ResetStack();
}

void set_entity_collision(int entity, bool collision)
{
	SaveStack();
	VMArgs[2][0] = entity;
	VMArgs[2][1] = collision;
	VMArgs[2][2] = 0;
	((void(*)(void *))FindNative(0x139FD37D))(VMArgs);
	ResetStack();
}

bool request_script(char* script)
{
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0xE26B2666))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

bool does_script_exist(char* script)
{
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0xDEAB87AB))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

void terminate_all_scripts_with_this_name(char* script)
{
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0x9F861FD4))(VMArgs);
	ResetStack();
}

bool has_script_loaded(char* script)
{
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0x5D67F751))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

bool start_new_script(char* script, int arg)
{
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	VMArgs[2][1] = arg;
	((void(*)(void *))FindNative(0x3F166D0E))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

void set_script_as_no_longer_needed(char* script)
{
	SaveStack();
	VMArgs[2][0] = (DWORD)script;
	((void(*)(void *))FindNative(0x6FCB7795))(VMArgs);
	ResetStack();
}

int get_vehicle_max_number_of_passengers(int vehicle)
{
	SaveStack();
	VMArgs[2][0] = vehicle;
	((void(*)(void *))FindNative(0x0A2FC08C))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

bool is_vehicle_seat_free(int vehicle, int seat)
{
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = seat;
	((void(*)(void *))FindNative(0xDAF42B02))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) != 0);
}

void task_warp_ped_into_vehicle(int ped, int vehicle, int seat)
{
	SaveStack();
	VMArgs[2][0] = ped;
	VMArgs[2][1] = vehicle;
	VMArgs[2][2] = seat;
	((void(*)(void *))FindNative(0x65D4A35D))(VMArgs);
	ResetStack();
}

unsigned int GetPlayerHandle(int index) {
	SaveStack();
	VMArgs[2][0] = index;
	int (__cdecl *get_player_ped)(void *) = (int (__cdecl *)(void *))FindNative(0x6E31E993);
	get_player_ped(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

int PlayerId() {
	int (__cdecl *player_id)(void *) = (int (__cdecl *)(void *))FindNative(0x8AEA886C);

	player_id(VMArgs);

	return (int)(*VMArgs[0]);
}

void GiveWeaponDelayed(int playerid, int weapon, int ammo, int unk)
{
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = weapon;
	VMArgs[2][2] = ammo;
	VMArgs[2][3] = unk;

	((void(*)(void *))FindNative(0x5868D20D))(VMArgs); 
	ResetStack();
}

unsigned int PlayerPedId()
{
	int (__cdecl *player_ped_id)(void *) = (int (__cdecl *)(void *))FindNative(0xFA92E226);
	player_ped_id(VMArgs);
	return (int)(*VMArgs[0]);
}

int get_entity_model(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;
	((void(*)(void *))FindNative(0xDAFCB3EC))(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

void set_entity_as_no_longer_needed(int entity) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&entity;
	((void(*)(void *))FindNative(0x3F6B949F))(VMArgs);
	ResetStack();
}

void delete_vehicle(int vehicle) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&vehicle;
	((void(*)(void *))FindNative(0x9803AF60))(VMArgs);
	ResetStack();
}

void set_vehicle_as_no_longer_needed(int vehicle) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&vehicle;
	((void(*)(void *))FindNative(0x9B0E10BE))(VMArgs);
	ResetStack();
}

void clear_weather_type_persist()
{
	((void(*)())FindNative(0x6AB757D8))();
}

void PopCarTyre(int vehicle, int tyre)
{
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][0] = tyre;
	((void(*)(void *))FindNative(0x89D28068))(VMArgs);
	ResetStack();
}
void set_weather_type_now_persist(char* weather)
{
	SaveStack();
    VMArgs[2][0] = (int)weather;
	((void(*)(void *))FindNative(0xC869FE97))(VMArgs);
	ResetStack();
}

void delete_entity(int entity) {
	SaveStack();
	VMArgs[2][0] = (DWORD)&entity;
	((void(*)(void *))FindNative(0xFAA3D236))(VMArgs);
	ResetStack();
}

void ExplodeNetworkCar(int vehicle, boolean unknownTrue, boolean unknownFalse)
{
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = unknownTrue;
	VMArgs[2][2] = unknownFalse;

    ((void(*)(void *))FindNative(0x0E1B38AE))(VMArgs);
	ResetStack();
}

char *GetPlayerName(int index) {
	SaveStack();
	VMArgs[2][0] = index;

	int (__cdecl *get_player_name)(void *) = (int (__cdecl *)(void *))FindNative(0x406B4B20);

	get_player_name(VMArgs);
	ResetStack();
	return (char*)(*VMArgs[0]);
}

int NetworkIsPlayerActive(int index) {
	return 0;
}


bool get_current_ped_weapon(int PedHandle, int* OutWeaponHash, bool unk)
{
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = (int)OutWeaponHash;
	VMArgs[2][2] = unk;
	((void(*)(void *))FindNative(0xB8278882))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool has_entity_been_damaged_by_entity(int PedHandle, int pedhandle2, bool unk)
{
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = pedhandle2;
	VMArgs[2][2] = unk;
	((void(*)(void *))FindNative(0x07FC77E0))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool has_ped_been_damaged_by_weapon(int PedHandle, int weapon, bool unk)
{
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = weapon;
	VMArgs[2][2] = unk;
	((void(*)(void *))FindNative(0xCDFBBCC6))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}


void SetPlayerInvincible(int index, bool active) {
	SaveStack();
	VMArgs[2][0] = index;
	VMArgs[2][1] = active;

	int (__cdecl *set_player_invincible)(void *) = (int (__cdecl *)(void *))FindNative(0xDFB9A2A2);
	set_player_invincible(VMArgs);
	ResetStack();
}

bool DoesEntityExist(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;

	int (__cdecl *does_entity_exist)(void *) = (int (__cdecl *)(void *))FindNative(0x3AC90869);
	does_entity_exist(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void FixCar(int carhandle) {
	SaveStack();
	VMArgs[2][0] = carhandle;

	int (__cdecl *set_vehicle_fixed)(void *) = (int (__cdecl *)(void *))FindNative(0x17469AA1);
	set_vehicle_fixed(VMArgs);
	ResetStack();
}

void set_number_plate(int Vehicle, char* Text) {
	SaveStack();
    VMArgs[2][0] = Vehicle;
	VMArgs[2][1] = (DWORD)Text;

	((void(__cdecl *)(void *))FindNative(0x400F9556))(VMArgs);
	ResetStack();
}

bool is_string_null_or_empty(char* string) {
	SaveStack();
	VMArgs[2][0] = (DWORD)string;

	((void(__cdecl *)(void *))FindNative(0x42E9F2CA))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

void display_onscreen_keyboard(int arg0, char* str0, char* str1, char* str2, char* str3, char* str4, int arg1) {
    SaveStack();
    VMArgs[2][0] = arg0;
    VMArgs[2][1] = (int)str0;
    VMArgs[2][2] = (int)str1;
    VMArgs[2][3] = (int)str2;
    VMArgs[2][4] = (int)str3;
    VMArgs[2][5] = (int)str4;
    VMArgs[2][6] = arg1;
    ((void(__cdecl *)(void *))FindNative(0xAD99F2CE))(VMArgs);
    ResetStack();
}

void unk_0x27A244D8(char* String) {
    SaveStack();
    VMArgs[2][0] = (int)String;
    ((void(__cdecl *)(void *))FindNative(0x27A244D8))(VMArgs);
    ResetStack();
}

void unk_0x38F82261(int Time, int unk) {
    SaveStack();
    VMArgs[2][0] = Time;
    VMArgs[2][1] = unk;
    ((void(__cdecl *)(void *))FindNative(0x38F82261))(VMArgs);
    ResetStack();
}

void unk_0xF42C43C7(char* String) {
    SaveStack();
    VMArgs[2][0] = (int)String;
    ((void(__cdecl *)(void *))FindNative(0xF42C43C7))(VMArgs);
    ResetStack();
}

bool is_system_ui_being_displayed() {
	((void(__cdecl *)(void *))FindNative(0xE495B6DA))(VMArgs);
	return VMArgs[0][0] != 0;
}

char* get_onscreen_keyboard_result() {
	((void(__cdecl *)(void *))FindNative(0x44828FB3))(VMArgs);
	return (char*)VMArgs[0][0];
}
bool is_ped_in_any_vehicle(int ped)
{
	SaveStack();
    VMArgs[2][0] = ped;
	VMArgs[2][1] = 0;
	
	((void(__cdecl *)(void *))FindNative(0x3AC90869))(VMArgs);
	ResetStack();
	return VMArgs[0][0] != 0;
}

bool IsEntityVehicle(int entity) {
	SaveStack();
	VMArgs[2][0] = entity;

	int (__cdecl *is_entity_a_vehicle)(void *) = (int (__cdecl *)(void *))FindNative(0xBE800B01);
	is_entity_a_vehicle(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void AddExplosion(float X, float Y, float Z, int ExplosionType, float radius, bool playsound, bool novisual, float camshake)
{
	SaveStack();
	VMArgs[2][0] = *(DWORD *)&(X);
	VMArgs[2][1] = *(DWORD *)&(Y);
	VMArgs[2][2] = *(DWORD *)&(Z);
	VMArgs[2][3] = ExplosionType;
	VMArgs[2][4] = *(DWORD *)&(radius);
	VMArgs[2][5] = playsound ? 1 : 0;
	VMArgs[2][6] = novisual ? 1 : 0;
	VMArgs[2][7] = *(DWORD *)&(camshake);
	((void(*)(void *))FindNative(0x10AF5258))(VMArgs);
	ResetStack();
}

bool network_has_control_of_entity(int entity)
{
	SaveStack();
    VMArgs[2][0] = entity;
    ((void(*)(void *))FindNative(0x005FD797))(VMArgs);
	ResetStack();
    return ((int)(*VMArgs[0]) != 0);
}

bool network_has_control_of_network_id(int id)
{
	SaveStack();
	VMArgs[2][0] = id;
    ((void(*)(void *))FindNative(0x92E77D21))(VMArgs);
	ResetStack();
    return ((int)(*VMArgs[0]) != 0);
}

void network_session_kick_player(int playerindex)
{
	SaveStack();
	VMArgs[2][0] = playerindex;
	((void(*)(void *))FindNative(0x1E20138A))(VMArgs);
	ResetStack();
}

bool network_does_network_id_exist(int id)
{
	SaveStack();
	VMArgs[2][0] = id;
    ((void(*)(void *))FindNative(0x1E2E3177))(VMArgs);
	ResetStack();
    return VMArgs[0][0] != 0;
}

bool network_request_control_of_entity(int entity)
{
	SaveStack();
    VMArgs[2][0] = entity;
    ((void(*)(void *))FindNative(0xA05FEBD7))(VMArgs);
	ResetStack();
    return VMArgs[0][0] != 0;
}

int network_request_control_of_network_id(int id)
{
	SaveStack();
	VMArgs[2][0] = id;
    ((void(*)(void *))FindNative(0x9262A60A))(VMArgs);
	ResetStack();
    return (int)VMArgs[0][0];
}

int network_get_network_id_from_entity(int entity)
{
	SaveStack();
	VMArgs[2][0] = entity;
    ((void(*)(void *))FindNative(0x9E35DAB6))(VMArgs);
	ResetStack();
    return (int)VMArgs[0][0];
}



void GetEntityCoords(int PedID, void* Out)
{
	SaveStack();
    VMArgs[2][0] = PedID;
    VMArgs[2][1] = 1;
    ((void(*)(void *))FindNative(0x1647F1CB))(VMArgs);
	ResetStack();
	 memcpy(Out, VMArgs[0], 0xC);
}

void set_entity_coords(int PedID, float X, float Y, float Z, int unk1, int unk2, int unk3, int unk4) {
	SaveStack();
	VMArgs[2][0] = PedID;
    VMArgs[2][1] = *(int *)&X;
	VMArgs[2][2] = *(int *)&Y;
	VMArgs[2][3] = *(int *)&Z;
	VMArgs[2][4] = unk1;
	VMArgs[2][5] = unk2;
	VMArgs[2][6] = unk3;
	VMArgs[2][7] = unk4;

    ((void(*)(void *))FindNative(0xDF70B41B))(VMArgs);
	ResetStack();
}
//set_entity_coords( Entity, x, y, z, 0, 1, 0, 1)

void SetTextFont(int font) {
	SaveStack();
	VMArgs[2][0] = font;

	int (__cdecl *set_text_font)(void *) = (int (__cdecl *)(void *))FindNative(0x80BC530D);
	set_text_font(VMArgs);
	ResetStack();
}

void SetTextScale(float x, float y) {
	SaveStack();
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int (__cdecl *set_text_scale)(void *) = (int (__cdecl *)(void *))FindNative(0xB6E15B23);
	set_text_scale(VMArgs);
	ResetStack();
}

void SetTextColor(int a, int r, int g, int b) {
	SaveStack();
	VMArgs[2][0] = a;
	VMArgs[2][1] = r;
	VMArgs[2][2] = g;
	VMArgs[2][3] = b;

	int (__cdecl *set_text_color)(void *) = (int (__cdecl *)(void *))FindNative(0xE54DD2C8);
	set_text_color(VMArgs);
	ResetStack();
}

void SetTextWrap(float x, float y) {
	SaveStack();
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int (__cdecl *set_text_wrap)(void *) = (int (__cdecl *)(void *))FindNative(0x6F60AB54);
	set_text_wrap(VMArgs);
	ResetStack();
}

void SetTextCenter(int value) {
	SaveStack();
	VMArgs[2][0] = value;

	int (__cdecl *set_text_center)(void *) = (int (__cdecl *)(void *))FindNative(0xE26D39A1);
	set_text_center(VMArgs);
	ResetStack();
}

void unk_0x3E35563E(char *str) {
	SaveStack();
	VMArgs[2][0] = (DWORD)str;

	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))FindNative(0x3E35563E);
	unk(VMArgs);
	ResetStack();
}

// Suppose to be the original print but all it did was print ints
void unk_0x12929BDF(DWORD a, DWORD b) {
	SaveStack();
	VMArgs[2][0] = a;
	VMArgs[2][1] = b;

	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))FindNative(0x12929BDF);
	unk(VMArgs);
	ResetStack();
}

void unk_0x6F8350CE(float x, float y) {
	SaveStack();
	VMArgs[2][0] = *(DWORD*)(&x);
	VMArgs[2][1] = *(DWORD*)(&y);

	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))FindNative(0x6F8350CE);
	unk(VMArgs);
	ResetStack();
}

void set_ped_random_component_variation(int Ped, int Val) {
	SaveStack();
	VMArgs[2][0] = Ped;
	VMArgs[2][1] = Val;

	((void(*)(void*))FindNative(0x4111BA46))(VMArgs);
	ResetStack();
}

void set_ped_into_vehicle(int Ped, int Vehicle, int Seat) {
	SaveStack();
	VMArgs[2][0] = Ped;
	VMArgs[2][1] = Vehicle;
	VMArgs[2][2] = Seat;

	((void(*)(void*))FindNative(0x7500C79))(VMArgs);
	ResetStack();
}

void set_ped_component_variation(int Ped, int r4, int r5, int Shirt, int r7) {
	//ped, uint component, uint modelVariation, uint textureVariation)
	SaveStack();
	VMArgs[2][0] = Ped;
	VMArgs[2][1] = r4;
	VMArgs[2][2] = r5;
	VMArgs[2][3] = Shirt;
	VMArgs[2][4] = r7;

	((void(*)(void*))FindNative(0xD4F7B05C))(VMArgs);
	ResetStack();
}

int create_object(int ModelHash, float X, float Y, float Z, int Unk1, int Unk2, int Unk3)// returns the handle
{
	SaveStack();
	VMArgs[2][0] = ModelHash;
	VMArgs[2][1] = *(int *)&X;
	VMArgs[2][2] = *(int *)&Y;
	VMArgs[2][3] = *(int *)&Z;
	VMArgs[2][4] = Unk1;
	VMArgs[2][5] = Unk2;
	VMArgs[2][6] = Unk3;

	((void(*)(void*))FindNative(0x2F7AA05C))(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void PrintToScreen(char *str, float x, float y, int r, int g, int b, int a, float scaleX, float scaleY, int centerText) {
	SaveStack();
	VMArgs[2][0] = (int)str;

	SetTextFont(0);
	SetTextColor(r, g, b, a);
	SetTextScale(scaleX, scaleY);
	((void(*)(void))FindNative(0xC753412F))();  // Draws outline
	//SetTextWrap(0.0f, 1.0f);
	SetTextCenter(centerText);

	unk_0x3E35563E("STRING");
	//unk_0x12929BDF((DWORD)str, true);
	//int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))FindNative(0x0829A799);
	//unk(VMArgs);

	int (__cdecl *unk)(void *) = (int (__cdecl *)(void *))0x82AAA308;
	unk(str);

	unk_0x6F8350CE(x, y);
	ResetStack();
}


void PaintCar(int carhandle, int paint, int paint1) {
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = paint;
	VMArgs[2][2] = paint1;

	int (__cdecl *set_vehicle_colours)(void *) = (int (__cdecl *)(void *))FindNative(0x57F24253);
	set_vehicle_colours(VMArgs);
	ResetStack();
}


void PaintCarExtra(int carhandle, int paint, int paint1) {
	SaveStack();
	VMArgs[2][0] = carhandle;
	VMArgs[2][1] = paint;
	VMArgs[2][2] = paint1;

	int (__cdecl *set_vehicle_extra_colours)(void *) = (int (__cdecl *)(void *))FindNative(0x515DB2A0);
	set_vehicle_extra_colours(VMArgs);
	ResetStack();
}

int GetCarCharIsIn(int PedHandle, int PlayerID) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = PlayerID;

	int (__cdecl *get_vehicle_ped_is_in)(void *) = (int (__cdecl *)(void *))FindNative(0xAFE92319);
	get_vehicle_ped_is_in(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

int GetCarCharIsIn2(int PedHandle, int PlayerID) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	VMArgs[2][1] = PlayerID;

	int (__cdecl *get_vehicle_ped_is_using)(void *) = (int (__cdecl *)(void *))FindNative(0x6DE3AADA);
	get_vehicle_ped_is_using(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

int veh_to_net(int vehicle) {
	SaveStack();
	VMArgs[2][0] = vehicle;

	int (__cdecl *veh_to_net)(void *) = (int (__cdecl *)(void *))FindNative(0xF17634EB);
	veh_to_net(VMArgs);
	ResetStack();
	return (int)(*VMArgs[0]);
}

bool is_ped_getting_into_a_vehicle(int PedHandle) {
	SaveStack();
	VMArgs[2][0] = PedHandle;
	((void(*)(void *))FindNative(0x90E805AC))(VMArgs);
	ResetStack();
	return ((int)(*VMArgs[0]) >= 1);
}

bool HasModelLoaded(DWORD hash) {
	SaveStack();
	VMArgs[2][0] = hash;

	int (__cdecl *has_model_loaded)(void *) = (int (__cdecl *)(void *))FindNative(0x62BFDB37);
	has_model_loaded(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void RequestModel(int hash) {
	SaveStack();
	VMArgs[2][0] = hash;
	((void(__cdecl *)(void *))FindNative(0xFFF1B500))(VMArgs);
	ResetStack();
}

void set_entity_visible(int Entity, bool visable) {
	SaveStack();
	VMArgs[2][0] = Entity;
	VMArgs[2][1] = visable;
	((void(*)(void *))FindNative(0xD043E8E1))(VMArgs);
	ResetStack();
}

void set_player_wanted_level_now(int player, int level) {
	SaveStack();
	VMArgs[2][0] = player;
	VMArgs[2][1] = level;
	((void(*)(void *))FindNative(0xAF3AFD83))(VMArgs);
	ResetStack();
}

void set_vehicle_petrol_tank_health(int Vehicle, float Health) {
	SaveStack();
	VMArgs[2][0] = Vehicle;
	VMArgs[2][1] = *(int *)&Health;
	((void(*)(void *))FindNative(0x660A3692))(VMArgs);
	ResetStack();
}

void SetPlayerModel(int playerId, DWORD hash) {
	SaveStack();
	VMArgs[2][0] = playerId;
	VMArgs[2][1] = hash;

	int (__cdecl *set_player_model)(void *) = (int (__cdecl *)(void *))FindNative(0x774A4C54);
	set_player_model(VMArgs);
	ResetStack();
}

int give_achievement_to_player(int acheivement){
	SaveStack();
	VMArgs[2][0] = acheivement;

	int (__cdecl *give_achievement_to_player)(void *) = (int (__cdecl *)(void *))FindNative(0x822BC992);
	give_achievement_to_player(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void StartEntityFire(int playerid)
{
	SaveStack();
    VMArgs[2][0] = playerid;

	int (__cdecl *start_entity_fire)(void *) = (int (__cdecl *)(void *))FindNative(0x8928428E);
	start_entity_fire(VMArgs);
	ResetStack();
}

bool IsModelInCdImage(DWORD hash) {
	SaveStack();
	VMArgs[2][0] = hash;

	int (__cdecl *is_model_in_cdimage)(void *) = (int (__cdecl *)(void *))FindNative(0x1094782F);
	is_model_in_cdimage(VMArgs);
	ResetStack();
	return VMArgs[0][0];
}

void RemoveWeapons(int playerid) {
	SaveStack();
	VMArgs[2][0] = playerid;
	VMArgs[2][1] = 1;

	int (__cdecl *remove_all_ped_weapons)(void *) = (int (__cdecl *)(void *))FindNative(0xA44CE817);
	remove_all_ped_weapons(VMArgs);
	ResetStack();
}

void GiveCash(int Amount, int PedHandle) {
	SaveStack();
 VMArgs[2][0] = Amount;
 VMArgs[2][1] = ((int(*)(int))0x823721F8)(PedHandle);
 ((void(*)(void *))0x82D91540)(VMArgs);
 ResetStack();
}

void set_vehicle_dirt_level(int vehicle, float dirt)
{
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = *(int *)&dirt;

	int (__cdecl *set_vehicle_dirt_level)(void *) = (int (__cdecl *)(void *))FindNative(0x2B39128B);
	set_vehicle_dirt_level(VMArgs);
	ResetStack();
}

void set_engine_health(int vehicle, float health)
{
	SaveStack();
	VMArgs[2][0] = vehicle;
	VMArgs[2][1] = *(int *)&health;

	int (__cdecl *set_engine_health)(void *) = (int (__cdecl *)(void *))FindNative(0x1B760FB5);
	set_engine_health(VMArgs);
	ResetStack();
}

//CREATE_CAR(MODEL_ORACLE, x4, y4 + 10, z4, &Gang, true);
unsigned int CreateCar(int hash, float x, float y, float z, float h, int createhandle, bool unk) {//returns car id
	SaveStack();
	VMArgs[2][0] = hash;
	VMArgs[2][1] = *(int *)&x;
	VMArgs[2][2] = *(int *)&y;
	VMArgs[2][3] = *(int *)&z;
	VMArgs[2][4] = *(int *)&h;
	VMArgs[2][5] = createhandle;
	VMArgs[2][6] = unk;

	int (__cdecl *create_vehicle)(void *) = (int (__cdecl *)(void *))FindNative(0xDD75460A);
	create_vehicle(VMArgs);
	ResetStack();
	//int hash, float x, float y, float z, float unk, int unk2 = 1, int unk3 = 1
	return VMArgs[0][0];
}
