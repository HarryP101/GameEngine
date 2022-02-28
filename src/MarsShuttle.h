#pragma once

#include "Vector3D.h"
#include "Planet.h"

class MarsShuttle
{
public:
    bool Launch();

    void UpdatePosition(float fElapsedTime, const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars);
private:
    void UpdateAcceleration(const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars);
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;
};