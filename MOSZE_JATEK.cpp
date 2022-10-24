// MOSZE_JATEK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Windows_Resz.hpp"

int main()
{	
	//jatekmenet konstruktora
	//(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya,
	//bool van_e_gyujteni, int collX, int collY, int mennyitad)

	jatekmenet j(4, 5, 3, false, 0, 0, 0, nullptr, false, 0, 0, 0);
	j.beolvas(j,"Text.txt");
	j.kiir(j, 'M');
	//j.fut(j);
}


