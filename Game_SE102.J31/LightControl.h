#pragma once
#include "Enemy.h"

class LightControl : public Enemy {
public: 
	bool isAttacked;
	LightControl() {
		tag = ENEMY;
		type = LIGHTCONTROL;
		width = 16;
		height = 16;
		isAttacked = false;
		isActive = true;
	}
	void Render(float cameraX, float cameraY) {}
	void Update(float dt) {}
};