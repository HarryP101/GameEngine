#pragma once

#include "Matrix4x4.h"

class ProjectionMatrix : public Matrix4x4
{
public:
    ProjectionMatrix();
    ProjectionMatrix(double aspectRatio, double fieldOfView, double zNear, double zFar);
};