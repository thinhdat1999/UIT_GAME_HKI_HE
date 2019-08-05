#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class PlayerShieldDownState : public PlayerState
{
//private:
//	bool _reverse;
public:
	PlayerShieldDownState();
	void Update(float dt);
	void HandleKeyboard();
};
