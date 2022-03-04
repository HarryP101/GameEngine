#include "MarsShuttle.h"
#include "Planet.h"
#include "Constants.h"
#include "Vector3D.h"

MarsShuttle::MarsShuttle(const Vector3D& realPosition, double mass) : m_realPosition(realPosition), m_velocity(0.0, 0.0, 0.0), m_acceleration(0.0, 0.0, 0.0),
    m_launched(false), m_mass(mass) {}

bool MarsShuttle::Launch(const Planet::Position& earth)
{
    std::cout << "Launched!\n";
    m_launched = true;

    m_velocity = CalcLaunchVelocity(earth);
    //m_velocity = Vector3D(-60000.0, 0.0, 0.0);
    return true;
}

void MarsShuttle::UpdatePosition(float fElapsedTime, const Planet::Position& earth, const Planet::Position& mars)
{
    if (m_launched)
    {
        UpdateAcceleration(earth, mars);

        // Update velocity from acceleration
        m_velocity += m_acceleration * fElapsedTime;

        // Update position from velocity
        m_realPosition += m_velocity * fElapsedTime;

        // Check position isnt inside the earth
        if ((m_realPosition - Vector3D(earth.x, earth.y, earth.z)).Mag() < 6378e3)
        {
            std::cout << "Crashed" << std::endl;
            // Rebound lol
            m_velocity = m_velocity * -1;
        }        
    }
    else
    {
        m_realPosition = Vector3D(earth.x, earth.y + 3e10, earth.z);
    }
}

Vector3D MarsShuttle::GetScreenPosition(const Vector3D& screenScaling) const
{
    return m_realPosition.Scale(screenScaling);
}

void MarsShuttle::UpdateAcceleration(const Planet::Position& earth, const Planet::Position& mars)
{
    Vector3D rShuttleEarth = Vector3D(earth.x, earth.y, earth.z) - m_realPosition;
    double earthGravForce = Constants::G * m_mass * Constants::EARTH_MASS / (std::pow(rShuttleEarth.Mag(), 2));

    rShuttleEarth.Normalise();

    Vector3D rShuttleMars = Vector3D(mars.x, mars.y, mars.z) - m_realPosition;
    double marsGravForce = Constants::G * m_mass * Constants::MARS_MASS / (std::pow(rShuttleMars.Mag(), 2));

    rShuttleMars.Normalise();

    m_acceleration = (rShuttleEarth * earthGravForce + rShuttleMars * marsGravForce) * (1.0 / m_mass);
}

Vector3D MarsShuttle::CalcLaunchVelocity(const Planet::Position& earth) const
{
    Vector3D orbitVec = m_realPosition - Vector3D(earth.x, earth.y, earth.z);
    double orbitRadius = orbitVec.Mag();
    double velMagReq = std::sqrt(Constants::G * Constants::EARTH_MASS / orbitRadius);

    double angle = std::atan(orbitVec.GetY() / orbitVec.GetX());

    double xVelReq = velMagReq * sin(angle);
    double yVelReq = velMagReq * cos(angle);

    return Vector3D(xVelReq, yVelReq, 0.0);
}