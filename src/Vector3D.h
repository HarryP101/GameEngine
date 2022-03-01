#pragma once
#include <cstdint>
#include "Matrix4x4.h"
#include "ProjectionMatrix.h"

class Vector3D
{
public:
    Vector3D(double x, double y, double z);
    Vector3D(const Vector3D& copy);

    double GetX() const;
    double GetY() const;
    double GetZ() const;

    int32_t GetPixelX() const;
    int32_t GetPixelY() const;
    int32_t GetPixelZ() const;
    
    Vector3D Scale(const Vector3D& xyzScalingFactors) const;

    void Normalise();

    double Mag() const;

    Vector3D operator+(const Vector3D& rhs) const;
    Vector3D& operator+=(const Vector3D& rhs);

    Vector3D operator-(const Vector3D& rhs) const;
    Vector3D& operator-=(const Vector3D& rhs);

    Vector3D operator*(const Matrix4x4& rhs) const;
    Vector3D operator*(const ProjectionMatrix& rhs) const;
    Vector3D operator*(double scaling) const;

    Vector3D Cross(const Vector3D& rhs) const;

    double Dot(const Vector3D& rhs) const;

    static Vector3D IntersectPlane(const Vector3D& planePoint, Vector3D planeNormal, const Vector3D& lineStart, const Vector3D& lineEnd);

private:
    double m_x;
    double m_y;
    double m_z;        
};