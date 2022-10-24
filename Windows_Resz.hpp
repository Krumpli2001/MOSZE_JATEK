#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <Windows.h>


using namespace std;

class entity
{
protected:
    int x, y;
public:
    entity() { x = 0; x = 0; }
    entity(int koordX, int koordY)
    {
        x = koordX;
        y = koordY;
    }
    //virtual ~entity() {};

    //virtual void func() =0;

    int getX() { return x; }
    int getY() { return y; }

};

class jatekos : public entity
{
private:
	//int x, y;
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
    ~jatekos() {};

    void Reset();
    //int getX() { return x; }
    //int getY() { return y; }
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
    int x, y, sebzes;
public:
    elenseg(int koordX, int koordY, int seb)
    {
        x = koordX;
        y = koordY;
        sebzes = seb;
    }
    ~elenseg() {};

    int getX() { return x; }
    int getY() { return y; }
};

class gyujteni
{
private:
    int x, y, mennyit_ad;
public:
    gyujteni() { x = -1; y = -1; mennyit_ad = 0; }
    gyujteni(int koordX, int koordY, int ad)
    {
        x = koordX;
        y = koordY;
        mennyit_ad = ad;
    }
    ~gyujteni() {};

    int getX() { return x; }
    int getY() { return y; }
    int getMennyit_Ad() { return mennyit_ad; }
};

class jatekmenet
{
private:
    bool kilep;
    int cp;
    char** palya;
    int magassag;
    int szelsseg;
    jatekos* jancsi;
    elenseg* boss;
    gyujteni* coll;

public:
    jatekmenet() { kilep = false; cp = 0; palya = nullptr; magassag = 0; szelsseg = 0; jancsi = nullptr; boss = nullptr; coll = nullptr; }
    jatekmenet(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya, bool van_e_gyujteni, int collX, int collY, int mennyitad)
    {
        //Jancsi letrehozasa
        jancsi = new jatekos(jancsiX, jancsiY, jancsihp);

        //boss letrehozasa
        if (van_e_boss)
        {
            boss = new elenseg(bossX, bossY, seb);
        }
        else
        {
            boss = nullptr;
        }

        //gyujtogethetok letrehozasa
        if (van_e_gyujteni)
        {
            coll = new gyujteni(collX, collY, mennyitad);
        }
        else
        {
            coll = nullptr;
        }

        kilep = false;

        cp = 0;

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

    jatekmenet& setKilep(bool kilepo);

    jatekmenet& setCP( int cpszam );

    void mentes(jatekmenet& jatekosunk);

    void mentes_be(string mentes_neve);

    jatekmenet& beolvas(jatekmenet& j, string palyanev);

    bool lepes(jatekmenet& j);

    void kiir(jatekmenet& j, char boss_jele);

};