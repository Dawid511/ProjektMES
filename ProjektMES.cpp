#include <iostream>
#include <fstream>
#include <string>
#include "GlobalData.h"
#include "Grid.h"
#include "Node.h"
#include "Element.h"
#include "UniversalElement.h"
#include "GaussTable.h"
#include "Aggregation.h"

using namespace std;

void GaussElimination(double** A, int size);
void BackSubstitution(double** A, double* x, int size);

int main()
{
    //ifstream inputFile("Test1_4_4.txt");
    ifstream inputFile("Test2_4_4_MixGrid.txt");
    //ifstream inputFile("Test3_31_31_kwadrat.txt");
    //ifstream inputFile("Test4_31_31_trapez.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku z danymi." << std::endl;
        return 1;
    }

    // dane globalne
    GlobalData globalData;
    string temps;
    int tempi;
    double tempd;

    inputFile >> temps >> tempi;
    globalData.setSimulationTime(tempi);

    inputFile >> temps >> tempi;
    globalData.setSimulationStepTime(tempi);

    inputFile >> temps >> tempi;
    globalData.setConductivity(tempi);

    inputFile >> temps >> tempi;
    globalData.setAlfa(tempi);

    inputFile >> temps >> tempi;
    globalData.setTot(tempi);

    inputFile >> temps >> tempi;
    globalData.setInitialTemp(tempi);

    inputFile >> temps >> tempi;
    globalData.setDensity(tempi);

    inputFile >> temps >> tempi;
    globalData.setSpecificHeat(tempi);

    inputFile >> temps >> tempi;
    globalData.setNodesNumber(tempi);

    inputFile >> temps >> tempi;
    globalData.setElementsNumber(tempi);

    inputFile >> temps;
    
    // tworzenie siatki na podstawie wczytanych danych
    Grid grid(globalData.getNodesNumber(), globalData.getElementsNumber());

    Node* nodes = new Node[globalData.getNodesNumber()];
    Element element;
    int id[4];

    // wczytanie wezlow
    for (int i = 0; i < globalData.getNodesNumber(); i++) {
        inputFile >> tempi;
        inputFile >> temps;

        inputFile >> tempd;
        nodes[i].setX(tempd);

        inputFile >> temps;

        inputFile >> tempd;
        nodes[i].setY(tempd);
    }
    getline(inputFile, temps);
    getline(inputFile, temps);
    
    // wczytanie elemnetow
    for (int i = 0; i < globalData.getElementsNumber(); ++i) {
        inputFile >> tempi;
        inputFile >> temps;

        inputFile >> id[0];
        inputFile >> temps;
        inputFile >> id[1];
        inputFile >> temps;
        inputFile >> id[2];
        inputFile >> temps;
        inputFile >> id[3];
        element.setNodeIDs(id);
        grid.addElement(element, i);
    }

    getline(inputFile, temps);
    getline(inputFile, temps);

    while(!inputFile.eof()){
        inputFile >> tempi;
        nodes[--tempi].setBC(1);
        inputFile >> temps;
    }
    for (int i = 0; i < globalData.getNodesNumber(); i++) 
        grid.addNode(nodes[i], i);

    inputFile.close();
    delete[] nodes;

    globalData.printGlobalData();
    grid.printNodes(globalData);
    grid.printElements(globalData);
    
    grid.Calculate(globalData);
    Aggregation aggregation(globalData.getNodesNumber());



    int nodesNumber = globalData.getNodesNumber();
    double* temp = new double[nodesNumber];
    for (int i = 0; i < nodesNumber; i++)
        temp[i] = globalData.getInitialTemp();
    int time = globalData.getSimulationStepTime();

   // double* wyn = new double[nodesNumber];
    double** A = new double* [nodesNumber]; // do eliminacji gaussa
    double minT, maxT;
    double* temp2 = new double[nodesNumber];
    for (int i = 0; i < nodesNumber; i++) {
        temp2[i] = globalData.getInitialTemp();;
    }
    for (int i = 0; i < nodesNumber; i++) {
        A[i] = new double[nodesNumber + 1];
    }

    int indexWrite = 0;
    while (time <= globalData.getSimulationTime()) { // symulacja
        for (int i = 0; i < nodesNumber; i++)        // zeruje A
            for (int j = 0; j < nodesNumber + 1; j++) 
                A[i][j] = 0;

        for (int i = 0; i < globalData.getElementsNumber(); i++) 
            aggregation.aggregate(grid.getElement(i), globalData.getSimulationStepTime(), temp2); 
        
        for (int i = 0; i < nodesNumber; i++)           // wyznaczam A
            for (int j = 0; j < nodesNumber + 1; j++)
                if (j < nodesNumber)
                    A[i][j] = aggregation.globalH_C_div_dtau[i][j];
                else
                    A[i][j] = aggregation.globalP[i];
            

        for (int i = 0; i < nodesNumber; i++) {
            for (int j = 0; j < nodesNumber; j++) {
                aggregation.globalH_C_div_dtau[i][j] = 0;
                aggregation.globalC_div_dtau[i][j] = 0;
            }
            aggregation.globalP[i] = 0;
            aggregation.globalBC[i] = 0;
        }
     

        GaussElimination(A, nodesNumber);
        BackSubstitution(A, temp2, nodesNumber);

        minT = temp2[0], maxT = temp2[0];
        for (int i = 0; i < nodesNumber; i++) {
            if (temp2[i] < minT)
                minT = temp2[i];
            if (temp2[i] > maxT)
                maxT = temp2[i];
        }

        cout << "Time: " << time << "  min_T: " << minT << "  max_T: " << maxT << endl;
        time += globalData.getSimulationStepTime();

        
        string str = ("Grid" + to_string(3) + "/Foo" + to_string(indexWrite+1) + ".vtk");
        indexWrite++;
        ofstream outFile(str);

        outFile << "# vtk DataFile Version 2.0\n";
        outFile << "Unstructured Grid Example\n";
        outFile << "ASCII\n";
        outFile << "DATASET UNSTRUCTURED_GRID\n";
        outFile << "\n";

        outFile << ("POINTS " + to_string(globalData.getNodesNumber()) + " float\n");
        for (int i = 0; i < globalData.getNodesNumber(); i++) 
            outFile << grid.getNode(i).getX() << " " << grid.getNode(i).getY() << " 0\n";

        outFile << "\nCELLS " << globalData.getElementsNumber() << " " << (5 * globalData.getElementsNumber()) << "\n";
        for (int i = 0; i < globalData.getElementsNumber(); i++) {
            outFile << "4";
            for (int j = 0; j < 4; j++)
                outFile << " " << grid.getElement(i).getNodeIDs()[j];
            outFile << "\n";
        }
        outFile << "\n";

        //outFile << "CELL_TYPES 9\n";
        outFile << "CELL_TYPES " << globalData.getElementsNumber() << "\n";
        for (int i = 0; i < globalData.getElementsNumber(); i++)
            outFile << "9\n";
        outFile << "\n";

        outFile << "POINT_DATA " << globalData.getNodesNumber() << "\n";
        outFile << "SCALARS Temp float 1\n";
        outFile << "LOOKUP_TABLE default\n";

        for (int i = 0; i < globalData.getNodesNumber(); i++)
            outFile << temp2[i] << "\n";
            
            
    }
    
    return 0;
}




void GaussElimination(double** A, int size) {
    for (int i = 0; i < size; i++) {

        int maxRow = i;
        for (int j = i + 1; j < size; j++)
            if (std::abs(A[j][i]) > std::abs(A[maxRow][i]))
                maxRow = j;

        for (int j = i; j <= size; j++)
            std::swap(A[maxRow][j], A[i][j]);

        for (int j = i + 1; j < size; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k <= size; k++)
                A[j][k] -= factor * A[i][k];
        }
    }
}

void BackSubstitution(double** A, double* x, int size) {
    for (int i = size - 1; i >= 0; i--) {
        x[i] = A[i][size];
        for (int j = i + 1; j < size; j++)
            x[i] -= A[i][j] * x[j];

        x[i] /= A[i][i];
    }
}
