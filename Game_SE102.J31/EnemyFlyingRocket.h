#pragma once
#include "Enemy.h"

class EnemyFlyingRocket : public Enemy
{
public:
	bool isOnGround;
	float delayTime;
	int maxDistanceX;
	int maxDistanceY;

	EnemyFlyingRocket();
	~EnemyFlyingRocket() {};
	void CheckGroundCollision(std::unordered_set<Platform*> grounds);
	float activeDistance;
	void UpdateDistance(float dt);
	void Update(float dt);
	void ChangeState(State StateName);
	void Render(float cameraX = 0, float cameraY = 0);
};
