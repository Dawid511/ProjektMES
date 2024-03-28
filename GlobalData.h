#pragma once
class GlobalData {
    double simulationTime;
    double simulationStepTime;
    double conductivity;
    double alfa;
    double tot;
    double initialTemp;
    double density;
    double specificHeat;
    int nodesNumber;
    int elementsNumber;

public:
    GlobalData();


    // Gettery
    double getSimulationTime() const;
    double getSimulationStepTime() const;
    double getConductivity() const;
    double getAlfa() const;
    double getTot() const;
    double getInitialTemp() const;
    double getDensity() const;
    double getSpecificHeat() const;
    int getNodesNumber() const;
    int getElementsNumber() const;

    // Settery
    void setSimulationTime(double value);
    void setSimulationStepTime(double value);
    void setConductivity(double value);
    void setAlfa(double value);
    void setTot(double value);
    void setInitialTemp(double value);
    void setDensity(double value);
    void setSpecificHeat(double value);
    void setNodesNumber(int value);
    void setElementsNumber(int value);


    void printGlobalData() const;
};