#pragma once

class Entity
{
protected:
    int x, y;
public:
    Entity() { x = 0; y = 0; }
    Entity(int koordX, int koordY)
    {
        x = koordX;
        y = koordY;
    }

    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual ~Entity() {};
};