#pragma once
#include "Enemy.h"
class EnemyMiniBoss : public Enemy
{
private:
	int health;
	float delayDead;
	float delayAttack;

public:
	Bullet *b;
	bool canShoot;
	bool isOnGround;
	int bulletType;
	EnemyMiniBoss();
	~EnemyMiniBoss() {};
	void UpdateDistance(float dt);
	void UpdateState(float dt);
	void Update(float dt);
	void ChangeState(State StateName);
	void SubtractHealth();
	void CheckGroundCollision(std::unordered_set<Platform*> grounds);
	void Render(float cameraX = 0, float cameraY = 0);
};