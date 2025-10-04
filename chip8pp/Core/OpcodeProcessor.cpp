#include "OpcodeProcessor.h"

OpcodeProcessor::OpcodeProcessor(int screenW, int screenH)
{
	screenWidth = screenW;
	screenHeight = screenH;
}



void OpcodeProcessor::clearFrame(
	uint8_t* framebuffer, 
	bool* drawflag,
	uint16_t* pc)
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
	uint16_t* pc, 
	uint16_t* stack, 
	unsigned int* sp)
{
	(*sp)--; // =  *sp += 1
	*pc = stack[*sp];
}

void OpcodeProcessor::jumpToAdress(uint16_t opcode, uint16_t* pc)
{
	*pc = opcode & 0x0FFF;// last 3 bytes (NNN)
}

void OpcodeProcessor::callSubroutine(
	uint16_t opcode, 
	uint16_t* pc, 
	uint16_t* stack, 
	unsigned int* sp)
{
	stack[*sp] = *pc + 2;
	(*sp)++;
	*pc = opcode & 0x0FFF;
}

void OpcodeProcessor::skipNext1(
	uint16_t opcode, 
	uint8_t* V, 
	uint16_t* pc)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t NN = opcode & 0x00FF;	

	if (V[X] == NN)
	{
		*pc += 4;
		return;
	}
	*pc += 2;
}

void OpcodeProcessor::skipNext2(
	uint16_t opcode, 
	uint8_t* V, 
	uint16_t* pc)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t NN = opcode & 0x00FF;

	if (V[X] != NN)
	{
		*pc += 4;
		return;
	}
	*pc += 2;
}

void OpcodeProcessor::skipNext3(
	uint16_t opcode, 
	uint8_t* V, 
	uint16_t* pc)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
	if (V[X] == V[Y])
	{
		*pc += 4;
		return;
	}
	*pc += 2;
}

void OpcodeProcessor::setVxToVn(
	uint16_t opcode, 
	uint8_t* V, 
	uint16_t* pc)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t NN = opcode & 0x00FF;

	V[X] = (uint8_t)NN;
	*pc += 2;
}

//void OpcodeProcessor::addVxToVn(
//	uint16_t opcode, 
//	uint8_t* V, 
//	uint16_t* pc)
//{
//	uint8_t X = (opcode & 0x0F00) >> 8;
//	uint8_t NN = opcode & 0x00FF;
//	V[X] += NN;
//	*pc += 2;
//}

void OpcodeProcessor::addNnToVx(
	uint16_t opcode, 
	uint8_t* V, 
	uint16_t* pc)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t NN = opcode & 0x00FF;
	V[X] = V[X] + NN;
	*pc += 2;
}

void OpcodeProcessor::vx8FFF(
	uint16_t opcode, 
	uint8_t* V, 
	uint16_t* pc)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	uint8_t Y = (opcode & 0x00F0) >> 4;
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
		break;
	case 0x0004:
		{
		// scope issue c++
		uint16_t sum = V[X] + V[Y];
		V[0xF] = (sum > 255) ? 1 : 0;
		V[X] = sum & 0xFF;
		}
		break;
	case 0x0005:
		{
		V[0xF] = (uint8_t)(V[X] >= V[Y] ? 1 : 0);
		uint8_t sub = V[X] - V[Y];
		V[X] = (uint8_t)sub;
		}
		break;
	case 0x0006:
		V[0xF] = (uint8_t)V[X] & 0x1;
		V[X] = (uint8_t)(V[X] & 0xFF) >> 1;
		break;
	case 0x0007:
		V[0xF] = (uint8_t)V[Y] >= V[X] ? 1 : 0;
		V[X] = (uint8_t)V[Y] - V[X];
		break;
	case 0x000E:
		V[0xF] = (V[X] & 0x80) >> 7; // 0x80 -> 1000 0000 binary
		V[X] = (uint8_t)V[X] << 1;
		break;
	default:
		break;
	}
	*pc += 2;
}

void OpcodeProcessor::op9FFF(
	uint16_t opcode, 
	uint8_t* V, 
	uint16_t* pc)
{
	if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
	{
		*pc += 4;
		return;
	}
	*pc += 2;
}

void OpcodeProcessor::opAFFF(
	uint16_t opcode, 
	uint16_t* I, 
	uint16_t* pc)
{
	*I = opcode & 0x0FFF;
	*pc += 2;
}

void OpcodeProcessor::opBFFF(
	uint16_t opcode, 
	uint16_t* pc, 
	uint8_t* V)
{
	*pc = V[0] + (opcode & 0x0FFF);
}

void OpcodeProcessor::opCFFF(
	uint16_t opcode, 
	uint16_t* pc, 
	uint8_t* V)
{
	uint8_t X = (opcode & 0x0F00) >> 8;

	V[X] = (uint8_t)(rand() % 256) & (opcode & 0x00FF);
	*pc += 2;
}

void OpcodeProcessor::opEFFF(
	uint16_t opcode, 
	uint16_t* pc, 
	uint8_t* V, 
	uint8_t* key)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
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
		*pc += 2;
		break;
	}
	
}

