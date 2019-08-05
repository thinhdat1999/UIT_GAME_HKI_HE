#pragma once
#include "Bullet.h"

class BulletRocketSoldier : public Bullet {
public:
	BulletRocketSoldier() {
		activeAnimation = new Animation(BULLET, 6);
		this->type = ROCKETSOLDIER;
		this->height =11;
		this->width = 17;
		vx = 0.1f;
		vy = 0;
	}

};