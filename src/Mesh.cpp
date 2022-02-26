#include "Mesh.h"
#include <string>
#include <vector>
#include "ObjFileLoader.h"
#include "Triangle.h"

Mesh::Mesh() : m_originalTriangles(), m_transformedTriangles() {}

Mesh::Mesh(const std::vector<Triangle>& triangles) : m_originalTriangles(triangles), m_transformedTriangles(triangles) {}

Mesh::Mesh(const std::string& objFileLocation, double size) : m_originalTriangles(ObjFileLoader::Load(objFileLocation, size)),
    m_transformedTriangles(m_originalTriangles) {}
    
/*
Mesh Mesh::CreateCube()
{
    typedef Vector3D Point;

    Mesh mesh;
    
    // Set up unit cube

    // South
    Triangle tri1(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(1.0, 1.0, 0.0));
    Triangle tri2(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 0.0), Point(1.0, 0.0, 0.0));

    // East
    Triangle tri3(Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 0.0), Point(1.0, 1.0, 1.0));
    Triangle tri4(Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 1.0), Point(1.0, 0.0, 1.0));

    // North
    Triangle tri5(Point(1.0, 0.0, 1.0), Point(1.0, 1.0, 1.0), Point(0.0, 1.0, 1.0));
    Triangle tri6(Point(1.0, 0.0, 1.0), Point(0.0, 1.0, 1.0), Point(0.0, 0.0, 1.0));

    // West
    Triangle tri7(Point(0.0, 0.0, 1.0), Point(0.0, 1.0, 1.0), Point(0.0, 1.0, 0.0));
    Triangle tri8(Point(0.0, 0.0, 1.0), Point(0.0, 1.0, 0.0), Point(0.0, 0.0, 0.0));

    // Top
    Triangle tri9(Point(0.0, 1.0, 0.0), Point(0.0, 1.0, 1.0), Point(1.0, 1.0, 1.0));
    Triangle tri10(Point(0.0, 1.0, 0.0), Point(1.0, 1.0, 1.0), Point(1.0, 1.0, 0.0));

    // Bottom
    Triangle tri11(Point(1.0, 0.0, 1.0), Point(0.0, 0.0, 1.0), Point(0.0, 0.0, 0.0));
    Triangle tri12(Point(1.0, 0.0, 1.0), Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0));

    mesh.AddTriangle(tri1);
    mesh.AddTriangle(tri2);
    mesh.AddTriangle(tri3);
    mesh.AddTriangle(tri4);
    mesh.AddTriangle(tri5);
    mesh.AddTriangle(tri6);
    mesh.AddTriangle(tri7);
    mesh.AddTriangle(tri8);
    mesh.AddTriangle(tri9);
    mesh.AddTriangle(tri10);
    mesh.AddTriangle(tri11);
    mesh.AddTriangle(tri12);

    return mesh;
}
*/