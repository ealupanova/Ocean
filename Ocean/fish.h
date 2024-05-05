#pragma once
#include "unit.h"

class Fish:public Unit
{
public:
    Fish(double x, double y) :Unit(x, y) { count_fish++; }
    virtual ~Fish() { count_fish--; }
    virtual StepInfo Live(std::vector<std::vector<Unit*>>& ocean) override;
    virtual void Print(int* arr)const override;
    static void SetMaxAge(int age) { max_age = age; }
    static void SetMaxStep(int step) { max_step = step; }
    static void SetReproductionTime(int rep_time) { reproduction_time = rep_time; }
    static void SetReproductionFreq(int rep_freq) { reproduction_freq = rep_freq; }
    static void SetHungryFreq(int hung_freq) { hungry_freq = hung_freq; }
    static void SetHungryMax(int hung_max) { hungry_max = hung_max; }
    static void SetMaxView(int view) { max_view = view; }
    static int GetCount() { return count_fish; }
    static void SetCountNeighbours(int count_neigh) { count_neighbours = count_neigh; }
private:
    static int max_age;
    static int max_step;
    static int reproduction_time;
    static int reproduction_freq;
    static int hungry_freq;
    static int hungry_max;
    static int max_view;
    static int count_fish;
    static int count_neighbours;
};

