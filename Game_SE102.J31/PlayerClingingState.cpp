#include "PlayerClingingState.h"

PlayerClingingState::PlayerClingingState()
{
	player->_allow[CLINGING] = false;
	player->_allow[ATTACKING] = false;
	player->_allow[JUMPING] = false;
	player->isOnWall = true;
	player->isOnGround = false;
	player->vx = player->dx = 0;
	player->vy = player->dy = 0;
	StateName = CLINGING;
}

void PlayerClingingState::Update(float dt)
{
	this->HandleKeyboard();
}

void PlayerClingingState::HandleKeyboard()
{
	if (keyCode[DIK_X])
	{
		if (player->isReverse && keyCode[DIK_LEFT])
		{
			player->isReverse = false;
			player->posX--;
			player->isOnWall = false;
			player->ChangeState(new PlayerJumpingState());
		}

		else if (!player->isReverse && keyCode[DIK_RIGHT])
		{
			player->isReverse = true;
			player->posX++;
			player->isOnWall = false;
			player->ChangeState(new PlayerJumpingState());
		}
		else {
			player->isOnWall = false;
			player->ChangeState(new PlayerJumpingState());
		}
	}
	else if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT]) {
		if (player->isReverse && keyCode[DIK_LEFT])
		{
			player->isReverse = false;
			player->posX--;
		}

		else if (!player->isReverse && keyCode[DIK_RIGHT])
		{
			player->isReverse = true;
			player->posX++;
		}
	}
	else if (keyCode[DIK_DOWN])
	{
		player->isOnWall = false;
		player->ChangeState(new PlayerFallingState());
	}

	//else if (keyCode[DIK_UP] || keyCode[DIK_DOWN])
	//{
	//	if (player->wallBound.type == 2)
	//	{
	//		player->ChangeState(new PlayerClimbingState());
	//		return;
	//	}
	//}
}