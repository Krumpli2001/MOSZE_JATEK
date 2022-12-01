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
int palya_letrehoz(jatekmenet* j, int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya, int mennyi_coll, int coll1X, int coll1Y, int coll1M, int coll2X, int coll2Y, int coll2M, int coll3X, int coll3Y, int coll3M, std::string palya_neve, char boss_char)
{
	bool fin;
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
	int gelet = j->getJElet();
	//labirintus torlese
	delete j;
	j = nullptr;
	return gelet;
}

void run(int fut)
{
	if (fut != 4)
	{
		int gelet = 3;
		int gCP = 0;
		bool helyesbe = false;
		bool germemutatas = false;
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
							std::cout << "\nKetszer adtad meg ugy azt a szamot!\n";
						}
					}
					else
					{
						std::cout << "\nHibas bemenet\n";
					}
				}
				else
				{
					std::cout << "\nHibas bemenet\n";
				}
			}

			gelet = palya_letrehoz(j, 4, 5, gelet, false, 0, 0, 0, nullptr, 2, 1, 5, 1, 2, 5, 2, 0, 0, 0, "Text.txt", 'M');

			//kerdesre valasz
			story_kerdesek("Story/CH1_KERDES2.txt", 1);
			if (elsovetel == '1' or masodikvetel == '1')
			{
				story_kerdesek("Story/CH1_KERDES2.txt", 2);
			}
			else if (elsovetel == '3' or masodikvetel == '3')
			{
				story_kerdesek("Story/CH1_KERDES2.txt", 3);
			}
			else if (elsovetel == '4' or masodikvetel == '4')
			{
				story_kerdesek("Story/CH1_KERDES2.txt", 4);
			}
			spause();

			//kerdesre valasz
			story_kerdesek("Story/CH1_KERDES2.txt", 5);
			if (elsovetel == '2' or masodikvetel == '2')
			{
				story_kerdesek("Story/CH1_KERDES2.txt", 6);
				spause();
			}
			else
			{
				//felteteles labirintus
				story_kerdesek("Story/CH1_KERDES2.txt", 7);
				spause();
				gelet = palya_letrehoz(j, 4, 5, gelet, false, 0, 0, 0, nullptr, 1, 1, 5, 1, 0, 0, 0, 0, 0, 0, "Text.txt", 'M');
			}
			gCP = 1;
		}

		if (gCP == 1)
		{

			story_be("Story/CH2_1.txt");

			coutszoveg("\nKovacs: eloszor is fiam, valaszd ki melyik kozetbol szeretned elkesziteni a kardodat :\n- Fekete\n- Kek\n- Lila\n- Zold\n");
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
			//CP2

			coutszoveg("\nN: a pancel olyan konnyu volt, hogy Jancsi ugy erezte, konnyebb futni mint gyalogolni.\
Egy fel nap alatt a fovarosban talalta magat eques, az oreg lovag haza elott.\n");

			char ajtobe;
			coutszoveg("\n1. - bekopogsz\n2.- benyitsz\n3.- bedontod az ajtot\n");
			helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> ajtobe;
				if ((ajtobe == '1') or (ajtobe == '2') or (ajtobe == '3'))
				{
					helyesbe = true;
					if (ajtobe == '3')
					{
						coutszoveg("\nLovag : Most ezt miert kellett? Na mindegy ugy is rozoga volt. Amugy is ");
					}
				}
				else
				{
					std::cout << "\nHibas bemenet\n";
				}
			}
			if (ajtobe != '3')
			{
				coutszoveg("Lovag:");
			}
			coutszoveg("Te meg mit akarsz itt te gyerek!?\n");
			coutszoveg("\nJancsi : Faber kovacs mester kuldott, azt mondta te megtanitasz a kardforgatasra.\n");
			coutszoveg("\nN : megmutatod neki az ermet\n- Igen\n- Nem\n");
			std::string ermemutatas;
			std::cin >> ermemutatas;
			ermemutatas[0] = tolower(ermemutatas[0]);
			if (ermemutatas[0] == 'i')
			{
				coutszoveg("\nLovag : Barmire is keszulsz igazan megbizhat benned, ha az oreg torpe a tuzallosag ermet is neked adta. Egye fene megtanitalak.\n");
				germemutatas = true;
			}
			coutszoveg("\nMeg biza, de nem ingyen, ");
			if (ajtobe == '3')
			{
				coutszoveg("Javitsd meg az ajtomat te mamlasz, miert kellett betorni, van kilincse is.\n");
			}
			else
			{
				coutszoveg("Mire kell neked a kardforgatas muveszete?\n");
				std::string indok;
				std::cin >> indok;
				coutszoveg("\nJol van, ez egy nemes indok, megtanitalak.\n");
			}
			coutszoveg("\nN : 3 nap  kemeny edzes utan eljott a teszt ideje\n");
			coutszoveg("\nLovag : Ha a sarkany a karmaival tamad, mit csinalsz ?\n");
			char mitcsinalsz;
			helyesbe = false;

			coutszoveg("\n1.- elugrasz elole\n2.- vedekezel a kardoddal\n3.- elszaladsz\n4.- alsz egy helybe\n");
			while (!helyesbe)
			{
				std::cin >> mitcsinalsz;
				if (mitcsinalsz == '1')
				{
					coutszoveg("\nHelyes!\n");
					helyesbe = true;
				}
				else if (mitcsinalsz == '2')
				{
					coutszoveg("\nNem, nem birod el a sarkanyt, ahhoz tul nagy!\n");
				}
				else if (mitcsinalsz == '3')
				{
					coutszoveg("\nNem, tud repulni, utol fog erni!\n");
				}
				else if (mitcsinalsz == '4')
				{
					coutszoveg("\nRemenytelen...\n");
				}
				else
				{
					std::cout << "\nHibas bemenet\n";
				}
			}

			coutszoveg("\nLovag : Ha tuzet okad, azt hogy veded ki?\n1. - elbujsz egy szikla moge\n2. - megprobalsz elszaladni elolen\n");
			if (ermemutatas[0] == 'i')
			{
				coutszoveg("3. - hasznalod az ermet\n");
			}

			helyesbe = false;
			while (!helyesbe)
			{
				std::cin >> mitcsinalsz;
				if (mitcsinalsz == '1')
				{
					coutszoveg("\nHelyes!\n");
					helyesbe = true;
				}
				else if (mitcsinalsz == '2')
				{
					coutszoveg("\nNem, a tuz utol fog erni!\n");
				}
				else if ((mitcsinalsz == '3') and (ermemutatas[0] == 'i'))
				{
					coutszoveg("\nAz is lehet, habar kockazatos szerintem.\n");
					helyesbe = true;
				}
				else
				{
					std::cout << "\nHibas bemenet\n";
				}
			}
			gCP = 2;
			spause();
		}

		if (gCP == 2)
		{

			story_be("Story/CH3.txt");

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
			gCP = 3;
			delete j;
			j = nullptr;
			//CP3

		}

		if (gCP == 3)
		{

			story_be("Story/CH4.txt");

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
			gCP = 4;
			delete j;
			j = nullptr;
			//CP4
		}

		if (gCP == 4)
		{

			story_be("Story/CH5.txt");

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
			gCP = 5;
			delete j;
			j = nullptr;
			//CP5
		}

		if (gCP == 5)
		{

			story_be("Story/CH6.txt");

			while (gCP == 5)
			{
				coutszoveg("\nN: Maradsz ejszakara [ I / N ]\n");
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
						std::cout << "Hibsa bemenet!";
					}
				}
				if (ded)
				{
					coutszoveg("\nN: Meg kellett volna fogadni a mano tanacsat, miutan lehunytad a szemed, tobbet mar soha nem nyitottad ki ujra\n");
					spause();
					std::cout << "MEGHALTAL";
					spause();
					gCP = 5;
				}
			}
		}

		if (gCP == 6)
		{

			story_be("Story/CH7.txt");

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

			bool tovabb = false;
			coutszoveg("\nN: a hosszu ejszaka utan ugy dontesz, hogy kell valami fele reggelit szerezni.\nelmesz :\n1. -vadaszni\n2. - horgaszni\n3. - gyujtogetni\n");
			while (!tovabb)
			{
				char el;
				std::cin >> el;
				if (el == '1')
				{
					char valasztas;
					coutszoveg("\nN: az erdo surujeben megpillantasz valami fene vadat. Utana futsz ? [I / N]\n");
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							coutszoveg("\nN: a felszereleseddel konnyeden elejtetted a vadat, igy meg is van mi lesz a reggeli.\n");
							spause();
							tovabb = true;
						}
						else
						{
							coutszoveg("\nNem sikerult vacsit szerezni, ezert mas modszerhez folyamodsz. (Ird be ujra a kivant szamot!)\n");
							spause();
						}
					}
				}

				else if (el == '2')
				{
					char valasztas;
					coutszoveg("\nN: elmesz egy kozelben csorgedezo patak melle es ugy dontesz, hogy nekiallsz horgaszni.Lassan mar egy oraja itt ucsorogsz de meg nem volt fogas.Folytatod a horgaszast ? [I / N]\n");
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							coutszoveg("\nN: Nagyjabol ket perc mulva, meg is hozta turelmed a gyumolcset, igy meg is van mi lesz a reggeli.\n");
							spause();
							tovabb = true;
						}
						else
						{
							coutszoveg("\nNem sikerult vacsit szerezni, ezert mas modszerhez folyamodsz. (Ird be ujra a kivant szamot!)\n");
							spause();
						}
					}
				}

				else if (el == '3')
				{
					char valasztas;
					coutszoveg("\nN: rengeteg szines bogyot latsz noni az erdoben de egyiket sem ismered.Biztos meg akarod oket kostolni ? [I / N]\n");
					std::cin >> valasztas;
					if (isalpha(valasztas))
					{
						valasztas = tolower(valasztas);
						if (valasztas == 'i')
						{
							coutszoveg("\nN: Ugy dontesz hogy egy kicsit megperkelet a talalt gyumolcsoket, hatha attol jobb izuk lesz. Szerencsere igazad lett!\n");
							spause();
							tovabb = true;
						}
						else
						{
							coutszoveg("\nNem sikerult vacsit szerezni, ezert mas modszerhez folyamodsz. (Ird be ujra a kivant szamot!)\n");
							spause();
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
			coutszoveg("\nN: Neki is allsz tuzet rakni, hogy elkeszitsd a varva vart reggelidet, de a finom illatra, megjelenik egy medve az erdobol.\n");
			spause();

			while (gCP == 7)
			{
				int eredeti_hp = gelet;
				j = new jatekmenet(4, 5, gelet, true, 2, 5, 5, nullptr, 1);
				//j->gyujteni_be(1, 5, 1, 0);
				j->beolvas(*j, "Text.txt");
				fin = j->kiir(*j, 'M');
				if (!fin)
				{
					delete j;
					j = nullptr;
					exit(0);
				}
				int sebzes = j->getBSebzes();
				gelet = j->getJElet();
				delete j;
				j = nullptr;

				coutszoveg("\nN: a medve rad tamad, mit csinalsz ?\n1. - adsz neki a reggelibol\n2. - elugrasz elole, es beledofod a kardodat\n 3. - felmaszol a fara ami alatt sutogettel\n");

				char mit;
				std::cin >> mit;

				if (mit == '1')
				{
					coutszoveg("\nAdtal a medvenek a reggelidbol, az pedig bekesen tovabb al.\n");
					spause();
					gCP = 8;
				}

				else if (mit == '2')
				{
					coutszoveg("\nA medve osszerogyik elotted, keves ember mondhatja el ezt magarol\n");
					spause();
					gCP = 8;
				}

				else if (mit == '3')
				{
					coutszoveg("\nA medve nagyon jol maszik fara, es lerant az agrol\n");
					gelet = gelet - sebzes;
					if (gelet < 0)
					{
						std::cout << "MEGHALTAL";
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
					std::cout << "Hibas bemenet!";
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