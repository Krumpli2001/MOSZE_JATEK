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

void jatekmenet::setCP(int cpszam)
{
    cp = cpszam;
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
void jatekmenet::beolvas(string palyanev, jatekmenet& j)
{
    ifstream f(palyanev);
    string sor;
    if (f.is_open())
    {
        while (getline(f, sor))
        {
            for (int i = 0; i < MAGASSAG; i++)
            {
                for (int j = 0; j < SZELESSEG; j++)
                {
                    palya[i][j] = sor[j];
                }
            }

        }
    }
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
void jatekmenet::kiir(jatekmenet& j, bool leptunk_e)
{
    if (leptunk_e)
    {
        system("cls");
    }
    for (int i = 0; i < MAGASSAG; i++)
    {
        for (int j = 0; j < SZELESSEG; j++)
        {
            //"lenyek"
            int jancsi_X = jancsi->getX();
            int Jancsi_Y = jancsi->getY();
            int ellllenseg_X = boss->getX();
            int ellllenseg_Y = boss->getY();

            if (jancsi_X == j and Jancsi_Y == i)
            {
                cout << "J";
            }
            else if (ellllenseg_X == j and ellllenseg_Y == i)
            {
                cout << "S";
            }
            else
                cout << palya[i][j];
        }
        cout << endl;
    }
}

void jatekmenet::fut(jatekmenet& j)
{
    bool leptunk = true;
    while (!kilep, leptunk)
    {
        kiir(j, leptunk);
        leptunk = lepes(j);
    }
}