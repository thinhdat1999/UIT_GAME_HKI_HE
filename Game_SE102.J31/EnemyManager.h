#pragma once
#include "EnemyBlueSoldier.h"
#include "EnemyWizard.h"
#include "EnemyRocketSoldier.h"
#include "EnemyMiniBoss.h"
#include "MovingPlatform.h"
#include "SplittingPlatform.h"
#include "LightControl.h"
class EnemyManager
{
public:
	EnemyManager() {};
	~EnemyManager() {};

	static Enemy* CreateEnemy(int enemyID)
	{
		switch (enemyID)
		{
		case 1: return new EnemyBlueSoldier();
		case 2: return new EnemyWizard();
		case 3: return new EnemyRocketSoldier();
		case 4: return new EnemyMiniBoss();
		case 5: return new SplittingPlatform();
		case 6: return new MovingPlatform();
		case 11: return new LightControl();
		default: return NULL;
		}
	}
};