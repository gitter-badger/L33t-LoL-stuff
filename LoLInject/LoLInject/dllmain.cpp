// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"

struct Vector3 {
	float x;
	float y;
	float z;
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
	DWORD VTABLE; //0x0000 
	char unknown1[16];
	int team; //0x0014				//100 == blue;200 == red;300 == neutral
	int IsChamp; //0x0018                      // Jungle 3073, Champion 5121
	char unknown2[4];
	char PlayerName[16]; //0x0020 
	int ObjectType; //0x0030		//12 == LOCAL PLAYER
	char unknown3[40];
	float XPos; //0x005C 
	float YPos; //0x0060 
	float ZPos; //0x0064 
	char unknown4[68];
	int IsDead; //0x00AC			//642 == ALIVE;658 == DEAD
	char unknown5[72];
	DWORD NetworkId; //0x00F8		//USED FOR CAST SPELL
	char unknown6[84];
	float CurrentHealth; //0x0150 
	char unknown7[12];
	float MaxHealth; //0x0160 
	char unknown8[120];
	BYTE* isVisible;//0x1DC			//if(*(IsVisible + 0x84) == 0x01){ VISIBLE };
	char unknown23[44];
	float CurrentMana; //0x020C 
	char unknown9[12];
	float MaxMana; //0x021C 
	char unknown10[1446];
	char ChampionName[16];//0x7C6	//Player with Udyr: "Udyr"; Dragon:"SRU_Dragon";Baron:"SRU_Baron"...
	char unknown11[370];
	float ArmorPen; //0x0948 
	float MagicPen; //0x094C 
	char unknown12[48];
	float BonusAttackDamage; //0x0980 
	char unknown13[4];
	float AbilityPower; //0x0988 
	char unknown14[92];
	float BaseAttackDamage; //0x09E8 
	char unknown15[32];
	float ArmorResistance; //0x0A0C 
	float MagicResistance; //0x0A10 
	char unknown16[20];
	float MovementSpeed; //0x0A28 
	float NormalAttackRange; //0x0A2C 
	char unknown17[1476];
	float Gold; //0x0FF4 
	char unknown18[4772];
	char unknown19[1300];
	SpellLevelInformation* QSpell; //0x27B0 
	SpellLevelInformation* WSpell; //0x27B4 
	SpellLevelInformation* ESpell; //0x27B8 
	SpellLevelInformation* RSpell; //0x27BC 
	SpellLevelInformation* DSpell; //0x27C0 
	SpellLevelInformation* FSpell; //0x27C4 
	char unknown20[3188];
	int ChampionLevel; //0x343C 
	char unknown21[68];
	char DSummonerSpellName[16]; //0x3484 
	char unknown22[8];
	char FSummonerSpellName[16]; //0x349C
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

void easyMain() {


	DWORD Entry = (DWORD)GetModuleHandleA(NULL);
	ObjManager = (ObjectManager*)(Entry + 0x2E59440);
	Player = *(cObject**)(Entry + 0x11DC950);
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
		return Player->ArmorPen;
	case 2:
		return Player->ArmorResistance;
	case 3:
		return Player->BaseAttackDamage;
	case 4:
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


//Big thanks to http://www.unknowncheats.me/forum/other-games/80055-league-legends-7.html

