#pragma once

#include <string>
#include <vector>

#include "Triangle.h"

class ObjFileLoader
{
public:
    static std::vector<Triangle> Load(const std::string& fileName);
};