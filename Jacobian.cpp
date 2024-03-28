#include "Jacobian.h"

Jacobian::Jacobian() {};
void Jacobian::CalculateJacobian(Node* nodes, int indexN) {
    dxdksi = 0;
    dxdeta = 0;
    dydksi = 0;
    dydeta = 0;
    for (int i = 0; i < 4; i++) {
        dxdeta += nodes[i].getX() * UniversalElement::NodeEta[indexN][i]; 
        dxdksi += nodes[i].getX() * UniversalElement::NodeKsi[indexN][i];
        dydksi += nodes[i].getY() * UniversalElement::NodeKsi[indexN][i];
        dydeta += nodes[i].getY() * UniversalElement::NodeEta[indexN][i]; 
    }
    det = (dxdksi * dydeta) - (dxdeta * dydksi);
    odw_det = 1 / det;

    matrix[0][0] = odw_det * dydeta;
    matrix[0][1] = odw_det * -1.0 * dxdeta;
    matrix[1][0] = odw_det * -1.0 * dydksi;
    matrix[1][1] = odw_det * dxdksi;
}


void Jacobian::printJacobian() {
    using namespace std;
    cout << "|" << dxdksi << " " << dydksi << "|" << endl;
    cout << "|" << dxdeta << " " << dydeta << "|" << endl;
    cout << "det = " << det << endl;
    cout << "1/det = " << odw_det << endl;
}

void Jacobian::printReversedMatrix() {
    using namespace std;
    cout << "|" << matrix[0][0] << " " << matrix[0][1] << "|" << endl;
    cout << "|" << matrix[1][0] << " " << matrix[1][1] << "|" << endl;
    cout << endl;
}