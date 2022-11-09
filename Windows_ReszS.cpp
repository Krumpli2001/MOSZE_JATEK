#include "Windows_Resz.hpp"

//jatekmenet konstruktora
	//(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya,
	//bool van_e_gyujteni, int collX, int collY, int mennyitad)

void run()
{
	jatekmenet j(4, 5, 3, false, 0, 0, 0, nullptr, false, 0, 0, 0);
	j.beolvas(j, "Text.txt");
	j.kiir(j, 'M');
}















