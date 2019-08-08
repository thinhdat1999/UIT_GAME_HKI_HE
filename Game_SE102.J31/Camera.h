#pragma once
#include "GameGlobal.h"

class Camera
{
private:
	static Camera* instance;
	bool isLock;
public:
	// Tọa độ world (top,left)
	float worldY;
	// Tọa độ viewport
	float x, y;
	int width, height;

	static Camera* GetInstance();
	Camera();
	Rect GetRect();
	bool isLocked();
	void LockCamera();
	void Unlock();
	void Update(Rect MapRect);
};