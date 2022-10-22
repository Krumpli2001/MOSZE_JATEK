#include "Windows_Resz.hpp"

//jatekos reset
void jatekos::Reset()
{
    x = eredeti_x;
    y = eredeti_y;
}

jatekos& jatekos::setElet(int hp)
{
    elet = hp;
    return *this;
}

//jatekos iranyitasa
void jatekos::MozgasFel()
{
    y--;
}

void jatekos::MozgasLe()
{
    y++;
}

void jatekos::MozgasBalra()
{
    x--;
}

void jatekos::MozgasJobbra()
{
    x++;
}

//elenseg reset
void elenseg::Reset()
{
    x = eredeti_x;
    y = eredeti_y;
}

gyujteni& gyujteni::setX(int koordX)
{
    x = koordX;
    return *this;
}

gyujteni& gyujteni::setY(int koordX)
{
    y = koordX;
    return *this;
}

jatekmenet& jatekmenet::setCP(int cpszam)
{
    cp = cpszam;
    return *this;
}

//mentes
void jatekmenet::mentes(jatekos& jatekosunk, int mentes_szama)
{
    string file_nev;
    file_nev = "Jatek_Mentes " + mentes_szama;
    int cpszama;
    cpszama = getCP();
    int hpszama;
    hpszama = jatekosunk.getElet();
    ofstream f(file_nev);
    if (f.is_open())
    {
        f << cpszama << endl;
        f << hpszama << endl;
        f.close();
    }
    else
    {
        cerr << "\nMENTESI HIBA!\n";
    }

}

//mentett cp beolvasasa
void jatekmenet::mentes_be(jatekos& jatekosunk, int mentes_szama)
{
    string file_nev;
    file_nev = "Jatek_Mentes " + mentes_szama;
    ifstream f(file_nev);
    if (f.is_open())
    {
        string* data = new string[2];
        for (int i = 0; i < 2; i++)
        {
            getline(f, data[i]);
        }
        setCP(stoi(data[0]));
        jatekosunk.setElet(stoi(data[1]));
    }
    else
    {
        cerr << "\nNEM SIKERULT BETOLTENI A MENTEST\n";
    }
}

//palya beolvasasa
jatekmenet& jatekmenet::beolvas(jatekmenet& j, string palyanev)
{

    string egysor;

    ifstream f(palyanev);
    int karakterek = 0;
    int sorok = 0;


    if (f.is_open())
    {
        //palya meretenek meghatarozasa
        while (getline(f, egysor)) {

            //cout << egysor << endl;
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
        while (getline(f, egysor)) {
            for (int i = 0; i < karakterek; i++) {   
                j.palya[sor][i] = egysor[i];
            }
            sor++;
        }

    }
    f.close();
    //cout << endl << karakterek << endl << sorok << endl;

    /*for (int k = 0; k < sorok; k++) {
        for (int l = 0; l < karakterek; l++) {
            palya[k][l] = '0';
        }
    }*/

    //gyors teszt h beolvasta-e
   /* for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < karakterek; j++) {
            cout << palya[i][j];
        }
        cout << endl;
    }*/



    //system("pause");
    return *this;
}

//OMFG MOZOG!!!
bool jatekmenet::lepes(jatekmenet& j)
{

    int jancsi_X = jancsi->getX();
    int jancsi_Y = jancsi->getY();
    int elozo_jancsi_X = jancsi_X;
    int elozo_jancsi_Y = jancsi_Y;

    if (_kbhit())
    {
        char hit = _getch();
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
            kilep = true;
            return true;
        }
        if (hit == 'r')
        {
            jancsi->Reset();
            boss->Reset();
            return true;
        }
        else
        {
            cout << "\nHibas bemenet\n";
            return true;
        }

    }
    return false;
}

//palya kirajzolasa
void jatekmenet::kiir(jatekmenet& j)
{
    bool leptunk_e;
    while (true) {
        leptunk_e = false;

        leptunk_e = lepes(j);

        if (leptunk_e)
        {
            system("cls");

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
                        cout << "J";
                    }

                    else if (boss) {
                        if (ellllenseg_X == j and ellllenseg_Y == i)
                        {
                            cout << "S";
                        }
                    }
                    else
                        cout << palya[i][j];
                }
                cout << endl;
            }
        }
    }
}

//void jatekmenet::fut(jatekmenet& j)
//{
//    bool leptunk = true;
//    while (!kilep, leptunk)
//    {
//        kiir(j, leptunk);
//        leptunk = lepes(j);
//    }
//}