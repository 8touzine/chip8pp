#pragma once

#include <string>
#include <SDL.h>
#include <fstream>
#include <vector>
#include "Fontset.h"

class Memory {
private:
	unsigned char memory[4096];
	unsigned short stack[16];
	unsigned int sp = 0; //rsp;
	//unsigned char fontSet[80];
	const size_t MEMORY_SIZE = 4096;
public:	
	void loadToMemory(std::vector<unsigned char>, size_t offset);//fstream
	void loadFontset();
	void loadRom(std::string path);
	unsigned char* getMemory();
	unsigned short* getStack();
	unsigned int* getSp();
};