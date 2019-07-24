#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
	Game *game = Game::GetInstance();

	game->GameInit(hInstance, cmdShow);
	game->GameStartUp();
	game->GameRun();
	return 0;
}