#include "Element.h"
#include <iostream>
#include <cstring> // dla std::memcpy


using namespace std;

Element::Element() {
    memset(ID, 0, sizeof(ID));
    memset(H, 0, sizeof(H));
    memset(Hbc, 0, sizeof(Hbc));
    memset(C, 0, sizeof(C));
    memset(P, 0, sizeof(P));
}

void Element::setNodeIDs(int nodeIDs[4]) {
    memcpy(this->ID, nodeIDs, sizeof(this->ID));
}

void Element::setMatrixH(double H[4][4]) {
    memcpy(this->H, H, sizeof(this->H));
}

void Element::setMatrixHbc(double Hbc[4][4]) {
    memcpy(this->Hbc, Hbc, sizeof(this->Hbc));
}

void Element::setMatrixC(double C[4][4]) {
    memcpy(this->C, C, sizeof(this->C));
}

void Element::setVectorP(double P[4]) {
    memcpy(this->P, P, sizeof(this->P));
}

int* Element::getNodeIDs() {
    return ID;
}

double(*Element::getMatrixH())[4] {
    return H;
}

double(*Element::getMatrixHbc())[4] {
    return Hbc;
}

double(*Element::getMatrixC())[4] {
    return C;
}

double* Element::getVectorP() {
    return P;
}

void Element::printIDs() {
        for (int i = 0; i < 4; i++) 
            cout << ID[i] << ", ";
        cout << endl;
}

void Element::printHbc() {
    cout << endl << "Hbc:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << Hbc[i][j] << " ";
        }
        cout << endl;
    }
}

void Element::printH() {
    cout << endl << "H:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << H[i][j] << " ";
        }
        cout << endl;
    }
}

void Element::printC() {
    cout << endl << "C:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
}

void Element::printP() {
    cout << endl << "P:" << endl;
    for (int i = 0; i < 4; i++) 
        cout << P[i] << " ";
        cout << endl;
}
