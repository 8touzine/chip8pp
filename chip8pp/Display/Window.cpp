#include "Window.h"

Window::Window(SDL_Renderer* canv)
{
	canvas = canv;

	pixelSizeX = (int)(WINDOWW / screenW);
	pixelSizeY = (int)(WINDOWH / screenH);

	
}

void Window::init()
{
	SDL_SetRenderDrawColor(canvas, 0x00, 0x00, 0x1F, 0xFF);
	
}

void Window::draw(unsigned char* framebuffer)
{	
	SDL_RenderClear(canvas);
	int x = 0;
	int y = 0;
	for (int pix; pix < frameBuffersize; pix++)
	{
		x = (pix % screenW)* pixelSizeX;
		y = (pix / screenH) * pixelSizeY;
		/*if (pix >= 64)
		{
			y += pixelSizeY;
		}*/
		SDL_Rect pixel = { x, y, pixelSizeX, pixelSizeY };
		SDL_SetRenderDrawColor(canvas, 0x00, 0x00, 0x1F, 0xFF);

		if (framebuffer[pix] == 1)
		{
			SDL_SetRenderDrawColor(canvas, 0x00, 0x00, 0xF1, 0xFF);
		}
		
		SDL_RenderFillRect(canvas, &pixel);
	}

	
}
