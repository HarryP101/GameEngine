#include "Camera.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

Camera::Camera(const Vector3D& position) : m_position(position), m_target(0.0, 0.0, 1.0), m_origTarget(0.0, 0.0, 1.0), m_up(0.0, -1.0, 0.0) {}

Matrix4x4 Camera::CreateLookAtMatrix() const
{
    Matrix4x4 lookAt;

    // Calculate new forward direction
    Vector3D newForward = m_target - m_position;
    newForward.Normalise();

    // Calculate new up direction
    Vector3D a = newForward * m_up.Dot(newForward);
    Vector3D newUp = m_up - a;
    newUp.Normalise();

    Vector3D newRight = newUp.Cross(newForward);

    lookAt.SetRow(0, newRight.GetX(), newUp.GetX(), newForward.GetX(), 0.0);
    lookAt.SetRow(1, newRight.GetY(), newUp.GetY(), newForward.GetY(), 0.0);
    lookAt.SetRow(2, newRight.GetZ(), newUp.GetZ(), newForward.GetZ(), 0.0);

    double t1 = -(m_position.GetX() * newRight.GetX() + m_position.GetY() * newUp.GetX() + m_position.GetZ() * newForward.GetX());
    double t2 = -(m_position.GetX() * newRight.GetY() + m_position.GetY() * newUp.GetY() + m_position.GetZ() * newForward.GetY());
    double t3 = -(m_position.GetX() * newRight.GetZ() + m_position.GetY() * newUp.GetZ() + m_position.GetZ() * newForward.GetZ());

    lookAt.SetRow(3, t1, t2, t3, 1.0);

    return lookAt;
}

void Camera::UpdateTarget(double pitch, double yaw, double roll) 
{
    // TODO
    (void)pitch;
    (void)yaw; 
    (void)roll;
    m_target = m_origTarget + m_position;
}

Vector3D Camera::GetPosition() const
{
    return m_position;
}

void Camera::UpdatePosition(double x, double y, double z)
{
    m_position = Vector3D(m_position.GetX() + x, m_position.GetY() + y, m_position.GetZ() + z);
}