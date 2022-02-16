#pragma once
#include <cstdint>

class Vector3D
{
public:
    Vector3D(int32_t x, int32_t y, int32_t z);
    Vector3D(const Vector3D& copy);

    int32_t GetX() const;
    int32_t GetY() const;
    int32_t GetZ() const;

    Vector3D operator+(const Vector3D& rhs) const;
private:
    int32_t m_x;
    int32_t m_y;
    int32_t m_z;        
};