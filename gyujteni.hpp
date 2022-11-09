#pragma once
#include "entity.hpp"

class gyujteni : public entity
{
private:
    //int x, y;
    int mennyit_ad;
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