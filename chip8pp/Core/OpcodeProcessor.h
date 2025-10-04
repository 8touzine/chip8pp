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
		uint16_t* pc);
	void returnFromSubroutine(
		uint16_t* pc, 
		unsigned short* stack,
		unsigned int* sp);
	void jumpToAdress(unsigned short opcode, uint16_t* pc);
	void callSubroutine(
		unsigned short opcode,
		uint16_t* pc,
		unsigned short* stack,
		unsigned int* sp);
	void skipNext1(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void skipNext2(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void skipNext3(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void setVxToVn(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void addVxToVn(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void addNnToVx(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void vx8FFF(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void op9FFF(
		unsigned short opcode,
		unsigned char* V,
		uint16_t* pc);
	void opAFFF(
		unsigned short opcode,
		unsigned short* I,
		uint16_t* pc);
	void opBFFF(
		unsigned short opcode,
		uint16_t* pc,
		unsigned char* V);
	void opCFFF(
		unsigned short opcode,
		uint16_t* pc,
		unsigned char* V);
	void opEFFF(
		unsigned short opcode,
		uint16_t* pc,
		unsigned char* V,
		unsigned char* key);
	void beeping();
	void tickTimers(
		unsigned char* delay_timer,
		unsigned char* sound_timer);
	void opFF18(
		unsigned short opcode,
		unsigned char* sound_timer,
		uint16_t* pc,
		unsigned char* V);
	void opFF15(
		unsigned short opcode,
		unsigned char* delay_timer,
		uint16_t* pc,
		unsigned char* V);
	void opFF07(
		unsigned short opcode,
		unsigned char* delay_timer,
		uint16_t* pc,
		unsigned char* V);
	void setKey(
		int index, 
		bool pressed, 
		uint16_t* pc, 
		unsigned char* key, 
		unsigned char* V, 
		bool* waitingKey,
		unsigned char* awaitingRegister);
	void opFF0A(
		unsigned short opcode,
		bool* waitingKey,
		unsigned char* awaitingRegister);
	void opFF1E(
		unsigned short opcode,
		uint16_t* pc,
		unsigned char* V,
		unsigned short* I);
	void opFF29(
		unsigned short opcode,
		uint16_t* pc,
		unsigned char* V,
		unsigned short* I);
	void opFF33(
		unsigned short opcode, 
		uint16_t* pc,
		Memory* mem,
		unsigned short* I,
		unsigned char* V);
	void opD000(
		unsigned short opcode,
		unsigned char* framebuffer,
		unsigned char* V,
		unsigned short* I, 
		Memory* mem,
		bool* drawflag,
		uint16_t* pc);
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
		unsigned short opcode, 
		uint16_t* pc,
		Memory* mem,
		unsigned char* V,
		unsigned short* I);
	void opFF65(
		unsigned short opcode,
		uint16_t* pc,
		Memory* mem,
		unsigned char* V,
		unsigned short* I);
};