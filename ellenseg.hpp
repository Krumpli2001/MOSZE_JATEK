#pragma once
#include "entity.hpp"

class Ellenseg : public Entity
{
private:
    int sebzes;
public:
    Ellenseg(int koordX, int koordY, int seb)
    {
        x = koordX;
        y = koordY;
        sebzes = seb;
    }
    ~Ellenseg() {};

    int getX() { return x; }
    int getY() { return y; }
    int getSebzes() { return sebzes; }
};