#include "futas.hpp"

//jatekmenet konstruktora
//jatekmenet(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya, int mennyi_coll)

//a jatek inditasa
int kezdes()
{
	std::cout << "1. Uj jatek\n2. Mentes folytatasa\n3. Costum palya\n4. Kilepes\nIrd be a megfelelo szamot, vagy szoveget a folytatashoz\n";
	std::string inditas;
	std::getline(std::cin, inditas);
	bool helyes = false;
	while (!helyes)
	{
		//ha stringkent irjuk akkor kisbetuve
		if (isalpha(inditas[0]))
		{
			inditas[0] = tolower(inditas[0]);
		}
		//Kilepes
		if (inditas[0] == '4' or inditas[0] == 'k')
		{
			helyes = true;
			return 4;
		}
		//Inditas eleerol
		if (inditas[0] == '1' or inditas[0] == 'u')
		{
			helyes = true;
			return 1;
		}
		//Mentes folytatasa
		if (inditas[0] == '2' or inditas[0] == 'm')
		{
			helyes = true;
			return 2;
		}
		//Costum palya
		if (inditas[0] == '3' or inditas[0] == 'c')
		{
			helyes = true;
			return 3;
		}
		//hiba
		else
		{
			std::cout << "Hibas gombot utottel le\n";
			std::getline(std::cin, inditas);
		}
	}
	return -1;
}

