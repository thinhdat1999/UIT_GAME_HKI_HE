#pragma once
#include "GameGlobal.h"

class Camera
{
private:
	static Camera* instance;

public:
	// Tọa độ world (top,left)
	float worldY;
	// Tọa độ viewport
	float x, y;
	int width, height;

	static Camera* GetInstance();
	Camera();
	Rect GetRect();
	void Update(Rect MapRect);
};