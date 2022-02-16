#include "Vector3D.h"
#include <cstdint>

Vector3D::Vector3D(int32_t x, int32_t y, int32_t z) : m_x(x), m_y(y), m_z(z) {};

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

int32_t Vector3D::GetX() const { return m_x; }
int32_t Vector3D::GetY() const { return m_y; }
int32_t Vector3D::GetZ() const { return m_z; }