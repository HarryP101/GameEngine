#include "RotationMatrix4x4.h"
#include <cmath>

RotationMatrix4x4::RotationMatrix4x4(Axis axis, double initialTheta) : m_axis(axis)
{
    switch(axis)
    {
        case Axis::X:
            SetRow(0, 1.0, 0.0, 0.0, 0.0);
            SetRow(1, 0.0, cos(initialTheta * 0.5), sin(initialTheta * 0.5), 0.0);
            SetRow(2, 0.0, -sin(initialTheta * 0.5), cos(initialTheta * 0.5), 0.0);
            SetRow(3, 0.0, 0.0, 0.0, 1.0);
            break;
        case Axis::Y:
            SetRow(0, cos(initialTheta), 0.0, sin(initialTheta), 0.0);
            SetRow(1, 0.0, 1.0, 0.0, 0.0);
            SetRow(2, -sin(initialTheta), 0.0, cos(initialTheta), 0.0);
            SetRow(3, 0.0, 0.0, 0.0, 1.0);
            break;
        case Axis::Z:
            SetRow(0, cos(initialTheta), sin(initialTheta), 0.0, 0.0);
            SetRow(1, -sin(initialTheta), cos(initialTheta), 0.0, 0.0);
            SetRow(2, 0.0, 0.0, 1.0, 0.0);
            SetRow(3, 0.0, 0.0, 0.0, 1.0);
            break;
        default:
            break;
    }
}

void RotationMatrix4x4::Update(double theta)
{
    switch(m_axis)
    {
        case Axis::X:
            m_data[5] = cos(theta * 0.5);
            m_data[6] = sin(theta * 0.5);
            m_data[9] = -sin(theta * 0.5);
            m_data[10] = cos(theta * 0.5);
            break;
        case Axis::Y:
            m_data[0] = cos(theta);
            m_data[2] = sin(theta);
            m_data[8] = -sin(theta);
            m_data[10] = cos(theta);
            break;
        case Axis::Z:
            m_data[0] = cos(theta);
            m_data[1] = sin(theta);
            m_data[4] = -sin(theta);
            m_data[5] = cos(theta);
            break;
        default:
            break;
    }
}