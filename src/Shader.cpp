#include "Shader.h"

olc::Pixel Shader::GetColour(double lum, Planet::Colour colour)
{
    uint8_t scaledLum = static_cast<uint8_t>(255.0 * lum);

    switch(colour)
    {
        case Planet::Colour::BLUE:
            return olc::Pixel(0, 0, scaledLum);
            break;
        case Planet::Colour::RED:
            return olc::Pixel(scaledLum, 0, 0);
            break;
        default:
            return olc::Pixel(scaledLum, scaledLum, scaledLum);
    }
}