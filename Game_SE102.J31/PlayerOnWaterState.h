#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerOnWaterState : public PlayerState
{
private:
	State prevState;
public:
	PlayerOnWaterState();
	~PlayerOnWaterState() {}
	void Update(float dt);
	void HandleKeyboard();
};