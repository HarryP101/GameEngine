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

void Planet::UpdateScreenPosAndOrient(float fElapsedTime, double simSecondsPerRealSecond, const Vector3D& screenScaling)
{
    // TODO: update orientation
    //(void)theta;

    auto speed = std::sqrt(Constants::SOLAR_MASS * Constants::G / m_orbitRadius);
    auto angularSpeed = speed / m_orbitRadius;

    m_theta += angularSpeed * static_cast<double>(fElapsedTime) * simSecondsPerRealSecond;

    // Make sure to scale back to screen space...
    // TODO make this clearer
    auto screenX = screenScaling.GetX() * m_orbitRadius * sin(m_theta);
    auto screenY = screenScaling.GetY() * m_orbitRadius * cos(m_theta);

    for (size_t i = 0; i < m_originalTriangles.size(); ++i)
    {
        m_transformedTriangles[i] = m_originalTriangles[i] + Vector3D(screenX, screenY, m_depthIntoScreen);
    }
}

Planet::Colour Planet::GetColour() const
{
    return m_colour;
}

Planet::PlanetData Planet::GetPlanetData() const
{
    auto cartesianX = m_orbitRadius * sin(m_theta);
    auto cartesianY = m_orbitRadius * cos(m_theta);
    return PlanetData {Vector3D(cartesianX, cartesianY, m_z), Constants::EARTH_MASS};
}