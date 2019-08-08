#pragma once
#include "EnemyBlueSoldier.h"
#include "EnemyWizard.h"
#include "EnemyRocketSoldier.h"
#include "EnemyMiniBoss.h"
#include "MovingPlatform.h"
#include "SplittingPlatform.h"
#include "LightControl.h"
#include "EnemyElectricBat1.h"
#include "EnemyElectricBat2.h"
#include "EnemyFlyingRocket.h"
#include "EnemyTank.h"

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
		case 7: return new EnemyTank();
		case 8: return new EnemyElectricBat1();
		case 9: return new EnemyElectricBat2();
		case 10: return new EnemyFlyingRocket();
		case 11: return new LightControl();
		default: return NULL;
		}
	}
};