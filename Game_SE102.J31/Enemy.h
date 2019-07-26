#pragma once
#include "Object.h"
#include "EnemySprite.h"
class Enemy : public Object
{
protected:
	std::unordered_map<State, Animation*> animations;
	Animation* curAnimation;
	Rect groundBound;

public:
	float speed;
	State stateName;
	bool isActive, isOutScreen;
	int bulletCount;
	int bullets;


	Enemy();
	~Enemy() {};

	void Respawn();
	void ChangeState(State newState);
	virtual void Update(float dt);
	virtual void Render(float cameraX = 0, float cameraY = 0);
};