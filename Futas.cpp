#include "futas.hpp"

//jatekmenet konstruktora
	//(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya,
	//bool van_e_gyujteni, int collX, int collY, int mennyitad)

//jatekmenet& kezdes()

int kezdes()
{
	std::cout << "1. Uj jatek\n2. Mentes folytatasa\n3. Costum palya\n4. Kilepes\nIrd be a megfelelo szamot, vagy szoveget a folytatashoz\n";
	std::string inditas;
	std::getline(std::cin, inditas);
	bool helyes = false;
	while (!helyes)
	{
		if (isalpha(inditas[0]))
		{
			inditas[0] = tolower(inditas[0]);
		}
		if (inditas[0] == '4' or inditas[0] == 'k')
		{
			/*std::cout << "Beleptel\n";
			system("pause");*/
			helyes = true;
			return 0;
		}
		if (inditas[0] == '1' or inditas[0] == 'u')
		{
			helyes = true;
			return 1;
		}
		if (inditas[0] == '2' or inditas[0] == 'm')
		{
			helyes = true;
			return 2;
		}
		if (inditas[0] == '3' or inditas[0] == 'c')
		{
			helyes = true;
			return 3;
		}
		else
		{
			std::cout << "Hibas gombot utottel le\n";
			std::getline(std::cin, inditas);
		}
	}
}

void story_be(std::string CH)
{
	system(CLEAR);
	std::string egysor;

	std::ifstream f(CH);
	int karakterek = 0;
	int sorok = 0;


	if (f.is_open())
	{
		//palya meretenek meghatarozasa
		while (std::getline(f, egysor)) {
			int karakterek = egysor.length();
			for (int i = 0; i < karakterek; i++) {
				std::cout << egysor[i];
				Sleep(5);
			}
			std::cout << std::endl;
		}
		f.close();
	}
	else
	{
		std::cerr << "\nNem sikerult a beolvasas\n";
	}
	std::cout << std::endl<<"\nNyomj entert a folytatashoz\n";
	system("pause");
	system(CLEAR);
}

void run(int fut)
{
	if (fut != 0)
	{
		story_be("Story/CH1.txt");
		jatekmenet j(4, 5, 3, false, 0, 0, 0, nullptr, false, 0, 0, 0);
		j.beolvas(j, "Text.txt");
		j.kiir(j, 'M');
	}
}















