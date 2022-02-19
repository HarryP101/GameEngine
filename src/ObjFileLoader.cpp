#include "ObjFileLoader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Vector3D.h"
#include "Triangle.h"

Mesh ObjFileLoader::Load(const std::string& filename)
{
    std::ifstream f(filename);
    if (!f.is_open())
    {
        throw std::runtime_error("Cannot open file " + filename);
    }
    else
    {
        // Local cache of vertices
        std::vector<Vector3D> vertices;

        std::vector<Triangle> triangles;

        while (!f.eof())
        {
            std::string line;

            std::getline(f, line);

            std::stringstream lineStream;
            lineStream << line;

            char junk;

            if (line[0] == 'v')
            {
                double x, y, z;
                lineStream >> junk >> x >> y >> z;

                vertices.push_back(Vector3D(x, y, z));
            }

            if (line[0] == 'f')
            {
                size_t i1, i2, i3;
                lineStream >> junk >> i1 >> i2 >> i3;

                triangles.push_back(Triangle(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]));
            }
        }
        return Mesh(triangles);
    }
}