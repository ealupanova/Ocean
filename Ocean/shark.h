#pragma once
#include "unit.h"

class Shark:public Unit
{
public:
	Shark(double x, double y) :Unit(x, y) { count_shark++; }
	~Shark() { count_shark--; }
	static int GetCount() { return count_shark; }
	virtual StepInfo Live(std::vector<std::vector<Unit*>>&) override;
	static void SetMaxAge(int age) { max_age = age; }
	static void SetMaxStep(int step) { max_step = step; }
	static void SetReproductionTime(int rep_time) { reproduction_time = rep_time; }
	static void SetReproductionFreq(int rep_freq) { reproduction_freq = rep_freq; }
	static void SetHungryFreq(int hung_freq) { hungry_freq = hung_freq; }
	static void SetHungryMax(int hung_max) { hungry_max = hung_max; }
	static void SetMaxView(int view) { max_view = view; }
	static void SetCountNeighbours(int count_neigh) { count_neighbours = count_neigh; }
	static void SetHungryReproduction(int hungry_reprod) { hungry_reproduction = hungry_reprod; }
	virtual void Print(int* arr)const override;
private:
	static int count_shark;
	static int max_age;
	static int max_step;
	static int reproduction_time;
	static int reproduction_freq;
	static int hungry_freq;
	static int hungry_max;
	static int max_view;
	static int count_neighbours;
	static int hungry_reproduction;
};

