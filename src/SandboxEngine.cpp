#define OLC_PGE_APPLICATION

#include "SandboxEngine.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Vector3D.h"

SandboxEngine::SandboxEngine()
{
    sAppName = "Harrys Example";
}

bool SandboxEngine::OnUserCreate()
{
    // Called once at the start, so create things here
    typedef Vector3D Point;

    // South
    Triangle tri1(Point(0.0, 0.0, 0.0), Point(0.0, 1.0, 0.0), Point(1.0, 1.0, 0.0));
    Triangle tri2(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 0.0), Point(1.0, 0.0, 0.0));

    // East
    Triangle tri3(Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 0.0), Point(1.0, 1.0, 1.0));
    Triangle tri4(Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 1.0), Point(1.0, 0.0, 0.0));

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

    m_meshCube.AddTriangle(tri1);
    m_meshCube.AddTriangle(tri2);
    m_meshCube.AddTriangle(tri3);
    m_meshCube.AddTriangle(tri4);
    m_meshCube.AddTriangle(tri5);
    m_meshCube.AddTriangle(tri6);
    m_meshCube.AddTriangle(tri7);
    m_meshCube.AddTriangle(tri8);
    m_meshCube.AddTriangle(tri9);
    m_meshCube.AddTriangle(tri10);
    m_meshCube.AddTriangle(tri11);
    m_meshCube.AddTriangle(tri12);

    return true;
}

bool SandboxEngine::OnUserUpdate(float fElapsedTime)
{
    // called once per frame
    auto triangles = m_meshCube.GetTriangles();

    for (const auto& tri : triangles)
    {
        DrawTriangle(tri.vert1.GetX(), tri.vert1.GetY(),
            tri.vert2.GetX(), tri.vert2.GetY(),
            tri.vert3.GetX(), tri.vert3.GetY());
    }

    return true;
}