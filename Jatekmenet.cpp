#include "jatekmenet.hpp"

jatekmenet& jatekmenet::setCP(int cpszam)
{
    cp = cpszam;
    return *this;
}

jatekmenet& jatekmenet::setKilep(bool kilepo)
{
    kilep = kilepo;
    return *this;
}

void jatekmenet::gyujteni_be(int X, int Y, int M, int darab)
{
    coll[darab].setX(X);
    coll[darab].setY(Y);
    coll[darab].setAD(M);
}

void jatekmenet::megvan_e(int i)
{
    for (int j = 0; j < i; j++)
    {
        if ((jancsi->getX() == coll[j].getX()) and (jancsi->getY() == coll[j].getY()) and (coll[j].getMegvolt() == false))
        {
            jancsi->setElet(jancsi->getElet() + coll[j].getMennyit_Ad());
            coll[j].setMegvolt(true);
        }
    }
}

//mentes
void jatekmenet::mentes(jatekmenet& j)
{
    system(CLEAR);
    bool kilep = false;
    bool mentes = false;
    std::cout << "Biztosan ki szeretnel lepni? [ I / N ]\n";
    char biztos_k;
    std::cin >> biztos_k;
    biztos_k = tolower(biztos_k);
    if (biztos_k == 'i' or biztos_k == 'y') {
        std::cout << "Szeretnel menteni? [ I / N ]\n";
        char biztos_m;
        std::cin >> biztos_m;
        biztos_m = tolower(biztos_m);
        if (biztos_m == 'i' or biztos_m == 'y') {

            std::string file_nev;
            std::cout << "\nMi legyen a mentesed neve?\n";
            std::cin >> file_nev;
            int cpszama;
            cpszama = getCP();
            int hpszama;
            hpszama = j.jancsi->getElet();
            std::ofstream f(file_nev);
            if (f.is_open())
            {
                f << cpszama << std::endl;
                f << hpszama << std::endl;
                f.close();
                setKilep(true);
            }
            else
            {
                std::cerr << "\nMENTESI HIBA!\n";
            }
        }
        else if (biztos_m == 'N' or biztos_m == 'n')
        {
            std::cout << "Nem mentettel\n";
            setKilep(true);
            spause();
        }
    }
    else if (biztos_k == 'n' or biztos_k == 'N')
    {
        std::cout << "Nem leptel ki\n";
        spause();
    }
    else
    {
        std::cout << "Hibas valasz\n";
        spause();
    }

}

//mentett cp beolvasasa
void jatekmenet::mentes_be(std::string mentes_neve)
{
    std::string file_nev;
    std::cin >> file_nev;
    std::ifstream f(file_nev);
    if (f.is_open())
    {
        std::string* data = new std::string[2];
        for (int i = 0; i < 2; i++)
        {
            std::getline(f, data[i]);
        }
        setCP(stoi(data[0]));
        jancsi->setElet(stoi(data[1]));
        f.close();
    }
    else
    {
        std::cerr << "\nNEM SIKERULT BETOLTENI A MENTEST\n";
    }
}

//palya beolvasasa
jatekmenet& jatekmenet::beolvas(jatekmenet& j, std::string palyanev)
{

    std::string egysor;

    std::ifstream f(palyanev);
    int karakterek = 0;
    int sorok = 0;


    if (f.is_open())
    {
        //palya meretenek meghatarozasa
        while (std::getline(f, egysor)) {

            //std::cout << egysor << std::endl;
            sorok++;
        }
        karakterek += egysor.length();
        f.clear();
        f.seekg(0);

        j.magassag = sorok;
        j.szelsseg = karakterek;

        //matrix letrehozasa
        j.palya = new char* [sorok];
        for (int i = 0; i < sorok; i++) {
            j.palya[i] = new char[karakterek];
        }

        //matrix feltoltese
        int sor = 0;
        while (std::getline(f, egysor)) {
            for (int i = 0; i < karakterek; i++) {
                j.palya[sor][i] = egysor[i];
            }
            sor++;
        }

        f.close();
    }
    else
    {
        std::cerr << "\nNem sikerult a beolvasas\n";
    }
    return *this;
}

//OMFG MOZOG!!!
bool jatekmenet::lepes(jatekmenet& j)
{

    int jancsi_X = jancsi->getX();
    int jancsi_Y = jancsi->getY();
    int elozo_jancsi_X = jancsi_X;
    int elozo_jancsi_Y = jancsi_Y;

    megvan_e(coll_mennyiseg);

        char hit = _getch();
        hit = tolower(hit);
        if (hit == 'w')
        {
            if (palya[jancsi_Y - 1][jancsi_X] == ' ')
            {
                jancsi->MozgasFel();
            }
            return true;
        }
        if (hit == 's')
        {
            if (palya[jancsi_Y + 1][jancsi_X] == ' ')
            {
                jancsi->MozgasLe();
            }
            return true;
        }
        if (hit == 'a')
        {
            if (palya[jancsi_Y][jancsi_X - 1] == ' ')
            {
                jancsi->MozgasBalra();
            }
            return true;
        }
        if (hit == 'd')
        {
            if (palya[jancsi_Y][jancsi_X + 1] == ' ')
            {
                jancsi->MozgasJobbra();
            }
            return true;
        }
        if (hit == 27 or hit == 'q')
        {
            mentes(j);
            return true;
        }
        if (hit == 'r')
        {
            jancsi->Reset();
            //boss->Reset();
            return true;
        }
        else
        {
            std::cout << "\nHibas bemenet\n";
            return true;
        }
    return false;
}

//palya kirajzolasa
void jatekmenet::kiir(jatekmenet& j, char boss_jele)
{
    system(CLEAR);
    bool leptunk_e;
    bool elso_kiiras = true;
    bool fin = false;

    while (!kilep) {
        leptunk_e = false;

        if (!elso_kiiras)
        {
            leptunk_e = lepes(j);
        }

        if (leptunk_e or elso_kiiras)
        {
            elso_kiiras = false;
            //system("CLEAR");
            KursorReset();

            for (int i = 0; i < j.magassag; i++)
            {
                for (int j = 0; j < szelsseg; j++)
                {
                    //"lenyek"
                    int jancsi_X = jancsi->getX();
                    int Jancsi_Y = jancsi->getY();

                    int ellllenseg_X = -1;
                    int ellllenseg_Y = -1;

                    if (boss) {
                        ellllenseg_X = boss->getX();
                        ellllenseg_Y = boss->getY();
                    }

                    if (jancsi_X == j and Jancsi_Y == i)
                    {
                        std::cout << "J";
                    }

                    else if (boss) {
                        if (ellllenseg_X == j and ellllenseg_Y == i)
                        {
                            std::cout << boss_jele;
                        }
                    }
                    else
                        std::cout << palya[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << "\nIRANYITAS: WASD, PALYA UJRAKEZDESE: R, KILEPES: Q/ESC\n";
            int volt_elet = jancsi->getElet();
            std::cout << "Eleteid: " << jancsi->getElet();
            if (volt_elet < jancsi->getElet())
            {
                std::cout << "\nTALALTAL EGY KINCSET, AZ ELETED NAGYOBB LETT " << jancsi->getElet() - volt_elet << "PONTTAL";
            }
        }
        if((jancsi->getX() == 0) or (jancsi->getX() == j.szelsseg) or (jancsi->getY() == 0) or (jancsi->getY() == magassag))
        {
            kilep = true;
            fin = true;
        }
    }
    if (!fin) 
    {
        system(CLEAR);
        std::cout << "Kileptel!";
        spause();
        exit(0);
    }
    system(CLEAR);
}
