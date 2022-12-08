#pragma once

#include <conio.h>
#include <Windows.h>

#define CLEAR "cls"
#define STORYL "../Story"
#define PALYAKL "../palyak"

//kursor visszaallitasa
inline void KursorReset()
{
	COORD ccoord;
	ccoord.X = 0;
	ccoord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ccoord);
}

//pause
inline void spause()
{
	int p = _getch();
}