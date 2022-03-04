#pragma once

#include "Vector3D.h"
#include "Planet.h"

class MarsShuttle
{
public:
    MarsShuttle(const Vector3D& realPosition, double mass);

    bool Launch(const Planet::Position& earth);

    void UpdatePosition(float fElapsedTime, const Planet::Position& earth, const Planet::Position& mars);

    Vector3D GetScreenPosition(const Vector3D& screenScaling) const;

    bool HasLaunched() const {return m_launched;}

private:
    void UpdateAcceleration(const Planet::Position& earth, const Planet::Position& mars);
    Vector3D CalcLaunchVelocity(const Planet::Position& earth) const;
    Vector3D m_realPosition;
    Vector3D m_velocity;
    Vector3D m_acceleration;

    bool m_launched;
    double m_mass;
};