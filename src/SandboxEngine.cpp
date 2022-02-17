#define OLC_PGE_APPLICATION

#include "SandboxEngine.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Vector3D.h"
#include "Constants.h"
#include "RotationMatrix4x4.h"

SandboxEngine::SandboxEngine() : m_rotateX(RotationMatrix4x4::Axis::X, 0.0), m_rotateZ(RotationMatrix4x4::Axis::Z, 0.0), m_theta(0.0)
{
    sAppName = "Harrys Example";
}

bool SandboxEngine::OnUserCreate()
{
    // Called once at the start, so create things here

    // Set up unit cube
    m_meshCube = Mesh::CreateCube();

    // Set up projection matrix
    double zNear = 0.1;
    double zFar = 1000.0;
    double fov = 90.0;
    double aspectRatio = static_cast<double>(ScreenHeight()) / static_cast<double>(ScreenWidth());
    double fovRad = 1.0 / tan(((fov * 0.5) / 180.0) * Constants::PI);

    m_projectionMatrix.SetRow(0, aspectRatio * fovRad, 0.0, 0.0, 0.0);
    m_projectionMatrix.SetRow(1, 0.0, fovRad, 0.0, 0.0);
    m_projectionMatrix.SetRow(2, 0.0, 0.0, zFar / (zFar - zNear), 1.0);
    m_projectionMatrix.SetRow(3, 0.0, 0.0, -(zFar * zNear) / (zFar - zNear), 0.0);

    return true;
}

bool SandboxEngine::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK);

    Matrix4x4 rotateZ;
    Matrix4x4 rotateX;

    m_theta += 1.0 * static_cast<double>(fElapsedTime);

    m_rotateZ.Update(m_theta);
    m_rotateX.Update(m_theta);

    // called once per frame
    auto triangles = m_meshCube.GetTriangles();

    // Draw triangles
    for (const auto& tri : triangles)
    {
        Vector3D rotVert1 = tri.vert1 * m_rotateZ;
        Vector3D rotVert2 = tri.vert2 * m_rotateZ;
        Vector3D rotVert3 = tri.vert3 * m_rotateZ;

        rotVert1 = rotVert1 * m_rotateX;
        rotVert2 = rotVert2 * m_rotateX;
        rotVert3 = rotVert3 * m_rotateX;

        Vector3D translation(0.0, 0.0, 3.0);
        Vector3D transVert1 = rotVert1 + translation;
        Vector3D transVert2 = rotVert2 + translation;
        Vector3D transVert3 = rotVert3 + translation;

        Triangle transTri(transVert1, transVert2, transVert3);

        Vector3D projVert1 = transTri.vert1 * m_projectionMatrix;
        Vector3D projVert2 = transTri.vert2 * m_projectionMatrix;
        Vector3D projVert3 = transTri.vert3 * m_projectionMatrix;

        Triangle projTri(projVert1, projVert2, projVert3);

        // Scale into view
        Vector3D one(1.0, 1.0, 0.0);
        projTri.vert1 = projTri.vert1 + one;
        projTri.vert2 = projTri.vert2 + one;
        projTri.vert3 = projTri.vert3 + one;

        Vector3D xyzScaling(0.5 * static_cast<double>(ScreenWidth()), 0.5 * static_cast<double>(ScreenHeight()), 1.0);
        projTri.vert1 = projTri.vert1.Scale(xyzScaling);
        projTri.vert2 = projTri.vert2.Scale(xyzScaling);
        projTri.vert3 = projTri.vert3.Scale(xyzScaling);

        DrawTriangle(projTri.vert1.GetPixelX(), projTri.vert1.GetPixelY(),
            projTri.vert2.GetPixelX(), projTri.vert2.GetPixelY(),
            projTri.vert3.GetPixelX(), projTri.vert3.GetPixelY());
    }

    return true;
}