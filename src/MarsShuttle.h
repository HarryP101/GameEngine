#pragma once

#include "Vector3D.h"
#include "Planet.h"

class MarsShuttle
{
public:
    MarsShuttle(const Vector3D& position, double mass);

    bool Launch();

    void UpdatePosition(float fElapsedTime, const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars);

    Vector3D GetPosition() const;

    bool HasLaunched() const {return m_launched;}

private:
    void UpdateAcceleration(const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars);
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;

    bool m_launched;
    double m_mass;
};