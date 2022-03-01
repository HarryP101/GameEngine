#define OLC_PGE_APPLICATION

#include "SandboxEngine.h"
#include <algorithm>
#include <vector>
#include <list>

#include "Triangle.h"
#include "Vector3D.h"
#include "Constants.h"
#include "Sun.h"
#include "Planet.h"
#include "MarsShuttle.h"
#include "ProjectionMatrix.h"

constexpr unsigned int N_SIM_SECONDS_PER_REAL_SECOND = 6200000;
constexpr unsigned int GRANULARITY = 100;

SandboxEngine::SandboxEngine() : m_lookDirection(0.0, 0.0, 1.0), m_sun(Vector3D(0.0, 0.0, 8.0), "sampleobjects/sphere.obj", 0.5),
    m_camera(Vector3D(0.0, 0.0, -5.0)), m_marsShuttle(Vector3D(1.5*sin(30), 1.5*cos(30), 8.0), 4.0e4)
{
    sAppName = "Harrys Example";
}

bool SandboxEngine::OnUserCreate()
{
    // Called once at the start, so create things here
    
    // EARTH
    m_solarSystem.push_back(Planet(1.5e11, 30, 0.2, Planet::Colour::BLUE, "sampleobjects/sphere.obj"));

    // MARS
    m_solarSystem.push_back(Planet(7.5e11, 60, 0.15, Planet::Colour::RED, "sampleobjects/sphere.obj"));

    //m_solarSystem.push_back(Planet(3.0, 10, 0.9, 0.5, "sampleobjects/sphere.obj"));

    // Set up projection matrix
    constexpr double zNear = 0.1;
    constexpr double zFar = 1000.0;
    constexpr double fov = 90.0;
    double aspectRatio = static_cast<double>(ScreenHeight()) / static_cast<double>(ScreenWidth());
    double fovRad = 1.0 / tan(((fov * 0.5) / 180.0) * Constants::PI);

    m_projectionMatrix = ProjectionMatrix(aspectRatio, fovRad, zNear, zFar);

    return true;
}

