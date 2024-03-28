#include "UniversalElement.h"
#include "ShapeFunctions.h"
#include "GaussTable.h"
#include <iostream>
#include <cmath>
using namespace std;

double** UniversalElement::NodeKsi = nullptr;
double** UniversalElement::NodeEta = nullptr;
double** UniversalElement::shapeTable = nullptr;



UniversalElement::Surface::Surface() {
    NV = new double* [N];
    for (int i = 0; i < N; i++)
        NV[i] = new double[4] {};
}

UniversalElement::Surface::~Surface() {
    for (int i = 0; i < N; i++)
        delete[] NV[i];
    delete[] NV;
}

UniversalElement::UniversalElement() {
    NodeKsi = new double* [N * N];
    NodeEta = new double* [N * N];
    shapeTable = new double* [N * N];

    for (int i = 0; i < N * N; i++) {
        NodeKsi[i] = new double[4] {};
        NodeEta[i] = new double[4] {};
        shapeTable[i] = new double[4] {};
    }
    GaussTable gaussTable(N);
    double* nodes = gaussTable.getNodes();
    double* weights = gaussTable.getWeights();
    // do Hbc i P
    for (int j = 0; j < N; j++) {
        surface[0].NV[j][0] = ShapeFunctions::shapeN1(nodes[j], -1);
        surface[0].NV[j][1] = ShapeFunctions::shapeN2(nodes[j], -1);
        surface[0].NV[j][2] = ShapeFunctions::shapeN3(nodes[j], -1);
        surface[0].NV[j][3] = ShapeFunctions::shapeN4(nodes[j], -1);
    }

    for (int j = 0; j < N; j++) {
        surface[1].NV[j][0] = ShapeFunctions::shapeN1(1, nodes[j]);
        surface[1].NV[j][1] = ShapeFunctions::shapeN2(1, nodes[j]);
        surface[1].NV[j][2] = ShapeFunctions::shapeN3(1, nodes[j]);
        surface[1].NV[j][3] = ShapeFunctions::shapeN4(1, nodes[j]);
    }

    for (int j = 0; j < N; j++) {
        surface[2].NV[j][0] = ShapeFunctions::shapeN1(-nodes[j], 1);
        surface[2].NV[j][1] = ShapeFunctions::shapeN2(-nodes[j], 1);
        surface[2].NV[j][2] = ShapeFunctions::shapeN3(-nodes[j], 1);
        surface[2].NV[j][3] = ShapeFunctions::shapeN4(-nodes[j], 1);
    }

    for (int j = 0; j < N; j++) {
        surface[3].NV[j][0] = ShapeFunctions::shapeN1(-1, nodes[j]);
        surface[3].NV[j][1] = ShapeFunctions::shapeN2(-1, nodes[j]);
        surface[3].NV[j][2] = ShapeFunctions::shapeN3(-1, nodes[j]);
        surface[3].NV[j][3] = ShapeFunctions::shapeN4(-1, nodes[j]);
    }

    // do C
    for (int i = 0; i < N * N; i++) {
       
            shapeTable[i][0] = ShapeFunctions::shapeN1(nodes[i%N], nodes[i/N]);
            shapeTable[i][1] = ShapeFunctions::shapeN2(nodes[i%N], nodes[i/N]);
            shapeTable[i][2] = ShapeFunctions::shapeN3(nodes[i%N], nodes[i/N]);
            shapeTable[i][3] = ShapeFunctions::shapeN4(nodes[i%N], nodes[i/N]);
        
    }
    // do H
    for (int i = 0; i < N * N; i++) {
        
            NodeKsi[i][0] = ShapeFunctions::dN1_dksi(nodes[i / N]);
            NodeKsi[i][1] = ShapeFunctions::dN2_dksi(nodes[i / N]);
            NodeKsi[i][2] = ShapeFunctions::dN3_dksi(nodes[i / N]);
            NodeKsi[i][3] = ShapeFunctions::dN4_dksi(nodes[i / N]);

            NodeEta[i][0] = ShapeFunctions::dN1_deta(nodes[i % N]);
            NodeEta[i][1] = ShapeFunctions::dN2_deta(nodes[i % N]);
            NodeEta[i][2] = ShapeFunctions::dN3_deta(nodes[i % N]);
            NodeEta[i][3] = ShapeFunctions::dN4_deta(nodes[i % N]);
        
    }


}


void UniversalElement::printNodes() {
    cout << endl << "NodeKsi:" << endl;
    for (int i = 0; i < N * N; i++) {
        for (int j = 0; j < 4; j++) {
            cout << NodeKsi[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "NodeEta:" << endl;
    for (int i = 0; i < N * N; i++) {
        for (int j = 0; j < 4; j++) {
            cout << NodeEta[i][j] << " ";
        }
        cout << endl;
    }
}

void UniversalElement::printSurface() {
    cout << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Surface: " << i << endl;

        for (int k = 0; k < N; k++) {
            cout << " punkt " << k << ":" << endl;
            for (int j = 0; j < 4; j++)
                cout << surface[i].NV[k][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
}

void UniversalElement::printShapeTable() {
    cout << endl << "ShapeTable:" << endl;
    for (int i = 0; i < N * N; i++) {
        for (int j = 0; j < 4; j++)
            cout << shapeTable[i][j] << " ";

        cout << endl;
    }
}

UniversalElement::~UniversalElement(){
}

void UniversalElement::cleanup() {
    for (int i = 0; i < N * N; i++) {
        delete[] NodeKsi[i];
        delete[] NodeEta[i];
        delete[] shapeTable[i];
    }
    delete[] NodeKsi;
    delete[] NodeEta;
    delete[] shapeTable;
}