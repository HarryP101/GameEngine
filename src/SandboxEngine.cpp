#define OLC_PGE_APPLICATION

#include "SandboxEngine.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Vector3D.h"
#include "Constants.h"
#include "RotationMatrix4x4.h"
#include "Shader.h"


SandboxEngine::SandboxEngine() : m_camera(0.0, 0.0, 0.0), m_rotateX(RotationMatrix4x4::Axis::X, 0.0), m_rotateZ(RotationMatrix4x4::Axis::Z, 0.0), m_theta(0.0)
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

    m_theta += 1.0 * static_cast<double>(fElapsedTime);

    m_rotateZ.Update(m_theta);
    m_rotateX.Update(m_theta);

    // called once per frame
    auto triangles = m_meshCube.GetTriangles();

    // Draw triangles
    for (auto& tri : triangles)
    {
        // Spin the triangles for fun
        tri *= m_rotateZ;
        tri *= m_rotateX;

        Vector3D translation(0.0, 0.0, 3.0);
        tri += translation;

        Vector3D line1 = tri.vert2 - tri.vert1;
        Vector3D line2 = tri.vert3 - tri.vert1;

        Vector3D normal = line1.Cross(line2);
        normal.Normalise();

        // Can choose any vertice here as the triangle exists in a plane
        if ((normal.Dot(tri.vert1 - m_camera)) < 0.0)
        {
            // Illumination
            Vector3D lightDirection(0.0, 0.0, -1.0);
            lightDirection.Normalise();

            double dp = normal.Dot(lightDirection);

            olc::Pixel s = Shader::GetColour(dp);

            // Project from 3D space to 2D
            tri *= m_projectionMatrix;

            // Scale into view
            Vector3D one(1.0, 1.0, 0.0);
            tri += one;

            Vector3D xyzScaling(0.5 * static_cast<double>(ScreenWidth()), 0.5 * static_cast<double>(ScreenHeight()), 1.0);
            tri *= xyzScaling;

            // Rasterize triangles
            FillTriangle(tri.vert1.GetPixelX(), tri.vert1.GetPixelY(),
                tri.vert2.GetPixelX(), tri.vert2.GetPixelY(),
                tri.vert3.GetPixelX(), tri.vert3.GetPixelY(), s);
        }
    }

    return true;
}