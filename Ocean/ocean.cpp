#include "ocean.h"
#include "plankton.h"
#include "fish.h"
#include "shark.h"

#include "creator.h"
#include "creator_plankton.h"
#include "creator_fish.h"
#include "creator_shark.h"
#include <random>
#include <iostream>
//#include <windows.h>
#include  "sfml/Graphics/Text.hpp"
#include <string>

int Ocean::ROWS = 40;
int Ocean::COLS = 150;
int Ocean::startPlankton = 500;
int Ocean::startFish = 100;
int Ocean::startShark = 15;
bool Ocean::isCenter = true;


//std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<Unit*>>& ocean)
//{
//    for (auto& row : ocean)
//    {
//        for (auto x : row)
//        {
//            if (x)
//                x->Print();
//            else
//                out << ' ';
//        }
//        out << std::endl;
//    }
//    return out;
//}



Ocean::Ocean() 
{
    for (int i = 0; i < ROWS; ++i)
    {
        std::vector<Unit*> temp(COLS);
        for (int j = 0; j < COLS; ++j)
        {
            temp[j] = nullptr;
        }
        ocean.push_back(temp);
    }
}

void Ocean::ColonizeOcean()
{
    std::vector<Creator*> fabrics;
    fabrics.push_back(new CreatorPlankton());
    fabrics.push_back(new CreatorFish());
    fabrics.push_back(new CreatorShark());
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, COUNT_ID-1); // distribute results between 0 and 2 inclusive.
    int count_units[COUNT_ID] = { 0,0,0 };
    int max_counts[COUNT_ID] = { 0,0,0 };
    max_counts[ID_PLANKTON] = startPlankton;
    max_counts[ID_FISH] = startFish;
    max_counts[ID_SHARK] = startShark;
    int total = startPlankton + startFish + startShark;
    int mx = ROWS;
    int my = COLS;
    if (isCenter)
    {
        mx /= 4;
        my /= 4;
    }
    std::uniform_int_distribution<> distX(0+mx*isCenter, ROWS-1-mx*isCenter); // distribute results between 0 and 2 inclusive.
    std::uniform_int_distribution<> distY(0+my*isCenter, COLS-1-my*isCenter); // distribute results between 0 and 2 inclusive.
    for (int i = 0; i < total; ++i)
    {
        int index = dist(gen);
        if (max_counts[index] == count_units[index])
        {
            --i;
            continue;
        }
        int x, y;
        do
        {
            x = distX(gen);
            y = distY(gen);
        } while (ocean[x][y]);
        units.push_back(fabrics[index]->CreateUnit(x, y));
        ocean[x][y] = units.back();
        count_units[index]++;
    }
    
}

void Ocean::Live(sf::RenderWindow& window, sf::Sprite& sprite)
{
    int step = 0;
    PrintOcean(window, sprite, step);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                std::cout << "Life is over by closing window at " << ++step << " step." << std::endl;
                return;
            }
        }
        std::list<Unit*> new_unit;       
        OceanLive(new_unit);
        if (PrintStateOcean(new_unit, step))
        {
            window.close();
            return;
        }
        //if(step%2)
        PrintOcean(window, sprite, step);    
        units = new_unit;  
        step++;
    }
}

void Ocean::PrintOcean(sf::RenderWindow& window, sf::Sprite& sprite, int step)
{
    std::cout << "Step: " << step << ". Plankton: " << Plankton::GetCount() << ". Fish: " << Fish::GetCount() << ". Shark: " << Shark::GetCount() << ". Total: " << units.size() << std::endl;
    extern int SIZE_RECT;
    window.clear();
    for (int i = 0; i < ocean.size(); ++i)
    {
        for (int j = 0; j < ocean[i].size(); ++j)
        {
            if (!ocean[i][j])
                sprite.setTextureRect(sf::IntRect(0, 0, SIZE_RECT, SIZE_RECT));
            else
            {
                int arr[2] = { 0 };
                ocean[i][j]->Print(arr);
                sprite.setTextureRect(sf::IntRect(
                    arr[0] * SIZE_RECT,
                    arr[1] * SIZE_RECT,
                    SIZE_RECT,
                    SIZE_RECT));              
            }
            sprite.setPosition(j * SIZE_RECT, i * SIZE_RECT);
            window.draw(sprite);
        }
    }
    sf::Font font;
    font.loadFromFile("COOPBL.TTF");
    std::string str = std::to_string(step);
    sf::Text text(str, font);
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Black);
    text.setPosition(0, 0);
    window.draw(text);
    window.display();

}

void Ocean::OceanLive(std::list<Unit*> &new_unit)
{
    //std::list<Unit*> new_unit;
    for (auto x : units)
    {
        if (x)
        {
            StepInfo info = x->Live(ocean);
            try
            {
                if (info.isAlive)
                {
                    new_unit.push_back(x);
                    try
                    {
                        if (info.isMoved)
                        {
                            ocean[x->GetX()][x->GetY()] = nullptr;
                            x->Move(info.x, info.y);
                            ocean[x->GetX()][x->GetY()] = x;
                        }
                    }
                    catch (std::exception& ex)
                    {
                        std::cerr << ex.what() << std::endl;
                    }
                    try
                    {
                        if (info.child)
                        {
                            new_unit.push_back(info.child);
                            ocean[info.child->GetX()][info.child->GetY()] = info.child;
                        }
                    }
                    catch (std::exception& ex)
                    {
                        std::cerr << ex.what() << std::endl;
                    }
                    try
                    {
                        if (info.eaten)
                        {
                            units.remove(info.eaten);
                            new_unit.remove(info.eaten);
                            //ocean[info.eaten->GetX()][info.eaten->GetY()] = nullptr;
                            delete info.eaten;
                        }
                    }
                    catch (std::exception& ex)
                    {
                        std::cerr << ex.what() << std::endl;
                    }
                }
                else
                {
                    ocean[x->GetX()][x->GetY()] = nullptr;
                    delete x;
                }
            }
            catch (std::exception& ex)
            {
                std::cerr << ex.what() << std::endl;
            }
        }
    }
    
}

int Ocean::PrintStateOcean(const std::list<Unit*>& new_unit, int step)
{
    if (new_unit.size() == 0)
    {
        std::cout << "Step: " << step << ". Live is over" << std::endl;
        return 1;
    }
    if (new_unit.size() >= ROWS * COLS)
    {
        std::cout << "Step: " << step << ". Ocean is overflow. Life is over" << std::endl;
        return 2;
    }
    if (Plankton::GetCount() == 0)
    {
        std::cout << "Step: " << step << ". Plankton and life is over" << std::endl;
        return 3;
    }
    if (Fish::GetCount() == 0)
    {
        std::cout << "Step: " << step << ". All fishes died. Life is over" << std::endl;
        return 4;
    }
    if (Shark::GetCount() == 0)
    {
        std::cout << "Step: " << step << ". All sharks died. Life is over" << std::endl;
        return 5;
    }
    return 0;
}
