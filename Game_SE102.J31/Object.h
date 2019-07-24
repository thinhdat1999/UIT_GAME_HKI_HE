#pragma once
#include "GameGlobal.h"
#include "SpriteManager.h"
#include "Animation.h"
#include "Camera.h"
#include "Collision.h"

class Object
{
public:
	Object() {}
	virtual ~Object() {}

	Tag tag;									// Tag định loại Object
	Type type;
	float spawnX, spawnY;
	float posX, posY;							// Vị trí (đồng thời là tâm của Object đó)
	float screenX, screenY;
	float vx, vy;								// Vận tốc
	float dx, dy;
	int width, height;							// Kích thước
	bool isReverse;								// Kiểm tra lật hình theo chiều ngang
	bool isDead;

	Rect GetRect();
	BoundingBox GetBoundingBox();

	void Update(float dt);
	bool IsCollide(Rect r);
	virtual void Render(float cameraX, float cameraY) {}
};