#pragma once
#include <vector>
#include "step_info.h"


enum Colors {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

class Unit
{
	struct Point
	{
		double x, y;
		Point(double x, double y) :x(x), y(y) {}
	};
public:
	Unit(double x, double y) :coord(x, y), age(0), eated(0) {}
	virtual ~Unit() {}
	void Move(double x, double y) { this->coord.x = x; this->coord.y = y; }
	double GetX()const { return coord.x; }
	double GetY()const { return coord.y; }
	Point& Coord() { return coord; }
	Point Coord() const { return coord; }
	virtual StepInfo Live(std::vector<std::vector<Unit*>>&) = 0;
	int GrowUp() { return ++age; }
	int GetAge()const { return age; }
	int GetEated()const { return eated; }
	void SetEated() { eated = 0; }
	int MoreHungry() { return ++eated; }
	virtual void Print(int * arr)const = 0;
protected:
	bool GetPoint(std::vector<std::vector<Unit*>>& ocean, double& x, double& y, double notx, double noty, int step, bool (*comparator)(Unit*));
	int CountNeighbours(std::vector<std::vector<Unit*>>& ocean, bool (*comparator)(Unit*));
	
private:
	Point coord;
	int age;
	int eated;
};

bool IsNull(Unit* punit);

bool IsPlankton(Unit* punit);

bool IsFish(Unit* punit);

void SetColor(int Fore, int Back);