#pragma once
#include "Object.h"
#include "EnemySprite.h"
#include <unordered_set>
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
	D3DCOLOR originalColor = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR flashColor = D3DCOLOR_ARGB(0, 255, 255, 255);
	D3DCOLOR curColor;
	Enemy();
	~Enemy() {};

	void Respawn();
	void ChangeState(State newState);
	Rect GetSpawnRect();
	bool isFinishAttack();
	virtual void Update(float dt);
	virtual void Render(float cameraX = 0, float cameraY = 0);
	virtual void DetectGround(std::unordered_set<Platform*> grounds);
	void UpdateColor();
};