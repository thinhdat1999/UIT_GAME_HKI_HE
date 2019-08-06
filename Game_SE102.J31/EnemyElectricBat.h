#pragma once
#include "Enemy.h"
class EnemyElectricBat : public Enemy
{
	EnemyElectricBat(float spawnX, float spawnY);
	~EnemyElectricBat() {};

	void UpdatePosition(float dt);
	virtual void Update(float dt);
};