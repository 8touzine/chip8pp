#pragma once

#include <string>
#include <SDL.h>
#include <fstream>
#include <vector>
#include "Fontset.h"

class Memory {
private:
	uint8_t memory[4096] = { 0 };
	uint16_t stack[16] = { 0 };
	unsigned int sp = 0; //rsp;
	//uint8_t fontSet[80];
	const size_t MEMORY_SIZE = 4096;
public:	
	void loadToMemory(std::vector<uint8_t>, size_t offset);//fstream
	void loadFontset();
	void loadRom(std::string path);
	uint8_t* getMemory();
	uint16_t* getStack();
	unsigned int* getSp();
};