#pragma once
#include "EnemyBlueSoldier.h"
#include "EnemyWizard.h"
#include "EnemyRocketSoldier.h"
#include "EnemyMiniBoss.h"
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
		default: return NULL;
		}
	}
};