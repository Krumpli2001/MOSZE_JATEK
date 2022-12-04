#pragma once
#include "entity.hpp"

class ellenseg : public entity
{
private:
    int sebzes;
public:
    ellenseg(int koordX, int koordY, int seb)
    {
        x = koordX;
        y = koordY;
        sebzes = seb;
    }
    ~ellenseg() {};

    int getX() { return x; }
    int getY() { return y; }
    int getSebzes() { return sebzes; }
};