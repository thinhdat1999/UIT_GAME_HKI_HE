#pragma once
#include "Enemy.h"

class SplittingPlatform : public Enemy {

public:
	float delayTime;
	bool isHasPlayerOn;
	Platform *platform;
	SplittingPlatform();
	~SplittingPlatform() {}
	void UpdateDistance(float dt);
	void Update(float dt);
	void Render(float cameraX = 0, float cameraY = 0);
	void ChangeState(State StateName);
};