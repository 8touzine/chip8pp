#include "Cpu.h"
#include "Cpu.h"
#include "Cpu.h"
#include "Cpu.h"

Cpu::Cpu()
{

}

uint8_t* Cpu::getV()
{
	return V;
}

unsigned short* Cpu::getI()
{
	return &I;
}

uint16_t* Cpu::getPC()
{
	return &PC;
}

