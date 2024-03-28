#include "GaussTable.h"
#include <iostream>

GaussTable::GaussTable(int points) : pointsNumber(points) {
    initialize(points); 
}

void GaussTable::initialize(int n) {
    nodes = new double[n];
    weights = new double[n];

    switch (n) {
    case 2:
        nodes[0] = -sqrt(3.0) / 3.0;
        nodes[1] = sqrt(3.0) / 3.0;
        weights[0] = 1.0;
        weights[1] = 1.0;
        break;
    case 3:
        nodes[0] = -sqrt(3.0 / 5.0);
        nodes[1] = 0;
        nodes[2] = sqrt(3.0 / 5.0);
        weights[0] = 5.0 / 9.0;
        weights[1] = 8.0 / 9.0;
        weights[2] = 5.0 / 9.0;
        break;
    case 4:
        nodes[0] = -sqrt((3.0 / 7.0) + (2.0 / 7.0 * sqrt(6.0 / 5.0)));
        nodes[1] = -sqrt((3.0 / 7.0) - (2.0 / 7.0 * sqrt(6.0 / 5.0)));
        nodes[2] = sqrt((3.0 / 7.0) - (2.0 / 7.0 * sqrt(6.0 / 5.0)));
        nodes[3] = sqrt((3.0 / 7.0) + (2.0 / 7.0 * sqrt(6.0 / 5.0)));
        weights[1] = (18.0 + sqrt(30)) / 36.0;
        weights[0] = (18.0 - sqrt(30)) / 36.0;
        weights[3] = (18.0 - sqrt(30)) / 36.0;
        weights[2] = (18.0 + sqrt(30)) / 36.0;
        break;
    }
}

double* GaussTable::getNodes() {
    return nodes;
}

double* GaussTable::getWeights() {
    return weights;
}

int GaussTable::getPointsNumber() {
    return pointsNumber;
}

GaussTable::~GaussTable() {
    delete[] nodes;
    delete[] weights;
}
