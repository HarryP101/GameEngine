#include "MarsShuttle.h"

bool MarsShuttle::Launch()
{
    return true;
}

void MarsShuttle::UpdatePosition(float fElapsedTime, const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars)
{
    UpdateAcceleration(earth, mars);

    // Update velocity from acceleration

    // Update position from velocity
}

void MarsShuttle::UpdateAcceleration(const Planet::MassAndPosition& earth, const Planet::MassAndPosition& mars)
{

}