#include "nifty.h"

//This function will read in the map data from a file and put it into a matrix
void readIn(ifstream &file, apmatrix<short> &m) {
    for (int i = 0; i < m.numrows(); i++) {
        for (int j = 0; j < m.numcols(); j++) {
            file >> m[i][j];
        }
    }
}

//find the maximum value of a matrix
void findMax(short &maximum, const apmatrix<short> &m) {
    maximum = 0;

    for (int i = 0; i < m.numrows(); i++) {
        for (int j = 0; j < m.numcols(); j++) {
            if (m[i][j] > maximum) {
                maximum = m[i][j];
            }
        }
    }
}

//find the minimum value of a matrix
void findMin(short &minimum, const apmatrix<short> &m) {
    minimum = m[0][0];

    for (int i = 0; i < m.numrows(); i++) {
        for (int j = 0; j < m.numcols(); j++) {
            if (m[i][j] < minimum) {
                minimum = m[i][j];
            }
        }
    }
}
