#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerDashingState.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState();
	void Update(float dt);
	void HandleKeyboard();
};