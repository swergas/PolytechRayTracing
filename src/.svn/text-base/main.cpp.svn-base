#include <iostream>
#include <fstream> // ofstream
#include <cstdio> // sprintf

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "RayTracer.h"
#include "SceneParser.h"
#include "Timer.h"

//Screen attributes
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int OVERSAMPLING;
const int SCREEN_BPP = 32;

nsUtil::Timer timer = nsUtil::Timer();
SceneParser *parser = NULL;
bool quit = false;
int mouse_clicked_x;
int mouse_clicked_y;
int mouse_pos_x;
int mouse_pos_y;
bool mouse_down = false;
RayTracer *rt = NULL;
Image *img = NULL;
SDL_Surface* screen = NULL;
double camera_t = 0.0;

Vector3 posSphere;
Set<Shape*> shapes = Set<Shape*>();
Set<LightSource*> lights = Set<LightSource*>();
double rayonCamera = 1.0;
bool recordvideo = false;
int videoimages = 0;


SDL_Surface *load_image(std::string filename) {
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image using SDL_image
	loadedImage = IMG_Load(filename.c_str());

	//If the image loaded
	if(loadedImage != NULL) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}

	//Return the optimized image
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
	//Rectangle to hold the offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void fillSurfaceFromFile(SDL_Surface *surface, Image* img, const char* f) {
	SDL_Surface *img_sdl = load_image(f);
	apply_surface(0, 0, img_sdl, screen);
	SDL_FreeSurface(img_sdl);
}

void refreshDisplay() {
	char f[100] = "img.ppm";
	if(recordvideo) {
		sprintf(f, "img%05d.ppm", ++videoimages);
	}
	img->printImage(f);
	fillSurfaceFromFile(screen, img, f);
	SDL_Flip(screen);
}

