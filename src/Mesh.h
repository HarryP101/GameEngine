#pragma once

#include <vector>
#include <string>
#include "Triangle.h"

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<Triangle>& triangles);

    static Mesh CreateCube();
    static Mesh CreateCoolShip(const std::string& location);
    void AddTriangle(const Triangle& tri) { m_triangles.push_back(tri); }
    std::vector<Triangle> GetTriangles() const { return m_triangles; }
private:
    std::vector<Triangle> m_triangles;
};