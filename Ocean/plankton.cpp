#include "plankton.h"

#include <iostream>

int Plankton::max_age = 4;
int Plankton::max_step = 2;
int Plankton::reproduction_time = 1;
int Plankton::reproduction_freq = 1;
int Plankton::count_plankton = 0;
int Plankton::count_neighbours = 7;



StepInfo Plankton::Live(std::vector<std::vector<Unit*>>& ocean)
{
    StepInfo info;
    info.isAlive = true;
    info.child = nullptr;
    info.eaten = nullptr;
    if (GrowUp() == max_age)
    {
        info.isAlive = false;
        return info;
    }
    double x=GetX(), y = GetY();
        
    if (GetAge() >= reproduction_time)
    {
        if ((GetAge() - reproduction_time) % reproduction_freq == 0)
        {
            if (CountNeighbours(ocean, IsPlankton) < count_neighbours)
            {
                if (GetPoint(ocean, x, y, GetX(), GetY(), max_step, IsNull))
                {
                    info.child = new Plankton(x, y);
                }
            }
        }
    }
    double x1 = GetX();
    double y1 = GetY();
    if (GetPoint(ocean, x1, y1, x, y, max_step, IsNull))
    {
        info.isMoved = true;
        info.x = x1;
        info.y = y1;
    }
    return info;
}

void Plankton::Print(int* arr) const
{ 
   /* if (GetAge() < 2)
        SetColor(LightGreen, White);
    else
        SetColor(Brown, White);
    std::cout << '*';*/

    arr[0] = 1;
}



