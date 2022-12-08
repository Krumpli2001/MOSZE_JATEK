#pragma once

#include "jatekmenet.hpp"
#include "global.hpp"

int kezdes();

void costum_palya();

void story_be(std::string CH);

void story_kerdesek(std::ifstream& f, int pos);

bool palya_letrehoz(Global* g, int jancsiX, int jancsiY, bool van_e_boss, int bossX, int bossY, int seb, char** palya, int mennyi_coll, int coll1X, int coll1Y, int coll1M, int coll2X, int coll2Y, int coll2M, int coll3X, int coll3Y, int coll3M, std::string palya_neve, char boss_char);

void kilep(Global* g, bool fin, std::ifstream& f);

void kilep(Global* g, bool fin);

void run(int fut);

