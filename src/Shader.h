#pragma once

#include "olcPixelGameEngine.h"
#include "Planet.h"

class Shader
{
public:
    static olc::Pixel GetColour(double lum, Planet::Colour colour);
};