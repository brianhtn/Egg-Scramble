#include "Dummy.h"

Dummy::Dummy(int newId, int newx, int newy)
{
    x = newx;
    y = newy;
    id = newId;
}

Dummy::~Dummy(void)
{
    
}

void Dummy::move(int direction)
{
    switch (direction)
    {
        case MOVE_FORWARD:
            y++;
            break;

        case MOVE_BACKWARD:
            y--;
            break;

        case MOVE_LEFT:
            x--;
            break;

        case MOVE_RIGHT:
            x++;
            break;

        default:
            break;
    }
}

void Dummy::move(int newx, int newy)
{
    x = newx;
    y = newy;
}

int Dummy::getX()
{
    return x;
}

int Dummy::getY()
{
    return y;
}

int Dummy::getId()
{
    return id;
}