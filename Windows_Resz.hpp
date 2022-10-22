#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <Windows.h>


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

class gyujteni
{
private:
    int x, y;
public:
    gyujteni() { x = -1; y = -1; }
    gyujteni(int koordX, int koordY)
    {
        x = koordX;
        y = koordY;
    }

    int getX() { return x; }
    int getY() { return y; }
    gyujteni& setX( int x );
    gyujteni& setY( int y );
};

class jatekmenet
{
private:
    bool kilep;
    int cp;
    int mentes_szama;
    char** palya;
    int magassag;
    int szelsseg;
    jatekos* jancsi;
    elenseg* boss;
    gyujteni* coll;

public:
    jatekmenet() { kilep = false; cp = 0; mentes_szama = 0; palya = nullptr; magassag = 0; szelsseg = 0; jancsi = nullptr; boss = nullptr; coll = nullptr; }
    jatekmenet(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, char** palya, bool van_e_gyujteni, int collX, int collY)
    {
        //Jancsi letrehozasa
        jancsi = new jatekos(jancsiX, jancsiY, jancsihp);

        //boss letrehozasa
        if (van_e_boss)
        {
            boss = new elenseg(bossX, bossY);
        }
        else
        {
            boss = nullptr;
        }

        //gyujtogethetok letrehozasa
        if (van_e_gyujteni)
        {
            coll = new gyujteni(collX, collY);
        }
        else
        {
            coll = nullptr;
        }

        kilep = false;

        cp = 0;

        mentes_szama = 0;

        palya = nullptr;
        magassag = 0;
        szelsseg = 0;
    }
    ~jatekmenet()
    {
        delete jancsi;
        if (boss) { delete boss; }
        if (coll) { delete coll; }
    }

    int getCP() { return cp; }
    int getM_S() { return mentes_szama; }

    jatekmenet& setCP( int cpszam );

    void mentes(jatekos& jatekosunk, int mentes_szama);

    void mentes_be(jatekos& jatekosunk, int mentes_szama);

    jatekmenet& beolvas(jatekmenet& j, string palyanev);

    bool lepes(jatekmenet& j);

    void kiir(jatekmenet& j);

    //void fut(jatekmenet& j);

};