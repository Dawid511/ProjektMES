#pragma once
#include "Node.h"
#include "Element.h" 
#include "GlobalData.h"
#include "UniversalElement.h"
#include "GaussTable.h"
#include "Jacobian.h"

class Grid {
private:
    Node* nodes;
    Element* elements;
    int nodesNumber;
    int elementsNumber;

public:
    Grid(int nodesNumber, int elementsNumber);
    ~Grid();

    void addNode(Node& node, int index);
    void addElement(Element& element, int index);

    Node getNode(int index) const;
    Element getElement(int index) const;
    int getNodesNumber() const;
    int getElementsNumber() const;

    void Calculate(GlobalData globalData);
   
    void printElements(GlobalData gd);
    void printNodes(GlobalData gd);
 
};