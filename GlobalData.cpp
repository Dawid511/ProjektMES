#include "GlobalData.h"
#include <iostream>
using namespace std;

GlobalData::GlobalData()
    : simulationTime(0.0), simulationStepTime(0.0), conductivity(0.0),
    alfa(0.0), tot(0.0), initialTemp(0.0), density(0.0), specificHeat(0.0),
    nodesNumber(0), elementsNumber(0) {
}

double GlobalData::getSimulationTime() const { return simulationTime; }
double GlobalData::getSimulationStepTime() const { return simulationStepTime; }
double GlobalData::getConductivity() const { return conductivity; }
double GlobalData::getAlfa() const { return alfa; }
double GlobalData::getTot() const { return tot; }
double GlobalData::getInitialTemp() const { return initialTemp; }
double GlobalData::getDensity() const { return density; }
double GlobalData::getSpecificHeat() const { return specificHeat; }
int GlobalData::getNodesNumber() const { return nodesNumber; }
int GlobalData::getElementsNumber() const { return elementsNumber; }

void GlobalData::setSimulationTime(double value) { simulationTime = value; }
void GlobalData::setSimulationStepTime(double value) { simulationStepTime = value; }
void GlobalData::setConductivity(double value) { conductivity = value; }
void GlobalData::setAlfa(double value) { alfa = value; }
void GlobalData::setTot(double value) { tot = value; }
void GlobalData::setInitialTemp(double value) { initialTemp = value; }
void GlobalData::setDensity(double value) { density = value; }
void GlobalData::setSpecificHeat(double value) { specificHeat = value; }
void GlobalData::setNodesNumber(int value) { nodesNumber = value; }
void GlobalData::setElementsNumber(int value) { elementsNumber = value; }

void GlobalData::printGlobalData() const {
    cout << "SimulationTime: " << getSimulationTime() << endl;
    cout << "SimulationStepTime: " << getSimulationStepTime() << endl;
    cout << "Conductivity: " << getConductivity() << endl;
    cout << "Alfa: " << getAlfa() << endl;
    cout << "Tot: " << getTot() << endl;
    cout << "InitialTemp: " << getInitialTemp() << endl;
    cout << "Density: " << getDensity() << endl;
    cout << "SpecificHeat: " << getSpecificHeat() << endl;
    cout << "NodesNumber: " << getNodesNumber() << endl;
    cout << "ElementsNumber: " << getElementsNumber() << endl;
}
