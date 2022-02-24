#include "Triangle.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "ProjectionMatrix.h"

Triangle::Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) : vert1(v1), vert2(v2), vert3(v3), normal(0.0, 0.0, 0.0) 
{
    Vector3D line1 = vert2 - vert1;
    Vector3D line2 = vert3 - vert1;

    normal = line1.Cross(line2);
    normal.Normalise();
}

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

Triangle& Triangle::operator*=(const ProjectionMatrix& rhs)
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

bool Triangle::CanBeSeen(const Vector3D& camera) const
{
    return (normal.Dot(vert1 - camera)) < 0.0;
}