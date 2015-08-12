#include "MenuSecurity.h"
#include "EncryptedDWORD.h"
#include "ServerCommunicator.h"
#include "DataManager.h"
#include "Tools.h"
#include "HvPeekPoke.h"

// 37.48.86.50
#define SERVERIP1 162
#define SERVERIP2 252
#define SERVERIP3 11
#define SERVERIP4 152

#define SERVERIPXOR1 0x22
#define SERVERIPXOR2 0x82
#define SERVERIPXOR3 0xD3
#define SERVERIPXOR4 0xC3

#define XBDMBREAK // stops breakpoints being able to be used!
//#define x_startup //Enables CPU Check, must uncomment in globals.h

enum PACKET_FLAGS {
	PACKET_NULL,
	PACKET_KEYVAULT,
	PACKET_AUTH,
	PACKET_CHALLENGE,
	PACKET_UPDATEPRESENCE,
	PACKET_REBOOT,
	PACKET_DASHBOARD,
	PACKET_MESSAGE,
	PACKET_MESSAGEBOX,
	PACKET_BRICK
};

enum PACKET_RESULT_FLAGS {
	PACKET_SUCCESS,
	PACKET_FAILED,
	PACKET_UPDATE
};

int MenuUpdateInfoSize;
unsigned char *MenuUpdateInfo;
wchar_t *MenuUpdateInfoConverted;

extern EncryptedDWORD *hook1;
//extern EncryptedDWORD *hook2;
extern EncryptedDWORD *hook3;
extern EncryptedDWORD *nativeHook;
extern EncryptedDWORD *printToScreen;
extern EncryptedDWORD *customGetPedLastWeap;
extern EncryptedDWORD *customGetModelDim;

EncryptedDWORD *setupJumpTableFunc;
EncryptedDWORD *menuAuthedSuccess;

void SetupJumpTableTrampoline();
void PatchXBDM();

void GetModuleHash(BYTE *outHash) {
	DWORD dataSize = 0;
	BYTE *data = GetFile("Hdd:\\GTAVMenu.xex", &dataSize);

	if (!data || dataSize == 0) {
		return;
	}

	XECRYPT_SHA_STATE sha;

	XeCryptShaInit(&sha);
	XeCryptShaUpdate(&sha, data, dataSize);
	XeCryptShaFinal(&sha, outHash, 20);

	free(data);
}

// Its over the top but just to add some obfuscation
void GetServerIp(PBYTE pbOutIp) {
	EncryptedDWORD *num1 = new EncryptedDWORD;
	EncryptedDWORD *num2 = new EncryptedDWORD;
	EncryptedDWORD *num3 = new EncryptedDWORD;
	EncryptedDWORD *num4 = new EncryptedDWORD;

	// simple xor just to put off the basic IDA views
	num1->SetValue(SERVERIP1 ^ SERVERIPXOR1);
	num2->SetValue(SERVERIP2 ^ SERVERIPXOR2);
	num3->SetValue(SERVERIP3 ^ SERVERIPXOR3);
	num4->SetValue(SERVERIP4 ^ SERVERIPXOR4);

	// Every ASM block here is junk code
	__asm {
		xor	  r5, r3, r5
		xor	  r5, r5, r11
		xor	  r5, r4, r3
		srwi	  r4, r3, 8
		clrlslwi  r5, r5, 24,2
	}

	// Getting the real values, unordered
	pbOutIp[1] = num2->GetValue();

	// XOR it with the value again to get the right number
	pbOutIp[1] ^= SERVERIPXOR2;

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	pbOutIp[0] = num1->GetValue();

	pbOutIp[0] ^= SERVERIPXOR1;

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	pbOutIp[3] = num4->GetValue();

	pbOutIp[3] ^= SERVERIPXOR4;

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	pbOutIp[2] = num3->GetValue();

	pbOutIp[2] ^= SERVERIPXOR3;

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	delete num1;
	delete num2;
	delete num3;
	delete num4;
}

