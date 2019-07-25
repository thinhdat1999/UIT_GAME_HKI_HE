#include "PlayerAttackingState.h"

// Khởi tạo State ATTACK (StateName tùy vào trạng thái trước đó là đánh hoặc ngồi)
PlayerAttackingState::PlayerAttackingState()
{
	_curState = player->state->StateName;
	_reverse = player->isReverse;
	switch (_curState) {
	case SITTING:
		StateName = ATTACKING_SIT;
		player->posX += (player->isReverse) ? 3 : -3;
		break;
	case JUMPING: case FALLING: case SHIELD_DOWN:
		StateName = ATTACKING_JUMP;
		break;
	case STANDING: case RUNNING: case SHIELD_UP:
		if (player->isThrowing)
		{
			StateName = THROWING;
			player->isHoldingShield = false;
		}
		else
			StateName = ATTACKING_STAND;
		break;
	}
	player->_allow[JUMPING] = player->_allow[SITTING] = false;
}

// Update lại tráng thái khi đang ATTACK
void PlayerAttackingState::Update(float dt)
{
	this->HandleKeyboard();

	// Khi đã đánh xong
	if (player->curAnimation->isLastFrame)
	{
		player->_allow[ATTACKING] = player->_allow[JUMPING] = player->_allow[SITTING] = true;

		switch (_curState)
		{
		case STANDING: case RUNNING:
			player->ChangeState(new PlayerStandingState());
			return;

		case SITTING:
			player->posY += 8;
			player->height += 8;
			player->posX += (player->isReverse) ? -3 : 3;
			player->ChangeState(new PlayerSittingState());
			return;

		case FALLING:
			player->ChangeState(new PlayerFallingState());
			return;

		case JUMPING:
			player->ChangeState(new PlayerJumpingState());
			return;
		case SHIELD_UP:
			player->ChangeState(new PlayerShieldUpState());
			return;
		}
	}
	else
	{
		// Khi chưa đánh xong / bắt đầu đánh
		player->_allow[ATTACKING] = false;

		switch (_curState)
		{
		case RUNNING: case STANDING: case SITTING:
			player->vx = 0;
			player->vy = 0;
			break;

		case JUMPING:
		{
			// Nếu đã nhảy đến độ cao nhất định -> _curState về trạng thái FALLING
			player->vy -= GRAVITY_SPEED;

	/*		if ((player->vx == SCREEN_WIDTH - player->width
				|| player->vx == player->width >> 1) && player->_allow[CLINGING])
			{
				player->ChangeState(new PlayerClingingState());
				return;
			}*/

			if (player->vy <= 0)
			{
				_curState = FALLING;
				player->vy = -PLAYER_FALLING_SPEED;
			}
			break;
		}
		}
	}
}

// Xử lí sự kiện bàn phím khi đang ATTACK
// Khi đang nhảy / rơi: nếu ngược hướng thì vận tốc theo x chậm hơn (khoảng 1/2)
void PlayerAttackingState::HandleKeyboard()
{
	if (keyCode[DIK_LEFT])
	{
		player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED / 2;
	}

	else if (keyCode[DIK_RIGHT])
	{
		player->vx = !_reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED / 2;
	}
	else player->vx = 0;
}