void OpcodeProcessor::beeping()
{
	//sdl beep Mix_PlayChannel( -1, beep, 0 );
	//todo: implimenter son avec SDL
}

void OpcodeProcessor::tickTimers(
	uint8_t* delay_timer, 
	uint8_t* sound_timer)
{
	if(*delay_timer > 0)
	{
		(*delay_timer)--;
	}
	if (*sound_timer > 0)
	{
		(*sound_timer)--;

	}
	if (*sound_timer == 0)
	{
		beeping();
	}
}

void OpcodeProcessor::opFF18(
	uint16_t opcode, 
	uint8_t* sound_timer,
	uint16_t* pc, 
	uint8_t* V)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	*sound_timer = V[X];
	*pc += 2;
}

void OpcodeProcessor::opFF15(
	uint16_t opcode, 
	uint8_t* delay_timer, 
	uint16_t* pc, 
	uint8_t* V)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	*delay_timer = V[X];
	*pc += 2;
}

void OpcodeProcessor::opFF07(
	uint16_t opcode, 
	uint8_t* delay_timer, 
	uint16_t* pc, 
	uint8_t* V)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	V[X] = (uint8_t)*delay_timer;
	*pc += 2;
}



void OpcodeProcessor::setKey(
	int index, 
	bool pressed, 
	uint16_t* pc, 
	uint8_t* key, 
	uint8_t* V,
	bool* waitingKey,
	uint8_t* awaitingRegister)
{
	key[index] = (uint8_t)(pressed ? 1 : 0);
	if (*waitingKey && pressed)
	{
		V[*awaitingRegister] = (uint8_t)index;
		*waitingKey = false;
		*pc += 2;
	}
}

void OpcodeProcessor::opFF0A(
	uint16_t opcode, 
	bool* waitingKey, 
	uint8_t* awaitingRegister)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	*waitingKey = true;
	*awaitingRegister = X;
}

void OpcodeProcessor::opFF1E(
	uint16_t opcode, 
	uint16_t* pc,
	uint8_t* V,
	uint16_t* I)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	*I = (*I + V[X]) & 0x0FFF;
	*pc += 2;
}

void OpcodeProcessor::opFF29(
	uint16_t opcode, 
	uint16_t* pc, 
	uint8_t* V, 
	uint16_t* I)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	*I = 0x50 + (V[X]) * 5; //0x50 80 -> adress de base ou les fontset sont stocké
	*pc += 2;
}

void OpcodeProcessor::opFF33(
	uint16_t opcode, 
	uint16_t* pc, 
	Memory* mem,
	uint16_t* I,
	uint8_t* V)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	mem->getMemory()[*I] = (uint8_t)(V[X]) / 100;
	mem->getMemory()[*I + 1] = (uint8_t)(((V[X]) / 10) % 10);
	mem->getMemory()[*I + 2] = (uint8_t)((V[X]) % 10);
	*pc += 2;
}

void OpcodeProcessor::opD000(
	uint16_t opcode, 
	uint8_t* framebuffer, 
	uint8_t* V, 
	uint16_t* I,
	Memory* mem,
	bool* drawflag,
	uint16_t* pc)
{
	uint8_t x = V[(opcode & 0x0F00) >> 8];
	uint8_t y = V[(opcode & 0x00F0) >> 4];
	uint8_t n = opcode & 0x000F;
	V[0xF] = 0;
	for (int row = 0; row < n; row++)
	{
		uint8_t spriteByte = mem->getMemory()[*I + row]; //ligne de sprite a checker
		for (int bit = 0; bit < 8; bit++)
		{
			detectPixelToDraw(x, bit, y, row, spriteByte, framebuffer, V);
		}
	}
	*drawflag = true;
	*pc += 2;
	
}

void OpcodeProcessor::detectPixelToDraw(
	uint8_t x, 
	int bit, 
	uint8_t y, 
	int row, 
	uint8_t spriteByte, 
	uint8_t* framebuffer, 
	uint8_t* V)
{
	int pixelVector = x + bit + ((y + row) * screenWidth);
	// bit per bit check of row
	if ((spriteByte & (0x80 >> bit)) != 0)
	{
		//1D Array
		if (framebuffer[pixelVector] == 1)
		{
			V[0xF] = 1;
			framebuffer[pixelVector] ^= 1;
		}
		else
		{
			framebuffer[pixelVector] ^= 1;
		}
	}
}

void OpcodeProcessor::opFF55(
	uint16_t opcode,
	uint16_t* pc,
	Memory* mem,
	uint8_t* V,
	uint16_t* I)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	for(int i = 0; i <= X; i++)
	{
		mem->getMemory()[*I + i] = V[i];
	}
	*pc += 2;
}

void OpcodeProcessor::opFF65(
	uint16_t opcode,
	uint16_t* pc,
	Memory* mem,
	uint8_t* V,
	uint16_t* I)
{
	uint8_t X = (opcode & 0x0F00) >> 8;
	for (int i = 0; i <= X; i++)
	{
		V[i] = mem->getMemory()[*I + i];
	}
	*pc += 2;
}

