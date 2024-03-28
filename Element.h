#pragma once
#include "UniversalElement.h"
//#include "Grid.h"

class Element {
    int ID[4];
    double H[4][4];
    double Hbc[4][4];
    double C[4][4];
    double P[4];   

public:
    Element();
    Element(int nodeIDs[4]); // Konstruktor z ID wêz³ów

    // Settery
    void setNodeIDs(int nodeIDs[4]);
    void setMatrixH(double H[4][4]);
    void setMatrixHbc(double Hbc[4][4]);
    void setMatrixC(double C[4][4]);
    void setVectorP(double P[4]);

    // Gettery
    int* getNodeIDs();
    double(*getMatrixH())[4];
    double(*getMatrixHbc())[4];
    double(*getMatrixC())[4];
    double* getVectorP();

    void printIDs();
    void printH();
    void printHbc();
    void printC();
    void printP();
    //void CalculateHbc(Grid grid);
   


};