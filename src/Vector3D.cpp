#include "Vector3D.h"
#include <cstdint>
#include <iostream>

#if defined(__APPLE__)
    #include <cmath>
#else
    #include <math.h>
#endif

Vector3D::Vector3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {};

Vector3D::Vector3D(const Vector3D& rhs)
{
    m_x = rhs.m_x;
    m_y = rhs.m_y;
    m_z = rhs.m_z;
}

Vector3D Vector3D::Scale(const Vector3D& xyzScalingFactors) const
{
    return Vector3D(m_x * xyzScalingFactors.GetX(), m_y * xyzScalingFactors.GetY(), m_z * xyzScalingFactors.GetZ());
}

void Vector3D::Normalise()
{
    double magnitude = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    m_x /= magnitude;
    m_y /= magnitude;
    m_z /= magnitude;
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
    return Vector3D(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
    return Vector3D(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
}

// This shouldnt be a member function, as it does something unexpected
// Create new class "ProjectionHelper for example"
Vector3D Vector3D::operator*(const Matrix4x4& rhs) const
{
    double x = m_x * rhs.GetValue(0, 0) + m_y * rhs.GetValue(1, 0) + m_z * rhs.GetValue(2, 0) + rhs.GetValue(3, 0);
    double y = m_x * rhs.GetValue(0, 1) + m_y * rhs.GetValue(1, 1) + m_z * rhs.GetValue(2, 1) + rhs.GetValue(3, 1);
    double z = m_x * rhs.GetValue(0, 2) + m_y * rhs.GetValue(1, 2) + m_z * rhs.GetValue(2, 2) + rhs.GetValue(3, 2);

    double w = m_x * rhs.GetValue(0, 3) + m_y * rhs.GetValue(1, 3) + m_z * rhs.GetValue(2, 3) + rhs.GetValue(3, 3);

    if (w != 0.0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
    return Vector3D(x, y, z);
}

Vector3D Vector3D::Cross(const Vector3D& rhs) const
{
    double x = m_y * rhs.m_z - m_z * rhs.m_y;
    double y = m_z * rhs.m_x - m_x * rhs.m_z;
    double z = m_x * rhs.m_y - m_y * rhs.m_x;

    return Vector3D(x, y, z);
}

double Vector3D::Dot(const Vector3D& rhs) const
{
    return m_x * rhs.m_x + m_y * rhs.m_y + m_z * rhs.m_z;
}

double Vector3D::GetX() const { return m_x; }
double Vector3D::GetY() const { return m_y; }
double Vector3D::GetZ() const { return m_z; }

int32_t Vector3D::GetPixelX() const { return static_cast<int32_t>(m_x); }
int32_t Vector3D::GetPixelY() const { return static_cast<int32_t>(m_y); }
int32_t Vector3D::GetPixelZ() const { return static_cast<int32_t>(m_z); }
