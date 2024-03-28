#pragma once
class ShapeFunctions {
public:
    static double dN1_dksi(double eta);
    static double dN2_dksi(double eta);
    static double dN3_dksi(double eta);
    static double dN4_dksi(double eta);

    static double dN1_deta(double ksi);
    static double dN2_deta(double ksi);
    static double dN3_deta(double ksi);
    static double dN4_deta(double ksi);

    static double shapeN1(double ksi, double eta);
    static double shapeN2(double ksi, double eta);
    static double shapeN3(double ksi, double eta);
    static double shapeN4(double ksi, double eta);
};
