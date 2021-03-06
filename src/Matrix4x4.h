#pragma once

#include <vector>
#include <ostream>

class Matrix4x4
{
public:
    Matrix4x4();
    double GetValue(size_t row, size_t col) const;
    void SetRow(size_t rowNumber, double col1, double col2, double col3, double col4);

    Matrix4x4 operator*(const Matrix4x4& rhs) const;
    Matrix4x4& operator+=(const Matrix4x4& rhs);

    friend std::ostream& operator<<(std::ostream& stream, const Matrix4x4& matrix4x4);
protected:
    std::vector<double> m_data;
};