#pragma once
void slider(int x,int y,SDL_Renderer* renderer,int s_w){
	SDL_FRect rect1 = { x, y, 1*s_w,5};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer,&rect1);
}