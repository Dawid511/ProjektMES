#include "Aggregation.h"
using namespace std;

Aggregation::Aggregation(int nodesNumber) : nodesNumber(nodesNumber) {
	globalH_C_div_dtau = new double* [nodesNumber];
	globalC_div_dtau = new double* [nodesNumber];
	globalP = new double[nodesNumber];
	globalBC = new double[nodesNumber];
	for (int i = 0; i < nodesNumber; i++) {
		globalH_C_div_dtau[i] = new double[nodesNumber];
		globalC_div_dtau[i] = new double[nodesNumber];
	}
	for (int i = 0; i < nodesNumber; i++) {
		for (int j = 0; j < nodesNumber; j++) {
			globalH_C_div_dtau[i][j] = 0;
			globalC_div_dtau[i][j] = 0;
		}
		globalP[i] = 0;
		globalBC[i] = 0;
	}

};

void Aggregation::aggregate(Element elements, double dT, double* temp) {
	int* id = elements.getNodeIDs();
	double pom3[4];
	memset(pom3, 0, sizeof(pom3));
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
			
				globalH_C_div_dtau[id[i]][id[j]] += elements.getMatrixH()[i][j];
				globalH_C_div_dtau[id[i]][id[j]] += elements.getMatrixHbc()[i][j];
				globalH_C_div_dtau[id[i]][id[j]] += elements.getMatrixC()[i][j]/dT;

				globalC_div_dtau[id[i]][id[j]] += elements.getMatrixC()[i][j] / dT;
				pom3[i] += (elements.getMatrixC()[i][j] / dT)*temp[id[j]];
			}	
		}
		for (int i = 0; i < 4; i++)
			globalP[id[i]] += elements.getVectorP()[i] + pom3[i];

		

}


void Aggregation::printGlobalH_C_div_dtau() {
	cout << "GlobalH_C_div_dtau:" << endl;
	for (int i = 0; i < nodesNumber; i++){
		for (int j = 0; j < nodesNumber; j++) 
			cout<< globalH_C_div_dtau[i][j] << " ";
		cout << endl;
	}
}

void Aggregation::printGlobalC_div_dtau() {
	cout << "GlobalC_div_dtau:" << endl;
	for (int i = 0; i < nodesNumber; i++) {
		for (int j = 0; j < nodesNumber; j++)
			cout << globalC_div_dtau[i][j] << " ";
		cout << endl;
	}
}

void Aggregation::printGlobalP() {
	cout << "GlobalP:" << endl;
	for (int i = 0; i < nodesNumber; i++) 
			cout << globalP[i] << " ";
	cout << endl;
}



Aggregation::~Aggregation() {
	for (int i = 0; i < nodesNumber; i++) {
		delete[] globalH_C_div_dtau[i];
		delete[] globalC_div_dtau[i];
	}

	delete[] globalH_C_div_dtau;
	delete[] globalC_div_dtau;
	delete[] globalP;
	delete[] globalBC;
}
