#pragma once

#include "Vector3D.h"
#include "olcPixelGameEngine.h"

// Represents a point light source, emitting in a sphere
// Assumes that the sun is much greater in size than the 
// object it is illuminating
class Sun
{
public:
    Sun(const Vector3D& position);
    olc::Pixel GetIllumination(const Vector3D& objectPosition, const Vector3D& normal) const;
private:
    Vector3D m_position;    
};