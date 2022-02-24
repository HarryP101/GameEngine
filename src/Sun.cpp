#include "Sun.h"
#include "Vector3D.h"
#include "Shader.h"

Sun::Sun(const Vector3D& position) : m_position(position) {}

olc::Pixel Sun::GetIllumination(const Vector3D& objectPosition, const Vector3D& normal) const
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
        illum = Shader::GetColour(std::fabs(similar));
    }

    return illum;
}