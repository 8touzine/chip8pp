#include "OpcodeProcessor.h"

OpcodeProcessor::OpcodeProcessor(int screenW, int screenH)
{
	screenWidth = screenW;
	screenHeight = screenH;
}



void OpcodeProcessor::clearFrame(
	unsigned char* framebuffer, 
	bool* drawflag,
	unsigned short* pc)
{
	int totalFrames = screenWidth * screenHeight;
	for (int x = 0; x < totalFrames; x++)
	{
		framebuffer[x] = 0;
	}

	*drawflag = true;
	*pc += 2;
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

void OpcodeProcessor::setVxToVn(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	unsigned char NN = opcode & 0x00FF;

	V[X] = (unsigned char)NN;
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
	*pc = 2;
}

void OpcodeProcessor::op9FFF(
	unsigned char opcode, 
	unsigned char* V, 
	unsigned short* pc)
{
	if (V[(opcode & 0x0F00) >> 8] != V[opcode & 0x00F0 >> 4])
	{
		*pc += 4;
	}
	*pc += 2;
}

void OpcodeProcessor::opAFFF(
	unsigned char opcode, 
	unsigned short* I, 
	unsigned short* pc)
{
	*I = opcode & 0x0FFF;
	*pc += 2;
}

void OpcodeProcessor::opBFFF(
	unsigned char opcode, 
	unsigned short* pc, 
	unsigned char* V)
{
	*pc = V[0] + (opcode & 0x0FFF);
}

void OpcodeProcessor::opCFFF(
	unsigned char opcode, 
	unsigned short* pc, 
	unsigned char* V)
{
	unsigned char X = (opcode & 0x0F00) >> 8;

	V[X] = (unsigned char)(rand() % 255) & (opcode & 0x00FF);
	pc += 2;
}

void OpcodeProcessor::opEFFF(
	unsigned char opcode, 
	unsigned short* pc, 
	unsigned char* V, 
	unsigned char* key)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	switch (opcode & 0x00FF)
	{
	case 0x9E:
		if (key[V[X]] != 0)
		{
			*pc += 4;
		}
		break;
	case 0xA1:
		if (key[V[X]] == 0)
		{
			*pc += 4;
		}
		break;
	default:
		break;
	}
	pc += 2;
}

void OpcodeProcessor::beeping()
{
	//sdl beep Mix_PlayChannel( -1, beep, 0 );
	//todo: implimenter son avec SDL
}

void OpcodeProcessor::tickTimers(
	unsigned char* delay_timer, 
	unsigned char* sound_timer)
{
	if(*delay_timer > 0)
	{
		*delay_timer--;
	}
	if (*sound_timer > 0)
	{
		*sound_timer--;

	}
	if (*sound_timer == 0)
	{
		beeping();
	}
}

void OpcodeProcessor::opFF18(
	unsigned char opcode, 
	unsigned char* sound_timer,
	unsigned short* pc, 
	unsigned char* V)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	*sound_timer = V[X];
	*pc += 2;
}

void OpcodeProcessor::opFF15(
	unsigned char opcode, 
	unsigned char* delay_timer, 
	unsigned short* pc, 
	unsigned char* V)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	*delay_timer = V[X];
	*pc += 2;
}

void OpcodeProcessor::opFF07(
	unsigned char opcode, 
	unsigned char* delay_timer, 
	unsigned short* pc, 
	unsigned char* V)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	V[X] = (unsigned char)*delay_timer;
	*pc += 2;
}



void OpcodeProcessor::setKey(
	int index, 
	bool pressed, 
	unsigned short* pc, 
	unsigned char* key, 
	unsigned char* V,
	bool* waitingKey,
	unsigned char* awaitingRegister)
{
	key[index] = (unsigned char)(pressed ? 1 : 0);
	if (waitingKey && pressed)
	{
		V[*awaitingRegister] = (unsigned char)index;
		waitingKey = false;
		*pc += 2;
	}
}

void OpcodeProcessor::opFF0A(
	unsigned char opcode, 
	bool* waitingKey, 
	unsigned char* awaitingRegister)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	*waitingKey = true;
	*awaitingRegister = X;
}

void OpcodeProcessor::opFF1E(
	unsigned char opcode, 
	unsigned short* pc,
	unsigned char* V,
	unsigned short* I)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	*I = (*I + (V[X] & 0x00FF)) & 0x0FFF;
}

void OpcodeProcessor::opFF29(
	unsigned char opcode, 
	unsigned short* pc, 
	unsigned char* V, 
	unsigned short* I)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	*I = 0x50 + (V[X]) * 5; //0x50 80 -> adress de base ou les fontset sont stocké

}

void OpcodeProcessor::opFF33(
	unsigned char opcode, 
	unsigned short* pc, 
	Memory* mem,
	unsigned short* I,
	unsigned char* V)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	mem->getMemory()[*I] = (unsigned char)(V[X]) / 100;
	mem->getMemory()[*I + 1] = (unsigned char)(((V[X]) / 10) % 10);
	mem->getMemory()[*I + 1] = (unsigned char)((V[X]) % 10);
}

void OpcodeProcessor::opD000(
	unsigned char opcode, 
	unsigned char* framebuffer, 
	unsigned char* V, 
	unsigned short* I,
	Memory* mem,
	bool* drawflag,
	unsigned short* pc)
{
	unsigned char x = V[(opcode & 0x0F00) >> 8];
	unsigned char y = V[(opcode & 0x0F00) >> 4];
	unsigned char n = opcode & 0x000F;
	V[0xF] = 0;
	for (int row = 0; row < n; row++)
	{
		unsigned char spriteByte = mem->getMemory()[*I + row]; //ligne de sprite a checker
		for (int bit = 0; bit < 8; bit++)
		{
			detectPixelToDraw(x, bit, y, row, spriteByte, framebuffer, V);
		}
	}
	*drawflag = true;
	*pc += 2;
	
}

void OpcodeProcessor::detectPixelToDraw(
	unsigned char x, 
	int bit, 
	unsigned char y, 
	int row, 
	unsigned char spriteByte, 
	unsigned char* framebuffer, 
	unsigned char* V)
{
	int pixelVector = x + bit + ((y + row) * 64);
	// bit per bit check of row
	if ((spriteByte & (0x80 >> bit)) != 0)
	{
		//1D Array
		if (framebuffer[pixelVector] == 1)
		{
			V[0xF] = 1;
			framebuffer[pixelVector] ^= 1;
		}
	}
}

void OpcodeProcessor::opFF55(
	unsigned char opcode,
	unsigned short* pc,
	Memory* mem,
	unsigned char* V,
	unsigned short* I)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	for (int i = 0; i <= X; X++)
	{
		mem->getMemory()[*I + i] = V[i];
	}
	*pc += 2;
}

void OpcodeProcessor::opFF65(
	unsigned char opcode,
	unsigned short* pc,
	Memory* mem,
	unsigned char* V,
	unsigned short* I)
{
	unsigned char X = (opcode & 0x0F00) >> 8;
	for (int i = 0; i <= X; X++)
	{
		V[i] = mem->getMemory()[*I + i];
	}
	*pc += 2;
}

