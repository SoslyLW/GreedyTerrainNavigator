#include "nifty.h"

//This function will read in the map data from a file and put it into a matrix
void readIn(ifstream &file, short m[mapRows][mapCols]) {
    for (int i = 0; i < mapRows; i++) {
        for (int j = 0; j < mapCols; j++) {
            file >> m[i][j];
        }
    }
}

//find the maximum value of a matrix
void findMax(short &maximum, const short m[mapRows][mapCols]) {
    maximum = 0;

    for (int i = 0; i < mapRows; i++) {
        for (int j = 0; j < mapCols; j++) {
            if (m[i][j] > maximum) {
                maximum = m[i][j];
            }
        }
    }
}

//find the minimum value of a matrix
void findMin(short &minimum, const short m[mapRows][mapCols]) {
    minimum = m[0][0];

    for (int i = 0; i < mapRows; i++) {
        for (int j = 0; j < mapCols; j++) {
            if (m[i][j] < minimum) {
                minimum = m[i][j];
            }
        }
    }
}
