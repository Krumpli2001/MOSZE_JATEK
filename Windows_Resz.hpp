#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <filesystem>
#include <ShlObj_core.h>

#define MAGASSAG 21
#define SZELESSEG 54

using namespace std;

class jatekos
{
private:
	int x, y;
	int eredeti_x, eredeti_y;
    int elet;
public:
    jatekos(int koordX, int koordY, int hp)
    {
        eredeti_x = koordX;
        eredeti_y = koordY;
        x = koordX;
        y = koordY;
        elet = hp;
    }

    void Reset();
    int getX() { return x; }
    int getY() { return y; }
    int getElet() { return elet; }
    jatekos& setElet(int hp);
    void MozgasFel();
    void MozgasLe();
    void MozgasBalra();
    void MozgasJobbra();
};

class elenseg
{
private:
    int x, y;
    int eredeti_x, eredeti_y;
public:
    elenseg(int koordX, int koordY)
    {
        eredeti_x = koordX;
        eredeti_y = koordY;
        x = koordX;
        y = koordY;
    }

    void Reset();
    int getX() { return x; }
    int getY() { return y; }
};

class jatekmenet
{
private:
    bool kilep;
    int cp;
    int mentes_szama;
    char palya[MAGASSAG][SZELESSEG];
    jatekos* jancsi;
    elenseg* boss;
public:
    jatekmenet()
    {
        jancsi = new jatekos(1,2,3);
        boss = new elenseg(15, 20);
        kilep = false;
        cp = 0;
        mentes_szama = 0;
        for (int i = 0; i < MAGASSAG; i++)
        {
            for (int j = 0; j < SZELESSEG; j++)
            {
                palya[i][j] = '0';
            }
        }
    }
    ~jatekmenet()
    {
        delete jancsi;
        delete boss;
    }
    int getCP() { return cp; }
    void setCP( int cpszam );
    int getM_S() { return mentes_szama; }
    void mentes(jatekos& jatekosunk, int mentes_szama);
    void mentes_be(jatekos& jatekosunk, int mentes_szama);
    void beolvas(string palyanev, jatekmenet& j);
    bool lepes(jatekmenet& j);
    void kiir(jatekmenet& j, bool leptunk_e);
    void fut(jatekmenet& j);

};