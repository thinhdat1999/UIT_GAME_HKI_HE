#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState()
{
	player->_allow[ATTACKING] = false;
	player->_allow[THROWING] = false;
	if (player->isOnWall)
	{
		player->isOnWall = false;

		if (player->isReverse)
		{
			player->posX++;
		}
		else player->posX--;
	}

	player->height = PLAYER_STANDING_HEIGHT;
	player->vy = 0.15f;
	player->vx = player->isReverse ? -0.02 : 0.02f;
	StateName = INJURED;
}

void PlayerInjuredState::Update(float dt)
{
	player->vy -= GRAVITY_SPEED;
	if (player->isOnGround)
	{
		player->ChangeState(new PlayerStandingState());
	}
}

State PlayerInjuredState::GetName()
{
	return INJURED;
}