bool SandboxEngine::OnUserUpdate(float fElapsedTime)
{
    const Vector3D zNearPlane(0.0, 0.0, 0.1);
    const Vector3D zNormal(0.0, 0.0, 1.0);

    UpdateCameraFromInput(fElapsedTime);

    Vector3D one(1.0, 1.0, 0.0);

    // Update camera position and target. Gen new matrix
    m_camera.UpdateTarget(0.0, 0.0, 0.0);
    Matrix4x4 cameraView = m_camera.CreateLookAtMatrix();

    Clear(olc::BLACK);

    // Only draw the final one though
    Vector3D xyzScaling(0.5 * static_cast<double>(ScreenWidth()), 0.5 * static_cast<double>(ScreenHeight()), 1.0);

    for (unsigned int i = 0; i < N_SIM_SECONDS_PER_REAL_SECOND / GRANULARITY; ++i)
    {
        // Update the shuttles position - TODO: TIDY UP
        m_marsShuttle.UpdatePosition(fElapsedTime * GRANULARITY, m_solarSystem[0].GetMassAndPosition(), m_solarSystem[1].GetMassAndPosition());
    }

    if (m_marsShuttle.HasLaunched())
    {
        auto shuttlePosition = m_marsShuttle.GetPosition();
        m_shuttlePath.push_back(shuttlePosition);
    }

    std::vector<Vector3D> pointsToRaster;
    for (const auto& pos : m_shuttlePath)
    {
        auto viewedShuttlePosition = pos * cameraView;

        // Project from 3D space to 2D
        auto projectedShuttlePosition = viewedShuttlePosition * m_projectionMatrix;

        // Scale into view
        projectedShuttlePosition += one;
        auto scaledShuttlePosition = projectedShuttlePosition.Scale(xyzScaling);

        pointsToRaster.push_back(scaledShuttlePosition);
    }

    std::vector<Triangle> trisToRaster;
    // Update planet position and size and add to triangles to be rastered
    for (auto& planet : m_solarSystem)
    {
        planet.UpdatePosAndOrient(0.0, N_SIM_SECONDS_PER_REAL_SECOND);

        // Called once per frame
        auto triangles = planet.GetTriangles();

        // Determine which triangles to draw
        for (auto& tri : triangles)
        {
            // Can choose any vertice here as the triangle exists in a plane
            if (tri.CanBeSeen(m_camera.GetPosition()))
            {
                // Illumination
                tri.illum = m_sun.GetIllumination(tri.vert1, tri.normal, planet.GetColour());

                // Convert world space to view space
                tri *= cameraView;

                // Clip viewed triangle against near plane. This could form up to two additional triangles
                std::vector<Triangle> clippedTris(2, Triangle(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0)));

                size_t nClippedTriangles = ClipAgainstPlane(zNearPlane, zNormal, tri, clippedTris[0], clippedTris[1]);

                for (size_t n = 0; n < nClippedTriangles; ++n)
                {
                    // Project from 3D space to 2D
                    clippedTris[n] *= m_projectionMatrix;

                    // Scale into view
                    clippedTris[n] += one;
                    clippedTris[n] *= xyzScaling;

                    trisToRaster.push_back(clippedTris[n]);
                }
            }
        }
    }

    // Add the suns triangles to be rastered
    auto triangles = m_sun.GetTriangles();

    // Determine which triangles to draw
    for (auto& tri : triangles)
    {
        // Can choose any vertice here as the triangle exists in a plane
        if (tri.CanBeSeen(m_camera.GetPosition()))
        {
            // Illumination
            tri.illum = olc::Pixel(255, 255, 255);

            // Convert world space to view space
            tri *= cameraView;

            // Clip viewed triangle against near plane. This could form up to two additional triangles
            std::vector<Triangle> clippedTris(2, Triangle(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0)));

            size_t nClippedTriangles = ClipAgainstPlane(zNearPlane, zNormal, tri, clippedTris[0], clippedTris[1]);

            for (size_t n = 0; n < nClippedTriangles; ++n)
            {
                // Project from 3D space to 2D
                clippedTris[n] *= m_projectionMatrix;

                // Scale into view
                clippedTris[n] += one;
                clippedTris[n] *= xyzScaling;

                trisToRaster.push_back(clippedTris[n]);
            }
        }
    }

    // Painters algorithm
    std::sort(trisToRaster.begin(), trisToRaster.end(), [](Triangle &t1, Triangle &t2){ return t1.GetCentroid().GetZ() > t2.GetCentroid().GetZ(); });

    for (const auto& triRaster : trisToRaster)
    {
        // Clip triangles against all four screen edges. Create a queue (list??) to traverse
        // all new triangles so we only test new triangles generated against plane

        std::vector<Triangle> clipped(2, Triangle(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0)));
        std::list<Triangle> listTriangles;

        // Add initial triangle
        listTriangles.push_back(triRaster);
        size_t nNewTriangles = 1;

        for (unsigned int p = 0; p < 4; ++p)
        {
            size_t nTrisToAdd = 0;
            while (nNewTriangles > 0)
            {
                // Take triangle from front of queue
                Triangle test = listTriangles.front();
                listTriangles.pop_front();
                nNewTriangles--;

                // Clip against plane. Only need to test each subsequent plane, against
                // subsequent new triangles as all triangles after plane clip are guaranteed to
                // lie on the inside of the plane
                switch(p)
                {
                    case 0:
                        nTrisToAdd = ClipAgainstPlane(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 1.0, 0.0), test, clipped[0], clipped[1]);
                        break;
                    case 1:
                        nTrisToAdd = ClipAgainstPlane(Vector3D(0.0, static_cast<double>(ScreenHeight()) - 1.0, 0.0), Vector3D(0.0, -1.0, 0.0),
                            test, clipped[0], clipped[1]);
                        break;
                    case 2:
                        nTrisToAdd = ClipAgainstPlane(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0), test, clipped[0], clipped[1]);
                        break;
                    case 3:
                        nTrisToAdd = ClipAgainstPlane(Vector3D(static_cast<double>(ScreenWidth()) - 1.0, 0.0, 0.0), Vector3D(-1.0, 0.0, 0.0),
                            test, clipped[0], clipped[1]);
                        break;
                    default:
                        break;
                }

                // Add new triangles generated to queue
                for (size_t w = 0; w < nTrisToAdd; ++w)
                {
                    listTriangles.push_back(clipped[w]);
                }
            }
            nNewTriangles = listTriangles.size();
        }

        for (const auto& tri : listTriangles)
        {
            // Rasterize triangles
            FillTriangle(tri.vert1.GetPixelX(), tri.vert1.GetPixelY(),
                tri.vert2.GetPixelX(), tri.vert2.GetPixelY(),
                tri.vert3.GetPixelX(), tri.vert3.GetPixelY(), tri.illum);
        }
    }

    
    if (pointsToRaster.size() > 1)
    {
        for (size_t i = 0; i < pointsToRaster.size()-1; ++i)
        {
            auto sP = pointsToRaster[i];
            auto eP = pointsToRaster[i+1];
            DrawLine({sP.GetPixelX(), sP.GetPixelY()}, {eP.GetPixelX(), eP.GetPixelY()});
        }
    }

    return true;
}

