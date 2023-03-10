#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <time.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

//const
const int mapRows = 480;
const int mapCols = 844;

//Structs
struct Coordinate {
    int x, y;
};

struct Path {
    vector<short> directions;
    long change = 0;
    bool best = false;

    //for looking at five points
    vector<short> xdirections;
    short lastmove = -1;
};

//define colors
#define LUSH     al_map_rgb(5, 77, 21)
#define ROCK     al_map_rgb(255, 250, 245)
#define LOWPLATEAU   al_map_rgb(91, 94, 92)
#define HIGHPLATEAU  al_map_rgb(210, 190, 200)

#define WHITE    al_map_rgb(255, 255, 255)
#define RED		 al_map_rgb(230, 25, 75)
#define GREEN	 al_map_rgb(60, 180, 75)
#define YELLOW	 al_map_rgb(255, 225, 25)
#define BLUE	 al_map_rgb(0, 130, 200)
#define ORANGE   al_map_rgb(245, 130, 48)
#define PURPLE	 al_map_rgb(145, 30, 180)
#define CYAN	 al_map_rgb(70, 240, 240)
#define MAGENTA	 al_map_rgb(240, 50, 230)
#define LIME	 al_map_rgb(210, 245, 60)
#define PINK	 al_map_rgb(250, 190, 190)
#define TEAL	 al_map_rgb(0, 128, 128)
#define BROWN	 al_map_rgb(170, 110, 40)
#define NAVY	 al_map_rgb(0, 0, 128)
#define GREY	 al_map_rgb(128, 128, 128)
#define BLACK    al_map_rgb(0, 0, 0)
#define DARKGREY al_map_rgb(27, 27, 27)
#define LIGHTBLUE al_map_rgb(0, 255, 255)

//prototypes
void readIn(ifstream &file, short m[mapRows][mapCols]);
void findMax(short &maximum, const short m[mapRows][mapCols]);
void findMin(short &minimum, const short m[mapRows][mapCols]);
int checkSetup(ALLEGRO_DISPLAY *display);
void initializeAllegro();
void drawMap(const short m[mapRows][mapCols], int maximum, int minimum, ALLEGRO_DISPLAY *display);
bool headFlip();
void calcLowestElevPaths(const short m[mapRows][mapCols], Coordinate &c, Path p[]);
void moveOne(const short m[mapRows][mapCols], Coordinate &c, Path &p);
bool headFlip();
void findBestPath(Path p[], int &best);
void drawPaths(Path p[], ALLEGRO_DISPLAY *display, ALLEGRO_COLOR normal, ALLEGRO_COLOR ideal, int best);
void calcStayLowPaths(const short m[mapRows][mapCols], Coordinate &c, Path p[]);
void moveLow(const short m[mapRows][mapCols], Coordinate &c, Path &p);
void fivePointPath(short m[mapRows][mapCols], Coordinate &c, Path p[], ifstream &file);
void moveFive(short m[mapRows][mapCols], Coordinate &c, Path &p);
void drawFivePaths(Path p[], ALLEGRO_DISPLAY *display, ALLEGRO_COLOR normal, ALLEGRO_COLOR ideal, int best);
