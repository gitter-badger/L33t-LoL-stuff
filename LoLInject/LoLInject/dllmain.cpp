// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"

struct Vector3 {
	float x;
	float y;
	float z;
};

class Camera
{
public:
	Vector3 position;
};

class SpellData
{
public:
	BYTE unknown1[1196];
	float Mana[5];
};

class SpellLevelInformation
{
public:
	/*0x0*/		BYTE unknown1[16];
	/*0x10*/	int Level;
	/*0x14*/	float TimeCDOver;
	BYTE unknown2[188];
	SpellData* pSpellData;
};


class cObject
{
public:
public:
	DWORD VTABLE; //0x0000 
	char unknown1[16];
	int team; //0x0014				//100 == blue;200 == red;300 == neutral
	int IsChamp; //0x0018 
	char unknown2[4];
	char PlayerName[16]; //0x0020 
	int ObjectType; //0x0030		//12 == LOCAL PLAYER
	char unknown3[40];
	Vector3 position;
	char unknown4[68];
	int IsDead; //0x00AC			//642 == ALIVE;658 == DEAD
	char unknown5[72];
	DWORD NetworkId; //0x00F8		//USED FOR CAST SPELL
	char unknown6[88];
	float CurrentHealth; //0x0154 
	char unknown7[12];
	float MaxHealth; //0x0164 
	char unknown8[120];
	BYTE* isVisible;//0x1E0			//if([IsVisible + 0x84] == 0x01){ VISIBLE };
	char unknown23[44];
	float CurrentMana; //0x0210 
	char unknown9[12];
	float MaxMana; //0x0220
	char unknown10[1490];

	char ChampionName[16];//0x7F6	//Player with Udyr: "Udyr"; Dragon:"SRU_Dragon";Baron:"SRU_Baron"...

	char unknown11[426];
	float BonusAttackDamage; //0x09B0
	char unknown13[4];
	float AbilityPower; //0x09B8
	char unknown14[92];
	float BaseAttackDamage; //0x0A18 
	char unknown15[32];
	float ArmorResistance; //0x0A3C 
	float MagicResistance; //0x0A40
	char unknown16[20];
	float MovementSpeed; //0x0A58 
	float NormalAttackRange; //0x0A5C
	char unknown17[1476];
	float Gold; //0x1024
	char unknown18[4812];
	float QManaCost;//0x22F4
	char unknown19[12];
	float WManaCost;//0x2304
	char unknown26[12];
	float EManaCost;//0x2314
	char unknown24[12];
	float RManaCost;//0x2324
	char unknown25[1208];
	SpellLevelInformation* QSpell; //0x27E0 
	SpellLevelInformation* WSpell; //0x27E4 
	SpellLevelInformation* ESpell; //0x27E8 
	SpellLevelInformation* RSpell; //0x27EC 
	SpellLevelInformation* DSpell; //0x27F0 
	SpellLevelInformation* FSpell; //0x27F4 
	char unknown20[3196];
	int ChampionLevel; //0x3474 
	char unknown21[68];
	char DSummonerSpellName[16]; //0x34BC 
	char unknown22[8];
	char FSummonerSpellName[16]; //0x34D4

};



class ObjectManager
{
public:
	/*0x14*/	cObject** ObjectArray;
	/*0x4*/	int MaxObjects;
	/*0x8*/	int NumberObjectsUsed;
	/*0xC*/	int HighestIndexObjectUsed;
};

cObject* Player;
ObjectManager* ObjManager;
Camera* CameraObj;
void easyMain() {


	DWORD Entry = (DWORD)GetModuleHandleA(NULL);
	ObjManager = (ObjectManager*)(Entry + 0x2D9A3A0);
	float* TimeSinceStartup = (float*)(Entry + 0x2DAF928);
	Player = *(cObject**)(Entry + 0x11161F8);
	CameraObj = (Camera*)(Entry + 0x10BFC90);
	AllocConsole();
	FILE* pCout;
	freopen_s(&pCout, "conout$", "w", stdout); //returns 0
	while(true){
		std::cout << "PlayerInfo: " << Player->AbilityPower << ". Camerapos = " << CameraObj->position.x << " " << CameraObj->position.y << " " << CameraObj->position.z << std::endl;
		Sleep(20);
	}
	fclose(pCout);
	FreeConsole();
	//delete Player; whooooops
}

extern float  __cdecl GetPlayerStat(int stat) {
	if (Player == NULL)
		return -1.f;
	switch (stat)
	{
	case 0:
		return Player->AbilityPower;
	case 1:
		return Player->ArmorResistance;
	case 2:
		return Player->BaseAttackDamage;
	case 3:
		return Player->BaseAttackDamage + Player->BonusAttackDamage;
	default:
		return -1;
	}
}
extern bool __cdecl IsDead() {
	if (Player == NULL)
		return true;
	if (Player->IsDead == 642)
		return false;
	return true;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	
	
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		easyMain();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


//Big thanks to http://www.unknowncheats.me/forum/other-games/80055-league-legends-8.html

