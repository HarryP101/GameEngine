#pragma once

#include <vector>
#include "Triangle.h"

class Mesh
{
public:
    static Mesh CreateCube();
    void AddTriangle(const Triangle& tri) { m_triangles.push_back(tri); }
    std::vector<Triangle> GetTriangles() const { return m_triangles; }
private:
    std::vector<Triangle> m_triangles;
};