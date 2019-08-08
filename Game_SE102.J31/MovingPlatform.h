#pragma once
#include "Enemy.h"

class MovingPlatform : public Enemy {

public:
	int maxDistanceX;
	int maxDistanceY;
	float delayTime;
	float oldPosY;
	Platform *platform;
	MovingPlatform();
	~MovingPlatform() {}
	void UpdateDistance(float dt);
	void Update(float dt);
	void Render(float cameraX = 0, float cameraY = 0);
	void ChangeState(State StateName);
};