#include "nifty.h"

//Draws the elevation map on the screen
void drawMap(const apmatrix<short> &m, int maximum, int minimum, ALLEGRO_DISPLAY *display) {
    //variables
    ALLEGRO_COLOR shade;
    float scaleShade[3];
    int scaleDifference = maximum - minimum;
    float LPdiff[3] = {LOWPLATEAU.r - LUSH.r, LOWPLATEAU.g - LUSH.g, LOWPLATEAU.b - LUSH.b};
    float mountaindiff[3] = {HIGHPLATEAU.r - LOWPLATEAU.r, HIGHPLATEAU.g - LOWPLATEAU.g, HIGHPLATEAU.b - LOWPLATEAU.b};
    float PRdiff[3] = {ROCK.r - HIGHPLATEAU.r, ROCK.g - HIGHPLATEAU.g, ROCK.b - HIGHPLATEAU.b};

    //color the map
    for (int i = 0; i < m.numrows(); i++) {
        for (int j = 0; j < m.numcols(); j++) {
            float intensity = (m[i][j] - minimum) / float (scaleDifference);
            if (intensity >= 0.82) {
                intensity = (intensity - 0.82) / 0.18;
                for (int k = 0; k < 3; k++) {
                    scaleShade[k] = intensity * PRdiff[k];
                }
                scaleShade[0] += HIGHPLATEAU.r;
                scaleShade[1] += HIGHPLATEAU.g;
                scaleShade[2] += HIGHPLATEAU.b;
            } else if (intensity >= 0.3) {
                intensity = (intensity - 0.3) / 0.52;
                for (int k = 0; k < 3; k++) {
                    scaleShade[k] = intensity * mountaindiff[k];
                }
                scaleShade[0] += LOWPLATEAU.r;
                scaleShade[1] += LOWPLATEAU.g;
                scaleShade[2] += LOWPLATEAU.b;
            } else {
                intensity = (intensity) / 0.3;
                for (int k = 0; k < 3; k++) {
                    scaleShade[k] = intensity * LPdiff[k];
                }
                scaleShade[0] += LUSH.r;
                scaleShade[1] += LUSH.g;
                scaleShade[2] += LUSH.b;
            }
            shade = al_map_rgb_f(scaleShade[0], scaleShade[1], scaleShade[2]);
            al_draw_pixel(j, i, shade);
        }
    }
    al_flip_display();
}

//flips a virtual coin and return true if "heads"
bool headFlip() {
    int coin = rand() % 2;
    if (coin == 1) {
        return true;
    } else {
        return false;
    }
}

//draws all basic paths
void drawPaths(Path p[], ALLEGRO_DISPLAY *display, ALLEGRO_COLOR normal, ALLEGRO_COLOR ideal, int best) {
    Coordinate c;

    //draw all non-best paths
    for (int i = 0; i < mapRows; i++) {
        if (p[i].best == true) {
            continue;
        }
        c.x = 0;
        c.y = i;
        al_draw_pixel(0, i, normal);
        for (int j = 0; j < mapCols - 1; j++) {
            c.x++;
            c.y += p[i].directions[j];
            al_draw_pixel(c.x, c.y, normal);
        }
        al_flip_display();
    }
    al_rest(0.5);

    //draw the best path over top and animate it
    c.x = 0;
    c.y = best;
    al_draw_pixel(c.x, c.y, ideal);
    for (int i = 0; i < mapCols - 1; i++) {
        c.x++;
        c.y += p[best].directions[i];
        al_draw_pixel(c.x, c.y, ideal);
        al_flip_display();
        al_rest(0.001);
    }

    al_flip_display();
    al_rest(1);
}

//draws the paths for the look at five walk
void drawFivePaths(Path p[], ALLEGRO_DISPLAY *display, ALLEGRO_COLOR normal, ALLEGRO_COLOR ideal, int best) {
    Coordinate c;

    //draw all non-best paths
    for (int i = 0; i < mapRows; i++) {
        if (p[i].best == true) {
            continue;
        }
        c.x = 0;
        c.y = i;
        al_draw_pixel(0, i, normal);
        for (int j = 0; j < p[i].directions.size() - 1; j++) {
            c.x += p[i].xdirections[j];
            c.y += p[i].directions[j];
            al_draw_pixel(c.x, c.y, normal);
        }
        al_flip_display();
    }
    al_rest(0.5);

    //draw the best path over top and animate it
    c.x = 0;
    c.y = best;
    al_draw_pixel(c.x, c.y, ideal);
    for (int i = 0; i < p[best].directions.size() - 1; i++) {
        c.x += p[best].xdirections[i];
        c.y += p[best].directions[i];
        al_draw_pixel(c.x, c.y, ideal);
        al_flip_display();
        al_rest(0.001);
    }

    al_flip_display();
    al_rest(1);
}

