#include "VFMatrix.h"

VFMatrix::VFMatrix(size_t N) : N(N), Total(N * N)
{
    matrix = new double[Total];
    for (size_t elem = 0; elem < Total; elem++)
        matrix[elem] = 0.0;
}

VFMatrix::~VFMatrix()
{
    delete[] matrix;
}

VFMatrix::VFMatrix(const VFMatrix &other)
{
    delete[] matrix;
    N = other.N;
    Total = N * N;

    matrix = new double[Total];

    for (size_t elem = 0; elem < Total; elem++)
    {
        matrix[elem] = other.matrix[elem];
    }
}

VFMatrix &VFMatrix::operator=(VFMatrix rhs)
{
    swap(rhs);
    return *this;
}

const void VFMatrix::print()
{
    for (size_t elem = 0; elem < Total; elem++)
    {
        std::cout << matrix[elem] << ' ';
        if (elem % N == 0 && elem != 0)
            std::cout << '\n';
    }
    std::cout << '\n';
}

void VFMatrix::swap(VFMatrix &other)
{
    using std::swap;
    swap(N, other.N);
    swap(Total, other.Total);
    swap(matrix, other.matrix);
}