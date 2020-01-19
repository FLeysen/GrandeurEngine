#include "pch.h"
#pragma comment(lib,"xinput.lib")
#include <vld.h>
#include "SDL.h"
#include "Game.h"
#include <time.h>

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) 
{
#pragma warning( pop )
	srand(unsigned int(time(nullptr)));
	DigDug::Game game{};
	game.Run();
	return 0;
}