#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerFallingState.h"

class PlayerSpinningState : public PlayerState
{
private:
	bool _reverse;
public:
	PlayerSpinningState();
	void Update(float dt);
	void HandleKeyboard();
};