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

    struct PlanetData
    {
        Vector3D position;
        Vector3D velocity;
        double mass;
    };

    Planet();
    Planet(double orbitRadius, double initialTheta, double depthIntoScreen, double size, Colour colour, const std::string& objFileLocation);
    void UpdatePosition(float fElapsedTime);
    void UpdateScreenPosAndOrient(const Vector3D& screenScaling);
    Colour GetColour() const;
    PlanetData GetPlanetData() const;

private:
    double m_orbitRadius;
    double m_theta;
    double m_speed;

    // Set to 1.0 for now i.e. 2D circ motion
    const double m_z = 1.0;
    double m_depthIntoScreen;
    Colour m_colour;
};