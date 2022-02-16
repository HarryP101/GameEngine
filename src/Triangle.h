#pragma once

#include "Vector3D.h"

struct Triangle
{
    Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) : vert1(v1), vert2(v2), vert3(v3) {}

    Vector3D vert1;
    Vector3D vert2;
    Vector3D vert3;    
};