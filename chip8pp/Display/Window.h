#pragma once
#include "IDisplayBridge.h"
#include <SDL.h>
#include <SDL_image.h>

class Window : public IDisplayBridge 
{
private:	
	int screenW = 64;
	int screenH = 32;
	int pixelSizeX;
	int pixelSizeY;
	int frameBuffersize = 64 * 32;
	SDL_Renderer* canvas;
public:	
	Window(SDL_Renderer* canv);
	virtual void init();
	virtual void draw(unsigned char* framebuffer);


};