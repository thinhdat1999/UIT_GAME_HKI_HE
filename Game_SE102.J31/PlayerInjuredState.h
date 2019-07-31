#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerInjuredState : public PlayerState
{
private:
	int delayTime;
public:
	PlayerInjuredState();
	void Update(float dt);
	void HandleKeyboard() {};
	State GetName();
};