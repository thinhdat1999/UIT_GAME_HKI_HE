#pragma once
#include "Enemy.h"

class EnemyTank : public Enemy
{
private:
	int hitcount;
public:
	EnemyTank(float spawnX, float spawnY);
	~EnemyTank() {};

	void UpdatePosition(float dt);
	virtual void Update(float dt);
};