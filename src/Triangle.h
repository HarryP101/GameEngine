#pragma once

#include "Vector3D.h"
#include "Matrix4x4.h"

struct Triangle
{
    Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

    Triangle& operator+=(const Vector3D& rhs);
    Triangle& operator*=(const Matrix4x4& rhs);
    Triangle& operator*=(const Vector3D& xyzScaling);

    Vector3D vert1;
    Vector3D vert2;
    Vector3D vert3;    
};