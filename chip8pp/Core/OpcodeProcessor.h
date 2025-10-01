#pragma once
#include <cstdlib>
#include "../Memory/Memory.h"

class OpcodeProcessor {
private:
	int screenWidth;
	int screenHeight;

public:

	OpcodeProcessor(int screenW = 64, int screenH = 32);
	~OpcodeProcessor() = default;

	void clearFrame(
		unsigned char* framebuffer, 
		bool* drawflag,
		unsigned short* pc);
	void returnFromSubroutine(
		unsigned short* pc, 
		unsigned short* stack,
		unsigned short* sp);
	void jumpToAdress(unsigned char opcode, unsigned short* pc);
	void callSubroutine(
		unsigned char opcode,
		unsigned short* pc,
		unsigned short* stack,
		unsigned short* sp);
	void skipNext1(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void skipNext2(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void skipNext3(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void setVxToVn(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void addVxToVn(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void addNnToVx(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void vx8FFF(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void op9FFF(
		unsigned char opcode,
		unsigned char* V,
		unsigned short* pc);
	void opAFFF(
		unsigned char opcode,
		unsigned short* I,
		unsigned short* pc);
	void opBFFF(
		unsigned char opcode,
		unsigned short* pc,
		unsigned char* V);
	void opCFFF(
		unsigned char opcode,
		unsigned short* pc,
		unsigned char* V);
	void opEFFF(
		unsigned char opcode,
		unsigned short* pc,
		unsigned char* V,
		unsigned char* key);
	void beeping();
	void tickTimers(
		unsigned char* delay_timer,
		unsigned char* sound_timer);
	void opFF18(
		unsigned char opcode,
		unsigned char* sound_timer,
		unsigned short* pc,
		unsigned char* V);
	void opFF15(
		unsigned char opcode,
		unsigned char* delay_timer,
		unsigned short* pc,
		unsigned char* V);
	void opFF07(
		unsigned char opcode,
		unsigned char* delay_timer,
		unsigned short* pc,
		unsigned char* V);
	void setKey(
		int index, 
		bool pressed, 
		unsigned short* pc, 
		unsigned char* key, 
		unsigned char* V, 
		bool* waitingKey,
		unsigned char* awaitingRegister);
	void opFF0A(
		unsigned char opcode,
		bool* waitingKey,
		unsigned char* awaitingRegister);
	void opFF1E(
		unsigned char opcode,
		unsigned short* pc,
		unsigned char* V,
		unsigned short* I);
	void opFF29(
		unsigned char opcode,
		unsigned short* pc,
		unsigned char* V,
		unsigned short* I);
	void opFF33(
		unsigned char opcode, 
		unsigned short* pc,
		Memory* mem,
		unsigned short* I,
		unsigned char* V);
	void opD000(
		unsigned char opcode,
		unsigned char* framebuffer,
		unsigned char* V,
		unsigned short* I, 
		Memory* mem,
		bool* drawflag,
		unsigned short* pc);
	void detectPixelToDraw(
		unsigned char x, 
		int bit, 
		unsigned char y, 
		int row, 
		unsigned char spriteByte, 
		unsigned char* framebuffer, 
		unsigned char* V);
	/*unsigned char detectCollision(
		unsigned char x, 
		unsigned char y, 
		unsigned char* framebuffer);*/
	void opFF55(
		unsigned char opcode, 
		unsigned short* pc,
		Memory* mem,
		unsigned char* V,
		unsigned short* I);
	void opFF65(
		unsigned char opcode,
		unsigned short* pc,
		Memory* mem,
		unsigned char* V,
		unsigned short* I);
};