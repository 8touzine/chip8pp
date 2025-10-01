#pragma once

#include <SDL.h>
#include "../Display/DisplayBridge.h"
#include "../Memory/Memory.h"
#include "../Core/OpcodeProcessor.h"
#include <stdio.h>

class Core {
private:
	DisplayBridge* display = nullptr;
	Memory* memory = nullptr;
	OpcodeProcessor* opcodeprocessor = nullptr;
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

	void mainLoop();	
	int fetchOpcode();
	void decode(int opcode);
	void loadMemory();

};