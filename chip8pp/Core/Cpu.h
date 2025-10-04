#pragma
#include <iomanip>

class Cpu {
private:
	uint8_t V[16] = { 0 }; //general purpose registers
	unsigned short I;
	uint16_t PC;//rip
public:

	Cpu();
	~Cpu() = default;
	uint8_t* getV();
	unsigned short* getI();
	uint16_t* getPC();

};