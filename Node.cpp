#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(double x, double y, int BC) : x(x), y(y), BC(BC) {}
Node::Node() : x(-1), y(-1), BC(0) {}

double Node::getX() const {
    return x;
}

double Node::getY() const {
    return y;
}

int Node::getBC() const {
    return BC;
}

void Node::setX(double x) {
    this->x = x;
}

void Node::setY(double y) {
    this->y = y;
}

void Node::setBC(int BC) {
    this->BC = BC;
}

void Node::printNode() {
        cout << "x: " << this->x << " y, " << this->y << " warunek brzegowy: " << this->BC << endl;
}