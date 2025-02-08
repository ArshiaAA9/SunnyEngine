#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "headers/physics.h"


bool init();
void kill();
bool loop(Object& obj);


// Pointers to our window and renderer
SDL_Window* window;
SDL_Renderer* renderer;


int main(int argc, char** args){
//object creation 
Object obj(0, 0, 1);
// applyGravity(obj);


//----------SDL SETUP ------------

    //initialisation 
	if ( !init() ) return 1;


	while ( loop(obj) ) {
		// time before next frame 16 for 60fps
		SDL_Delay(1000); 
	}

	kill();

    return 0;
}


bool loop(Object& obj ) {

	//declarations
	static int mouseXPos, mouseYPos; //mouse x and y position
	static const unsigned char* keys = SDL_GetKeyboardState( NULL ); //keyboard

	SDL_Event event; 
	SDL_Rect objRect;



	//calculation for delta time
	static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert ms to seconds
    lastTime = currentTime;


	//updating object and printing its value
    updateObject(obj, deltaTime);
	obj.printProperties();
	std::cout << "time: " << currentTime/1000.0f << " ";

	//clearing renderer after each frame so it doesn't ghost frames
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);



	objRect.h = 10;
	objRect.w = 10;

	// we substract w and h divided by 2 to get the top left corner of the obj because thats how sdl2 renters the position
	objRect.x = obj.position.x - objRect.w/2; 
	objRect.y = -obj.position.y - objRect.h/2; // we take -y cause else object would go upward when the value decreases


	//drawing a the object rect
	SDL_SetRenderDrawColor(renderer, 18, 88, 94, 255);
	SDL_RenderFillRect(renderer, &objRect);


	// Event loop
	while ( SDL_PollEvent( &event ) != 0 ) {
		switch ( event.type ) {
			case SDL_QUIT:
				return false;

			//case for printing the mouse x and y position
			case SDL_MOUSEBUTTONDOWN:
				mouseXPos = event.button.x;
				mouseYPos = event.button.y;
				std::cout << "Mouse position (" << mouseXPos << "," << mouseYPos << ")" << std::endl;
		}
	}

	// Update window
	SDL_RenderPresent( renderer );
    

	return true;
}


bool init() {
	// See last example for comments
	SDL_Init(SDL_INIT_EVERYTHING);


    //window and renderer creation
	SDL_CreateWindowAndRenderer(1300, 860, 0, &window, &renderer);



	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	
	return true;
}


void kill() {
	// Quit
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}