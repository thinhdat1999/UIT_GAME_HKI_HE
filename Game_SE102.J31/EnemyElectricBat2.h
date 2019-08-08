#pragma once
#include "Enemy.h"

class EnemyElectricBat2 : public Enemy
{
public:

	EnemyElectricBat2();
	~EnemyElectricBat2() {};

	float activeDistance;

	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};
