#include "creator_plankton.h"
#include "plankton.h"

Unit* CreatorPlankton::CreateUnit(double x, double y) const
{
    return  new Plankton(x, y);
}
