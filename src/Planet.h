#pragma once

#include <string>

#include "Vector3D.h"
#include "Mesh.h"
#include "Triangle.h"

// Assumes perfect circular motion about the centre of some massive object
// Not calculating any grav forces... yet!!
class Planet : public Mesh
{
public:
    Planet();
    Planet(double orbitRadius, double initialTheta, double speed, double size, const std::string& objFileLocation);
    void UpdatePosAndOrient(float fElapsedTime);
private:
    double m_orbitRadius;
    double m_theta;
    double m_speed;
};