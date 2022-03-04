#pragma once

#include <vector>
#include "Vector3D.h"
#include "Planet.h"

class MarsShuttle
{
public:
    MarsShuttle(const Vector3D& realPosition, double mass);

    bool Launch(const Planet::PlanetData& earth);

    void UpdatePosition(float fElapsedTime, const std::vector<Planet>& planets);

    Vector3D GetScreenPosition(const Vector3D& screenScaling) const;

    bool HasLaunched() const {return m_launched;}

private:
    void UpdateAcceleration(const std::vector<Planet>& planets);
    Vector3D CalcLaunchVelocity(const Planet::PlanetData& earth) const;
    Vector3D m_realPosition;
    Vector3D m_velocity;
    Vector3D m_acceleration;

    bool m_launched;
    double m_mass;
};