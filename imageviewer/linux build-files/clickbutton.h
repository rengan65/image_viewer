#pragma once
void DrawButton(float x,float y,float w,float h,SDL_Renderer* renderer,bool &b_s,int mousex,int mousey){
	SDL_FRect rect = {x ,y ,w ,h};
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	SDL_RenderFillRect(renderer,&rect);
	if(mousex > x&& mousex < x + w && mousey > y && mousey < h+x){
		b_s = true;
	}
	else{
		b_s = false;
	}
}