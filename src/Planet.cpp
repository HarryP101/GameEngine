#include "Planet.h"

#include <vector>
#include <string>

#include "Vector3D.h"
#include "ObjFileLoader.h"
#include "Triangle.h"
#include "Constants.h"

Planet::Planet() : Mesh(), m_orbitRadius(0.0), m_theta(0.0) {}

Planet::Planet(double orbitRadius, double initialTheta, double speed, double size, const std::string& objFileLocation) : Mesh(objFileLocation, size),
    m_orbitRadius(orbitRadius), m_theta(initialTheta), m_speed(speed) 
{

}

void Planet::UpdatePosAndOrient(float fElapsedTime)
{
    // TODO: update orientation
    //(void)theta;

    auto speed = std::sqrt(Constants::SOLAR_MASS * Constants::G / m_orbitRadius);
    auto angularSpeed = speed / m_orbitRadius;

    // 1 second here = 1 week in normal time...
    angularSpeed *= 604800.0;
    m_theta += angularSpeed * static_cast<double>(fElapsedTime);

    // Make sure to scale back to screen space...
    // TODO make this clearer
    auto cartesianX = 1.0e-11 * m_orbitRadius * sin(m_theta);
    auto cartesianY = 1.0e-11 * m_orbitRadius * cos(m_theta);

    // Need a new variable
    auto cartesianZ = 8.0;

    for (size_t i = 0; i < m_originalTriangles.size(); ++i)
    {
        m_transformedTriangles[i] = m_originalTriangles[i] + Vector3D(cartesianX, cartesianY, cartesianZ);
    }
}