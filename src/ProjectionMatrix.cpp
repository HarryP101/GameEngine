#include "ProjectionMatrix.h"

ProjectionMatrix::ProjectionMatrix() : Matrix4x4() {}

ProjectionMatrix::ProjectionMatrix(double aspectRatio, double fieldOfView, double zNear, double zFar)
{
    SetRow(0, aspectRatio * fieldOfView, 0.0, 0.0, 0.0);
    SetRow(1, 0.0, fieldOfView, 0.0, 0.0);
    SetRow(2, 0.0, 0.0, zFar / (zFar - zNear), 1.0);
    SetRow(3, 0.0, 0.0, -(zFar * zNear) / (zFar - zNear), 0.0);
}