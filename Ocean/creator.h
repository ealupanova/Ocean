#pragma once

enum UnitID { ID_PLANKTON, ID_FISH, ID_SHARK, COUNT_ID };

#include "unit.h"


class Creator
{
public:
	virtual Unit* CreateUnit(double x, double y)const = 0;
};

