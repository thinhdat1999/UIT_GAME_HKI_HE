#pragma once
#include "Enemy.h"
#include <cmath>
class MovingPlatform : public Enemy {

public:
	int platformID;
	int maxDistanceX;
	int maxDistanceY;
	float rotationRadius = 0.2f; 
	float angularSpeed = 2.0f;
	float angle;
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