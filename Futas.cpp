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

void costum_palya()
{
	int J_X, J_Y;
	std::cout << "\nJatekosod X koordinataja: ";  std::cin >> J_X;
	std::cout << "\nJatekosod Y koordinataja: ";  std::cin >> J_Y;
	std::cout << "A palyadon egy lyuk a cel vagy egy adott karakter?\n1 = lyuk\n2 = karakter";
	char veg;
	//do, while valamiert csak most jutott egyembe h igy is lehetett volna... - 2022.12.08. 23:24
	do {
		std::cin >> veg;
	} while (veg != '1' and veg != '2');
	bool van_e_boss = false;
	int B_X = 0, B_Y = 0;
	char veg_char = 'C';
	if (veg == '2')
	{
		van_e_boss = true;
		std::cout << "\nCel X koordinataja: ";  std::cin >> B_X;
		std::cout << "\nCel Y koordinataja: ";  std::cin >> B_Y;
		std::cout << "\nCel karaktere: ";  std::cin >> veg_char;
	}
	Jatekmenet* j = new Jatekmenet(J_X, J_Y, 1, van_e_boss, B_X, B_Y, 0, nullptr, 0);
	std::cout << "\nIrd be a palyad nevet (legyen ugyan abban a mappaban ahol a jatek, vagy add meg a teljes eleresi utvonalat)\n";
	std::string palya_neve;
	std::cin >> palya_neve;
	j->beolvas(*j, palya_neve);
	bool fin = j->kiir(*j, veg_char);

	delete j;
	j = nullptr;
	if (fin)
	{
		system(CLEAR);
		std::cout << "Teljesitetted a labirintusodat! GG\n";
		spause();
		exit(0);
	}
	else
	{
		system(CLEAR);
		std::cout << "Kileptel!\n";
		spause();
		exit(0);
	}
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
				std::this_thread::sleep_for(5ms);
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
			hanyadik_sor++;
			//kiiras
			for (int i = 0; i < karakterek; i++) {
				// #-nel megall
				if (egysor[i] == '#' and hanyadik_sor == pos)
				{
					var = true;
				}
				//kiirja a sort
				if (!var and hanyadik_sor == pos)
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
bool palya_letrehoz(Global* g, int jancsiX, int jancsiY, bool van_e_boss, int bossX, int bossY, int seb, char** palya, int mennyi_coll, int coll1X, int coll1Y, int coll1M, int coll2X, int coll2Y, int coll2M, int coll3X, int coll3Y, int coll3M, std::string palya_neve, char boss_char)
{
	int jancsihp = g->getgElet();
	//labirintus letrehozasa
	g->jatekter = new Jatekmenet(jancsiX, jancsiY, jancsihp, van_e_boss, bossX, bossY, seb, palya, mennyi_coll);
	//gyujtogetni valok letrehozasa, ha van (max 3)
	if (mennyi_coll >= 1)
	{
		g->jatekter->gyujteni_be(coll1X, coll1Y, coll1M, 0);
		if (mennyi_coll >= 2)
		{
			g->jatekter->gyujteni_be(coll2X, coll2Y, coll2M, 1);
			if (mennyi_coll == 3)
			{
				g->jatekter->gyujteni_be(coll3X, coll3Y, coll3M, 2);
			}
		}
	}
	//palya beolvasasa
	g->jatekter->beolvas(*g->jatekter, palya_neve);
	//kiiras
	g->setFin(g->jatekter->kiir(*g->jatekter, boss_char));
	//elet, CP frissitese
	if (!g->getFin())
	{
		delete g->jatekter;
		g->jatekter = nullptr;
	}
	if(g->getFin())
	{
	//player elet kiirasa
	g->setgElet(g->jatekter->getJElet());
	//int gelet = j->getelet();
	//*ghp = gelet;
	//sebzes kiirasa
	if (seb > 0)
	{
		g->setSebzes(g->jatekter->getBSebzes());
	/*int sebzes = j->getBSebzes();
	*gsebzes = sebzes;*/
	}
	//labirintus torlese
		delete g->jatekter;
		g->jatekter = nullptr;
	}
	return g->getFin();
}

//kilepes, ha van kerdes
void kilep(Global* g, bool fin, std::ifstream& f)
{
	if(!fin)
	{		
		bool kilep = g->mentes();
		if(kilep)
		{
		if (f) { f.close(); }
		if (g) { delete g; }
		g = nullptr;
		exit(0);
		}
	}
}

void kilep(Global* g, bool fin)
{
	if(!fin)
	{
		bool kilep = g->mentes();
		if(kilep)
		{
		if (g) { delete g; }
		g = nullptr;
		exit(0);
		}
	}
}

void run(int fut)
{
	if (fut != 4)
	{
		Global* global_valtozok = new Global;

		if (fut == 2)
		{
			global_valtozok->mentes_be();
		}

		if (fut == 3)
		{
			costum_palya();
		}

		if (global_valtozok->getgCP() == 0)
		{
			story_be(STORYL"/CH1.txt");

			//kerdes
			std::ifstream f(STORYL"/CH1_KERDES1.txt");
			story_kerdesek(f, 1);
			char elsovetel;
			char masodikvetel;
			while (!global_valtozok->getHelyesbe())
			{
				std::cin >> elsovetel;
				std::cin >> masodikvetel;
				if (elsovetel == '1' or elsovetel == '2' or elsovetel == '3' or elsovetel == '4')
				{
					if (masodikvetel == '1' or masodikvetel == '2' or masodikvetel == '3' or masodikvetel == '4')
					{
						if (elsovetel != masodikvetel)
						{
							global_valtozok->setHelyesbe(true);
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

			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 2, 1, 5, 1, 2, 5, 2, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());

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

			//kerdesre valasz 2
			story_kerdesek(f, 12);
			if (elsovetel == '2' or masodikvetel == '2')
			{
				story_kerdesek(f, 13);
				spause();
			}
			else
			{
				//felteteles labirintus, (ez a futasba az utolso erdemelges komment, igy fognak lefolyni a CHapter-ek)
				story_kerdesek(f, 14);
				spause();
				do{
				global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
				kilep(global_valtozok, global_valtozok->getFin(), f);
				}while(!global_valtozok->getFin());

			}
			f.close();
			global_valtozok->setgCP(1);
		}

		if (global_valtozok->getgCP() == 1)
		{

			story_be(STORYL"/CH2_1.txt");

			std::ifstream f(STORYL"/CH2_KERDES1.txt");
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

			story_be(STORYL"/CH2_2.txt");

			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());

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
				global_valtozok->setgErmemutatas(true);
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
			global_valtozok->setgCP(2);
		}

		if (global_valtozok->getgCP() == 2)
		{

			story_be(STORYL"/CH3.txt");
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getgCP());
			}while(!global_valtozok->getFin());
			global_valtozok->setgCP(3);
		}

		if (global_valtozok->getgCP() == 3)
		{

			story_be(STORYL"/CH4.txt");
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin());
			}while(!global_valtozok->getFin());
			global_valtozok->setgCP(4);
		}

		if (global_valtozok->getgCP() == 4)
		{

			story_be(STORYL"/CH5.txt");
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin());
			}while(!global_valtozok->getFin());
			global_valtozok->setgCP(5);
		}

		if (global_valtozok->getgCP() == 5)
		{

			story_be(STORYL"/CH6.txt");

			while (global_valtozok->getgCP() == 5)
			{
				std::ifstream f(STORYL"/CH6_KERDES1.txt");
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
								global_valtozok->setgCP(6);
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
				}
				f.close();
			}
		}

		if (global_valtozok->getgCP() == 6)
		{

			story_be(STORYL"/CH7.txt");
			std::ifstream f(STORYL"/CH7_KERDES1.txt");
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());
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
			global_valtozok->setgCP(7);
		}

		if (global_valtozok->getgCP() == 7)
		{
			std::ifstream f(STORYL"/CH7_KERDES2.txt");
			story_kerdesek(f, 1);
			spause();

			while (global_valtozok->getgCP() == 7)
			{
				int eredeti_hp = global_valtozok->getgElet();
				do{
				global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, true, 2, 5, 5, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
				kilep(global_valtozok, global_valtozok->getFin(), f);
				}while(!global_valtozok->getFin());
				story_kerdesek(f, 3);

				char mit;
				std::cin >> mit;

				if (mit == '1')
				{
					story_kerdesek(f, 7);
					spause();
					global_valtozok->setgCP(8);
				}

				else if (mit == '2')
				{
					story_kerdesek(f, 8);
					spause();
					global_valtozok->setgCP(8);
				}

				else if (mit == '3')
				{
					story_kerdesek(f, 9);
					global_valtozok->setgElet(global_valtozok->getgElet() - global_valtozok->getSebzes());
					if (global_valtozok->getgElet() < 0)
					{
						story_kerdesek(f, 10);
						spause();
						global_valtozok->setgElet(eredeti_hp);
					}
					else
					{
						std::cout << global_valtozok->getSebzes() << " eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
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

		if (global_valtozok->getgCP() == 8)
		{
			story_be(STORYL"/CH8.txt");
			std::ifstream f(STORYL"/CH8_KERDES1.txt");
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, true, 2, 5, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'G'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());

			story_kerdesek(f, 1);
			spause();

			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, true, 2, 5, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'D'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());
			story_kerdesek(f, 2);
			spause();

			f.close();
			global_valtozok->setgCP(9);
		}

		if (global_valtozok->getgCP() == 9)
		{
			std::ifstream f(STORYL"/CH9_KERDES1.txt");
			story_kerdesek(f, 1);
			spause();
			story_kerdesek(f, 2);
			
			bool tovabb = false;
			while (!tovabb)
			{
				int eredeti_elet = global_valtozok->getgElet();
				std::string mit;
				std::cin >> mit;
				if (isalpha(mit[0]))
				{
					mit[0] = tolower(mit[0]);
					if (mit[0] == 'g')
					{
						story_kerdesek(f, 5);
						spause();
						global_valtozok->setgElet(global_valtozok->getgElet() + 10);
						tovabb = true;
					}
					if (mit[0] == 'd')
					{
						story_kerdesek(f, 6);
						global_valtozok->setgElet(global_valtozok->getgElet() - 2);
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 7);
							spause();
							global_valtozok->setgElet(eredeti_elet);
						}
						else
						{
							std::cout << "2 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
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
			global_valtozok->setgCP(10);
		}

		if (global_valtozok->getgCP() == 10)
		{
			std::ifstream f(STORYL"/CH10_KERDES1.txt");
			story_kerdesek(f, 1);
			f.close();
			spause();
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());
			global_valtozok->setgCP(11);
		}

		if (global_valtozok->getgCP() == 11)
		{
			std::ifstream f(STORYL"/CH11_KERDES1.txt");
			story_kerdesek(f, 1);
			spause();
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());

			story_kerdesek(f, 3);
			spause();
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", 'M'));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());

			f.close();
			global_valtozok->setgCP(12);
		}

		if (global_valtozok->getgCP() == 12)
		{
			story_be(STORYL"/CH12.txt");
			std::ifstream f(STORYL"/CH12_KERDES1.txt");
			do{
			global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, true, 2, 5, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", ' '));
			kilep(global_valtozok, global_valtozok->getFin(), f);
			}while(!global_valtozok->getFin());

			story_kerdesek(f, 1);
			spause();

			int sarkany_hp = 3;
			int eredeti_hp = global_valtozok->getgElet();

			while (sarkany_hp > 0)
			{
				if (sarkany_hp == 3)
				{
					do{
					global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, true, 2, 5, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", ' '));
					kilep(global_valtozok, global_valtozok->getFin(), f);
					}while(!global_valtozok->getFin());

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
						global_valtozok->setgElet(global_valtozok->getgElet() - 2);
						spause();
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 11);
							spause();
						}
						else
						{
							std::cout << "2 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
							spause();
						}
					}

					else if (mit == '3')
					{
						story_kerdesek(f, 12);
						global_valtozok->setgElet(global_valtozok->getgElet() - 5);
						spause();
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 11);
							spause();
						}
						else
						{
							std::cout << "5 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
							spause();
						}
					}

					else if (mit == '4')
					{
						story_kerdesek(f, 13);
						global_valtozok->setgElet(global_valtozok->getgElet() - 10);
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 11);
							spause();
						}
						else
						{
							std::cout << "10 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
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
					do{
					global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, true, 2, 5, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", ' '));
					kilep(global_valtozok, global_valtozok->getFin(), f);
					}while(!global_valtozok->getFin());

					story_kerdesek(f, 15);
					if (global_valtozok->getgErmemutatas())
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
						global_valtozok->setgElet(global_valtozok->getgElet() - 7);
						spause();
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 11);
							spause();
						}
						else
						{
							std::cout << "7 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
							spause();
						}
					}

					else if (mit == '3' and global_valtozok->getgErmemutatas())
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
					do{
					global_valtozok->setFin(palya_letrehoz(global_valtozok, 4, 5, true, 2, 5, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, PALYAKL"/Text.txt", ' '));
					kilep(global_valtozok, global_valtozok->getFin(), f);
					}while(!global_valtozok->getFin());

					story_kerdesek(f, 22);

					char mit;
					std::cin >> mit;

					if (mit == '1')
					{
						story_kerdesek(f, 27);
						global_valtozok->setgElet(global_valtozok->getgElet() - 5);
						spause();
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 11);
							spause();
						}
						else
						{
							std::cout << "5 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
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
						global_valtozok->setgElet(global_valtozok->getgElet() - 12);
						spause();
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 11);
							spause();
						}
						else
						{
							std::cout << "12 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
							spause();
						}
					}

					else if (mit == '4')
					{
						story_kerdesek(f, 30);
						global_valtozok->setgElet(global_valtozok->getgElet() - 10);
						if (global_valtozok->getgElet() < 0)
						{
							story_kerdesek(f, 11);
							spause();
						}
						else
						{
							std::cout << "10 eletet vesztettel, mostmar csak " << global_valtozok->getgElet() << " eleted van\n";
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
			story_be(STORYL"/CH13.txt");
		}
	}
}