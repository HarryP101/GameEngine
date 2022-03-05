#include "MarsShuttle.h"
#include "Planet.h"
#include "Constants.h"
#include "Vector3D.h"

MarsShuttle::MarsShuttle(const Vector3D& realPosition, double mass) : m_realPosition(realPosition), m_velocity(0.0, 0.0, 0.0), m_acceleration(0.0, 0.0, 0.0),
    m_launched(false), m_mass(mass) {}

bool MarsShuttle::Launch(const Planet::PlanetData& earth)
{
    std::cout << "Launched!\n";
    m_launched = true;

    m_velocity = CalcLaunchVelocity(earth);
    //m_velocity = Vector3D(-60000.0, 0.0, 0.0);
    return true;
}

void MarsShuttle::UpdatePosition(float fElapsedTime, const std::vector<Planet>& planets)
{
    Planet::PlanetData earth = planets[0].GetPlanetData();

    if (m_launched)
    {
        // Shuttle has detached from planet and become a free body

        UpdateAcceleration(planets);

        // Update velocity from acceleration
        m_velocity += m_acceleration * fElapsedTime;

        // Update position from velocity
        m_realPosition += m_velocity * fElapsedTime;

        // Check position isnt inside the earth
        if ((m_realPosition - earth.position).Mag() < 6378e3)
        {
            std::cout << "Crashed" << std::endl;
            // Rebound lol
            m_velocity = m_velocity * -1;
        }       
    }
    else
    {
        // Shuttle is attached to planet
        m_realPosition = earth.position + Vector3D(0.0, 3e8, 0.0);
        m_velocity = earth.velocity;
    }
}

Vector3D MarsShuttle::GetScreenPosition(const Vector3D& screenScaling) const
{
    return m_realPosition.Scale(screenScaling);
}

void MarsShuttle::UpdateAcceleration(const std::vector<Planet>& planets)
{
    Vector3D totalForce(0.0, 0.0, 0.0);

    for (const auto& planet : planets)
    {
        auto planetData = planet.GetPlanetData();

        Vector3D rShuttleToPlanet = planetData.position - m_realPosition;
        double planetGravForce = Constants::G * planetData.mass * m_mass / (rShuttleToPlanet.MagSq());

        rShuttleToPlanet.Normalise();

        totalForce += rShuttleToPlanet * planetGravForce;
    }

    m_acceleration = totalForce * (1.0 / m_mass);
}

Vector3D MarsShuttle::CalcLaunchVelocity(const Planet::PlanetData& earth) const
{
    // This doesnt work as intended... yet...
    Vector3D orbitVec = m_realPosition - earth.position;
    double orbitRadius = orbitVec.Mag();
    double velMagReq = std::sqrt(Constants::G * earth.mass / orbitRadius);

    double angle = std::atan(orbitVec.GetY() / orbitVec.GetX());

    double xVelReq = velMagReq * cos(angle);
    double yVelReq = velMagReq * -sin(angle);

    return Vector3D(xVelReq + m_velocity.GetX(), yVelReq + m_velocity.GetY(), 0.0);
}