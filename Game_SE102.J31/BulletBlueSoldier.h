#pragma once
#include "Bullet.h"

class BulletBlueSoldier : public Bullet {
public:
	bool isStopped;
	BulletBlueSoldier() {
		activeAnimation = new Animation(BULLET, 5);
		this->type = BLUESOLDIER;
		this->height = 6;
		this->width = 8;
		vx = 0.2f;
		vy = 0;
	}
	void UpdateDistance(float dt) {
		this->dy = vy * dt;
		this->dx = vx * dt;
	}

};