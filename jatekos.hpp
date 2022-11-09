#pragma once
#include "entity.hpp"

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