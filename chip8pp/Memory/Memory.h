#pragma once

#include <string>

class Memory {
private:
	char memory[4096];
	unsigned short stack[16];
	unsigned short sp; //rsp;
	unsigned char fontSet[80];
public:
	void loadToMemory();//fstream
	void loadFontset();
	void loadRom(std::string path);
};