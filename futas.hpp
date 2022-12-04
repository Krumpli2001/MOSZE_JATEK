#pragma once

#include "jatekmenet.hpp"

int kezdes();

void story_be(std::string CH);

void story_kerdesek(std::ifstream& f, int pos);

void palya_letrehoz(jatekmenet* j, int jancsiX, int jancsiY, int* ghp, bool van_e_boss, int bossX, int bossY, int seb, int* gsebzes, char** palya, int mennyi_coll, int coll1X, int coll1Y, int coll1M, int coll2X, int coll2Y, int coll2M, int coll3X, int coll3Y, int coll3M, std::string palya_neve, char boss_char);

void run(int fut);

