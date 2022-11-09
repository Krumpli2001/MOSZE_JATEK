#pragma once

class entity
{
protected:
    int x, y;
public:
    entity() { x = 0; x = 0; }
    entity(int koordX, int koordY)
    {
        x = koordX;
        y = koordY;
    }
    //virtual ~entity() {};

    //virtual void func() =0;

    int getX() { return x; }
    int getY() { return y; }

};