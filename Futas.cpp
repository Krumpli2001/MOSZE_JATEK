#include "futas.hpp"

//jatekmenet konstruktora
	//(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya,
	//bool van_e_gyujteni, int collX, int collY, int mennyitad)

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
			return 0;
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

void coutszoveg(std::string sz)
{
	//karakterenkenti kiiras
	using namespace std::chrono_literals;
	int karakterek = sz.length();
	for (int i = 0; i < karakterek; i++) {
		std::cout << sz[i];
		std::this_thread::sleep_for(5ms);
	}
}

void run(int fut)
{
	if (fut != 0)
	{
		int gelet = 3;
		int gCP = 0;

		//CP 0
		story_be("Story/CH1.txt");

		//kerdes
		coutszoveg("\nN: Mit viszel magaddal ? (2 valasztas)\n- 1. etel es ital\n- 2. meleg ruha\n- 3. kes es csuzli\n- 4. kotel\n(Ird be a megfelelo szamot)\n");
		char elsovetel;
		char masodikvetel;
		bool helyesvetel = false;
		while (!helyesvetel)
		{
			std::cin >> elsovetel;
			std::cin >> masodikvetel;
			if (elsovetel == '1' or elsovetel == '2' or elsovetel == '3' or elsovetel == '4')
			{
				if (masodikvetel == '1' or masodikvetel == '2' or masodikvetel == '3' or masodikvetel == '4')
				{
					if(elsovetel != masodikvetel)
					{
						helyesvetel = true;
					}
				}
			}
			else
			{
				std::cout << "\nHibas bemenet\n";
			}
		}

		//labirintus letrehozasa
		jatekmenet* j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, true, 1, 5, 1, false);
		//palya beolvasasa
		j->beolvas(*j, "Text.txt");
		//kiiras
		j->kiir(*j, 'M');
		//elet, CP frissitese
		gelet = j->getJElet();
		gCP = 1;
		//labirintus torlese
		delete j;
		j = nullptr;
		//CP1

		//kerdesre valasz
		coutszoveg("\nJancsi: teljesitettem estere utam felet azonban, az ejszaka hideg, es egy kicsit ehes is vagyok, mit kene tennem ehseg ellen?\n");
		if (elsovetel == '1' or masodikvetel == '1')
		{
			coutszoveg("\nAh tudom, megeszem amit magammal hoztam\n");
		}
		else if (elsovetel == '3' or masodikvetel == '3')
		{
			coutszoveg("\nAh tudom, elmegyek vadaszni a kessel es csuzlival\n");
		}
		else if (elsovetel == '4' or masodikvetel == '4')
		{
			coutszoveg("\nAh tudom, allitok a kotellel egy csapdat\n");
		}
		spause();

		//kerdesre valasz
		coutszoveg("\nNa de a hideg ellen mi tevo legyek?\n");
		if (elsovetel == '2' or masodikvetel == '2')
		{
			coutszoveg("\nFelveszem a kabatom, kulonben beteg leszek\n");
			spause();
		}
		else
		{
			//felteteles labirintus
			coutszoveg("\nSzerintem keresek egy barlangot ahol aludhatok, meg ne fazzak\n");
			spause();
			j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, true, 1, 5, 1, false);
			j->beolvas(*j, "Text.txt");
			j->kiir(*j, 'M');
			delete j;
			j = nullptr;
		}

		story_be("Story/CH2_1.txt");

		coutszoveg("\nKovacs: eloszor is fiam, valaszd ki melyik kozetbol szeretned elkesziteni a kardodat :\n- Fekete\n- Kek\n- Lila\n- Zold\n");
		std::string kardszin;
		bool helyeskardszin = false;
		while (!helyeskardszin)
		{
			std::cin >> kardszin;
			kardszin[0] = tolower(kardszin[0]);
			if (kardszin[0] == 'f' or kardszin[0] == 'k' or kardszin[0] == 'l' or kardszin[0] == 'z')
			{
				helyeskardszin = true;
			}
			if (!helyeskardszin) {
				coutszoveg("\nKovacs: Te fiam, nem latod a kozeteket?\n");
			}
		}

		story_be("Story/CH2_2.txt");

		j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, true, 1, 5, 1, false);
		j->beolvas(*j, "Text.txt");
		j->kiir(*j, 'M');
		gelet = j->getJElet();
		gCP = 2;
		delete j;
		j = nullptr;
		//CP2

		coutszoveg("\nN: a pancel olyan konnyu volt, hogy Jancsi ugy erezte, konnyebb futni mint gyalogolni.\
Egy fel nap alatt a fovarosban talalta magat eques, az oreg lovag haza elott.\n");

		char ajtobe;
		coutszoveg("\n1. - bekopogsz\n2.- benyitsz\n3.- bedontod az ajtot\n");
		bool helyesajtobe = false;
		while (!helyesajtobe)
		{
			std::cin >> ajtobe;
			if ((ajtobe == '1') or (ajtobe == '2') or (ajtobe == '3'))
			{
				helyesajtobe = true;
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
		bool helyesmitcsinalsz = false;

		coutszoveg("\n1.- elugrasz elole\n2.- vedekezel a kardoddal\n3.- elszaladsz\n4.- alsz egy helybe\n");
		while (!helyesmitcsinalsz)
		{
			std::cin >> mitcsinalsz;
			if (mitcsinalsz == '1')
			{
				coutszoveg("\nHelyes!\n");
				helyesmitcsinalsz = true;
			}
			else if (mitcsinalsz == '2')
			{
				coutszoveg("\nNem, nem birod el a sarkanyt, ahhoz tul nagy!\n");
			}
			else if (mitcsinalsz == '3')
			{
				coutszoveg("\nNem, tud repulni, utol fog erni!\n");
			}
			else if(mitcsinalsz == '4')
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

		helyesmitcsinalsz = false;
		while (!helyesmitcsinalsz)
		{
			std::cin >> mitcsinalsz;
			if (mitcsinalsz == '1')
			{
				coutszoveg("\nHelyes!\n");
				helyesmitcsinalsz = true;
			}
			else if (mitcsinalsz == '2')
			{
				coutszoveg("\nNem, a tuz utol fog erni!\n");
			}
			else if ((mitcsinalsz == '3') and (ermemutatas[0] == 'i'))
			{
				coutszoveg("\nAz is lehet, habar kockazatos szerintem.\n");
				helyesmitcsinalsz = true;
			}
			else
			{
				std::cout << "\nHibas bemenet\n";
			}
		}
		spause();


		story_be("Story/CH3.txt");

		j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, true, 1, 5, 1, false);
		j->beolvas(*j, "Text.txt");
		j->kiir(*j, 'M');
		gelet = j->getJElet();
		gCP = 3;
		delete j;
		j = nullptr;
		//CP3

		story_be("Story/CH4.txt");

		j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, true, 1, 5, 1, false);
		j->beolvas(*j, "Text.txt");
		j->kiir(*j, 'M');
		gelet = j->getJElet();
		gCP = 4;
		delete j;
		j = nullptr;
		//CP4

		story_be("Story/CH5.txt");

		j = new jatekmenet(4, 5, gelet, false, 0, 0, 0, nullptr, true, 1, 5, 1, false);
		j->beolvas(*j, "Text.txt");
		j->kiir(*j, 'M');
		gelet = j->getJElet();
		gCP = 4;
		delete j;
		j = nullptr;
		//CP5

		story_be("Story/CH5.txt");


	}
}















