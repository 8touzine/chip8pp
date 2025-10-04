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
	uint16_t opcode;
	uint8_t V[16] = { 0 }; //general purpose registers
	unsigned short I;	
	uint16_t PC;//rip
	uint8_t framebuffer[64 * 32] = { 0 };
	uint8_t delay_timer;
	uint8_t sound_timer;	
	uint8_t key[16] = { 0 };
	bool drawFlag = true;
	bool awaitingKey = false;
	uint8_t awaitingRegister; 	
	const int FRAME_DELAY = 1000 / 120; // 60Hz
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