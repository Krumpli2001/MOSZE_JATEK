#pragma once

#include <conio.h>
#include <Windows.h>


inline void KursorReset()
{
	COORD ccoord;
	ccoord.X = 0;
	ccoord.Y = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ccoord);
}

inline void pause()
{
	int p = _getch();
}