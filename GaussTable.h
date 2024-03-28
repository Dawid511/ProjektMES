#pragma once
class GaussTable {
    double* nodes;
    double* weights;
    int pointsNumber;
   
public:
    GaussTable(int points);

    void initialize(int n);
    double* getNodes();
    double* getWeights();
    int getPointsNumber();
    ~GaussTable();
};