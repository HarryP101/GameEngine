#include "Sun.h"
#include <string>
#include "Mesh.h"
#include "Vector3D.h"
#include "Shader.h"

Sun::Sun(const Vector3D& position, const std::string& objFileLocation, double size) : Mesh(objFileLocation, size), m_position(position) 
{
    for (size_t i = 0; i < m_originalTriangles.size(); ++i)
    {
        m_transformedTriangles[i] = m_originalTriangles[i] + position;
    }
}

olc::Pixel Sun::GetIllumination(const Vector3D& objectPosition, const Vector3D& normal, Planet::Colour colour) const
{
    olc::Pixel illum = 0.0;

    Vector3D rayToSun(objectPosition.GetX() - m_position.GetX(),
        objectPosition.GetY() - m_position.GetY(),
        objectPosition.GetZ() - m_position.GetZ());

    rayToSun.Normalise();

    double similar = rayToSun.Dot(normal);

    // Dark side of the planet
    if (similar > 0)
    {

    }
    else
    {
        illum = Shader::GetColour(std::fabs(similar), colour);
    }

    return illum;
}