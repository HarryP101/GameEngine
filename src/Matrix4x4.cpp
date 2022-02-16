#include "Matrix4x4.h"

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