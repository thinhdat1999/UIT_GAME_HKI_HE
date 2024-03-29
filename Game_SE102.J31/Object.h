﻿#pragma once
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
	float screenX, screenY;						// vị trí trên màn hình
	float vx, vy;								// Vận tốc
	float dx, dy;
	int width, height;							// Kích thước
	int flashingTime;
	bool isReverse;								// Kiểm tra lật hình theo chiều ngang
	bool isDead, isAttacked;
	int typeAI;

	Rect GetRect();
	BoundingBox GetBoundingBox();
	virtual void SubtractHealth() {};
	virtual void ChangeState(State stateName) {}
	void Update(float dt);
	bool IsCollide(Rect r);
	virtual void Render(float cameraX, float cameraY) {}
};