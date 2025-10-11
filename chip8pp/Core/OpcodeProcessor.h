#pragma once
#include <cstdlib>
#include "../Memory/Memory.h"
#include "../Core/Cpu.h"

class OpcodeProcessor {
private:
	int screenWidth;
	int screenHeight;

public:

	OpcodeProcessor(int screenW = 64, int screenH = 32);
	~OpcodeProcessor() = default;

	void clearFrame(
		uint8_t* framebuffer, 
		bool* drawflag,
		Cpu* cpu);
	void returnFromSubroutine(
		Cpu* cpu,
		uint16_t* stack,
		unsigned int* sp);
	void jumpToAdress(uint16_t opcode, uint16_t* pc);
	void callSubroutine(
		uint16_t opcode,
		Cpu* cpu,
		uint16_t* stack,
		unsigned int* sp);
	void skipNext1(
		uint16_t opcode,
		Cpu* cpu);
	void skipNext2(
		uint16_t opcode,
		Cpu* cpu);
	void skipNext3(
		uint16_t opcode,
		Cpu* cpu);
	void setVxToVn(
		uint16_t opcode,
		Cpu* cpu);
	void addVxToVn(
		uint16_t opcode,
		Cpu* cpu);
	void addNnToVx(
		uint16_t opcode,
		Cpu* cpu);
	void vx8FFF(
		uint16_t opcode,
		Cpu* cpu);
	void op9FFF(
		uint16_t opcode,
		Cpu* cpu);
	void opAFFF(
		uint16_t opcode,
		Cpu* cpu);
	void opBFFF(
		uint16_t opcode,
		Cpu* cpu);
	void opCFFF(
		uint16_t opcode,
		Cpu* cpu);
	void opEFFF(
		uint16_t opcode,
		Cpu* cpu,
		uint8_t* key);
	void beeping();
	void tickTimers(
		uint8_t* delay_timer,
		uint8_t* sound_timer);
	void opFF18(
		uint16_t opcode,
		uint8_t* sound_timer,
		Cpu* cpu);
	void opFF15(
		uint16_t opcode,
		uint8_t* delay_timer,
		Cpu* cpu);
	void opFF07(
		uint16_t opcode,
		uint8_t* delay_timer,
		Cpu* cpu);
	void setKey(
		int index, 
		bool pressed, 		
		uint8_t* key, 
		Cpu* cpu,
		bool* waitingKey,
		uint8_t* awaitingRegister);
	void opFF0A(
		uint16_t opcode,
		bool* waitingKey,
		uint8_t* awaitingRegister);
	void opFF1E(
		uint16_t opcode,
		Cpu* cpu);
	void opFF29(
		uint16_t opcode,
		Cpu* cpu);
	void opFF33(
		uint16_t opcode, 
		uint16_t* pc,
		Memory* mem,
		Cpu* cpu);
	void opD000(
		uint16_t opcode,
		uint8_t* framebuffer,
		Memory* mem,
		bool* drawflag,
		Cpu* cpu);
	void detectPixelToDraw(
		uint8_t x, 
		int bit, 
		uint8_t y, 
		int row, 
		uint8_t spriteByte, 
		uint8_t* framebuffer, 
		Cpu* cpu);
	/*uint8_t detectCollision(
		uint8_t x, 
		uint8_t y, 
		uint8_t* framebuffer);*/
	void opFF55(
		uint16_t opcode, 
		Memory* mem,
		Cpu* cpu);
	void opFF65(
		uint16_t opcode,
		Memory* mem,
		Cpu* cpu);
};