//nagyobb story reszletekne - van press enter a vegen
void story_be(std::string CH)
{
	//Kepernyo uritese
	system(CLEAR);
	std::string egysor;
	std::ifstream f(CH);
	int karakterek = 0;

	if (f.is_open())
	{
		using namespace std::chrono_literals;
		while (std::getline(f, egysor)) {
			//karakterenkenti kiiras
			int karakterek = egysor.length();
			for (int i = 0; i < karakterek; i++) {
				std::cout << egysor[i];
				//std::this_thread::sleep_for(5ms);
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
	spause();
	system(CLEAR);
}

//rovidebb kerdesekre van, 1-1 sor, "sorkovetes" - nincs press enter a vegen
void story_kerdesek(std::ifstream& f, int pos)
{
	std::string egysor;
	int karakterek = 0;

	if (f.is_open())
	{
		f.clear();
		f.seekg(0);
		using namespace std::chrono_literals;
		int hanyadik_sor = 0;
		while (std::getline(f, egysor)) {
			int karakterek = egysor.length();
			bool var = false;
			//sorok szamolasa
			if (egysor[0] == '@')
			{
				hanyadik_sor++;
			}
			//kiiras
			for (int i = 2; i < karakterek; i++) {
				// #-nel megall
				if (egysor[i] == '#' and hanyadik_sor == pos)
				{
					var = true;
				}
				//@ kiirja a sort
				if (!var and egysor[0] == '@' and hanyadik_sor == pos)
				{
					std::cout << egysor[i];
					std::this_thread::sleep_for(5ms);
				}
			}
			if (hanyadik_sor == pos)
			{
				pos++;
				std::cout << std::endl;
			}
			if (var)
			{
				break;
			}
		}
	}
	else
	{
		std::cerr << "\nNem sikerult a beolvasas\n";
	}
}

//max 3 coll
void palya_letrehoz(jatekmenet* j, int jancsiX, int jancsiY, int* ghp, bool van_e_boss, int bossX, int bossY, int seb, int* gsebzes, char** palya, int mennyi_coll, int coll1X, int coll1Y, int coll1M, int coll2X, int coll2Y, int coll2M, int coll3X, int coll3Y, int coll3M, std::string palya_neve, char boss_char)
{
	bool fin;
	int jancsihp = *ghp;
	//labirintus letrehozasa
	j = new jatekmenet(jancsiX, jancsiY, jancsihp, van_e_boss, bossX, bossY, seb, palya, mennyi_coll);
	//gyujtogetni valok letrehozasa, ha van (max 3)
	if (mennyi_coll >= 1)
	{
		j->gyujteni_be(coll1X, coll1Y, coll1M, 0);
		if (mennyi_coll >= 2)
		{
			j->gyujteni_be(coll2X, coll2Y, coll2M, 1);
			if (mennyi_coll == 3)
			{
				j->gyujteni_be(coll3X, coll3Y, coll3M, 2);
			}
		}
	}
	//palya beolvasasa
	j->beolvas(*j, palya_neve);
	//kiiras
	fin = j->kiir(*j, boss_char);
	//elet, CP frissitese
	if (!fin)
	{
		delete j;
		j = nullptr;
		exit(0);
	}
	//player elet kiirasa
	int gelet = j->getJElet();
	*ghp = gelet;
	//sebzes kiirasa
	if (gsebzes)
	{
	int sebzes = j->getBSebzes();
	*gsebzes = sebzes;
	}
	//labirintus torlese
	delete j;
	j = nullptr;
}

void run(int fut)
{
	if (fut != 4)
	{
		int gelet = 3;
		int gCP = 0;
		int sebzes = 0;
		bool helyesbe = false;
		bool germemutatas = false;
		jatekmenet* j = nullptr;


		if (gCP == 0)
		{
			story_be("Story/CH1.txt");

			//kerdes
			std::ifstream f("Story/CH1_KERDES1.txt");
			story_kerdesek(f, 1);
			char elsovetel;
			char masodikvetel;
			while (!helyesbe)
			{
				std::cin >> elsovetel;
				std::cin >> masodikvetel;
				if (elsovetel == '1' or elsovetel == '2' or elsovetel == '3' or elsovetel == '4')
				{
					if (masodikvetel == '1' or masodikvetel == '2' or masodikvetel == '3' or masodikvetel == '4')
					{
						if (elsovetel != masodikvetel)
						{
							helyesbe = true;
						}
						else
						{
							story_kerdesek(f, 15);
						}
					}
					else
					{
						story_kerdesek(f, 16);
					}
				}
				else
				{
					story_kerdesek(f, 16);
				}
			}

			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 2, 1, 5, 1, 2, 5, 2, 0, 0, 0, "Text.txt", 'M');

			//kerdesre valasz
			story_kerdesek(f, 7);
			if (elsovetel == '1' or masodikvetel == '1')
			{
				story_kerdesek(f, 9);
			}
			else if (elsovetel == '3' or masodikvetel == '3')
			{
				story_kerdesek(f, 10);
			}
			else if (elsovetel == '4' or masodikvetel == '4')
			{
				story_kerdesek(f, 11);
			}
			spause();

			//kerdesre valasz
			story_kerdesek(f, 12);
			if (elsovetel == '2' or masodikvetel == '2')
			{
				story_kerdesek(f, 13);
				spause();
			}
			else
			{
				//felteteles labirintus
				story_kerdesek(f, 14);
				spause();
				palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			}
			f.close();
			gCP = 1;
		}

		if (gCP == 1)
		{

			story_be("Story/CH2_1.txt");

			std::ifstream f("Story/CH2_KERDES1.txt");
			story_kerdesek(f, 1);
			std::string kardszin;
			bool helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> kardszin;
				kardszin[0] = tolower(kardszin[0]);
				if (kardszin[0] == 'f' or kardszin[0] == 'k' or kardszin[0] == 'l' or kardszin[0] == 'z')
				{
					helyesbe = true;
				}
				if (!helyesbe) {
					story_kerdesek(f, 41);
				}
			}

			story_be("Story/CH2_2.txt");

			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');

			story_kerdesek(f, 6);

			char ajtobe;
			helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> ajtobe;
				if ((ajtobe == '1') or (ajtobe == '2') or (ajtobe == '3'))
				{
					helyesbe = true;
					if (ajtobe == '3')
					{
						story_kerdesek(f, 11);
					}
				}
				else
				{
					story_kerdesek(f, 12);
				}
			}
			if (ajtobe != '3')
			{
				story_kerdesek(f, 13);
			}
			story_kerdesek(f, 14);
			std::string ermemutatas;
			std::cin >> ermemutatas;
			ermemutatas[0] = tolower(ermemutatas[0]);
			if (ermemutatas[0] == 'i')
			{
				story_kerdesek(f, 19);
				germemutatas = true;
			}
			if (ajtobe == '3')
			{
				story_kerdesek(f, 21);
			}
			else
			{
				story_kerdesek(f, 22);
				std::string indok;
				std::cin >> indok;
				story_kerdesek(f, 23);
			}
			story_kerdesek(f, 24);

			char mitcsinalsz;
			helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> mitcsinalsz;
				if (mitcsinalsz == '1')
				{
					story_kerdesek(f, 30);
					helyesbe = true;
				}
				else if (mitcsinalsz == '2')
				{
					story_kerdesek(f, 31);
				}
				else if (mitcsinalsz == '3')
				{
					story_kerdesek(f, 32);
				}
				else if (mitcsinalsz == '4')
				{
					story_kerdesek(f, 33);
				}
				else
				{
					story_kerdesek(f, 34);
				}
			}

			story_kerdesek(f, 35);
			if (ermemutatas[0] == 'i')
			{
				story_kerdesek(f, 38);
			}

			helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> mitcsinalsz;
				if (mitcsinalsz == '1')
				{
					story_kerdesek(f, 30);
					helyesbe = true;
				}
				else if (mitcsinalsz == '2')
				{
					story_kerdesek(f, 39);
				}
				else if ((mitcsinalsz == '3') and (ermemutatas[0] == 'i'))
				{
					story_kerdesek(f, 40);
					helyesbe = true;
				}
				else
				{
					story_kerdesek(f, 34);
				}
			}
			spause();
			f.close();
			gCP = 2;
		}

		if (gCP == 2)
		{

			story_be("Story/CH3.txt");
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			gCP = 3;
		}

		if (gCP == 3)
		{

			story_be("Story/CH4.txt");
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			gCP = 4;
		}

		if (gCP == 4)
		{

			story_be("Story/CH5.txt");
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			gCP = 5;
		}

		if (gCP == 5)
		{

			story_be("Story/CH6.txt");

			while (gCP == 5)
			{
				std::ifstream f("Story/CH6_KERDES1.txt");
				story_kerdesek(f, 1);
				bool helyesbe = false;
				bool ded = false;
				while (!helyesbe)
				{
					std::string maradsz;
					std::cin >> maradsz;
					if (isalpha(maradsz[0]))
					{
						maradsz[0] = tolower(maradsz[0]);
						if (maradsz[0] == 'i' or maradsz[0] == 'n')
						{
							helyesbe = true;
							if (maradsz[0] == 'i')
							{
								ded = true;
							}
							else
							{
								gCP = 6;
							}
						}
					}
					else
					{
						story_kerdesek(f, 2);
					}
				}
				if (ded)
				{
					story_kerdesek(f, 3);
					spause();
					gCP = 5;
				}
				f.close();
			}
		}

		if (gCP == 6)
		{

			story_be("Story/CH7.txt");
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			std::ifstream f("Story/CH7_KERDES1.txt");
			story_kerdesek(f, 1);

			bool tovabb = false;
			while (!tovabb)
			{
				char el;
				std::cin >> el;
				if (el == '1')
				{
					story_kerdesek(f, 6);
					char valasztas;
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							story_kerdesek(f, 7);
							spause();
							tovabb = true;
						}
						else
						{
							story_kerdesek(f, 8);
							story_kerdesek(f, 3);
						}
					}
				}

				else if (el == '2')
				{
					char valasztas;
					story_kerdesek(f, 9);
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							story_kerdesek(f, 11);
							spause();
							tovabb = true;
						}
						else
						{
							story_kerdesek(f, 8);
							story_kerdesek(f, 3);

						}
					}
				}

				else if (el == '3')
				{
					char valasztas;
					story_kerdesek(f, 12);
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							story_kerdesek(f, 13);
							spause();
							tovabb = true;
						}
						else
						{
							story_kerdesek(f, 8);
							story_kerdesek(f, 3);
						}
					}
				}

				else
				{
					std::cout << "Hibas bemenet!";
					spause();
				}
			}
			f.close();
			gCP = 7;
		}

		if (gCP == 7)
		{
			std::ifstream f("Story/CH7_KERDES2.txt");
			story_kerdesek(f, 1);
			spause();

			while (gCP == 7)
			{
				int eredeti_hp = gelet;
				palya_letrehoz(j, 4, 5, &gelet, false, 2, 5, 5, &sebzes, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');

				story_kerdesek(f, 3);

				char mit;
				std::cin >> mit;

				if (mit == '1')
				{
					story_kerdesek(f, 7);
					spause();
					gCP = 8;
				}

				else if (mit == '2')
				{
					story_kerdesek(f, 8);
					spause();
					gCP = 8;
				}

				else if (mit == '3')
				{
					story_kerdesek(f, 9);
					gelet = gelet - sebzes;
					if (gelet < 0)
					{
						story_kerdesek(f, 10);
						spause();
						gCP = 7;
						gelet = eredeti_hp;
					}
					else
					{
						std::cout << sebzes << " eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
						spause();
					}
				}
				else
				{
					story_kerdesek(f, 11);
					spause();
				}
			}
			f.close();
		}

		if (gCP == 8)
		{
			story_be("Story/CH8.txt");
			palya_letrehoz(j, 4, 5, &gelet, true, 2, 5, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'G');

			std::ifstream f("Story/CH8_KERDES1.txt");
			story_kerdesek(f, 1);
			spause();

			palya_letrehoz(j, 4, 5, &gelet, true, 2, 5, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'D');

			story_kerdesek(f, 2);
			spause();

			f.close();
			gCP = 9;
		}

		if (gCP == 9)
		{
			std::ifstream f("Story/CH9_KERDES1.txt");
			story_kerdesek(f, 1);
			spause();
			story_kerdesek(f, 2);
			
			bool tovabb = false;
			while (!tovabb)
			{
				int eredeti_elet = gelet;
				std::string mit;
				std::cin >> mit;
				if (isalpha(mit[0]))
				{
					mit[0] = tolower(mit[0]);
					if (mit[0] == 'g')
					{
						story_kerdesek(f, 5);
						spause();
						gelet += 10;
						tovabb = true;
					}
					if (mit[0] == 'd')
					{
						story_kerdesek(f, 6);
						gelet -= 2;
						if (gelet < 0)
						{
							story_kerdesek(f, 7);
							spause();
							gCP = 7;
							gelet = eredeti_elet;
						}
						else
						{
							std::cout << "2 eletet vesztettel, mostmar csak " << gelet-2 << " eleted van\n";
							spause();
						}
					}
				}
				else
				{
					story_kerdesek(f, 8);
				}
			}
			f.close();
			gCP = 10;
		}

		if (gCP == 10)
		{
			std::ifstream f("Story/CH10_KERDES1.txt");
			story_kerdesek(f, 1);
			f.close();
			spause();
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');

			gCP = 11;
		}

		if (gCP == 11)
		{
			std::ifstream f("Story/CH11_KERDES1.txt");
			story_kerdesek(f, 1);
			spause();
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');

			story_kerdesek(f, 3);
			spause();
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');

			f.close();
			gCP = 12;
		}

		if (gCP == 12)
		{
			story_be("Story/CH12.txt");
			palya_letrehoz(j, 4, 5, &gelet, true, 2, 5, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", ' ');
			std::ifstream f("Story/CH12_KERDES1.txt");
			story_kerdesek(f, 1);
			spause();

			int sarkany_hp = 3;
			int eredeti_hp = gelet;

			while (sarkany_hp > 0)
			{
				palya_letrehoz(j, 4, 5, &gelet, true, 2, 5, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", ' ');

				if (sarkany_hp == 3)
				{
					story_kerdesek(f, 4);

					char mit;
					std::cin >> mit;

					if (mit == '1')
					{
						story_kerdesek(f, 9);
						sarkany_hp -= 1;
						spause();
					}

					else if (mit == '2')
					{
						story_kerdesek(f, 10);
						gelet -= 2;
						spause();
						if (gelet < 0)
						{
							story_kerdesek(f, 11);
							spause();
							gCP = 12;
						}
						else
						{
							std::cout << "2 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}

					else if (mit == '3')
					{
						story_kerdesek(f, 12);
						gelet -= 5;
						spause();
						if (gelet < 0)
						{
							story_kerdesek(f, 11);
							spause();
							gCP = 12;
						}
						else
						{
							std::cout << "5 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}

					else if (mit == '4')
					{
						story_kerdesek(f, 13);
						gelet -= 10;
						if (gelet < 0)
						{
							story_kerdesek(f, 11);
							spause();
							gCP = 12;
						}
						else
						{
							std::cout << "10 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}
					else
					{
						story_kerdesek(f, 14);
						spause();
					}
				}

				else if (sarkany_hp == 2)
				{
					story_kerdesek(f, 15);
					if (germemutatas)
					{
						story_kerdesek(f, 18);
					}

					char mit;
					std::cin >> mit;

					if (mit == '1')
					{
						story_kerdesek(f, 19);
						sarkany_hp -= 1;
						spause();
					}

					else if (mit == '2')
					{
						story_kerdesek(f, 20);
						gelet -= 7;
						spause();
						if (gelet < 0)
						{
							story_kerdesek(f, 11);
							spause();
							gCP = 12;
						}
						else
						{
							std::cout << "7 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}

					else if (mit == '3' and germemutatas)
					{
						story_kerdesek(f, 21);
						sarkany_hp -= 1;
						spause();
					}

					else
					{
						story_kerdesek(f, 14);
						spause();
					}
				}

				else if (sarkany_hp == 1)
				{

					story_kerdesek(f, 22);

					char mit;
					std::cin >> mit;

					if (mit == '1')
					{
						story_kerdesek(f, 27);
						gelet -= 5;
						spause();
						if (gelet < 0)
						{
							story_kerdesek(f, 11);
							spause();
							gCP = 12;
						}
						else
						{
							std::cout << "5 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}

					else if (mit == '2')
					{
						story_kerdesek(f, 28);
						sarkany_hp -= 1;
						spause();
					}

					else if (mit == '3')
					{
						story_kerdesek(f, 29);
						gelet -= 12;
						spause();
						if (gelet < 0)
						{
							story_kerdesek(f, 11);
							spause();
							gCP = 12;
						}
						else
						{
							std::cout << "12 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}

					else if (mit == '4')
					{
						story_kerdesek(f, 30);
						gelet -= 10;
						if (gelet < 0)
						{
							story_kerdesek(f, 11);
							spause();
							gCP = 12;
						}
						else
						{
							std::cout << "10 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}
					else
					{
						story_kerdesek(f, 14);
						spause();
					}
				}
			}
			f.close();
			story_be("Story/CH13.txt");
		}
	}
}