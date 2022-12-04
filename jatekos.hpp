#pragma once
#include "entity.hpp"

class Jatekos : public Entity
{
private:
    int eredeti_x, eredeti_y;
    int elet;
public:
    Jatekos(int koordX, int koordY, int hp)
    {
        eredeti_x = koordX;
        eredeti_y = koordY;
        x = koordX;
        y = koordY;
        elet = hp;
    }
    ~Jatekos() {};

    void Reset();
    int getX() { return x; }
    int getY() { return y; }
    int getElet() { return elet; }
    Jatekos& setElet(int hp);
    void MozgasFel();
    void MozgasLe();
    void MozgasBalra();
    void MozgasJobbra();
};