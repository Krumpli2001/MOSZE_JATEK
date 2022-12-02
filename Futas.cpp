#include "futas.hpp"

//jatekmenet konstruktora
//jatekmenet(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya, int mennyi_coll)


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
		//char skip;
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
void story_kerdesek(std::string CH, int pos)
{
	std::string egysor;

	std::ifstream f(CH);
	int karakterek = 0;

	if (f.is_open())
	{
		//char skip;
		using namespace std::chrono_literals;
		int hanyadik_sor = 0;
		while (std::getline(f, egysor)) {
			//karakterenkenti kiiras
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
				}
				//std::this_thread::sleep_for(5ms);
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
		f.close();
	}
	else
	{
		std::cerr << "\nNem sikerult a beolvasas\n";
	}
}

void coutszoveg(std::string sz)
{
	//karakterenkenti kiiras
	using namespace std::chrono_literals;
	int karakterek = sz.length();
	for (int i = 0; i < karakterek; i++) {
		std::cout << sz[i];
		//std::this_thread::sleep_for(5ms);
	}
}

//max 3 coll
void palya_letrehoz(jatekmenet* j, int jancsiX, int jancsiY, int* ghp, bool van_e_boss, int bossX, int bossY, int seb, int* gsebzes, char** palya, int mennyi_coll, int coll1X, int coll1Y, int coll1M, int coll2X, int coll2Y, int coll2M, int coll3X, int coll3Y, int coll3M, std::string palya_neve, char boss_char)
{
	bool fin;
	int jancsihp = *ghp;
	//labirintus letrehozasa
	j = new jatekmenet(4, 5, jancsihp, false, 0, 0, 0, nullptr, 2);
	//gyujtogetni valok letrehozasa, ha van
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
		bool fin;
		jatekmenet* j = nullptr;


		if (gCP == 0)
		{

			//CP 0
			story_be("Story/CH1.txt");

			//kerdes
			story_kerdesek("Story/CH1_KERDES1.txt", 1);
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
							story_kerdesek("Story/CH1_KERDES1.txt", 15);
						}
					}
					else
					{
						story_kerdesek("Story/CH1_KERDES1.txt", 16);
					}
				}
				else
				{
					story_kerdesek("Story/CH1_KERDES1.txt", 16);
				}
			}

			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 2, 1, 5, 1, 2, 5, 2, 0, 0, 0, "Text.txt", 'M');

			//kerdesre valasz
			story_kerdesek("Story/CH1_KERDES1.txt", 7);
			if (elsovetel == '1' or masodikvetel == '1')
			{
				story_kerdesek("Story/CH1_KERDES1.txt", 9);
			}
			else if (elsovetel == '3' or masodikvetel == '3')
			{
				story_kerdesek("Story/CH1_KERDES1.txt", 10);
			}
			else if (elsovetel == '4' or masodikvetel == '4')
			{
				story_kerdesek("Story/CH1_KERDES1.txt", 11);
			}
			spause();

			//kerdesre valasz
			story_kerdesek("Story/CH1_KERDES1.txt", 12);
			if (elsovetel == '2' or masodikvetel == '2')
			{
				story_kerdesek("Story/CH1_KERDES1.txt", 13);
				spause();
			}
			else
			{
				//felteteles labirintus
				story_kerdesek("Story/CH1_KERDES1.txt", 14);
				spause();
				palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			}
			gCP = 1;
		}

		if (gCP == 1)
		{

			story_be("Story/CH2_1.txt");

			story_kerdesek("Story/CH2_KERDES1.txt", 1);
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
					coutszoveg("\nKovacs: Te fiam, nem latod a kozeteket?\n");
				}
			}

			story_be("Story/CH2_2.txt");

			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');


			story_kerdesek("Story/CH2_KERDES1.txt", 6);

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
						story_kerdesek("Story/CH2_KERDES1.txt", 11);
					}
				}
				else
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 12);
				}
			}
			if (ajtobe != '3')
			{
				story_kerdesek("Story/CH2_KERDES1.txt", 13);
			}
			story_kerdesek("Story/CH2_KERDES1.txt", 14);
			std::string ermemutatas;
			std::cin >> ermemutatas;
			ermemutatas[0] = tolower(ermemutatas[0]);
			if (ermemutatas[0] == 'i')
			{
				story_kerdesek("Story/CH2_KERDES1.txt", 19);
				germemutatas = true;
			}
			if (ajtobe == '3')
			{
				story_kerdesek("Story/CH2_KERDES1.txt", 21);
			}
			else
			{
				story_kerdesek("Story/CH2_KERDES1.txt", 22);
				std::string indok;
				std::cin >> indok;
				story_kerdesek("Story/CH2_KERDES1.txt", 23);
			}
			story_kerdesek("Story/CH2_KERDES1.txt", 24);

			char mitcsinalsz;
			helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> mitcsinalsz;
				if (mitcsinalsz == '1')
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 30);
					helyesbe = true;
				}
				else if (mitcsinalsz == '2')
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 31);
				}
				else if (mitcsinalsz == '3')
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 32);
				}
				else if (mitcsinalsz == '4')
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 33);
				}
				else
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 34);
				}
			}

			story_kerdesek("Story/CH2_KERDES1.txt", 35);
			if (ermemutatas[0] == 'i')
			{
				story_kerdesek("Story/CH2_KERDES1.txt", 38);
			}

			helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> mitcsinalsz;
				if (mitcsinalsz == '1')
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 30);
					helyesbe = true;
				}
				else if (mitcsinalsz == '2')
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 39);
				}
				else if ((mitcsinalsz == '3') and (ermemutatas[0] == 'i'))
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 40);
					helyesbe = true;
				}
				else
				{
					story_kerdesek("Story/CH2_KERDES1.txt", 34);
				}
			}
			gCP = 2;
			spause();
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
				story_kerdesek("Story/CH6_KERDES1.txt", 1);
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
						story_kerdesek("Story/CH6_KERDES1.txt", 2);
					}
				}
				if (ded)
				{
					story_kerdesek("Story/CH6_KERDES1.txt", 3);
					spause();
					gCP = 5;
				}
			}
		}

		if (gCP == 6)
		{

			story_be("Story/CH7.txt");
			palya_letrehoz(j, 4, 5, &gelet, false, 0, 0, 0, nullptr, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			story_kerdesek("Story/CH7_KERDES1.txt", 1);

			bool tovabb = false;
			while (!tovabb)
			{
				char el;
				std::cin >> el;
				if (el == '1')
				{
					story_kerdesek("Story/CH7_KERDES1.txt", 6);
					char valasztas;
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							story_kerdesek("Story/CH7_KERDES1.txt", 7);
							spause();
							tovabb = true;
						}
						else
						{
							story_kerdesek("Story/CH7_KERDES1.txt", 8);
							story_kerdesek("Story/CH7_KERDES1.txt", 3);
						}
					}
				}

				else if (el == '2')
				{
					char valasztas;
					story_kerdesek("Story/CH7_KERDES1.txt", 9);
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							story_kerdesek("Story/CH7_KERDES1.txt", 11);
							spause();
							tovabb = true;
						}
						else
						{
							story_kerdesek("Story/CH7_KERDES1.txt", 8);
							story_kerdesek("Story/CH7_KERDES1.txt", 3);

						}
					}
				}

				else if (el == '3')
				{
					char valasztas;
					story_kerdesek("Story/CH7_KERDES1.txt", 12);
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							story_kerdesek("Story/CH7_KERDES1.txt", 13);
							spause();
							tovabb = true;
						}
						else
						{
							story_kerdesek("Story/CH7_KERDES1.txt", 8);
							story_kerdesek("Story/CH7_KERDES1.txt", 3);
						}
					}
				}

				else
				{
					std::cout << "Hibas bemenet!";
					spause();
				}
			}
			gCP = 7;
		}

		if (gCP == 7)
		{
			story_kerdesek("Story/CH7_KERDES2.txt", 1);
			spause();

			while (gCP == 7)
			{
				int eredeti_hp = gelet;
				palya_letrehoz(j, 4, 5, &gelet, false, 2, 5, 5, &sebzes, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');

				story_kerdesek("Story/CH7_KERDES2.txt", 3);

				char mit;
				std::cin >> mit;

				if (mit == '1')
				{
					story_kerdesek("Story/CH7_KERDES2.txt", 7);
					spause();
					gCP = 8;
				}

				else if (mit == '2')
				{
					story_kerdesek("Story/CH7_KERDES2.txt", 8);
					spause();
					gCP = 8;
				}

				else if (mit == '3')
				{
					story_kerdesek("Story/CH7_KERDES2.txt", 9);
					gelet = gelet - sebzes;
					if (gelet < 0)
					{
						story_kerdesek("Story/CH7_KERDES2.txt", 10);
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
					story_kerdesek("Story/CH7_KERDES2.txt", 11);
					spause();
				}
			}
		}

		if (gCP == 8)
		{
			story_be("Story/CH8.txt");

			j = new jatekmenet(4, 5, gelet, true, 2, 5, 5, nullptr, 1);
			j->gyujteni_be(1, 5, 1, 0);
			j->beolvas(*j, "Text.txt");
			fin = j->kiir(*j, 'G');
			if (!fin)
			{
				delete j;
				j = nullptr;
				exit(0);
			}
			gelet = j->getJElet();
			delete j;
			j = nullptr;

			coutszoveg("\nSzuper, megvan a gomba!\n");
			spause();

			j = new jatekmenet(4, 5, gelet, true, 2, 5, 5, nullptr, 1);
			j->gyujteni_be(1, 5, 1, 0);
			j->beolvas(*j, "Text.txt");
			fin = j->kiir(*j, 'D');
			if (!fin)
			{
				delete j;
				j = nullptr;
				exit(0);
			}
			gelet = j->getJElet();
			delete j;
			j = nullptr;

			coutszoveg("\nEs mostmar a dinnye is!\n");
			spause();

			gCP = 9;
		}

		if (gCP == 9)
		{
			coutszoveg("\nMori: Most, hogy megvannak az alapanyagok, ugy emlekszem eloszor a gombat kell belerakni a forro vizbe es utana a dinnyet.\n");
			spause();

			coutszoveg("\nN: Mit raksz bele eloszor?\n - gomba\n - dinnye\n");
			bool tovabb = false;
			while (!tovabb)
			{
				std::string mit;
				std::cin >> mit;
				if (isalpha(mit[0]))
				{
					mit[0] = tolower(mit[0]);
					if (mit[0] == 'g')
					{
						coutszoveg("\nN: Lefozod a csodaszert, es ugy erzed, ez az ital barmitol meg fog menteni!\n");
						spause();
						gelet += 10;
						tovabb = true;
					}
					if (mit[0] == 'd')
					{
						coutszoveg("\nN: A fozes rosszul sul el, eltort az uvegcsed es megvagta az ujad\n");
						gelet -= 2;
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
							spause();
							gCP = 7;
							gelet += 2;
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
					std::cout << "Hibsa bemenet!";
				}
			}
			gCP = 10;
		}

		if (gCP == 10)
		{
			coutszoveg("\nJancsi: elkeszultek a gyogyitalok, mehetunk is tovabb!\nMori: Gyere pattanj fel.\n");
			spause();

			j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, 1);
			j->gyujteni_be(1, 5, 1, 0);
			j->beolvas(*j, "Text.txt");
			fin = j->kiir(*j, 'M');
			if (!fin)
			{
				delete j;
				j = nullptr;
				exit(0);
			}
			gelet = j->getJElet();
			delete j;
			j = nullptr;

			gCP = 11;
		}

		if (gCP == 11)
		{
			coutszoveg("\nMori: Na es most, hogyan tovabb?\nJancsi: Nezd, ott latok egy csonakot nezzuk meg.\n");
			spause();

			j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, 1);
			j->gyujteni_be(1, 5, 1, 0);
			j->beolvas(*j, "Text.txt");
			fin = j->kiir(*j, 'M');
			if (!fin)
			{
				delete j;
				j = nullptr;
				exit(0);
			}
			gelet = j->getJElet();
			delete j;
			j = nullptr;

			coutszoveg("\nJancsi: Szuper, nem lyukas es nem tunik ugy mintha elsullyedne\n");
			spause();

			j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, 1);
			j->gyujteni_be(1, 5, 1, 0);
			j->beolvas(*j, "Text.txt");
			fin = j->kiir(*j, 'M');
			if (!fin)
			{
				delete j;
				j = nullptr;
				exit(0);
			}
			gelet = j->getJElet();
			delete j;
			j = nullptr;

			gCP = 12;
		}

		if (gCP == 12)
		{
			story_be("Story/CH12.txt");

			j = new jatekmenet(4, 5, gelet, true, 2, 5, 0, nullptr, 1);
			j->gyujteni_be(1, 5, 1, 0);
			j->beolvas(*j, "Text.txt");
			fin = j->kiir(*j, ' ');
			if (!fin)
			{
				delete j;
				j = nullptr;
				exit(0);
			}
			gelet = j->getJElet();
			delete j;
			j = nullptr;

			coutszoveg("\nSaccularius: Ki MeReSZeL iDe BeJoNNi!!! aZ eN oTTHoNoMBa!!!\nN: eszreveszi a sarkany a lovag kozeledtet, toppant egy nagyot, a barlang bejarata ele egy nagy szikla leesik.\n");
			spause();

			int sarkany_hp = 3;
			int eredeti_hp = gelet;

			while (sarkany_hp > 0)
			{

				j = new jatekmenet(4, 5, gelet, true, 2, 5, 0, nullptr, 1);
				j->gyujteni_be(1, 5, 1, 0);
				j->beolvas(*j, "Text.txt");
				fin = j->kiir(*j, ' ');
				if (!fin)
				{
					delete j;
					j = nullptr;
					exit(0);
				}
				gelet = j->getJElet();
				delete j;
				j = nullptr;

				if (sarkany_hp == 3)
				{

					coutszoveg("\nN: a sarkany a karmaival tamad, mit csinalsz?\n1. - elugrasz elole\n2. - vedekezel a kardoddal\n3. - elszaladsz\n4 - alsz egy helybe\n");

					char mit;
					std::cin >> mit;

					if (mit == '1')
					{
						coutszoveg("\nElograsz a tamadas elol!\n");
						sarkany_hp -= 1;
						spause();
					}

					else if (mit == '2')
					{
						coutszoveg("\nMegprobalsz vedekezni a kardoddal, de a sarkany elsopor!\n");
						gelet -= 2;
						spause();
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
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
						coutszoveg("\nA sarkany tud repulni es hamar utol er!\n");
						gelet -= 5;
						spause();
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
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
						coutszoveg("\nA sarkany telibe eltalal!\n");
						gelet -= 10;
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
							spause();
							gCP = 7;
						}
						else
						{
							std::cout << "10 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}
					else
					{
						std::cout << "Hibas bemenet!";
						spause();
					}
				}

				else if (sarkany_hp == 2)
				{

					coutszoveg("\nN: a sarkany tuzet okad, hogy veded ki?\n1. - elbujsz egy szikla moge\n2. - megprobalsz elszaladni elole\n");
					if (germemutatas)
					{
						coutszoveg("3 - hasznalod az ermet \n");
					}

					char mit;
					std::cin >> mit;

					if (mit == '1')
					{
						coutszoveg("\nElbujsz egy szikla moge, itt a langok nem egetnek meg!\n");
						sarkany_hp -= 1;
						spause();
					}

					else if (mit == '2')
					{
						coutszoveg("\nMegprobalsz elszaladni a sarkany elol, de a langjai megegetnek!\n");
						gelet -= 7;
						spause();
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
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
						coutszoveg("\nAz erme mukodott! Semmi nyoma a langoknak!\n");
						sarkany_hp -= 1;
						spause();
					}

					else
					{
						std::cout << "Hibas bemenet!";
						spause();
					}
				}

				else if (sarkany_hp == 1)
				{

					coutszoveg("\nN: A sarkany megprobal felfalni, mit csinalsz?\n1. - hagyod hogy lenyeljen hatha jol sul el\n2. - megvarod meg eleg kozel er es atszurod a nyakat\n3. - kiszurod az egyik szemet\n4. - megprobalsz elszaladni elole\n");

					char mit;
					std::cin >> mit;

					if (mit == '1')
					{
						coutszoveg("\nNem igazan jol sult el a dolog!\n");
						gelet -= 5;
						spause();
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
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
						coutszoveg("\nTokeletes volt a kardforgatasod! A sarkany osszeomlik elotted!\n");
						sarkany_hp -= 1;
						spause();
					}

					else if (mit == '3')
					{
						coutszoveg("\nEttol csak mergesebb lett! Megprobal a fogaival osszeroppantani!\n");
						gelet -= ~12;
						spause();
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
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
						coutszoveg("\nMegprobalsz elszaladni elole hatha elfelejti a sarkany ez az egeszet, de siman utol er!\n");
						gelet -= 10;
						if (gelet < 0)
						{
							std::cout << "MEGHALTAL";
							spause();
							gCP = 7;
						}
						else
						{
							std::cout << "10 eletet vesztettel, mostmar csak " << gelet << " eleted van\n";
							spause();
						}
					}
					else
					{
						std::cout << "Hibas bemenet!";
						spause();
					}
				}
			}

			coutszoveg("\nHercegno: o megmentom, nem hittem volna hogy valaki le tudja gyozni a sarkanyt!\nJancsi: Gyere hercegno, a beszelo lovam es a kiraly mar var!\n");
			spause();
		}
	}
}