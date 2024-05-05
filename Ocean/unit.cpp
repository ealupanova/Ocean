#include "unit.h"
#include <random>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include "plankton.h"
#include "fish.h"
#include "shark.h"

#include <windows.h>



bool Unit::GetPoint(std::vector<std::vector<Unit*>>& ocean, double& x_, double& y_, double notx, double noty, int step, bool (*comparator)(Unit*))
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(-1 * step, 1 * step); // distribute results between 1 and 6 inclusive.
    for (int i = 0; i < 3 * step * step; ++i)
    {
        try
        {
            double x = x_;
            double y = y_;
            double max_x = ocean.size();
            double max_y = ocean[0].size();
            double move_x = dist(gen);
            double move_y = dist(gen);
            x += move_x;
            y += move_y;
            /*if (x<0 || y<0 || x>max_x - 1 || y>max_y - 1)
                continue;*/
            int ix = x, iy = y, imx = max_x, imy = max_y;
            x = (ix % imx + imx) % imx;
            y = (iy % imy + imy) % imy;
			if (comparator(ocean[x][y]) && !(notx == x && noty == y))
			{

				x_ = x;
				y_ = y;
				return true;

			}
		}
        catch (std::exception rt)
        {
            std::cerr << rt.what() << std::endl;
        }
    }
    return false;
}

int Unit::CountNeighbours(std::vector<std::vector<Unit*>>& ocean, bool(*comparator)(Unit*))
{
    int res = 0;
    double x = GetX(), y = GetY();
    double max_x = ocean.size();
    double max_y = ocean[0].size();

    int ix = x, iy = y, imx = max_x, imy = max_y;
    
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			res += comparator(ocean[((ix + i)%imx+imx)%imx][((iy + j)%imy+imy)%imy]);
		}
	}
    
    return res;
}

void SetColor(int Fore, int Back)
{
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((Back << 4) | Fore));   
}

bool IsNull(Unit* punit)
{
    return !punit;
}

bool IsPlankton(Unit* punit)
{
    return punit && typeid(Plankton) == typeid(*punit);
}

bool IsFish(Unit* punit)
{
    return punit && typeid(Fish) == typeid(*punit);
}

bool IsShark(Unit* punit)
{
    return punit && typeid(Shark) == typeid(*punit);
}


