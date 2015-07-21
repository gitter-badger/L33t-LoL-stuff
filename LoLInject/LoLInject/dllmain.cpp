// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Unit {
	char unknown[24];//from 0x0 to 0x17
	int Team; //0x18
	int isChamp;
	char unknown2[68];
	Vector3 position;

};

void easyMain() {
	Unit* Player;
	DWORD Entry = (DWORD)GetModuleHandleA(NULL);
	Player = *(Unit**)(Entry + 0x11DC950);
	wchar_t buffer[255] = {};
	swprintf_s(buffer, L"%f", Player);
	MessageBox(NULL, (LPCWSTR)(buffer), (LPCWSTR)"Detroit", 0);
	delete Player;
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


//Big thanks to BDKPlayer for the first offsets :3

