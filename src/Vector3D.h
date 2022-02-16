#pragma once

class Vector3D
{
public:
    Vector3D(double x, double y, double z);
    Vector3D(const Vector3D& copy);

    Vector3D operator+(const Vector3D& rhs) const;
private:
    double m_x;
    double m_y;
    double m_z;        
};