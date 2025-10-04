#include "Memory.h"

void Memory::loadToMemory(std::vector<unsigned char> rom, size_t offset)
{  
    //size_t as rom.size() returns size_t
    for (size_t i = 0; i < rom.size(); i++)
    {
        if (rom.size() > MEMORY_SIZE)
        {
            offset = 0;
        }
        if (offset + i < MEMORY_SIZE)
        {
            memory[offset + i] = rom[i];
        }
       
    }
}

void Memory::loadFontset()
{
    loadToMemory(fontset, 0);
}

void Memory::loadRom(std::string path)
{
    std::ifstream rom(path, std::ios::binary | std::ios::ate);

    if (!rom.is_open())
    {
        printf("problem reading ROM");
        return;
    }
    //size of binary
    std::streamsize size = rom.tellg();
    rom.seekg(0, std::ios::beg);

    if (size > 0)
    {
        std::vector<unsigned char> buffer(size);
        

        if (rom.read(reinterpret_cast<char*>(buffer.data()), size))
        {
            loadToMemory(buffer, 0x200);
        }
    }
    
    
    
}

unsigned char* Memory::getMemory()
{
    return memory;
}

unsigned short* Memory::getStack()
{
    return stack;
}

unsigned int* Memory::getSp()
{
    return &sp;
}
