#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<iostream>
#include<SDL3_ttf/SDL_ttf.h>
#include"tinyfiledialogs.h"
#include"clickbutton.h"
#include"slider.h"
int main(){
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	const int screen_width = 800;
    const int screen_height = 600;
	SDL_Window* window = SDL_CreateWindow("main", screen_width, screen_height, SDL_WINDOW_RESIZABLE);
	if(window == NULL){
		std::cout << "unable to initialie window";
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window,NULL);
	if(renderer == NULL){
		std::cout << "unable to start renderer";
		SDL_DestroyWindow(window);
	}
	bool running = true;
	bool button_state = false;
	bool mouse_button_state = false;
	float mx,my;
	float imagesize = 0;
	SDL_Event event;
	int w = screen_width;
	int h = screen_height-50; //open the file explorer first
	const char* file = tinyfd_openFileDialog("choose a file", "", 0, NULL, NULL,0);
	SDL_Color color = {0,0,0,0};
	//font initialisation
	TTF_Font* font = TTF_OpenFont("myfont1.ttf",24);
	if(font == NULL){
		SDL_Quit();
	}
	SDL_Surface* textsurface = TTF_RenderText_Solid(font,file,strlen(file),color);
	SDL_Texture* texttexture = SDL_CreateTextureFromSurface(renderer,textsurface);
	//size of the font
	SDL_FRect textrec = {(float)0, (float)10, textsurface->w-10, textsurface->h-10};
	SDL_DestroySurface(textsurface);
	SDL_Surface* surface = IMG_Load(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
	while(running){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_EVENT_QUIT){
				running = false;
			}

			if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
				if(event.button.button == SDL_BUTTON_LEFT){
                       mouse_button_state = true;
				}
				else{
					mouse_button_state = false;
				}
			}
			if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
				if(event.button.button == SDL_BUTTON_LEFT){
					imagesize = 0;
				}
			}

			if(event.type == SDL_EVENT_MOUSE_WHEEL){
				if(event.wheel.y > 0){
					imagesize-=5;
				}
				if(event.wheel.y < 0){
                   imagesize+=5;			
				}
			}
		}
		SDL_GetMouseState(&mx,&my);
		if(mouse_button_state && button_state){
			file = tinyfd_openFileDialog("choose a file", "", 0, NULL, NULL,0);
            surface = IMG_Load(file);
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_DestroySurface(surface);
            mouse_button_state = false; button_state = false;
		}
		const bool* state = SDL_GetKeyboardState(NULL);
		SDL_GetWindowSize(window, &w, &h);
        SDL_FRect rect = {0 + imagesize, 50, w-2*imagesize, h-100-1.2*imagesize};
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		//IMAGE
		SDL_RenderTexture(renderer, texture, NULL, &rect);
		//TEXTURE
		SDL_RenderTexture(renderer,texttexture,NULL,&textrec);
		DrawButton(w-100,h-30,90,25,renderer,button_state,mx,my);
		slider(10,screen_height-10,renderer,imagesize);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_SetRenderScale(renderer, 1, 1);
		SDL_RenderDebugTextFormat(renderer,w-100 + 5 + 20,h-30 + 5,"open");
		SDL_RenderPresent(renderer);
		SDL_Delay(120);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_Quit();
}