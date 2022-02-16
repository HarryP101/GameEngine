#include "Vector3D.h"

Vector3D::Vector3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {};

Vector3D::Vector3D(const Vector3D& rhs)
{
    m_x = rhs.m_x;
    m_y = rhs.m_y;
    m_z = rhs.m_z;
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
    return Vector3D(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
}
