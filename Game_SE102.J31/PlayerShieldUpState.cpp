#include "PlayerShieldUpState.h"

PlayerShieldUpState::PlayerShieldUpState()
{
	player->vx = 0;
	player->vy = 0;
	player->_allow[RUNNING] = true;
	player->_allow[JUMPING] = true;
	StateName = SHIELD_UP;
}

void PlayerShieldUpState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí các sự kiện bàn phím cho nhân vật
void PlayerShieldUpState::HandleKeyboard()
{
	// Nhấn phím di chuyển -> RUNNING
	if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		player->ChangeState(new PlayerRunningState());
	}
	/* Nhấn phím DOWN -> STANDING*/
	else if (keyCode[DIK_DOWN])
	{
		player->ChangeState(new PlayerStandingState());
	}
}

