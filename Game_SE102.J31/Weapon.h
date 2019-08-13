#pragma once
#include "Player.h"
#include "EnemyManager.h"
#include <unordered_set>
#include <map>

class Weapon : public Object
{
protected:
	unordered_map<State, Animation*> animations;
	Animation *curAnimation;
	State stateName;
public:
	bool isOut, isBack, isRender;

	Weapon()
	{
		tag = WEAPON;
	}

	~Weapon()
	{
		if (type == SHIELD)
		{
			player->_allow[THROWING] = true;
		}
	}

	virtual void Update(float dt) {
		curAnimation = animations[stateName];
		curAnimation->isReverse = player->isReverse;

		if (!isOut) {
			this->dx  = 0;
			this->dy = 0;
			this->posX = player->posX;
			this->posY = player->posY;
			switch (player->stateName) {
			case SHIELD_UP:
				stateName = SHIELD_UP;
				this->posY += 16;
				this->posX += (player->isReverse ? 2 : -2);
				this->width = WEAPON_SHIELD_UP_WIDTH;
				this->height = WEAPON_SHIELD_UP_HEIGHT;
				isRender = true;
				break;
			case SHIELD_DOWN:
				stateName = SHIELD_DOWN;
				this->posY -= 10;
				isRender = true;
				break;
				// player->isOnGround == false -> JUMPING
			case JUMPING: case FALLING:
				stateName = JUMPING;
				this->posY = player->posY + 10;
				this->posX += (player->isReverse ? -5 : 5);
				isRender = true;
				break;
			case ATTACKING_JUMP:
				stateName = STANDING;
				this->posX += (player->isReverse ? -18 : 18);
				isRender = true;
				break;
			case ATTACKING_SIT:
				stateName = JUMPING;
				this->posX += (player->isReverse ? -2 : 2);
				this->posY += -4;
				isRender = true;
				break;
			case SPINNING:
				isRender = false;
				break;
			case INJURED: {
				stateName = JUMPING;
				isRender = false;
				break;
			}
			case DASHING: {
				stateName = STANDING;
				this->posY += 6;
				this->posX += (player->isReverse ? 16 : -16);
				break;
			}
			default:
				stateName = STANDING;
				this->posY += (player->stateName != SITTING) ? 6 : -4;
				this->posX += (player->isReverse ? 9 : -9);
				this->width = WEAPON_STANDING_SHIELD_WIDTH;
				this->height = WEAPON_STANDING_SHIELD_HEIGHT;
				isRender = true;
				break;
			}
		}
		curAnimation->Update(dt);
		if (player->isOnWater || player->isDead) {
			isRender = false;
		}
	}			// Update thông số của Object sau khoảng thời gian delta-time

	virtual void Render(float cameraX = 0, float cameraY = 0)
	{
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		curAnimation->isReverse = this->isReverse;
		if (isRender)
			curAnimation->Render(screenX, screenY);
		else
			curAnimation->AlphaRender(screenX, screenY, D3DCOLOR_ARGB(0, 255, 255, 255), NULL);
	}

	virtual void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
		this->dy = vy * dt;
	}

	virtual void Update(float dt, std::unordered_set<Object*> ColliableObjects)
	{
		UpdateDistance(dt);
		if (isOut)
		{
	
			stateName = SHIELD_UP;
			this->posX += dx;
			if (isBack)	this->posY += dy;

			curAnimation = animations[stateName];
			curAnimation->isReverse = player->isReverse;
			curAnimation->Update(dt);

			auto rect = this->GetRect();
			for (auto obj : ColliableObjects)
			{
				if (rect.isContain(obj->GetRect()))
				{
					switch (obj->tag)
					{
					case ENEMY:
					{
						switch (obj->type) {
						case LIGHTCONTROL:
						{
							auto e = (LightControl*)obj;
							if (!e->flashingTime) {
								e->isAttacked = true;
							}
							break;
						}
						case BOSS1:
						{
							auto e = (EnemyWizard*)obj;
							e->SubtractHealth();
							break;
						}
						case BOSS2:
						{
							auto e = (EnemyMiniBoss*)obj;
							if (e->GetHealth() <= 3)
								e->SubtractHealth();
							break;
						}
						case MINITANK:
						{
							auto e = (EnemyTank*)obj;
							if (e->hitdelay < 200)
							{
								e->ChangeState(RUNNING);
								e->hitdelay = 1500;
							}
							break;
						}
						case SPLITTING_PLATFORM: case MOVING_PLATFORM:
						{
							break;
						}
						default:
						{
							auto e = (Enemy*)obj;
							e->ChangeState(DEAD);
							Sound::getInstance()->play("exploded");
							break;
						}
						}
						break;
					}
					case BULLET:
					{
						switch (obj->type) {
						case BOSS2:
						{
							auto b = (BulletMiniBoss*)obj;
							if (b->bulletType == 0)
								b->ChangeState(DEAD);
							break;
						}
						}
						break;
					}
					case HOLDER:
					{
						auto h = (Holder*)obj;
						h->isAttacked = true;
						break;
					}
					}
				}
			}
		}
		else if (player->isHoldingShield) {
			Update(dt);
			auto rect = this->GetRect();
			for (auto obj : ColliableObjects)
			{
				if (rect.isContain(obj->GetRect()))
				{
					switch (obj->tag)
					{
					case BULLET:
						switch (obj->type) {
						case BLUESOLDIER:
							auto b = (BulletBlueSoldier*)obj;
							if (!b->isStopped) {
								if (b->vy == 0)
								{
									b->vx = b->dx = 0;
									b->vy = b->dy = 1.0f;
									b->isStopped = true;
									break;
								}
								else {
									b->vx = b->dx = 1.0f;
									b->vy = b->dy = 0;
									b->isStopped = true;
									break;
								}
							}
						}
						break;
					}
				}
			}

		}
	}
};