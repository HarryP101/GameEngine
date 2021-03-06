#pragma once

#include <vector>
#include <string>
#include "Triangle.h"

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<Triangle>& triangles);
    Mesh(const std::string& objFileLocation, double size);

    //static Mesh CreateCube();
    void AddTriangle(const Triangle& tri) { m_transformedTriangles.push_back(tri); }
    std::vector<Triangle> GetTriangles() const { return m_transformedTriangles; }
protected:
    const std::vector<Triangle> m_originalTriangles;
    std::vector<Triangle> m_transformedTriangles;
};