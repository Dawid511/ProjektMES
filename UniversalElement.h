#pragma once
const int N = 2;

class UniversalElement {
public:
    struct Surface {
        double** NV;

        Surface();
        ~Surface();
    };

    UniversalElement();
    ~UniversalElement();
    void cleanup();

    void printNodes();
    void printSurface();
    void printShapeTable();

    static double** NodeKsi;
    static double** NodeEta;
    static double** shapeTable;
    Surface surface[4];
}; 
