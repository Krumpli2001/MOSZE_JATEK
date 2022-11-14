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

    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual ~entity() {};

};