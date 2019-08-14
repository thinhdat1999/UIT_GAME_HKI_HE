#pragma once
#include "Bullet.h"

class BulletRocketSoldier : public Bullet {
public:
	int bulletType;
	BulletRocketSoldier() {
		activeAnimation = new Animation(BULLET, 6, 7, DEFAULT_TPF >> 1);
		this->type = ROCKETSOLDIER;
		this->height = 12;
		this->width = 16;
		vx = 0.1f;
		vy = 0;
		bulletType = 0;
	}
	void UpdateDistance(float dt)
	{
		if (this->bulletType == 0) {
			this->dx = vx * dt;
			this->dy = vy * dt;
		}
		else {
			if ((((this->vx < 0) && (this->posX - this->spawnX < -15))
				|| ((this->vx > 0) && (this->posX - this->spawnX > 15))) && !this->vy)
			{
				this->vy = 0.1f;
				this->curAnimation = new Animation(BULLET, 8, 9, DEFAULT_TPF);
			}
			this->dx = vx * dt;
			this->dy = vy * dt;
		}
	}
	void ChangeType(int type) {
		switch (type) {
		case 1:
			bulletType = 1;
			activeAnimation = new Animation(BULLET, 6, 7, DEFAULT_TPF);
			this->height = 14;
			this->width = 12;
			vx = 0.08f;
			vy = 0;
			break;
		default:
			activeAnimation = new Animation(BULLET, 6, 7, DEFAULT_TPF >> 1);
			this->height = 12;
			this->width = 14;
			vx = 0.1f;
			vy = 0;
			bulletType = 0;
			break;
		}

	}
};