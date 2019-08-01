#pragma once
#include "Bullet.h"

class BulletWizard : public Bullet
{
public:

	BulletWizard()
	{
		activeAnimation = new Animation(BULLET, 0);
		this->type = BOSS1;
		this->height = 12;
		this->width = 16;
		vx = 0.08f;
		vy = 0;
		bulletType = 0;
	}
	void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
		this->dy = vy * dt;
	}
	void ChangeType(int type) {
		switch (type) {
		case 1:
			activeAnimation = new Animation(BULLET, 1);
			this->height = 8;
			this->width = 16;
			vx = 0.15f;
			vy = 0;
			break;
		case 2:
			activeAnimation = new Animation(BULLET, 2);
			this->height = 16;
			this->width = 12;
			vy = -0.2f;
			vx = 0.0f;
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