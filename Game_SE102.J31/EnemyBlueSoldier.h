#pragma once
#include "Enemy.h"

class EnemyBlueSoldier : public Enemy
{
private:
	Platform curGroundBound;
public:
	bool isOnGround;
	float delayTime, delay;
	float activeDistance;
	EnemyBlueSoldier();
	~EnemyBlueSoldier() {};
	void DetectCurGround(std::unordered_set<Platform*> grounds);
	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};