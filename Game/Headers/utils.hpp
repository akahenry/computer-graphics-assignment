#pragma once

#include <vector>
#include <vector.hpp>
#include <object.hpp>
#include <math.h>

namespace MovementUtility
{
    Vector3 Bezier(std::vector<Vector3> controlPoints, float t);
};