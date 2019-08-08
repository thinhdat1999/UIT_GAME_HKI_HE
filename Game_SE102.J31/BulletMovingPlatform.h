#pragma once
#include "Bullet.h"

class BulletMovingPlatform : public Bullet {
public:
	BulletMovingPlatform() {
		//Vertical
		activeAnimation = new Animation(BULLET, 10);
		this->type = MOVING_PLATFORM;
		this->height = 12;
		this->width = 8;
		bulletType = 0;
		this->dx = this->vx = this->dy = this->vy = 0;
	}
	void UpdateDistance(float dt) {
		this->dx = vx * dt;
	}
	void ChangeType(int type) {
		switch (type) {
		case 1:
			//Horizontal
			activeAnimation = new Animation(BULLET, 11);
			this->height = 8;
			this->width = 16;
			vx = 0.25f;
			vy = 0;
			break;
		default:
			activeAnimation = new Animation(BULLET, 0);
			this->height = 8;
			this->width = 16;
			vx = 0.1f;
			vy = 0;
			break;
		}
	}
};