#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerSpinningState.h"
class PlayerJumpingState : public PlayerState
{
private:
	bool _reverse;
	int holdingTime;
public:
	PlayerJumpingState();
	void Update(float dt);
	void HandleKeyboard();
};