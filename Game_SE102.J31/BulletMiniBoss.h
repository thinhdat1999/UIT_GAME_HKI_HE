#pragma once
#include "Bullet.h"
class BulletMiniBoss : public Bullet
{
public:
	int delayTime;
	bool isOut;
	//Type 0: Barrel
	//Type 1: Bullet
	BulletMiniBoss()
	{
		activeAnimation = new Animation(BULLET, 4);
		this->type = BOSS2;
		this->height = 14;
		this->width = 22;
		vx = 0.08f;
		vy = 0.3f;
		bulletType = 0;
		delayTime = 1500;
	}
	void UpdateDistance(float dt)
	{
		if (bulletType == 0) {
			//delayTime -= dt;
			//if (delayTime < 0) {
			//	//if(vy > 0)
			//	//	vy -= 0.014f;
			//	//else if (vy <= 0) {
			//	//	vy = -0.25f;
			//	//}
			//	if (vy > 0)
			//		vy -= 0.014f;
			//	if (vy <= 0)
			//		vy = -0.3f;
			if(isOut){
				if(vy > 0)
				if (vy > 0)
					vy -= 0.014f;
				if (vy <= 0)
					vy = -0.3f;
				this->dx = vx * dt;
				this->dy = vy * dt;
				if (isOnGround) {
					ChangeState(DEAD);
				}
			}
			else {
				this->dx = 0;
				this->dy = 0;
			}
		}
		else {
			this->dx = vx * dt;
		}
	}
	void ChangeType(int type) {
		switch (type) {
		case 1:
			activeAnimation = new Animation(BULLET, 3);
			this->height = 14;
			this->width = 16;
			vx = 0.25f;
			vy = 0;
			break;
		default:
			activeAnimation = new Animation(BULLET, 4);
			this->height = 14;
			this->width = 22;
			vx = 0.08f;
			vy = 0.3f;
			break;
		}

	}
};