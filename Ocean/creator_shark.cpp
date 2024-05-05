#include "creator_shark.h"
#include "shark.h"

Unit* CreatorShark::CreateUnit(double x, double y) const
{
    return new Shark(x,y);
}
