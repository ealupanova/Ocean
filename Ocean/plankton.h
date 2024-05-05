#pragma once
#include "unit.h"

class Plankton :
    public Unit
{
public:
    Plankton(double x, double y) :Unit(x, y) { count_plankton++; }
    virtual ~Plankton() { count_plankton--; }
    virtual StepInfo Live(std::vector<std::vector<Unit*>>& ocean) override;
    virtual void Print(int* arr)const override;
    static void SetMaxAge(int age) { max_age = age; }
    static void SetMaxStep(int step) { max_step = step; }
    static void SetReproductionTime(int rep_time) { reproduction_time = rep_time; }
    static void SetReproductionFreq(int rep_freq) { reproduction_freq = rep_freq; }
    static void SetCountNeighbours(int count_neigh) { count_neighbours = count_neigh; }
    static int GetCount() { return count_plankton; }
private:
    static int max_age;
    static int max_step;
    static int reproduction_time;
    static int reproduction_freq;
    static int count_plankton;
    static int count_neighbours;
};

