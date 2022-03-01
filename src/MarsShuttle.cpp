#include "MarsShuttle.h"
#include "Planet.h"
#include "Constants.h"
#include "Vector3D.h"

MarsShuttle::MarsShuttle(const Vector3D& position, double mass) : m_position(position), m_velocity(0.0, 0.0, 0.0), m_acceleration(0.0, 0.0, 0.0),
    m_launched(false), m_mass(mass) {}

bool MarsShuttle::Launch()
{
    std::cout << "Launched!\n";
    m_launched = true;
    m_velocity = Vector3D(-1500.0, 0.0, 0.0);
    return true;
}

void MarsShuttle::UpdatePosition(float fElapsedTime, const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars)
{
    if (m_launched)
    {
        UpdateAcceleration(earth, mars);

        // Update velocity from acceleration
        m_velocity += m_acceleration * fElapsedTime;

        // Update position from velocity
        m_position += m_velocity * fElapsedTime;

        // Check position isnt inside the earth
        if ((m_position - Vector3D(earth.x, earth.y, earth.z)).Mag() < 6378e3)
        {
            std::cout << "Crashed" << std::endl;
            // Rebound lol
            m_velocity = m_velocity * -1;
        }        
    }
    else
    {
        m_position = Vector3D(earth.x, earth.y + 3e8, earth.z);
    }
}

Vector3D MarsShuttle::GetPosition() const
{
    return m_position.Scale(Vector3D(2.0e-11, 2.0e-11, 1.0));
}

void MarsShuttle::UpdateAcceleration(const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars)
{
    Vector3D rShuttleEarth = Vector3D(earth.x, earth.y, earth.z) - m_position;
    double earthGravForce = Constants::G * m_mass * Constants::EARTH_MASS / (std::pow(rShuttleEarth.Mag(), 2));

    rShuttleEarth.Normalise();

    Vector3D rShuttleMars = Vector3D(mars.x, mars.y, mars.z) - m_position;
    double marsGravForce = Constants::G * m_mass * Constants::MARS_MASS / (std::pow(rShuttleMars.Mag(), 2));

    rShuttleMars.Normalise();

    m_acceleration = (rShuttleEarth * earthGravForce + rShuttleMars * marsGravForce) * (1.0 / m_mass);
}