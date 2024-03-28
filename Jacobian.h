#pragma once
#include "Node.h"
#include "ShapeFunctions.h"
#include "UniversalElement.h"
#include <iostream>

class Jacobian {
public:
	double dxdksi, dxdeta, dydksi, dydeta, det, odw_det;
    double matrix[2][2];
    Jacobian();
    void CalculateJacobian(Node* nodes, int n);
    void printJacobian();
    void printReversedMatrix();
};

