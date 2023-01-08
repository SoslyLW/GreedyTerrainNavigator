#include "nifty.h"

//finds the best path in an array of paths
void findBestPath(Path p[], int &best) {
    int minimum = 1000000;

    for (int i = 0; i < mapRows; i++) {
        if (p[i].change < minimum) {
            minimum = p[i].change;
            best = i;
        }
    }
    p[best].best = true;
}

//calculate the greedy walk paths
void calcLowestElevPaths(const apmatrix<short> &m, Coordinate &c, Path p[]) {
    for (int i = 0; i < m.numrows(); i++) {
        c.x = 0;
        c.y = i;

        while (c.x < m.numcols() - 1) {
            moveOne(m, c, p[i]);
        }
    }
}

//calculate the stay low paths
void calcStayLowPaths(const apmatrix<short> &m, Coordinate &c, Path p[]) {
    for (int i = 0; i < m.numrows(); i++) {
        c.x = 0;
        c.y = i;

        while (c.x < m.numcols() - 1) {
            moveLow(m, c, p[i]);
        }
    }
}

//move one space for the stay low walk
void moveLow(const apmatrix<short> &m, Coordinate &c, Path &p) {
    //if on top row
    if (c.y == 0) {
        //options
        int differences[2];
        differences[0] = m[c.y][c.x + 1] - m[c.y][c.x];
        differences[1] = m[c.y + 1][c.x + 1] - m[c.y][c.x];

        //logic
        if (differences[1] < differences[0]) {
            c.y++;
            p.directions.push_back(1);
            p.change += abs(differences[1]);
        } else {
            p.directions.push_back(0);
            p.change += abs(differences[0]);
        }
    //if on bottom row
    } else if (c.y == m.numrows() - 1) {
        //options
        int differences[2];
        differences[0] = m[c.y][c.x + 1] - m[c.y][c.x];
        differences[1] = m[c.y - 1][c.x + 1] - m[c.y][c.x];

        //logic
        if (differences[1] < differences[0]) {
            c.y--;
            p.directions.push_back(-1);
            p.change += abs(differences[1]);
        } else {
            p.directions.push_back(0);
            p.change += abs(differences[0]);
        }
    //if in middle
    } else {
        //options
        int differences[3];
        differences[0] = m[c.y - 1][c.x + 1] - m[c.y][c.x];
        differences[1] = m[c.y][c.x + 1] - m[c.y][c.x];
        differences[2] = m[c.y + 1][c.x + 1] - m[c.y][c.x];

        //logic
        if (differences[0] == differences[2] && differences[0] < differences[1]) {
            if (headFlip()) {
                c.y--;
                p.directions.push_back(-1);
                p.change += abs(differences[0]);
            } else {
                c.y++;
                p.directions.push_back(1);
                p.change += abs(differences[2]);
            }
        } else if (differences[0] < differences[1] && differences[0] < differences[2]) {
            c.y--;
            p.directions.push_back(-1);
            p.change += abs(differences[0]);
        } else if (differences[2] < differences[1] && differences[2] < differences[0]) {
            c.y++;
            p.directions.push_back(1);
            p.change += abs(differences[2]);
        } else if (differences[1] < differences[0] && differences[1] < differences[2]) {
            p.directions.push_back(0);
            p.change += abs(differences[1]);
        } else if (differences[1] == differences[0] || differences[1] == differences[2]) {
            p.directions.push_back(0);
            p.change += abs(differences[1]);
        }
    }

    //move over one
    c.x++;
}

//move one space for greedy walk
void moveOne(const apmatrix<short> &m, Coordinate &c, Path &p) {
    //if on top row
    if (c.y == 0) {
        //options
        int differences[2];
        differences[0] = abs(m[c.y][c.x + 1] - m[c.y][c.x]);
        differences[1] = abs(m[c.y + 1][c.x + 1] - m[c.y][c.x]);

        //logic
        if (differences[0] > differences[1]) {
            c.y++;
            p.directions.push_back(1);
            p.change += differences[1];
        } else {
            p.directions.push_back(0);
            p.change += differences[0];
        }
    //if on bottom row
    } else if (c.y == m.numrows() - 1) {
        //options
        int differences[2];
        differences[0] = abs(m[c.y][c.x + 1] - m[c.y][c.x]);
        differences[1] = abs(m[c.y - 1][c.x + 1] - m[c.y][c.x]);

        //logic
        if (differences[0] > differences[1]) {
            c.y--;
            p.directions.push_back(-1);
            p.change += differences[1];
        } else {
            p.directions.push_back(0);
            p.change += differences[0];
        }
    //if in middle rows
    } else {
        //options
        int differences[3];
        differences[0] = abs(m[c.y - 1][c.x + 1] - m[c.y][c.x]);
        differences[1] = abs(m[c.y][c.x + 1] - m[c.y][c.x]);
        differences[2] = abs(m[c.y + 1][c.x + 1] - m[c.y][c.x]);

        //logic
        if (differences[0] == differences[2] && differences[1] > differences[0]) {
            if (headFlip()) {
                c.y--;
                p.directions.push_back(-1);
                p.change += differences[0];
            } else {
                c.y++;
                p.directions.push_back(1);
                p.change += differences[2];
            }
        } else if (differences[0] < abs(differences[1]) && differences[0] < differences[2]) {
            c.y--;
            p.directions.push_back(-1);
            p.change += differences[0];
        } else if (differences[2] < differences[1] && differences[2] < differences[0]) {
            c.y++;
            p.directions.push_back(1);
            p.change += differences[2];
        } else if (differences[1] < differences[0] && differences[1] < differences[2]) {
            p.directions.push_back(0);
            p.change += differences[1];
        } else if (differences[1] == differences[0] || differences[1] == differences[2]) {
            p.directions.push_back(0);
            p.change += differences[1];
        }
    }

    //move over one
    c.x++;
}

