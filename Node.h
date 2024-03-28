#pragma once
class Node {
private:
    double x;
    double y;
    int BC;

public:
    Node();
    Node(double x, double y, int BC);

    double getX() const;
    double getY() const;
    int getBC() const;

    void setX(double x);
    void setY(double y);
    void setBC(int BC);

    void printNode();
};