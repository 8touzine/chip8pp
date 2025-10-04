// chip8pp.cpp : Defines the entry point for the application.
//

#include "chip8pp.h"

using namespace std;

int main(int argc, char* args[])
{
	printf("CHIP8PP");
	Core* core = new Core();

	core->mainLoop();

	delete core;

	return 0;
}
