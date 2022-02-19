#pragma once

#include <string>

#include "Mesh.h"

class ObjFileLoader
{
public:
    static Mesh Load(const std::string& fileName);
};