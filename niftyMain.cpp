/** Logan White - ICS4U - Nifty Mountains - Feb 24, 2020

    This program will draw out an elevation map of the
    mountains in Colorado and will the find paths with the
    lowest elevation change using a greedy walk, the path
    that stays low to the ground with the lowest elevation
    and the best greedy walk path when looking at 5 points**/

#include "nifty.h"

int main() {
    //seed random
    srand(time(0));

    //set up file for reading in
    ifstream file("colorado.dat");
    if (!file.is_open()) {
        cout << "Colorado.dat not found";
        return 404;
    }

    //variables
    //apmatrix<short> mapData(mapRows, mapCols);
    short mapData[mapRows][mapCols];

    short maxElev, minElev;
    Coordinate coor;
    char input;
    bool validInput = false;
    bool greedy = false;
    bool lowest = false;
    bool five = false;

    //map functions (read, find max & min)
    readIn(file, mapData);
    findMax(maxElev, mapData);
    findMin(minElev, mapData);

    file.close();

    //get the user's first input before starting allegro
    while (!validInput) {
        cout << "Pick a path:" << endl
             << "[g] Greedy Walk" << endl
             << "[l] Stay Low Walk" << endl
             << "[f] Look Around Five Greedy" << endl
             << "[e] Run everything" << endl
             << "[q] Quit" << endl
             << "Enter your selection: ";
        cin >> input;

        switch (input) {
            case 'g':   greedy = true;
                        validInput = true;
                        break;
            case 'l':   lowest = true;
                        validInput = true;
                        break;
            case 'f':   five = true;
                        validInput = true;
                        break;
            case 'e':   greedy = true;
                        lowest = true;
                        five = true;
                        validInput = true;
                        break;
            case 'q':   return 0;
            default:    cout << "invalid input" << endl << endl;
        }
    }

    //initialize allegro
    initializeAllegro();

    //Initialize allegro display
    ALLEGRO_DISPLAY *display = al_create_display(mapCols, mapRows);

    checkSetup(display);

    //main loop
    while (true) {
        //set variables for each run through
        Path allPaths[mapRows];
        Path lowPaths[mapRows];
        Path fivePaths[mapRows];
        int bestPathNum;
        validInput = false;

        //redraw map
        drawMap(mapData, maxElev, minElev, display);

        //do greedy walk
        if (greedy) {
            calcLowestElevPaths(mapData, coor, allPaths);
            findBestPath(allPaths, bestPathNum);
            drawPaths(allPaths, display, RED, YELLOW, bestPathNum);
            cout << endl << "Std::Greedy Walk: Red paths, Yellow best" << endl
                 << "The path with the lowest elevation change starts on row " << bestPathNum << endl
                 << "It has a total elevation change of " << allPaths[bestPathNum].change << endl;
        }

        //do stay low walk
        if (lowest) {
            calcStayLowPaths(mapData, coor, lowPaths);
            findBestPath(lowPaths, bestPathNum);
            drawPaths(lowPaths, display, PINK, ORANGE, bestPathNum);
            cout << endl << "Stay Low Walk: Pink paths, Orange best" << endl
                 << "The path that stays low with the lowest elevation change starts on row " << bestPathNum << endl
                 << "It has a total elevation change of " << lowPaths[bestPathNum].change << endl;
        }

        //do look at five walk
        if (five) {
            cout << endl << "****** ATTENTION! THIS REQUIRES A LOT MORE COMPARISONS AND TAKES LONGER TO RUN ******" << endl;
            fivePointPath(mapData, coor, fivePaths, file);
            findBestPath(fivePaths, bestPathNum);
            drawFivePaths(fivePaths, display, BLUE, LIGHTBLUE, bestPathNum);
            cout << endl << "Look at Five Walk: Blue Paths, Light Blue best" << endl
                 << "The path with the lowest elevation change while looking at five points starts on row " << bestPathNum << endl
                 << "It has a total elevation change of " << fivePaths[bestPathNum].change << endl;
        }

        //reset selection variables
        greedy = false;
        lowest = false;
        five = false;

        //get another input
        cout << endl;
        while (!validInput) {
            cout << "Pick a path:" << endl
                 << "[g] Greedy Walk" << endl
                 << "[l] Stay Low Walk" << endl
                 << "[f] Look Around Five Greedy" << endl
                 << "[e] Run. Everything." << endl
                 << "[q] Quit" << endl
                 << "Enter your selection: ";
            cin >> input;

            switch (input) {
                case 'g':   greedy = true;
                            validInput = true;
                            break;
                case 'l':   lowest = true;
                            validInput = true;
                            break;
                case 'f':   five = true;
                            validInput = true;
                            break;
                case 'e':   greedy = true;
                            lowest = true;
                            five = true;
                            validInput = true;
                            break;
                case 'q':   return 0;
                default:    cout << "invalid input" << endl << endl;
            }
        }
    }

    return 0;
}
