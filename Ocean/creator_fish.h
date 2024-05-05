#pragma once
#include "creator.h"


class CreatorFish :public Creator {
public:
	virtual Unit* CreateUnit(double x, double y)const override;

};