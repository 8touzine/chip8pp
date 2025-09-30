#pragma once

#include <string>

class Memory {
private:
	unsigned short stack[16];
	unsigned short sp; //rsp;
	unsigned char fontSet[80];
	unsigned char key[16];

public:
	unsigned char memory[4096];
	void loadToMemory();//fstream
	void loadFontset();
	void loadRom(std::string path);
};