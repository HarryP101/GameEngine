#define OLC_PGE_APPLICATION

#include "SandboxEngine.h"
#include <algorithm>
#include <vector>
#include <list>

#include "Mesh.h"
#include "Triangle.h"
#include "Vector3D.h"
#include "Constants.h"
#include "RotationMatrix4x4.h"
#include "Shader.h"

SandboxEngine::SandboxEngine() : m_camera(0.0, 0.0, 0.0), m_lookDirection(0.0, 0.0, 1.0), m_rotateX(RotationMatrix4x4::Axis::X, 0.0),
    m_rotateY(RotationMatrix4x4::Axis::Y, 0.0), m_rotateZ(RotationMatrix4x4::Axis::Z, 0.0), m_theta(0.0), m_yaw(0.0)
{
    sAppName = "Harrys Example";
}

bool SandboxEngine::OnUserCreate()
{
    // Called once at the start, so create things here

    // Set up unit cube
    m_meshCube = Mesh::CreateCoolShip("sampleobjects/teapot.obj");

    // Set up projection matrix
    constexpr double zNear = 0.1;
    constexpr double zFar = 1000.0;
    constexpr double fov = 90.0;
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
    const Vector3D userMoveY(0.0, -1.0, 0.0);
    const Vector3D userMoveX(-1.0, 0.0, 0.0);

    const Vector3D zNearPlane(0.0, 0.0, 0.1);
    const Vector3D zNormal(0.0, 0.0, 1.0);

    // Move camera up down left and right
    if (GetKey(olc::UP).bHeld)
    { 
        m_camera += userMoveY * 8.0 * fElapsedTime;
    }
    if (GetKey(olc::DOWN).bHeld)
    {
        m_camera -= userMoveY * 8.0 * fElapsedTime;
    }
    if (GetKey(olc::LEFT).bHeld)
    {
        auto temp = userMoveX * m_rotateY; 
        m_camera += temp * 8.0 * fElapsedTime;
    }
    if (GetKey(olc::RIGHT).bHeld)
    {
        auto temp = userMoveX * m_rotateY;
        m_camera -= temp * 8.0 * fElapsedTime;
    }

    // FPS controls
    Vector3D vForward = m_lookDirection * 8.0 * fElapsedTime;
    if(GetKey(olc::A).bHeld)
    {
        m_yaw += 2.0 * fElapsedTime;
    }
    if (GetKey(olc::D).bHeld)
    {
        m_yaw -= 2.0 * fElapsedTime;
    }
    if (GetKey(olc::W).bHeld)
    {
        m_camera += vForward;
    }
    if (GetKey(olc::S).bHeld)
    {
        m_camera -= vForward;
    }

    m_theta += 1.0 * static_cast<double>(fElapsedTime);

    //m_rotateZ.Update(m_theta);

    // Naughty... this should be given a better name to separate it from the random spinning...
    m_rotateY.Update(m_yaw);

    //m_rotateX.Update(m_theta);

    Matrix4x4 worldMatrix = m_rotateZ * m_rotateX;
    Vector3D translation(0.0, 0.0, 8.0);
    Vector3D one(1.0, 1.0, 0.0);
    Vector3D xyzScaling(0.5 * static_cast<double>(ScreenWidth()), 0.5 * static_cast<double>(ScreenHeight()), 1.0);
    Vector3D lightDirection(0.0, 0.0, -1.0);
    lightDirection.Normalise();

    // called once per frame
    auto triangles = m_meshCube.GetTriangles();

    Vector3D vUp(0.0, -1.0, 0.0);
    Vector3D vTarget(0.0, 0.0, 1.0);
    m_lookDirection = vTarget * m_rotateY;
    vTarget = m_camera + m_lookDirection;

    Matrix4x4 cameraView = CreateLookAtMatrix(m_camera, vTarget, vUp);

    std::vector<Triangle> trisToRaster;
    // Determine which triangles to draw
    for (auto& tri : triangles)
    {
        tri *= worldMatrix;
        tri += translation;

        Vector3D line1 = tri.vert2 - tri.vert1;
        Vector3D line2 = tri.vert3 - tri.vert1;

        Vector3D normal = line1.Cross(line2);
        normal.Normalise();

        // Can choose any vertice here as the triangle exists in a plane
        if ((normal.Dot(tri.vert1 - m_camera)) < 0.0)
        {
            // Illumination
            double dp = normal.Dot(m_lookDirection.Scale(Vector3D(-1.0, -1.0, -1.0)));

            olc::Pixel s = Shader::GetColour(dp);
            tri.illum = s;

            // Convert world space to view space
            tri *= cameraView;

            // Clip viewed triangle against near plane. This could form up to two additional triangles
            std::vector<Triangle> clippedTris(2, Triangle(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0)));

            unsigned int nClippedTriangles = ClipAgainstPlane(zNearPlane, zNormal, tri, clippedTris[0], clippedTris[1]);

            for (unsigned int n = 0; n < nClippedTriangles; ++n)
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

    std::sort(trisToRaster.begin(), trisToRaster.end(), [](Triangle &t1, Triangle &t2){ return t1.GetCentroid().GetZ() > t2.GetCentroid().GetZ(); });
    
    Clear(olc::BLACK);

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

    return true;
}

Matrix4x4 SandboxEngine::CreateLookAtMatrix(const Vector3D& pos, const Vector3D& target, const Vector3D& up) const
{
    Matrix4x4 lookAt;

    // Calculate new forward direction
    Vector3D newForward = target - pos;
    newForward.Normalise();

    // Calculate new up direction
    Vector3D a = newForward * up.Dot(newForward);
    Vector3D newUp = up - a;
    newUp.Normalise();

    Vector3D newRight = newUp.Cross(newForward);

    lookAt.SetRow(0, newRight.GetX(), newUp.GetX(), newForward.GetX(), 0.0);
    lookAt.SetRow(1, newRight.GetY(), newUp.GetY(), newForward.GetY(), 0.0);
    lookAt.SetRow(2, newRight.GetZ(), newUp.GetZ(), newForward.GetZ(), 0.0);

    double t1 = -(pos.GetX() * newRight.GetX() + pos.GetY() * newUp.GetX() + pos.GetZ() * newForward.GetX());
    double t2 = -(pos.GetX() * newRight.GetY() + pos.GetY() * newUp.GetY() + pos.GetZ() * newForward.GetY());
    double t3 = -(pos.GetX() * newRight.GetZ() + pos.GetY() * newUp.GetZ() + pos.GetZ() * newForward.GetZ());

    lookAt.SetRow(3, t1, t2, t3, 1.0);

    return lookAt;
}

unsigned int SandboxEngine::ClipAgainstPlane(const Vector3D& planePoint, Vector3D planeNormal, const Triangle& inputTriangle,
    Triangle &outTri1, Triangle &outTri2) const
{
    // Ensure it has been normalised
    planeNormal.Normalise();

    // Return shortest distance from point to plane
    auto shortestDist = [planePoint, planeNormal](Vector3D p)
    {
        p.Normalise();
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
        return 0U;
    }
    else if (nInsidePointCount == 3)
    {
        // All points lie on the inside of the plane. Do nothing
        outTri1 = inputTriangle;

        return 1U;
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

        return 1U;
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

        return 2U;
    }
    else
    {
        throw std::runtime_error("Something has gone horribly wrong");
    }
}
