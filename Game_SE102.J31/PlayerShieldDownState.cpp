#include "PlayerShieldDownState.h"

// Khởi tạo trạng thái JUMPING với Vector JUMPING dùng để giảm tốc
// Xem vận tốc ban đầu = -Gravity_Speed
PlayerShieldDownState::PlayerShieldDownState()
{
	_reverse = player->isReverse;
	player->_allow[ATTACKING] = true;
	player->_allow[CLINGING] = true;
	player->_allow[THROWING] = false;
	player->_allow[JUMPING] = true;
	player->_allow[SHIELD_DOWN] = false;
	player->vy = -PLAYER_FALLING_SPEED;
	StateName = SHIELD_DOWN;
}

void PlayerShieldDownState::Update(float dt)
{
	
	this->HandleKeyboard();
}

void PlayerShieldDownState::HandleKeyboard()
{
	player->vx = 0;

	if (keyCode[DIK_LEFT])
	{
		player->isReverse = false;
		player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED;
	}

	else if (keyCode[DIK_RIGHT])
	{
		player->isReverse = true;
		player->vx = _reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED;
	}
	if (!keyCode[DIK_DOWN])
	{
	/*	player->height = PLAYER_STANDING_HEIGHT;
		player->posY += 8;*/

		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			player->ChangeState(new PlayerRunningState());
		}
		else
		{
			player->ChangeState(new PlayerStandingState());
		}
		player->ChangeState(new PlayerStandingState());
	}
}