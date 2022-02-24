#pragma once

#include <string>

#include "Vector3D.h"
#include "Mesh.h"
#include "Triangle.h"

class Planet : public Mesh
{
public:
    Planet();
    Planet(const Vector3D& initialPos, double size, const std::string& objFileLocation);
    void UpdatePosAndOrient(double x, double y, double z, double theta);
    constexpr double GetSize() const { return m_size; }
private:
    Vector3D m_position;
    double m_size;
};