#include "OpcodeProcessor.h"

OpcodeProcessor::OpcodeProcessor(int screenW, int screenH)
{
	screenWidth = screenW;
	screenHeight = screenH;
}



void OpcodeProcessor::clearFrame(int* framebuffer[], bool* drawflag)
{
	int totalFrames = screenWidth * screenHeight;
	for (int x = 0; x < totalFrames; x++)
	{
		*framebuffer[x] = 0;
	}

	*drawflag = true;
}

void OpcodeProcessor::returnFromSubroutine(
	unsigned short* pc, 
	unsigned short* stack, 
	unsigned short* sp)
{
	*sp--;
	*pc = stack[*sp];
}

void OpcodeProcessor::jumpToAdress(unsigned char opcode, unsigned short* pc)
{
	*pc = opcode & 0x0FFF;// last 3 bytes (NNN)
}

void OpcodeProcessor::callSubroutine(
	unsigned char opcode, 
	unsigned short* pc, 
	unsigned short* stack, 
	unsigned short* sp)
{
	stack[*sp] = *pc + 2;
	*sp++;
	*pc = opcode & 0xFFF;
}

void OpcodeProcessor::skipNext1(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	unsigned char NN = opcode & 0x00FF;

	if (V[X] == NN)
	{
		*pc += 4;
		return;
	}
	*pc += 2;
}

void OpcodeProcessor::skipNext2(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	unsigned char NN = opcode & 0x00FF;

	if (V[X] != NN)
	{
		*pc += 4;
		return;
	}
	*pc += 2;
}

void OpcodeProcessor::skipNext3(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	unsigned char Y = (opcode & 0x00F0) >> 4;
	if (V[X] == V[Y])
	{
		*pc += 4;
		return;
	}
	*pc += 2;
}

void OpcodeProcessor::addVxToVn(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	unsigned char NN = opcode & 0x00FF;
	V[X] = NN;
	*pc += 2;
}

void OpcodeProcessor::addNnToVx(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	unsigned char NN = opcode & 0x00FF;
	V[X] = V[X] + NN;
	*pc += 2;
}

void OpcodeProcessor::vx8FFF(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	unsigned char Y = (opcode & 0x00F0) >> 4;
	switch (opcode & 0x000F)
	{
		//8XY0 8XY1, 8XY2, 8XY3, 8XY4, 8XY5, 8XY6, 8XY7, 8XYE
	case 0x0000:
		V[X] = V[Y];
		break;
	case 0x0001:
		V[X] |= V[Y];
		break;
	case 0x0002:
		V[X] &= V[Y];
		break;
	case 0x0003:
		V[X] ^= V[Y];
	case 0x0004:
		unsigned char sum = V[X] + V[Y];
		V[0xF] = (unsigned char)(sum > 255) ? 1 : 0;
		V[X] = (unsigned char) sum;
		break;
	case 0x0005:
		V[0xF] = (unsigned char)(V[X] >= V[Y] ? 1 : 0);
		unsigned char sub = V[X] - V[Y];
		V[X] = (unsigned char)sub;
		break;
	case 0x0006:
		V[0xF] = (unsigned char)V[X] & 0x1;
		V[X] = (unsigned char)(V[X] & 0xFF) >> 1;
	case 0x0007:
		V[0xF] = (unsigned char)V[Y] >= V[X] ? 1 : 0;
		V[X] = (unsigned char)V[Y] - V[X];
		break;
	case 0x000E:
		V[0xF] = (V[X] & 0x80) >> 7; // 0x80 -> 1000 0000 binary
		V[X] = (unsigned char)V[Y] << 1;
	default:
		break;
	}

}
