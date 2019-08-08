#pragma once
#include "Enemy.h"
class EnemyWizard : public Enemy
{
private:
	int health;
	float delayDead;
public:
	bool firstJump;
	bool isOnGround;
	float delayHit;
	int bulletCountdown;
	int bulletType;
	EnemyWizard();
	~EnemyWizard() {};
	void UpdateDistance(float dt);
	void UpdateState(float dt);
	void Update(float dt);
	void ChangeState(State StateName);
	void SubtractHealth();
	void CheckGroundCollision(std::unordered_set<Platform*> grounds);
	void Render(float cameraX = 0, float cameraY = 0);
};