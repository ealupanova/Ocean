#include "fish.h"

#include <iostream>
#include <cmath>

int Fish::max_age = 14;
int Fish::max_step = 2;
int Fish::max_view = 4;
int Fish::reproduction_time = 4;
int Fish::reproduction_freq = 3;
int Fish::hungry_freq = 1;
int Fish::hungry_max = 5;
int Fish::count_fish = 0;
int Fish::count_neighbours = 3;

StepInfo Fish::Live(std::vector<std::vector<Unit*>>& ocean)
{
    StepInfo info;
    info.isAlive = true;
    info.child = nullptr;
    info.eaten = nullptr;
    info.isMoved = false;
    //std::cout << "Fish: " << GetX() << ", " << GetY() << "; ";
    if (GrowUp() == max_age)
    {
        info.isAlive = false;
       // std::cout << "Died" << std::endl;
        return info;
    }
    double xp = GetX(), yp = GetY();
    if (MoreHungry() == hungry_max)
    {
        info.isAlive = false;
        //std::cout << "Died" << std::endl;
        return info;
    }

    if (GetEated() >= hungry_freq)
    {
       // std::cout << "Try to eat: ";
        int i = 1;
        for (; i <= max_step; ++i)
        {
            try
            {
                if (GetPoint(ocean, xp, yp, GetX(), GetY(), i, IsPlankton))
                {
                   // std::cout << xp << ", " << yp << "; ";
                    info.eaten = ocean[xp][yp];
                    info.isMoved = true;
                    info.x = xp;
                    info.y = yp;
                    SetEated();
                    
                    break;
                }
            }
            catch (std::exception ex)
            {
                std::cerr << ex.what() << std::endl;
                break;
            }
        }
        if (i > max_step)
        {
            
            for (; i <= max_view; ++i)
            {
                if (GetPoint(ocean, xp, yp, GetX(), GetY(), i, IsPlankton))
                {
                    //std::cout << "Out of step" << xp << ", " << yp << "; ";
                    double move_x = xp - GetX();
                    double move_y = yp - GetY();
                    
                    if (abs(move_x)<=max_step && abs(move_y)<=max_step)
                    {
                        try
                        {
                           // std::cout << "Try to go" << xp << ", " << yp << "; ";
                            info.eaten = ocean[xp][yp];
                            info.isMoved = true;
                            info.x = xp;
                            info.y = yp;
                            SetEated();
                            break;
                        }
                        catch (std::exception rt)
                        {
                            std::cerr << rt.what() << std::endl;
                            break;
                        }
                    }
                    else if (abs(move_x) <= max_step)
                    {
						try
						{
							int sign = move_y > 0 ? 1 : -1;
							double ty = max_step * sign;
                           // std::cout << "Try to go" << xp << ", " << ty + GetY() << "; ";
							while (ty && ocean[xp][ty + GetY()] != nullptr)
							{                 
								ty>0?ty--:ty++;
                               // std::cout << "Try to go" << xp << ", " << ty + GetY() << "; ";
							}
							//if (ty)
							//{
                               // std::cout << "Try to go" << xp << ", " << ty + GetY() << "; ";
								info.isMoved = true;
								info.x = xp;
                                int iy = ty + GetY();
                                int imy = ocean[0].size();            
								info.y = (iy % imy + imy) % imy; //ty + GetY();
								break;
							//}
						}

						catch (std::exception rt)
						{
							std::cerr << rt.what() << std::endl;
							break;
						}
                    }
                    else if (abs(move_y) <= max_step)
                    {
                        try
                        {
                            int sign = move_x > 0 ? 1 : -1;
                            double tx = max_step * sign;
                           // std::cout << "Try to go" << tx + GetX() << ", " << yp << "; ";
                            while (tx && ocean[tx + GetX()][yp] != nullptr)
                            {
                                tx>0?tx--:tx++;
                                //std::cout << "Try to go" << tx + GetX() << ", " << yp << "; ";
                            }
                            //if (tx)
                            //{
                               // std::cout << "Try to go" << tx + GetX() << ", " << yp << "; ";
                                info.isMoved = true;
                                int ix= tx + GetX();
                                int imx = ocean.size();
                                info.x = (ix % imx + imx) % imx; 
                                //info.x = tx + GetX();
                                info.y = yp;
                                break;
                            //}
                        }
                        catch (std::exception rt)
                        {
                            std::cerr << rt.what() << std::endl;
                            break;
                        }
                    }
                }
            }
        }
    }
    double x = GetX(), y = GetY();
    
    if (GetAge() >= reproduction_time)
    {
		if ((GetAge() - reproduction_time) % reproduction_freq == 0)
		{
            if (CountNeighbours(ocean, IsFish) < count_neighbours)
            {
                try
                {
                    if (GetPoint(ocean, x, y, xp, yp, max_step, IsNull))
                    {
                        //std::cout << "Child at " << x << ", " << y << "; ";
                        info.child = new Fish(x, y);
                    }
                    else if (GetPoint(ocean, x, y, xp, yp, max_step, IsPlankton))
                    {
                        //std::cout << "Child at " << x << ", " << y << " and eated plankton; ";
                        info.child = new Fish(x, y);
                        info.eaten = ocean[x][y];
                    }
                }
                catch (std::exception ex)
                {
                    std::cerr << ex.what() << std::endl;
                }
            }

		}
    }
    double x1 = GetX(), y1 = GetY();
    
    if (!info.isMoved && GetPoint(ocean, x1, y1, x, y, max_step, IsNull))
    {
        info.isMoved = true;
      //  std::cout << "Moved " << x1 << ", " << y1 << "; ";
        info.x = x1;
        info.y = y1;
    }
    //std::cout << std::endl;
    return info;
}

void Fish::Print(int* arr) const
{
    /*if (GetEated() == hungry_max-1 || GetAge() == max_age-1)
    {
        SetColor(Brown, White);
    }
    else if (GetEated() >= hungry_freq)
    {
        SetColor(Red, White);
    }
    else if (GetAge() <= 1)
    {
        SetColor(Green, White);
    }
    else
    {
        SetColor(LightBlue, White);
    }
    std::cout << '#';*/

    arr[0] = arr[1] = 1;
}
