#pragma once

#include <SDL.h>
#include "../Display/IDisplayBridge.h"
#include "../Display/Window.h"
#include "../Memory/Memory.h"
#include "../Core/OpcodeProcessor.h"
#include "../Controls/Keyboard.h"

#include <stdio.h>
#include <iostream>
#include <iomanip>

class Core {
private:
	IDisplayBridge* display = nullptr;
	Memory* memory = nullptr;
	OpcodeProcessor* opcodeprocessor = nullptr;
	SDL_Window* win = NULL;
	SDL_Renderer* rendZER = NULL;
	unsigned char V[16]; //general purpose registers
	uint16_t opcode;
	unsigned short I;
	uint16_t PC;//rip
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned char framebuffer[64 * 32];
	unsigned char key[16];
	bool drawFlag;
	bool awaitingKey;
	unsigned char awaitingRegister; 	
	const int FRAME_DELAY = 1000 / 60; // 60Hz
public:
	Core();
	bool init();
	void close();
	void mainLoop();
	void handleInput(SDL_Event& e, bool& quit);

	uint16_t fetchOpcode();
	void decode(uint16_t opcode);
	//void loadMemory();

};