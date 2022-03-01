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
    enum class Colour {RED, GREEN, BLUE};

    struct MassAndPosition
    {
        double mass;
        double x;
        double y;
        double z;
    };

    Planet();
    Planet(double orbitRadius, double initialTheta, double size, Colour colour, const std::string& objFileLocation);
    void UpdatePosAndOrient(float fElapsedTime, double simSecondsPerRealSecond);
    Colour GetColour() const;

    MassAndPosition GetMassAndPosition() const;

private:
    double m_orbitRadius;
    double m_theta;
    Colour m_colour;
};