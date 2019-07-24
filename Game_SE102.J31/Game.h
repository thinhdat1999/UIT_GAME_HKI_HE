#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "SceneManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "PlayScene.h"

class Game
{
private:

	static Game* _instance;
	HWND hWnd;
	WNDCLASSEX wc;
	LPDIRECTINPUT8 di8;
	LPDIRECTINPUTDEVICE8 didv8;
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
	TextureManager * gTextureManager;
	SpriteManager * gSpriteManager;
	SceneManager *gSceneManager;

public:
	Game();

	Scene * CurScene;
	void GameInit(HINSTANCE hInstance, int cmdShow);
	void GameRun(); //Khoi chay game
	void GameStartUp();
	void GameShutDown();

	//virtual void Update(int dt); //cap nhat game theo 1 khoang thoi gian dt
	void Render();//ve khung hinh
	void Update(float dt);

	//Xu ly ban phim
	void ProcessKeyboard();
	static Game* GetInstance();
};
LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);