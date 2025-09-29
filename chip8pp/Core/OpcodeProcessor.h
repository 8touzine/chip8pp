#pragma once

class OpcodeProcessor {

public:
	void opFF65(unsigned char opcode);
	void opFF55(unsigned char opcode);
	unsigned char opD000(unsigned char opcode);
	void opFF33(unsigned char opcode);
	void opFF29(unsigned char opcode);
	void opFF1E(unsigned char opcode);
};