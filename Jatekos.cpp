#include "jatekos.hpp"

//Jatekos reset
void Jatekos::Reset()
{
    x = eredeti_x;
    y = eredeti_y;
}

Jatekos& Jatekos::setElet(int hp)
{
    elet = hp;
    return *this;
}

//Jatekos iranyitasa
void Jatekos::MozgasFel()
{
    y--;
}

void Jatekos::MozgasLe()
{
    y++;
}

void Jatekos::MozgasBalra()
{
    x--;
}

void Jatekos::MozgasJobbra()
{
    x++;
}