#pragma once

#include "Vector3D.h"
#include "Matrix4x4.h"

// Defines the cameras location and orientation in space
class Camera
{
public:
    Camera(const Vector3D& position);

    Matrix4x4 CreateLookAtMatrix() const;

    void UpdateTarget(double pitch, double yaw, double roll);

    Vector3D GetPosition() const;

    void UpdatePosition(double x, double y, double z);
private:
    Vector3D m_position;
    Vector3D m_target;
    const Vector3D m_origTarget;
    const Vector3D m_up;
};