size_t SandboxEngine::ClipAgainstPlane(const Vector3D& planePoint, Vector3D planeNormal, const Triangle& inputTriangle,
    Triangle &outTri1, Triangle &outTri2) const
{
    // Ensure it has been normalised
    planeNormal.Normalise();

    // Return shortest distance from point to plane
    auto shortestDist = [planePoint, planeNormal](const Vector3D& p)
    {
        return (planeNormal.GetX() * p.GetX() + planeNormal.GetY() * p.GetY() + planeNormal.GetZ() * p.GetZ() - planeNormal.Dot(planePoint));
    };

    // Storage to classify points either side of the plane
    std::vector<Vector3D> insidePoints(3, Vector3D(0.0, 0.0, 0.0));
    std::vector<Vector3D> outsidePoints(3, Vector3D(0.0, 0.0, 0.0));
    size_t nInsidePointCount = 0;
    size_t nOutsidePointCount = 0;

    // Get distance of each point in triangle to plane
    double d0 = shortestDist(inputTriangle.vert1);
    double d1 = shortestDist(inputTriangle.vert2);
    double d2 = shortestDist(inputTriangle.vert3);

    if (d0 >= 0)
    {
        insidePoints[nInsidePointCount++] = inputTriangle.vert1;
    }
    else
    {
        outsidePoints[nOutsidePointCount++] = inputTriangle.vert1;
    }
    if (d1 >= 0)
    {
        insidePoints[nInsidePointCount++] = inputTriangle.vert2;
    }
    else
    {
        outsidePoints[nOutsidePointCount++] = inputTriangle.vert2;
    }
    if (d2 >= 0)
    {
        insidePoints[nInsidePointCount++] = inputTriangle.vert3;
    }
    else
    {
        outsidePoints[nOutsidePointCount++] = inputTriangle.vert3;
    }

    // Classify the triangle points and break the input triangle into smaller
    // output triangles if required.

    if (nInsidePointCount == 0)
    {
        // All points lie on the outside of the plane. Clip the whole triangle
        return 0;
    }
    else if (nInsidePointCount == 3)
    {
        // All points lie on the inside of the plane. Do nothing
        outTri1 = inputTriangle;

        return 1;
    }
    else if (nInsidePointCount == 1 && nOutsidePointCount == 2)
    {
        // Triangle should be clipped. Triangle becomes a smaller triangle

        outTri1.illum = inputTriangle.illum;

        // Outside point is valid
        outTri1.vert1 = inputTriangle.vert1;

        // Two new points are at the locations where the original sides of the triangle intersect
        // with the plane
        outTri1.vert2 = Vector3D::IntersectPlane(planePoint, planeNormal, insidePoints[0], outsidePoints[0]);
        outTri1.vert3 = Vector3D::IntersectPlane(planePoint, planeNormal, insidePoints[0], outsidePoints[1]);

        return 1;
    }
    else if (nInsidePointCount == 2 && nOutsidePointCount == 1)
    {
        // Triangle should be clipped. Triangle becomes a quad, represented
        // with two new triangles.

        outTri1.illum = inputTriangle.illum;
        outTri2.illum = inputTriangle.illum;

        // First triangle consists of two inside points and new point determined
        // by where one side of the triangle intersects the plane
        outTri1.vert1 = insidePoints[0];
        outTri1.vert2 = insidePoints[1];
        outTri1.vert3 = Vector3D::IntersectPlane(planePoint, planeNormal, insidePoints[0], outsidePoints[0]);

        // Second triangle is composed of one of the inside points, a new point
        // from the intersection of the other side of the triangle and the plane
        // and the newly created point above
        outTri2.vert1 = insidePoints[1];
        outTri2.vert2 = outTri1.vert2;
        outTri2.vert3 = Vector3D::IntersectPlane(planePoint, planeNormal, insidePoints[1], outsidePoints[0]);

        return 2;
    }
    else
    {
        throw std::runtime_error("Something has gone horribly wrong");
    }
}

void SandboxEngine::UpdateCameraFromInput(float fElapsedTime)
{
    // Move camera up down left and right
    if (GetKey(olc::UP).bHeld)
    { 
        m_camera.UpdatePosition(0.0, -8.0 * fElapsedTime, 0.0);
    }
    if (GetKey(olc::DOWN).bHeld)
    {
        m_camera.UpdatePosition(0.0, 8.0 * fElapsedTime, 0.0);
    }
    if (GetKey(olc::LEFT).bHeld)
    {
        m_camera.UpdatePosition(-8.0 * fElapsedTime, 0.0, 0.0);
    }
    if (GetKey(olc::RIGHT).bHeld)
    {
        m_camera.UpdatePosition(8.0 * fElapsedTime, 0.0, 0.0);
    }

    // FPS controls
    if(GetKey(olc::A).bHeld)
    {
        //m_spin += 2.0 * fElapsedTime;
    }
    if (GetKey(olc::D).bHeld)
    {
        //m_spin -= 2.0 * fElapsedTime;
    }
    if (GetKey(olc::W).bHeld)
    {
        m_camera.UpdatePosition(0.0, 0.0, 8.0 * fElapsedTime);
    }
    if (GetKey(olc::S).bHeld)
    {
        m_camera.UpdatePosition(0.0, 0.0, -8.0 * fElapsedTime);
    }

    // Launch the shuttle
    if (GetKey(olc::ENTER).bPressed)
    {
        m_marsShuttle.Launch(m_solarSystem[0].GetMassAndPosition());
    }
}