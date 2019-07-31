#pragma once
#include "BulletWizard.h"

class BulletManager
{
public:
	static Bullet* CreateBullet(Type bulletType)
	{
		switch (bulletType)
		{
		case BOSS1: return new BulletWizard();
		}
	}
};