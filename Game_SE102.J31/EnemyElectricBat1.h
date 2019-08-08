#pragma once

#include "Enemy.h"
class EnemyElectricBat1 : public Enemy
{
public:
	EnemyElectricBat1();
	~EnemyElectricBat1() {};

	float activeDistance;

	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};