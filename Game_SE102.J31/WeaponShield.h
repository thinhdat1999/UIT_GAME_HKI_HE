#pragma once
#include "Weapon.h"

class WeaponShield : public Weapon
{
public:
	WeaponShield()
	{
		animations[STANDING] = new Animation(WEAPON, 0);
		animations[JUMPING] = new Animation(WEAPON, 1);
		animations[SHIELD_UP] = new Animation(WEAPON, 2);
		animations[SHIELD_DOWN] = new Animation(WEAPON, 3);
		this->vx = WEAPON_SHIELD_SPEED;
		this->vy = 0;
		type = SHIELD;
		stateName = STANDING;
		width = WEAPON_SHIELD_WIDTH;
		height = WEAPON_SHIELD_HEIGHT;
		isOut = false;
		isBack = false;
	}
	void UpdateDistance(float dt) {
		this->dx = vx * dt;
		this->dy = WEAPON_SHIELD_SPEED * player->vy * dt;
		if (this->posX > player->posX) {
			if (vx > 0)
			{
				this->dx = min(WEAPON_SHIELD_MAX_DISTANCEX, this->dx);
			}
			else {
				this->isBack = true;
			}
			this->vx -= WEAPON_SHIELD_REVERSE_ACCELERATEX;
		}
		else
		{
			if (this->vx < 0)
			{
				this->dx = max(-WEAPON_SHIELD_MAX_DISTANCEX, this->dx);
			}
			this->vx += WEAPON_SHIELD_REVERSE_ACCELERATEX;
			if (vx >= 0)
				this->isBack = true;
		}
		// Nếu player đang ném vũ khí:
		if (this->GetRect().isContain(player->GetRect()) && !player->isHoldingShield)
		{
			if (!isOut)
			{
				this->isOut = true;
				this->isBack = false;
				this->posX = player->posX + (player->isReverse ? player->width : -player->width);
				this->posY = player->posY + 4;
			}
			else
			{
				this->isOut = false;
				player->isHoldingShield = true;
				player->_allow[THROWING] = true;
				/*this->isDead = true;*/
			}
		}
	}
	void Render(float cameraX = 0, float cameraY = 0)
	{
	/*	auto frameIndex = player->curAnimation->CurFrameIndex - 1;
		if (frameIndex != 0 && frameIndex != 1) return;*/
		auto sprite = curAnimation->GetSprite(0);
		sprite->_isFlipHorizontal = player->isReverse;

		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		sprite->Render(screenX, screenY);
	}
};