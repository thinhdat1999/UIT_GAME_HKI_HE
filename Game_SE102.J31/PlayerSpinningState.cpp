#include "PlayerSpinningState.h"

PlayerSpinningState::PlayerSpinningState()
{
	player->_allow[SHIELD_DOWN] = true;
	player->_allow[THROWING] = false;
	_reverse = player->isReverse;
	StateName = SPINNING;
	player->height = PLAYER_SITTING_HEIGHT;
	/*player->vy == 0.03f;*/
}

void PlayerSpinningState::Update(float dt)
{
	player->vy -= GRAVITY_SPEED;

	if (player->vy <= 0)
	{
		player->height = PLAYER_STANDING_HEIGHT;
		player->ChangeState(new PlayerFallingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerSpinningState::HandleKeyboard()
{
	if (keyCode[DIK_LEFT])
	{
		player->isReverse = false;
		player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2;
	}

	else if (keyCode[DIK_RIGHT])
	{
		player->isReverse = true;
		player->vx = _reverse ? PLAYER_RUNNING_SPEED / 2 : PLAYER_RUNNING_SPEED;
	}
}