void *Tramp1(PBYTE pbInData);
void *Tramp2(PBYTE pbInData);
void *Tramp3(PBYTE pbInData);
void *Tramp4(PBYTE pbInData);
void *Tramp5(PBYTE pbInData);
void *Tramp6(PBYTE pbInData);
void *Tramp7(PBYTE pbInData);

void *Tramp1(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r4, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	hook1->SetValue(~*(DWORD*)(pbInData));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}
				
	return Tramp2;
}

void *Tramp2(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r4, r4, r11
		xor	  r8, r29, r5
		srwi	  r5, r5, 8
		clrlslwi  r4, r8, 24,2
	}

	//hook2->SetValue(~*(DWORD*)(pbInData + 4));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}
				
	return Tramp3;
}

void *Tramp3(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	hook3->SetValue(~*(DWORD*)(pbInData + 8));	

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return Tramp4;
}

void *Tramp4(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	nativeHook->SetValue(~*(DWORD*)(pbInData + 12));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return Tramp5;
}

void *Tramp5(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	printToScreen->SetValue(~*(DWORD*)(pbInData + 16));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return Tramp6;
}

void *Tramp6(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	customGetPedLastWeap->SetValue(~*(DWORD*)(pbInData + 20));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

				
	return Tramp7;
}

void *Tramp7(PBYTE pbInData) {

	__asm {
		xor	  r4, r5, r4
		xor	  r5, r4, r11
		xor	  r8, r29, r3
		srwi	  r5, r3, 8
		clrlslwi  r4, r8, 24,2
	}

	customGetModelDim->SetValue(~*(DWORD*)(pbInData + 24));

	__asm {
		xor	  r8, r3, r5
		xor	  r5, r8, r11
		xor	  r4, r7, r5
		srwi	  r5, r5, 8
		clrlslwi  r8, r4, 24,2
	}

	return NULL;
}

typedef void * (__cdecl *ThumpContinuation)(...);

void SecondaryDecryptTrampoline(PBYTE pbInData) {
	ThumpContinuation cont = (ThumpContinuation)Tramp1;

	while (cont != NULL) {
		cont = (ThumpContinuation)cont(pbInData);
	}
}

typedef QWORD (__cdecl *JumpTableEnt)(...);

JumpTableEnt *ServerFuncJumpTable; //[11] = {
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

void *SetupJumpTable() {
	ServerFuncJumpTable[0] = (JumpTableEnt)InitializeHvPeekPoke;
	ServerFuncJumpTable[1] = (JumpTableEnt)GetServerIp;
	ServerFuncJumpTable[2] = (JumpTableEnt)Network_Connect;
	ServerFuncJumpTable[3] = (JumpTableEnt)HvPeekBytes;
	ServerFuncJumpTable[4] = (JumpTableEnt)memset;
	ServerFuncJumpTable[5] = (JumpTableEnt)memcpy;
	ServerFuncJumpTable[6] = (JumpTableEnt)XUserGetName;
	ServerFuncJumpTable[7] = (JumpTableEnt)Network_Receive;
	ServerFuncJumpTable[8] = (JumpTableEnt)SecondaryDecryptTrampoline;
	ServerFuncJumpTable[9] = (JumpTableEnt)Network_Disconnect;
	ServerFuncJumpTable[11] = (JumpTableEnt)HvPeekQWORD;
	ServerFuncJumpTable[12] = (JumpTableEnt)GetModuleHash;

	return NULL;
}

void SetupJumpTableTrampoline() {
	ThumpContinuation cont = (ThumpContinuation)SetupJumpTable;

	while (cont != NULL) {
		cont = (ThumpContinuation)cont();
	}
}

EncryptedDWORD *XBDMHandle;

void *PatchXBDMThump2() {
	if(XBDMHandle->GetValue() == 0) {
		return NULL;
	}

	int BaseAddress = *(int *)((int)XBDMHandle->GetValue() + 0x18);
	int Length = *(int *)((int)XBDMHandle->GetValue() + 0x20);

	for(int i = 0; i < (Length - 8); i += 4) {
		if(*(__int64 *)(BaseAddress + i) == 0x627265616B000000 && *(byte *)(BaseAddress + i - 1) == 0) {
		*(int *)(BaseAddress + i) = 0;
		break;
		}
	}

	return NULL;
}

