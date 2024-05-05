#pragma once

class Unit;

struct StepInfo
{
	bool isAlive = true;
	Unit* child = nullptr;
	Unit* eaten = nullptr;
	bool isMoved = false;
	double x=0, y=0;
};

