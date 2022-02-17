#include "Matrix4x4.h"
#include <ostream>

constexpr size_t MAX_ELEMENTS = 16;

Matrix4x4::Matrix4x4() : m_data(MAX_ELEMENTS, 0.0) {}

double Matrix4x4::GetValue(size_t row, size_t col) const
{
    return m_data[row * 4 + col];
}

void Matrix4x4::SetRow(size_t row, double col1, double col2, double col3, double col4)
{
    m_data[row*4] = col1;
    m_data[row*4 + 1] = col2;
    m_data[row*4 + 2] = col3;
    m_data[row*4 + 3] = col4;
}

std::ostream& operator<<(std::ostream& stream, const Matrix4x4& matrix4x4)
{
    for (size_t row = 0; row < 4; ++row)
    {
        for (size_t col = 0; col < 4; ++col)
        {
            stream << matrix4x4.m_data[row * 4 + col] << " ";
        }
        stream << '\n';
    }

    return stream;
}