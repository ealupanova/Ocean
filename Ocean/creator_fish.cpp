#include "creator_fish.h"
#include "fish.h"

Unit* CreatorFish::CreateUnit(double x, double y) const
{
    return new Fish(x,y);
}
