#include "nifty.h"

//Initialize allegro functions
void initializeAllegro() {

    //Initialize Allegro
	al_init();

	//initialize addons
    al_init_image_addon();
    al_init_primitives_addon();
}

//checks to make sure all the allegro addons are properly installed
int checkSetup(ALLEGRO_DISPLAY *display) {

    //Check display
	if (!display) {
    	cout << "allegro display error";
       	return -1;
	}

   //Check image addon
   if (!al_init_image_addon()) {
    	cout << "Image addon error";
    	return -1;
	}

   	//Primitives addon
   	if (!al_init_primitives_addon()) {
    	cout << "primatives addon error";
    	return -1;
	}

   return 0;
}

