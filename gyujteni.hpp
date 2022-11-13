#pragma once
#include "entity.hpp"

class gyujteni : public entity
{
private:
    //int x, y;
    int mennyit_ad;
    bool megvolt;
public:
    gyujteni() { x = -1; y = -1; mennyit_ad = 0; megvolt = false; }
    gyujteni(int koordX, int koordY, int ad, bool meg)
    {
        x = koordX;
        y = koordY;
        mennyit_ad = ad;
        megvolt = meg;
    }
    ~gyujteni() {};

    int getX() { return x; }
    int getY() { return y; }
    int getMennyit_Ad() { return mennyit_ad; }
    bool getMegvolt() { return megvolt; }
    gyujteni& setMegvolt(bool m)
    {
        megvolt = m;
        return *this;
    }
};