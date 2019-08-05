#pragma once
#include "Object.h"
#include "Player.h"
#include "EnemySprite.h"
#include "Bullet.h"
#include <unordered_set>
class Enemy : public Object
{
protected:
	std::unordered_map<State, Animation*> animations;
	Animation* curAnimation;
	Platform groundBound;

public:
	float speed;
	State stateName;
	bool isActive, isOutScreen;
	int bulletCount;
	int bullets;
	int typeAI;
	D3DCOLOR originalColor = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR flashColor = D3DCOLOR_ARGB(0, 255, 255, 255);
	D3DCOLOR curColor;
	Enemy();
	~Enemy() {};

	void Respawn();
	virtual void ChangeState(State StateName);
	Rect GetSpawnRect();
	bool isFinishAttack();
	virtual void Update(float dt);
	virtual void UpdateDistance(float dt);
	virtual void Render(float cameraX = 0, float cameraY = 0);
	void DetectSpawnY(std::unordered_set<Platform*> grounds);
	virtual bool DetectGround(std::unordered_set<Platform*> grounds);
	void UpdateColor();
};