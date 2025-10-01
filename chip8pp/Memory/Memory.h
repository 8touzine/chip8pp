#pragma once

#include <string>

class Memory {
private:
	unsigned char memory[4096];
	unsigned short stack[16];
	unsigned short sp; //rsp;
	unsigned char fontSet[80];
	unsigned char key[16];

public:	
	void loadToMemory();//fstream
	void loadFontset();
	void loadRom(std::string path);
	unsigned char* getMemory();
	unsigned short* getStack();
	unsigned short* getSp();
};