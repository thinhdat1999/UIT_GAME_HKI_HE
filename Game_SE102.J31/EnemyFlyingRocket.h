#pragma once
#include "Enemy.h"

class EnemyFlyingRocket : public Enemy
{
public:
	float delayTime;
	int maxDistanceX;
	int maxDistanceY;

	EnemyFlyingRocket();
	~EnemyFlyingRocket() {};

	float activeDistance;
	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};
