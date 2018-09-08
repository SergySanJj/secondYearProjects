/**
 * @brief
 * This module is used to represent backend part of 
 * VectorField datastructure.
 * 
 * @usage
 * VFMatrix stores values of common matrixes and provides
 * some methods to do calculations.
 * 
 */ 

#pragma once

#include <stdlib.h>
#include <algorithm>
#include <array>
#include <iostream>

 using std::array;
 using std::size_t;

class VFMatrix
{
public:
    VFMatrix(size_t N);
    ~VFMatrix();
    VFMatrix(const VFMatrix& other);
    VFMatrix& operator=(VFMatrix rhs);

    const void print();

    void swap(VFMatrix & other);

    size_t size() { return N; }
private:
    size_t N;
    size_t Total;
    double* matrix;
protected:
};
