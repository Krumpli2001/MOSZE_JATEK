#include "futas.hpp"

//jatekmenet konstruktora
	//(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya,
	//bool van_e_gyujteni, int collX, int collY, int mennyitad)

//jatekmenet& kezdes()

int kezdes()
{
	std::cout << "1. Uj jatek\n2. Mentes folytatasa\n3. Kilepes\n \
				  Ird be a megfelelo szamot, vagy szoveget a folytatashoz\n";
	std::string inditas;
	std::getline(std::cin, inditas);
	if (isalpha(inditas[0]))
	{
		inditas[0] = tolower(inditas[0]);
	}
	if (inditas[0] == '3' or inditas[0] == 'k')
	{
		/*std::cout << "Beleptel\n";
		system("pause");*/
		return 0;
	}
	
	return 1;
}

//void run(jatekmenet* g)
//{
//	g->kiir( ,'0');
//	jatekmenet j(4, 5, 3, false, 0, 0, 0, nullptr, false, 0, 0, 0);
//}

void run(int fut)
{
	if (fut != 0)
	{
		jatekmenet j(4, 5, 3, false, 0, 0, 0, nullptr, false, 0, 0, 0);
		j.beolvas(j, "Text.txt");
		j.kiir(j, 'M');
	}
}















