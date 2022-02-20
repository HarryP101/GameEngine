#include "Matrix4x4.h"
#include <ostream>

constexpr size_t NROWS = 4;
constexpr size_t NCOLS = 4;
constexpr size_t MAX_ELEMENTS = NROWS * NCOLS;

Matrix4x4::Matrix4x4() : m_data(MAX_ELEMENTS, 0.0) {}

double Matrix4x4::GetValue(size_t row, size_t col) const
{
    return m_data[row * NCOLS + col];
}

void Matrix4x4::SetRow(size_t row, double col1, double col2, double col3, double col4)
{
    m_data[row*NCOLS] = col1;
    m_data[row*NCOLS + 1] = col2;
    m_data[row*NCOLS + 2] = col3;
    m_data[row*NCOLS + 3] = col4;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
{
    Matrix4x4 result;

    for (size_t row = 0; row < NROWS; ++row)
    {
        for (size_t col = 0; col < NCOLS; ++col)
        {
            double value = 0.0;
            for (size_t k = 0; k < 4; ++k)
            {
                value += m_data[row * 4 + k] * rhs.GetValue(k, col);
            }
            result.m_data[row * 4 + col] = value;
        }
    }

    return result;
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
{
    for (size_t row = 0; row < 4; ++row)
    {
        SetRow(row, GetValue(row, 0) + rhs.GetValue(row, 0),
            GetValue(row, 1) + rhs.GetValue(row, 1),
            GetValue(row, 2) + rhs.GetValue(row, 2),
            GetValue(row, 3) + rhs.GetValue(row, 3));
    }

    return *this;
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