#include "Fish.h"

Fish::Fish(float x, float y, float dx, float dy)
            : Triangle::Triangle(x, y)
{
    this->dx = dx;
    this->dy = dy;
}