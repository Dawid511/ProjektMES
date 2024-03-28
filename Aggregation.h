#pragma once
#include "UniversalElement.h"
#include <cstring>
#include <iostream>
#include "GlobalData.h"
#include "Grid.h"

class Aggregation{
public:
	int nodesNumber;
	double** globalH_C_div_dtau;
	double** globalC_div_dtau;
	double* globalP;
	double* globalBC;

	//Aggregation();
	~Aggregation();
	Aggregation(int nodesNumber);
	void aggregate(Element elements, double dT, double* temp);
	void printGlobalH_C_div_dtau();
	void printGlobalC_div_dtau();
	void printGlobalP();
	
};

