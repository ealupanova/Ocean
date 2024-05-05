#pragma once
#include "creator.h"


class CreatorPlankton:public Creator {
public:
	virtual Unit* CreateUnit(double x, double y)const override;

};