#include "Core.h"


Core::Core()
{
	*cpu = Cpu();
	*cpu->getPC() = 0x200;
	PC = 0x200;
}

bool Core::init()
{
	bool success = true;

	win = SDL_CreateWindow(
		"chip8pp",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		IDisplayBridge::WINDOWW,
		IDisplayBridge::WINDOWH,
		SDL_WINDOW_SHOWN);

	if (win == NULL)
	{
		printf("problem window");
		success = false;
	}
	else
	{
		printf("window init OK");
		rendZER = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (rendZER == NULL)
		{
			printf("renderer problem");
			success = false;
		}
	}
	return success;
}

void Core::close()
{
	delete memory;
	delete opcodeprocessor;
	delete display;
	SDL_DestroyRenderer(rendZER);
	SDL_DestroyWindow(win);
	win = NULL;
	SDL_Quit();
}

void Core::mainLoop()
{
	if (!init())
	{
		printf("failed to initiate SDL");
	}
	else
	{
		bool quit = false;

		SDL_Event e;
		memory = new Memory();
		memory->loadFontset();
		memory->loadRom("rom/current.ch8");
		opcodeprocessor = new OpcodeProcessor();
		display = new Window(rendZER);
		display->init();
		while (!quit)
		{
			std::cout << PC << "\n";

			Uint32 frameStart = SDL_GetTicks();

			while (SDL_PollEvent(&e) != 0)
			{

				handleInput(e, quit);
			
			}

				if (!awaitingKey)
				{

					opcode = fetchOpcode();
					decode(opcode);

				}
				else
				{
					printf("AWAITING KEY");
				}
				
			

				opcodeprocessor->tickTimers(&delay_timer, &sound_timer);
				if (drawFlag)
				{
					display->draw(framebuffer);
				}
				
								
			
			Uint32 frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < FRAME_DELAY)
			{
				SDL_Delay(FRAME_DELAY - frameTime);
			}
		}
		close();
	}
}

void Core::handleInput(SDL_Event& e, bool& quit)
{
	if (e.type == SDL_QUIT)
	{
		quit = true;
	}
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) 
	{
		auto input = keyboard.find(e.key.keysym.sym);
		if (input != keyboard.end())
		{
			opcodeprocessor->setKey(input->second, true, &PC, key, V, &awaitingKey, &awaitingRegister);
			printf("pressed");
		}
		
	} 
	else if (e.type == SDL_KEYUP)
	{
		auto input = keyboard.find(e.key.keysym.sym);
		if (input != keyboard.end())
		{
			printf("release");
			opcodeprocessor->setKey(input->second, false, &PC, key, V, &awaitingKey, &awaitingRegister);
		}
	}
}


uint16_t Core::fetchOpcode()
{
	uint8_t high = memory->getMemory()[PC];
	uint8_t low = memory->getMemory()[PC + 1];
	
	uint16_t opcde = (high << 8) | low;
	std::cout << "fetch"
		<< "PC=" << PC
		<< " high=" << std::hex << (int)high
		<< " low=" << (int)low
		<< " opcode=" << opcde << std::dec << "\n";
	return opcde;
}

void Core::decode(uint16_t opcode)
{
	std::cout << "decode"
		<< "PC=" << PC	
		<< " opcode=" << opcode << std::dec << "\n";
	switch (opcode & 0xF000)
	{
	case 0x0000:
		switch (opcode & 0x000F)
		{
		case 0x0000:
			opcodeprocessor->clearFrame(framebuffer, &drawFlag, &PC);
			break;
		case 0x000E:
			opcodeprocessor->returnFromSubroutine(&PC, memory->getStack(), memory->getSp());
			break;
		default:
			printf("unkown opcode 0x0000");
			PC += 2;
			break;
		}
		break;
	case 0x1000:
		opcodeprocessor->jumpToAdress(opcode, &PC);
		break;
	case 0x2000:
		opcodeprocessor->callSubroutine(opcode, &PC,memory->getStack(), memory->getSp());
		break;
	case 0x3000:
		opcodeprocessor->skipNext1(opcode, V, &PC);
		break;
	case 0x4000:
		opcodeprocessor->skipNext2(opcode, V, &PC);
		break;
	case 0x5000:
		opcodeprocessor->skipNext3(opcode, V, &PC);
		break;
	case 0x6000:
		opcodeprocessor->setVxToVn(opcode, V, &PC);
		break;
	case 0x7000:
		opcodeprocessor->addNnToVx(opcode, V, &PC);
		break;
	case 0x8000:
		opcodeprocessor->vx8FFF(opcode, V, &PC);
		break;
	case 0x9000:
		opcodeprocessor->op9FFF(opcode, V, &PC);
		break;
	case 0xA000:
		opcodeprocessor->opAFFF(opcode, &I, &PC);
		break;
	case 0xB000:
		opcodeprocessor->opBFFF(opcode, &PC, V);
		break;
	case 0xC000:
		opcodeprocessor->opCFFF(opcode, &PC, V);
		break;
	case 0xD000:
		opcodeprocessor->opD000(opcode, framebuffer, V, &I, memory, &drawFlag, &PC);
		break;
	case 0xE000:
		opcodeprocessor->opEFFF(opcode, &PC, V, key);
		break;
	case 0xF000:
		switch (opcode & 0x00FF)
		{
		case 0x0007:
			opcodeprocessor->opFF07(opcode, &delay_timer, &PC, V);
			break;
		case 0x0015:
			opcodeprocessor->opFF15(opcode, &delay_timer, &PC, V);
			break;
		case 0x0018:
			opcodeprocessor->opFF18(opcode, &sound_timer, &PC, V);
			break;
		case 0x000A:
			opcodeprocessor->opFF0A(opcode, &awaitingKey, &awaitingRegister);
			break;
		case 0x000E:
			printf("unkown opcode FXXE");
			PC += 2;
			break;
		case 0x001E:
			opcodeprocessor->opFF1E(opcode, &PC, V, &I);
			break;
		case 0x0029:
			opcodeprocessor->opFF29(opcode, &PC, V, &I);
			break;
		case 0x0033:
			opcodeprocessor->opFF33(opcode, &PC, memory, &I, V);
			break;
		case 0x0055:
			opcodeprocessor->opFF55(opcode, &PC, memory, V, &I);
			break;
		case 0x0065:
			opcodeprocessor->opFF65(opcode, &PC, memory, V, &I);
			break;

		default:
			printf("unkown opcode F000");
			PC += 2;
			break;
		}
		break;
	default:
		printf("unkown opcode main");
		PC += 2;
		break;
	}
}
