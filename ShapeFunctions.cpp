#include "ShapeFunctions.h"

double ShapeFunctions::dN1_dksi(double eta) {
    return -1.0 / 4.0 * (1 - eta);
}

double ShapeFunctions::dN2_dksi(double eta) {
    return 1.0 / 4.0 * (1 - eta);
}

double ShapeFunctions::dN3_dksi(double eta) {
    return (1.0 / 4.0) * (1 + eta);
}

double ShapeFunctions::dN4_dksi(double eta) {
    return -1.0 / 4.0 * (1 + eta);
}

double ShapeFunctions::dN1_deta(double ksi) {
    return -1.0 / 4.0 * (1 - ksi);
}

double ShapeFunctions::dN2_deta(double ksi) {
    return -1.0 / 4.0 * (1 + ksi);
}

double ShapeFunctions::dN3_deta(double ksi) {
    return 1.0 / 4.0 * (1 + ksi);
}

double ShapeFunctions::dN4_deta(double ksi) {
    return 1.0 / 4.0 * (1 - ksi);
}

double ShapeFunctions::shapeN1(double ksi, double eta) {
    return 0.25 * (1 - ksi) * (1 - eta);
}

double ShapeFunctions::shapeN2(double ksi, double eta) {
    return 0.25 * (1 + ksi) * (1 - eta);
}

double ShapeFunctions::shapeN3(double ksi, double eta) {
    return 0.25 * (1 + ksi) * (1 + eta);
}

double ShapeFunctions::shapeN4(double ksi, double eta) {
    return 0.25 * (1 - ksi) * (1 + eta);
}