#include "Planet.h"

#include <vector>
#include <string>

#include "Vector3D.h"
#include "ObjFileLoader.h"
#include "Triangle.h"

Planet::Planet() : Mesh(), m_position(Vector3D(0.0, 0.0, 0.0)), m_size(0.0) {}

Planet::Planet(const Vector3D& initialPos, double size, const std::string& objFileLocation) : Mesh(objFileLocation), m_position(initialPos), m_size(size) {}

void Planet::UpdatePosAndOrient(double x, double y, double z, double theta)
{
    // TODO: update orientation
    (void)theta;

    m_position = Vector3D(x, y, z);

    for (size_t i = 0; i < m_originalTriangles.size(); ++i)
    {
        m_transformedTriangles[i] = m_originalTriangles[i] + Vector3D(x, y, z);
    }
}