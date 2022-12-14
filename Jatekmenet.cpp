#include "jatekmenet.hpp"

Jatekmenet& Jatekmenet::setKilep(bool kilepo)
{
    kilep = kilepo;
    return *this;
}

void Jatekmenet::gyujteni_be(int X, int Y, int M, int darab)
{
    coll[darab].setX(X);
    coll[darab].setY(Y);
    coll[darab].setAD(M);
}

void Jatekmenet::megvan_e(int i)
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

//palya beolvasasa
Jatekmenet& Jatekmenet::beolvas(Jatekmenet& j, std::string palyanev)
{

    std::string egysor;

    std::ifstream f(palyanev);
    int karakterek = 0;
    int sorok = 0;


    if (f.is_open())
    {
        //palya meretenek meghatarozasa
        while (std::getline(f, egysor)) {
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
bool Jatekmenet::lepes(Jatekmenet& j)
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
            setKilep(true);
            return true;
        }
        if (hit == 'r')
        {
            jancsi->Reset();
            return true;
        }
    return false;
}

//palya kirajzolasa
bool Jatekmenet::kiir(Jatekmenet& j, char boss_jele)
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
            KursorReset();
            for (int i = 0; i < j.magassag; i++)
            {
                for (int j = 0; j < szelsseg; j++)
                {
                    bool volt_kiiras = false;

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
                        volt_kiiras = true;
                    }

                    if (boss) {
                        if (ellllenseg_X == j and ellllenseg_Y == i)
                        {
                            std::cout << boss_jele;
                            volt_kiiras = true;
                        }
                    }

                    if (!volt_kiiras)
                    {
                        std::cout << palya[i][j];
                    }
                }
                std::cout << std::endl;
            }
            std::cout << "\nIRANYITAS: WASD, PALYA UJRAKEZDESE: R, KILEPES: Q/ESC\n";
            std::cout << "Eleteid: " << jancsi->getElet();
        }
        if((jancsi->getX() == 0) or (jancsi->getX() == (j.szelsseg-1)) or (jancsi->getY() == 0) or (jancsi->getY() == (j.magassag-1)))
        {
            kilep = true;
            fin = true;
        }
        if (boss)
        {
             if((jancsi->getX() == boss->getX()) and (jancsi->getY() == boss->getY()))
             {
                 kilep = true;
                 fin = true;
             }
        }
    }
    if (!fin) 
    {
        system(CLEAR);
        std::cout << "\nKileptel!\n";
        spause();
    }
    system(CLEAR);
    return fin;
}
