#include "Planet.h"

#include <vector>
#include <string>

#include "Vector3D.h"
#include "ObjFileLoader.h"
#include "Triangle.h"
#include "Constants.h"

Planet::Planet() : Mesh(), m_orbitRadius(0.0), m_theta(0.0) {}

Planet::Planet(double orbitRadius, double initialTheta, double depthIntoScreen, double size, Colour colour, const std::string& objFileLocation) : Mesh(objFileLocation, size),
    m_orbitRadius(orbitRadius), m_theta(initialTheta), m_depthIntoScreen(depthIntoScreen), m_colour(colour) 
{

}

void Planet::UpdateScreenPosAndOrient(const Vector3D& screenScaling)
{
    // TODO: update orientation

    // Make sure to scale back to screen space...
    auto screenX = screenScaling.GetX() * m_orbitRadius * sin(m_theta);
    auto screenY = screenScaling.GetY() * m_orbitRadius * cos(m_theta);

    for (size_t i = 0; i < m_originalTriangles.size(); ++i)
    {
        m_transformedTriangles[i] = m_originalTriangles[i] + Vector3D(screenX, screenY, m_depthIntoScreen);
    }
}

void Planet::UpdatePosition(float fElapsedTime)
{
    m_speed = std::sqrt(Constants::SOLAR_MASS * Constants::G / m_orbitRadius);
    auto angularSpeed = m_speed / m_orbitRadius;
    m_theta += angularSpeed * static_cast<double>(fElapsedTime);
}

Planet::Colour Planet::GetColour() const
{
    return m_colour;
}

Planet::PlanetData Planet::GetPlanetData() const
{
    auto cartesianX = m_orbitRadius * sin(m_theta);
    auto cartesianY = m_orbitRadius * cos(m_theta);
    Vector3D position(cartesianX, cartesianY, m_z);

    auto velX = m_speed * cos(m_theta);
    auto velY = m_speed * -sin(m_theta);

    Vector3D velocity(velX, velY, 0.0);

    return PlanetData {position, velocity, Constants::EARTH_MASS};
}