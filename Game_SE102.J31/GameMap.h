#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "SpriteManager.h"
#include "GameGlobal.h"
#include "Camera.h"
#include <fstream>
#include "string"
#include <math.h>
#include <iostream>
#include "Player.h"
class GameMap
{
public:
	GameMap(const char* filePath);
	int mWidth, mHeight;
	void Update(float dt);
	void Render();
	int getRow();
	int getColumn();
	Rect rect;
	~GameMap();

private:
	void LoadMap(const char* filePath);

	int **mapMatrix;
	int rows, columns;
	int cBegin, cEnd;
	int rBegin, rEnd;
};
