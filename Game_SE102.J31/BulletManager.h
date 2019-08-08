#pragma once
#include "BulletWizard.h"
#include "BulletBlueSoldier.h"
#include "BulletRocketSoldier.h"
#include "BulletMiniBoss.h"
#include "BulletMovingPlatform.h"
class BulletManager
{
public:
	static Bullet* CreateBullet(Type bulletType)
	{
		switch (bulletType)
		{
		case BOSS1: return new BulletWizard();
		case BLUESOLDIER: return new BulletBlueSoldier();
		case ROCKETSOLDIER: return new BulletRocketSoldier();
		case BOSS2: return new BulletMiniBoss();
		}
	}
};