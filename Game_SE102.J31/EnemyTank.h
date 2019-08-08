#pragma once
#include "Enemy.h"

class EnemyTank : public Enemy
{

public:
	EnemyTank();
	~EnemyTank() {};

	int hitcount;
	bool lastReverse;
	float delayTime, hitdelay;
	float activeDistance;
	//bool isSpinning;

	void UpdateAttackingState(int hitcount);
	void Update(float dt);
	void UpdateDistance(float dt);
	void ChangeState(State StateName);
};