#pragma once
#include <SDL.h>
#include <SDL_image.h>

class IDisplayBridge {

public:
	int static const WINDOWW = 840;
	int static const WINDOWH = 680;
	~IDisplayBridge() {};
	virtual void init() = 0;
	virtual void draw(unsigned char* framebuffer) = 0;
};