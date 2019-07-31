#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState()
{
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
	player->posX = player->isReverse ? 2 : -2;
	StateName = INJURED;
}

void PlayerInjuredState::Update(float dt)
{
	/*if (player->isOnGround)
	{
		player->ChangeState(new PlayerStandingState());
	}*/
	player->ChangeState(new PlayerStandingState());
}

State PlayerInjuredState::GetName()
{
	return INJURED;
}