#pragma once

#include "creator.h"


class CreatorShark :public Creator {
public:
	virtual Unit* CreateUnit(double x, double y)const override;

};