void fivePointPath(apmatrix<short> &m, Coordinate &c, Path p[], ifstream &file) {
    for (int i = 0; i < m.numrows(); i++) {
        c.x = 0;
        c.y = i;

        //move
        while (c.x < m.numcols() - 1) {
            moveFive(m, c, p[i]);
        }

        //reset matrix
        file.open("colorado.dat");
        readIn(file, m);
        file.close();
    }
}

void moveFive(apmatrix<short> &m, Coordinate &c, Path &p) {
    //if on top row
    if (c.y == 0) {
        //options
        int differences[5]; //size 5 to make the numbers line up with the rest of the rows
        differences[2] = abs(m[c.y][c.x + 1] - m[c.y][c.x]);
        differences[3] = abs(m[c.y + 1][c.x + 1] - m[c.y][c.x]);
        differences[4] = abs(m[c.y + 1][c.x] - m[c.y][c.x]);

        //logic
        if (differences[4] < differences[2] && differences[4] < differences[3] && p.lastmove != 0) {
            p.xdirections.push_back(0);
            p.directions.push_back(1);
            m[c.y][c.x] = SHRT_MAX;
            c.y++;
            p.change += differences[4];
            p.lastmove = 4;
        } else if ((differences[3] < differences[2] && differences[3] < differences[4]) || (differences[3] == differences[4] && differences[3] < differences[2])) {
            p.xdirections.push_back(1);
            p.directions.push_back(1);
            m[c.y][c.x] = SHRT_MAX;
            c.y++;
            c.x++;
            p.change += differences[3];
            p.lastmove = 3;
        } else if ((differences[2] < differences[3] && differences[2] < differences[4]) || (differences[2] == differences[3] || differences[2] == differences[4])) {
            p.xdirections.push_back(1);
            p.directions.push_back(0);
            m[c.y][c.x] = SHRT_MAX;
            c.x++;
            p.change += differences[2];
            p.lastmove = 2;
        } else {
            p.xdirections.push_back(1);
            p.directions.push_back(0);
            m[c.y][c.x] = SHRT_MAX;
            c.x++;
            p.change += differences[2];
            p.lastmove = 2;
        }
    //if on bottom row
    } else if (c.y == m.numrows() - 1) {
        //options
        int differences[3];
        differences[0] = abs(m[c.y - 1][c.x] - m[c.y][c.x]);
        differences[1] = abs(m[c.y - 1][c.x + 1] - m[c.y][c.x]);
        differences[2] = abs(m[c.y][c.x + 1] - m[c.y][c.x]);

        //logic
        if (differences[0] < differences[2] && differences[0] < differences[1] && p.lastmove != 4) {
            p.xdirections.push_back(0);
            p.directions.push_back(-1);
            m[c.y][c.x] = SHRT_MAX;
            c.y--;
            p.change += differences[0];
            p.lastmove = 0;
        } else if ((differences[1] < differences[0] && differences[1] < differences[2]) || (differences[1] == differences[0] && differences[1] < differences[2])) {
            p.xdirections.push_back(1);
            p.directions.push_back(-1);
            m[c.y][c.x] = SHRT_MAX;
            c.y--;
            c.x++;
            p.change += differences[1];
            p.lastmove = 1;
        } else if ((differences[2] < differences[1] && differences[2] < differences[0]) || (differences[2] == differences[1] || differences[2] == differences[0])) {
            p.xdirections.push_back(1);
            p.directions.push_back(0);
            m[c.y][c.x] = SHRT_MAX;
            c.x++;
            p.change += differences[2];
            p.lastmove = 2;
        } else {
            p.xdirections.push_back(1);
            p.directions.push_back(0);
            m[c.y][c.x] = SHRT_MAX;
            c.x++;
            p.change += differences[2];
            p.lastmove = 2;
        }
    //if in middle rows
    } else {
        //options
        int differences[5];
        differences[0] = abs(m[c.y - 1][c.x] - m[c.y][c.x]);
        differences[1] = abs(m[c.y - 1][c.x + 1] - m[c.y][c.x]);
        differences[2] = abs(m[c.y][c.x + 1] - m[c.y][c.x]);
        differences[3] = abs(m[c.y + 1][c.x + 1] - m[c.y][c.x]);
        differences[4] = abs(m[c.y + 1][c.x] - m[c.y][c.x]);

        //logic
        if (differences[0] < differences[1] && differences[0] < differences[2] && differences[0] < differences[3] && differences[0] < differences[4] && p.lastmove != 4) {
            p.xdirections.push_back(0);
            p.directions.push_back(-1);
            m[c.y][c.x] = SHRT_MAX;
            c.y--;
            p.change += differences[0];
            p.lastmove = 0;
        } else if (differences[1] < differences[0] && differences[1] < differences[2] && differences[1] < differences[3] && differences[1] < differences[4]) {
            p.xdirections.push_back(1);
            p.directions.push_back(-1);
            m[c.y][c.x] = SHRT_MAX;
            c.y--;
            c.x++;
            p.change += differences[1];
            p.lastmove = 1;
        } else if (differences[2] < differences[1] && differences[2] < differences[0] && differences[2] < differences[3] && differences[2] < differences[4]) {
            p.xdirections.push_back(1);
            p.directions.push_back(0);
            m[c.y][c.x] = SHRT_MAX;
            c.x++;
            p.change += differences[2];
            p.lastmove = 2;
        } else if (differences[3] < differences[1] && differences[3] < differences[2] && differences[3] < differences[0] && differences[3] < differences[4]) {
            p.xdirections.push_back(1);
            p.directions.push_back(1);
            m[c.y][c.x] = SHRT_MAX;
            c.y++;
            c.x++;
            p.change += differences[3];
            p.lastmove = 3;
        } else if (differences[4] < differences[1] && differences[4] < differences[2] && differences[4] < differences[3] && differences[4] < differences[0] && p.lastmove != 0) {
            p.xdirections.push_back(0);
            p.directions.push_back(1);
            m[c.y][c.x] = SHRT_MAX;
            c.y++;
            p.change += differences[4];
            p.lastmove = 4;
        } else if (differences[0] == differences[4] && differences[0] < differences[1] && differences[0] < differences[2] && differences[0] < differences[3]) {
            if (headFlip() && p.lastmove != 4) {
                //up
                p.xdirections.push_back(0);
                p.directions.push_back(-1);
                m[c.y][c.x] = SHRT_MAX;
                c.y--;
                p.change += differences[0];
                p.lastmove = 0;
            } else {
                //down
                p.xdirections.push_back(0);
                p.directions.push_back(1);
                m[c.y][c.x] = SHRT_MAX;
                c.y++;
                p.change += differences[4];
                p.lastmove = 4;
            }
        } else if ((differences[1] == differences[3] && differences[1] < differences[0] && differences[1] < differences[2] && differences[1] < differences[4])) {
            if (headFlip()) {
                //up
                p.xdirections.push_back(1);
                p.directions.push_back(-1);
                m[c.y][c.x] = SHRT_MAX;
                c.y--;
                c.x++;
                p.change += differences[1];
                p.lastmove = 1;
            } else {
                //down
                p.xdirections.push_back(1);
                p.directions.push_back(1);
                m[c.y][c.x] = SHRT_MAX;
                c.y++;
                c.x++;
                p.change += differences[3];
                p.lastmove = 3;
            }
        } else if (differences[0] == differences[1] && differences[0] < differences[2] && differences[0] < differences[3] && differences[0] <= differences[4]) {
            p.xdirections.push_back(1);
            p.directions.push_back(-1);
            m[c.y][c.x] = SHRT_MAX;
            c.y--;
            c.x++;
            p.change += differences[1];
            p.lastmove = 1;
        } else if (differences[3] == differences[4] && differences[3] < differences[2] && differences[3] < differences[0] && differences[3] <= differences[1]) {
            p.xdirections.push_back(1);
            p.directions.push_back(1);
            m[c.y][c.x] = SHRT_MAX;
            c.y++;
            c.x++;
            p.change += differences[3];
            p.lastmove = 3;
        } else if (differences[0] == differences[3] && differences[0] < differences[2] && differences[0] <= differences[1] && differences[0] < differences[4]) {
            p.xdirections.push_back(1);
            p.directions.push_back(1);
            m[c.y][c.x] = SHRT_MAX;
            c.y++;
            c.x++;
            p.change += differences[3];
            p.lastmove = 3;
        } else if (differences[1] == differences[4] && differences[1] < differences[2] && differences[1] < differences[0] && differences[1] <= differences[3]) {
            p.xdirections.push_back(1);
            p.directions.push_back(-1);
            m[c.y][c.x] = SHRT_MAX;
            c.y--;
            c.x++;
            p.change += differences[1];
            p.lastmove = 1;
        } else if (differences[2] <= differences[0] && differences[2] <= differences[1] && differences[2] <= differences[3] && differences[2] <= differences[4]) {
            p.xdirections.push_back(1);
            p.directions.push_back(0);
            m[c.y][c.x] = SHRT_MAX;
            c.x++;
            p.change += differences[2];
            p.lastmove = 2;
        } else {
            p.xdirections.push_back(1);
            p.directions.push_back(0);
            m[c.y][c.x] = SHRT_MAX;
            c.x++;
            p.change += differences[2];
            p.lastmove = 2;
        }
    }
}