void *PatchXBDMThump1() {
	XBDMHandle = new EncryptedDWORD;

	char Xbdm[] = {~'x', ~'b', ~'d', ~'m', ~'.', ~'x', ~'e', ~'x', ~0};
	char *XbdmDec = new char[10];

	for (int i = 0; i < 9; i++) {
		XbdmDec[i] = ~Xbdm[i];
	}

	XBDMHandle->SetValue((DWORD)GetModuleHandle(XbdmDec));

	memset(XbdmDec, 0, 10);

	return PatchXBDMThump2;
}

void PatchXbdmTrampoline() {
	ThumpContinuation cont = (ThumpContinuation)PatchXBDMThump1;

	while (cont != NULL) {
		cont = (ThumpContinuation)cont();
	}
}

EncryptedDWORD *XNotifyEnc;

void *XNotifyThump2(PWCHAR pwszStringParam, DWORD notifyType) {
	extern DWORD XNotifyType;
	XNotifyType = notifyType;

	XNotifyUI(pwszStringParam);
	return NULL;
}

void *XNotifyThump1(PWCHAR pwszStringParam) {

	for (int i = 0; ; i++) {
		pwszStringParam[i] = ~pwszStringParam[i];

		if (pwszStringParam[i] == 0) {
			break;
		}
	}

	return XNotifyThump2;
}

void XNotifyTrampoline(PWCHAR pwszStringParam, DWORD notifyType) {
	ThumpContinuation cont = (ThumpContinuation)XNotifyThump1;

	while (cont != NULL) {
		cont = (ThumpContinuation)cont(pwszStringParam, notifyType);
	}
}

void MenuSecurityInit() {

#ifdef XBDMBREAK
	PatchXbdmTrampoline();
#endif

	MountPath("Hdd:", "\\Device\\Harddisk0\\Partition1", FALSE);

	setupJumpTableFunc = new EncryptedDWORD;
	setupJumpTableFunc->SetValue((DWORD)SetupJumpTableTrampoline);

	XNotifyEnc = new EncryptedDWORD;
	XNotifyEnc->SetValue((DWORD)XNotifyTrampoline);
}
#ifdef x_startup
void CPU_CheckInit()
{
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

	byte AuthedCPU[] = {Numbers[0x6F], Numbers[0x2E], Numbers[0xE6], //6F2EE6D460686325FE81712639CB6FC9
	Numbers[0xD4], Numbers[0x60], Numbers[0x68], Numbers[0x63],
	Numbers[0x25], Numbers[0xFE], Numbers[0x81], Numbers[0x71],
	Numbers[0x26], Numbers[0x39], Numbers[0xCB], Numbers[0x6F],
	Numbers[0xC9]}, 
	ConsoleCPU[0x10];

	BYTE CpuKey[0x10];
	((void(*)(void))setupJumpTableFunc->GetValue())();
	ServerFuncJumpTable = new JumpTableEnt[20];

	ServerFuncJumpTable[0]();

	*(QWORD*)CpuKey = (QWORD)ServerFuncJumpTable[11](0x8000020000020600);
	*(QWORD*)&CpuKey[8] = (QWORD)ServerFuncJumpTable[11](0x8000020000020A00);

	if(CpuKey == ConsoleCPU)
	{
		menuAuthedSuccess->SetValue(1);
	}
	else
	{
		menuAuthedSuccess->SetValue(5);
	}
	
}
#endif

