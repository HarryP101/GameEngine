#pragma once

#include <string>
#include "Vector3D.h"
#include "olcPixelGameEngine.h"
#include "Planet.h"
#include "Mesh.h"

// Represents a point light source, emitting in a sphere
// Assumes that the sun is much greater in size than the 
// object it is illuminating
class Sun : public Mesh
{
public:
    Sun(const Vector3D& position, const std::string& objFileLocation, double size);
    olc::Pixel GetIllumination(const Vector3D& objectPosition, const Vector3D& normal, Planet::Colour colour) const;
private:
    Vector3D m_position;    
};