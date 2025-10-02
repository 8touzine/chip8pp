#pragma once

#include <SDL.h>
#include "../Display/IDisplayBridge.h"
#include "../Display/Window.h"
#include "../Memory/Memory.h"
#include "../Core/OpcodeProcessor.h"
#include <stdio.h>


class Core {
private:
	IDisplayBridge* display = nullptr;
	Memory* memory = nullptr;
	OpcodeProcessor* opcodeprocessor = nullptr;
	SDL_Window* win = NULL;
	SDL_Renderer* rendZER = NULL;
	unsigned char V[16]; //general purpose registers
	unsigned short opcode;
	unsigned short I;
	unsigned short PC;//rip
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned char framebuffer[64 * 32];
	bool drawFlag;
	bool awaitingKey;
	unsigned char awaitingRegister; 	
public:
	Core() {};
	bool init();
	void close();
	void mainLoop();	
	int fetchOpcode();
	void decode(int opcode);
	void loadMemory();

};