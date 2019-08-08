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
class Map
{
public:
	Map(int level);
	int width, height;
	void Update();
	void Render();
	Rect rect;

private:
	int **mapMatrix;
	int rows, columns;
	int cBegin, cEnd;
	int rBegin, rEnd;
	Tag mapLevel;
};