void handle_events(SDL_Event& event) {
	bool refresh = false;
	bool changeCamera = false;

	if(event.type == SDL_MOUSEMOTION) {
		if(mouse_down) {
			mouse_pos_x = event.button.x;
			mouse_pos_y = event.button.y;
		}
	} else if(event.type == SDL_MOUSEBUTTONDOWN) {
		//If the left mouse button was pressed
		if(event.button.button == SDL_BUTTON_LEFT) {
			mouse_down = true;
			//Get the mouse offsets
			mouse_clicked_x = event.button.x;
			mouse_clicked_y = event.button.y;
		}
	} else if(event.type == SDL_MOUSEBUTTONUP) {
		if(event.button.button == SDL_BUTTON_LEFT) {
			mouse_down = false;
		}
	} else if(event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym) {
		case SDLK_ESCAPE:
			quit = true;
			break;

		case SDLK_LEFT:
			rt->_camera._observer[0] -= 10.0;
			cerr << rt->_camera._observer[0] << endl;
			refresh = changeCamera = true;
			break;

		case SDLK_RIGHT:
			rt->_camera._observer[0] += 10.0;
			refresh = changeCamera = true;
			break;

		case SDLK_UP:
			rt->_camera._observer[2] += 10.0;
			refresh = changeCamera = true;
			break;

		case SDLK_DOWN:
			rt->_camera._observer[2] -= 10.0;
			refresh = changeCamera = true;
			break;

		case SDLK_d:
			camera_t -= .1;
			cerr << "camera_t: " << camera_t << endl;
			rt->_camera._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->_camera._observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
			refresh = changeCamera = true;
			break;

		case SDLK_f: {
			int n = 63;
			recordvideo = true;
			for(int i = 0; i < n; ++i){
				cerr << "iteration " << i << " sur " << n << endl;
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->_camera._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->_camera._observer[1] = posSphere[1] + sin(camera_t)*rayonCamera;
				rt->_camera.initFromDistScreen(rt->_camera._distScreen);
				rt->raytrace(img, OVERSAMPLING);
				refreshDisplay();
			}
		}
			break;

		case SDLK_t: {
			int n = 63;
			recordvideo = true;
			for(int i = 0; i < n; ++i){
				cerr << "iteration " << i << " sur " << n << endl;
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->_camera._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->_camera._observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				rt->_camera.initFromDistScreen(rt->_camera._distScreen);
				rt->raytrace(img, OVERSAMPLING);
				refreshDisplay();
			}
		}
			break;

		case SDLK_l: {
			int n = 63;
			recordvideo = true;
			rt->_scene._lightSources->get(0)->_position[1] = 20;
			for(int i = 0; i < n; ++i){
				cerr << "iteration " << i << " sur " << n << endl;
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->_scene._lightSources->get(0)->_position[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->_scene._lightSources->get(0)->_position[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				rt->raytrace(img, OVERSAMPLING);
				refreshDisplay();
			}
		}
			break;

		case SDLK_q:
			camera_t += .1;
			cerr << "camera_t: " << camera_t << endl;
			rt->_camera._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->_camera._observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
			refresh = changeCamera = true;
			break;

		case SDLK_w:
			camera_t -= 0.50;
			cerr << "camera_t: " << camera_t << endl;
			rt->_camera._aimedPoint[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->_camera._aimedPoint[2] = posSphere[2] + sin(camera_t)*rayonCamera;
			refresh = changeCamera = true;
			break;

		case SDLK_x:
			camera_t += 0.50;
			cerr << "camera_t: " << camera_t << endl;
			rt->_camera._aimedPoint[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->_camera._aimedPoint[2] = posSphere[2] + sin(camera_t)*rayonCamera;
			refresh = changeCamera = true;
			break;

		case SDLK_v:
			recordvideo = !recordvideo;
			cerr << "recordvideo: " << recordvideo << endl;
			break;

		default:
			break;
		}
	}

	if (changeCamera == true) {
		rt->_camera.initFromDistScreen(parser->_camera._distScreen);
	}

	if (refresh == true) {
		rt->raytrace(img, OVERSAMPLING);
		refreshDisplay();
	}
}

int main(int argv, char** argc) {

	if (argv > 2) {
		std::cerr << "Please, enter a file name in argument or nothing to load the default scene." << std::endl;
		return -1;
	} else {
		//Scene Setups
		//If a file has been specified, we load it, otherwise, we load the default file defaultScene.xml

		cout << "\n## XML Parsing:\n" << endl;
		if (argv == 2) {
			parser = new SceneParser(argc[1]);
		} else {
			parser = new SceneParser();
		}

		cout << "\nInitialization..." << endl;
		timer.start();
		shapes = parser->_shapes;
		lights = parser->_lightSources;
		SCREEN_HEIGHT = parser->_screenHeight;
		SCREEN_WIDTH = parser->_screenWidth;
		OVERSAMPLING = parser->_oversampling;
		ScreenV2 camera = parser->_camera;
		Scene s = Scene(&shapes, &lights);
		PhongModel lm = PhongModel();
		rt = new RayTracer(s, lm, camera);
		img = new Image(SCREEN_WIDTH, SCREEN_HEIGHT, Color(0.0, 0.0, 0.0));
		int timeInitialize = timer.getTicks();
		rayonCamera = (camera._observer - camera._aimedPoint).norm();
		cout << "Initialization time: " << timeInitialize/1000.0 << "s\n" << endl;



		//SDL Setups
		SDL_Event event;
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
			exit(1);
		}
		atexit(SDL_Quit);

		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE); // w, h
		if(screen == NULL) {
			fprintf(stderr, "Unable to set video mode.");
			cerr << SDL_GetError() << endl;
			exit(1);
		}
		SDL_WM_SetCaption("Polytech Ray Tracing", NULL);



		//Picture creation
		timer.start();
		rt->raytrace(img, OVERSAMPLING);
		int timeElapsed = timer.getTicks();
		cout << "Creating picture time: " << timeElapsed/1000.0 << "s" << endl;
		timer.stop();

		refreshDisplay();

		int fps = 35;



		// main loop
		//While the user hasn't quit
		while(quit == false) {
			//While there's an event to handle
			while(SDL_PollEvent(&event)) {
				handle_events(event);
				if(event.type == SDL_QUIT) {
					//Quit the program
					quit = true;
				}
			}

			if(timer.getTicks() < 1000 / fps) {
				SDL_Delay((1000 / fps) - timer.getTicks());
			}
		}
		SDL_FreeSurface(screen);
		SDL_Quit();

		return 0;
	}
} // main()
