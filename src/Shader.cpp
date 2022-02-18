#include "Shader.h"
#include <iostream>

olc::Pixel Shader::GetColour(double lum)
{
    uint8_t scaledLum = static_cast<uint8_t>(255.0 * lum);

    return olc::Pixel(scaledLum, scaledLum, scaledLum);
}