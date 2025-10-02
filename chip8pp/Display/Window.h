#pragma once
#include "IDisplayBridge.h"

class Window : public IDisplayBridge 
{
private:
	int static const WINDOWW = 840;
	int static const WINDOWH = 680;
	int screenW = 64;
	int screenH = 32;
	int pixelSizeX;
	int pixelSizeY;
	int frameBuffersize = 64 * 32;
	SDL_Renderer* canvas;
public:

	Window(SDL_Renderer* canv){};
	virtual void init();

	virtual void draw(unsigned char* framebuffer);


};