#pragma once
#include "Bullet.h"

class BulletWizard : public Bullet
{
public:

	BulletWizard()
	{
		activeAnimation = new Animation(BULLET, 0);
		type = BOSS1;
		height = 16;
		width = 16;
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
			vx = 0.1f;
			vy = 0;
			break;
		case 2:
			activeAnimation = new Animation(BULLET, 2);
			vy = -0.2f;
			vx = 0.0f;
			break;
		default: 
			activeAnimation = new Animation(BULLET, 0);
			vx = 0.08f;
			vy = 0;
			break;
		}
		
	}
};