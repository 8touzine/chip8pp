#pragma once

class OpcodeProcessor {
private:
	int screenWidth;
	int screenHeight;

public:

	OpcodeProcessor(int screenW = 64, int screenH = 32);
	~OpcodeProcessor() = default;

	void clearFrame(int* framebuffer[], bool* drawflag);
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
	void op9FFF(unsigned char opcode);
	void opAFFF(unsigned char opcode);
	void opBFFF(unsigned char opcode);
	void opCFFF(unsigned char opcode);
	void opEFFF(unsigned char opcode);
	void beeping();
	void tickTimers();
	void opFF18(unsigned char opcode);
	void opFF15(unsigned char opcode);
	void opFF07(unsigned char opcode);
	void setKey(int index, bool pressed);
	void opFF0A(unsigned char opcode);
	void opFF1E(unsigned char opcode);
	void opFF29(unsigned char opcode);
	void opFF33(unsigned char opcode);
	unsigned char opD000(unsigned char opcode);
	void opFF55(unsigned char opcode);
	void opFF65(unsigned char opcode);
};