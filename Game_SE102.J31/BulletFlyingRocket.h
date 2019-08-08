#pragma once
#include "Bullet.h"

class BulletFlyingRocket : public Bullet {
public:
	Animation *TopLeftAnim, *BotLeftAnim, *UpAnim, *DownAnim;
	float flyTime;
	BulletFlyingRocket() {
		spawnX = posX;
		activeAnimation = new Animation(BULLET, 6, 7);
		TopLeftAnim = new Animation(BULLET, 8, 9);
		BotLeftAnim = new Animation(BULLET, 10, 11);
		UpAnim = new Animation(BULLET, 12, 13);
		DownAnim = new Animation(BULLET, 14, 15);
		this->type = FLYINGROCKET;
		this->height = 11;
		this->width = 17;
		flyTime = 3500;
		vx = 0.1f;
		vy = 0;
	}

	void Update(float dt)
	{
		Bullet::Update(dt);
		flyTime -= dt;

		if (flyTime > 3000)
		{
			vx = -0.13f;
			return;
		}
		if (2700 < flyTime && flyTime < 3000)
		{
			curAnimation = BotLeftAnim;
			vy = -0.13f;
			return;
		}
		if (2200 < flyTime &&flyTime < 2700)
		{
			curAnimation = DownAnim;
			vx = 0;
			return;
		}
		if (1900 < flyTime && flyTime < 2200)
		{
			curAnimation = BotLeftAnim;
			isReverse = -true;
			vx = 0.13f;
			vy = -0.13f;
			return;
		}
		if (1400 < flyTime && flyTime < 1900)
		{
			curAnimation = activeAnimation;
			vy = 0;
			return;
		}
		if (1100 < flyTime && flyTime < 1400)
		{
			curAnimation = TopLeftAnim;
			vy = 0.13f;
			return;
		}
		if (0 < flyTime && flyTime < 1100)
		{
			curAnimation = UpAnim;
			vx = 0;
			return;
		}
		if (flyTime < 0)
			flyTime = 3500;
	}
};

