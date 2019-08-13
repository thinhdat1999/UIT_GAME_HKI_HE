#pragma once
#include "Enemy.h"

class EnemyRocketSoldier : public Enemy
{
private:
	Platform curGroundBound;
public:
	bool isOnGround;
	float delayTime;
	float activeDistance;
	int bulletType;
	EnemyRocketSoldier();
	~EnemyRocketSoldier();
	void DetectCurGround(std::unordered_set<Platform*> grounds);
	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};