#pragma once
#include "entity.hpp"

class Gyujteni : public Entity
{
private:
    int mennyit_ad;
    bool megvolt;
public:
    Gyujteni() { x = -1; y = -1; mennyit_ad = 0; megvolt = false; }
    Gyujteni(int koordX, int koordY, int ad, bool meg)
    {
        x = koordX;
        y = koordY;
        mennyit_ad = ad;
        megvolt = meg;
    }
    ~Gyujteni() {};

    int getX() { return x; }
    int getY() { return y; }
    Gyujteni& setX(int sX)
    {
        x = sX;
        return *this;
    }
    Gyujteni& setY(int sY)
    {
        y = sY;
        return *this;
    }
    Gyujteni& setAD(int A)
    {
        mennyit_ad = A;
        return *this;
    }
    
    Gyujteni& setMegvolt(bool m)
    {
        megvolt = m;
        return *this;
    }

    int getMennyit_Ad() { return mennyit_ad; }
    bool getMegvolt() { return megvolt; }
};