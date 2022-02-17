#pragma once

#include "Matrix4x4.h"

class RotationMatrix4x4 : public Matrix4x4
{
public:
    enum class Axis { X, Y, Z };

    RotationMatrix4x4(Axis axis, double initialTheta);

    void Update(double theta);

private:
    Axis m_axis;
};