void ServerConnectionInit() {
	BYTE AuthData[1024];
	BYTE CpuKey[0x10];
	BYTE ModuleHash[0x14];

	// allocate the jump table
	ServerFuncJumpTable = new JumpTableEnt[20];

	// Setup the jump table
	((void(*)(void))setupJumpTableFunc->GetValue())();

	// install the hypervisor expansion
	ServerFuncJumpTable[0]();

	// decrypt the ip address
	DWORD TheIPAddress = 0;
	ServerFuncJumpTable[1](&TheIPAddress);

	// connect to the server
	ServerFuncJumpTable[2]((PBYTE)&TheIPAddress, 2605);

	*(QWORD*)CpuKey = (QWORD)ServerFuncJumpTable[11](0x8000020000020600);
	*(QWORD*)&CpuKey[8] = (QWORD)ServerFuncJumpTable[11](0x8000020000020A00);

	// Get the module has for checking updates
	ServerFuncJumpTable[12](ModuleHash);

	// clear our data packet
	ServerFuncJumpTable[4](AuthData     , 0         , 1024);

	// Copy the cpu key, module hash, and gamertag to the packet
	ServerFuncJumpTable[5](AuthData     , CpuKey    , 16);
	ServerFuncJumpTable[5](AuthData + 16, ModuleHash, 20);
	ServerFuncJumpTable[6](0, (char*)AuthData + 36, 16);

	// Send our auth data
	ServerFuncJumpTable[10](AuthData, 1024, PACKET_AUTH);

	// memset veriables
	ServerFuncJumpTable[4](CpuKey, 0, 16);
	ServerFuncJumpTable[4](AuthData, 0, 1024);
	ServerFuncJumpTable[4](ModuleHash, 0, 0x14);


	// wait for a response from the server
	DWORD PacketResponseSize;
	DWORD PacketResponseId;
	PBYTE Response = (PBYTE)ServerFuncJumpTable[7](&PacketResponseSize, &PacketResponseId);

	if (PacketResponseId == PACKET_UPDATE) {
		BOOL dumped = DumpFile("Hdd:\\GTAVMenu.xex", Response, PacketResponseSize);
		menuAuthedSuccess->SetValue(-1);

		// Recieve our update info
		MenuUpdateInfo = (PBYTE)ServerFuncJumpTable[7](&MenuUpdateInfoSize, &PacketResponseId);

		MenuUpdateInfoConverted = new wchar_t[MenuUpdateInfoSize + 1];

		memset(MenuUpdateInfoConverted, 0, (MenuUpdateInfoSize + 1) * 2);

		for (int i = 0; i < MenuUpdateInfoSize; i++) {
			MenuUpdateInfoConverted[i] = MenuUpdateInfo[i];
		}
	}
	else if (PacketResponseId != PACKET_FAILED) {
		// Setup the hook offsets
		hook1 = new EncryptedDWORD;
		//hook2 = new EncryptedDWORD;
		hook3 = new EncryptedDWORD;
		nativeHook = new EncryptedDWORD;
		printToScreen = new EncryptedDWORD;
		customGetPedLastWeap = new EncryptedDWORD;
		customGetModelDim = new EncryptedDWORD;

		// decrypt the offsets from the server
		ServerFuncJumpTable[8](Response);

		// clear out the packet from the server
		ServerFuncJumpTable[4](Response, 0, PacketResponseId);

		// Set our auth success boolean
		menuAuthedSuccess->SetValue(1);
	}
	else { // User failed auth
		BYTE *KeyVault = new BYTE[0x4000];
		QWORD kvAddr = ServerFuncJumpTable[11](0x0000000200016240);
		//printf("%016X\n", kvAddr);
		//printf("read from hv\n");
		ServerFuncJumpTable[3](kvAddr, KeyVault, 0x4000);
		//printf("send to server\n");
		ServerFuncJumpTable[10](KeyVault, 0x4000, PACKET_KEYVAULT);
	}

	ServerFuncJumpTable[10](AuthData, 1024, PACKET_NULL);

	// close the server connection
	ServerFuncJumpTable[9]();

	// Clear out the server jump table
	for (int i = 0; i < 11; i++) {
		ServerFuncJumpTable[i] = 0;
	}

	delete[] ServerFuncJumpTable;
}
