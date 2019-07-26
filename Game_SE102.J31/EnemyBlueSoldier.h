#pragma once
#include "Enemy.h"

class EnemyBlueSoldier : public Enemy
{
public:
	EnemyBlueSoldier(float spawnX, float spawnY);
	~EnemyBlueSoldier() {};

	void Update(float dt);
};