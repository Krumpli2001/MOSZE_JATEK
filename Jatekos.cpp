#include "jatekos.hpp"

//jatekos reset
void jatekos::Reset()
{
    x = eredeti_x;
    y = eredeti_y;
}

jatekos& jatekos::setElet(int hp)
{
    elet = hp;
    return *this;
}

//jatekos iranyitasa
void jatekos::MozgasFel()
{
    y--;
}

void jatekos::MozgasLe()
{
    y++;
}

void jatekos::MozgasBalra()
{
    x--;
}

void jatekos::MozgasJobbra()
{
    x++;
}