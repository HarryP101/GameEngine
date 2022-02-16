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
    Triangle tri(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 1.0, 0.0), Vector3D(1.0, 1.0, 0.0));
    m_meshCube.AddTriangle(tri);

    return true;
}

bool SandboxEngine::OnUserUpdate(float fElapsedTime)
{
    // called once per frame
    for (int x = 0; x < ScreenWidth(); x++)
        for (int y = 0; y < ScreenHeight(); y++)
            Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));

    return true;
}