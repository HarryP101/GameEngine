#include "Triangle.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

Triangle::Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) : vert1(v1), vert2(v2), vert3(v3) {}

Triangle& Triangle::operator+=(const Vector3D& rhs)
{
    vert1 = vert1 + rhs;
    vert2 = vert2 + rhs;
    vert3 = vert3 + rhs;

    return *this;
}

Triangle& Triangle::operator*=(const Matrix4x4& rhs)
{
    vert1 = vert1 * rhs;
    vert2 = vert2 * rhs;
    vert3 = vert3 * rhs;

    return *this;
}

Triangle& Triangle::operator*=(const Vector3D& xyzScaling)
{
    vert1 = vert1.Scale(xyzScaling);
    vert2 = vert2.Scale(xyzScaling);
    vert3 = vert3.Scale(xyzScaling);

    return *this;
}

Vector3D Triangle::GetCentroid() const
{
    double x = (vert1.GetX() + vert2.GetX() + vert3.GetX()) / 3.0;
    double y = (vert1.GetY() + vert2.GetY() + vert3.GetY()) / 3.0;
    double z = (vert1.GetZ() + vert2.GetZ() + vert3.GetZ()) / 3.0;

    return Vector3D(x, y, z);
}