#include <iostream>
#include "Grid.h"

using namespace std;

Grid::Grid(int nodesNumber, int elementsNumber)
    : nodes(new Node[nodesNumber]), elements(new Element[elementsNumber]),
    nodesNumber(nodesNumber), elementsNumber(elementsNumber) {
}

Grid::~Grid() {
    delete[] nodes;
    delete[] elements;
}

void Grid::addNode(Node& node, int index) {
    if (index >= 0 && index < nodesNumber) {
        nodes[index] = node;
    }
}

void Grid::addElement(Element& element, int index) {
    if (index >= 0 && index < elementsNumber) {
        elements[index] = element;
    }
}

Node Grid::getNode(int index) const {
    if (index >= 0 && index < nodesNumber) {
        return nodes[index];
    }
}

Element Grid::getElement(int index) const {
    if (index >= 0 && index < elementsNumber) {
        return elements[index];
    }
}

int Grid::getNodesNumber() const {
    return nodesNumber;
}

int Grid::getElementsNumber() const {
    return elementsNumber;
}

void Grid::printNodes(GlobalData gd) {
    for (int i = 0; i < gd.getNodesNumber(); i++) {
        cout << "Node " << i + 1 << ": ";
        nodes[i].printNode();
    }
}

void Grid::printElements(GlobalData gd) {

    for (int i = 0; i < gd.getElementsNumber(); i++) {
        cout << "Element " << i + 1 << ": "; 
        elements[i].printIDs();
    }
    cout << endl;
}


void Grid::Calculate(GlobalData g) {
    GaussTable gaussTable(N);
    UniversalElement u;
    Jacobian jacobian;

    double detHbc = 0;
    double newHbc[4][4];
    double newP[4];
    double newH[4][4];
    double newC[4][4];
    double** dNdx = new double* [N * N];
    double** dNdy = new double* [N * N];

    for (int i = 0; i < N * N; i++) {
        dNdx[i] = new double[4] {};
        dNdy[i] = new double[4] {};
    }


    memset(newHbc, 0, sizeof(newHbc));
    memset(newP, 0, sizeof(newP));
    memset(newH, 0, sizeof(newH));
    memset(newC, 0, sizeof(newC));
    Node nodes_temp[4];

    // iteracja po wszystkich elementach
    for (int k = 0; k < g.getElementsNumber(); k++) {
        int* iDs = elements[k].getNodeIDs();
        nodes_temp[0] = nodes[--iDs[0]]; // minusy zeby dostac sie do odpowiednich indeksw tablicy
        nodes_temp[1] = nodes[--iDs[1]];
        nodes_temp[2] = nodes[--iDs[2]];
        nodes_temp[3] = nodes[--iDs[3]];

        // dNdx dNdy
        for (int i = 0; i < N * N; i++) {
            for (int j = 0; j < 4; j++) {
                jacobian.CalculateJacobian(nodes_temp, i);
                dNdx[i][j] = u.NodeKsi[i][j] * jacobian.matrix[0][0] + u.NodeEta[i][j] * jacobian.matrix[1][0];
                dNdy[i][j] = u.NodeKsi[i][j] * jacobian.matrix[0][1] + u.NodeEta[i][j] * jacobian.matrix[1][1];
            }
        }

        // macierz H
        int index = 0;
        for (int m = 0; m < N; m++) {
            for (int i = 0; i < N; i++) {
   
                jacobian.CalculateJacobian(nodes_temp, index);
                double weight = gaussTable.getWeights()[i] * gaussTable.getWeights()[m];
                for (int j = 0; j < 4; j++)
                    for (int n = 0; n < 4; n++)
                        newH[j][n] += ((dNdx[index][j] * dNdx[index][n]) + (dNdy[index][j] * dNdy[index][n])) * g.getConductivity() * jacobian.det * weight;
                index++;
            }
        }

        // macierz C
        index = 0;
        for (int m = 0; m < N; m++) {
            for (int i = 0; i < N; i++) {

                jacobian.CalculateJacobian(nodes_temp, index);
                double weight = gaussTable.getWeights()[i] * gaussTable.getWeights()[m];
                for (int j = 0; j < 4; j++)
                    for (int n = 0; n < 4; n++)
                        newC[j][n] += (u.shapeTable[index][j] * u.shapeTable[index][n]) * g.getSpecificHeat() * g.getDensity() * jacobian.det * weight;
                index++;
            }
        }

        
        // Macierz Hbc oraz wektor P
        for (int l = 0; l < 4; l++) {   // dla kazdej sciany
            if (l < 3) {
                if ((nodes_temp[l].getBC() != nodes_temp[l + 1].getBC()) || (nodes_temp[l].getBC() != 1) && l < 3)
                    continue;
                detHbc = sqrt(pow(nodes_temp[l].getX() - nodes_temp[l + 1].getX(), 2) + pow(nodes_temp[l].getY() - nodes_temp[l + 1].getY(), 2));
            }
            else {
                if ((nodes_temp[0].getBC() != nodes_temp[3].getBC()) || nodes_temp[0].getBC() != 1)
                    continue;
                detHbc = sqrt(pow(nodes_temp[3].getX() - nodes_temp[0].getX(), 2) + pow(nodes_temp[3].getY() - nodes_temp[0].getY(), 2));
            }
            detHbc /= 2;


            for (int i = 0; i < N; i++) // dla kazdego pc
                for (int j = 0; j < 4; j++) { // petle do sumowania iloczynu macierzy z macierz¹ 
                    for (int n = 0; n < 4; n++)
                        newHbc[j][n] += (u.surface[l].NV[i][j] * u.surface[l].NV[i][n]) * detHbc * gaussTable.getWeights()[i] * g.getAlfa();

                    newP[j] += u.surface[l].NV[i][j] * g.getTot() * gaussTable.getWeights()[i] * g.getAlfa() * detHbc;
                }

        }

        elements[k].setMatrixH(newH);
        elements[k].setVectorP(newP);
        elements[k].setMatrixHbc(newHbc);
        elements[k].setMatrixC(newC);
        memset(newHbc, 0, sizeof(newHbc));
        memset(newP, 0, sizeof(newP));
        memset(newH, 0, sizeof(newH));
        memset(newC, 0, sizeof(newC));
    }


    u.cleanup();
}


