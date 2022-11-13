#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

//#include <stdlib.h>

#include "jatekos.hpp"
#include "ellenseg.hpp"
#include "gyujteni.hpp"

#ifdef _WIN32
#define CLEAR "cls"
#include "Windowsra.hpp"
#else 
#define CLEAR "clear"
#include "linuxra.hpp"
#endif

class jatekmenet
{
private:
    bool kilep;
    int cp;
    char** palya;
    int magassag;
    int szelsseg;
    jatekos* jancsi;
    ellenseg* boss;
    gyujteni* coll;

public:
    jatekmenet() { kilep = false; cp = 0; palya = nullptr; magassag = 0; szelsseg = 0; jancsi = nullptr; boss = nullptr; coll = nullptr; }
    jatekmenet(int jancsiX, int jancsiY, int jancsihp, bool van_e_boss, int bossX, int bossY, int seb, char** palya, bool van_e_gyujteni, int collX, int collY, int mennyitad, bool meg)
    {
        //Jancsi letrehozasa
        jancsi = new jatekos(jancsiX, jancsiY, jancsihp);

        //boss letrehozasa
        if (van_e_boss)
        {
            boss = new ellenseg(bossX, bossY, seb);
        }
        else
        {
            boss = nullptr;
        }

        //gyujtogethetok letrehozasa
        if (van_e_gyujteni)
        {
            coll = new gyujteni(collX, collY, mennyitad, meg);
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
        for (int i = 0; i < magassag; i++)
        {
            delete[] palya[i];
        }
        delete[] palya;
    }

    int getCP() { return cp; }

    int getJElet() { return jancsi->getElet(); }

    jatekmenet& setKilep(bool kilepo);

    jatekmenet& setCP(int cpszam);

    void mentes(jatekmenet& jatekosunk);

    void mentes_be(std::string mentes_neve);

    jatekmenet& beolvas(jatekmenet& j, std::string palyanev);

    bool lepes(jatekmenet& j);

    void kiir(jatekmenet& j, char boss_jele);

};