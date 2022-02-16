#pragma once

#include <vector>

class Matrix4x4
{
public:
    double GetValue(size_t row, size_t col) const;
    void SetRow(size_t rowNumber, double col1, double col2, double col3, double col4);
private:
    std::vector<double> m_data;
};