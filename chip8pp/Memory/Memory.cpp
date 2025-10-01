#include "Memory.h"

unsigned char* Memory::getMemory()
{
    return memory;
}

unsigned short* Memory::getStack()
{
    return stack;
}

unsigned short* Memory::getSp()
{
    return &sp;
}
